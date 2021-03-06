//@+leo-ver=5-thin
//@+node:gcross.20101116210424.2275: * @thin operator_space.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101116210424.2278: ** << Includes >>
#include <iostream>
#include <illuminate.hpp>

#include "operator_space.hh"
#include "solution_iterator.hh"

#include "test_utils.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101121200631.1632: ** Functions
//@+node:gcross.20101121200631.1633: *3* validateOperators
void validateOperators(OperatorSpace* m) {
    vector<dynamic_quantum_operator> operators = m->getOperators();
    int first_qubit = 0;
    for(int i = 0; i < m->number_of_pairs; ++i) {
        ASSERT_EQ('X',operators[2*i+0].pauli_char_at(i));
        ASSERT_EQ('Z',operators[2*i+1].pauli_char_at(i));
        ++first_qubit;
    }
    IntMatrix O_matrix = m->getOMatrix();
    for(int i = 0; i < m->number_of_operators; ++i) {
        for(int j = 0; j < m->number_of_qubits; ++j) {
            ASSERT_EQ(O_matrix(j,i).val(),operators[i][first_qubit+j]);
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
//@+node:gcross.20101123222425.2049: *3* runUpdateValidationTest
template<int number_of_operators, int number_of_qubits> void runUpdateValidationTest() {
    typedef static_quantum_operator<number_of_qubits+number_of_operators/2> quantum_operator;
    typedef static_vector<quantum_operator,number_of_operators> operator_vector;
    OperatorSpace* m = new OperatorSpace(number_of_operators,number_of_qubits);
    operator_vector operators;
    m->initializeOperators(operators);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> correct_operators = m->getOperators();
        m->updateOperators(operators);
        for(int i = 0; i < number_of_operators; ++i) {
            for(int j = 0; j < number_of_qubits+number_of_operators/2; ++j) {
                ASSERT_EQ(correct_operators[i].pauli_char_at(j),operators[i].pauli_char_at(j));
            }
        }
        delete m;
    }
}
//@+node:gcross.20101203210234.1831: *3* runMaximumWeightTest
void runMaximumWeightTest(int number_of_operators, int number_of_qubits, int maximum_weight) {
    int number_of_solutions = 0;
    for(SolutionIterator<> solution(auto_ptr<OperatorSpace>(new OperatorSpace(number_of_operators,number_of_qubits,make_optional(maximum_weight))));
        solution;
        ++solution
    ) {
        BOOST_FOREACH(const dynamic_quantum_operator& op, *solution) {
            ASSERT_TRUE(op.weight() <= maximum_weight);
        }
        ++number_of_solutions;
    }
    int correct_number_of_solutions = 0;
    for(SolutionIterator<> solution(auto_ptr<OperatorSpace>(new OperatorSpace(number_of_operators,number_of_qubits)));
        solution;
        ++solution
    ) {
        BOOST_FOREACH(const dynamic_quantum_operator& op, *solution) {
            if(op.weight() > maximum_weight) goto skip;
        }
        ++correct_number_of_solutions;
        skip: ;
    }
    ASSERT_EQ(correct_number_of_solutions,number_of_solutions);
}
//@+node:gcross.20101116210424.2279: ** Tests
TEST_SUITE(OperatorSpace_) {

//@+others
//@+node:gcross.20101116222338.1277: *3* 1x1
TEST_SUITE(_1x1) {

//@+others
//@+node:gcross.20101116222338.1384: *4* number of solutions
TEST_CASE(number_of_solutions) {
    ASSERT_EQ(4,countSolutions(new OperatorSpace(1,1)));
}
//@+node:gcross.20101116222338.1397: *4* correct order
TEST_CASE(correct_order) {
    OperatorSpace* m = new OperatorSpace(1,1);
    DFS<OperatorSpace> e(m);
    delete m;

    bool X[4] = {false,true,false,true}
       , Z[4] = {false,false,true,true};

    for(int i = 0; i < 4; ++i) {
        m = e.next();
        ASSERT_TRUE(m != NULL);
        ASSERT_EQ(X[i],m->X[0].val());
        ASSERT_EQ(Z[i],m->Z[0].val());
        delete m;
    }

    m = e.next();
    ASSERT_TRUE(m == NULL);
}
//@+node:gcross.20101119160843.1436: *4* correct properties
TEST_CASE(correct_properties) {
    OperatorSpace* m = new OperatorSpace(1,1);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        ASSERT_EQ(m->O[0].val() > 0 ? 1 : 0,m->non_trivial[0].val());
        validateNonTrivial(m->X,m->Z,m->non_trivial);
        ASSERT_EQ(m->non_trivial[0].val(),m->weights[0].val());
        delete m;
    }
}
//@+node:gcross.20101121200631.1635: *4* correct operators
TEST_CASE(correct_operators) { runOperatorValidationTest(1,1); }
//@+node:gcross.20101123222425.2047: *4* correct update
TEST_CASE(correct_update) { runUpdateValidationTest<1,1>(); }
//@+node:gcross.20101203210234.1830: *4* maximum weight
TEST_SUITE(maximum_weight) {
    TEST_CASE(_0) { runMaximumWeightTest(1,1,0); }
    TEST_CASE(_1) { runMaximumWeightTest(1,1,1); }
    TEST_CASE(_2) { runMaximumWeightTest(1,1,2); }
}
//@+node:gcross.20101209224839.2309: *4* correct codes
TEST_CASE(correct_codes) { checkCodes(new OperatorSpace(1,1)); }
//@-others

}
//@+node:gcross.20101116222338.1387: *3* 1x2
TEST_SUITE(_1x2) {

//@+others
//@+node:gcross.20101116222338.1388: *4* number of solutions
TEST_CASE(number_of_solutions) {
    ASSERT_EQ(16,countSolutions(new OperatorSpace(1,2)));
}
//@+node:gcross.20101116222338.1403: *4* correct order
TEST_CASE(correct_order) {
    OperatorSpace* m = new OperatorSpace(1,2);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 1; i > 0; --i) {
            ASSERT_EQ(x%2,m->X[i].val());
            x >>= 1;
            ASSERT_EQ(x%2,m->Z[i].val());
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@+node:gcross.20101119160843.1438: *4* correct properties
TEST_CASE(correct_properties) {
    OperatorSpace* m = new OperatorSpace(1,2);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < 2; ++i) ASSERT_EQ(m->O[i].val() > 0 ? 1 : 0,m->non_trivial[i].val());
        validateNonTrivial(m->X,m->Z,m->non_trivial);
        ASSERT_EQ(m->non_trivial[0].val()+m->non_trivial[1].val(),m->weights[0].val());
        delete m;
    }
}
//@+node:gcross.20101121200631.1637: *4* correct operators
TEST_CASE(correct_operators) { runOperatorValidationTest(1,2); }
//@+node:gcross.20101123222425.2051: *4* correct update
TEST_CASE(correct_update) { runUpdateValidationTest<1,2>(); }
//@+node:gcross.20101203210234.1833: *4* maximum weight
TEST_SUITE(maximum_weight) {
    TEST_CASE(_0) { runMaximumWeightTest(1,2,0); }
    TEST_CASE(_1) { runMaximumWeightTest(1,2,1); }
    TEST_CASE(_2) { runMaximumWeightTest(1,2,2); }
    TEST_CASE(_3) { runMaximumWeightTest(1,2,3); }
}
//@+node:gcross.20101209224839.2311: *4* correct codes
TEST_CASE(correct_codes) { checkCodes(new OperatorSpace(1,2)); }
//@-others

}
//@+node:gcross.20101116222338.1391: *3* 2x1
TEST_SUITE(_2x1) {

//@+others
//@+node:gcross.20101116222338.1392: *4* number of solutions
TEST_CASE(number_of_solutions) {
    ASSERT_EQ(16,countSolutions(new OperatorSpace(2,1)));
}
//@+node:gcross.20101116222338.1401: *4* correct order
TEST_CASE(correct_order) {
    OperatorSpace* m = new OperatorSpace(2,1);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 1; i > 0; --i) {
            ASSERT_EQ(x%2,m->X[i].val());
            x >>= 1;
            ASSERT_EQ(x%2,m->Z[i].val());
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@+node:gcross.20101119160843.1440: *4* correct properties
TEST_CASE(correct_properties) {
    OperatorSpace* m = new OperatorSpace(2,1);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < 2; ++i) ASSERT_EQ(m->O[i].val() > 0 ? 1 : 0,m->non_trivial[i].val());
        validateNonTrivial(m->X,m->Z,m->non_trivial);
        for(int row = 0; row < 2; ++row) ASSERT_EQ(m->non_trivial[row].val(),m->weights[row].val());
        delete m;
    }
}
//@+node:gcross.20101121200631.1639: *4* correct operators
TEST_CASE(correct_operators) { runOperatorValidationTest(2,1); }
//@+node:gcross.20101123222425.2053: *4* correct update
TEST_CASE(correct_update) { runUpdateValidationTest<2,1>(); }
//@+node:gcross.20101203210234.1835: *4* maximum weight
TEST_SUITE(maximum_weight) {
    TEST_CASE(_0) { runMaximumWeightTest(2,1,0); }
    TEST_CASE(_1) { runMaximumWeightTest(2,1,1); }
    TEST_CASE(_2) { runMaximumWeightTest(2,1,2); }
}
//@+node:gcross.20101209224839.2313: *4* correct codes
TEST_CASE(correct_codes) { checkCodes(new OperatorSpace(2,1)); }
//@-others

}
//@+node:gcross.20101116222338.1395: *3* 2x2
TEST_SUITE(_2x2) {

//@+others
//@+node:gcross.20101116222338.1396: *4* number of solutions
TEST_CASE(number_of_solutions) {
    ASSERT_EQ(256,countSolutions(new OperatorSpace(2,2)));
}
//@+node:gcross.20101116222338.1399: *4* correct order
TEST_CASE(correct_order) {
    OperatorSpace* m = new OperatorSpace(2,2);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 3; i > 0; --i) {
            ASSERT_EQ(x%2,m->X[i].val());
            x >>= 1;
            ASSERT_EQ(x%2,m->Z[i].val());
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@+node:gcross.20101119160843.1442: *4* correct properties
TEST_CASE(correct_properties) {
    OperatorSpace* m = new OperatorSpace(2,2);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < 4; ++i) ASSERT_EQ(m->O[i].val() > 0 ? 1 : 0,m->non_trivial[i].val());
        validateNonTrivial(m->X,m->Z,m->non_trivial);
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        for(int row = 0; row < 2; ++row) {
            int correct_weight = 0;
            for(int col = 0; col < 2; ++col) correct_weight += non_trivial_matrix(col,row).val();
            ASSERT_EQ(correct_weight,m->weights[row].val());
        }
        delete m;
    }
}
//@+node:gcross.20101121200631.1641: *4* correct operators
TEST_CASE(correct_operators) { runOperatorValidationTest(2,2); }
//@+node:gcross.20101123222425.2055: *4* correct update
TEST_CASE(correct_update) { runUpdateValidationTest<2,2>(); }
//@+node:gcross.20101203210234.1837: *4* maximum weight
TEST_SUITE(maximum_weight) {
    TEST_CASE(_0) { runMaximumWeightTest(2,2,0); }
    TEST_CASE(_1) { runMaximumWeightTest(2,2,1); }
    TEST_CASE(_2) { runMaximumWeightTest(2,2,2); }
    TEST_CASE(_3) { runMaximumWeightTest(2,2,3); }
}
//@+node:gcross.20101209224839.2315: *4* correct codes
TEST_CASE(correct_codes) { checkCodes(new OperatorSpace(2,2)); }
//@-others

}
//@+node:gcross.20101116222338.1407: *3* 3x3
TEST_SUITE(_3x3) {

//@+others
//@+node:gcross.20101116222338.1408: *4* number of solutions
TEST_CASE(number_of_solutions) {
    ASSERT_EQ(1<<(2*3*3),countSolutions(new OperatorSpace(3,3)));
}
//@+node:gcross.20101116222338.1415: *4* correct order
TEST_CASE(correct_order) {
    OperatorSpace* m = new OperatorSpace(3,3);
    DFS<OperatorSpace> e(m);
    delete m;

    int solution_number = 0;
    m = e.next();
    while(m != NULL) {
        int x = solution_number;
        for(int i = 8; i > 0; --i) {
            ASSERT_EQ(x%2,m->X[i].val());
            x >>= 1;
            ASSERT_EQ(x%2,m->Z[i].val());
            x >>= 1;
        }
        ++solution_number;
        delete m;
        m = e.next();
    }
}
//@+node:gcross.20101119160843.1444: *4* correct properties
TEST_CASE(correct_properties) {
    OperatorSpace* m = new OperatorSpace(3,3);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < 9; ++i) ASSERT_EQ(m->O[i].val() > 0 ? 1 : 0,m->non_trivial[i].val());
        validateNonTrivial(m->X,m->Z,m->non_trivial);
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        for(int row = 0; row < 3; ++row) {
            int correct_weight = 0;
            for(int col = 0; col < 3; ++col) correct_weight += non_trivial_matrix(col,row).val();
            ASSERT_EQ(correct_weight,m->weights[row].val());
        }
        delete m;
    }
}
//@+node:gcross.20101121200631.1643: *4* correct operators
TEST_CASE(correct_operators) { runOperatorValidationTest(3,3); }
//@+node:gcross.20101123222425.2057: *4* correct update
TEST_CASE(correct_update) { runUpdateValidationTest<3,3>(); }
//@+node:gcross.20101203210234.1839: *4* maximum weight
TEST_SUITE(maximum_weight) {
    TEST_CASE(_0) { runMaximumWeightTest(3,3,0); }
    TEST_CASE(_1) { runMaximumWeightTest(3,3,1); }
    TEST_CASE(_2) { runMaximumWeightTest(3,3,2); }
}
//@+node:gcross.20101209224839.2317: *4* correct codes
TEST_CASE(correct_codes) { checkCodes(new OperatorSpace(3,3)); }
//@-others

}
//@-others

}
//@-others
//@-leo
