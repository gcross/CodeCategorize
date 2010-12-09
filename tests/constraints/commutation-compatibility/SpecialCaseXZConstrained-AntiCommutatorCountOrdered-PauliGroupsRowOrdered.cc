#include "constraints/interactions.hh"
#include "constraints/special_case_XZ.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runCommutationCompatibilityTestsFor(SpecialCaseXZConstrained,AntiCommutatorCountOrdered,PauliGroupsRowOrdered);

