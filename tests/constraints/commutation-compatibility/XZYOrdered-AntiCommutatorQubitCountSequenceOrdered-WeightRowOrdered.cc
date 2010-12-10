#include "constraints/interactions.hh"
#include "constraints/XZY_ordered.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/weight.hh"

runCommutationCompatibilityTestsFor(XZYOrdered,AntiCommutatorQubitCountSequenceOrdered,WeightRowOrdered);
