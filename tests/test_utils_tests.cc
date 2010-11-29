//@+leo-ver=5-thin
//@+node:gcross.20101128153132.1766: * @thin test_utils_tests.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128153132.1767: ** << Includes >>
#include <unit--.hpp>

#include "test_utils.hh"

using namespace Gecode;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128153132.1772: ** Tests
testSuite(Test_Utils) {

//@+others
//@+node:gcross.20101128153132.1773: *3* longFromOperatorSpace
subSuite(longFromOperatorSpace_) {

//@+others
//@+node:gcross.20101128153132.1774: *4* correctly ordered
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
