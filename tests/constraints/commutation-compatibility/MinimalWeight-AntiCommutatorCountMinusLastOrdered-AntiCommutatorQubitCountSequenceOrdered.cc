#include "constraints/interactions.hh"
#include "constraints/minimal_weight.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"

runOddRowsCommutationCompatibilityTestsFor(MinimalWeight,AntiCommutatorCountMinusLastOrdered,AntiCommutatorQubitCountSequenceOrdered);
