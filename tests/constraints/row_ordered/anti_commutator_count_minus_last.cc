//@+leo-ver=5-thin
//@+node:gcross.20101128153132.1836: * @thin anti_commutator_count_minus_last.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128153132.1837: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <illuminate.hpp>

#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128153132.1838: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(RowOrdered) { TEST_SUITE(AntiCommutatorCountMinusLast) {

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
            ASSERT_EQ(number_of_anti_commuting_operators,m->number_of_anti_commuting_operators[i].val());
        }
        delete m;
    }
}

TEST_CASE(_2x1) { runCountTest(2,1); }
TEST_CASE(_2x2) { runCountTest(2,2); }
TEST_CASE(_3x1) { runCountTest(3,1); }
TEST_CASE(_3x2) { runCountTest(3,2); }
TEST_CASE(_4x1) { runCountTest(4,1); }
TEST_CASE(_4x2) { runCountTest(4,2); }

} } }
//@-others
//@-leo
