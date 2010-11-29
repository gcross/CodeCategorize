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
    , X_set_sizes(*this,number_of_qubits,0,number_of_operators)
    , Y_set_sizes(*this,number_of_qubits,0,number_of_operators)
    , Z_set_sizes(*this,number_of_qubits,0,number_of_operators)
    , intrapair_ties(*this,number_of_qubits*number_of_pairs,0,1)
    , interpair_ties(*this,number_of_qubits*max(number_of_pairs-1,0),0,1)
{
    IntMatrix  pauli_orderings_matrix(pauli_orderings,4,number_of_qubits),
               unsorted_orderings_matrix(unsorted_orderings,number_of_operators,number_of_qubits),
               orderings_matrix(orderings,number_of_operators,number_of_qubits),
               O_matrix = getOMatrix();
    BoolMatrix intrapair_ties_matrix(intrapair_ties,number_of_pairs,number_of_qubits),
               interpair_ties_matrix(interpair_ties,max(number_of_pairs-1,0),number_of_qubits);
    for(int i = 0; i < number_of_qubits; ++i) {
        cardinality(*this,X_sets[i],X_set_sizes[i]);
        cardinality(*this,Y_sets[i],Y_set_sizes[i]);
        cardinality(*this,Z_sets[i],Z_set_sizes[i]);
        rel(*this,
            (X_set_sizes[i] < Z_set_sizes[i] && (
                (Z_set_sizes[i] <  Y_set_sizes[i]
                 && pauli_orderings_matrix(0,i) == 0
                 && pauli_orderings_matrix(1,i) == 1
                 && pauli_orderings_matrix(2,i) == 2
                 && pauli_orderings_matrix(3,i) == 3
                )
             ^  (Z_set_sizes[i] == Y_set_sizes[i]
                 && pauli_orderings_matrix(0,i) == 0
                 && pauli_orderings_matrix(1,i) == 1
                 && pauli_orderings_matrix(2,i) == 2
                 && pauli_orderings_matrix(3,i) == 2
                )
             ^  (Z_set_sizes[i] >  Y_set_sizes[i] && (
                    (X_set_sizes[i] <  Y_set_sizes[i]
                     && pauli_orderings_matrix(0,i) == 0
                     && pauli_orderings_matrix(1,i) == 1
                     && pauli_orderings_matrix(2,i) == 3
                     && pauli_orderings_matrix(3,i) == 2
                    )
                 ^  (X_set_sizes[i] == Y_set_sizes[i]
                     && pauli_orderings_matrix(0,i) == 0
                     && pauli_orderings_matrix(1,i) == 1
                     && pauli_orderings_matrix(2,i) == 2
                     && pauli_orderings_matrix(3,i) == 1
                    )
                 ^  (X_set_sizes[i] >  Y_set_sizes[i]
                     && pauli_orderings_matrix(0,i) == 0
                     && pauli_orderings_matrix(1,i) == 2
                     && pauli_orderings_matrix(2,i) == 3
                     && pauli_orderings_matrix(3,i) == 1
                    )
                ))
            ))
         ^  (X_set_sizes[i] == Z_set_sizes[i] && (
                (Z_set_sizes[i] <  Y_set_sizes[i]
                 && pauli_orderings_matrix(0,i) == 0
                 && pauli_orderings_matrix(1,i) == 1
                 && pauli_orderings_matrix(2,i) == 1
                 && pauli_orderings_matrix(3,i) == 2
                )
             ^  (Z_set_sizes[i] == Y_set_sizes[i]
                 && pauli_orderings_matrix(0,i) == 0
                 && pauli_orderings_matrix(1,i) == 1
                 && pauli_orderings_matrix(2,i) == 1
                 && pauli_orderings_matrix(3,i) == 1
                )
             ^  (Z_set_sizes[i] >  Y_set_sizes[i]
                 && pauli_orderings_matrix(0,i) == 0
                 && pauli_orderings_matrix(1,i) == 2
                 && pauli_orderings_matrix(2,i) == 2
                 && pauli_orderings_matrix(3,i) == 1
                )
            ))
         ^  (X_set_sizes[i] > Z_set_sizes[i] && (
                (Z_set_sizes[i] <  Y_set_sizes[i] && (
                    (X_set_sizes[i] <  Y_set_sizes[i]
                     && pauli_orderings_matrix(0,i) == 0
                     && pauli_orderings_matrix(1,i) == 2
                     && pauli_orderings_matrix(2,i) == 1
                     && pauli_orderings_matrix(3,i) == 3
                    )
                 ^  (X_set_sizes[i] == Y_set_sizes[i]
                     && pauli_orderings_matrix(0,i) == 0
                     && pauli_orderings_matrix(1,i) == 2
                     && pauli_orderings_matrix(2,i) == 1
                     && pauli_orderings_matrix(3,i) == 2
                    )
                 ^  (X_set_sizes[i] >  Y_set_sizes[i]
                     && pauli_orderings_matrix(0,i) == 0
                     && pauli_orderings_matrix(1,i) == 3
                     && pauli_orderings_matrix(2,i) == 1
                     && pauli_orderings_matrix(3,i) == 2
                    )
                ))
             ^  (Z_set_sizes[i] == Y_set_sizes[i]
                 && pauli_orderings_matrix(0,i) == 0
                 && pauli_orderings_matrix(1,i) == 2
                 && pauli_orderings_matrix(2,i) == 1
                 && pauli_orderings_matrix(3,i) == 1
                )
             ^  (Z_set_sizes[i] >  Y_set_sizes[i]
                 && pauli_orderings_matrix(0,i) == 0
                 && pauli_orderings_matrix(1,i) == 3
                 && pauli_orderings_matrix(2,i) == 2
                 && pauli_orderings_matrix(3,i) == 1
                )
            ))
        );
        for(int j = 0; j < number_of_operators; ++j) {
            element(*this,pauli_orderings_matrix.row(i),O_matrix(i,j),unsorted_orderings_matrix(j,i));
        }
        postOrderingConstraint
            (orderings_matrix.row(i)
            ,intrapair_ties_matrix.row(i)
            ,interpair_ties_matrix.row(i)
            );
    }
    for(int i = 0; i < number_of_operators; ++i) {
        sorted(*this,unsorted_orderings_matrix.col(i),orderings_matrix.col(i));
    }
}

PauliGroupsRowOrderedOperatorSpace::PauliGroupsRowOrderedOperatorSpace(bool share, PauliGroupsRowOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , ColumnPauliSetsOperatorSpace(share,s)
    , OperatorSpace(share,s)
{
    pauli_orderings.update(*this,share,s.pauli_orderings);
    unsorted_orderings.update(*this,share,s.unsorted_orderings);
    orderings.update(*this,share,s.orderings);
    X_set_sizes.update(*this,share,s.X_set_sizes);
    Y_set_sizes.update(*this,share,s.Y_set_sizes);
    Z_set_sizes.update(*this,share,s.Z_set_sizes);
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
