#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"

runOddRowsCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorCountMinusLastOrdered,AntiCommutatorQubitCountSequenceOrdered);
