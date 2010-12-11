//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4269: * @thin test_utils.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101121135345.1485: ** << Includes >>
#include <illuminate.hpp>

#include "solution_iterator.hh"
#include "utilities.hh"

#include "test_utils.hh"

using namespace CodeCategorize;
using namespace Gecode;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101121135345.1477: ** Functions
//@+node:gcross.20101209224839.2296: *3* countSolutions
long countSolutions(OperatorSpace* space) {
    return countSolutions(auto_ptr<OperatorSpace>(space));
}
//@+node:gcross.20101128173348.1865: *3* gatherSolutions
vector<long> gatherSolutions(OperatorSpace* space) {
    vector<long> solutions;
    auto_ptr<OperatorSpace> space_ptr(space);
    for(SolutionIterator<> solution(space_ptr); solution; ++solution) {
        solutions.push_back(longFromOperatorSpace(solution.getSpace()));
    }
    return solutions;
}
//@+node:gcross.20101127142618.1761: *3* longFromOperatorSpace
long longFromOperatorSpace(const OperatorSpace* m) {
    long n = 0;
    for(int i = 0; i < m->O.size(); ++i) {
        n <<= 2;
        n += m->O[i].val();
    }
    return n;
}
//@+node:gcross.20101121135345.1478: *3* validateNonTrivial
void validateNonTrivial(const BoolVarArray& X, const BoolVarArray& Z, const BoolVarArray& non_trivial) {
    for(int i = 0; i < non_trivial.size(); ++i) {
        ASSERT_EQ(X[i].val() || Z[i].val(),non_trivial[i].val());
    }
}
//@-others
//@-leo
