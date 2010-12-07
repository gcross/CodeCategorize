//@+leo-ver=5-thin
//@+node:gcross.20101128173348.1788: * @thin pauli_groups.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128173348.1789: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <illuminate.hpp>

#include "constraints/row_ordered/pauli_groups.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128173348.1790: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(RowOrdered) { TEST_SUITE(PauliGroups) {

void runTest(int number_of_operators, int number_of_qubits) {
    PauliGroupsRowOrderedOperatorSpace* m = new PauliGroupsRowOrderedOperatorSpace(number_of_operators,number_of_qubits);
    branch(*m,m->pauli_orderings,INT_VAR_NONE,INT_VAL_SPLIT_MIN);
    DFS<PauliGroupsRowOrderedOperatorSpace> e(m);
    delete m;
    int number_of_solutions = 0;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix(),
                  unsorted_orderings_matrix(m->unsorted_orderings,number_of_operators,number_of_qubits),
                  pauli_orderings_matrix(m->pauli_orderings,4,number_of_qubits);
        for(int i = 0; i < number_of_qubits; ++i) {
            int counts[3] = {0,0,0};
            for(int j = 0; j < number_of_operators; ++j) {
                if(O_matrix(i,j).val() > 0) ++counts[O_matrix(i,j).val()-1];
            }
            for(int j = 0; j < 3; ++j) {
                for(int k = 0; k < 3; ++k) {
                    #define tryRelation(_CMP_) \
                        if(counts[j] _CMP_  counts[k]) \
                            ASSERT_TRUE(pauli_orderings_matrix(j+1,i).val() _CMP_ pauli_orderings_matrix(k+1,i).val());
                    tryRelation(<);
                    tryRelation(==);
                    tryRelation(>);
                }
                ASSERT_TRUE(pauli_orderings_matrix(j+1,i).val() > pauli_orderings_matrix(0,i).val());
            }
            for(int j = 0; j < number_of_operators; ++j) {
                ASSERT_EQ(pauli_orderings_matrix(O_matrix(i,j).val(),i).val(),unsorted_orderings_matrix(j,i).val());
            }
        }
        delete m;
        ++number_of_solutions;
    }
    ASSERT_TRUE(number_of_solutions > 0);
}

TEST_CASE(_1x1) { runTest(1,1); }
TEST_CASE(_1x2) { runTest(1,2); }
TEST_CASE(_1x3) { runTest(1,3); }
TEST_CASE(_2x1) { runTest(2,1); }
TEST_CASE(_2x2) { runTest(2,2); }
TEST_CASE(_2x3) { runTest(2,3); }
TEST_CASE(_3x1) { runTest(3,1); }
TEST_CASE(_3x2) { runTest(3,2); }
TEST_CASE(_4x1) { runTest(4,1); }
TEST_CASE(_4x2) { runTest(4,2); }
TEST_CASE(_5x1) { runTest(5,1); }
TEST_CASE(_5x2) { runTest(5,2); }
TEST_CASE(_6x1) { runTest(6,1); }

} } }
//@-others
//@-leo
