//@+leo-ver=5-thin
//@+node:gcross.20101129210852.1817: * @thin scan.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101129210852.1818: ** << Includes >>
#include <boost/foreach.hpp>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <codequest.hpp>

#include "constrained_operator_space.hh"
#include "operator_space.hh"

using namespace CodeCategorize;
using namespace Gecode;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101129210852.1820: ** fast_scan
template<int number_of_qubits> void fast_scan(int number_of_operators) {
    typedef static_quantum_operator<number_of_qubits> quantum_operator;
    typedef static_vector<quantum_operator,2*number_of_qubits> operator_vector;
    typedef qubit<quantum_operator> qubit_type;
    typedef static_vector<qubit_type,number_of_qubits> qubit_vector;
    typedef static_vector<size_t,2*number_of_qubits> index_vector;
    typedef qec<quantum_operator,qubit_vector,operator_vector,index_vector> qec_type;

    operator_vector operators;

    OperatorSpace* m = constructConstrainedOperatorSpace(number_of_qubits,number_of_operators);
    DFS<OperatorSpace> e(m);
    m->initializeOperators<quantum_operator,operator_vector>(operators);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        m->updateOperators<quantum_operator,operator_vector>(operators);
        delete m;
        qec_type code(operators);
        code.optimize_logical_qubits(false);
        for(typename index_vector::iterator iter = code.logical_qubit_error_distances.begin();
            iter != code.logical_qubit_error_distances.end();
            ++iter
        ) {
            if(*iter >= 3) {
                cout << "---" << endl;
                cout << "Operators:" << endl;
                BOOST_FOREACH(quantum_operator& op, operators) {
                    cout << "    - " << op << endl;
                }
                code.writeYAML(cout);
                cout.flush();
                break;
            }
        }
    }

}
//@+node:gcross.20101129210852.2670: ** slow_scan
void slow_scan(int number_of_qubits, int number_of_operators) {
    typedef dynamic_quantum_operator quantum_operator;
    typedef vector<quantum_operator> operator_vector;
    typedef qubit<quantum_operator> qubit_type;
    typedef vector<qubit_type> qubit_vector;
    typedef vector<size_t> index_vector;
    typedef qec<quantum_operator,qubit_vector,operator_vector,index_vector> qec_type;

    operator_vector operators;

    OperatorSpace* m = constructConstrainedOperatorSpace(number_of_qubits,number_of_operators);
    DFS<OperatorSpace> e(m);
    m->initializeOperators<quantum_operator,operator_vector>(operators);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        m->updateOperators<quantum_operator,operator_vector>(operators);
        delete m;
        qec_type code(operators);
        code.optimize_logical_qubits(false);
        for(index_vector::iterator iter = code.logical_qubit_error_distances.begin();
            iter != code.logical_qubit_error_distances.end();
            ++iter
        ) {
            if(*iter >= 3) {
                cout << "---" << endl;
                cout << "Operators:" << endl;
                BOOST_FOREACH(quantum_operator& op, operators) {
                    cout << "    - " << op << endl;
                }
                code.writeYAML(cout);
                cout.flush();
                break;
            }
        }
    }

}
//@+node:gcross.20101129210852.1819: ** main
int main(int argc, char** argv) {
    if(argc < 3) {
        cout << "Usage: scan <# of qubits> <# of operators>" << endl;
        return 1;
    }
    int number_of_qubits = atoi(argv[1]),
        number_of_operators = atoi(argv[2]);
    if(number_of_operators < 3) {
        cerr << "The number of operators must be three or greater." << endl;
        return -1;
    }
    if(number_of_operators >= 2*number_of_qubits-1) {
        cerr << "The number of operators must be less than two times the number of qubits minus one (# < " << (2*number_of_qubits-1) << ")." << endl;
        return -1;
    }
    switch(number_of_qubits) {
        case 4: fast_scan<4>(number_of_operators); break;
        case 5: fast_scan<5>(number_of_operators); break;
        case 6: fast_scan<6>(number_of_operators); break;
        case 7: fast_scan<7>(number_of_operators); break;
        case 8: fast_scan<8>(number_of_operators); break;
        default: goto slow_scan;
    }
    return 0;

slow_scan:
    cout << "# (No hard-coded fast scaner for the given arguments;  falling back on the slow scaner.)" << endl;
    slow_scan(number_of_qubits,number_of_operators);
    return 0;
}
//@-others
//@-leo
