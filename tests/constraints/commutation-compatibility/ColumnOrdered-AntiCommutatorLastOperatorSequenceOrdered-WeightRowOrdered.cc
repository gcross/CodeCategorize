#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
#include "constraints/row_ordered/weight.hh"

runOddRowCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorLastOperatorSequenceOrdered,WeightRowOrdered);

