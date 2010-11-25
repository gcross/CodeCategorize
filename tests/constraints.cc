//@+leo-ver=5-thin
//@+node:gcross.20101117133000.1340: * @thin constraints.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117133000.1341: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <unit--.hpp>

#include "commutator.hh"
#include "constrained_operator_space.hh"
#include "constraints.hh"
#include "constraints/column_ordered.hh"
#include "constraints/minimal_weight.hh"
#include "constraints/row_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/weight.hh"
#include "constraints/row_ordered/weight_and_first_column.hh"
#include "operator_space.hh"
#include "test_utils.hh"
#include "utilities.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
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
    int number_of_solutions = 0;
    {
        ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(1,3);
        DFS<ColumnOrderedOperatorSpace> e(m);
        delete m;

        for(m = e.next(); m != NULL; m = e.next()) {
            assertTrue(m->O[0].val() >= m->O[1].val());
            assertTrue(m->O[1].val() >= m->O[2].val());
            ++number_of_solutions;
            delete m;
        }
    }
    int correct_number_of_solutions = 0;
    {
        OperatorSpace* m = new OperatorSpace(1,3);
        DFS<OperatorSpace> e(m);
        delete m;

        for(m = e.next(); m != NULL; m = e.next()) {
            if(m->O[0].val() >= m->O[1].val() && m->O[1].val() >= m->O[2].val()) ++correct_number_of_solutions;
            delete m;
        }
    }
    assertEqual(correct_number_of_solutions,number_of_solutions);
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
    int number_of_solutions = 0;
    {
        ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(2,3);
        DFS<ColumnOrderedOperatorSpace> e(m);
        delete m;    
        for(m = e.next(); m != NULL; m = e.next()) {
            IntMatrix O_matrix = m->getOMatrix();
            for(int i = 0; i < 2; ++i) {
                assertTrue(O_matrix(i,0).val() >= O_matrix(i+1,0).val());
                assertTrue(
                        O_matrix(i,0).val() >  O_matrix(i+1,0).val()
                  ||    O_matrix(i,0).val() == O_matrix(i+1,0).val()
                     && O_matrix(i,1).val() >= O_matrix(i+1,1).val()
                );
            }
            ++number_of_solutions;
            delete m;
        }
    }
    int correct_number_of_solutions = 0;
    {
        OperatorSpace* m = new OperatorSpace(2,3);
        DFS<OperatorSpace> e(m);
        delete m;

        for(m = e.next(); m != NULL; m = e.next()) {
            IntMatrix O_matrix = m->getOMatrix();
            for(int i = 0; i < 2; ++i) {
                if( not (
                            O_matrix(i,0).val() >  O_matrix(i+1,0).val()
                      ||    O_matrix(i,0).val() == O_matrix(i+1,0).val()
                         && O_matrix(i,1).val() >= O_matrix(i+1,1).val()
                )) goto skip;
            }
            ++correct_number_of_solutions;
            skip:
            delete m;
        }
    }
    assertEqual(correct_number_of_solutions,number_of_solutions);
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
    int number_of_solutions = 0;
    {
        ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(3,2);
        DFS<ColumnOrderedOperatorSpace> e(m);
        delete m;
        for(m = e.next(); m != NULL; m = e.next()) {
            IntMatrix O_matrix = m->getOMatrix();
            assertTrue(O_matrix(0,0).val() >= O_matrix(1,0).val());
            assertTrue(
                    O_matrix(0,0).val() >  O_matrix(1,0).val()
              ||    O_matrix(0,0).val() == O_matrix(1,0).val()
                 && O_matrix(0,1).val() >  O_matrix(1,1).val()
              ||    O_matrix(0,0).val() == O_matrix(1,0).val()
                 && O_matrix(0,1).val() == O_matrix(1,1).val()
                 && O_matrix(0,2).val() >= O_matrix(1,2).val()
            );
            ++number_of_solutions;
            delete m;
        }
    }
    int correct_number_of_solutions = 0;
    {
        OperatorSpace* m = new OperatorSpace(3,2);
        DFS<OperatorSpace> e(m);
        delete m;
        for(m = e.next(); m != NULL; m = e.next()) {
            IntMatrix O_matrix = m->getOMatrix();
            if(
                    O_matrix(0,0).val() >  O_matrix(1,0).val()
              ||    O_matrix(0,0).val() == O_matrix(1,0).val()
                 && O_matrix(0,1).val() >  O_matrix(1,1).val()
              ||    O_matrix(0,0).val() == O_matrix(1,0).val()
                 && O_matrix(0,1).val() == O_matrix(1,1).val()
                 && O_matrix(0,2).val() >= O_matrix(1,2).val()
            ) ++correct_number_of_solutions;
            delete m;
        }
    }
    assertEqual(correct_number_of_solutions,number_of_solutions);
}
//@+node:gcross.20101118114009.1479: *4* _3x3
testCase(_3x3) {
    int number_of_solutions = 0;
    {
        ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(3,3);
        DFS<ColumnOrderedOperatorSpace> e(m);
        delete m;
        for(m = e.next(); m != NULL; m = e.next()) {
            IntMatrix O_matrix = m->getOMatrix();
            //cout << O_matrix << endl << endl;
            for(int i = 0; i < 2; ++i) {
                assertTrue(O_matrix(i,0).val() >= O_matrix(i+1,0).val());
                assertTrue(
                        O_matrix(i,0).val() >  O_matrix(i+1,0).val()
                  ||    O_matrix(i,0).val() == O_matrix(i+1,0).val()
                     && O_matrix(i,1).val() >  O_matrix(i+1,1).val()
                  ||    O_matrix(i,0).val() == O_matrix(i+1,0).val()
                     && O_matrix(i,1).val() == O_matrix(i+1,1).val()
                     && O_matrix(i,2).val() >= O_matrix(i+1,2).val()
                );
            }
            ++number_of_solutions;
            delete m;
        }
    }
    int correct_number_of_solutions = 0;
    {
        OperatorSpace* m = new OperatorSpace(3,3);
        DFS<OperatorSpace> e(m);
        delete m;
        for(m = e.next(); m != NULL; m = e.next()) {
            IntMatrix O_matrix = m->getOMatrix();
            for(int i = 0; i < 2; ++i) {
                if( not (
                        O_matrix(i,0).val() >  O_matrix(i+1,0).val()
                  ||    O_matrix(i,0).val() == O_matrix(i+1,0).val()
                     && O_matrix(i,1).val() >  O_matrix(i+1,1).val()
                  ||    O_matrix(i,0).val() == O_matrix(i+1,0).val()
                     && O_matrix(i,1).val() == O_matrix(i+1,1).val()
                     && O_matrix(i,2).val() >= O_matrix(i+1,2).val()
                )) goto skip;
            }
            ++correct_number_of_solutions;
            skip:
            delete m;
        }
    }
    assertEqual(correct_number_of_solutions,number_of_solutions);
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
//@+node:gcross.20101123173026.1543: *4* AntiCommutatorCount
subSuite(AntiCommutatorCount) {

void runCountTest(int number_of_operators, int number_of_qubits) {
    AntiCommutatorCountOrderedOperatorSpace* m = new AntiCommutatorCountOrderedOperatorSpace(number_of_operators,number_of_qubits);
    DFS<AntiCommutatorCountOrderedOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        for(int i = 0; i < number_of_operators; ++i) {
            int number_of_anti_commuting_operators = 0;
            for(int j = 0; j < number_of_operators; ++j) {
                if(operators[i]&&operators[j]) ++number_of_anti_commuting_operators;
            }
            assertEqual(number_of_anti_commuting_operators,m->number_of_anti_commuting_operators[i].val());
        }
        delete m;
    }
}

testCase(_2x1) { runCountTest(2,1); }
testCase(_2x2) { runCountTest(2,2); }
testCase(_3x1) { runCountTest(3,1); }
testCase(_3x2) { runCountTest(3,2); }
testCase(_4x1) { runCountTest(4,1); }
testCase(_4x2) { runCountTest(4,2); }

}
//@-others

}
//@+node:gcross.20101121135345.1486: *3* MinimalWeight
subSuite(MinimalWeight) {

//@+others
//@+node:gcross.20101121135345.1494: *4* Functions
//@+node:gcross.20101121200631.1645: *5* checkAllProducts
bool checkAllProducts(
    const vector<dynamic_quantum_operator>& operators,
    const dynamic_quantum_operator op,
    const size_t minimum_weight,
    const int first_operator_number
) {
    for(int i = first_operator_number; i < operators.size(); ++i) {
        const dynamic_quantum_operator product = op * operators[i];
        const int product_minimum_weight = min(minimum_weight,operators[i].weight());
        if(product.weight() < product_minimum_weight) return false;
        if(not checkAllProducts(operators,product,product_minimum_weight,i+1)) return false;
    }
    return true;
}
//@+node:gcross.20101121162317.1583: *5* validateWeights
void validateWeights(int number_of_qubits,BoolVarArray& non_trivial,IntVarArray& weights) {
    int number_of_operators = non_trivial.size() / number_of_qubits;
    BoolMatrix non_trivial_matrix(non_trivial,number_of_qubits,number_of_operators);
    for(int i = 0; i < number_of_operators; ++i) {
        int correct_weight = 0;
        for(int j = 0; j < number_of_qubits; ++j) correct_weight += non_trivial_matrix(j,i).val();
        assertEqual(correct_weight,weights[i].val());
    }
}
//@+node:gcross.20101121200631.1646: *5* runCorrectNumberOfProductsTest
void runCorrectNumberOfProductsTest(int number_of_operators, int number_of_qubits, int correct_number_of_products) {
    MinimalWeightOperatorSpace* m = new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits);
    assertEqual(correct_number_of_products,m->number_of_products);
    delete m;
}
//@+node:gcross.20101121135345.1493: *5* runDerivedFieldsTest
void runDerivedFieldsTest(int number_of_operators, int number_of_qubits) {
    MinimalWeightOperatorSpace* m = new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits);
    DFS<MinimalWeightOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        validateNonTrivial(m->products_X,m->products_Z,m->products_non_trivial);
        validateWeights(number_of_qubits,m->products_non_trivial,m->products_weights);
        delete m;
    }
}
//@+node:gcross.20101121200631.1644: *5* runWeightTest
void runWeightTest(int number_of_operators, int number_of_qubits) {
    MinimalWeightOperatorSpace* m = new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits);
    DFS<MinimalWeightOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        for(int i = 0; i < number_of_operators; ++i) {
            assertTrue(checkAllProducts(operators,operators[i],operators[i].weight(),i+1));
        }
        delete m;
    }
}
//@+node:gcross.20101122101448.1538: *5* runCorrectNumberOfSolutionsTest
void runCorrectNumberOfSolutionsTest(int number_of_operators, int number_of_qubits) {
    int correct_number_of_solutions = 0;
    {
        OperatorSpace* m = new OperatorSpace(number_of_operators,number_of_qubits);
        DFS<OperatorSpace> e(m);
        delete m;
        for(m = e.next(); m != NULL; m = e.next()) {
            vector<dynamic_quantum_operator> operators = m->getOperators();
            bool is_minimal_weight_solution = true;
            for(int i = 0; i < number_of_operators; ++i) {
                if(not checkAllProducts(operators,operators[i],operators[i].weight(),i+1)) {
                    is_minimal_weight_solution = false;
                    break;
                }
            }
            if(is_minimal_weight_solution) ++correct_number_of_solutions;
            delete m;
        }
    }
    int number_of_solutions = 0;
    {
        MinimalWeightOperatorSpace* m = new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits);
        DFS<MinimalWeightOperatorSpace> e(m);
        delete m;
        for(m = e.next(); m != NULL; m = e.next()) {
            ++number_of_solutions;
            delete m;
        }
    }
    assertEqual(correct_number_of_solutions,number_of_solutions);
}
//@+node:gcross.20101121135345.1487: *4* 2x1
subSuite(_2x1) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(2,1); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(2,1,1); }
    testCase(minimal_weight) { runWeightTest(2,1); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(2,1); }

}
//@+node:gcross.20101121135345.1498: *4* 2x2
subSuite(_2x2) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(2,2); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(2,2,1); }
    testCase(minimal_weight) { runWeightTest(2,2); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(2,2); }

}
//@+node:gcross.20101121135345.1500: *4* 2x3
subSuite(_2x3) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(2,3); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(2,3,1); }
    testCase(minimal_weight) { runWeightTest(2,3); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(2,3); }

}
//@+node:gcross.20101121135345.1504: *4* 3x1
subSuite(_3x1) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(3,1); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(3,1,2*1+2); }
    testCase(minimal_weight) { runWeightTest(3,1); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(3,1); }

}
//@+node:gcross.20101121135345.1506: *4* 3x2
subSuite(_3x2) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(3,2); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(3,2,2*1+2); }
    testCase(minimal_weight) { runWeightTest(3,2); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(3,2); }

}
//@+node:gcross.20101121135345.1502: *4* 3x3
subSuite(_3x3) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(3,3); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(3,3,2*1+2); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(3,3); }

}
//@+node:gcross.20101121135345.1508: *4* 4x1
subSuite(_4x1) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(4,1); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(4,1,2); }
    testCase(minimal_weight) { runWeightTest(4,1); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(4,1); }

}
//@+node:gcross.20101121135345.1510: *4* 4x2
subSuite(_4x2) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(4,2); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(4,2,2+3*3); }
    testCase(minimal_weight) { runWeightTest(4,2); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(4,2); }

}
//@+node:gcross.20101121135345.1512: *4* 5x1
subSuite(_5x1) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(5,1); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(5,1,2*2+4); }
    testCase(minimal_weight) { runWeightTest(5,1); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(5,1); }

}
//@+node:gcross.20101121200631.4183: *4* 5x2
//@+at
// subSuite(_5x2) {
// 
//     testCase(correct_derived_fields) { runDerivedFieldsTest(5,2); }
//     testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(5,2,(2+3*3)*2+5); }
//     testCase(minimal_weight) { runWeightTest(5,2); }
// 
// }
//@+node:gcross.20101121162317.1476: *4* 6x1
subSuite(_6x1) {

    testCase(correct_derived_fields) { runDerivedFieldsTest(6,1); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(6,1,3); }
    testCase(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(6,1); }

}
//@+node:gcross.20101121200631.1648: *4* 6x2
subSuite(_6x2) {

    //testCase(correct_derived_fields) { runDerivedFieldsTest(6,2); }
    testCase(correct_number_of_products) { runCorrectNumberOfProductsTest(6,2,3+3*3*3); }
    //testCase(minimal_weight) { runWeightTest(6,2); }

}
//@-others

}
//@+node:gcross.20101122154804.1499: *3* NonTrivialWeight
subSuite(NonTrivialWeight) {

void runNonTrivialWeightTest(int number_of_operators,int number_of_qubits,int correct_number_of_solutions) {
    OperatorSpace* m = new OperatorSpace(number_of_operators,number_of_qubits);
    postNonTrivialWeightConstraints(*m);
    DFS<OperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        for(int i = 0; i < number_of_operators; ++i) assertTrue(m->weights[i].val() >= 1);
        if(number_of_operators % 2 == 1) assertTrue(m->weights[number_of_operators-1].val() >= 2);
        delete m;
        ++number_of_solutions;
    }
    if(correct_number_of_solutions >= 0) assertEqual(correct_number_of_solutions,number_of_solutions);
}

