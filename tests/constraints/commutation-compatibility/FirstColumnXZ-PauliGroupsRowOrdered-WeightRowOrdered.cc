#include "constraints/interactions.hh"
#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered/pauli_groups.hh"
#include "constraints/row_ordered/weight.hh"

runOddRowCommutationCompatibilityTestsFor(FirstColumnXZ,PauliGroupsRowOrdered,WeightRowOrdered);

