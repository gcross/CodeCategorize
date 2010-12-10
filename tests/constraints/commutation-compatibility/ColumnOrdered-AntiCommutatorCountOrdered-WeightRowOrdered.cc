#include "constraints/interactions.hh"
#include "constraints/column_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/weight.hh"

runCommutationCompatibilityTestsFor(ColumnOrdered,AntiCommutatorCountOrdered,WeightRowOrdered);
