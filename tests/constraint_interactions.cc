//@+leo-ver=5-thin
//@+node:gcross.20101127142618.1751: * @thin constraint_interactions.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101127142618.1753: ** << Includes >>
#include <algorithm>
#include <set>
#include <unit--.hpp>

#include "column_pauli_sets.hh"
#include "commutator.hh"
#include "constraints/column_ordered.hh"
#include "constraints/minimal_weight.hh"
#include "constraints/row_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_count_minus_last.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/pauli_groups.hh"
#include "constraints/row_ordered/weight.hh"
#include "constraints/special_case_XZ.hh"
#include "constraints/XZY_ordered.hh"
#include "operator_space.hh"

#include "test_utils.hh"

using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101127142618.1756: ** struct ConstraintInteractionOperatorSpace
template <class T1,class T2> struct ConstraintInteractionOperatorSpace
    : public virtual OperatorSpace
    , public virtual RowOrderedOperatorSpace
    , public virtual CommutatorOperatorSpace
    , public virtual ColumnPauliSetsOperatorSpace
    , public T1
    , public T2
{

    //@+others
    //@+node:gcross.20101127142618.1757: *3* (constructors)
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
    //@+node:gcross.20101127142618.1759: *3* copy
    Space* copy(bool share)
    {
        return new ConstraintInteractionOperatorSpace(share,*this);
    }
    //@+node:gcross.20101127142618.1760: *3* runTest
    static void runTest(int number_of_operators, int number_of_qubits) {
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
            assertTrue(solutions_difference.empty() && "combining the two constraints *removes* solutions");
        }
        {
            vector<long> solutions_difference;
            set_difference(
                solutions_12.begin(),solutions_12.end(),
                solutions_intersection.begin(),solutions_intersection.end(),
                insert_iterator<vector<long> >(solutions_difference,solutions_difference.begin())
            );
            assertTrue(solutions_difference.empty() && "combining the two constraints *adds* solutions");
        }
    }
    //@-others

};
//@+node:gcross.20101127142618.1767: ** Macros
#define runTestFor(T1,T2,m,n) \
    testCase( _##m##x##n ) { ConstraintInteractionOperatorSpace< T1##OperatorSpace , T2##OperatorSpace >::runTest(m,n); };
#define runTestsFor(T1,T2)     \
    subSuite( T1##_and_##T2 ) {  \
        runTestFor(T1,T2,2,1); \
        runTestFor(T1,T2,2,2); \
        runTestFor(T1,T2,2,3); \
        runTestFor(T1,T2,3,1); \
        runTestFor(T1,T2,3,2); \
        runTestFor(T1,T2,3,3); \
        runTestFor(T1,T2,4,1); \
        runTestFor(T1,T2,4,2); \
        runTestFor(T1,T2,5,1); \
    };
//@+node:gcross.20101127142618.1768: ** Tests
testSuite(Constraint_Interactions) {
    runTestsFor(ColumnOrdered,MinimalWeight);
    runTestsFor(ColumnOrdered,AntiCommutatorCountOrdered);
    runTestsFor(ColumnOrdered,AntiCommutatorCountMinusLastOrdered);
    runTestsFor(ColumnOrdered,AntiCommutatorQubitCountSequenceOrdered);
    runTestsFor(ColumnOrdered,AntiCommutatorLastOperatorSequenceOrdered);
    runTestsFor(ColumnOrdered,FirstColumnXRowOrdered);
    runTestsFor(ColumnOrdered,PauliGroupsRowOrdered);
    runTestsFor(ColumnOrdered,WeightRowOrdered);
    runTestsFor(ColumnOrdered,SpecialCaseXZConstrained);
    runTestsFor(ColumnOrdered,XZYOrdered);

    runTestsFor(MinimalWeight,AntiCommutatorCountOrdered);
    runTestsFor(MinimalWeight,AntiCommutatorCountMinusLastOrdered);
    runTestsFor(MinimalWeight,AntiCommutatorQubitCountSequenceOrdered);
    runTestsFor(MinimalWeight,AntiCommutatorLastOperatorSequenceOrdered);
    runTestsFor(MinimalWeight,FirstColumnXRowOrdered);
    runTestsFor(MinimalWeight,PauliGroupsRowOrdered);
    runTestsFor(MinimalWeight,WeightRowOrdered);
    runTestsFor(MinimalWeight,SpecialCaseXZConstrained);
    runTestsFor(MinimalWeight,XZYOrdered);

    runTestsFor(AntiCommutatorCountOrdered,AntiCommutatorCountMinusLastOrdered);
    runTestsFor(AntiCommutatorCountOrdered,AntiCommutatorQubitCountSequenceOrdered);
    runTestsFor(AntiCommutatorCountOrdered,AntiCommutatorLastOperatorSequenceOrdered);
    runTestsFor(AntiCommutatorCountOrdered,FirstColumnXRowOrdered);
    runTestsFor(AntiCommutatorCountOrdered,PauliGroupsRowOrdered);
    runTestsFor(AntiCommutatorCountOrdered,WeightRowOrdered);
    runTestsFor(AntiCommutatorCountOrdered,SpecialCaseXZConstrained);
    runTestsFor(AntiCommutatorCountOrdered,XZYOrdered);

    runTestsFor(AntiCommutatorCountMinusLastOrdered,AntiCommutatorQubitCountSequenceOrdered);
    runTestsFor(AntiCommutatorCountMinusLastOrdered,AntiCommutatorLastOperatorSequenceOrdered);
    runTestsFor(AntiCommutatorCountMinusLastOrdered,FirstColumnXRowOrdered);
    runTestsFor(AntiCommutatorCountMinusLastOrdered,PauliGroupsRowOrdered);
    runTestsFor(AntiCommutatorCountMinusLastOrdered,WeightRowOrdered);
    runTestsFor(AntiCommutatorCountMinusLastOrdered,SpecialCaseXZConstrained);
    runTestsFor(AntiCommutatorCountMinusLastOrdered,XZYOrdered);

    runTestsFor(AntiCommutatorQubitCountSequenceOrdered,AntiCommutatorLastOperatorSequenceOrdered);
    runTestsFor(AntiCommutatorQubitCountSequenceOrdered,FirstColumnXRowOrdered);
    runTestsFor(AntiCommutatorQubitCountSequenceOrdered,PauliGroupsRowOrdered);
    runTestsFor(AntiCommutatorQubitCountSequenceOrdered,WeightRowOrdered);
    runTestsFor(AntiCommutatorQubitCountSequenceOrdered,SpecialCaseXZConstrained);
    runTestsFor(AntiCommutatorQubitCountSequenceOrdered,XZYOrdered);

    runTestsFor(AntiCommutatorLastOperatorSequenceOrdered,FirstColumnXRowOrdered);
    runTestsFor(AntiCommutatorLastOperatorSequenceOrdered,PauliGroupsRowOrdered);
    runTestsFor(AntiCommutatorLastOperatorSequenceOrdered,WeightRowOrdered);
    runTestsFor(AntiCommutatorLastOperatorSequenceOrdered,SpecialCaseXZConstrained);
    runTestsFor(AntiCommutatorLastOperatorSequenceOrdered,XZYOrdered);

    runTestsFor(FirstColumnXRowOrdered,PauliGroupsRowOrdered);
    runTestsFor(FirstColumnXRowOrdered,WeightRowOrdered);
    runTestsFor(FirstColumnXRowOrdered,SpecialCaseXZConstrained);
    runTestsFor(FirstColumnXRowOrdered,XZYOrdered);

    runTestsFor(PauliGroupsRowOrdered,WeightRowOrdered);
    runTestsFor(PauliGroupsRowOrdered,SpecialCaseXZConstrained);
    runTestsFor(PauliGroupsRowOrdered,XZYOrdered);

    runTestsFor(WeightRowOrdered,SpecialCaseXZConstrained);
    runTestsFor(WeightRowOrdered,XZYOrdered);

    runTestsFor(SpecialCaseXZConstrained,XZYOrdered);
};
//@-others
//@-leo
