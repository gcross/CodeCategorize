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
//@+node:gcross.20101118114009.1445: *3* struct ColumnOrderedOperatorSpace
//@+node:gcross.20101118114009.1446: *4* (constructors)
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
    for(int row = 1; row < number_of_operators; ++row) {
        for(int col = 0; col < number_of_qubits-1; ++col) {
            rel(*this,ties_matrix(col,row-1) >> (O_matrix(col,row) >= O_matrix(col+1,row)));
        }
        if(row < number_of_operators-1) {
            for(int col = 0; col < number_of_qubits-1; ++col) {
                ties_matrix(col,row) = expr(*this,ties_matrix(col,row) && (O_matrix(col,row) == O_matrix(col+1,row)));
            }
        }
    }
}

ColumnOrderedOperatorSpace::ColumnOrderedOperatorSpace(bool share, OperatorSpace& s)
    : OperatorSpace(share,s)
{
}
//@+node:gcross.20101118114009.1447: *4* copy
Space* ColumnOrderedOperatorSpace::copy(bool share)
{
    return new ColumnOrderedOperatorSpace(share,*this);
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
        weights[i] = expr(*this,sum(non_trivial_matrix.slice(first_column,number_of_qubits,i,i+1)));
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
    for(int i = 0; i < number_of_operators; ++i) channel(*this,X_matrix(0,i),first_column_X[i]);
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
//@+node:gcross.20101118114009.1492: *3* struct AllConstraintsOddRowsOperatorSpace
//@+node:gcross.20101118114009.1493: *4* (constructors)
AllConstraintsOddRowsOperatorSpace::AllConstraintsOddRowsOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , WeightAndFirstColumnXRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnOrderedOperatorSpace(number_of_operators,number_of_qubits)
{
    assert(number_of_operators % 2 == 1);
    postColumnXZYOrderingConstraints(*this);
}

AllConstraintsOddRowsOperatorSpace::AllConstraintsOddRowsOperatorSpace(bool share, AllConstraintsOddRowsOperatorSpace& s)
    : OperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , WeightAndFirstColumnXRowOrderedOperatorSpace(share,s)
    , ColumnOrderedOperatorSpace(share,s)
{
}
//@+node:gcross.20101118114009.1494: *4* copy
Space* AllConstraintsOddRowsOperatorSpace::copy(bool share)
{
    return new AllConstraintsOddRowsOperatorSpace(share,*this);
}
//@+node:gcross.20101118114009.1498: *3* struct AllConstraintsEvenRowsOperatorSpace
//@+node:gcross.20101118114009.1499: *4* (constructors)
AllConstraintsEvenRowsOperatorSpace::AllConstraintsEvenRowsOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , WeightRowOrderedOperatorSpace(number_of_operators,number_of_qubits,false)
    , ColumnOrderedOperatorSpace(number_of_operators,number_of_qubits)
{
    assert(number_of_operators % 2 == 0);
    postColumnXZYOrderingConstraints(*this);
}

AllConstraintsEvenRowsOperatorSpace::AllConstraintsEvenRowsOperatorSpace(bool share, AllConstraintsEvenRowsOperatorSpace& s)
    : OperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , WeightRowOrderedOperatorSpace(share,s)
    , ColumnOrderedOperatorSpace(share,s)
{
}
//@+node:gcross.20101118114009.1500: *4* copy
Space* AllConstraintsEvenRowsOperatorSpace::copy(bool share)
{
    return new AllConstraintsEvenRowsOperatorSpace(share,*this);
}
//@+node:gcross.20101117133000.1469: ** Functions
//@+node:gcross.20101117133000.1470: *3* postFirstColumnSpecialCaseConstraint
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m) {
    rel(m,m.getOMatrix()(0,m.number_of_operators-1) == Z);
    BoolMatrix Z_matrix = m.getZMatrix();
    for(int row = 0; row < m.number_of_operators-1; ++row) rel(m,Z_matrix(0,row) == 0);
}
//@+node:gcross.20101117133000.1622: *3* postColumnXZYOrderingConstraints
void postColumnXZYOrderingConstraints(OperatorSpace& m) {
    static DFA::Transition t[] =
        {{0,0,0}
        ,{0,1,1}
        ,{1,0,1}
        ,{1,1,1}
        ,{1,2,2}
        ,{2,0,2}
        ,{2,1,2}
        ,{2,2,2}
        ,{2,3,3}
        ,{3,0,3}
        ,{3,1,3}
        ,{3,2,3}
        ,{3,3,3}
        ,{-1,-1,-1}
        };
    static int f[] = {2,3,-1};
    static DFA d(0,t,f);

    IntMatrix O_matrix = m.getOMatrix();
    for(int i = 0; i < m.number_of_qubits; ++i) extensional(m,O_matrix.col(i),d);
}
//@+node:gcross.20101118114009.1509: *3* constructConstrainedOperatorSpace
OperatorSpace* constructConstrainedOperatorSpace(int number_of_qubits,int number_of_operators) {
    return number_of_operators % 2 == 0
        ? dynamic_cast<OperatorSpace*>(
            new AllConstraintsEvenRowsOperatorSpace(number_of_operators,number_of_qubits-number_of_operators/2)
          )
        : dynamic_cast<OperatorSpace*>(
            new AllConstraintsOddRowsOperatorSpace(number_of_operators,number_of_qubits-number_of_operators/2)
          )
        ;
}
//@-others
//@-leo
