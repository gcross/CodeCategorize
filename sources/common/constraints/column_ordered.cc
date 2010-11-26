//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3372: * @thin column_ordered.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3373: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/column_ordered.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3375: ** struct ColumnOrderedOperatorSpace
//@+node:gcross.20101123222425.3376: *3* (constructors)
ColumnOrderedOperatorSpace::ColumnOrderedOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , number_of_ties(max(0,number_of_qubits-1-number_of_operators%2))
    , ties(*this,(number_of_operators-1)*number_of_ties,0,1)
{
    if(number_of_ties <= 0) return;
    const int first_column = number_of_operators % 2;
    IntMatrix O_matrix = getOMatrix();
    rel(*this,O_matrix.slice(first_column,number_of_qubits,0,1),IRT_GQ);
    if(number_of_operators <= 1) return;
    BoolMatrix ties_matrix(ties,number_of_ties,number_of_operators-1);
    if(number_of_operators > 1) {
        for(int col = first_column, i = 0; i < number_of_ties; ++col, ++i) {
            ties_matrix(i,0) = expr(*this,O_matrix(col,0) == O_matrix(col+1,0));
        }
    }
    for(int row = 1; row < number_of_operators-1; ++row) {
        for(int col = first_column, i = 0; i < number_of_ties; ++col, ++i) {
            ties_matrix(i,row) = expr(*this,ties_matrix(i,row-1) && (O_matrix(col,row) == O_matrix(col+1,row)));
        }
    }
    for(int row = 1; row < number_of_operators; ++row) {
        for(int col = first_column, i = 0; i < number_of_ties; ++col, ++i) {
            rel(*this,ties_matrix(i,row-1) >> (O_matrix(col,row) >= O_matrix(col+1,row)));
        }
    }
}

ColumnOrderedOperatorSpace::ColumnOrderedOperatorSpace(bool share, ColumnOrderedOperatorSpace& s)
    : OperatorSpace(share,s)
    , number_of_ties(s.number_of_ties)
{
    ties.update(*this,share,s.ties);
}
//@+node:gcross.20101123222425.3377: *3* copy
Space* ColumnOrderedOperatorSpace::copy(bool share)
{
    return new ColumnOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
