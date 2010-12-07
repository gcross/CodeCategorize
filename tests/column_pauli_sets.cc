//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4468: * @thin column_pauli_sets.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.4469: ** << Includes >>
#include <illuminate.hpp>

#include "column_pauli_sets.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101123222425.4491: ** Tests
TEST_SUITE(ColumnPauliSets) {

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
                    ASSERT_TRUE(m->X_bit_sets[i].contains(j));
                } else {
                    ASSERT_TRUE(m->X_bit_sets[i].notContains(j));
                }
                if(Z_matrix(i,j).val()) {
                    ASSERT_TRUE(m->Z_bit_sets[i].contains(j));
                } else {
                    ASSERT_TRUE(m->Z_bit_sets[i].notContains(j));
                }
                if(O_matrix(i,j).val() == 0) {
                    ASSERT_TRUE(m->I_sets[i].contains(j));
                    ASSERT_TRUE(m->non_trivial_sets[i].notContains(j));
                } else {
                    ASSERT_TRUE(m->I_sets[i].notContains(j));
                    ASSERT_TRUE(m->non_trivial_sets[i].contains(j));
                }
                if(O_matrix(i,j).val() == 1) {
                    ASSERT_TRUE(m->X_sets[i].contains(j));
                } else {
                    ASSERT_TRUE(m->X_sets[i].notContains(j));
                }
                if(O_matrix(i,j).val() == 2) {
                    ASSERT_TRUE(m->Z_sets[i].contains(j));
                } else {
                    ASSERT_TRUE(m->Z_sets[i].notContains(j));
                }
                if(O_matrix(i,j).val() == 3) {
                    ASSERT_TRUE(m->Y_sets[i].contains(j));
                } else {
                    ASSERT_TRUE(m->Y_sets[i].notContains(j));
                }
            }
        }
        delete m;
    }
}

TEST_CASE(_1x1) { runTests(1,1); }
TEST_CASE(_1x2) { runTests(1,2); }
TEST_CASE(_1x3) { runTests(1,3); }
TEST_CASE(_2x1) { runTests(2,1); }
TEST_CASE(_2x2) { runTests(2,2); }
TEST_CASE(_2x3) { runTests(2,3); }
TEST_CASE(_3x1) { runTests(3,1); }
TEST_CASE(_3x2) { runTests(3,2); }
TEST_CASE(_4x1) { runTests(4,1); }

}
//@-others
//@-leo
