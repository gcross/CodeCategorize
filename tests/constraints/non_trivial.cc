//@+leo-ver=5-thin
//@+node:gcross.20101129164055.1905: * @thin non_trivial.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101129164055.1906: ** << Includes >>
#include <unit--.hpp>

#include "constraints/non_trivial.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101129164055.1920: ** Tests
testSuite(Constraints) { subSuite(NonTrivialWeight) {

void runNonTrivialWeightTest(int number_of_operators,int number_of_qubits,int correct_number_of_solutions) {
    NonTrivialOperatorSpace* m = new NonTrivialOperatorSpace(number_of_operators,number_of_qubits);
    DFS<NonTrivialOperatorSpace> e(m);
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

} }
//@-others
//@-leo
