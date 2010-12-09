#include "constraints/interactions.hh"
#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/first_column.hh"

runOddRowCommutationCompatibilityTestsFor(FirstColumnXZ,AntiCommutatorCountMinusLastOrdered,FirstColumnXRowOrdered);

