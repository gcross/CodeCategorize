//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4266: * @thin test_utils.hh
//@@language cplusplus

#ifndef TEST_UTILS_HH
#define TEST_UTILS_HH

//@+<< Includes >>
//@+node:gcross.20101121135345.1483: ** << Includes >>
#include <gecode/int.hh>
#include <illuminate.hpp>
#include <set>
#include <vector>

#include "operator_space.hh"

using namespace Gecode;
using namespace CodeCategorize;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101209224839.2297: ** struct Code
struct Code {
    int number_of_stabilizers, number_of_gauge_qubits;
    vector<size_t> logical_qubit_distances;

    Code(const int number_of_stabilizers, const int number_of_gauge_qubits, const vector<size_t>& logical_qubit_distances)
        : number_of_stabilizers(number_of_stabilizers)
        , number_of_gauge_qubits(number_of_gauge_qubits)
        , logical_qubit_distances(logical_qubit_distances)
    { }

    bool operator<(const Code& c) const {
        if(number_of_stabilizers < c.number_of_stabilizers) return true;
        if(number_of_stabilizers > c.number_of_stabilizers) return false;
        if(number_of_gauge_qubits < c.number_of_gauge_qubits) return true;
        if(number_of_gauge_qubits > c.number_of_gauge_qubits) return false;
        if(logical_qubit_distances.size() < c.logical_qubit_distances.size()) return true;
        if(logical_qubit_distances.size() > c.logical_qubit_distances.size()) return false;
        for(int i = 0; i < logical_qubit_distances.size(); ++i) {
            if(logical_qubit_distances[i] < c.logical_qubit_distances[i]) return true;
            if(logical_qubit_distances[i] > c.logical_qubit_distances[i]) return false;
        }
        return false;
    }
    bool operator==(const Code& c) const {
        if(number_of_stabilizers != c.number_of_stabilizers) return false;
        if(number_of_gauge_qubits != c.number_of_gauge_qubits) return false;
        if(logical_qubit_distances.size() != c.logical_qubit_distances.size()) return false;
        for(int i = 0; i < logical_qubit_distances.size(); ++i) {
            if(logical_qubit_distances[i] != c.logical_qubit_distances[i]) return false;
        }
        return true;
    }
};
//@+node:gcross.20101121135345.1481: ** Functions
void checkCodes(OperatorSpace* space);
long countSolutions(OperatorSpace* space);
set<Code> gatherCodes(OperatorSpace* space);
vector<long> gatherSolutions(OperatorSpace* space);
long longFromOperatorSpace(const OperatorSpace* space);
void validateNonTrivial(const BoolVarArray& X, const BoolVarArray& Z, const BoolVarArray& non_trivial);
//@-others

#endif
//@-leo
