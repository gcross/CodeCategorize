//@+leo-ver=5-thin
//@+node:gcross.20101117113704.1319: * @thin constraints.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117113704.1322: ** << Includes >>
#include "gecode/minimodel.hh"

#include "constraints.hh"
//@-<< Includes >>

//@+others
//@+node:gcross.20101117133000.1334: ** struct CompleteColumnsOperatorSpace
//@+node:gcross.20101117133000.1336: *3* (constructors)
CompleteColumnsOperatorSpace::CompleteColumnsOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , column_operator_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,3),0,4)
{
    OMatrix O_matrix = getOMatrix();
    for(int column = 0; column < number_of_qubits; ++column) {
        IntVarArgs O_column;
        for(int row = 0; row < number_of_operators; ++row) {
            O_column << O_matrix(row,column);
        }
        channel(*this,O_column,column_operator_sets[column]);
        rel(*this,cardinality(column_operator_sets[column] - singleton(0)) >= 2);
    }
}

CompleteColumnsOperatorSpace::CompleteColumnsOperatorSpace(bool share, CompleteColumnsOperatorSpace& s)
    : OperatorSpace(share,s)
{
    column_operator_sets.update(*this,share,s.column_operator_sets);
}
//@+node:gcross.20101117133000.1339: *3* (methods)
Space* CompleteColumnsOperatorSpace::copy(bool share)
{
    return new CompleteColumnsOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1469: ** Functions
//@+node:gcross.20101117133000.1470: *3* postFirstColumnSpecialCaseConstraint
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m) {
    rel(m,m.getOMatrix()(m.number_of_operators-1,0) == Z);
    ZMatrix Z_matrix = m.getZMatrix();
    for(int row = 0; row < m.number_of_operators-1; ++row) rel(m,Z_matrix(row,0) == 0);
}
//@-others
//@-leo
