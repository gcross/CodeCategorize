//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3780: * @thin anti_commutator_qubit_count_sequence.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3781: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3799: ** struct AntiCommutatorQubitCountSequenceOrderedOperatorSpace
//@+node:gcross.20101123222425.3800: *3* (constructors)
AntiCommutatorQubitCountSequenceOrderedOperatorSpace::AntiCommutatorQubitCountSequenceOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , sorted_anti_commuting_qubit_counts(*this,number_of_operators*number_of_operators,0,number_of_qubits+1)
    , intrapair_ties(*this,number_of_operators*number_of_pairs,0,1)
    , interpair_ties(*this,number_of_operators*max(number_of_pairs-1,0),0,1)
{
    IntMatrix sorted_anti_commuting_qubit_counts_matrix(sorted_anti_commuting_qubit_counts,number_of_operators,number_of_operators),
              anti_commuting_qubit_counts_matrix = getAntiCommutingQubitCountsMatrix();
    for(int i = 0; i < number_of_operators; ++i) {
        sorted(*this,anti_commuting_qubit_counts_matrix.row(i),sorted_anti_commuting_qubit_counts_matrix.row(i));
    }
    BoolMatrix intrapair_ties_matrix(intrapair_ties,number_of_pairs,number_of_operators),
               interpair_ties_matrix(interpair_ties,max(number_of_pairs-1,0),number_of_operators);
    for(int i = number_of_operators-1; i >= 0; --i) {
        postOrderingConstraint
            (sorted_anti_commuting_qubit_counts_matrix.col(i)
            ,intrapair_ties_matrix.row(i)
            ,interpair_ties_matrix.row(i)
            );
    }

}

AntiCommutatorQubitCountSequenceOrderedOperatorSpace::AntiCommutatorQubitCountSequenceOrderedOperatorSpace(bool share, AntiCommutatorQubitCountSequenceOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , CommutatorOperatorSpace(share,s)
    , OperatorSpace(share,s)
{
    sorted_anti_commuting_qubit_counts.update(*this,share,s.sorted_anti_commuting_qubit_counts);
    intrapair_ties.update(*this,share,s.intrapair_ties);
    interpair_ties.update(*this,share,s.interpair_ties);
}
//@+node:gcross.20101123222425.3801: *3* copy
Space* AntiCommutatorQubitCountSequenceOrderedOperatorSpace::copy(bool share)
{
    return new AntiCommutatorQubitCountSequenceOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
