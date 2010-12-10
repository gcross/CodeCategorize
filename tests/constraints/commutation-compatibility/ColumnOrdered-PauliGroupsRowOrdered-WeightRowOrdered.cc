#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/pauli_groups.hh"
#include "constraints/row_ordered/weight.hh"

runCommutationCompatibilityTestsFor(ColumnOrdered,PauliGroupsRowOrdered,WeightRowOrdered);
