//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4266: * @thin test_utils.hh
//@@language cplusplus

#ifndef TEST_UTILS_HH
#define TEST_UTILS_HH

//@+<< Includes >>
//@+node:gcross.20101121135345.1483: ** << Includes >>
#include <gecode/int.hh>
#include <vector>

#include "operator_space.hh"

using namespace Gecode;
using namespace CodeCategorize;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101121135345.1481: ** Functions
vector<long> gatherSolutions(OperatorSpace* m);
long longFromOperatorSpace(OperatorSpace* m);
void validateNonTrivial(const BoolVarArray& X, const BoolVarArray& Z, const BoolVarArray& non_trivial);
//@-others

#endif
//@-leo
