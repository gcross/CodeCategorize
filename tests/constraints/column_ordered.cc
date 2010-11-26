//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4141: * @thin column_ordered.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.4142: ** << Includes >>
#include <unit--.hpp>

#include "constraints/column_ordered.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101118114009.1454: ** Tests
testSuite(Constraints) { subSuite(ColumnOrdered) {

//@+others
//@+node:gcross.20101118114009.1455: *3* _1x1
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
//@+node:gcross.20101118114009.1461: *3* _1x2
testCase(_1x2) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(1,2);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(16,number_of_solutions);
}
//@+node:gcross.20101118114009.1463: *3* _1x3
testCase(_1x3) {
    int number_of_solutions = 0;
    {
        ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(1,3);
        DFS<ColumnOrderedOperatorSpace> e(m);
        delete m;
        for(m = e.next(); m != NULL; m = e.next()) {
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
            if(m->O[1].val() >= m->O[2].val()) ++correct_number_of_solutions;
            delete m;
        }
    }
    assertEqual(correct_number_of_solutions,number_of_solutions);
}
//@+node:gcross.20101118114009.1467: *3* _2x1
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
//@+node:gcross.20101118114009.1473: *3* _2x2
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
//@+node:gcross.20101118114009.1475: *3* _2x3
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
//@+node:gcross.20101118114009.1469: *3* _3x1
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
//@+node:gcross.20101118114009.1477: *3* _3x2
testCase(_3x2) {
    ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(3,2);
    DFS<ColumnOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        ++number_of_solutions;
        delete m;
    }
    assertEqual(4*4*4*4*4*4,number_of_solutions);
}
//@+node:gcross.20101118114009.1479: *3* _3x3
testCase(_3x3) {
    int number_of_solutions = 0;
    {
        ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(3,3);
        DFS<ColumnOrderedOperatorSpace> e(m);
        delete m;
        for(m = e.next(); m != NULL; m = e.next()) {
            IntMatrix O_matrix = m->getOMatrix();
            assertTrue(O_matrix(1,0).val() >= O_matrix(2,0).val());
            assertTrue(
                    O_matrix(1,0).val() >  O_matrix(2,0).val()
              ||    O_matrix(1,0).val() == O_matrix(2,0).val()
                 && O_matrix(1,1).val() >  O_matrix(2,1).val()
              ||    O_matrix(1,0).val() == O_matrix(2,0).val()
                 && O_matrix(1,1).val() == O_matrix(2,1).val()
                 && O_matrix(1,2).val() >= O_matrix(2,2).val()
            );
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
            if( not (
                    O_matrix(1,0).val() >  O_matrix(2,0).val()
              ||    O_matrix(1,0).val() == O_matrix(2,0).val()
                 && O_matrix(1,1).val() >  O_matrix(2,1).val()
              ||    O_matrix(1,0).val() == O_matrix(2,0).val()
                 && O_matrix(1,1).val() == O_matrix(2,1).val()
                 && O_matrix(1,2).val() >= O_matrix(2,2).val()
            )) goto skip;
            ++correct_number_of_solutions;
            skip:
            delete m;
        }
    }
    assertEqual(correct_number_of_solutions,number_of_solutions);
}
//@+node:gcross.20101123222425.4276: *3* _4x2
testCase(_4x2) {
    int number_of_solutions = 0;
    {
        ColumnOrderedOperatorSpace* m = new ColumnOrderedOperatorSpace(4,2);
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
                 && O_matrix(0,2).val() >  O_matrix(1,2).val()
              ||    O_matrix(0,0).val() == O_matrix(1,0).val()
                 && O_matrix(0,1).val() == O_matrix(1,1).val()
                 && O_matrix(0,2).val() == O_matrix(1,2).val()
                 && O_matrix(0,3).val() >= O_matrix(1,3).val()
            );
            ++number_of_solutions;
            delete m;
        }
    }
    int correct_number_of_solutions = 0;
    {
        OperatorSpace* m = new OperatorSpace(4,2);
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
                 && O_matrix(0,2).val() >  O_matrix(1,2).val()
              ||    O_matrix(0,0).val() == O_matrix(1,0).val()
                 && O_matrix(0,1).val() == O_matrix(1,1).val()
                 && O_matrix(0,2).val() == O_matrix(1,2).val()
                 && O_matrix(0,3).val() >= O_matrix(1,3).val()
            ) ++correct_number_of_solutions;
            delete m;
        }
    }
    assertEqual(correct_number_of_solutions,number_of_solutions);
}
//@-others

} }
//@-others
//@-leo
