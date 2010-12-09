#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorQubitCountSequenceOrdered,PauliGroupsRowOrdered);

