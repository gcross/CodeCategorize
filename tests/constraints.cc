//@+leo-ver=5-thin
//@+node:gcross.20101117133000.1340: * @thin constraints.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117133000.1341: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/minimodel.hh>
#include <iostream>
#include <unit--.hpp>

#include "constraints.hh"

using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101117133000.1448: ** Tests
//@+node:gcross.20101117133000.1449: *3* CompleteColumns
testSuite(CompleteColumns) {

//@+others
//@+node:gcross.20101117133000.1454: *4* _1x1
testCase(_1x1,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(1,1);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(0,number_of_solutions);
}
//@+node:gcross.20101117133000.1457: *4* _1x2
testCase(_1x2,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(1,2);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(0,number_of_solutions);
}
//@+node:gcross.20101117133000.1459: *4* _2x1
testCase(_2x1,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(2,1);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(m->non_trivial[0].val());
        assertTrue(m->non_trivial[1].val());
        assertTrue(
            (m->X[0].val() != m->X[1].val())
         || (m->Z[0].val() != m->Z[1].val())
        );
        delete m;
    }
}
//@+node:gcross.20101117133000.1461: *4* _2x2
testCase(_2x2,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(2,2);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        for(int i = 0; i < 4; ++i) assertTrue(m->non_trivial[i].val());
        Matrix<IntVarArgs> O_matrix(m->O,2,2);
        assertTrue(O_matrix(0,0).val() != O_matrix(1,0).val());
        assertTrue(O_matrix(0,1).val() != O_matrix(1,1).val());
        delete m;
    }
    assertTrue(number_of_solutions > 0);
}
//@+node:gcross.20101117133000.1463: *4* _3x3
testCase(_3x3,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(3,3);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        Matrix<IntVarArgs> O_matrix(m->O,3,3);
        for(int column = 0; column < 3; ++column) {
            bool present[4];  BOOST_FOREACH(bool& x, present) { x = false; }
            for(int row = 0; row < 3; ++row) present[O_matrix(row,column).val()] = true;
            int count = 0;
            for(int i = 1; i < 4; ++i) if(present[i]) ++count;
            assertTrue(count >= 2);
        }
        delete m;
    }
    assertTrue(number_of_solutions > 0);
}
//@-others

}
//@-others
//@-leo
