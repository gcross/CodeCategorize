#include "constraints/interactions.hh"
#include "constraints/special_case_XZ.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runOddRowCommutationCompatibilityTestsFor(SpecialCaseXZConstrained,AntiCommutatorLastOperatorSequenceOrdered,PauliGroupsRowOrdered);

