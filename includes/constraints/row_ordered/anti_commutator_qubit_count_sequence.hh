//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3113: * @thin anti_commutator_qubit_count_sequence.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_ANTI_COMMUTATOR_QUBIT_COUNT_SEQUENCE_HH
#define CONSTRAINTS_ROW_ORDERED_ANTI_COMMUTATOR_QUBIT_COUNT_SEQUENCE_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.3114: ** << Includes >>
#include <gecode/int.hh>

#include "commutator.hh"
#include "constraints/row_ordered.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3123: ** struct AntiCommutatorQubitCountSequenceOrderedOperatorSpace
struct AntiCommutatorQubitCountSequenceOrderedOperatorSpace
    : public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.3124: *3* (fields)
    IntVarArray sorted_anti_commuting_qubit_counts;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.3125: *3* (constructors)
    AntiCommutatorQubitCountSequenceOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    AntiCommutatorQubitCountSequenceOrderedOperatorSpace(bool share, AntiCommutatorQubitCountSequenceOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.3126: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
