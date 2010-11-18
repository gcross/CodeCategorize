//@+leo-ver=5-thin
//@+node:gcross.20101117133000.1340: * @thin constraints.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117133000.1341: ** << Includes >>
#include <boost/foreach.hpp>
#include <iostream>
#include <unit--.hpp>

#include "constraints.hh"

using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101117133000.1448: ** Tests
testSuite(Constraints) {

//@+others
//@+node:gcross.20101117133000.1449: *3* CompleteColumns
subSuite(CompleteColumns,Constraints) {

//@+others
//@+node:gcross.20101117133000.1454: *4* _1x1
testCase(_1x1,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(1,1);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(0,number_of_solutions);
}
//@+node:gcross.20101117133000.1457: *4* _1x2
testCase(_1x2,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(1,2);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(0,number_of_solutions);
}
//@+node:gcross.20101117133000.1459: *4* _2x1
testCase(_2x1,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(2,1);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(m->non_trivial[0].val());
        assertTrue(m->non_trivial[1].val());
        assertTrue(
            (m->X[0].val() != m->X[1].val())
         || (m->Z[0].val() != m->Z[1].val())
        );
        delete m;
    }
}
//@+node:gcross.20101117133000.1461: *4* _2x2
testCase(_2x2,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(2,2);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        for(int i = 0; i < 4; ++i) assertTrue(m->non_trivial[i].val());
        IntMatrix O_matrix = m->getOMatrix();
        assertTrue(O_matrix(0,0).val() != O_matrix(1,0).val());
        assertTrue(O_matrix(0,1).val() != O_matrix(1,1).val());
        delete m;
    }
    assertTrue(number_of_solutions > 0);
}
//@+node:gcross.20101117133000.1463: *4* _3x3
testCase(_3x3,CompleteColumns) {
    CompleteColumnsOperatorSpace* m = new CompleteColumnsOperatorSpace(3,3);
    DFS<CompleteColumnsOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        IntMatrix O_matrix = m->getOMatrix();
        for(int column = 0; column < 3; ++column) {
            bool present[4];  BOOST_FOREACH(bool& x, present) { x = false; }
            for(int row = 0; row < 3; ++row) present[O_matrix(row,column).val()] = true;
            int count = 0;
            for(int i = 1; i < 4; ++i) if(present[i]) ++count;
            assertTrue(count >= 2);
        }
        delete m;
    }
    assertTrue(number_of_solutions > 0);
}
//@-others

}
//@+node:gcross.20101117133000.1487: *3* FirstColumnSpecialCase
subSuite(FirstColumnSpecialCase,Constraints) {

//@+others
//@+node:gcross.20101117133000.1489: *4* _1x1
testCase(_1x1,FirstColumnSpecialCase) {
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
//@+node:gcross.20101117133000.1491: *4* _1x2
testCase(_1x2,FirstColumnSpecialCase) {
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
//@+node:gcross.20101117133000.1493: *4* _2x1
testCase(_2x1,FirstColumnSpecialCase) {
    OperatorSpace* m = new OperatorSpace(2,1);
    postFirstColumnSpecialCaseConstraint(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(0,m->getZMatrix()(0,0).val());
        assertEqual(Z,m->getOMatrix()(1,0).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(2,number_of_solutions);
}
//@+node:gcross.20101117133000.1495: *4* _2x2
testCase(_2x2,FirstColumnSpecialCase) {
    OperatorSpace* m = new OperatorSpace(2,2);
    postFirstColumnSpecialCaseConstraint(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(0,m->getZMatrix()(0,0).val());
        assertEqual(Z,m->getOMatrix()(1,0).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(32,number_of_solutions);
}
//@+node:gcross.20101117133000.1497: *4* _3x3
testCase(_3x3,FirstColumnSpecialCase) {
    OperatorSpace* m = new OperatorSpace(3,3);
    postFirstColumnSpecialCaseConstraint(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertEqual(0,m->getZMatrix()(0,0).val());
        assertEqual(0,m->getZMatrix()(1,0).val());
        assertEqual(Z,m->getOMatrix()(2,0).val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(2*2*4*4*4*4*4*4,number_of_solutions);
}
//@-others

}
//@+node:gcross.20101117133000.1531: *3* RowOrdered
subSuite(RowOrdered,Constraints) {

//@+others
//@+node:gcross.20101117133000.1533: *4* Weight
subSuite(Weight,RowOrdered) {

//@+others
//@+node:gcross.20101117133000.1535: *5* _1x1
testCase(_1x1,Weight) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(1,1,false);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101117133000.1539: *5* _1x2
testCase(_1x2,Weight) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(1,2,false);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101117133000.1541: *5* _2x1
testCase(_2x1,Weight) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(2,1,false);
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
//@+node:gcross.20101117133000.1543: *5* _2x2
testCase(_2x2,Weight) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(2,2,false);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        assertTrue(non_trivial_matrix(0,0).val() + non_trivial_matrix(0,1).val()
                >= non_trivial_matrix(1,0).val() + non_trivial_matrix(1,1).val());
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
//@+node:gcross.20101117133000.1545: *5* _4x2
testCase(_4x2,Weight) {
    WeightRowOrderedOperatorSpace* m = new WeightRowOrderedOperatorSpace(4,2,false);
    DFS<WeightRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix();
        assertTrue(non_trivial_matrix(0,0).val() + non_trivial_matrix(0,1).val()
                >= non_trivial_matrix(1,0).val() + non_trivial_matrix(1,1).val());
        assertTrue(non_trivial_matrix(2,0).val() + non_trivial_matrix(2,1).val()
                >= non_trivial_matrix(3,0).val() + non_trivial_matrix(3,1).val());
        assertTrue(
                   non_trivial_matrix(0,0).val() + non_trivial_matrix(0,1).val()
                 > non_trivial_matrix(2,0).val() + non_trivial_matrix(2,1).val()
           ||      non_trivial_matrix(0,0).val() + non_trivial_matrix(0,1).val()
                == non_trivial_matrix(2,0).val() + non_trivial_matrix(2,1).val()
           &&      non_trivial_matrix(0,0).val() + non_trivial_matrix(0,1).val()
                >= non_trivial_matrix(2,0).val() + non_trivial_matrix(2,1).val()
        );
        ++number_of_solutions;
        delete m;
    }
    assertTrue(number_of_solutions > 0);
}
//@-others

}
//@+node:gcross.20101117133000.1567: *4* FirstColumnX
subSuite(FirstColumnX,RowOrdered) {

//@+others
//@+node:gcross.20101117133000.1568: *5* _1x1
testCase(_1x1,FirstColumnX) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(1,1);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101117133000.1569: *5* _1x2
testCase(_1x2,FirstColumnX) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(1,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101117133000.1570: *5* _2x1
testCase(_2x1,FirstColumnX) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(2,1);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(m->X[1].val() == 0 || m->X[0].val() == 1);
        ++number_of_solutions;
        delete m;
    }
    assertEqual(12,number_of_solutions);
}
//@+node:gcross.20101117133000.1571: *5* _2x2
testCase(_2x2,FirstColumnX) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(2,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        assertTrue(X_matrix(1,0).val() == 0 || X_matrix(0,0).val() == 1);
        ++number_of_solutions;
        delete m;
    }
    assertEqual(12*16,number_of_solutions);
}
//@+node:gcross.20101117133000.1572: *5* _4x2
testCase(_4x2,FirstColumnX) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(4,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        assertTrue(X_matrix(1,0).val() == 0 || X_matrix(0,0).val() == 1);
        assertTrue(X_matrix(3,0).val() == 0 || X_matrix(2,0).val() == 1);
        assertTrue(X_matrix(0,0).val() >= X_matrix(2,0).val()
           ||      X_matrix(0,0).val() == X_matrix(2,0).val()
               &&  X_matrix(1,0).val() >= X_matrix(3,0).val()

        );
        ++number_of_solutions;
        delete m;
    }
    assertTrue(number_of_solutions > 0);
}
//@-others

}
//@+node:gcross.20101117133000.1573: *4* TieBraker: Weight, FirstColumnX
subSuite(Tie_breaking_between_Weight_and_FirstColumnX,RowOrdered) {

//@+others
//@+node:gcross.20101117133000.1575: *5* _1x1
testCase(_1x1,Tie_breaking_between_Weight_and_FirstColumnX) {
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
//@+node:gcross.20101117133000.1588: *5* _1x2
testCase(_1x2,Tie_breaking_between_Weight_and_FirstColumnX) {
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
//@+node:gcross.20101117133000.1591: *5* _2x1
testCase(_2x1,Tie_breaking_between_Weight_and_FirstColumnX) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,1);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(m->X[1].val() == 0 || m->X[0].val() == 1);
        ++number_of_solutions;
        delete m;
    }
    assertEqual(12,number_of_solutions);
}
//@+node:gcross.20101117133000.1593: *5* _2x2
testCase(_2x2,Tie_breaking_between_Weight_and_FirstColumnX) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,2);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix(),
                   X_matrix = m->getXMatrix();
        assertTrue(non_trivial_matrix(0,1).val() >= non_trivial_matrix(1,1).val());
        assertTrue(
                    non_trivial_matrix(0,1).val() > non_trivial_matrix(1,1).val()
            ||      non_trivial_matrix(0,1).val() == non_trivial_matrix(1,1).val()
                &&  X_matrix(0,0).val() >= X_matrix(1,0).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101117133000.1595: *5* _2x3
testCase(_2x3,Tie_breaking_between_Weight_and_FirstColumnX) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(2,3);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix(),
                   X_matrix = m->getXMatrix();
        int row_0_weight = non_trivial_matrix(0,1).val() + non_trivial_matrix(0,2).val(),
            row_1_weight = non_trivial_matrix(1,1).val() + non_trivial_matrix(1,2).val();
        assertTrue(row_0_weight >= row_1_weight);
        assertTrue(
                    row_0_weight > row_1_weight
            ||      row_0_weight == row_1_weight
                &&  X_matrix(0,0).val() >= X_matrix(1,0).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101117133000.1599: *5* _4x2
testCase(_4x2,Tie_breaking_between_Weight_and_FirstColumnX) {
    WeightAndFirstColumnXRowOrderedOperatorSpace* m = new WeightAndFirstColumnXRowOrderedOperatorSpace(4,2);
    DFS<WeightAndFirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix non_trivial_matrix = m->getNonTrivialMatrix(),
                   X_matrix = m->getXMatrix();
        for(int i = 0; i < 4; i += 2) {
            assertTrue(non_trivial_matrix(i+0,1).val() >= non_trivial_matrix(i+1,1).val());
            assertTrue(
                        non_trivial_matrix(i+0,1).val() > non_trivial_matrix(i+1,1).val()
                ||      non_trivial_matrix(i+0,1).val() == non_trivial_matrix(i+1,1).val()
                    &&  X_matrix(i+0,0).val() >= X_matrix(i+1,0).val()
            );
        }
        assertTrue(non_trivial_matrix(0,1).val() >= non_trivial_matrix(2,1).val());
        assertTrue(
                    non_trivial_matrix(0,1).val() > non_trivial_matrix(2,1).val()
            ||      non_trivial_matrix(0,1).val() == non_trivial_matrix(2,1).val()
                &&  non_trivial_matrix(1,1).val() > non_trivial_matrix(3,1).val()
            ||      non_trivial_matrix(0,1).val() == non_trivial_matrix(2,1).val()
                &&  non_trivial_matrix(1,1).val() == non_trivial_matrix(3,1).val()
                &&  X_matrix(0,0).val() > X_matrix(2,0).val()
            ||      non_trivial_matrix(0,1).val() == non_trivial_matrix(2,1).val()
                &&  non_trivial_matrix(1,1).val() == non_trivial_matrix(3,1).val()
                &&  X_matrix(0,0).val() == X_matrix(2,0).val()
                &&  X_matrix(1,0).val() >= X_matrix(3,0).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@-others

}
//@-others

}
//@-others

}
//@-others
//@-leo