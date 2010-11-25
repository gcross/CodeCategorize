//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3908: * @thin anti_commutator_count.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3909: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/row_ordered/anti_commutator_count.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3911: ** struct AntiCommutatorCountOrderedOperatorSpace
//@+node:gcross.20101123222425.3912: *3* (constructors)
AntiCommutatorCountOrderedOperatorSpace::AntiCommutatorCountOrderedOperatorSpace(
    int number_of_operators,
    int number_of_qubits
)
    : RowOrderedOperatorSpace(number_of_operators,number_of_qubits)
    , CommutatorOperatorSpace(number_of_operators,number_of_qubits)
    , OperatorSpace(number_of_operators,number_of_qubits)
    , number_of_anti_commuting_operators(*this,number_of_operators,0,number_of_operators)
    , intrapair_ties(*this,number_of_pairs,0,1)
    , interpair_ties(*this,max(number_of_pairs-1,0),0,1)
{
    BoolMatrix anti_commutator_matrix = getAntiCommutatorMatrix();
    for(int i = 0; i < number_of_operators; ++i) {
        linear(*this,anti_commutator_matrix.row(i),IRT_EQ,number_of_anti_commuting_operators[i]);
    }
    postOrderingConstraint(number_of_anti_commuting_operators,intrapair_ties,interpair_ties);
}

AntiCommutatorCountOrderedOperatorSpace::AntiCommutatorCountOrderedOperatorSpace(bool share, AntiCommutatorCountOrderedOperatorSpace& s)
    : RowOrderedOperatorSpace(share,s)
    , CommutatorOperatorSpace(share,s)
    , OperatorSpace(share,s)
{
    number_of_anti_commuting_operators.update(*this,share,s.number_of_anti_commuting_operators);
    intrapair_ties.update(*this,share,s.intrapair_ties);
    interpair_ties.update(*this,share,s.interpair_ties);
}
//@+node:gcross.20101123222425.3913: *3* copy
Space* AntiCommutatorCountOrderedOperatorSpace::copy(bool share)
{
    return new AntiCommutatorCountOrderedOperatorSpace(share,*this);
}
//@-others

}
//@-leo
