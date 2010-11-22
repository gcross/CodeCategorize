//@+leo-ver=5-thin
//@+node:gcross.20101116210424.2275: * @thin operator_space.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101116210424.2278: ** << Includes >>
#include <iostream>
#include <unit--.hpp>

#include "operator_space.hh"

using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101121200631.1632: ** Functions
//@+node:gcross.20101121200631.1633: *3* validateOperators
void validateOperators(OperatorSpace* m) {
    vector<dynamic_quantum_operator> operators = m->getOperators();
    int first_qubit = 0;
    for(int i = 0; i < m->number_of_pairs; ++i) {
        assertEqual('X',operators[2*i+0].pauli_char_at(i));
        assertEqual('Z',operators[2*i+1].pauli_char_at(i));
        ++first_qubit;
    }
    IntMatrix O_matrix = m->getOMatrix();
    for(int i = 0; i < m->number_of_operators; ++i) {
        for(int j = 0; j < m->number_of_qubits; ++j) {
            assertEqual(O_matrix(j,i).val(),operators[i][first_qubit+j]);
        }
    }
}
//@+node:gcross.20101121200631.1634: *3* runOperatorValidationTest
void runOperatorValidationTest(int number_of_operators, int number_of_qubits) {
    OperatorSpace* m = new OperatorSpace(number_of_operators,number_of_qubits);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        validateOperators(m);
        delete m;
    }
}
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
//@+node:gcross.20101119160843.1436: *4* correct properties
testCase(correct_properties,_1x1) {
    OperatorSpace* m = new OperatorSpace(1,1);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(m->O[0].val() > 0 ? 1 : 0,m->non_trivial[0].val());
        assertEqual(m->non_trivial[0].val(),m->weights[0].val());
        delete m;
    }
}
//@+node:gcross.20101121200631.1635: *4* correct operators
testCase(correct_operators) { runOperatorValidationTest(1,1); }
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
//@+node:gcross.20101119160843.1438: *4* correct properties
testCase(correct_properties,_1x2) {
    OperatorSpace* m = new OperatorSpace(1,2);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < 2; ++i) assertEqual(m->O[i].val() > 0 ? 1 : 0,m->non_trivial[i].val());
        assertEqual(m->non_trivial[0].val()+m->non_trivial[1].val(),m->weights[0].val());
        delete m;
    }
}
//@+node:gcross.20101121200631.1637: *4* correct operators
testCase(correct_operators) { runOperatorValidationTest(1,2); }
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
//@+node:gcross.20101119160843.1440: *4* correct properties
testCase(correct_properties,_2x1) {
    OperatorSpace* m = new OperatorSpace(2,1);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < 2; ++i) assertEqual(m->O[i].val() > 0 ? 1 : 0,m->non_trivial[i].val());
        for(int row = 0; row < 2; ++row) assertEqual(m->non_trivial[row].val(),m->weights[row].val());
        delete m;
    }
}
//@+node:gcross.20101121200631.1639: *4* correct operators
testCase(correct_operators) { runOperatorValidationTest(2,1); }
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
//@+node:gcross.20101119160843.1442: *4* correct properties
testCase(correct_properties,_2x2) {
    OperatorSpace* m = new OperatorSpace(2,2);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < 4; ++i) assertEqual(m->O[i].val() > 0 ? 1 : 0,m->non_trivial[i].val());
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        for(int row = 0; row < 2; ++row) {
            int correct_weight = 0;
            for(int col = 0; col < 2; ++col) correct_weight += non_trivial_matrix(col,row).val();
            assertEqual(correct_weight,m->weights[row].val());
        }
        delete m;
    }
}
//@+node:gcross.20101121200631.1641: *4* correct operators
testCase(correct_operators) { runOperatorValidationTest(2,2); }
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
//@+node:gcross.20101119160843.1444: *4* correct properties
testCase(correct_properties,_3x3) {
    OperatorSpace* m = new OperatorSpace(3,3);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < 9; ++i) assertEqual(m->O[i].val() > 0 ? 1 : 0,m->non_trivial[i].val());
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        for(int row = 0; row < 3; ++row) {
            int correct_weight = 0;
            for(int col = 0; col < 3; ++col) correct_weight += non_trivial_matrix(col,row).val();
            assertEqual(correct_weight,m->weights[row].val());
        }
        delete m;
    }
}
//@+node:gcross.20101121200631.1643: *4* correct operators
testCase(correct_operators) { runOperatorValidationTest(3,3); }
//@-others

}
//@-others

}
//@-others
//@-leo
