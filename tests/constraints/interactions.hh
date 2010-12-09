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
//@+node:gcross.20101209010739.1834: ** struct ConstraintInteractionOperatorSpace3
template <class T1,class T2,class T3> struct ConstraintInteractionOperatorSpace3
    : public virtual OperatorSpace
    , public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
    , public virtual ColumnPauliSetsOperatorSpace
    , public T1
    , public T2
    , public T3
{

    //@+others
    //@+node:gcross.20101209010739.1835: *3* (constructors)
    ConstraintInteractionOperatorSpace3(int number_of_operators, int number_of_qubits)
        : OperatorSpace(number_of_operators,number_of_qubits)
        , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
        , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
        , ColumnPauliSetsOperatorSpace(number_of_operators,number_of_qubits)
        , T1(number_of_operators,number_of_qubits)
        , T2(number_of_operators,number_of_qubits)
        , T3(number_of_operators,number_of_qubits)
    { }

    ConstraintInteractionOperatorSpace3(bool share, ConstraintInteractionOperatorSpace3& s)
        : OperatorSpace(share,s)
        , RowOrderedOperatorSpace(share,s)
        , CommutatorOperatorSpace(share,s)
        , ColumnPauliSetsOperatorSpace(share,s)
        , T1(share,s)
        , T2(share,s)
        , T3(share,s)
    { }
    //@+node:gcross.20101209010739.1836: *3* copy
    Space* copy(bool share)
    {
        return new ConstraintInteractionOperatorSpace3(share,*this);
    }
    //@+node:gcross.20101209010739.1838: *3* runCommutationTest
    static void runCommutationTest(int number_of_operators, int number_of_qubits) {
        long number_of_solutions_12 = countSolutions(new ConstraintInteractionOperatorSpace3<T1,T2,T3>(number_of_operators,number_of_qubits));
        long number_of_solutions_21 = countSolutions(new ConstraintInteractionOperatorSpace3<T1,T3,T2>(number_of_operators,number_of_qubits));
        ASSERT_EQ(number_of_solutions_12,number_of_solutions_21);
    }
    //@-others

};
//@+node:gcross.20101128173348.1854: ** Macros
//@+node:gcross.20101209010739.1839: *3* Compatibility tests
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
//@+node:gcross.20101209010739.1840: *3* Commutation tests
#define runCommutationTestFor(T1,T2,m,n) \
    TEST_CASE( _##m##x##n ) { ConstraintInteractionOperatorSpace< T1##OperatorSpace , T2##OperatorSpace >::runCommutationTest(m,n); };

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
//@+node:gcross.20101209010739.1841: *3* Commutation-compatibility tests
#define runCommutationCompatibilityTestFor(T1,T2,T3,m,n) \
    TEST_CASE( _##m##x##n ) { ConstraintInteractionOperatorSpace3< T1##OperatorSpace , T2##OperatorSpace , T3##OperatorSpace >::runCommutationTest(m,n); };

#define runOddRowCommutationCompatibilityTestsFor(T1,T2,T3)          \
    TEST_SUITE(Constraint_Commutation_Compatibility) {              \
        TEST_SUITE( T1##_with_##T2##_and_##T3 ) {                  \
            runCommutationCompatibilityTestFor(T1,T2,T3,3,1);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,3,2);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,3,3);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,5,1);        \
        };                                           \
    }


#define runCommutationCompatibilityTestsFor(T1,T2,T3)                \
    TEST_SUITE(Constraint_Commutation_Compatibility) {              \
        TEST_SUITE( T1##_with_##T2##_and_##T3 ) {                  \
            runCommutationCompatibilityTestFor(T1,T2,T3,2,1);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,2,2);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,2,3);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,3,1);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,3,2);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,3,3);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,4,1);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,4,2);        \
            runCommutationCompatibilityTestFor(T1,T2,T3,5,1);        \
        };                                           \
    }
//@-others
//@-leo
