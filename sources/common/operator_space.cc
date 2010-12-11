//@+leo-ver=5-thin
//@+node:gcross.20101116210424.1514: * @thin operator_space.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101116210424.2281: ** << Includes >>
#include <gecode/minimodel.hh>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;
using namespace std;

//@+others
//@+node:gcross.20101116210424.1515: ** class OperatorSpace
//@+node:gcross.20101116210424.1516: *3* (constructors)
OperatorSpace::OperatorSpace(int number_of_operators, int number_of_qubits, optional<int> maximum_weight)
    : number_of_operators(number_of_operators)
    , number_of_qubits(number_of_qubits)
    , number_of_variables(number_of_qubits*number_of_operators)
    , number_of_pairs(number_of_operators/2)
    , maximum_weight(maximum_weight)
    , total_number_of_qubits(number_of_qubits+number_of_pairs)
    , last_row(number_of_operators-1)
    , last_even_row(odd_number_of_rows ? last_row-1 : last_row)
    , odd_number_of_rows(number_of_operators % 2 == 1)
    , X(*this,number_of_operators*number_of_qubits,0,1)
    , Z(*this,number_of_operators*number_of_qubits,0,1)
    , non_trivial(*this,number_of_operators*number_of_qubits,0,1)
    , O(*this,number_of_operators*number_of_qubits,0,3)
    , weights(*this,number_of_operators,0,number_of_qubits)
{
    for(int i = 0; i < number_of_variables; ++i) {
        O[i] = expr(*this,2*Z[i] + X[i]);
        non_trivial[i] = expr(*this,Z[i] || X[i]);
    }
    BoolMatrix non_trivial_matrix = getNonTrivialMatrix();
    for(int i = 0; i < number_of_operators; ++i) {
        linear(*this,non_trivial_matrix.row(i),IRT_EQ,weights[i]);
    }
    if(maximum_weight) {
        for(int i = 0; i <= last_even_row; ++i) {
            rel(*this,weights[i],IRT_LE,*maximum_weight);
        }
        if(odd_number_of_rows) {
            rel(*this,weights[last_row],IRT_LQ,*maximum_weight);
        }
    }
    branch(*this,O,INT_VAR_NONE,INT_VAL_MIN);
}

OperatorSpace::OperatorSpace(bool share, OperatorSpace& s)
    : Space(share,s)
    , number_of_operators(s.number_of_operators)
    , number_of_qubits(s.number_of_qubits)
    , number_of_variables(s.number_of_variables)
    , number_of_pairs(s.number_of_pairs)
    , maximum_weight(s.maximum_weight)
    , total_number_of_qubits(s.total_number_of_qubits)
    , last_row(s.last_row)
    , last_even_row(s.last_even_row)
    , odd_number_of_rows(s.odd_number_of_rows)
{
    X.update(*this,share,s.X);
    Z.update(*this,share,s.Z);
    non_trivial.update(*this,share,s.non_trivial);
    O.update(*this,share,s.O);
    weights.update(*this,share,s.weights);
}
//@+node:gcross.20101116222338.1276: *3* copy
Space* OperatorSpace::copy(bool share)
{
    return new OperatorSpace(share,*this);
}
//@+node:gcross.20101121200631.1631: *3* getOperators
vector<dynamic_quantum_operator> OperatorSpace::getOperators() {
    int total_number_of_qubits = number_of_pairs + number_of_qubits;
    vector<dynamic_quantum_operator> operators;
    IntMatrix O_matrix = getOMatrix();
    for(int i = 0; i < number_of_operators; ++i) {
        dynamic_quantum_operator op(total_number_of_qubits);
        for(int j = 0; j < number_of_qubits; ++j) {
            op.set(number_of_pairs+j,O_matrix(j,i).val());
        }
        operators.push_back(op);
    }
    for(int i = 0; i < number_of_pairs; ++i) {
        operators[2*i+0].set(i,1);
        operators[2*i+1].set(i,2);
    }
    return operators;
}
//@-others

}
//@-leo
