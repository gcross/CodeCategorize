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
    , pauli_orderings(*this,number_of_qubits*3,0,3)
    , orderings(*this,number_of_qubits*number_of_operators,0,2)
    , XZ(*this,number_of_qubits,0,1)
    , ZY(*this,number_of_qubits,0,1)
    , XY(*this,number_of_qubits,0,1)
    , intrapair_ties(*this,number_of_qubits*number_of_pairs,0,1)
    , interpair_ties(*this,number_of_qubits*max(number_of_pairs-1,0),0,1)
{
    IntMatrix  pauli_orderings_matrix(pauli_orderings,3,number_of_qubits),
               orderings_matrix(orderings,number_of_operators,number_of_qubits),
               O_matrix = getOMatrix();
    BoolMatrix intrapair_ties_matrix(intrapair_ties,number_of_pairs,number_of_qubits),
               interpair_ties_matrix(interpair_ties,max(number_of_pairs-1,0),number_of_qubits);
    for(int i = 0; i < number_of_qubits; ++i) {
        XZ[i] = expr(*this,cardinality(X_sets[i]) >= cardinality(Z_sets[i]));
        ZY[i] = expr(*this,cardinality(Z_sets[i]) >= cardinality(Y_sets[i]));
        XY[i] = expr(*this,cardinality(X_sets[i]) >= cardinality(Y_sets[i]));
        rel(*this,
            (XZ[i] && ZY[i]) >>
            (   pauli_orderings_matrix(0,i) == 0
             && pauli_orderings_matrix(1,i) == 1
             && pauli_orderings_matrix(2,i) == 2
            )
        );
        rel(*this,
            (XY[i] && !ZY[i]) >>
            (   pauli_orderings_matrix(0,i) == 0
             && pauli_orderings_matrix(2,i) == 1
             && pauli_orderings_matrix(1,i) == 2
            )
        );
        rel(*this,
            (!XY[i] && XZ[i]) >>
            (   pauli_orderings_matrix(2,i) == 0
             && pauli_orderings_matrix(0,i) == 1
             && pauli_orderings_matrix(1,i) == 2
            )
        );
        rel(*this,
            (!ZY[i] && !XZ[i]) >>
            (   pauli_orderings_matrix(2,i) == 0
             && pauli_orderings_matrix(1,i) == 1
             && pauli_orderings_matrix(0,i) == 2
            )
        );
        rel(*this,
            (ZY[i] && !XY[i]) >>
            (   pauli_orderings_matrix(1,i) == 0
             && pauli_orderings_matrix(2,i) == 1
             && pauli_orderings_matrix(0,i) == 2
            )
        );
        rel(*this,
            (!XZ[i] && XY[i]) >>
            (   pauli_orderings_matrix(1,i) == 0
             && pauli_orderings_matrix(0,i) == 1
             && pauli_orderings_matrix(2,i) == 2
            )
        );
        for(int j = 0; j < number_of_operators; ++j) {
            rel(*this,
                (O_matrix(i,j) == 0 && orderings_matrix(j,i) == 4)
              ^ (orderings_matrix(j,i) == element(pauli_orderings_matrix.row(i),O_matrix(i,j)-1))
            );
        }
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
