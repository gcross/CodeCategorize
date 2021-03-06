//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4207: * @thin special_case_XZ.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.4208: ** << Includes >>
#include <illuminate.hpp>

#include "constraints/special_case_XZ.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101123222425.4232: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(SpecialCaseXZ) {

void runTest(int number_of_operators,int number_of_qubits) {
    const int first_column = number_of_operators % 2;
    SpecialCaseXZConstrainedOperatorSpace* m = new SpecialCaseXZConstrainedOperatorSpace(number_of_operators,number_of_qubits);
    DFS<SpecialCaseXZConstrainedOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        IntMatrix O_matrix = m->getOMatrix();
        int first_X = -1, first_Z = -1, index = 0;
        for(int i = first_column; i < number_of_qubits; ++i) {
            if(O_matrix(i,0).val() != 1) goto skip;
            if(O_matrix(i,1).val() != 2) goto skip;
        }
        for(int i = first_column; i < number_of_qubits; ++i) {
            for(int j = 2; j < number_of_operators; ++j, ++index) {
                if(first_X == -1 && O_matrix(i,j).val() == 1) first_X = index;
                if(first_Z == -1 && O_matrix(i,j).val() == 2) first_Z = index;
            }
        }
        ASSERT_TRUE(first_Z == -1 || first_X != -1 && first_X < first_Z);
        skip:
        delete m;
    }
}

TEST_CASE(_2x1) { runTest(2,1); }
TEST_CASE(_2x2) { runTest(2,2); }
TEST_CASE(_2x3) { runTest(2,3); }
TEST_CASE(_3x1) { runTest(3,1); }
TEST_CASE(_3x2) { runTest(3,2); }
TEST_CASE(_3x3) { runTest(3,3); }
TEST_CASE(_4x1) { runTest(4,1); }
TEST_CASE(_4x2) { runTest(4,2); }

} }
//@-others
//@-leo
