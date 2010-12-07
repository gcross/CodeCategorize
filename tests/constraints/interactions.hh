//@+leo-ver=5-thin
//@+node:gcross.20101128173348.1848: * @thin interactions.hh
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101128173348.1849: ** << Includes >>
#include <algorithm>
#include <set>
#include <illuminate.hpp>

#include "column_pauli_sets.hh"
#include "commutator.hh"
#include "constraints/row_ordered.hh"
#include "operator_space.hh"

#include "test_utils.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101128173348.1850: ** struct ConstraintInteractionOperatorSpace
template <class T1,class T2> struct ConstraintInteractionOperatorSpace
    : public virtual OperatorSpace
    , public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
    , public virtual ColumnPauliSetsOperatorSpace
    , public T1
    , public T2
{

    //@+others
    //@+node:gcross.20101128173348.1851: *3* (constructors)
    ConstraintInteractionOperatorSpace(int number_of_operators, int number_of_qubits)
        : OperatorSpace(number_of_operators,number_of_qubits)
        , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
        , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
        , ColumnPauliSetsOperatorSpace(number_of_operators,number_of_qubits)
        , T1(number_of_operators,number_of_qubits)
        , T2(number_of_operators,number_of_qubits)
    { }

    ConstraintInteractionOperatorSpace(bool share, ConstraintInteractionOperatorSpace& s)
        : OperatorSpace(share,s)
        , RowOrderedOperatorSpace(share,s)
        , CommutatorOperatorSpace(share,s)
        , ColumnPauliSetsOperatorSpace(share,s)
        , T1(share,s)
        , T2(share,s)
    { }
    //@+node:gcross.20101128173348.1852: *3* copy
    Space* copy(bool share)
    {
        return new ConstraintInteractionOperatorSpace(share,*this);
    }
    //@+node:gcross.20101128173348.1853: *3* runCompatibilityTest
    static void runCompatibilityTest(int number_of_operators, int number_of_qubits) {
        vector<long> solutions_intersection;
        {
            vector<long> solutions_1 = gatherSolutions(new T1(number_of_operators,number_of_qubits));
            vector<long> solutions_2 = gatherSolutions(new T2(number_of_operators,number_of_qubits));
            set_intersection(
                solutions_1.begin(),solutions_1.end(),
                solutions_2.begin(),solutions_2.end(),
                insert_iterator<vector<long> >(solutions_intersection,solutions_intersection.begin())
            );
        }
        vector<long> solutions_12 = gatherSolutions(new ConstraintInteractionOperatorSpace<T1,T2>(number_of_operators,number_of_qubits));
        {
            vector<long> solutions_difference;
            set_difference(
                solutions_intersection.begin(),solutions_intersection.end(),
                solutions_12.begin(),solutions_12.end(),
                insert_iterator<vector<long> >(solutions_difference,solutions_difference.begin())
            );
            ASSERT_TRUE(solutions_difference.empty() && "combining the two constraints *removes* solutions");
        }
        {
            vector<long> solutions_difference;
            set_difference(
                solutions_12.begin(),solutions_12.end(),
                solutions_intersection.begin(),solutions_intersection.end(),
                insert_iterator<vector<long> >(solutions_difference,solutions_difference.begin())
            );
            ASSERT_TRUE(solutions_difference.empty() && "combining the two constraints *adds* solutions");
        }
    }
    //@+node:gcross.20101128193219.1853: *3* runCommutationTest
    static void runCommutationTest(int number_of_operators, int number_of_qubits) {
        long number_of_solutions_12 = countSolutions(new ConstraintInteractionOperatorSpace<T1,T2>(number_of_operators,number_of_qubits));
        long number_of_solutions_21 = countSolutions(new ConstraintInteractionOperatorSpace<T2,T1>(number_of_operators,number_of_qubits));
        ASSERT_EQ(number_of_solutions_12,number_of_solutions_21);
    }
    //@-others

};
//@+node:gcross.20101128173348.1854: ** Macros
#define runCompatibilityTestFor(T1,T2,m,n) \
    TEST_CASE( _##m##x##n ) { ConstraintInteractionOperatorSpace< T1##OperatorSpace , T2##OperatorSpace >::runCompatibilityTest(m,n); };

#define runCompatibilityTestsFor(T1,T2)              \
    TEST_SUITE(Constraint_Compatibility) {            \
        TEST_SUITE( T1##_and_##T2 ) {                  \
            runCompatibilityTestFor(T1,T2,2,1);      \
            runCompatibilityTestFor(T1,T2,2,2);      \
            runCompatibilityTestFor(T1,T2,2,3);      \
            runCompatibilityTestFor(T1,T2,3,1);      \
            runCompatibilityTestFor(T1,T2,3,2);      \
            runCompatibilityTestFor(T1,T2,3,3);      \
            runCompatibilityTestFor(T1,T2,4,1);      \
            runCompatibilityTestFor(T1,T2,4,2);      \
            runCompatibilityTestFor(T1,T2,5,1);      \
        };                                           \
    }
#define runCommutationTestFor(T1,T2,m,n) \
    TEST_CASE( _##m##x##n ) { ConstraintInteractionOperatorSpace< T1##OperatorSpace , T2##OperatorSpace >::runCommutationTest(m,n); };

#define runEvenRowCommutationTestsFor(T1,T2)         \
    TEST_SUITE(Constraint_Commutation) {              \
        TEST_SUITE( T1##_and_##T2 ) {                  \
            runCommutationTestFor(T1,T2,2,1);        \
            runCommutationTestFor(T1,T2,2,2);        \
            runCommutationTestFor(T1,T2,2,3);        \
            runCommutationTestFor(T1,T2,4,1);        \
            runCommutationTestFor(T1,T2,4,2);        \
        };                                           \
    }

#define runOddRowCommutationTestsFor(T1,T2)          \
    TEST_SUITE(Constraint_Commutation) {              \
        TEST_SUITE( T1##_and_##T2 ) {                  \
            runCommutationTestFor(T1,T2,3,1);        \
            runCommutationTestFor(T1,T2,3,2);        \
            runCommutationTestFor(T1,T2,3,3);        \
            runCommutationTestFor(T1,T2,5,1);        \
        };                                           \
    }


#define runCommutationTestsFor(T1,T2)                \
    TEST_SUITE(Constraint_Commutation) {              \
        TEST_SUITE( T1##_and_##T2 ) {                  \
            runCommutationTestFor(T1,T2,2,1);        \
            runCommutationTestFor(T1,T2,2,2);        \
            runCommutationTestFor(T1,T2,2,3);        \
            runCommutationTestFor(T1,T2,3,1);        \
            runCommutationTestFor(T1,T2,3,2);        \
            runCommutationTestFor(T1,T2,3,3);        \
            runCommutationTestFor(T1,T2,4,1);        \
            runCommutationTestFor(T1,T2,4,2);        \
            runCommutationTestFor(T1,T2,5,1);        \
        };                                           \
    }
//@-others
//@-leo
