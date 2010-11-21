//@+leo-ver=5-thin
//@+node:gcross.20101116210424.1511: * @thin operator_space.hh
//@@language cplusplus

#ifndef OPERATOR_SPACE_HH
#define OPERATOR_SPACE_HH

//@+<< Includes >>
//@+node:gcross.20101120151226.1488: ** << Includes >>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

#include "utilities.hh"

using namespace Gecode;
//@-<< Includes >>

//@+others
//@+node:gcross.20101117133000.1474: ** Enums
enum Pauli { I = 0, X = 1, Z = 2, Y = 3 };
//@+node:gcross.20101116210424.1513: ** struct OperatorSpace
struct OperatorSpace : public Space {

    //@+others
    //@+node:gcross.20101116210424.1674: *3* (fields)
    int number_of_operators, number_of_qubits, number_of_variables, number_of_pairs;

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
    //@-others

};
//@-others

#endif
//@-leo
