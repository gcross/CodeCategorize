//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2472: * @thin commutator.hh
//@@language cplusplus

#ifndef COMMUTATOR_HH
#define COMMUTATOR_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2473: ** << Includes >>
#include <gecode/int.hh>
#include <boost/numeric/ublas/matrix.hpp>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.2479: ** struct CommutatorOperatorSpace
struct CommutatorOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2480: *3* (fields)
    int number_of_commutators;

    boost::numeric::ublas::matrix<int> commutator_matrix;

    BoolVarArray anti_commuting_qubits, anti_commuting_operators;
    IntVarArray anti_commuting_qubit_counts_minus_hidden_qubits, anti_commuting_qubit_counts;
    //@+node:gcross.20101123222425.2481: *3* (constructors)
    CommutatorOperatorSpace(int number_of_operators, int number_of_qubits);
    CommutatorOperatorSpace(bool share, CommutatorOperatorSpace& s);
    //@+node:gcross.20101123222425.2482: *3* (methods)
    virtual Space* copy(bool share);
    BoolMatrix getAntiCommutingQubitsMatrix() { return BoolMatrix(anti_commuting_qubits,number_of_qubits,number_of_commutators); }
    BoolMatrix getAntiCommutatorMatrix() { return BoolMatrix(anti_commuting_operators,number_of_operators,number_of_operators); }
    IntMatrix getAntiCommutingQubitCountsMatrix() { return IntMatrix(anti_commuting_qubit_counts,number_of_operators,number_of_operators); }
    IntMatrix getAntiCommutingQubitCountsMinusHiddenQubitsMatrix() { return IntMatrix(anti_commuting_qubit_counts_minus_hidden_qubits,number_of_operators,number_of_operators); }
    //@-others

};
//@-others

}

#endif
//@-leo
