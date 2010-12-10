#include "constraints/interactions.hh"
#include "constraints/minimal_weight.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"

runOddRowsCommutationCompatibilityTestsFor(MinimalWeight,AntiCommutatorCountMinusLastOrdered,AntiCommutatorLastOperatorSequenceOrdered);
