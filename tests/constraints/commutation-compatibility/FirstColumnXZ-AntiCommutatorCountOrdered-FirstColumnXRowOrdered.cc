#include "constraints/interactions.hh"
#include "constraints/first_column_XZ.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/first_column.hh"

runOddRowCommutationCompatibilityTestsFor(FirstColumnXZ,AntiCommutatorCountOrdered,FirstColumnXRowOrdered);

