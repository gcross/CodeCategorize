#include "constraints/interactions.hh"
#include "constraints/minimal_weight.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"

runCommutationCompatibilityTestsFor(MinimalWeight,AntiCommutatorCountOrdered,AntiCommutatorQubitCountSequenceOrdered);
