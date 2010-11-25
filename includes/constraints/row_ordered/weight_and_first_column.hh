//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3025: * @thin weight_and_first_column.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_WEIGHT_AND_FIRST_COLUMN_HH
#define CONSTRAINTS_ROW_ORDERED_WEIGHT_AND_FIRST_COLUMN_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.3026: ** << Includes >>
#include <gecode/int.hh>

#include "constraints/row_ordered.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/weight.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3049: ** struct WeightAndFirstColumnXRowOrderedOperatorSpace
struct WeightAndFirstColumnXRowOrderedOperatorSpace
    : public WeightRowOrderedOperatorSpace
    , public FirstColumnXRowOrderedOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.3050: *3* (constructors)
    WeightAndFirstColumnXRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    WeightAndFirstColumnXRowOrderedOperatorSpace(bool share, WeightAndFirstColumnXRowOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.3051: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
