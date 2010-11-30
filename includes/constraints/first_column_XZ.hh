//@+leo-ver=5-thin
//@+node:gcross.20101129164055.1821: * @thin first_column_XZ.hh
//@@language cplusplus

#ifndef CONSTRAINTS_FIRST_COLUMN_XZ_HH
#define CONSTRAINTS_FIRST_COLUMN_XZ_HH

//@+<< Includes >>
//@+node:gcross.20101129164055.1822: ** << Includes >>
#include <gecode/int.hh>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101129164055.1823: ** struct FirstColumnXZOperatorSpace
struct FirstColumnXZOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101129164055.1825: *3* (constructors)
    FirstColumnXZOperatorSpace(int number_of_operators, int number_of_qubits);
    FirstColumnXZOperatorSpace(bool share, FirstColumnXZOperatorSpace& s);
    //@+node:gcross.20101129164055.1826: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
