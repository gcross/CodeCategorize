#include "constraints/interactions.hh"
#include "constraints/XZY_ordered.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runOddRowsCommutationCompatibilityTestsFor(XZYOrdered,AntiCommutatorLastOperatorSequenceOrdered,PauliGroupsRowOrdered);
