//@+leo-ver=5-thin
//@+node:gcross.20101122101448.1534: * @thin print-solutions.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101122101448.1535: ** << Includes >>
#include <boost/foreach.hpp>
#include <iostream>
#include <cstdlib>

#include "constraints.hh"
#include "operator_space.hh"

using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101122101448.1536: ** main
int main(int argc, char** argv) {
    if(argc < 3) {
        cout << "Usage: count-solutions <# of qubits> <# of operators>" << endl;
        return 1;
    }
    int number_of_qubits = atoi(argv[1]),
        number_of_operators = atoi(argv[2]);
    OperatorSpace* m = constructConstrainedOperatorSpace(number_of_qubits,number_of_operators);
    DFS<OperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        vector<dynamic_quantum_operator> operators = m->getOperators();
        BOOST_FOREACH(dynamic_quantum_operator& op, operators) { cout << op << endl; }
        cout << endl;
        delete m;
    }
}
//@-others
//@-leo
