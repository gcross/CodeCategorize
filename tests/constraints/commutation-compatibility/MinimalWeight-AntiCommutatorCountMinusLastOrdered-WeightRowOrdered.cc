#include "constraints/interactions.hh"
#include "constraints/minimal_weight.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/weight.hh"

runOddRowsCommutationCompatibilityTestsFor(MinimalWeight,AntiCommutatorCountMinusLastOrdered,WeightRowOrdered);
