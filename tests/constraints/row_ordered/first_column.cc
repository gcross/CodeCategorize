//@+leo-ver=5-thin
//@+node:gcross.20101128153132.1848: * @thin first_column.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128153132.1849: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <illuminate.hpp>

#include "constraints/row_ordered/first_column.hh"
#include "test_utils.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128153132.1857: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(RowOrdered) { TEST_SUITE(FirstColumnX) {

//@+others
//@+node:gcross.20101128153132.1858: *3* _1x1
TEST_CASE(_1x1) {
    int number_of_solutions = countSolutions(new FirstColumnXRowOrderedOperatorSpace(1,1));
    ASSERT_EQ(1,number_of_solutions);
}
//@+node:gcross.20101128153132.1859: *3* _1x2
TEST_CASE(_1x2) {
    int number_of_solutions = countSolutions(new FirstColumnXRowOrderedOperatorSpace(1,2));
    ASSERT_EQ(4,number_of_solutions);
}
//@+node:gcross.20101128153132.1860: *3* _3x1
TEST_CASE(_3x1) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(3,1);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ASSERT_TRUE(m->X[1].val() == 0 || m->X[0].val() == 1);
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(3,number_of_solutions);
}
//@+node:gcross.20101128153132.1861: *3* _3x2
TEST_CASE(_3x2) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(3,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        ASSERT_TRUE(X_matrix(0,1).val() == 0 || X_matrix(0,0).val() == 1);
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(3*4*4*4,number_of_solutions);
}
//@+node:gcross.20101128153132.1862: *3* _5x2
TEST_CASE(_5x2) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(5,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        ASSERT_TRUE(X_matrix(0,1).val() == 0 || X_matrix(0,0).val() == 1);
        ASSERT_TRUE(X_matrix(0,3).val() == 0 || X_matrix(0,2).val() == 1);
        ASSERT_TRUE(X_matrix(0,0).val() >= X_matrix(0,2).val()
           ||      X_matrix(0,0).val() == X_matrix(0,2).val()
               &&  X_matrix(0,1).val() >= X_matrix(0,3).val()

        );
        ++number_of_solutions;
        delete m;
    }
    ASSERT_TRUE(number_of_solutions > 0);
}
//@-others

} } }
//@-others
//@-leo
