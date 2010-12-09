#include "constraints/interactions.hh"
#include "constraints/special_case_XZ.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runCommutationCompatibilityTestsFor(SpecialCaseXZConstrained,AntiCommutatorQubitCountSequenceOrdered,PauliGroupsRowOrdered);

