//@+leo-ver=5-thin
//@+node:gcross.20101120151226.1468: * @thin utilities.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101120151226.1469: ** << Includes >>
#include <gecode/minimodel.hh>

#include "utilities.hh"
//@-<< Includes >>

//@+others
//@+node:gcross.20101120151226.1478: ** Functions
//@+node:gcross.20101120151226.1479: *3* computeNonTrivial
void computeNonTrivial(Space& home, const BoolVarArgs& X, const BoolVarArgs& Z, BoolVarArray& non_trivial) {
    for(int i = 0; i < non_trivial.size(); ++i) {
        non_trivial[i] = expr(home,Z[i] || X[i]);
    }
}
//@+node:gcross.20101120151226.1482: *3* computeWeights
void computeWeights(
    Space& home,
    int number_of_operators,
    int number_of_qubits,
    const BoolVarArgs& non_trivial,
    IntVarArray& weights
) {
    BoolMatrix non_trivial_matrix(non_trivial,number_of_qubits,number_of_operators);
    for(int i = 0; i < number_of_operators; ++i) {
        weights[i] = expr(home,sum(non_trivial_matrix.row(i)));
    }
}
//@+node:gcross.20101120151226.1480: *3* multiplyOperators
void multiplyOperators(
    Space& home,
    const BoolVarArgs& Xin1, const BoolVarArgs& Zin1,
    const BoolVarArgs& Xin2, const BoolVarArgs& Zin2,
          BoolVarArgs  Xout,       BoolVarArgs  Zout
) {
    for(int i = 0; i < Xin1.size(); ++i) {
        Xout[i] = expr(home,Xin1[i]^Xin2[i]);
        Zout[i] = expr(home,Zin1[i]^Zin2[i]);
    }
}
//@-others
//@-leo
