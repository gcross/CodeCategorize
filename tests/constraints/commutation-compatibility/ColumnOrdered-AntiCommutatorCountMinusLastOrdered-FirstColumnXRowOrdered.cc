#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/first_column.hh"

runOddRowsCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorCountMinusLastOrdered,FirstColumnXRowOrdered);
