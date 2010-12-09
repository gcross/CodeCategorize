#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"

runOddRowCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorCountOrdered,AntiCommutatorLastOperatorSequenceOrdered);