testCase(_1x1) { runNonTrivialWeightTest(1,1,0); }
testCase(_1x2) { runNonTrivialWeightTest(1,2,9); }
testCase(_2x1) { runNonTrivialWeightTest(2,1,9); }
testCase(_2x2) { runNonTrivialWeightTest(2,2,15*15); }
testCase(_3x1) { runNonTrivialWeightTest(3,1,0); }
testCase(_3x2) { runNonTrivialWeightTest(3,2,15*15*(16-3-3-1)); }
testCase(_4x1) { runNonTrivialWeightTest(4,1,81); }

}
//@+node:gcross.20101122154804.1515: *3* Commutator
subSuite(Commutator) {

//@+others
//@+node:gcross.20101123222425.1533: *4* correct counts
subSuite(correct_counts) {

void runCountTest(int number_of_operators,int number_of_qubits) {
    CommutatorOperatorSpace* m = new CommutatorOperatorSpace(number_of_operators,number_of_qubits);
    DFS<CommutatorOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        BoolMatrix anti_commutator_matrix = m->getAntiCommutatorMatrix();
        IntMatrix anti_commuting_qubit_counts_minus_hidden_qubits_matrix = m->getAntiCommutingQubitCountsMinusHiddenQubitsMatrix(),
                  anti_commuting_qubit_counts_matrix = m->getAntiCommutingQubitCountsMatrix();
        for(int i = 0; i < number_of_operators; ++i) {
            for(int j = 0; j < number_of_operators; ++j) {
                int count = 0;
                for(int k = 0; k < number_of_qubits+number_of_operators/2; ++k) {
                    if((operators[i].X[k] && operators[j].Z[k]) ^ (operators[i].Z[k] && operators[j].X[k])) ++count;
                }
                assertEqual(count,anti_commuting_qubit_counts_matrix(i,j).val());
                assertEqual(i != j && i/2 == j/2 ? count-1 : count,anti_commuting_qubit_counts_minus_hidden_qubits_matrix(i,j).val());
            }
        }
        delete m;
    }
}

testCase(_1x1) { runCountTest(1,1); }
testCase(_1x2) { runCountTest(1,2); }
testCase(_2x1) { runCountTest(2,1); }
testCase(_2x2) { runCountTest(2,2); }
testCase(_3x1) { runCountTest(3,1); }
testCase(_3x2) { runCountTest(3,2); }
testCase(_4x1) { runCountTest(4,1); }

}
//@+node:gcross.20101123222425.1534: *4* correct commutators
subSuite(correct_commutators) {

void runCommutatorTest(int number_of_operators,int number_of_qubits) {
    CommutatorOperatorSpace* m = new CommutatorOperatorSpace(number_of_operators,number_of_qubits);
    DFS<CommutatorOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        BoolMatrix anti_commutator_matrix = m->getAntiCommutatorMatrix();
        for(int i = 0; i < number_of_operators; ++i) {
            for(int j = 0; j < number_of_operators; ++j) {
                assertTrue((operators[i]&&operators[j]) == (anti_commutator_matrix(i,j).val() == 1));
            }
        }
        delete m;
    }
}

testCase(_1x1) { runCommutatorTest(1,1); }
testCase(_1x2) { runCommutatorTest(1,2); }
testCase(_2x1) { runCommutatorTest(2,1); }
testCase(_2x2) { runCommutatorTest(2,2); }
testCase(_3x1) { runCommutatorTest(3,1); }
testCase(_3x2) { runCommutatorTest(3,2); }
testCase(_4x1) { runCommutatorTest(4,1); }

}
//@-others

}
//@-others

}
//@-others
//@-leo
