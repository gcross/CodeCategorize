#include "constraints/interactions.hh"
#include "constraints/special_case_XZ.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runOddRowCommutationCompatibilityTestsFor(SpecialCaseXZConstrained,FirstColumnXRowOrdered,PauliGroupsRowOrdered);

