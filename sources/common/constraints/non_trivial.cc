//@+leo-ver=5-thin
//@+node:gcross.20101129164055.1884: * @thin non_trivial.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101129164055.1885: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/non_trivial.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101129164055.1886: ** struct NonTrivialOperatorSpace
//@+node:gcross.20101129164055.1887: *3* (constructors)
NonTrivialOperatorSpace::NonTrivialOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
{
    rel(*this,weights,IRT_GR,0);
    if(number_of_operators % 2 == 1) rel(*this,weights[number_of_operators-1],IRT_GR,1);
}

NonTrivialOperatorSpace::NonTrivialOperatorSpace(bool share, NonTrivialOperatorSpace& s)
    : OperatorSpace(share,s)
{
}
//@+node:gcross.20101129164055.1888: *3* copy
Space* NonTrivialOperatorSpace::copy(bool share)
{
    return new NonTrivialOperatorSpace(share,*this);
}
//@-others

}
//@-leo
