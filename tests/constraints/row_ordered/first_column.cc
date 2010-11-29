//@+leo-ver=5-thin
//@+node:gcross.20101128153132.1848: * @thin first_column.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128153132.1849: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <unit--.hpp>

#include "constraints/row_ordered/first_column.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128153132.1857: ** Tests
testSuite(Constraints) { subSuite(RowOrdered) { subSuite(FirstColumnX) {

//@+others
//@+node:gcross.20101128153132.1858: *3* _1x1
testCase(_1x1) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(1,1);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101128153132.1859: *3* _1x2
testCase(_1x2) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(1,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101128153132.1860: *3* _2x1
testCase(_2x1) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(2,1);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(m->X[1].val() == 0 || m->X[0].val() == 1);
        ++number_of_solutions;
        delete m;
    }
    assertEqual(12,number_of_solutions);
}
//@+node:gcross.20101128153132.1861: *3* _2x2
testCase(_2x2) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(2,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        assertTrue(X_matrix(0,1).val() == 0 || X_matrix(0,0).val() == 1);
        ++number_of_solutions;
        delete m;
    }
    assertEqual(12*16,number_of_solutions);
}
//@+node:gcross.20101128153132.1862: *3* _4x2
testCase(_4x2) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(4,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        assertTrue(X_matrix(0,1).val() == 0 || X_matrix(0,0).val() == 1);
        assertTrue(X_matrix(0,3).val() == 0 || X_matrix(0,2).val() == 1);
        assertTrue(X_matrix(0,0).val() >= X_matrix(0,2).val()
           ||      X_matrix(0,0).val() == X_matrix(0,2).val()
               &&  X_matrix(0,1).val() >= X_matrix(0,3).val()

        );
        ++number_of_solutions;
        delete m;
    }
    assertTrue(number_of_solutions > 0);
}
//@-others

} } }
//@-others
//@-leo
