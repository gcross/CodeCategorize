//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4269: * @thin test_utils.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101121135345.1485: ** << Includes >>
#include <algorithm>
#include <codequest.hpp>
#include <illuminate.hpp>

#include "solution_iterator.hh"
#include "utilities.hh"

#include "test_utils.hh"

using namespace CodeCategorize;
using namespace Gecode;
using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101121135345.1477: ** Functions
//@+node:gcross.20101209224839.2318: *3* checkCodes
void checkCodes(OperatorSpace* space) {
    typedef map<pair<int,int>,set<Code> > CodeTable;
    typedef CodeTable::const_iterator CodeTablePosition;
    static CodeTable operator_space_code_table;
    pair<int,int> id = make_pair(space->number_of_operators,space->number_of_qubits);
    CodeTablePosition operator_space_code_position = operator_space_code_table.find(id);
    if(operator_space_code_position == operator_space_code_table.end()) {
        operator_space_code_table.insert(make_pair(id,gatherCodes(new OperatorSpace(space->number_of_operators,space->number_of_qubits))));
        operator_space_code_position = operator_space_code_table.find(id);
    }
    const set<Code>& operator_space_codes = operator_space_code_position->second;
    const set<Code> constrained_space_codes = gatherCodes(space);
    ASSERT_EQ(operator_space_codes.size(),constrained_space_codes.size());
    ASSERT_TRUE(equal(operator_space_codes.begin(),operator_space_codes.end(),constrained_space_codes.begin()));
}
//@+node:gcross.20101209224839.2296: *3* countSolutions
long countSolutions(OperatorSpace* space) {
    return countSolutions(auto_ptr<OperatorSpace>(space));
}
//@+node:gcross.20101209224839.2299: *3* gatherCodes
set<Code> gatherCodes(OperatorSpace* space) {
    set<Code> codes;
    auto_ptr<OperatorSpace> space_ptr(space);
    for(SolutionIterator<> solution(space_ptr); solution; ++solution) {
        auto_ptr<SolutionIterator<>::qec_t> code = solution.computeOptimizedCode();
        int number_of_stabilizers = code->stabilizers.size(),
            number_of_gauge_qubits = code->gauge_qubits.size(),
            number_of_logical_qubits = code->logical_qubit_error_distances.size();
        if(number_of_stabilizers > 0 || number_of_gauge_qubits > 0 || number_of_logical_qubits > 0) {
            codes.insert(Code(number_of_stabilizers,number_of_gauge_qubits,code->logical_qubit_error_distances));
        }
    }
    return codes;
}
//@+node:gcross.20101128173348.1865: *3* gatherSolutions
vector<long> gatherSolutions(OperatorSpace* space) {
    vector<long> solutions;
    auto_ptr<OperatorSpace> space_ptr(space);
    for(SolutionIterator<> solution(space_ptr); solution; ++solution) {
        solutions.push_back(longFromOperatorSpace(solution.getSpace()));
    }
    return solutions;
}
//@+node:gcross.20101127142618.1761: *3* longFromOperatorSpace
long longFromOperatorSpace(const OperatorSpace* m) {
    long n = 0;
    for(int i = 0; i < m->O.size(); ++i) {
        n <<= 2;
        n += m->O[i].val();
    }
    return n;
}
//@+node:gcross.20101121135345.1478: *3* validateNonTrivial
void validateNonTrivial(const BoolVarArray& X, const BoolVarArray& Z, const BoolVarArray& non_trivial) {
    for(int i = 0; i < non_trivial.size(); ++i) {
        ASSERT_EQ(X[i].val() || Z[i].val(),non_trivial[i].val());
    }
}
//@-others
//@-leo
