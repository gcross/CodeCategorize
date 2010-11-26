//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3923: * @thin special_case_XZ.hh
//@@language cplusplus

#ifndef CONSTRAINTS_SPECIAL_CASE_XZ_HH
#define CONSTRAINTS_SPECIAL_CASE_XZ_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.3924: ** << Includes >>
#include <gecode/int.hh>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3925: ** struct SpecialCaseXZConstrainedOperatorSpace
struct SpecialCaseXZConstrainedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.3926: *3* (fields)
    BoolVar first_row_X, first_row_Z, second_row_X, second_row_Z;
    BoolVar special_case_is_present;
    IntVar special_case_is_present_as_int;
    //@+node:gcross.20101123222425.3927: *3* (constructors)
    SpecialCaseXZConstrainedOperatorSpace(int number_of_operators, int number_of_qubits);
    SpecialCaseXZConstrainedOperatorSpace(bool share, SpecialCaseXZConstrainedOperatorSpace& s);
    //@+node:gcross.20101123222425.3928: *3* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@-others

}

#endif
//@-leo
