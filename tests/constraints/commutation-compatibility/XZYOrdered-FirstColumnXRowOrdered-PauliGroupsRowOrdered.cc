#include "constraints/interactions.hh"
#include "constraints/XZY_ordered.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runOddRowCommutationCompatibilityTestsFor(XZYOrdered,FirstColumnXRowOrdered,PauliGroupsRowOrdered);

