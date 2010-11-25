//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3854: * @thin first_column.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3855: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/row_ordered/first_column.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3857: ** struct FirstColumnXRowOrderedOperatorSpace
//@+node:gcross.20101123222425.3858: *3* (constructors)
FirstColumnXRowOrderedOperatorSpace::FirstColumnXRowOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , first_column_X(*this,number_of_operators,0,1)
    , intrapair_ties(*this,number_of_pairs,0,1)
    , interpair_ties(*this,max(number_of_pairs-1,0),0,1)
{
    BoolMatrix X_matrix = getXMatrix();
    for(int i = 0; i < number_of_operators; ++i) channel(*this,X_matrix(0,i),first_column_X[i]);
    postOrderingConstraint(first_column_X,intrapair_ties,interpair_ties);
}

FirstColumnXRowOrderedOperatorSpace::FirstColumnXRowOrderedOperatorSpace(bool share, FirstColumnXRowOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{
    first_column_X.update(*this,share,s.first_column_X);
    intrapair_ties.update(*this,share,s.intrapair_ties);
    interpair_ties.update(*this,share,s.interpair_ties);
}
//@+node:gcross.20101123222425.3859: *3* copy
Space* FirstColumnXRowOrderedOperatorSpace::copy(bool share)
{
    return new FirstColumnXRowOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
