//@+leo-ver=5-thin
//@+node:gcross.20101122101448.1534: * @thin print-solutions.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101122101448.1535: ** << Includes >>
#include <boost/foreach.hpp>
#include <iostream>
#include <cstdlib>

#include "constrained_operator_space.hh"
#include "solution_iterator.hh"

using namespace CodeCategorize;
using namespace Gecode;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101122101448.1536: ** main
int main(int argc, char** argv) {
    if(argc < 3 || argc > 4) {
        cout << "Usage: print-solutions <# of qubits> <# of operators> [maximum weight]" << endl;
        return 1;
    }
    int number_of_qubits = atoi(argv[1]),
        number_of_operators = atoi(argv[2]);
    optional<int> maximum_weight;
    if(argc == 4) maximum_weight = atoi(argv[3]);
    for(SolutionIterator<> solution(constructConstrainedOperatorSpace(number_of_qubits,number_of_operators,maximum_weight));
        solution;
        ++solution
    ) {
        cout << "-";
        BOOST_FOREACH(const dynamic_quantum_operator& op, *solution) { cout << " - " << op << endl;  cout << " "; }
        cout << endl;
    }
}
//@-others
//@-leo
