//@+leo-ver=5-thin
//@+node:gcross.20101128153132.1871: * @thin weight_and_first_column.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128153132.1872: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <unit--.hpp>

#include "constraints/row_ordered/weight_and_first_column.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128153132.1886: ** Tests
testSuite(Constraints) { subSuite(RowOrdered) { subSuite(WeightAndFirstColumnX) {

//@+others
//@+node:gcross.20101128153132.1887: *3* _1x1
testCase(_1x1) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(1,1);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101128153132.1888: *3* _1x2
testCase(_1x2) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(1,2);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101128153132.1889: *3* _2x1
testCase(_2x1) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,1);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(
                m->weights[0].val() >  m->weights[1].val()
            ||  m->weights[0].val() == m->weights[1].val()
            &&  m->X[0].val() >= m->X[1].val()
        );
        ++number_of_solutions;
        delete m;
    }
    assertEqual(11,number_of_solutions);
}
//@+node:gcross.20101128153132.1890: *3* _2x2
testCase(_2x2) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,2);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        assertTrue(
                m->weights[0].val() >  m->weights[1].val()
            ||  m->weights[0].val() == m->weights[1].val()
            &&  X_matrix(0,0).val() >= X_matrix(0,1).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101128153132.1891: *3* _2x3
testCase(_2x3) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,3);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        assertTrue(
                m->weights[0].val() >  m->weights[1].val()
            ||  m->weights[0].val() == m->weights[1].val()
            &&  X_matrix(0,0).val() >= X_matrix(0,1).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101128153132.1892: *3* _4x2
testCase(_4x2) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(4,2);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        for(int row = 0; row < 4; row += 2) {
            assertTrue(
                    m->weights[row].val() >  m->weights[row+1].val()
                ||  m->weights[row].val() == m->weights[row+1].val()
                &&  X_matrix(0,row).val() >= X_matrix(0,row+1).val()
            );
        }
        assertTrue(
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
