//@+leo-ver=5-thin
//@+node:gcross.20101126142808.1688: * @thin XZY_ordered.hh
//@@language cplusplus

#ifndef CONSTRAINTS_XZY_ORDERED_HH
#define CONSTRAINTS_XZY_ORDERED_HH

//@+<< Includes >>
//@+node:gcross.20101126142808.1689: ** << Includes >>
#include <gecode/int.hh>

#include "column_pauli_sets.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101126142808.1690: ** struct XZYOrderedOperatorSpace
struct XZYOrderedOperatorSpace : public virtual ColumnPauliSetsOperatorSpace {

    //@+others
    //@+node:gcross.20101126142808.1691: *3* (fields)
    //@+node:gcross.20101126142808.1692: *3* (constructors)
    XZYOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    XZYOrderedOperatorSpace(bool share, XZYOrderedOperatorSpace& s);
    //@+node:gcross.20101126142808.1693: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
