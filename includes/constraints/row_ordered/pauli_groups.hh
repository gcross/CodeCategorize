//@+leo-ver=5-thin
//@+node:gcross.20101126220444.1905: * @thin pauli_groups.hh
//@@language cplusplus

#ifndef CONSTRAINTS_ROW_ORDERED_PAULI_GROUPS_HH
#define CONSTRAINTS_ROW_ORDERED_PAULI_GROUPS_HH

//@+<< Includes >>
//@+node:gcross.20101126220444.1906: ** << Includes >>
#include <gecode/int.hh>

#include "column_pauli_sets.hh"
#include "constraints/row_ordered.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101126220444.1907: ** struct PauliGroupsRowOrderedOperatorSpace
struct PauliGroupsRowOrderedOperatorSpace
    : public virtual RowOrderedOperatorSpace
    , public virtual ColumnPauliSetsOperatorSpace
{

    //@+others
    //@+node:gcross.20101126220444.1908: *3* (fields)
    IntVarArray pauli_orderings, orderings;
    BoolVarArray XZ, ZY, XY, interpair_ties, intrapair_ties;
    //@+node:gcross.20101126220444.1909: *3* (constructors)
    PauliGroupsRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    PauliGroupsRowOrderedOperatorSpace(bool share, PauliGroupsRowOrderedOperatorSpace& s);
    //@+node:gcross.20101126220444.1910: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
