//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4013: * @thin commutator.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.4014: ** << Includes >>
#include <illuminate.hpp>
#include <vector>

#include "commutator.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101123222425.4080: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(Commutator) {

//@+others
//@+node:gcross.20101123222425.4081: *3* correct counts
TEST_SUITE(correct_counts) {

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
                ASSERT_EQ(count,anti_commuting_qubit_counts_matrix(i,j).val());
                ASSERT_EQ(i != j && i/2 == j/2 ? count-1 : count,anti_commuting_qubit_counts_minus_hidden_qubits_matrix(i,j).val());
            }
        }
        delete m;
    }
}

TEST_CASE(_1x1) { runCountTest(1,1); }
TEST_CASE(_1x2) { runCountTest(1,2); }
TEST_CASE(_2x1) { runCountTest(2,1); }
TEST_CASE(_2x2) { runCountTest(2,2); }
TEST_CASE(_3x1) { runCountTest(3,1); }
TEST_CASE(_3x2) { runCountTest(3,2); }
TEST_CASE(_4x1) { runCountTest(4,1); }

}
//@+node:gcross.20101123222425.4082: *3* correct commutators
TEST_SUITE(correct_commutators) {

void runCommutatorTest(int number_of_operators,int number_of_qubits) {
    CommutatorOperatorSpace* m = new CommutatorOperatorSpace(number_of_operators,number_of_qubits);
    DFS<CommutatorOperatorSpace> e(m);
    CommutatorOperatorSpace* original_m = m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        BoolMatrix anti_commutator_qubit_matrix = m->getAntiCommutingQubitsMatrix();
        for(int i = 0; i < number_of_operators; ++i) {
            dynamic_quantum_operator op1 = operators[i];
            for(int j = i+1; j < number_of_operators; ++j) {
                dynamic_quantum_operator op2 = operators[j];
                ASSERT_TRUE(original_m->commutator_matrix(i,j) == original_m->commutator_matrix(j,i));
                const int commutator_number = original_m->commutator_matrix(i,j);
                for(int k = 0; k < number_of_qubits; ++k) {
                    const int q = k+m->number_of_pairs;
                    ASSERT_EQ((op1.X[q]&&op2.Z[q])^(op1.Z[q]&&op2.X[q]),anti_commutator_qubit_matrix(k,commutator_number).val());
                }
            }
        }
        delete m;
    }
}

TEST_CASE(_1x1) { runCommutatorTest(1,1); }
TEST_CASE(_1x2) { runCommutatorTest(1,2); }
TEST_CASE(_2x1) { runCommutatorTest(2,1); }
TEST_CASE(_2x2) { runCommutatorTest(2,2); }
TEST_CASE(_3x1) { runCommutatorTest(3,1); }
TEST_CASE(_3x2) { runCommutatorTest(3,2); }
TEST_CASE(_4x1) { runCommutatorTest(4,1); }

}
//@+node:gcross.20101126220444.1733: *3* correct commutator matrix
TEST_SUITE(correct_commutator_matrix) {

void runCommutatorTest(int number_of_operators,int number_of_qubits) {
    CommutatorOperatorSpace* m = new CommutatorOperatorSpace(number_of_operators,number_of_qubits);
    DFS<CommutatorOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        BoolMatrix anti_commutator_matrix = m->getAntiCommutatorMatrix();
        for(int i = 0; i < number_of_operators; ++i) {
            for(int j = 0; j < number_of_operators; ++j) {
                ASSERT_TRUE((operators[i]&&operators[j]) == (anti_commutator_matrix(i,j).val() == 1));
            }
        }
        delete m;
    }
}

TEST_CASE(_1x1) { runCommutatorTest(1,1); }
TEST_CASE(_1x2) { runCommutatorTest(1,2); }
TEST_CASE(_2x1) { runCommutatorTest(2,1); }
TEST_CASE(_2x2) { runCommutatorTest(2,2); }
TEST_CASE(_3x1) { runCommutatorTest(3,1); }
TEST_CASE(_3x2) { runCommutatorTest(3,2); }
TEST_CASE(_4x1) { runCommutatorTest(4,1); }

}
//@-others

} }
//@-others
//@-leo
