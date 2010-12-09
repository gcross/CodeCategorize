#include "constraints/interactions.hh"
#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"

runOddRowCommutationCompatibilityTestsFor(FirstColumnXZ,AntiCommutatorCountMinusLastOrdered,AntiCommutatorQubitCountSequenceOrdered);

