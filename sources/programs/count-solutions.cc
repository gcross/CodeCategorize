//@+leo-ver=5-thin
//@+node:gcross.20101118114009.1507: * @thin count-solutions.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101118114009.1508: ** << Includes >>
#include <iostream>
#include <cstdlib>

#include "constrained_operator_space.hh"
#include "utilities.hh"

using namespace CodeCategorize;
using namespace Gecode;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101118114009.1510: ** main
int main(int argc, char** argv) {
    if(argc < 3 || argc > 4) {
        cout << "Usage: count-solutions <# of qubits> <# of operators> [maximum weight]" << endl;
        return 1;
    }
    int number_of_qubits = atoi(argv[1]),
        number_of_operators = atoi(argv[2]);
    optional<int> maximum_weight;
    if(argc == 4) maximum_weight = atoi(argv[3]);
    cout << countSolutions(constructConstrainedOperatorSpace(number_of_qubits,number_of_operators,maximum_weight)) << endl;
}
//@-others
//@-leo
