#include "constraints/interactions.hh"
#include "constraints/special_case_XZ.hh"
#include "constraints/row_ordered/pauli_groups.hh"
#include "constraints/row_ordered/weight.hh"

runCommutationCompatibilityTestsFor(SpecialCaseXZConstrained,PauliGroupsRowOrdered,WeightRowOrdered);

