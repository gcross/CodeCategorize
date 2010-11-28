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
//@+node:gcross.20101127142618.1766: *3* gatherSolutions
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
//@+node:gcross.20101127142618.1769: ** Tests
testSuite(Test_Utils) {

//@+others
//@+node:gcross.20101127142618.1770: *3* longFromOperatorSpace
subSuite(longFromOperatorSpace_) {

//@+others
//@+node:gcross.20101127142618.1771: *4* correctly ordered
subSuite(correctly_ordered) {

void runTest(int number_of_operators, int number_of_qubits) {
    OperatorSpace* m = new OperatorSpace(number_of_operators,number_of_qubits);
    DFS<OperatorSpace> e(m);
    delete m;
    long last = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(last,longFromOperatorSpace(m));
        ++last;
        delete m;
    }
}

#define doTest(m,n) \
    testCase( _##m##x##n ) { runTest(m,n); };

doTest(1,1);
doTest(1,2);
doTest(1,3);
doTest(2,1);
doTest(2,2);
doTest(2,3);
doTest(3,1);
doTest(3,2);
doTest(3,3);

}
//@-others

}
//@-others

};
//@-others
//@-leo
