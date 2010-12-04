//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2656: * @thin minimal_weight.hh
//@@language cplusplus

#ifndef CONSTRAINTS_MINIMAL_WEIGHT_HH
#define CONSTRAINTS_MINIMAL_WEIGHT_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2657: ** << Includes >>
#include <gecode/set.hh>
#include <utility>
#include <vector>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.2691: ** struct MinimalWeightOperatorSpace
struct MinimalWeightOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2692: *3* (fields)
    int maximum_number_of_factors, number_of_products, number_of_variables;

    BoolVarArray products_X, products_Z, products_non_trivial;
    IntVarArray products_weights, products_minimum_weights;
    //@+node:gcross.20101123222425.2693: *3* (constructors)
    MinimalWeightOperatorSpace(int number_of_operators, int number_of_qubits, optional<int> minimum_weight=none);
    MinimalWeightOperatorSpace(bool share, MinimalWeightOperatorSpace& s);
    //@+node:gcross.20101123222425.2694: *3* (methods)
    virtual Space* copy(bool share);

    private:

    int computeNumberOfProducts();
    void formProductAndPostConstraints(
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
    );
    std::pair<const IntVar*,int> getPairOperatorFactor(
        int pair_number, int factor_index,
        BoolVarArgs& X, BoolVarArgs& Z
    );
    void multiplyOperators(
        const BoolVarArgs& Xin1, const BoolVarArgs& Zin1,
        const BoolVarArgs& Xin2, const BoolVarArgs& Zin2,
        const BoolVarArgs& Xout, const BoolVarArgs& Zout
    );
    void postWeightConstraints(
        BoolMatrix& products_X_matrix,
        BoolMatrix& products_Z_matrix,
        int& next_product_number,
        std::vector<int>& product_weight_adjustments,
        int number_of_factors,
        int next_pair_number,
        const BoolVarArgs& X,
        const BoolVarArgs& Z,
        const IntVar& minimal_weight,
        int weight_adjustment
    );
    //@-others

};
//@-others

}

#endif
//@-leo
