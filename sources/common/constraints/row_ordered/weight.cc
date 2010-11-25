//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3821: * @thin weight.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3822: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/row_ordered/weight.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3824: ** struct WeightRowOrderedOperatorSpace
//@+node:gcross.20101123222425.3825: *3* (constructors)
WeightRowOrderedOperatorSpace::WeightRowOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , intrapair_ties(*this,number_of_pairs,0,1)
    , interpair_ties(*this,max(number_of_pairs-1,0),0,1)
{
    postOrderingConstraint(weights,intrapair_ties,interpair_ties);
}

WeightRowOrderedOperatorSpace::WeightRowOrderedOperatorSpace(bool share, WeightRowOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{
    intrapair_ties.update(*this,share,s.intrapair_ties);
    interpair_ties.update(*this,share,s.interpair_ties);
}
//@+node:gcross.20101123222425.3826: *3* copy
Space* WeightRowOrderedOperatorSpace::copy(bool share)
{
    return new WeightRowOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
