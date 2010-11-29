//@+leo-ver=5-thin
//@+node:gcross.20101128153132.1842: * @thin anti_commutator_last_operator_sequence.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128153132.1843: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <unit--.hpp>

#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128153132.1844: ** Tests
testSuite(Constraints) { subSuite(RowOrdered) { subSuite(AntiCommutatorLastOperatorSequence) {

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

} } }
//@-others
//@-leo
