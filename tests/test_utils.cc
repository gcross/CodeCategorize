//@+leo-ver=5-thin
//@+node:gcross.20101121135345.1474: * @thin test_utils.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101121135345.1485: ** << Includes >>
#include <unit--.hpp>

#include "test_utils.hh"
//@-<< Includes >>

//@+others
//@+node:gcross.20101121135345.1477: ** Functions
//@+node:gcross.20101121135345.1478: *3* validateNonTrivial
void validateNonTrivial(const BoolVarArray& X, const BoolVarArray& Z, const BoolVarArray& non_trivial) {
    for(int i = 0; i < non_trivial.size(); ++i) {
        assertEqual(X[i].val() || Z[i].val(),non_trivial[i].val());
    }
}
//@-others
//@-leo
