//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4269: * @thin test_utils.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101121135345.1485: ** << Includes >>
#include <unit--.hpp>

#include "test_utils.hh"

using namespace Gecode;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101121135345.1477: ** Functions
//@+node:gcross.20101127142618.1766: *3* countSolutions
long countSolutions(OperatorSpace* m) {
    DFS<OperatorSpace> e(m);
    delete m;
    long number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    return number_of_solutions;
}
//@+node:gcross.20101128173348.1865: *3* gatherSolutions
vector<long> gatherSolutions(OperatorSpace* m) {
    DFS<OperatorSpace> e(m);
    delete m;
    vector<long> solutions;
    for(m = e.next(); m != NULL; m = e.next()) {
        solutions.push_back(longFromOperatorSpace(m));
        delete m;
    }
    return solutions;
}
//@+node:gcross.20101127142618.1761: *3* longFromOperatorSpace
long longFromOperatorSpace(OperatorSpace* m) {
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
        assertEqual(X[i].val() || Z[i].val(),non_trivial[i].val());
    }
}
//@-others
//@-leo
