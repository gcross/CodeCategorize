//@+leo-ver=5-thin
//@+node:gcross.20101126220444.1713: * @thin anti_commutator_last_operator_sequence.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101126220444.1714: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101126220444.1715: ** struct AntiCommutatorLastOperatorSequenceOrderedOperatorSpace
//@+node:gcross.20101126220444.1716: *3* (constructors)
AntiCommutatorLastOperatorSequenceOrderedOperatorSpace::AntiCommutatorLastOperatorSequenceOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , FirstColumnXZOperatorSpace(number_of_operators,number_of_qubits)
    , last_operator_anti_commuting_qubit_sequence(*this,number_of_operators*number_of_qubits,0,1)
    , intrapair_ties(*this,number_of_qubits*number_of_pairs,0,1)
    , interpair_ties(*this,number_of_qubits*max(number_of_pairs-1,0),0,1)
{
    if(number_of_operators <= 1) return;
    BoolMatrix anti_commuting_qubits_matrix = getAntiCommutingQubitsMatrix(),
               intrapair_ties_matrix(intrapair_ties,number_of_pairs,number_of_qubits),
               interpair_ties_matrix(interpair_ties,max(number_of_pairs-1,0),number_of_qubits);
    IntMatrix  matrix(last_operator_anti_commuting_qubit_sequence,number_of_qubits,number_of_operators);
    for(int i = 0; i < number_of_operators-1; ++i) {
        const int commutator_number = commutator_matrix(i,number_of_operators-1);
        for(int j = 0; j < number_of_qubits; ++j) {
            channel(*this,anti_commuting_qubits_matrix(j,commutator_number),matrix(j,i));
        }
    }
    rel(*this,matrix.row(number_of_operators-1),IRT_EQ,0);
    if(number_of_pairs <= 1) {
        BoolVarArgs empty_args;
        for(int i = number_of_qubits-1; i >= 0; --i) {
            postOrderingConstraint
                (matrix.col(i)
                ,intrapair_ties_matrix.row(i)
                ,empty_args
                );
        }
    } else {
        for(int i = number_of_qubits-1; i >= 0; --i) {
            postOrderingConstraint
                (matrix.col(i)
                ,intrapair_ties_matrix.row(i)
                ,interpair_ties_matrix.row(i)
                );
        }
    }
}

AntiCommutatorLastOperatorSequenceOrderedOperatorSpace::AntiCommutatorLastOperatorSequenceOrderedOperatorSpace(bool share, AntiCommutatorLastOperatorSequenceOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , CommutatorOperatorSpace(share,s)
    , OperatorSpace(share,s)
    , FirstColumnXZOperatorSpace(share,s)
{
    last_operator_anti_commuting_qubit_sequence.update(*this,share,s.last_operator_anti_commuting_qubit_sequence);
    intrapair_ties.update(*this,share,s.intrapair_ties);
    interpair_ties.update(*this,share,s.interpair_ties);
}
//@+node:gcross.20101126220444.1717: *3* copy
Space* AntiCommutatorLastOperatorSequenceOrderedOperatorSpace::copy(bool share)
{
    return new AntiCommutatorLastOperatorSequenceOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
