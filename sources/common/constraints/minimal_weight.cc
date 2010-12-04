//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3566: * @thin minimal_weight.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3567: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/minimal_weight.hh"
#include "utilities.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3595: ** struct MinimalWeightOperatorSpace
//@+node:gcross.20101123222425.3596: *3* (constructors)
MinimalWeightOperatorSpace::MinimalWeightOperatorSpace(int number_of_operators, int number_of_qubits, optional<int> maximum_weight)
    : OperatorSpace(number_of_operators,number_of_qubits,maximum_weight)
    , maximum_number_of_factors(maximum_weight ? min(number_of_qubits,*maximum_weight) : number_of_qubits)
    , number_of_products(computeNumberOfProducts())
    , number_of_variables(number_of_qubits*number_of_products)
    , products_X(*this,number_of_variables,0,1)
    , products_Z(*this,number_of_variables,0,1)
    , products_non_trivial(*this,number_of_variables,0,1)
    , products_weights(*this,number_of_products,0,number_of_qubits)
    , products_minimum_weights(*this,number_of_products,0,number_of_qubits+number_of_pairs)
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
            products_minimum_weights[i],
            1
        );
        product_weight_adjustments.push_back(1);
    }
    int next_product_number = number_of_pairs;
    if(maximum_number_of_factors > 1) {
        for(int pair_number = 0; pair_number < number_of_pairs; ++pair_number) {
            for(int factor_index = 0; factor_index < 3; ++factor_index) {
                BoolVarArgs factor_X, factor_Z;
                pair<const IntVar*,int> factor_weight_info = getPairOperatorFactor(pair_number,factor_index,factor_X,factor_Z);
                postWeightConstraints(
                    products_X_matrix,
                    products_Z_matrix,
                    next_product_number,
                    product_weight_adjustments,
                    2,
                    pair_number+1,
                    factor_X,
                    factor_Z,
                    *(factor_weight_info.first),
                    factor_weight_info.second
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
                products_minimum_weights[i],
                0,
                products_X_matrix.row(next_product_number),
                products_Z_matrix.row(next_product_number),
                products_weights[next_product_number],
                products_minimum_weights[next_product_number],
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
                products_minimum_weights[next_product_number],
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
    products_minimum_weights.update(*this,share,s.products_weights);
}
//@+node:gcross.20101123222425.3597: *3* computeNumberOfProducts
int MinimalWeightOperatorSpace::computeNumberOfProducts() {
    int number_of_products = number_of_pairs;
    for(int k = 2; k <= maximum_number_of_factors; ++k) {
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
//@+node:gcross.20101123222425.3598: *3* copy
Space* MinimalWeightOperatorSpace::MinimalWeightOperatorSpace::copy(bool share)
{
    return new MinimalWeightOperatorSpace(share,*this);
}
//@+node:gcross.20101123222425.3599: *3* formProductsAndPostConstraints
void MinimalWeightOperatorSpace::formProductAndPostConstraints(
    const BoolVarArgs& X1,
    const BoolVarArgs& Z1,
    const IntVar& minimal_weight1,
    const int weight_adjustment1,
    const BoolVarArgs& X2,
    const BoolVarArgs& Z2,
    const IntVar& minimal_weight2,
    const int weight_adjustment2,
    const BoolVarArgs& product_X,
    const BoolVarArgs& product_Z,
    IntVar& product_weight,
    IntVar& product_minimal_weight,
    const int product_weight_adjustment
) {
    multiplyOperators(X1,Z1,X2,Z2,product_X,product_Z);
    product_minimal_weight = expr(*this,Gecode::min(minimal_weight1+weight_adjustment1,minimal_weight2+weight_adjustment2));
    rel(*this,product_weight+product_weight_adjustment >= product_minimal_weight);
}
//@+node:gcross.20101123222425.3600: *3* getPairOperatorFactor
pair<const IntVar*,int> MinimalWeightOperatorSpace::getPairOperatorFactor(
    int pair_number, int factor_index,
    BoolVarArgs& X, BoolVarArgs& Z
) {
    switch(factor_index) {
        case 0:
        case 1:
            X = getXMatrix().row(2*pair_number+factor_index);
            Z = getZMatrix().row(2*pair_number+factor_index);
            return make_pair(&weights[2*pair_number+factor_index],1);
            break;
        case 2:
            {
                BoolMatrix products_X_matrix(products_X,number_of_qubits,number_of_products),
                           products_Z_matrix(products_Z,number_of_qubits,number_of_products);
                X = products_X_matrix.row(pair_number);
                Z = products_Z_matrix.row(pair_number);
                return make_pair(&products_minimum_weights[pair_number],0);
            }
            break;
    }
}
//@+node:gcross.20101123222425.3601: *3* multiplyOperators
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
//@+node:gcross.20101123222425.3602: *3* postWeightConstraints
void MinimalWeightOperatorSpace::postWeightConstraints(
    BoolMatrix& products_X_matrix,
    BoolMatrix& products_Z_matrix,
    int& next_product_number,
    vector<int>& product_weight_adjustments,
    int number_of_factors,
    int next_pair_number,
    const BoolVarArgs& X,
    const BoolVarArgs& Z,
    const IntVar& minimal_weight,
    int weight_adjustment
) {
    for(int pair_number = next_pair_number; pair_number < number_of_pairs; ++pair_number) {
        for(int factor_index = 0; factor_index < 3; ++factor_index) {
            assert(next_product_number < number_of_products);
            BoolVarArgs product_X = products_X_matrix.row(next_product_number),
                        product_Z = products_Z_matrix.row(next_product_number);
            IntVar&     product_weight = products_weights[next_product_number],
                        product_minimal_weight = products_weights[next_product_number];
            BoolVarArgs factor_X, factor_Z;
            pair<const IntVar*,int> factor_weight_info = getPairOperatorFactor(pair_number,factor_index,factor_X,factor_Z);
            formProductAndPostConstraints(
                X,
                Z,
                minimal_weight,
                weight_adjustment,
                factor_X,
                factor_Z,
                *(factor_weight_info.first),
                factor_weight_info.second,
                product_X,
                product_Z,
                product_weight,
                product_minimal_weight,
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
                    product_minimal_weight,
                    0
                );
            }
        }
    }
}
//@-others

}
//@-leo
