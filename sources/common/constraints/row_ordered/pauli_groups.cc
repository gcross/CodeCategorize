//@+leo-ver=5-thin
//@+node:gcross.20101126220444.1916: * @thin pauli_groups.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101126220444.1917: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/row_ordered/pauli_groups.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101126220444.1918: ** struct PauliGroupsRowOrderedOperatorSpace
//@+node:gcross.20101126220444.1919: *3* (constructors)
PauliGroupsRowOrderedOperatorSpace::PauliGroupsRowOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnPauliSetsOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , pauli_orderings(*this,number_of_qubits*4,0,3)
    , unsorted_orderings(*this,number_of_qubits*number_of_operators,0,3)
    , orderings(*this,number_of_qubits*number_of_operators,0,3)
    , XZ(*this,number_of_qubits,0,1)
    , ZY(*this,number_of_qubits,0,1)
    , XY(*this,number_of_qubits,0,1)
    , intrapair_ties(*this,number_of_qubits*number_of_pairs,0,1)
    , interpair_ties(*this,number_of_qubits*max(number_of_pairs-1,0),0,1)
{
    IntMatrix  pauli_orderings_matrix(pauli_orderings,4,number_of_qubits),
               unsorted_orderings_matrix(unsorted_orderings,number_of_operators,number_of_qubits),
               orderings_matrix(orderings,number_of_operators,number_of_qubits),
               O_matrix = getOMatrix();
    BoolMatrix intrapair_ties_matrix(intrapair_ties,number_of_pairs,number_of_qubits),
               interpair_ties_matrix(interpair_ties,max(number_of_pairs-1,0),number_of_qubits);
    for(int i = number_of_qubits-1; i >= 0; --i) {
        XZ[i] = expr(*this,cardinality(X_sets[i]) >= cardinality(Z_sets[i]));
        ZY[i] = expr(*this,cardinality(Z_sets[i]) >= cardinality(Y_sets[i]));
        XY[i] = expr(*this,cardinality(X_sets[i]) >= cardinality(Y_sets[i]));
        pauli_orderings_matrix(0,i) = expr(*this,3);
        rel(*this,
            (XZ[i] && ZY[i]
             && pauli_orderings_matrix(1,i) == 0
             && pauli_orderings_matrix(2,i) == 1
             && pauli_orderings_matrix(3,i) == 2
            )
          ^ (XY[i] && !ZY[i]
             && pauli_orderings_matrix(1,i) == 0
             && pauli_orderings_matrix(3,i) == 1
             && pauli_orderings_matrix(2,i) == 2
            )
          ^ (!XY[i] && XZ[i]
             && pauli_orderings_matrix(3,i) == 0
             && pauli_orderings_matrix(1,i) == 1
             && pauli_orderings_matrix(2,i) == 2
            )
          ^ (!ZY[i] && !XZ[i]
             && pauli_orderings_matrix(3,i) == 0
             && pauli_orderings_matrix(2,i) == 1
             && pauli_orderings_matrix(1,i) == 2
            )
          ^ (ZY[i] && !XY[i]
             && pauli_orderings_matrix(2,i) == 0
             && pauli_orderings_matrix(3,i) == 1
             && pauli_orderings_matrix(1,i) == 2
            )
          ^ (!XZ[i] && XY[i]
             && pauli_orderings_matrix(2,i) == 0
             && pauli_orderings_matrix(1,i) == 1
             && pauli_orderings_matrix(3,i) == 2
            )
        );
        for(int j = 0; j < number_of_operators; ++j) {
            element(*this,pauli_orderings_matrix.row(i),O_matrix(i,j),unsorted_orderings_matrix(j,i));
        }
        sorted(*this,unsorted_orderings_matrix.row(i),orderings_matrix.row(i));
        postOrderingConstraint
            (orderings_matrix.row(i)
            ,intrapair_ties_matrix.row(i)
            ,interpair_ties_matrix.row(i)
            );
    }
}

PauliGroupsRowOrderedOperatorSpace::PauliGroupsRowOrderedOperatorSpace(bool share, PauliGroupsRowOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , ColumnPauliSetsOperatorSpace(share,s)
    , OperatorSpace(share,s)
{
    pauli_orderings.update(*this,share,s.pauli_orderings);
    orderings.update(*this,share,s.orderings);
    unsorted_orderings.update(*this,share,s.unsorted_orderings);
    intrapair_ties.update(*this,share,s.intrapair_ties);
    interpair_ties.update(*this,share,s.interpair_ties);
}
//@+node:gcross.20101126220444.1920: *3* copy
Space* PauliGroupsRowOrderedOperatorSpace::copy(bool share)
{
    return new PauliGroupsRowOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
