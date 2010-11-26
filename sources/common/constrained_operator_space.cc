//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3723: * @thin constrained_operator_space.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3724: ** << Includes >>
#include "constraints.hh"
#include "constrained_operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3725: ** Classes
//@+node:gcross.20101123222425.3746: *3* struct AllConstraintsOddRowsOperatorSpace
//@+node:gcross.20101123222425.3747: *4* (constructors)
AllConstraintsOddRowsOperatorSpace::AllConstraintsOddRowsOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , WeightAndFirstColumnXRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , MinimalWeightOperatorSpace(number_of_operators,number_of_qubits)
    , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
    , AntiCommutatorCountOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , AntiCommutatorCountMinusLastOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , AntiCommutatorQubitCountSequenceOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , SpecialCaseXZConstrainedOperatorSpace(number_of_operators,number_of_qubits)
{
    assert(number_of_operators % 2 == 1);
    postFirstColumnSpecialCaseConstraint(*this);
    postColumnXZYOrderingConstraints(*this);
    postNonTrivialWeightConstraints(*this);
}

AllConstraintsOddRowsOperatorSpace::AllConstraintsOddRowsOperatorSpace(bool share, AllConstraintsOddRowsOperatorSpace& s)
    : OperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , WeightAndFirstColumnXRowOrderedOperatorSpace(share,s)
    , ColumnOrderedOperatorSpace(share,s)
    , MinimalWeightOperatorSpace(share,s)
    , CommutatorOperatorSpace(share,s)
    , AntiCommutatorCountOrderedOperatorSpace(share,s)
    , AntiCommutatorCountMinusLastOrderedOperatorSpace(share,s)
    , AntiCommutatorQubitCountSequenceOrderedOperatorSpace(share,s)
    , SpecialCaseXZConstrainedOperatorSpace(share,s)
{
}
//@+node:gcross.20101123222425.3748: *4* copy
Space* AllConstraintsOddRowsOperatorSpace::copy(bool share)
{
    return new AllConstraintsOddRowsOperatorSpace(share,*this);
}
//@+node:gcross.20101123222425.3749: *3* struct AllConstraintsEvenRowsOperatorSpace
//@+node:gcross.20101123222425.3750: *4* (constructors)
AllConstraintsEvenRowsOperatorSpace::AllConstraintsEvenRowsOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , WeightRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , MinimalWeightOperatorSpace(number_of_operators,number_of_qubits)
    , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
    , AntiCommutatorCountOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , AntiCommutatorQubitCountSequenceOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , SpecialCaseXZConstrainedOperatorSpace(number_of_operators,number_of_qubits)
{
    assert(number_of_operators % 2 == 0);
    postColumnXZYOrderingConstraints(*this);
    postNonTrivialWeightConstraints(*this);
}

AllConstraintsEvenRowsOperatorSpace::AllConstraintsEvenRowsOperatorSpace(bool share, AllConstraintsEvenRowsOperatorSpace& s)
    : OperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , WeightRowOrderedOperatorSpace(share,s)
    , ColumnOrderedOperatorSpace(share,s)
    , MinimalWeightOperatorSpace(share,s)
    , CommutatorOperatorSpace(share,s)
    , AntiCommutatorCountOrderedOperatorSpace(share,s)
    , AntiCommutatorQubitCountSequenceOrderedOperatorSpace(share,s)
    , SpecialCaseXZConstrainedOperatorSpace(share,s)
{
}
//@+node:gcross.20101123222425.3751: *4* copy
Space* AllConstraintsEvenRowsOperatorSpace::copy(bool share)
{
    return new AllConstraintsEvenRowsOperatorSpace(share,*this);
}
//@+node:gcross.20101123222425.3752: ** Functions
//@+node:gcross.20101123222425.3757: *3* constructConstrainedOperatorSpace
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

}
//@-leo
