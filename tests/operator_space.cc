//@+leo-ver=4-thin
//@+node:gcross.20101116210424.2275:@thin operator_space.cc
//@@language cplusplus

//@<< Includes >>
//@+node:gcross.20101116210424.2278:<< Includes >>
#include <unit--.hpp>

#include "operator_space.hh"
//@nonl
//@-node:gcross.20101116210424.2278:<< Includes >>
//@nl

//@+others
//@+node:gcross.20101116210424.2279:Tests
testSuite(OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1277:1x1
subSuite(_1x1,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1384:number of solutions
testCase(number_of_solutions,_1x1) {
    OperatorSpace* m = new OperatorSpace(1,1);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(number_of_solutions,4);
}
//@nonl
//@-node:gcross.20101116222338.1384:number of solutions
//@+node:gcross.20101116222338.1397:correct order
testCase(correct_order,_1x1) {
    OperatorSpace* m = new OperatorSpace(1,1);
    DFS<OperatorSpace> e(m);
    delete m;

    bool X[4] = {false,true,false,true}
       , Z[4] = {false,false,true,true};

    for(int i = 0; i < 4; ++i) {
        m = e.next();
        assertTrue(m != NULL);
        assertEqual(m->X[0].val(),X[i]);
        assertEqual(m->Z[0].val(),Z[i]);
        delete m;
    }

    m = e.next();
    assertTrue(m == NULL);
}
//@nonl
//@-node:gcross.20101116222338.1397:correct order
//@-others

}
//@nonl
//@-node:gcross.20101116222338.1277:1x1
//@+node:gcross.20101116222338.1387:1x2
subSuite(_1x2,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1388:number of solutions
testCase(number_of_solutions,_1x2) {
    OperatorSpace* m = new OperatorSpace(1,2);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(number_of_solutions,16);
}
//@nonl
//@-node:gcross.20101116222338.1388:number of solutions
//@+node:gcross.20101116222338.1403:correct order
testCase(correct_order,_1x2) {
    OperatorSpace* m = new OperatorSpace(1,2);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 1; i > 0; --i) {
            assertEqual(m->X[i].val(),x%2);
            x >>= 1;
            assertEqual(m->Z[i].val(),x%2);
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@nonl
//@-node:gcross.20101116222338.1403:correct order
//@-others

}
//@nonl
//@-node:gcross.20101116222338.1387:1x2
//@+node:gcross.20101116222338.1391:2x1
subSuite(_2x1,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1392:number of solutions
testCase(number_of_solutions,_2x1) {
    OperatorSpace* m = new OperatorSpace(2,1);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(number_of_solutions,16);
}
//@nonl
//@-node:gcross.20101116222338.1392:number of solutions
//@+node:gcross.20101116222338.1401:correct order
testCase(correct_order,_2x1) {
    OperatorSpace* m = new OperatorSpace(2,1);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 1; i > 0; --i) {
            assertEqual(m->X[i].val(),x%2);
            x >>= 1;
            assertEqual(m->Z[i].val(),x%2);
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@nonl
//@-node:gcross.20101116222338.1401:correct order
//@-others

}
//@nonl
//@-node:gcross.20101116222338.1391:2x1
//@+node:gcross.20101116222338.1395:2x2
subSuite(_2x2,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1396:number of solutions
testCase(number_of_solutions,_2x2) {
    OperatorSpace* m = new OperatorSpace(2,2);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(number_of_solutions,256);
}
//@nonl
//@-node:gcross.20101116222338.1396:number of solutions
//@+node:gcross.20101116222338.1399:correct order
testCase(correct_order,_2x2) {
    OperatorSpace* m = new OperatorSpace(2,2);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 3; i > 0; --i) {
            assertEqual(m->X[i].val(),x%2);
            x >>= 1;
            assertEqual(m->Z[i].val(),x%2);
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@nonl
//@-node:gcross.20101116222338.1399:correct order
//@-others

}
//@nonl
//@-node:gcross.20101116222338.1395:2x2
//@-others

}
//@nonl
//@-node:gcross.20101116210424.2279:Tests
//@-others
//@-node:gcross.20101116210424.2275:@thin operator_space.cc
//@-leo
