#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"

runCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorCountOrdered,AntiCommutatorQubitCountSequenceOrdered);
