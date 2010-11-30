//@+leo-ver=5-thin
//@+node:gcross.20101129164055.1853: * @thin first_column_XZ.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101129164055.1854: ** << Includes >>
#include <unit--.hpp>

#include "constraints/first_column_XZ.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101129164055.1862: ** Tests
testSuite(Constraints) { subSuite(FirstColumnXZ) {

//@+others
//@+node:gcross.20101129164055.1863: *3* _1x1
testCase(_1x1) {
    FirstColumnXZOperatorSpace* m = new FirstColumnXZOperatorSpace(1,1);
    DFS<FirstColumnXZOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(Z,m->getOMatrix()(0,0).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(1,number_of_solutions);
}
//@+node:gcross.20101129164055.1864: *3* _1x2
testCase(_1x2) {
    FirstColumnXZOperatorSpace* m = new FirstColumnXZOperatorSpace(1,2);
    DFS<FirstColumnXZOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(Z,m->getOMatrix()(0,0).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101129164055.1865: *3* _2x1
testCase(_2x1) {
    FirstColumnXZOperatorSpace* m = new FirstColumnXZOperatorSpace(2,1);
    DFS<FirstColumnXZOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(0,m->getZMatrix()(0,0).val());
        assertEqual(Z,m->getOMatrix()(0,1).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(2,number_of_solutions);
}
//@+node:gcross.20101129164055.1866: *3* _2x2
testCase(_2x2) {
    FirstColumnXZOperatorSpace* m = new FirstColumnXZOperatorSpace(2,2);
    DFS<FirstColumnXZOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(0,m->getZMatrix()(0,0).val());
        assertEqual(Z,m->getOMatrix()(0,1).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(32,number_of_solutions);
}
//@+node:gcross.20101129164055.1867: *3* _3x3
testCase(_3x3) {
    FirstColumnXZOperatorSpace* m = new FirstColumnXZOperatorSpace(3,3);
    DFS<FirstColumnXZOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(0,m->getZMatrix()(0,0).val());
        assertEqual(0,m->getZMatrix()(0,1).val());
        assertEqual(Z,m->getOMatrix()(0,2).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(2*2*4*4*4*4*4*4,number_of_solutions);
}
//@-others

} }
//@-others
//@-leo
