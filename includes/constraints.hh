//@+leo-ver=5-thin
//@+node:gcross.20101117113704.1320: * @thin constraints.hh
//@@language cplusplus

#ifndef CONSTRAINTS_HH
#define CONSTRAINTS_HH

//@+<< Includes >>
//@+node:gcross.20101117113704.1321: ** << Includes >>
#include <gecode/set.hh>

#include "operator_space.hh"
//@-<< Includes >>

//@+others
//@+node:gcross.20101117113704.1325: ** Classes
//@+node:gcross.20101118114009.1430: *3* struct ColumnOrderedOperatorSpace
struct ColumnOrderedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101118114009.1431: *4* (fields)
    BoolVarArray ties;
    //@+node:gcross.20101118114009.1432: *4* (constructors)
    ColumnOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    ColumnOrderedOperatorSpace(bool share, OperatorSpace& s);
    //@+node:gcross.20101118114009.1433: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101117133000.1607: *3* Row ordering constraints
//@+node:gcross.20101117133000.1502: *4* struct RowOrderedOperatorSpace
struct RowOrderedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101117133000.1503: *5* (fields)
    BoolVarArray *intrapair_ties, *interpair_ties;
    //@+node:gcross.20101117133000.1504: *5* (constructors)
    RowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    RowOrderedOperatorSpace(bool share, RowOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1510: *5* (methods)
    virtual Space* copy(bool share);
    void postOrderingConstraint(IntVarArgs ordering,BoolVarArray* interpair_ties_,BoolVarArray* intrapair_ties_);
    //@-others

};
//@+node:gcross.20101117133000.1519: *4* struct WeightRowOrderedOperatorSpace
struct WeightRowOrderedOperatorSpace : public virtual RowOrderedOperatorSpace {

    //@+others
    //@+node:gcross.20101117133000.1520: *5* (fields)
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101117133000.1521: *5* (constructors)
    WeightRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    WeightRowOrderedOperatorSpace(bool share, WeightRowOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1522: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101117133000.1551: *4* struct FirstColumnXRowOrderedOperatorSpace
struct FirstColumnXRowOrderedOperatorSpace : public virtual RowOrderedOperatorSpace {

    //@+others
    //@+node:gcross.20101117133000.1552: *5* (fields)
    IntVarArray first_column_X;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101117133000.1553: *5* (constructors)
    FirstColumnXRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    FirstColumnXRowOrderedOperatorSpace(bool share, FirstColumnXRowOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1554: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101117133000.1576: *4* struct WeightAndFirstColumnXRowOrderedOperatorSpace
struct WeightAndFirstColumnXRowOrderedOperatorSpace
    : public WeightRowOrderedOperatorSpace
    , public FirstColumnXRowOrderedOperatorSpace
{

    //@+others
    //@+node:gcross.20101117133000.1578: *5* (constructors)
    WeightAndFirstColumnXRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    WeightAndFirstColumnXRowOrderedOperatorSpace(bool share, WeightAndFirstColumnXRowOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1580: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101118114009.1485: *3* struct AllConstraintsOddRowsOperatorSpace
struct AllConstraintsOddRowsOperatorSpace
    : public WeightAndFirstColumnXRowOrderedOperatorSpace
    , public ColumnOrderedOperatorSpace
{

    //@+others
    //@+node:gcross.20101118114009.1487: *4* (constructors)
    AllConstraintsOddRowsOperatorSpace(int number_of_operators, int number_of_qubits);
    AllConstraintsOddRowsOperatorSpace(bool share, AllConstraintsOddRowsOperatorSpace& s);
    //@+node:gcross.20101118114009.1488: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101118114009.1504: *3* struct AllConstraintsEvenRowsOperatorSpace
struct AllConstraintsEvenRowsOperatorSpace
    : public WeightRowOrderedOperatorSpace
    , public ColumnOrderedOperatorSpace
{

    //@+others
    //@+node:gcross.20101118114009.1505: *4* (constructors)
    AllConstraintsEvenRowsOperatorSpace(int number_of_operators, int number_of_qubits);
    AllConstraintsEvenRowsOperatorSpace(bool share, AllConstraintsEvenRowsOperatorSpace& s);
    //@+node:gcross.20101118114009.1506: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101121135345.1445: *3* struct MinimalWeightOperatorSpace
struct MinimalWeightOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101121135345.1446: *4* (fields)
    int number_of_products;

    BoolVarArray products_X, products_Z, products_non_trivial;
    IntVarArray products_weights;
    //@+node:gcross.20101121135345.1447: *4* (constructors)
    MinimalWeightOperatorSpace(int number_of_operators, int number_of_qubits);
    MinimalWeightOperatorSpace(bool share, MinimalWeightOperatorSpace& s);
    //@+node:gcross.20101121135345.1448: *4* (methods)
    virtual Space* copy(bool share);

    private:

    static int computeNumberOfProducts(int number_of_operators, int number_of_qubits);
    void formProductAndPostConstraints(
        const BoolVarArgs& X1,
        const BoolVarArgs& Z1,
        const IntVar& weight1,
        const BoolVarArgs& X2,
        const BoolVarArgs& Z2,
        const IntVar& weight2,
        const BoolVarArgs& product_X,
        const BoolVarArgs& product_Z,
        const BoolVarArgs& product_non_trivial,
        IntVar& product_weight
    );
    IntVar& getPairOperatorFactor(
        int pair_number, int factor_index,
        BoolVarArgs& X, BoolVarArgs& Z
    );
    void multiplyOperators(
        const BoolVarArgs& Xin1, const BoolVarArgs& Zin1,
        const BoolVarArgs& Xin2, const BoolVarArgs& Zin2,
              BoolVarArgs  Xout,       BoolVarArgs  Zout
    );
    void postWeightConstraints(
        BoolMatrix& products_X_matrix,
        BoolMatrix& products_Z_matrix,
        BoolMatrix& products_non_trivial_matrix,
        int& next_product_number,
        int number_of_factors,
        int next_pair_number,
        const BoolVarArgs& X,
        const BoolVarArgs& Z,
        const IntVar& weight
    );
    //@-others

};
//@+node:gcross.20101117133000.1465: ** Functions
int choose(int n,int k);
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m);
void postColumnXZYOrderingConstraints(OperatorSpace& m);
OperatorSpace* constructConstrainedOperatorSpace(int number_of_qubits,int number_of_operators);
//@-others

#endif
//@-leo
