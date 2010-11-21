//@+leo-ver=5-thin
//@+node:gcross.20101121135345.1473: * @thin test_utils.hh
//@@language cplusplus

#ifndef TEST_UTILS_HH
#define TEST_UTILS_HH

//@+<< Includes >>
//@+node:gcross.20101121135345.1483: ** << Includes >>
#include <gecode/int.hh>

using namespace Gecode;
//@-<< Includes >>

//@+others
//@+node:gcross.20101121135345.1481: ** Functions
void validateNonTrivial(const BoolVarArray& X, const BoolVarArray& Z, const BoolVarArray& non_trivial);
//@-others

#endif
//@-leo
