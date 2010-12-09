#include "constraints/interactions.hh"
#include "constraints/XZY_ordered.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/first_column.hh"

runOddRowCommutationCompatibilityTestsFor(XZYOrdered,AntiCommutatorQubitCountSequenceOrdered,FirstColumnXRowOrdered);

