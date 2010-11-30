//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3723: * @thin constrained_operator_space.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3724: ** << Includes >>
#include "constrained_operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3725: ** Classes
//@+node:gcross.20101126220444.1931: *3* struct AllConstraintsBaseOperatorSpace
//@+node:gcross.20101126220444.1932: *4* (constructors)
AllConstraintsBaseOperatorSpace::AllConstraintsBaseOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , MinimalWeightOperatorSpace(number_of_operators,number_of_qubits)
    , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
    , AntiCommutatorQubitCountSequenceOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , SpecialCaseXZConstrainedOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnPauliSetsOperatorSpace(number_of_operators,number_of_qubits)
    , XZYOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , PauliGroupsRowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , NonTrivialOperatorSpace(number_of_operators,number_of_qubits)
{ }

AllConstraintsBaseOperatorSpace::AllConstraintsBaseOperatorSpace(bool share, AllConstraintsBaseOperatorSpace& s)
    : OperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , ColumnOrderedOperatorSpace(share,s)
    , MinimalWeightOperatorSpace(share,s)
    , CommutatorOperatorSpace(share,s)
    , AntiCommutatorQubitCountSequenceOrderedOperatorSpace(share,s)
    , SpecialCaseXZConstrainedOperatorSpace(share,s)
    , ColumnPauliSetsOperatorSpace(share,s)
    , XZYOrderedOperatorSpace(share,s)
    , PauliGroupsRowOrderedOperatorSpace(share,s)
    , NonTrivialOperatorSpace(share,s)
{ }
//@+node:gcross.20101126220444.1933: *4* copy
Space* AllConstraintsBaseOperatorSpace::copy(bool share)
{
    return new AllConstraintsBaseOperatorSpace(share,*this);
}
//@+node:gcross.20101123222425.3746: *3* struct AllConstraintsOddRowsOperatorSpace
//@+node:gcross.20101123222425.3747: *4* (constructors)
AllConstraintsOddRowsOperatorSpace::AllConstraintsOddRowsOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
    , AllConstraintsBaseOperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
    , AntiCommutatorLastOperatorSequenceOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnPauliSetsOperatorSpace(number_of_operators,number_of_qubits)
    , FirstColumnXZOperatorSpace(number_of_operators,number_of_qubits)
{
    assert(number_of_operators % 2 == 1);
}

AllConstraintsOddRowsOperatorSpace::AllConstraintsOddRowsOperatorSpace(bool share, AllConstraintsOddRowsOperatorSpace& s)
    : OperatorSpace(share,s)
    , AllConstraintsBaseOperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , CommutatorOperatorSpace(share,s)
    , AntiCommutatorLastOperatorSequenceOrderedOperatorSpace(share,s)
    , ColumnPauliSetsOperatorSpace(share,s)
    , FirstColumnXZOperatorSpace(share,s)
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
    , AllConstraintsBaseOperatorSpace(number_of_operators,number_of_qubits)
    , RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
    , ColumnPauliSetsOperatorSpace(number_of_operators,number_of_qubits)
{
    assert(number_of_operators % 2 == 0);
}

AllConstraintsEvenRowsOperatorSpace::AllConstraintsEvenRowsOperatorSpace(bool share, AllConstraintsEvenRowsOperatorSpace& s)
    : OperatorSpace(share,s)
    , AllConstraintsBaseOperatorSpace(share,s)
    , RowOrderedOperatorSpace(share,s)
    , CommutatorOperatorSpace(share,s)
    , ColumnPauliSetsOperatorSpace(share,s)
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
