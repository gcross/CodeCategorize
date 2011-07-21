//@+leo-ver=5-thin
//@+node:gcross.20101129164055.1853: * @thin first_column_XZ.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101129164055.1854: ** << Includes >>
#include <illuminate.hpp>

#include "constraints/first_column_XZ.hh"

#include "test_utils.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101129164055.1862: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(FirstColumnXZ) {

//@+others
//@+node:gcross.20101129164055.1863: *3* _1x1
TEST_CASE(_1x1) {
    FirstColumnXZOperatorSpace* m = new FirstColumnXZOperatorSpace(1,1);
    DFS<FirstColumnXZOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ASSERT_EQ(Z,m->getOMatrix()(0,0).val());
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(1,number_of_solutions);
    checkCodes(new FirstColumnXZOperatorSpace(1,1));
}
//@+node:gcross.20101129164055.1864: *3* _1x2
TEST_CASE(_1x2) {
    FirstColumnXZOperatorSpace* m = new FirstColumnXZOperatorSpace(1,2);
    DFS<FirstColumnXZOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ASSERT_EQ(Z,m->getOMatrix()(0,0).val());
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(4,number_of_solutions);
    checkCodes(new FirstColumnXZOperatorSpace(1,2));
}
//@+node:gcross.20101129164055.1867: *3* _3x3
TEST_CASE(_3x3) {
    FirstColumnXZOperatorSpace* m = new FirstColumnXZOperatorSpace(3,3);
    DFS<FirstColumnXZOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ASSERT_EQ(0,m->getZMatrix()(0,0).val());
        ASSERT_EQ(0,m->getZMatrix()(0,1).val());
        ASSERT_EQ(Z,m->getOMatrix()(0,2).val());
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(2*2*4*4*4*4*4*4,number_of_solutions);
    checkCodes(new FirstColumnXZOperatorSpace(3,3));
}
//@-others

} }
//@-others
//@-leo
