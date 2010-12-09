#include "constraints/interactions.hh"
#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/pauli_groups.hh"

runOddRowCommutationCompatibilityTestsFor(FirstColumnXZ,AntiCommutatorCountOrdered,PauliGroupsRowOrdered);

