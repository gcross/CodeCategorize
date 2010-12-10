#include "constraints/interactions.hh"
#include "constraints/non_trivial.hh"
#include "constraints/row_ordered/pauli_groups.hh"
#include "constraints/row_ordered/weight.hh"

runCommutationCompatibilityTestsFor(NonTrivial,PauliGroupsRowOrdered,WeightRowOrdered);
