//@+leo-ver=5-thin
//@+node:gcross.20101126220444.1724: * @thin anti_commutator_last_operator_sequence.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_ANTI_COMMUTATOR_LAST_OPERATOR_SEQUENCE_HH
#define CONSTRAINTS_ROW_ORDERED_ANTI_COMMUTATOR_LAST_OPERATOR_SEQUENCE_HH

//@+<< Includes >>
//@+node:gcross.20101126220444.1725: ** << Includes >>
#include <gecode/int.hh>

#include "commutator.hh"
#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101126220444.1726: ** struct AntiCommutatorLastOperatorSequenceOrderedOperatorSpace
struct AntiCommutatorLastOperatorSequenceOrderedOperatorSpace
    : public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
    , public virtual FirstColumnXZOperatorSpace
{

    //@+others
    //@+node:gcross.20101126220444.1727: *3* (fields)
    IntVarArray last_operator_anti_commuting_qubit_sequence, sorted_last_operator_anti_commuting_qubit_sequence;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101126220444.1728: *3* (constructors)
    AntiCommutatorLastOperatorSequenceOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    AntiCommutatorLastOperatorSequenceOrderedOperatorSpace(bool share, AntiCommutatorLastOperatorSequenceOrderedOperatorSpace& s);
    //@+node:gcross.20101126220444.1729: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
