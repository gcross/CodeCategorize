#include "constraints/interactions.hh"
#include "constraints/non_trivial.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runOddRowCommutationCompatibilityTestsFor(NonTrivial,AntiCommutatorCountMinusLastOrdered,PauliGroupsRowOrdered);

