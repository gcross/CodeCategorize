#include "constraints/interactions.hh"
#include "constraints/XZY_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/first_column.hh"

runOddRowsCommutationCompatibilityTestsFor(XZYOrdered,AntiCommutatorCountOrdered,FirstColumnXRowOrdered);
