#include "constraints/interactions.hh"
#include "constraints/XZY_ordered.hh"
#include "constraints/row_ordered/pauli_groups.hh"
#include "constraints/row_ordered/weight.hh"

runCommutationCompatibilityTestsFor(XZYOrdered,PauliGroupsRowOrdered,WeightRowOrdered);

