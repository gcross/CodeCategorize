//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4486: * @thin column_pauli_sets.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.4487: ** << Includes >>
#include <gecode/minimodel.hh>

#include "column_pauli_sets.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.4488: ** struct ColumnPauliSetsOperatorSpace
//@+node:gcross.20101123222425.4489: *3* (constructors)
ColumnPauliSetsOperatorSpace::ColumnPauliSetsOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , X_bit_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,number_of_operators))
    , Z_bit_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,number_of_operators))
    , X_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,number_of_operators))
    , Y_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,number_of_operators))
    , Z_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,number_of_operators))
    , I_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,number_of_operators))
    , non_trivial_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,number_of_operators))
{
    BoolMatrix X_matrix = getXMatrix(),
               Z_matrix = getZMatrix(),
               non_trivial_matrix = getNonTrivialMatrix();
    for(int i = 0; i < number_of_qubits; ++i) {
        channel(*this,X_matrix.col(i),X_bit_sets[i]);
        channel(*this,Z_matrix.col(i),Z_bit_sets[i]);
        X_sets[i] = expr(*this,X_bit_sets[i] - Z_bit_sets[i]);
        Z_sets[i] = expr(*this,Z_bit_sets[i] - X_bit_sets[i]);
        Y_sets[i] = expr(*this,X_bit_sets[i] & Z_bit_sets[i]);
        channel(*this,non_trivial_matrix.col(i),non_trivial_sets[i]);
        I_sets[i] = expr(*this,IntSet(0,number_of_operators-1)-non_trivial_sets[i]);
    }
}

ColumnPauliSetsOperatorSpace::ColumnPauliSetsOperatorSpace(bool share, ColumnPauliSetsOperatorSpace& s)
    : OperatorSpace(share,s)
{
    X_bit_sets.update(*this,share,s.X_bit_sets);
    Z_bit_sets.update(*this,share,s.Z_bit_sets);
    X_sets.update(*this,share,s.X_sets);
    Y_sets.update(*this,share,s.Y_sets);
    Z_sets.update(*this,share,s.Z_sets);
    I_sets.update(*this,share,s.I_sets);
    non_trivial_sets.update(*this,share,s.non_trivial_sets);
}
//@+node:gcross.20101123222425.4490: *3* copy
Space* ColumnPauliSetsOperatorSpace::copy(bool share)
{
    return new ColumnPauliSetsOperatorSpace(share,*this);
}
//@-others

}
//@-leo
