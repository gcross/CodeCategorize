//@+leo-ver=5-thin
//@+node:gcross.20101120151226.1470: * @thin utilities.hh
//@@language cplusplus

#ifndef UTILITIES_HH
#define UTILITIES_HH

//@+<< Includes >>
//@+node:gcross.20101120151226.1471: ** << Includes >>
#include <gecode/int.hh>

using namespace Gecode;
//@-<< Includes >>

//@+others
//@+node:gcross.20101120151226.1484: ** Type aliases
typedef Matrix<IntVarArgs> IntMatrix;
typedef Matrix<BoolVarArgs> BoolMatrix;
//@+node:gcross.20101120151226.1481: ** Functions
void computeNonTrivial(Space& home, const BoolVarArgs& X, const BoolVarArgs& Z, BoolVarArray& non_trivial);
void computeWeights(
    Space& home,
    int number_of_operators,
    int number_of_qubits,
    const BoolVarArgs& non_trivial,
    IntVarArray& weights
);
void multiplyOperators(
    Space& home,
    const BoolVarArgs& Xin1, const BoolVarArgs& Zin1,
    const BoolVarArgs& Xin2, const BoolVarArgs& Zin2,
          BoolVarArgs  Xout,       BoolVarArgs  Zout
);
//@-others

#endif
//@-leo
