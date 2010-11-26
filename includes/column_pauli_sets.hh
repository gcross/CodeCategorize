//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4449: * @thin column_pauli_sets.hh
//@@language cplusplus

#ifndef CONSTRAINTS_COLUMN_PAULI_SETS_HH
#define CONSTRAINTS_COLUMN_PAULI_SETS_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.4450: ** << Includes >>
#include <gecode/int.hh>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.4451: ** struct ColumnPauliSetsOperatorSpace
struct ColumnPauliSetsOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.4452: *3* (fields)
    SetVarArray X_bit_sets, Z_bit_sets, X_sets, Y_sets, Z_sets, I_sets, non_trivial_sets;
    //@+node:gcross.20101123222425.4453: *3* (constructors)
    ColumnPauliSetsOperatorSpace(int number_of_operators, int number_of_qubits);
    ColumnPauliSetsOperatorSpace(bool share, ColumnPauliSetsOperatorSpace& s);
    //@+node:gcross.20101123222425.4454: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
