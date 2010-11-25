//@+leo-ver=5-thin
//@+node:gcross.20101117113704.1319: * @thin constraints.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117113704.1322: ** << Includes >>
#include "constraints.hh"

using namespace std;
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101117133000.1469: ** Functions
//@+node:gcross.20101117133000.1470: *3* postFirstColumnSpecialCaseConstraint
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m) {
    rel(m,m.getOMatrix()(0,m.number_of_operators-1) == Z);
    BoolMatrix Z_matrix = m.getZMatrix();
    for(int row = 0; row < m.number_of_operators-1; ++row) rel(m,Z_matrix(0,row) == 0);
}
//@+node:gcross.20101117133000.1622: *3* postColumnXZYOrderingConstraints
void postColumnXZYOrderingConstraints(OperatorSpace& m) {
    static DFA::Transition t[] =
        {{0,0,0}
        ,{0,1,1}
        ,{1,0,1}
        ,{1,1,1}
        ,{1,2,2}
        ,{2,0,2}
        ,{2,1,2}
        ,{2,2,2}
        ,{2,3,3}
        ,{3,0,3}
        ,{3,1,3}
        ,{3,2,3}
        ,{3,3,3}
        ,{-1,-1,-1}
        };
    static int f[] = {2,3,-1};
    static DFA d(0,t,f);

    IntMatrix O_matrix = m.getOMatrix();
    for(int i = 0; i < m.number_of_qubits; ++i) extensional(m,O_matrix.col(i),d);
}
//@+node:gcross.20101122154804.1498: *3* postNonTrivialWeightConstraints
void postNonTrivialWeightConstraints(OperatorSpace& m) {
    rel(m,m.weights,IRT_GR,0);
    if(m.number_of_operators % 2 == 1) rel(m,m.weights[m.number_of_operators-1],IRT_GR,1);
}
//@-others

}
//@-leo
