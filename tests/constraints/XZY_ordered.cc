//@+leo-ver=5-thin
//@+node:gcross.20101126142808.1720: * @thin XZY_ordered.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101126142808.1721: ** << Includes >>
#include <unit--.hpp>

#include "constraints/XZY_ordered.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101126142808.1723: ** ColumnXZYOrdering
testSuite(Constraints) { subSuite(XZYOrdered) {

//@+others
//@+node:gcross.20101126142808.1724: *3* _1x1
testCase(_1x1) {
    XZYOrderedOperatorSpace* m = new XZYOrderedOperatorSpace(1,1);
    DFS<XZYOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(0,number_of_solutions);
}
//@+node:gcross.20101126142808.1725: *3* _1x2
testCase(_1x2) {
    XZYOrderedOperatorSpace* m = new XZYOrderedOperatorSpace(1,2);
    DFS<XZYOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(0,number_of_solutions);
}
//@+node:gcross.20101126142808.1726: *3* _2x1
testCase(_2x1) {
    XZYOrderedOperatorSpace* m = new XZYOrderedOperatorSpace(2,1);
    DFS<XZYOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(1,m->O[0].val());
        assertEqual(2,m->O[1].val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(1,number_of_solutions);
}
//@+node:gcross.20101126142808.1727: *3* _2x2
testCase(_2x2) {
    XZYOrderedOperatorSpace* m = new XZYOrderedOperatorSpace(2,2);
    DFS<XZYOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix();
        for(int column = 0; column < 2; ++column) {
            for(int row = 0; row < 2; ++row) {
                assertEqual(row+1,O_matrix(column,row).val());
            }
        }
        ++number_of_solutions;
        delete m;
    }
    assertEqual(1,number_of_solutions);
}
//@+node:gcross.20101126142808.1728: *3* _3x3
testCase(_3x3) {
    XZYOrderedOperatorSpace* m = new XZYOrderedOperatorSpace(3,3);
    DFS<XZYOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix();
        for(int column = 0; column < 3; ++column) {
            int first_X = -1,
                first_Z = -1,
                first_Y = 3;
            for(int row = 0; row < 3; ++row) {
                switch(O_matrix(column,row).val()) {
                    case X: if(first_X == -1) first_X = row;
                            break;
                    case Y: if(first_Y ==  3) first_Y = row;
                            break;
                    case Z: if(first_Z == -1) first_Z = row;
                            break;
                }
            }
            assertTrue(first_X != -1);
            assertTrue(first_Z != -1);
            assertTrue(first_X <= first_Z);
            assertTrue(first_Z <= first_Y);
        }
        ++number_of_solutions;
        delete m;
    }
    assertEqual(7*7*7,number_of_solutions);
}
//@-others

} }
//@-others
//@-leo
