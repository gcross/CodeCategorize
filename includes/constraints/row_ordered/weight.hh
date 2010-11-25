//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2748: * @thin weight.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_WEIGHT_HH
#define CONSTRAINTS_ROW_ORDERED_WEIGHT_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2749: ** << Includes >>
#include <gecode/int.hh>

#include "constraints/row_ordered.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.2764: ** struct WeightRowOrderedOperatorSpace
struct WeightRowOrderedOperatorSpace : public virtual RowOrderedOperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2765: *3* (fields)
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.2766: *3* (constructors)
    WeightRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    WeightRowOrderedOperatorSpace(bool share, WeightRowOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2767: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
