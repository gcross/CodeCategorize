//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2288: * @thin constraints.hh
//@@language cplusplus

#ifndef CONSTRAINTS_HH
#define CONSTRAINTS_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2289: ** << Includes >>
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

//@+others
//@+node:gcross.20101123222425.2333: ** Functions
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m);
void postColumnXZYOrderingConstraints(OperatorSpace& m);
void postNonTrivialWeightConstraints(OperatorSpace& m);
//@-others

}

#endif
//@-leo
