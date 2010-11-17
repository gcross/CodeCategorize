//@+leo-ver=5-thin
//@+node:gcross.20101116210424.1514: * @thin operator_space.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101116210424.2281: ** << Includes >>
#include <gecode/minimodel.hh>

#include "operator_space.hh"
//@-<< Includes >>

//@+others
//@+node:gcross.20101116210424.1515: ** class OperatorSpace
//@+node:gcross.20101116210424.1516: *3* (constructors)
OperatorSpace::OperatorSpace(int number_of_operators, int number_of_qubits)
    : number_of_operators(number_of_operators)
    , number_of_qubits(number_of_qubits)
    , number_of_variables(number_of_qubits*number_of_operators)
    , X(*this,number_of_operators*number_of_qubits,0,1)
    , Z(*this,number_of_operators*number_of_qubits,0,1)
    , non_trivial(*this,number_of_operators*number_of_qubits,0,1)
    , O(*this,number_of_operators*number_of_qubits,0,3)
{
    for(int i = 0; i < number_of_variables; ++i) {
        O[i] = expr(*this,2*Z[i] + X[i]);
        non_trivial[i] = expr(*this,Z[i] || X[i]);
    }
    branch(*this,O,INT_VAR_NONE,INT_VAL_MIN);
}

OperatorSpace::OperatorSpace(bool share, OperatorSpace& s)
    : Space(share,s)
    , number_of_operators(s.number_of_operators)
    , number_of_qubits(s.number_of_qubits)
    , number_of_variables(s.number_of_variables)
{
    X.update(*this,share,s.X);
    Z.update(*this,share,s.Z);
    non_trivial.update(*this,share,s.non_trivial);
    O.update(*this,share,s.O);
}
//@+node:gcross.20101116222338.1276: *3* copy
Space* OperatorSpace::copy(bool share)
{
    return new OperatorSpace(share,*this);
}
//@-others
//@-leo
