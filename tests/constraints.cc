//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4092: * @thin constraints.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.4093: ** << Includes >>
#include <unit--.hpp>

#include "constraints.hh"
#include "operator_space.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101123222425.4094: ** Tests
testSuite(Constraints) {

//@+others
//@+node:gcross.20101123222425.4104: *3* ColumnXZYOrdering
subSuite(ColumnXZYOrdering) {

//@+others
//@+node:gcross.20101123222425.4105: *4* _1x1
testCase(_1x1) {
    OperatorSpace* m = new OperatorSpace(1,1);
    postColumnXZYOrderingConstraints(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(0,number_of_solutions);
}
//@+node:gcross.20101123222425.4106: *4* _1x2
testCase(_1x2) {
    OperatorSpace* m = new OperatorSpace(1,2);
    postColumnXZYOrderingConstraints(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(0,number_of_solutions);
}
//@+node:gcross.20101123222425.4107: *4* _2x1
testCase(_2x1) {
    OperatorSpace* m = new OperatorSpace(2,1);
    postColumnXZYOrderingConstraints(*m);
    DFS<OperatorSpace> e(m);
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
//@+node:gcross.20101123222425.4108: *4* _2x2
testCase(_2x2) {
    OperatorSpace* m = new OperatorSpace(2,2);
    postColumnXZYOrderingConstraints(*m);
    DFS<OperatorSpace> e(m);
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
//@+node:gcross.20101123222425.4109: *4* _3x3
testCase(_3x3) {
    OperatorSpace* m = new OperatorSpace(3,3);
    postColumnXZYOrderingConstraints(*m);
    DFS<OperatorSpace> e(m);
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

}
//@+node:gcross.20101123222425.4116: *3* FirstColumnSpecialCase
subSuite(FirstColumnSpecialCase) {

//@+others
//@+node:gcross.20101123222425.4117: *4* _1x1
testCase(_1x1) {
    OperatorSpace* m = new OperatorSpace(1,1);
    postFirstColumnSpecialCaseConstraint(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(Z,m->getOMatrix()(0,0).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(1,number_of_solutions);
}
//@+node:gcross.20101123222425.4118: *4* _1x2
testCase(_1x2) {
    OperatorSpace* m = new OperatorSpace(1,2);
    postFirstColumnSpecialCaseConstraint(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(Z,m->getOMatrix()(0,0).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101123222425.4119: *4* _2x1
testCase(_2x1) {
    OperatorSpace* m = new OperatorSpace(2,1);
    postFirstColumnSpecialCaseConstraint(*m);
    DFS<OperatorSpace> e(m);
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
//@+node:gcross.20101123222425.4120: *4* _2x2
testCase(_2x2) {
    OperatorSpace* m = new OperatorSpace(2,2);
    postFirstColumnSpecialCaseConstraint(*m);
    DFS<OperatorSpace> e(m);
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
//@+node:gcross.20101123222425.4121: *4* _3x3
testCase(_3x3) {
    OperatorSpace* m = new OperatorSpace(3,3);
    postFirstColumnSpecialCaseConstraint(*m);
    DFS<OperatorSpace> e(m);
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

}
//@+node:gcross.20101123222425.4123: *3* NonTrivialWeight
subSuite(NonTrivialWeight) {

void runNonTrivialWeightTest(int number_of_operators,int number_of_qubits,int correct_number_of_solutions) {
    OperatorSpace* m = new OperatorSpace(number_of_operators,number_of_qubits);
    postNonTrivialWeightConstraints(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < number_of_operators; ++i) assertTrue(m->weights[i].val() >= 1);
        if(number_of_operators % 2 == 1) assertTrue(m->weights[number_of_operators-1].val() >= 2);
        delete m;
        ++number_of_solutions;
    }
    if(correct_number_of_solutions >= 0) assertEqual(correct_number_of_solutions,number_of_solutions);
}

testCase(_1x1) { runNonTrivialWeightTest(1,1,0); }
testCase(_1x2) { runNonTrivialWeightTest(1,2,9); }
testCase(_2x1) { runNonTrivialWeightTest(2,1,9); }
testCase(_2x2) { runNonTrivialWeightTest(2,2,15*15); }
testCase(_3x1) { runNonTrivialWeightTest(3,1,0); }
testCase(_3x2) { runNonTrivialWeightTest(3,2,15*15*(16-3-3-1)); }
testCase(_4x1) { runNonTrivialWeightTest(4,1,81); }

}
//@-others

}
//@-others
//@-leo
