//@+leo-ver=5-thin
//@+node:gcross.20101117113704.1320: * @thin column_ordered.hh
//@@language cplusplus

#ifndef CONSTRAINTS_COLUMN_ORDERED_HH
#define CONSTRAINTS_COLUMN_ORDERED_HH

//@+<< Includes >>
//@+node:gcross.20101117113704.1321: ** << Includes >>
#include <gecode/int.hh>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101118114009.1430: ** struct ColumnOrderedOperatorSpace
struct ColumnOrderedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101118114009.1431: *3* (fields)
    int number_of_ties;
    BoolVarArray ties;
    //@+node:gcross.20101118114009.1432: *3* (constructors)
    ColumnOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    ColumnOrderedOperatorSpace(bool share, ColumnOrderedOperatorSpace& s);
    //@+node:gcross.20101118114009.1433: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
