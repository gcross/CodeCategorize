//@+leo-ver=5-thin
//@+node:gcross.20101116210424.1511: * @thin operator_space.hh
//@@language cplusplus

#ifndef OPERATOR_SPACE_HH
#define OPERATOR_SPACE_HH

//@+<< Includes >>
//@+node:gcross.20101116210424.1512: ** << Includes >>
#include <codequest.hpp>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>
#include <vector>

using namespace Gecode;
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;
using namespace std;

//@+others
//@+node:gcross.20101117133000.1471: ** Type aliases
typedef Matrix<IntVarArgs> IntMatrix;
typedef Matrix<BoolVarArgs> BoolMatrix;
//@+node:gcross.20101117133000.1474: ** Enums
enum Pauli { I = 0, X = 1, Z = 2, Y = 3 };
//@+node:gcross.20101116210424.1513: ** struct OperatorSpace
struct OperatorSpace : public Space {

    //@+others
    //@+node:gcross.20101116210424.1674: *3* (fields)
    int number_of_operators, number_of_qubits, number_of_variables, number_of_pairs, total_number_of_qubits;

    BoolVarArray X, Z, non_trivial;
    IntVarArray O, weights;
    //@+node:gcross.20101116210424.1675: *3* (constructors)
    OperatorSpace(int number_of_operators, int number_of_qubits);
    OperatorSpace(bool share, OperatorSpace& s);
    //@+node:gcross.20101117133000.1468: *3* (methods)
    virtual Space* copy(bool share);
    IntMatrix getOMatrix() { return Matrix<IntVarArgs>(O,number_of_qubits,number_of_operators); }
    BoolMatrix getXMatrix() { return Matrix<BoolVarArgs>(X,number_of_qubits,number_of_operators); }
    BoolMatrix getZMatrix() { return Matrix<BoolVarArgs>(Z,number_of_qubits,number_of_operators); }
    BoolMatrix getNonTrivialMatrix() { return Matrix<BoolVarArgs>(non_trivial,number_of_qubits,number_of_operators); }

    std::vector<dynamic_quantum_operator> getOperators();
    //@+node:gcross.20101123222425.1890: *3* initializeOperators
    template<
        class quantum_operator,
        class operator_vector
    > void initializeOperators(operator_vector& operators) {
        for(int i = 0; i < number_of_operators; ++i) {
            operators.push_back(quantum_operator(total_number_of_qubits));
        }
        for(int i = 0; i < number_of_pairs; ++i) {
            operators[2*i+0].set(i,1);
            operators[2*i+1].set(i,2);
        }
    }
    //@+node:gcross.20101123222425.2046: *3* updateOperators
    template<
        class quantum_operator,
        class operator_vector
    > void updateOperators(operator_vector& operators) {
        int index = 0;
        for(int i = 0; i < number_of_operators; ++i) {
            for(int j = 0; j < number_of_qubits; ++j, ++index) {
                operators[i].set(number_of_pairs+j,O[index].val());
            }
        }
    }
    //@-others

};
//@-others

}

#endif
//@-leo
