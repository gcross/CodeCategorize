//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4343: * @thin anti_commutator_count_minus_last.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_ANTI_COMMUTATOR_COUNT_MINUS_LAST_HH
#define CONSTRAINTS_ROW_ORDERED_ANTI_COMMUTATOR_COUNT_MINUS_LAST_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.4344: ** << Includes >>
#include <gecode/int.hh>

#include "commutator.hh"
#include "constraints/row_ordered.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.4345: ** struct AntiCommutatorCountMinusLastOrderedOperatorSpace
struct AntiCommutatorCountMinusLastOrderedOperatorSpace
    : public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.4346: *3* (fields)
    IntVarArray number_of_anti_commuting_operators;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.4347: *3* (constructors)
    AntiCommutatorCountMinusLastOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    AntiCommutatorCountMinusLastOrderedOperatorSpace(bool share, AntiCommutatorCountMinusLastOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.4348: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
