//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3884: * @thin weight_and_first_column.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3885: ** << Includes >>
#include "constraints/row_ordered/weight_and_first_column.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3890: ** struct WeightAndFirstColumnXRowOrderedOperatorSpace
//@+node:gcross.20101123222425.3891: *3* (constructors)
WeightAndFirstColumnXRowOrderedOperatorSpace::WeightAndFirstColumnXRowOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : WeightRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , FirstColumnXRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
{ }

WeightAndFirstColumnXRowOrderedOperatorSpace::WeightAndFirstColumnXRowOrderedOperatorSpace(bool share, WeightAndFirstColumnXRowOrderedOperatorSpace& s)
    : WeightRowOrderedOperatorSpace(share,s)
    , FirstColumnXRowOrderedOperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{ }
//@+node:gcross.20101123222425.3892: *3* copy
Space* WeightAndFirstColumnXRowOrderedOperatorSpace::copy(bool share)
{
    return new WeightAndFirstColumnXRowOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
