//@+leo-ver=5-thin
//@+node:gcross.20101129164055.1874: * @thin non_trivial.hh
//@@language cplusplus

#ifndef CONSTRAINTS_NON_TRIVIAL_HH
#define CONSTRAINTS_NON_TRIVIAL_HH

//@+<< Includes >>
//@+node:gcross.20101129164055.1875: ** << Includes >>
#include <gecode/int.hh>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101129164055.1876: ** struct NonTrivialOperatorSpace
struct NonTrivialOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101129164055.1877: *3* (constructors)
    NonTrivialOperatorSpace(int number_of_operators, int number_of_qubits);
    NonTrivialOperatorSpace(bool share, NonTrivialOperatorSpace& s);
    //@+node:gcross.20101129164055.1878: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
