#include "constraints/interactions.hh"
#include "constraints/special_case_XZ.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runOddRowCommutationCompatibilityTestsFor(SpecialCaseXZConstrained,AntiCommutatorCountMinusLastOrdered,PauliGroupsRowOrdered);

