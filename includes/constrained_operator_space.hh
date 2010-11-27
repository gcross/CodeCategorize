//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2840: * @thin constrained_operator_space.hh
//@@language cplusplus

#ifndef CONSTRAINED_OPERATOR_SPACE_HH
#define CONSTRAINED_OPERATOR_SPACE_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2841: ** << Includes >>
#include "constraints/column_ordered.hh"
#include "constraints/minimal_weight.hh"
#include "constraints/row_ordered.hh"
#include "constraints/row_ordered/anti_commutator_count.hh"
#include "constraints/row_ordered/anti_commutator_last_operator_sequence.hh"
#include "constraints/row_ordered/anti_commutator_qubit_count_sequence.hh"
#include "constraints/row_ordered/first_column.hh"
#include "constraints/row_ordered/weight.hh"
#include "constraints/row_ordered/weight_and_first_column.hh"
#include "constraints/special_case_XZ.hh"
#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.2842: ** Classes
//@+node:gcross.20101123222425.2879: *3* struct AllConstraintsOddRowsOperatorSpace
struct AllConstraintsOddRowsOperatorSpace
    : public WeightAndFirstColumnXRowOrderedOperatorSpace
    , public ColumnOrderedOperatorSpace
    , public MinimalWeightOperatorSpace
    , public AntiCommutatorCountOrderedOperatorSpace
    , public AntiCommutatorQubitCountSequenceOrderedOperatorSpace
    , public AntiCommutatorLastOperatorSequenceOrderedOperatorSpace
    , public SpecialCaseXZConstrainedOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.2880: *4* (constructors)
    AllConstraintsOddRowsOperatorSpace(int number_of_operators, int number_of_qubits);
    AllConstraintsOddRowsOperatorSpace(bool share, AllConstraintsOddRowsOperatorSpace& s);
    //@+node:gcross.20101123222425.2881: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2882: *3* struct AllConstraintsEvenRowsOperatorSpace
struct AllConstraintsEvenRowsOperatorSpace
    : public WeightRowOrderedOperatorSpace
    , public ColumnOrderedOperatorSpace
    , public MinimalWeightOperatorSpace
    , public AntiCommutatorCountOrderedOperatorSpace
    , public AntiCommutatorQubitCountSequenceOrderedOperatorSpace
    , public SpecialCaseXZConstrainedOperatorSpace
{

    //@+others
    //@+node:gcross.20101123222425.2883: *4* (constructors)
    AllConstraintsEvenRowsOperatorSpace(int number_of_operators, int number_of_qubits);
    AllConstraintsEvenRowsOperatorSpace(bool share, AllConstraintsEvenRowsOperatorSpace& s);
    //@+node:gcross.20101123222425.2884: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101123222425.2885: ** Functions
OperatorSpace* constructConstrainedOperatorSpace(int number_of_qubits,int number_of_operators);
//@-others

}

#endif
//@-leo
