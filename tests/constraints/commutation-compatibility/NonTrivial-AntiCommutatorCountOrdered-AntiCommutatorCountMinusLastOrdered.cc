#include "constraints/interactions.hh"
#include "constraints/non_trivial.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"

runOddRowCommutationCompatibilityTestsFor(NonTrivial,AntiCommutatorCountOrdered,AntiCommutatorCountMinusLastOrdered);

