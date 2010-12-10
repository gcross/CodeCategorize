#include "constraints/interactions.hh"
#include "constraints/minimal_weight.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"

runOddRowsCommutationCompatibilityTestsFor(MinimalWeight,AntiCommutatorCountOrdered,AntiCommutatorLastOperatorSequenceOrdered);
