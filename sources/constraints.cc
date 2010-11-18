//@+leo-ver=5-thin
//@+node:gcross.20101117113704.1319: * @thin constraints.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117113704.1322: ** << Includes >>
#include <gecode/minimodel.hh>
#include <vector>

#include "constraints.hh"

using namespace std;
//@-<< Includes >>

//@+others
//@+node:gcross.20101117133000.1506: ** Classes
//@+node:gcross.20101117133000.1334: *3* struct CompleteColumnsOperatorSpace
//@+node:gcross.20101117133000.1336: *4* (constructors)
CompleteColumnsOperatorSpace::CompleteColumnsOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , column_operator_sets(*this,number_of_qubits,IntSet::empty,IntSet(0,3),0,4)
{
    IntMatrix O_matrix = getOMatrix();
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
//@+node:gcross.20101117133000.1339: *4* copy
Space* CompleteColumnsOperatorSpace::copy(bool share)
{
    return new CompleteColumnsOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1600: *3* Row ordering constraints
//@+node:gcross.20101117133000.1507: *4* struct RowOrderedOperatorSpace
//@+node:gcross.20101117133000.1508: *5* (constructors)
RowOrderedOperatorSpace::RowOrderedOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , number_of_pairs(number_of_operators/2)
    , interpair_ties(NULL)
    , intrapair_ties(NULL)
{ }

RowOrderedOperatorSpace::RowOrderedOperatorSpace(bool share, RowOrderedOperatorSpace& s)
    : OperatorSpace(share,s)
    , number_of_pairs(s.number_of_pairs)
{ }
//@+node:gcross.20101117133000.1512: *5* copy
Space* RowOrderedOperatorSpace::copy(bool share)
{
    return new RowOrderedOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1513: *5* postOrderingConstraint
void RowOrderedOperatorSpace::postOrderingConstraint(
    IntVarArgs ordering
   ,BoolVarArray* interpair_ties_
   ,BoolVarArray* intrapair_ties_
) {
    if(interpair_ties == NULL) {
        assert(interpair_ties == NULL);
        for(int i = 0; i < number_of_pairs; ++i) {
            rel(*this,ordering[2*i] >= ordering[2*i+1]);
        }
        for(int i = 0; i < number_of_pairs-1; ++i) {
            rel(*this,ordering[i] >= ordering[i+2]);
            rel(*this,(ordering[2*i+0] == ordering[2*(i+1)+0])
                   >> (ordering[2*i+1] >= ordering[2*(i+1)+1])
            );
        }
    } else {
        assert(interpair_ties != NULL);
        for(int i = 0; i < number_of_pairs; ++i) {
            rel(*this,(*intrapair_ties)[i] >> (ordering[2*i] >= ordering[2*i+1]));
        }
        for(int i = 0; i < number_of_pairs-1; ++i) {
            rel(*this,(*interpair_ties)[i] >> (ordering[i] >= ordering[i+2]));
            rel(*this,(*interpair_ties)[i] >> (
                      (ordering[2*i+0] == ordering[2*(i+1)+0])
                   >> (ordering[2*i+1] >= ordering[2*(i+1)+1])
            ));
        }
    }
    for(int i = 0; i < number_of_pairs; ++i) {
        (*intrapair_ties_)[i] = expr(*this,ordering[2*i]==ordering[2*i+1]);
    }
    for(int i = 0; i < number_of_pairs-1; ++i) {
        (*interpair_ties_)[i] = expr(*this,
                  (ordering[2*i+0] == ordering[2*(i+1)+0])
               && (ordering[2*i+1] == ordering[2*(i+1)+1])
        );
    }
    interpair_ties = interpair_ties_;
    intrapair_ties = intrapair_ties_;
}
//@+node:gcross.20101117133000.1527: *4* struct WeightRowOrderedOperatorSpace
//@+node:gcross.20101117133000.1528: *5* (constructors)
WeightRowOrderedOperatorSpace::WeightRowOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits,
    bool exclude_first_column
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , weights(*this,number_of_operators,0,number_of_qubits)
    , intrapair_ties(*this,number_of_pairs,0,1)
    , interpair_ties(*this,number_of_pairs,0,1)
{
    BoolMatrix non_trivial_matrix = getNonTrivialMatrix();
    int first_column = exclude_first_column ? 1 : 0;
    for(int i = 0; i < number_of_operators; ++i) {
        weights[i] = expr(*this,sum(non_trivial_matrix.slice(i,i+1,first_column,number_of_qubits)));
    }
    postOrderingConstraint(weights,&intrapair_ties,&interpair_ties);
}

WeightRowOrderedOperatorSpace::WeightRowOrderedOperatorSpace(bool share, WeightRowOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{ }
//@+node:gcross.20101117133000.1529: *5* copy
Space* WeightRowOrderedOperatorSpace::copy(bool share)
{
    return new WeightRowOrderedOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1558: *4* struct FirstColumnXRowOrderedOperatorSpace
//@+node:gcross.20101117133000.1559: *5* (constructors)
FirstColumnXRowOrderedOperatorSpace::FirstColumnXRowOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , first_column_X(*this,number_of_operators,0,1)
    , intrapair_ties(*this,number_of_pairs,0,1)
    , interpair_ties(*this,number_of_pairs,0,1)
{
    BoolMatrix X_matrix = getXMatrix();
    for(int i = 0; i < number_of_operators; ++i) channel(*this,X_matrix(i,0),first_column_X[i]);
    postOrderingConstraint(first_column_X,&intrapair_ties,&interpair_ties);
}

FirstColumnXRowOrderedOperatorSpace::FirstColumnXRowOrderedOperatorSpace(bool share, FirstColumnXRowOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{ }
//@+node:gcross.20101117133000.1560: *5* copy
Space* FirstColumnXRowOrderedOperatorSpace::copy(bool share)
{
    return new FirstColumnXRowOrderedOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1584: *4* struct WeightAndFirstColumnXRowOrderedOperatorSpace
//@+node:gcross.20101117133000.1585: *5* (constructors)
WeightAndFirstColumnXRowOrderedOperatorSpace::WeightAndFirstColumnXRowOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : WeightRowOrderedOperatorSpace(number_of_operators,number_of_qubits,true)
    , FirstColumnXRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
{ }

WeightAndFirstColumnXRowOrderedOperatorSpace::WeightAndFirstColumnXRowOrderedOperatorSpace(bool share, WeightAndFirstColumnXRowOrderedOperatorSpace& s)
    : WeightRowOrderedOperatorSpace(share,s)
    , FirstColumnXRowOrderedOperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{ }
//@+node:gcross.20101117133000.1586: *5* copy
Space* WeightAndFirstColumnXRowOrderedOperatorSpace::copy(bool share)
{
    return new WeightAndFirstColumnXRowOrderedOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1469: ** Functions
//@+node:gcross.20101117133000.1470: *3* postFirstColumnSpecialCaseConstraint
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m) {
    rel(m,m.getOMatrix()(m.number_of_operators-1,0) == Z);
    BoolMatrix Z_matrix = m.getZMatrix();
    for(int row = 0; row < m.number_of_operators-1; ++row) rel(m,Z_matrix(row,0) == 0);
}
//@-others
//@-leo
