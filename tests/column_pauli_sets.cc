//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4468: * @thin column_pauli_sets.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.4469: ** << Includes >>
#include <unit--.hpp>

#include "column_pauli_sets.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101123222425.4491: ** Tests
testSuite(ColumnPauliSets) {

void runTests(int number_of_operators, int number_of_qubits) {
    ColumnPauliSetsOperatorSpace* m = new ColumnPauliSetsOperatorSpace(number_of_operators,number_of_qubits);
    DFS<ColumnPauliSetsOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        BoolMatrix X_matrix = m->getXMatrix(),
                   Z_matrix = m->getZMatrix(),
                   non_trivial_matrix = m->getNonTrivialMatrix();
        IntMatrix  O_matrix = m->getOMatrix();
        for(int i = 0; i < number_of_qubits; ++i) {
            for(int j = 0; j < number_of_operators; ++j) {
                if(X_matrix(i,j).val()) {
                    assertTrue(m->X_bit_sets[i].contains(j));
                } else {
                    assertTrue(m->X_bit_sets[i].notContains(j));
                }
                if(Z_matrix(i,j).val()) {
                    assertTrue(m->Z_bit_sets[i].contains(j));
                } else {
                    assertTrue(m->Z_bit_sets[i].notContains(j));
                }
                if(O_matrix(i,j).val() == 0) {
                    assertTrue(m->I_sets[i].contains(j));
                    assertTrue(m->non_trivial_sets[i].notContains(j));
                } else {
                    assertTrue(m->I_sets[i].notContains(j));
                    assertTrue(m->non_trivial_sets[i].contains(j));
                }
                if(O_matrix(i,j).val() == 1) {
                    assertTrue(m->X_sets[i].contains(j));
                } else {
                    assertTrue(m->X_sets[i].notContains(j));
                }
                if(O_matrix(i,j).val() == 2) {
                    assertTrue(m->Z_sets[i].contains(j));
                } else {
                    assertTrue(m->Z_sets[i].notContains(j));
                }
                if(O_matrix(i,j).val() == 3) {
                    assertTrue(m->Y_sets[i].contains(j));
                } else {
                    assertTrue(m->Y_sets[i].notContains(j));
                }
            }
        }
        delete m;
    }
}

testCase(_1x1) { runTests(1,1); }
testCase(_1x2) { runTests(1,2); }
testCase(_1x3) { runTests(1,3); }
testCase(_2x1) { runTests(2,1); }
testCase(_2x2) { runTests(2,2); }
testCase(_2x3) { runTests(2,3); }
testCase(_3x1) { runTests(3,1); }
testCase(_3x2) { runTests(3,2); }
testCase(_4x1) { runTests(4,1); }

}
//@-others
//@-leo
