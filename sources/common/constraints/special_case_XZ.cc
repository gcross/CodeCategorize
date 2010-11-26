//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3934: * @thin special_case_XZ.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3935: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/special_case_XZ.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3936: ** struct SpecialCaseXZOperatorSpace
//@+node:gcross.20101123222425.3937: *3* (constructors)
SpecialCaseXZOperatorSpace::SpecialCaseXZOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , first_row_X(*this,0,1)
    , first_row_Z(*this,0,1)
    , second_row_X(*this,0,1)
    , second_row_Z(*this,0,1)
    , special_case_is_present(*this,0,1)
    , special_case_is_present_as_int(*this,0,1)
{
    BoolMatrix X_matrix = getXMatrix(),
               Z_matrix = getZMatrix();
    rel(*this,BOT_AND,X_matrix.row(0),first_row_X);
    rel(*this,BOT_OR ,Z_matrix.row(0),first_row_Z);
    rel(*this,BOT_OR ,X_matrix.row(1),second_row_X);
    rel(*this,BOT_AND,Z_matrix.row(1),second_row_Z);

    BoolVarArgs expected_to_be_true, expected_to_be_false;
    expected_to_be_true << first_row_X << second_row_Z;
    expected_to_be_false << first_row_Z << second_row_X;
    clause(*this,BOT_AND,expected_to_be_true,expected_to_be_false,special_case_is_present);
    channel(*this,special_case_is_present,special_case_is_present_as_int);

    static DFA::Transition t[] =
        {{0,0,1}
        ,{0,1,2}
        ,{1,0,1}
        ,{1,1,1}
        ,{1,2,1}
        ,{1,3,1}
        ,{2,0,2}
        ,{2,1,1}
        ,{2,3,2}
        ,{-1,-1,-1}
        };
    static int f[] = {0,1,2,-1};
    static DFA d(0,t,f);

    IntMatrix O_matrix = getOMatrix();
    IntVarArgs symbols;
    symbols << special_case_is_present_as_int;
    for(int i = 0; i < number_of_qubits; ++i) {
        symbols << O_matrix.slice(i,i+1,2,number_of_operators);
    }
    extensional(*this,symbols,d);
}

SpecialCaseXZOperatorSpace::SpecialCaseXZOperatorSpace(bool share, SpecialCaseXZOperatorSpace& s)
    : OperatorSpace(share,s)
{
    first_row_X.update(*this,share,s.first_row_X);
    first_row_Z.update(*this,share,s.first_row_Z);
    second_row_X.update(*this,share,s.second_row_X);
    second_row_Z.update(*this,share,s.second_row_Z);
    special_case_is_present.update(*this,share,s.special_case_is_present);
    special_case_is_present_as_int.update(*this,share,s.special_case_is_present_as_int);
}
//@+node:gcross.20101123222425.3938: *3* copy
Space* SpecialCaseXZOperatorSpace::copy(bool share)
{
    return new SpecialCaseXZOperatorSpace(share,*this);
}
//@-others

}
//@-leo
