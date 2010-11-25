//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2380: * @thin row_ordered.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_HH
#define CONSTRAINTS_ROW_ORDERED_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2381: ** << Includes >>
#include <gecode/int.hh>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.2392: ** struct RowOrderedOperatorSpace
struct RowOrderedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2393: *3* (fields)
    BoolVarArgs intrapair_ties, interpair_ties;
    //@+node:gcross.20101123222425.2394: *3* (constructors)
    RowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    RowOrderedOperatorSpace(bool share, RowOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2395: *3* (methods)
    virtual Space* copy(bool share);
    void postOrderingConstraint(const IntVarArgs& ordering,BoolVarArgs interpair_ties_,BoolVarArgs intrapair_ties_);
    //@-others

};
//@-others

}

#endif
//@-leo
