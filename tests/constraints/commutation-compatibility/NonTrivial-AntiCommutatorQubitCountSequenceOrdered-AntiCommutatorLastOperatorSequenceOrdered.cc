#include "constraints/interactions.hh"
#include "constraints/non_trivial.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"

runOddRowsCommutationCompatibilityTestsFor(NonTrivial,AntiCommutatorQubitCountSequenceOrdered,AntiCommutatorLastOperatorSequenceOrdered);
