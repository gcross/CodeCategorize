#include "constraints/interactions.hh"
#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"

runOddRowCommutationCompatibilityTestsFor(FirstColumnXZ,AntiCommutatorQubitCountSequenceOrdered,AntiCommutatorLastOperatorSequenceOrdered);

