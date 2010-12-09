#include "constraints/interactions.hh"
#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
#include "constraints/row_ordered/first_column.hh"

runOddRowCommutationCompatibilityTestsFor(FirstColumnXZ,AntiCommutatorLastOperatorSequenceOrdered,FirstColumnXRowOrdered);

