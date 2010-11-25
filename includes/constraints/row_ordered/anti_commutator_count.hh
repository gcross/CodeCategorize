//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3085: * @thin anti_commutator_count.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_ANTI_COMMUTATOR_COUNT_HH
#define CONSTRAINTS_ROW_ORDERED_ANTI_COMMUTATOR_COUNT_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.3086: ** << Includes >>
#include <gecode/int.hh>

#include "commutator.hh"
#include "constraints/row_ordered.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3091: ** struct AntiCommutatorCountOrderedOperatorSpace
struct AntiCommutatorCountOrderedOperatorSpace
    : public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.3092: *3* (fields)
    IntVarArray number_of_anti_commuting_operators;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.3093: *3* (constructors)
    AntiCommutatorCountOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    AntiCommutatorCountOrderedOperatorSpace(bool share, AntiCommutatorCountOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.3094: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
