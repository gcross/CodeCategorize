//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2748: * @thin constraints.hh
//@@language cplusplus

#ifndef CONSTRAINTS_HH
#define CONSTRAINTS_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2749: ** << Includes >>
#include <gecode/set.hh>
#include <utility>
#include <vector>

#include "operator_space.hh"
//@-<< Includes >>

//@+others
//@+node:gcross.20101123222425.2750: ** Classes
//@+node:gcross.20101123222425.2751: *3* struct ColumnOrderedOperatorSpace
struct ColumnOrderedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2752: *4* (fields)
    BoolVarArray ties;
    //@+node:gcross.20101123222425.2753: *4* (constructors)
    ColumnOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    ColumnOrderedOperatorSpace(bool share, ColumnOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2754: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2755: *3* struct CommutatorOperatorSpace
struct CommutatorOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2756: *4* (fields)
    int number_of_commutators;

    BoolVarArray anti_commuting_qubits, anti_commuting_operators;
    IntVarArray anti_commuting_qubit_counts_minus_hidden_qubits, anti_commuting_qubit_counts;
    //@+node:gcross.20101123222425.2757: *4* (constructors)
    CommutatorOperatorSpace(int number_of_operators, int number_of_qubits);
    CommutatorOperatorSpace(bool share, CommutatorOperatorSpace& s);
    //@+node:gcross.20101123222425.2758: *4* (methods)
    virtual Space* copy(bool share);
    BoolMatrix getAntiCommutatorMatrix() { return BoolMatrix(anti_commuting_operators,number_of_operators,number_of_operators); }
    IntMatrix getAntiCommutingQubitCountsMatrix() { return IntMatrix(anti_commuting_qubit_counts,number_of_operators,number_of_operators); }
    IntMatrix getAntiCommutingQubitCountsMinusHiddenQubitsMatrix() { return IntMatrix(anti_commuting_qubit_counts_minus_hidden_qubits,number_of_operators,number_of_operators); }
    //@-others

};
//@+node:gcross.20101123222425.2759: *3* Row ordering constraints
//@+node:gcross.20101123222425.2760: *4* struct RowOrderedOperatorSpace
struct RowOrderedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2761: *5* (fields)
    BoolVarArgs intrapair_ties, interpair_ties;
    //@+node:gcross.20101123222425.2762: *5* (constructors)
    RowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    RowOrderedOperatorSpace(bool share, RowOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2763: *5* (methods)
    virtual Space* copy(bool share);
    void postOrderingConstraint(const IntVarArgs& ordering,BoolVarArgs interpair_ties_,BoolVarArgs intrapair_ties_);
    //@-others

};
//@+node:gcross.20101123222425.2764: *4* struct WeightRowOrderedOperatorSpace
struct WeightRowOrderedOperatorSpace : public virtual RowOrderedOperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2765: *5* (fields)
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.2766: *5* (constructors)
    WeightRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    WeightRowOrderedOperatorSpace(bool share, WeightRowOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2767: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2768: *4* struct FirstColumnXRowOrderedOperatorSpace
struct FirstColumnXRowOrderedOperatorSpace : public virtual RowOrderedOperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2769: *5* (fields)
    IntVarArray first_column_X;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.2770: *5* (constructors)
    FirstColumnXRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    FirstColumnXRowOrderedOperatorSpace(bool share, FirstColumnXRowOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2771: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2772: *4* struct WeightAndFirstColumnXRowOrderedOperatorSpace
struct WeightAndFirstColumnXRowOrderedOperatorSpace
    : public WeightRowOrderedOperatorSpace
    , public FirstColumnXRowOrderedOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.2773: *5* (constructors)
    WeightAndFirstColumnXRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    WeightAndFirstColumnXRowOrderedOperatorSpace(bool share, WeightAndFirstColumnXRowOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2774: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2775: *4* struct AntiCommutatorCountOrderedOperatorSpace
struct AntiCommutatorCountOrderedOperatorSpace
    : public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.2776: *5* (fields)
    IntVarArray number_of_anti_commuting_operators;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.2777: *5* (constructors)
    AntiCommutatorCountOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    AntiCommutatorCountOrderedOperatorSpace(bool share, AntiCommutatorCountOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2778: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2779: *4* struct AntiCommutatorQubitCountSequenceOrderedOperatorSpace
struct AntiCommutatorQubitCountSequenceOrderedOperatorSpace
    : public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.2780: *5* (fields)
    IntVarArray sorted_anti_commuting_qubit_counts;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101123222425.2781: *5* (constructors)
    AntiCommutatorQubitCountSequenceOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    AntiCommutatorQubitCountSequenceOrderedOperatorSpace(bool share, AntiCommutatorQubitCountSequenceOrderedOperatorSpace& s);
    //@+node:gcross.20101123222425.2782: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2783: *3* struct MinimalWeightOperatorSpace
struct MinimalWeightOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101123222425.2784: *4* (fields)
    int number_of_products, number_of_variables, maximum_number_of_factors;

    BoolVarArray products_X, products_Z, products_non_trivial;
    IntVarArray products_weights, products_minimum_weights;
    //@+node:gcross.20101123222425.2785: *4* (constructors)
    MinimalWeightOperatorSpace(int number_of_operators, int number_of_qubits);
    MinimalWeightOperatorSpace(bool share, MinimalWeightOperatorSpace& s);
    //@+node:gcross.20101123222425.2786: *4* (methods)
    virtual Space* copy(bool share);

    private:

    static int computeNumberOfProducts(int number_of_operators, int number_of_qubits);
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
//@+node:gcross.20101123222425.2787: *3* struct AllConstraintsOddRowsOperatorSpace
struct AllConstraintsOddRowsOperatorSpace
    : public WeightAndFirstColumnXRowOrderedOperatorSpace
    , public ColumnOrderedOperatorSpace
    , public MinimalWeightOperatorSpace
    , public AntiCommutatorCountOrderedOperatorSpace
    , public AntiCommutatorQubitCountSequenceOrderedOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.2788: *4* (constructors)
    AllConstraintsOddRowsOperatorSpace(int number_of_operators, int number_of_qubits);
    AllConstraintsOddRowsOperatorSpace(bool share, AllConstraintsOddRowsOperatorSpace& s);
    //@+node:gcross.20101123222425.2789: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2790: *3* struct AllConstraintsEvenRowsOperatorSpace
struct AllConstraintsEvenRowsOperatorSpace
    : public WeightRowOrderedOperatorSpace
    , public ColumnOrderedOperatorSpace
    , public MinimalWeightOperatorSpace
    , public AntiCommutatorCountOrderedOperatorSpace
    , public AntiCommutatorQubitCountSequenceOrderedOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.2791: *4* (constructors)
    AllConstraintsEvenRowsOperatorSpace(int number_of_operators, int number_of_qubits);
    AllConstraintsEvenRowsOperatorSpace(bool share, AllConstraintsEvenRowsOperatorSpace& s);
    //@+node:gcross.20101123222425.2792: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2793: ** Functions
int choose(int n,int k);
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m);
void postColumnXZYOrderingConstraints(OperatorSpace& m);
void postNonTrivialWeightConstraints(OperatorSpace& m);
OperatorSpace* constructConstrainedOperatorSpace(int number_of_qubits,int number_of_operators);
//@-others

#endif
//@-leo
