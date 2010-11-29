//@+leo-ver=5-thin
//@+node:gcross.20101128173348.1804: * @thin weight.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128173348.1805: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <unit--.hpp>

#include "constraints/row_ordered/weight.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128173348.1818: ** Tests
testSuite(Constraints) { subSuite(RowOrdered) { subSuite(Weight) {

//@+others
//@+node:gcross.20101128173348.1819: *3* _1x1
testCase(_1x1) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(1,1);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101128173348.1820: *3* _1x2
testCase(_1x2) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(1,2);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101128173348.1821: *3* _2x1
testCase(_2x1) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(2,1);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(m->O[1].val() == 0 || m->O[0].val() > 0);
        ++number_of_solutions;
        delete m;
    }
    assertEqual(13,number_of_solutions);
}
//@+node:gcross.20101128173348.1822: *3* _2x2
testCase(_2x2) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(2,2);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        assertTrue(non_trivial_matrix(0,0).val() + non_trivial_matrix(1,0).val()
                >= non_trivial_matrix(0,1).val() + non_trivial_matrix(1,1).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(
        1     // top is identity
      + 6*7   // top is single operator
      + 9*16  // top is two operators
    ,number_of_solutions
    );
}
//@+node:gcross.20101128173348.1823: *3* _4x2
testCase(_4x2) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(4,2);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        assertTrue(non_trivial_matrix(0,0).val() + non_trivial_matrix(1,0).val()
                >= non_trivial_matrix(0,1).val() + non_trivial_matrix(1,1).val());
        assertTrue(non_trivial_matrix(0,2).val() + non_trivial_matrix(1,2).val()
                >= non_trivial_matrix(0,3).val() + non_trivial_matrix(1,3).val());
        assertTrue(
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
    assertTrue(number_of_solutions > 0);
}
//@-others

} } }
//@-others
//@-leo
