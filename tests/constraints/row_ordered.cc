//@+leo-ver=5-thin
//@+node:gcross.20101117133000.1340: * @thin row_ordered.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117133000.1341: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <unit--.hpp>

#include "constraints/row_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/pauli_groups.hh"
#include "constraints/row_ordered/weight.hh"
#include "constraints/row_ordered/weight_and_first_column.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101117133000.1531: ** Tests
testSuite(Constraints) { subSuite(RowOrdered) {

//@+others
//@+node:gcross.20101123173026.1543: *3* AntiCommutatorCount
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
//@+node:gcross.20101123222425.4360: *3* AntiCommutatorCountMinusLast
subSuite(AntiCommutatorCountMinusLast) {

void runCountTest(int number_of_operators, int number_of_qubits) {
    AntiCommutatorCountMinusLastOrderedOperatorSpace* m = new AntiCommutatorCountMinusLastOrderedOperatorSpace(number_of_operators,number_of_qubits);
    DFS<AntiCommutatorCountMinusLastOrderedOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        for(int i = 0; i < number_of_operators; ++i) {
            int number_of_anti_commuting_operators = 0;
            for(int j = 0; j < number_of_operators-1; ++j) {
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
//@+node:gcross.20101126220444.1731: *3* AntiCommutatorLastOperatorSequence
subSuite(AntiCommutatorLastOperatorSequence) {

void runCountTest(int number_of_operators, int number_of_qubits) {
    AntiCommutatorLastOperatorSequenceOrderedOperatorSpace* m = new AntiCommutatorLastOperatorSequenceOrderedOperatorSpace(number_of_operators,number_of_qubits);
    DFS<AntiCommutatorLastOperatorSequenceOrderedOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        dynamic_quantum_operator last_operator = operators[number_of_operators-1];
        //BOOST_FOREACH(dynamic_quantum_operator& op, operators) { cout << op << endl; } cout << endl;
        //cout << m->last_operator_anti_commuting_qubit_sequence << endl;
        IntMatrix matrix(m->last_operator_anti_commuting_qubit_sequence,number_of_qubits,number_of_operators);
        for(int i = 0; i < number_of_operators-1; ++i) {
            dynamic_quantum_operator op = operators[i];
            for(int j = 0; j < number_of_qubits; ++j) {
                const int q = j+m->number_of_pairs;
                assertEqual((op.X[q]&last_operator.Z[q])^(op.Z[q]&last_operator.X[q]),matrix(j,i).val());
            }
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
//@+node:gcross.20101117133000.1567: *3* FirstColumnX
subSuite(FirstColumnX) {

//@+others
//@+node:gcross.20101117133000.1568: *4* _1x1
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
//@+node:gcross.20101117133000.1569: *4* _1x2
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
//@+node:gcross.20101117133000.1570: *4* _2x1
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
//@+node:gcross.20101117133000.1571: *4* _2x2
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
//@+node:gcross.20101117133000.1572: *4* _4x2
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
//@+node:gcross.20101117133000.1573: *3* TieBraker: Weight, FirstColumnX
subSuite(Tie_breaking_between_Weight_and_FirstColumnX) {

//@+others
//@+node:gcross.20101117133000.1575: *4* _1x1
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
//@+node:gcross.20101117133000.1588: *4* _1x2
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
//@+node:gcross.20101117133000.1591: *4* _2x1
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
//@+node:gcross.20101117133000.1593: *4* _2x2
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
//@+node:gcross.20101117133000.1595: *4* _2x3
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
//@+node:gcross.20101117133000.1599: *4* _4x2
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
//@+node:gcross.20101126220444.1921: *3* PauliGroups
subSuite(PauliGroups) {

void runTest(int number_of_operators, int number_of_qubits) {
    PauliGroupsRowOrderedOperatorSpace* m = new PauliGroupsRowOrderedOperatorSpace(number_of_operators,number_of_qubits);
    DFS<PauliGroupsRowOrderedOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix(),
                  orderings_matrix(m->orderings,number_of_operators,number_of_qubits);
        for(int i = 0; i < number_of_qubits; ++i) {
            int counts[3] = {0,0,0};
            for(int j = 0; j < number_of_operators; ++j) {
                if(O_matrix(i,j).val() > 0) ++counts[O_matrix(i,j).val()-1];
            }
            int labels[4] = {4,-1,-1,-1};
            if(counts[0] >= counts[1] && counts[1] >= counts[2]) {
                labels[1] = 0; labels[2] = 1; labels[3] = 2;
            } else if(counts[0] >= counts[2] && counts[2] >= counts[1]) {
                labels[1] = 0; labels[3] = 1; labels[2] = 2;
            } else if(counts[1] >= counts[0] && counts[0] >= counts[2]) {
                labels[2] = 0; labels[1] = 1; labels[3] = 2;
            } else if(counts[1] >= counts[2] && counts[2] >= counts[0]) {
                labels[2] = 0; labels[3] = 1; labels[1] = 2;
            } else if(counts[2] >= counts[0] && counts[0] >= counts[1]) {
                labels[3] = 0; labels[1] = 1; labels[2] = 2;
            } else if(counts[2] >= counts[1] && counts[1] >= counts[0]) {
                labels[3] = 0; labels[2] = 1; labels[1] = 2;
            }
            for(int j = 0; j < number_of_operators; ++j) {
                assertEqual(labels[O_matrix(i,j).val()],orderings_matrix(j,i).val());
            }
        }
        delete m;
    }
}

testCase(_1x1) { runTest(1,1); }
testCase(_1x2) { runTest(1,2); }
testCase(_1x3) { runTest(1,3); }
testCase(_2x1) { runTest(2,1); }
testCase(_2x2) { runTest(2,2); }
testCase(_2x3) { runTest(2,3); }
testCase(_3x1) { runTest(3,1); }
testCase(_3x2) { runTest(3,2); }
testCase(_3x3) { runTest(3,3); }
testCase(_4x1) { runTest(4,1); }
testCase(_5x1) { runTest(5,1); }

}
//@+node:gcross.20101123222425.4260: *3* Weight
subSuite(Weight) {

//@+others
//@+node:gcross.20101123222425.4261: *4* _1x1
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
//@+node:gcross.20101123222425.4262: *4* _1x2
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
//@+node:gcross.20101123222425.4263: *4* _2x1
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
//@+node:gcross.20101123222425.4264: *4* _2x2
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
//@+node:gcross.20101123222425.4265: *4* _4x2
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
//@-others

} }
//@-others
//@-leo
