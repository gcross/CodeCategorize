//@+leo-ver=5-thin
//@+node:gcross.20101118114009.1514: * @thin count-all-solutions.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101118114009.1515: ** << Includes >>
#include <iostream>
#include <cstdlib>

#include "constrained_operator_space.hh"
#include "utilities.hh"

using namespace CodeCategorize;
using namespace Gecode;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101118114009.1516: ** main
int main(int argc, char** argv) {
    if(argc < 2 || argc > 3) {
        cout << "Usage: count-all-solutions <# of qubits> [maximum weight]" << endl;
        return 1;
    }
    int number_of_qubits = atoi(argv[1]);
    optional<int> maximum_weight;
    if(argc == 3) maximum_weight = atoi(argv[2]);
    Search::Options options = Search::Options::def;
    options.threads = 0;
    for(int number_of_operators = 3; number_of_operators < 2*number_of_qubits-1; ++number_of_operators) {
        cout << number_of_operators << ": " << countSolutions(constructConstrainedOperatorSpace(number_of_qubits,number_of_operators,maximum_weight),options) << endl;
    }
}
//@-others
//@-leo
