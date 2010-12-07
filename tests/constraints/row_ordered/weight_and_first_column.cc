//@+leo-ver=5-thin
//@+node:gcross.20101128153132.1871: * @thin weight_and_first_column.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128153132.1872: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <illuminate.hpp>

#include "constraints/row_ordered/weight_and_first_column.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128153132.1886: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(RowOrdered) { TEST_SUITE(WeightAndFirstColumnX) {

//@+others
//@+node:gcross.20101128153132.1887: *3* _1x1
TEST_CASE(_1x1) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(1,1);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(4,number_of_solutions);
}
//@+node:gcross.20101128153132.1888: *3* _1x2
TEST_CASE(_1x2) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(1,2);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(16,number_of_solutions);
}
//@+node:gcross.20101128153132.1889: *3* _2x1
TEST_CASE(_2x1) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,1);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ASSERT_TRUE(
                m->weights[0].val() >  m->weights[1].val()
            ||  m->weights[0].val() == m->weights[1].val()
            &&  m->X[0].val() >= m->X[1].val()
        );
        ++number_of_solutions;
        delete m;
    }
    ASSERT_EQ(11,number_of_solutions);
}
//@+node:gcross.20101128153132.1890: *3* _2x2
TEST_CASE(_2x2) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,2);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        ASSERT_TRUE(
                m->weights[0].val() >  m->weights[1].val()
            ||  m->weights[0].val() == m->weights[1].val()
            &&  X_matrix(0,0).val() >= X_matrix(0,1).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101128153132.1891: *3* _2x3
TEST_CASE(_2x3) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,3);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        ASSERT_TRUE(
                m->weights[0].val() >  m->weights[1].val()
            ||  m->weights[0].val() == m->weights[1].val()
            &&  X_matrix(0,0).val() >= X_matrix(0,1).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101128153132.1892: *3* _4x2
TEST_CASE(_4x2) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(4,2);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        for(int row = 0; row < 4; row += 2) {
            ASSERT_TRUE(
                    m->weights[row].val() >  m->weights[row+1].val()
                ||  m->weights[row].val() == m->weights[row+1].val()
                &&  X_matrix(0,row).val() >= X_matrix(0,row+1).val()
            );
        }
        ASSERT_TRUE(
                m->weights[0].val() >  m->weights[2].val()
            ||  m->weights[0].val() == m->weights[2].val()
            &&  m->weights[1].val() >  m->weights[3].val()
            ||  m->weights[0].val() == m->weights[2].val()
            &&  m->weights[1].val() == m->weights[3].val()
            &&  X_matrix(0,0).val() > X_matrix(0,2).val()
            ||  m->weights[0].val() == m->weights[2].val()
            &&  m->weights[1].val() == m->weights[3].val()
            &&  X_matrix(0,0).val() == X_matrix(0,2).val()
            &&  X_matrix(0,1).val() >= X_matrix(0,3).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@-others

} } }
//@-others
//@-leo
