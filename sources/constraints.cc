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
    , interpair_ties(NULL)
    , intrapair_ties(NULL)
{ }

RowOrderedOperatorSpace::RowOrderedOperatorSpace(bool share, RowOrderedOperatorSpace& s)
    : OperatorSpace(share,s)
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
    int number_of_qubits
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , intrapair_ties(*this,number_of_pairs,0,1)
    , interpair_ties(*this,number_of_pairs,0,1)
{
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
    : WeightRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
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
    , MinimalWeightOperatorSpace(number_of_operators,number_of_qubits)
{
    assert(number_of_operators % 2 == 1);
    postFirstColumnSpecialCaseConstraint(*this);
    postColumnXZYOrderingConstraints(*this);
}

AllConstraintsOddRowsOperatorSpace::AllConstraintsOddRowsOperatorSpace(bool share, AllConstraintsOddRowsOperatorSpace& s)
    : OperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , WeightAndFirstColumnXRowOrderedOperatorSpace(share,s)
    , ColumnOrderedOperatorSpace(share,s)
    , MinimalWeightOperatorSpace(share,s)
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
    , WeightRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , MinimalWeightOperatorSpace(number_of_operators,number_of_qubits)
{
    assert(number_of_operators % 2 == 0);
    postColumnXZYOrderingConstraints(*this);
}

AllConstraintsEvenRowsOperatorSpace::AllConstraintsEvenRowsOperatorSpace(bool share, AllConstraintsEvenRowsOperatorSpace& s)
    : OperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , WeightRowOrderedOperatorSpace(share,s)
    , ColumnOrderedOperatorSpace(share,s)
    , MinimalWeightOperatorSpace(share,s)
{
}
//@+node:gcross.20101118114009.1500: *4* copy
Space* AllConstraintsEvenRowsOperatorSpace::copy(bool share)
{
    return new AllConstraintsEvenRowsOperatorSpace(share,*this);
}
//@+node:gcross.20101121135345.1456: *3* struct MinimalWeightOperatorSpace
//@+node:gcross.20101121200631.4179: *4* (constructors)
MinimalWeightOperatorSpace::MinimalWeightOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , number_of_products(computeNumberOfProducts(number_of_operators,number_of_qubits))
    , number_of_variables(number_of_qubits*number_of_products)
    , maximum_number_of_factors(min(number_of_qubits,number_of_products))
    , products_X(*this,number_of_variables,0,1)
    , products_Z(*this,number_of_variables,0,1)
    , products_non_trivial(*this,number_of_variables,0,1)
    , products_weights(*this,number_of_products,0,number_of_qubits)
{
    for(int i = 0; i < number_of_variables; ++i) {
        products_non_trivial[i] = expr(*this,products_Z[i] || products_X[i]);
    }
    BoolMatrix products_non_trivial_matrix(products_non_trivial,number_of_qubits,number_of_products);
    for(int i = 0; i < number_of_products; ++i) {
        linear(*this,products_non_trivial_matrix.row(i),IRT_EQ,products_weights[i]);
    }

    BoolMatrix products_X_matrix(products_X,number_of_qubits,number_of_products),
               products_Z_matrix(products_Z,number_of_qubits,number_of_products),
               X_matrix = getXMatrix(),
               Z_matrix = getZMatrix();
    vector<int> product_weight_adjustments;
    for(int i = 0; i < number_of_pairs; ++i) {
        formProductAndPostConstraints(
            X_matrix.row (2*i+0),
            Z_matrix.row (2*i+0),
            weights      [2*i+0],
            1,
            X_matrix.row (2*i+1),
            Z_matrix.row (2*i+1),
            weights      [2*i+1],
            1,
            products_X_matrix.row(i),
            products_Z_matrix.row(i),
            products_weights[i],
            1
        );
        product_weight_adjustments.push_back(1);
    }
    int next_product_number = number_of_pairs;
    if(maximum_number_of_factors > 1) {
        for(int pair_number = 0; pair_number < number_of_pairs; ++pair_number) {
            for(int factor_index = 0; factor_index < 3; ++factor_index) {
                BoolVarArgs factor_X, factor_Z;
                IntVar& factor_weight = getPairOperatorFactor(pair_number,factor_index,factor_X,factor_Z);
                postWeightConstraints(
                    products_X_matrix,
                    products_Z_matrix,
                    next_product_number,
                    product_weight_adjustments,
                    2,
                    pair_number+1,
                    factor_X,
                    factor_Z,
                    factor_weight
                );
            }
        }
    }
    if(number_of_operators % 2 == 1) {
        BoolVarArgs last_operator_X = X_matrix.row(number_of_operators-1),
                    last_operator_Z = Z_matrix.row(number_of_operators-1);
        IntVar&     last_operator_weight = weights[number_of_operators-1];
        int number_of_products_without_last_operator = next_product_number;
        for(int i = 0; i < number_of_products_without_last_operator; ++i, ++next_product_number) {
            formProductAndPostConstraints(
                last_operator_X,
                last_operator_Z,
                last_operator_weight,
                0,
                products_X_matrix.row(i),
                products_Z_matrix.row(i),
                products_weights[i],
                product_weight_adjustments[i],
                products_X_matrix.row(next_product_number),
                products_Z_matrix.row(next_product_number),
                products_weights[next_product_number],
                product_weight_adjustments[i]
            );
        }
        for(int i = 0; i < number_of_operators-1; ++i, ++next_product_number) {
            formProductAndPostConstraints(
                last_operator_X,
                last_operator_Z,
                last_operator_weight,
                0,
                X_matrix.row(i),
                Z_matrix.row(i),
                weights[i],
                1,
                products_X_matrix.row(next_product_number),
                products_Z_matrix.row(next_product_number),
                products_weights[next_product_number],
                1
            );
        }
    }
    assert(next_product_number == number_of_products);
}

MinimalWeightOperatorSpace::MinimalWeightOperatorSpace(bool share, MinimalWeightOperatorSpace& s)
    : OperatorSpace(share,s)
    , number_of_products(s.number_of_products)
    , number_of_variables(s.number_of_variables)
    , maximum_number_of_factors(s.maximum_number_of_factors)
{
    products_X.update(*this,share,s.products_X);
    products_Z.update(*this,share,s.products_Z);
    products_non_trivial.update(*this,share,s.products_non_trivial);
    products_weights.update(*this,share,s.products_weights);
}
//@+node:gcross.20101121135345.1458: *4* computeNumberOfProducts
int MinimalWeightOperatorSpace::computeNumberOfProducts(int number_of_operators, int number_of_qubits) {
    int number_of_pairs = number_of_operators / 2;
    int number_of_products = number_of_pairs;
    for(int k = 2; k <= min(number_of_pairs,number_of_qubits); ++k) {
        int x = choose(number_of_pairs,k);
        for(int i = 0; i < k; ++i) x *= 3;
        number_of_products += x;
    }
    if(number_of_operators % 2 == 1) {
        number_of_products *= 2;
        number_of_products += number_of_operators-1;
    }
    return number_of_products;
}
//@+node:gcross.20101121135345.1459: *4* copy
Space* MinimalWeightOperatorSpace::MinimalWeightOperatorSpace::copy(bool share)
{
    return new MinimalWeightOperatorSpace(share,*this);
}
//@+node:gcross.20101121135345.1460: *4* formProductsAndPostConstraints
void MinimalWeightOperatorSpace::formProductAndPostConstraints(
    const BoolVarArgs& X1,
    const BoolVarArgs& Z1,
    const IntVar& weight1,
    const int weight_adjustment1,
    const BoolVarArgs& X2,
    const BoolVarArgs& Z2,
    const IntVar& weight2,
    const int weight_adjustment2,
    const BoolVarArgs& product_X,
    const BoolVarArgs& product_Z,
    IntVar& product_weight,
    const int product_weight_adjustment
) {
    multiplyOperators(X1,Z1,X2,Z2,product_X,product_Z);
    rel(*this,product_weight+product_weight_adjustment >= Gecode::min(weight1+weight_adjustment1,weight2+weight_adjustment2));
}
//@+node:gcross.20101121135345.1461: *4* getPairOperatorFactor
IntVar& MinimalWeightOperatorSpace::getPairOperatorFactor(
    int pair_number, int factor_index,
    BoolVarArgs& X, BoolVarArgs& Z
) {
    switch(factor_index) {
        case 0:
        case 1:
            X = getXMatrix().row(2*pair_number+factor_index);
            Z = getZMatrix().row(2*pair_number+factor_index);
            return weights[2*pair_number+factor_index];
            break;
        case 2:
            {
                BoolMatrix products_X_matrix(products_X,number_of_qubits,number_of_products),
                           products_Z_matrix(products_Z,number_of_qubits,number_of_products);
                X = products_X_matrix.row(pair_number);
                Z = products_Z_matrix.row(pair_number);
                return products_weights[pair_number];
            }
            break;
    }
}
//@+node:gcross.20101121135345.1464: *4* multiplyOperators
void MinimalWeightOperatorSpace::multiplyOperators(
    const BoolVarArgs& Xin1, const BoolVarArgs& Zin1,
    const BoolVarArgs& Xin2, const BoolVarArgs& Zin2,
    const BoolVarArgs& Xout, const BoolVarArgs& Zout
) {
    for(int i = 0; i < Xin1.size(); ++i) {
        rel(*this,Xout[i] == Xin1[i]^Xin2[i]);
        rel(*this,Zout[i] == Zin1[i]^Zin2[i]);
    }
}
//@+node:gcross.20101121135345.1462: *4* postWeightConstraints
void MinimalWeightOperatorSpace::postWeightConstraints(
    BoolMatrix& products_X_matrix,
    BoolMatrix& products_Z_matrix,
    int& next_product_number,
    vector<int>& product_weight_adjustments,
    int number_of_factors,
    int next_pair_number,
    const BoolVarArgs& X,
    const BoolVarArgs& Z,
    const IntVar& weight
) {
    for(int pair_number = next_pair_number; pair_number < number_of_pairs; ++pair_number) {
        for(int factor_index = 0; factor_index < 3; ++factor_index) {
            assert(next_product_number < number_of_products);
            BoolVarArgs product_X = products_X_matrix.row(next_product_number),
                        product_Z = products_Z_matrix.row(next_product_number);
            IntVar&     product_weight = products_weights[next_product_number];
            BoolVarArgs factor_X, factor_Z;
            IntVar&     factor_weight = getPairOperatorFactor(pair_number,factor_index,factor_X,factor_Z);
            formProductAndPostConstraints(
                X,
                Z,
                weight,
                number_of_factors-1,
                factor_X,
                factor_Z,
                factor_weight,
                1,
                product_X,
                product_Z,
                product_weight,
                number_of_factors
            );
            product_weight_adjustments.push_back(number_of_factors);
            ++next_product_number;
            if(number_of_factors < maximum_number_of_factors) {
                postWeightConstraints(
                    products_X_matrix,
                    products_Z_matrix,
                    next_product_number,
                    product_weight_adjustments,
                    number_of_factors+1,
                    pair_number+1,
                    product_X,
                    product_Z,
                    product_weight
                );
            }
        }
    }
}
//@+node:gcross.20101117133000.1469: ** Functions
//@+node:gcross.20101121135345.1466: *3* choose
int choose(int n,int k) {
    long total = 1;
    for(int i = n; i > n-k; --i) total *= i;
    for(int i = 1; i <= k; ++i) total /= i;
    int total_as_int = (int)total;
    assert(total_as_int == total);
    return total;
}
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
