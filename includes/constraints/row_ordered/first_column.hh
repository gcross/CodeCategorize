//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2933: * @thin first_column.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_FIRST_COLUMN_HH
#define CONSTRAINTS_ROW_ORDERED_FIRST_COLUMN_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2934: ** << Includes >>
#include <gecode/int.hh>

#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.2953: ** struct FirstColumnXRowOrderedOperatorSpace
struct FirstColumnXRowOrderedOperatorSpace
    : public virtual RowOrderedOperatorSpace
    , public virtual FirstColumnXZOperatorSpace 
{

    //@+others
    //@+node:gcross.20101123222425.2954: *3* (fields)
    IntVarArray first_column_X;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.2955: *3* (constructors)
    FirstColumnXRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    FirstColumnXRowOrderedOperatorSpace(bool share, FirstColumnXRowOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2956: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
