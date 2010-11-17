//@+leo-ver=4-thin
//@+node:gcross.20101116210424.1514:@thin operator_space.cc
//@@language cplusplus

//@<< Includes >>
//@+node:gcross.20101116210424.2281:<< Includes >>
#include "operator_space.hh"
//@nonl
//@-node:gcross.20101116210424.2281:<< Includes >>
//@nl

//@+others
//@+node:gcross.20101116210424.1515:class OperatorSpace
//@+node:gcross.20101116210424.1516:(constructors)
OperatorSpace::OperatorSpace(int number_of_operators, int number_of_qubits)
    : number_of_operators(number_of_operators)
    , number_of_qubits(number_of_qubits)
    , number_of_variables(number_of_qubits*number_of_operators)
    , X(*this,number_of_operators*number_of_qubits,0,1)
    , Z(*this,number_of_operators*number_of_qubits,0,1)
{
    for(int i = 0; i < number_of_variables; ++i) {
        branch(*this,Z[i],INT_VAL_MIN);
        branch(*this,X[i],INT_VAL_MIN);
    }
}

OperatorSpace::OperatorSpace(bool share, OperatorSpace& s)
    : Space(share,s)
    , number_of_operators(s.number_of_operators)
    , number_of_qubits(s.number_of_qubits)
    , number_of_variables(s.number_of_variables)
{
    X.update(*this,share,s.X);
    Z.update(*this,share,s.Z);
}
//@nonl
//@-node:gcross.20101116210424.1516:(constructors)
//@+node:gcross.20101116222338.1276:copy
Space* OperatorSpace::copy(bool share)
{
    return new OperatorSpace(share,*this);
}
//@nonl
//@-node:gcross.20101116222338.1276:copy
//@-node:gcross.20101116210424.1515:class OperatorSpace
//@-others
//@nonl
//@-node:gcross.20101116210424.1514:@thin operator_space.cc
//@-leo
