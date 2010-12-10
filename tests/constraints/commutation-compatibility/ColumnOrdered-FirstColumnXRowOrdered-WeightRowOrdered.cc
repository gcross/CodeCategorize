#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/weight.hh"

runOddRowsCommutationCompatibilityTestsFor(ColumnOrdered,FirstColumnXRowOrdered,WeightRowOrdered);
