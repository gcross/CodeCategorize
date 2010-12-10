#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
#include "constraints/row_ordered/first_column.hh"

runOddRowsCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorLastOperatorSequenceOrdered,FirstColumnXRowOrdered);
