#include "constraints/interactions.hh"
#include "constraints/XZY_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"

runOddRowsCommutationCompatibilityTestsFor(XZYOrdered,AntiCommutatorCountOrdered,AntiCommutatorCountMinusLastOrdered);
