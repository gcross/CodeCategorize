#include "constraints/interactions.hh"
#include "constraints/non_trivial.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"

runOddRowsCommutationCompatibilityTestsFor(NonTrivial,AntiCommutatorCountOrdered,AntiCommutatorLastOperatorSequenceOrdered);
