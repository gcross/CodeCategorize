//@+leo-ver=5-thin
//@+node:gcross.20101128173348.1804: * @thin weight.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128173348.1805: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <illuminate.hpp>

#include "constraints/row_ordered/weight.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128173348.1818: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(RowOrdered) { TEST_SUITE(Weight) {

//@+others
//@+node:gcross.20101128173348.1819: *3* _1x1
TEST_CASE(_1x1) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(1,1);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(4,number_of_solutions);
}
//@+node:gcross.20101128173348.1820: *3* _1x2
TEST_CASE(_1x2) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(1,2);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(16,number_of_solutions);
}
//@+node:gcross.20101128173348.1821: *3* _2x1
TEST_CASE(_2x1) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(2,1);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ASSERT_TRUE(m->O[1].val() == 0 || m->O[0].val() > 0);
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(13,number_of_solutions);
}
//@+node:gcross.20101128173348.1822: *3* _2x2
TEST_CASE(_2x2) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(2,2);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        ASSERT_TRUE(non_trivial_matrix(0,0).val() + non_trivial_matrix(1,0).val()
                >= non_trivial_matrix(0,1).val() + non_trivial_matrix(1,1).val());
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(
        1     // top is identity
      + 6*7   // top is single operator
      + 9*16  // top is two operators
    ,number_of_solutions
    );
}
//@+node:gcross.20101128173348.1823: *3* _4x2
TEST_CASE(_4x2) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(4,2);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        ASSERT_TRUE(non_trivial_matrix(0,0).val() + non_trivial_matrix(1,0).val()
                >= non_trivial_matrix(0,1).val() + non_trivial_matrix(1,1).val());
        ASSERT_TRUE(non_trivial_matrix(0,2).val() + non_trivial_matrix(1,2).val()
                >= non_trivial_matrix(0,3).val() + non_trivial_matrix(1,3).val());
        ASSERT_TRUE(
                   non_trivial_matrix(0,0).val() + non_trivial_matrix(1,0).val()
                 > non_trivial_matrix(0,2).val() + non_trivial_matrix(1,2).val()
           ||      non_trivial_matrix(0,0).val() + non_trivial_matrix(1,0).val()
                == non_trivial_matrix(0,2).val() + non_trivial_matrix(1,2).val()
           &&      non_trivial_matrix(0,0).val() + non_trivial_matrix(1,0).val()
                >= non_trivial_matrix(0,2).val() + non_trivial_matrix(1,2).val()
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
