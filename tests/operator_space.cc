//@+leo-ver=5-thin
//@+node:gcross.20101116210424.2275: * @thin operator_space.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101116210424.2278: ** << Includes >>
#include <unit--.hpp>

#include "operator_space.hh"
//@-<< Includes >>

//@+others
//@+node:gcross.20101116210424.2279: ** Tests
testSuite(OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1277: *3* 1x1
subSuite(_1x1,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1384: *4* number of solutions
testCase(number_of_solutions,_1x1) {
    OperatorSpace* m = new OperatorSpace(1,1);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101116222338.1397: *4* correct order
testCase(correct_order,_1x1) {
    OperatorSpace* m = new OperatorSpace(1,1);
    DFS<OperatorSpace> e(m);
    delete m;

    bool X[4] = {false,true,false,true}
       , Z[4] = {false,false,true,true};

    for(int i = 0; i < 4; ++i) {
        m = e.next();
        assertTrue(m != NULL);
        assertEqual(X[i],m->X[0].val());
        assertEqual(Z[i],m->Z[0].val());
        delete m;
    }

    m = e.next();
    assertTrue(m == NULL);
}
//@-others

}
//@+node:gcross.20101116222338.1387: *3* 1x2
subSuite(_1x2,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1388: *4* number of solutions
testCase(number_of_solutions,_1x2) {
    OperatorSpace* m = new OperatorSpace(1,2);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101116222338.1403: *4* correct order
testCase(correct_order,_1x2) {
    OperatorSpace* m = new OperatorSpace(1,2);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 1; i > 0; --i) {
            assertEqual(x%2,m->X[i].val());
            x >>= 1;
            assertEqual(x%2,m->Z[i].val());
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@-others

}
//@+node:gcross.20101116222338.1391: *3* 2x1
subSuite(_2x1,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1392: *4* number of solutions
testCase(number_of_solutions,_2x1) {
    OperatorSpace* m = new OperatorSpace(2,1);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101116222338.1401: *4* correct order
testCase(correct_order,_2x1) {
    OperatorSpace* m = new OperatorSpace(2,1);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 1; i > 0; --i) {
            assertEqual(x%2,m->X[i].val());
            x >>= 1;
            assertEqual(x%2,m->Z[i].val());
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@-others

}
//@+node:gcross.20101116222338.1395: *3* 2x2
subSuite(_2x2,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1396: *4* number of solutions
testCase(number_of_solutions,_2x2) {
    OperatorSpace* m = new OperatorSpace(2,2);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(256,number_of_solutions);
}
//@+node:gcross.20101116222338.1399: *4* correct order
testCase(correct_order,_2x2) {
    OperatorSpace* m = new OperatorSpace(2,2);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 3; i > 0; --i) {
            assertEqual(x%2,m->X[i].val());
            x >>= 1;
            assertEqual(x%2,m->Z[i].val());
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@-others

}
//@+node:gcross.20101116222338.1407: *3* 3x3
subSuite(_3x3,OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1408: *4* number of solutions
testCase(number_of_solutions,_3x3) {
    OperatorSpace* m = new OperatorSpace(3,3);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(1<<(2*3*3),number_of_solutions);
}
//@+node:gcross.20101116222338.1415: *4* correct order
testCase(correct_order,_3x3) {
    OperatorSpace* m = new OperatorSpace(3,3);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 8; i > 0; --i) {
            assertEqual(x%2,m->X[i].val());
            x >>= 1;
            assertEqual(x%2,m->Z[i].val());
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@-others

}
//@-others

}
//@-others
//@-leo
