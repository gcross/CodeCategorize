#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runOddRowsCommutationCompatibilityTestsFor(ColumnOrdered,FirstColumnXRowOrdered,PauliGroupsRowOrdered);
