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
    , ties(*this,(number_of_operators-1)*(number_of_qubits-1),0,1)
{
    IntMatrix O_matrix = getOMatrix();
    BoolMatrix ties_matrix(ties,number_of_qubits-1,number_of_operators-1);
    rel(*this,O_matrix.row(0),IRT_GQ);
    if(number_of_operators > 1) {
        for(int col = 0; col < number_of_qubits-1; ++col) {
            ties_matrix(col,0) = expr(*this,O_matrix(col,0) == O_matrix(col+1,0));
        }
    }
    for(int row = 1; row < number_of_operators-1; ++row) {
        for(int col = 0; col < number_of_qubits-1; ++col) {
            ties_matrix(col,row) = expr(*this,ties_matrix(col,row-1) && (O_matrix(col,row) == O_matrix(col+1,row)));
        }
    }
    for(int row = 1; row < number_of_operators; ++row) {
        for(int col = 0; col < number_of_qubits-1; ++col) {
            rel(*this,ties_matrix(col,row-1) >> (O_matrix(col,row) >= O_matrix(col+1,row)));
        }
    }
}

ColumnOrderedOperatorSpace::ColumnOrderedOperatorSpace(bool share, ColumnOrderedOperatorSpace& s)
    : OperatorSpace(share,s)
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
