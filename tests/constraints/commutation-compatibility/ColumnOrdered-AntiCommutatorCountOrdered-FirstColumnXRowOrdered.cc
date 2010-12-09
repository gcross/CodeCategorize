#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/first_column.hh"

runOddRowCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorCountOrdered,FirstColumnXRowOrdered);

