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
//@+node:gcross.20101117133000.1507: *3* struct OrderedOperatorSpace
//@+node:gcross.20101117133000.1508: *4* (constructors)
OrderedOperatorSpace::OrderedOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , number_of_pairs(number_of_operators/2)
    , interpair_ties(NULL)
    , intrapair_ties(NULL)
{ }

OrderedOperatorSpace::OrderedOperatorSpace(bool share, OrderedOperatorSpace& s)
    : OperatorSpace(share,s)
    , number_of_pairs(s.number_of_pairs)
{ }
//@+node:gcross.20101117133000.1512: *4* copy
Space* OrderedOperatorSpace::copy(bool share)
{
    return new OrderedOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1513: *4* postOrderingConstraint
void OrderedOperatorSpace::postOrderingConstraint(
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
//@+node:gcross.20101117133000.1527: *3* struct WeightOrderedOperatorSpace
//@+node:gcross.20101117133000.1528: *4* (constructors)
WeightOrderedOperatorSpace::WeightOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits,
    bool exclude_first_column
)
    : OrderedOperatorSpace(number_of_operators,number_of_qubits)
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

WeightOrderedOperatorSpace::WeightOrderedOperatorSpace(bool share, WeightOrderedOperatorSpace& s)
    : OrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{ }
//@+node:gcross.20101117133000.1529: *4* copy
Space* WeightOrderedOperatorSpace::copy(bool share)
{
    return new WeightOrderedOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1558: *3* struct FirstColumnXOrderedOperatorSpace
//@+node:gcross.20101117133000.1559: *4* (constructors)
FirstColumnXOrderedOperatorSpace::FirstColumnXOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : OrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , first_column_X(*this,number_of_operators,0,1)
    , intrapair_ties(*this,number_of_pairs,0,1)
    , interpair_ties(*this,number_of_pairs,0,1)
{
    BoolMatrix X_matrix = getXMatrix();
    for(int i = 0; i < number_of_operators; ++i) channel(*this,X_matrix(i,0),first_column_X[i]);
    postOrderingConstraint(first_column_X,&intrapair_ties,&interpair_ties);
}

FirstColumnXOrderedOperatorSpace::FirstColumnXOrderedOperatorSpace(bool share, FirstColumnXOrderedOperatorSpace& s)
    : OrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{ }
//@+node:gcross.20101117133000.1560: *4* copy
Space* FirstColumnXOrderedOperatorSpace::copy(bool share)
{
    return new FirstColumnXOrderedOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1584: *3* struct WeightAndFirstColumnXOrderedOperatorSpace
//@+node:gcross.20101117133000.1585: *4* (constructors)
WeightAndFirstColumnXOrderedOperatorSpace::WeightAndFirstColumnXOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : WeightOrderedOperatorSpace(number_of_operators,number_of_qubits,true)
    , FirstColumnXOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
{ }

WeightAndFirstColumnXOrderedOperatorSpace::WeightAndFirstColumnXOrderedOperatorSpace(bool share, WeightAndFirstColumnXOrderedOperatorSpace& s)
    : WeightOrderedOperatorSpace(share,s)
    , FirstColumnXOrderedOperatorSpace(share,s)
    , OrderedOperatorSpace(share,s)
    , OperatorSpace(share,s)
{ }
//@+node:gcross.20101117133000.1586: *4* copy
Space* WeightAndFirstColumnXOrderedOperatorSpace::copy(bool share)
{
    return new WeightAndFirstColumnXOrderedOperatorSpace(share,*this);
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
