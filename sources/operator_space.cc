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
//@+node:gcross.20101116210424.1516:(constructor)
OperatorSpace::OperatorSpace(int number_of_operators, int number_of_qubits)
    : X(*this,number_of_operators*number_of_qubits)
    , Z(*this,number_of_operators*number_of_qubits)
    , number_of_operators(number_of_operators)
    , number_of_qubits(number_of_qubits)
{

}
//@-node:gcross.20101116210424.1516:(constructor)
//@-node:gcross.20101116210424.1515:class OperatorSpace
//@-others
//@nonl
//@-node:gcross.20101116210424.1514:@thin operator_space.cc
//@-leo
