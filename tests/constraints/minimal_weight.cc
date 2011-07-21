//@+leo-ver=5-thin
//@+node:gcross.20101123222425.4170: * @thin minimal_weight.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.4171: ** << Includes >>
#include <illuminate.hpp>

#include "constraints/minimal_weight.hh"
#include "solution_iterator.hh"

#include "test_utils.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101121135345.1486: ** Tests
TEST_SUITE(Constraints) { TEST_SUITE(MinimalWeight) {

//@+others
//@+node:gcross.20101121135345.1494: *3* Functions
//@+node:gcross.20101121200631.1645: *4* checkAllProducts
bool checkAllProducts(
    const vector<dynamic_quantum_operator>& operators,
    const dynamic_quantum_operator op,
    const size_t minimum_weight,
    const int first_operator_number
) {
    for(int i = first_operator_number; i < operators.size(); ++i) {
        const dynamic_quantum_operator product = op * operators[i];
        const int product_minimum_weight = min(minimum_weight,operators[i].weight());
        if(product.weight() < product_minimum_weight) return false;
        if(not checkAllProducts(operators,product,product_minimum_weight,i+1)) return false;
    }
    return true;
}
//@+node:gcross.20101121162317.1583: *4* validateWeights
void validateWeights(int number_of_qubits,BoolVarArray& non_trivial,IntVarArray& weights) {
    int number_of_operators = non_trivial.size() / number_of_qubits;
    BoolMatrix non_trivial_matrix(non_trivial,number_of_qubits,number_of_operators);
    for(int i = 0; i < number_of_operators; ++i) {
        int correct_weight = 0;
        for(int j = 0; j < number_of_qubits; ++j) correct_weight += non_trivial_matrix(j,i).val();
        ASSERT_EQ(correct_weight,weights[i].val());
    }
}
//@+node:gcross.20101121200631.1646: *4* runCorrectNumberOfProductsTest
void runCorrectNumberOfProductsTest(int number_of_operators, int number_of_qubits, int correct_number_of_products) {
    MinimalWeightOperatorSpace* m = new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits);
    ASSERT_EQ(correct_number_of_products,m->number_of_products);
    delete m;
}
//@+node:gcross.20101121135345.1493: *4* runDerivedFieldsTest
void runDerivedFieldsTest(int number_of_operators, int number_of_qubits) {
    MinimalWeightOperatorSpace* m = new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits);
    DFS<MinimalWeightOperatorSpace> e(m);
    delete m;
    for(m = e.next(); m != NULL; m = e.next()) {
        validateNonTrivial(m->products_X,m->products_Z,m->products_non_trivial);
        validateWeights(number_of_qubits,m->products_non_trivial,m->products_weights);
        delete m;
    }
}
//@+node:gcross.20101121200631.1644: *4* runWeightTest
void runWeightTest(int number_of_operators, int number_of_qubits, optional<int> maximum_weight=none) {
    for(SolutionIterator<> solution(auto_ptr<OperatorSpace>(new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits,maximum_weight)));
        solution;
        ++solution
    ) {
        int i = 0;
        BOOST_FOREACH(const dynamic_quantum_operator& op, *solution) {
            if(maximum_weight) ASSERT_TRUE(op.weight() <= *maximum_weight);
            ASSERT_TRUE(checkAllProducts(*solution,op,op.weight(),i+1));
            ++i;
        }
    }
}
//@+node:gcross.20101122101448.1538: *4* runCorrectNumberOfSolutionsTest
void runCorrectNumberOfSolutionsTest(int number_of_operators, int number_of_qubits) {
    int correct_number_of_solutions = 0;
    for(SolutionIterator<> solution(auto_ptr<OperatorSpace>(new OperatorSpace(number_of_operators,number_of_qubits)));
        solution;
        ++solution
    ) {
        const vector<dynamic_quantum_operator>& operators = *solution;
        bool is_minimal_weight_solution = true;
        for(int i = 0; i < number_of_operators; ++i) {
            if(not checkAllProducts(operators,operators[i],operators[i].weight(),i+1)) {
                is_minimal_weight_solution = false;
                break;
            }
        }
        if(is_minimal_weight_solution) ++correct_number_of_solutions;
    }
    int number_of_solutions = countSolutions(new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits));
    ASSERT_EQ(correct_number_of_solutions,number_of_solutions);
}
//@+node:gcross.20101209224839.2817: *4* runCheckCodesTest
void runCheckCodesTest(int number_of_operators, int number_of_qubits) {
    checkCodes(new MinimalWeightOperatorSpace(number_of_operators,number_of_qubits));
}
//@+node:gcross.20101121135345.1487: *3* 2x1
TEST_SUITE(_2x1) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(2,1); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(2,1,1); }
    TEST_CASE(minimal_weight) { runWeightTest(2,1); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(2,1); }
    TEST_SUITE(minimal_weight_under_maximum_weight) {
        TEST_CASE(_1) { runWeightTest(2,1,make_optional(1)); }
        TEST_CASE(_2) { runWeightTest(2,1,make_optional(2)); }
        TEST_CASE(_3) { runWeightTest(2,1,make_optional(3)); }
    }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(2,1); }

}
//@+node:gcross.20101121135345.1498: *3* 2x2
TEST_SUITE(_2x2) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(2,2); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(2,2,1); }
    TEST_CASE(minimal_weight) { runWeightTest(2,2); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(2,2); }
    TEST_SUITE(minimal_weight_under_maximum_weight) {
        TEST_CASE(_1) { runWeightTest(2,2,make_optional(1)); }
        TEST_CASE(_2) { runWeightTest(2,2,make_optional(2)); }
        TEST_CASE(_3) { runWeightTest(2,2,make_optional(3)); }
        TEST_CASE(_4) { runWeightTest(2,2,make_optional(4)); }
    }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(2,2); }

}
//@+node:gcross.20101121135345.1500: *3* 2x3
TEST_SUITE(_2x3) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(2,3); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(2,3,1); }
    TEST_CASE(minimal_weight) { runWeightTest(2,3); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(2,3); }
    TEST_SUITE(minimal_weight_under_maximum_weight) {
        TEST_CASE(_1) { runWeightTest(2,3,make_optional(1)); }
        TEST_CASE(_2) { runWeightTest(2,3,make_optional(2)); }
        TEST_CASE(_3) { runWeightTest(2,3,make_optional(3)); }
        TEST_CASE(_4) { runWeightTest(2,3,make_optional(4)); }
        TEST_CASE(_5) { runWeightTest(2,3,make_optional(5)); }
    }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(2,3); }

}
//@+node:gcross.20101121135345.1504: *3* 3x1
TEST_SUITE(_3x1) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(3,1); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(3,1,2*1+2); }
    TEST_CASE(minimal_weight) { runWeightTest(3,1); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(3,1); }
    TEST_SUITE(minimal_weight_under_maximum_weight) {
        TEST_CASE(_1) { runWeightTest(3,1,make_optional(1)); }
        TEST_CASE(_2) { runWeightTest(3,1,make_optional(2)); }
        TEST_CASE(_3) { runWeightTest(3,1,make_optional(3)); }
    }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(3,1); }

}
//@+node:gcross.20101121135345.1506: *3* 3x2
TEST_SUITE(_3x2) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(3,2); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(3,2,2*1+2); }
    TEST_CASE(minimal_weight) { runWeightTest(3,2); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(3,2); }
    TEST_SUITE(minimal_weight_under_maximum_weight) {
        TEST_CASE(_1) { runWeightTest(3,2,make_optional(1)); }
        TEST_CASE(_2) { runWeightTest(3,2,make_optional(2)); }
        TEST_CASE(_3) { runWeightTest(3,2,make_optional(3)); }
        TEST_CASE(_4) { runWeightTest(3,2,make_optional(4)); }
    }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(3,2); }

}
//@+node:gcross.20101121135345.1502: *3* 3x3
TEST_SUITE(_3x3) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(3,3); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(3,3,2*1+2); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(3,3); }
    TEST_SUITE(minimal_weight_under_maximum_weight) {
        TEST_CASE(_1) { runWeightTest(3,3,make_optional(1)); }
        TEST_CASE(_2) { runWeightTest(3,3,make_optional(2)); }
        TEST_CASE(_3) { runWeightTest(3,3,make_optional(3)); }
        TEST_CASE(_4) { runWeightTest(3,3,make_optional(4)); }
        TEST_CASE(_5) { runWeightTest(3,3,make_optional(5)); }
    }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(3,3); }

}
//@+node:gcross.20101121135345.1508: *3* 4x1
TEST_SUITE(_4x1) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(4,1); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(4,1,2); }
    TEST_CASE(minimal_weight) { runWeightTest(4,1); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(4,1); }
    TEST_SUITE(minimal_weight_under_maximum_weight) {
        TEST_CASE(_1) { runWeightTest(4,1,make_optional(1)); }
        TEST_CASE(_2) { runWeightTest(4,1,make_optional(2)); }
        TEST_CASE(_3) { runWeightTest(4,1,make_optional(3)); }
    }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(4,1); }

}
//@+node:gcross.20101121135345.1510: *3* 4x2
TEST_SUITE(_4x2) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(4,2); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(4,2,2+3*3); }
    TEST_CASE(minimal_weight) { runWeightTest(4,2); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(4,2); }
    TEST_SUITE(minimal_weight_under_maximum_weight) {
        TEST_CASE(_1) { runWeightTest(4,2,make_optional(1)); }
        TEST_CASE(_2) { runWeightTest(4,2,make_optional(2)); }
        TEST_CASE(_3) { runWeightTest(4,2,make_optional(3)); }
        TEST_CASE(_4) { runWeightTest(4,2,make_optional(4)); }
    }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(4,2); }

}
//@+node:gcross.20101121135345.1512: *3* 5x1
TEST_SUITE(_5x1) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(5,1); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(5,1,2*2+4); }
    TEST_CASE(minimal_weight) { runWeightTest(5,1); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(5,1); }

}
//@+node:gcross.20101121200631.4183: *3* 5x2
//@+at
// TEST_SUITE(_5x2) {
// 
//     TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(5,2); }
//     TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(5,2,(2+3*3)*2+5); }
//     TEST_CASE(minimal_weight) { runWeightTest(5,2); }
// 
// }
//@+node:gcross.20101121162317.1476: *3* 6x1
TEST_SUITE(_6x1) {

    TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(6,1); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(6,1,3); }
    TEST_CASE(correct_number_of_solutions) { runCorrectNumberOfSolutionsTest(6,1); }
    TEST_CASE(no_codes_excluded){ runCheckCodesTest(6,1); }

}
//@+node:gcross.20101121200631.1648: *3* 6x2
TEST_SUITE(_6x2) {

    //TEST_CASE(correct_derived_fields) { runDerivedFieldsTest(6,2); }
    TEST_CASE(correct_number_of_products) { runCorrectNumberOfProductsTest(6,2,3+3*3*3); }
    //TEST_CASE(minimal_weight) { runWeightTest(6,2); }

}
//@-others

} }
//@-others
//@-leo
