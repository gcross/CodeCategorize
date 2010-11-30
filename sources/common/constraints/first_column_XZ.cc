//@+leo-ver=5-thin
//@+node:gcross.20101129164055.1832: * @thin first_column_XZ.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101129164055.1833: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/first_column_XZ.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101129164055.1834: ** struct FirstColumnXZOperatorSpace
//@+node:gcross.20101129164055.1835: *3* (constructors)
FirstColumnXZOperatorSpace::FirstColumnXZOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
{
    rel(*this,getOMatrix()(0,number_of_operators-1),IRT_EQ,2);
    rel(*this,getZMatrix().slice(0,1,0,number_of_operators-1),IRT_EQ,0);
}

FirstColumnXZOperatorSpace::FirstColumnXZOperatorSpace(bool share, FirstColumnXZOperatorSpace& s)
    : OperatorSpace(share,s)
{
}
//@+node:gcross.20101129164055.1836: *3* copy
Space* FirstColumnXZOperatorSpace::copy(bool share)
{
    return new FirstColumnXZOperatorSpace(share,*this);
}
//@-others

}
//@-leo
