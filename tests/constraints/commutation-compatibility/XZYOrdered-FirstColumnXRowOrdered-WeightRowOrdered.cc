#include "constraints/interactions.hh"
#include "constraints/XZY_ordered.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/weight.hh"

runOddRowsCommutationCompatibilityTestsFor(XZYOrdered,FirstColumnXRowOrdered,WeightRowOrdered);
