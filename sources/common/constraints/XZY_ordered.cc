//@+leo-ver=5-thin
//@+node:gcross.20101126142808.1699: * @thin XZY_ordered.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101126142808.1700: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/XZY_ordered.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101126142808.1701: ** struct XZYOrderedOperatorSpace
//@+node:gcross.20101126142808.1702: *3* (constructors)
XZYOrderedOperatorSpace::XZYOrderedOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , ColumnPauliSetsOperatorSpace(number_of_operators,number_of_qubits)
{
    for(int i = 0; i < number_of_qubits; ++i) {
        rel(*this,min(X_sets[i]) <= min(Z_sets[i]));
        rel(*this,min(Z_sets[i]) <= min(Y_sets[i] | Z_sets[i]));
    }
}

XZYOrderedOperatorSpace::XZYOrderedOperatorSpace(bool share, XZYOrderedOperatorSpace& s)
    : OperatorSpace(share,s)
    , ColumnPauliSetsOperatorSpace(share,s)
{
}
//@+node:gcross.20101126142808.1703: *3* copy
Space* XZYOrderedOperatorSpace::copy(bool share)
{
    return new XZYOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
