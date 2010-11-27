//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3650: * @thin commutator.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3651: ** << Includes >>
#include <gecode/minimodel.hh>

#include "commutator.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3679: ** struct CommutatorOperatorSpace
//@+node:gcross.20101123222425.3680: *3* (constructors)
CommutatorOperatorSpace::CommutatorOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , number_of_commutators(number_of_operators*(number_of_operators-1)/2)
    , anti_commuting_qubits(*this,number_of_commutators*number_of_qubits,0,1)
    , anti_commuting_qubit_counts_minus_hidden_qubits(*this,number_of_operators*number_of_operators,0,number_of_qubits)
    , anti_commuting_qubit_counts(*this,number_of_operators*number_of_operators,0,number_of_qubits+1)
    , anti_commuting_operators(*this,number_of_operators*number_of_operators,0,1)
    , commutator_matrix(number_of_operators,number_of_operators)
{
    BoolMatrix anti_commuting_qubits_matrix = getAntiCommutingQubitsMatrix(),
               anti_commuting_operators_matrix = getAntiCommutatorMatrix(),
               X_matrix = getXMatrix(),
               Z_matrix = getZMatrix();
    IntMatrix  anti_commuting_qubit_counts_minus_hidden_qubits_matrix = getAntiCommutingQubitCountsMinusHiddenQubitsMatrix(),
               anti_commuting_qubit_counts_matrix = getAntiCommutingQubitCountsMatrix();
    int commutator_number = 0;
    for(int i = 0; i < number_of_operators; ++i) {
        rel(*this,anti_commuting_qubit_counts_minus_hidden_qubits_matrix(i,i) == 0);
        rel(*this,anti_commuting_qubit_counts_matrix(i,i) == 0);
        rel(*this,anti_commuting_operators_matrix(i,i) == 0);
        commutator_matrix(i,i) = -1;
        for(int j = i+1; j < number_of_operators; ++j) {
            commutator_matrix(i,j) = commutator_number;
            commutator_matrix(j,i) = commutator_number;
            for(int k = 0; k < number_of_qubits; ++k) {
                rel(*this,anti_commuting_qubits_matrix(k,commutator_number) ==
                    (X_matrix(k,i) && Z_matrix(k,j))
                  ^ (X_matrix(k,j) && Z_matrix(k,i))
                );
            }
            rel(*this,anti_commuting_qubit_counts_minus_hidden_qubits_matrix(i,j) == sum(anti_commuting_qubits_matrix.row(commutator_number)));
            rel(*this,anti_commuting_qubit_counts_minus_hidden_qubits_matrix(j,i) == anti_commuting_qubit_counts_minus_hidden_qubits_matrix(i,j));
            if(i/2 == j/2) {
                rel(*this,anti_commuting_qubit_counts_matrix(i,j) == anti_commuting_qubit_counts_minus_hidden_qubits_matrix(i,j)+1);
            } else {
                rel(*this,anti_commuting_qubit_counts_matrix(i,j) == anti_commuting_qubit_counts_minus_hidden_qubits_matrix(i,j));
            }
            rel(*this,anti_commuting_qubit_counts_matrix(j,i) == anti_commuting_qubit_counts_matrix(i,j));
            rel(*this,anti_commuting_operators_matrix(i,j) == anti_commuting_qubit_counts_matrix(i,j)%2);
            rel(*this,anti_commuting_operators_matrix(j,i) == anti_commuting_operators_matrix(i,j));
            ++commutator_number;
        }
    }
}

CommutatorOperatorSpace::CommutatorOperatorSpace(bool share, CommutatorOperatorSpace& s)
    : OperatorSpace(share,s)
    , number_of_commutators(s.number_of_commutators)
{
    anti_commuting_qubits.update(*this,share,s.anti_commuting_qubits);
    anti_commuting_operators.update(*this,share,s.anti_commuting_operators);
    anti_commuting_qubit_counts_minus_hidden_qubits.update(*this,share,s.anti_commuting_qubit_counts_minus_hidden_qubits);
    anti_commuting_qubit_counts.update(*this,share,s.anti_commuting_qubit_counts);
}
//@+node:gcross.20101123222425.3681: *3* copy
Space* CommutatorOperatorSpace::copy(bool share)
{
    return new CommutatorOperatorSpace(share,*this);
}
//@-others

}
//@-leo
