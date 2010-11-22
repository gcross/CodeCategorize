//@+leo-ver=5-thin
//@+node:gcross.20101117133000.1340: * @thin constraints.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117133000.1341: ** << Includes >>
#include <boost/foreach.hpp>
#include <iostream>
#include <unit--.hpp>

#include "constraints.hh"
#include "test_utils.hh"

using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101117133000.1448: ** Tests
testSuite(Constraints) {

//@+others
//@+node:gcross.20101117133000.1629: *3* ColumnXZYOrdering
subSuite(ColumnXZYOrdering) {

//@+others
//@+node:gcross.20101117133000.1630: *4* _1x1
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
//@+node:gcross.20101117133000.1631: *4* _1x2
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
//@+node:gcross.20101117133000.1632: *4* _2x1
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
//@+node:gcross.20101117133000.1633: *4* _2x2
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
//@+node:gcross.20101118114009.1411: *4* _3x3
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
//@+node:gcross.20101118114009.1454: *3* ColumnOrdered
subSuite(ColumnOrdered) {

//@+others
//@+node:gcross.20101118114009.1455: *4* _1x1
testCase(_1x1) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(1,1);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4,number_of_solutions);
}
//@+node:gcross.20101118114009.1461: *4* _1x2
testCase(_1x2) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(1,2);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(m->O[0].val() >= m->O[1].val());
        ++number_of_solutions;
        delete m;
    }
    assertEqual(10,number_of_solutions);
}
//@+node:gcross.20101118114009.1463: *4* _1x3
testCase(_1x3) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(1,3);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        assertTrue(m->O[0].val() >= m->O[1].val());
        assertTrue(m->O[1].val() >= m->O[2].val());
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101118114009.1467: *4* _2x1
testCase(_2x1) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(2,1);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101118114009.1473: *4* _2x2
testCase(_2x2) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(2,2);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix();
        assertTrue(O_matrix(0,0).val() >= O_matrix(1,0).val());
        assertTrue(
                O_matrix(0,0).val() >  O_matrix(1,0).val()
          ||    O_matrix(0,0).val() == O_matrix(1,0).val()
             && O_matrix(0,1).val() >= O_matrix(1,1).val()
        );
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4*10+6*16,number_of_solutions);
}
//@+node:gcross.20101118114009.1475: *4* _2x3
testCase(_2x3) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(2,3);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix();
        assertTrue(O_matrix(0,0).val() >= O_matrix(1,0).val());
        assertTrue(
                O_matrix(0,0).val() >  O_matrix(1,0).val()
          ||    O_matrix(0,0).val() == O_matrix(1,0).val()
             && O_matrix(0,1).val() >= O_matrix(1,1).val()
        );
        assertTrue(O_matrix(1,0).val() >= O_matrix(2,0).val());
        assertTrue(
                O_matrix(1,0).val() >  O_matrix(2,0).val()
          ||    O_matrix(1,0).val() == O_matrix(2,0).val()
             && O_matrix(1,1).val() >= O_matrix(2,1).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101118114009.1469: *4* _3x1
testCase(_3x1) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(3,1);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(64,number_of_solutions);
}
//@+node:gcross.20101118114009.1477: *4* _3x2
testCase(_3x2) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(3,2);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix();
        assertTrue(O_matrix(0,0).val() >= O_matrix(1,0).val());
        assertTrue(
                O_matrix(0,0).val() >  O_matrix(1,0).val()
          ||    O_matrix(0,0).val() == O_matrix(1,0).val()
             && O_matrix(0,1).val() >= O_matrix(1,1).val()
          ||    O_matrix(0,0).val() == O_matrix(1,0).val()
             && O_matrix(0,1).val() == O_matrix(1,1).val()
             && O_matrix(0,2).val() >= O_matrix(1,2).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@+node:gcross.20101118114009.1479: *4* _3x3
testCase(_3x3) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(3,3);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix();
        assertTrue(O_matrix(0,0).val() >= O_matrix(1,0).val());
        assertTrue(
                O_matrix(0,0).val() >  O_matrix(1,0).val()
          ||    O_matrix(0,0).val() == O_matrix(1,0).val()
             && O_matrix(0,1).val() >= O_matrix(1,1).val()
          ||    O_matrix(0,0).val() == O_matrix(1,0).val()
             && O_matrix(0,1).val() == O_matrix(1,1).val()
             && O_matrix(0,2).val() >= O_matrix(1,2).val()
        );
        assertTrue(O_matrix(1,0).val() >= O_matrix(2,0).val());
        assertTrue(
                O_matrix(1,0).val() >  O_matrix(2,0).val()
          ||    O_matrix(1,0).val() == O_matrix(2,0).val()
             && O_matrix(1,1).val() >= O_matrix(2,1).val()
          ||    O_matrix(1,0).val() == O_matrix(2,0).val()
             && O_matrix(1,1).val() == O_matrix(2,1).val()
             && O_matrix(1,2).val() >= O_matrix(2,2).val()
        );
        ++number_of_solutions;
        delete m;
    }
}
//@-others

}
//@+node:gcross.20101117133000.1487: *3* FirstColumnSpecialCase
subSuite(FirstColumnSpecialCase) {

//@+others
//@+node:gcross.20101117133000.1489: *4* _1x1
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
//@+node:gcross.20101117133000.1491: *4* _1x2
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
//@+node:gcross.20101117133000.1493: *4* _2x1
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
//@+node:gcross.20101117133000.1495: *4* _2x2
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
//@+node:gcross.20101117133000.1497: *4* _3x3
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
//@+node:gcross.20101117133000.1531: *3* RowOrdered
subSuite(RowOrdered) {

//@+others
//@+node:gcross.20101117133000.1533: *4* Weight
subSuite(Weight) {

//@+others
//@+node:gcross.20101117133000.1535: *5* _1x1
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
//@+node:gcross.20101117133000.1539: *5* _1x2
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
//@+node:gcross.20101117133000.1541: *5* _2x1
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
//@+node:gcross.20101117133000.1543: *5* _2x2
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
//@+node:gcross.20101117133000.1545: *5* _4x2
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

}
//@+node:gcross.20101117133000.1567: *4* FirstColumnX
subSuite(FirstColumnX) {

//@+others
//@+node:gcross.20101117133000.1568: *5* _1x1
testCase(_1x1) {
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
testCase(_1x2) {
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
testCase(_2x1) {
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
testCase(_2x2) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(2,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        assertTrue(X_matrix(0,1).val() == 0 || X_matrix(0,0).val() == 1);
        ++number_of_solutions;
        delete m;
    }
    assertEqual(12*16,number_of_solutions);
}
//@+node:gcross.20101117133000.1572: *5* _4x2
testCase(_4x2) {
    FirstColumnXRowOrderedOperatorSpace* m = new FirstColumnXRowOrderedOperatorSpace(4,2);
    DFS<FirstColumnXRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix();
        assertTrue(X_matrix(0,1).val() == 0 || X_matrix(0,0).val() == 1);
        assertTrue(X_matrix(0,3).val() == 0 || X_matrix(0,2).val() == 1);
        assertTrue(X_matrix(0,0).val() >= X_matrix(0,2).val()
           ||      X_matrix(0,0).val() == X_matrix(0,2).val()
               &&  X_matrix(0,1).val() >= X_matrix(0,3).val()

        );
        ++number_of_solutions;
        delete m;
    }
    assertTrue(number_of_solutions > 0);
}
//@-others

}
//@+node:gcross.20101117133000.1573: *4* TieBraker: Weight, FirstColumnX
subSuite(Tie_breaking_between_Weight_and_FirstColumnX) {

//@+others
//@+node:gcross.20101117133000.1575: *5* _1x1
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
//@+node:gcross.20101117133000.1588: *5* _1x2
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
//@+node:gcross.20101117133000.1591: *5* _2x1
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
//@+node:gcross.20101117133000.1593: *5* _2x2
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
//@+node:gcross.20101117133000.1595: *5* _2x3
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
//@+node:gcross.20101117133000.1599: *5* _4x2
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

}
//@-others

}
//@+node:gcross.20101121135345.1486: *3* MinimalWeight
subSuite(MinimalWeight) {

//@+others
//@+node:gcross.20101121135345.1487: *4* 2x1
subSuite(_2x1) {

//@+others
//@+node:gcross.20101121135345.1488: *5* correct derived fields
testCase(correct_derived_fields) {
    MinimalWeightOperatorSpace* m = new MinimalWeightOperatorSpace(2,1);
    DFS<MinimalWeightOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        validateNonTrivial(m->products_X,m->products_Z,m->products_non_trivial);
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
