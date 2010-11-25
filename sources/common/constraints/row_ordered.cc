//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3471: * @thin row_ordered.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3472: ** << Includes >>
#include <gecode/minimodel.hh>

#include "constraints/row_ordered.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3478: ** struct RowOrderedOperatorSpace
//@+node:gcross.20101123222425.3479: *3* (constructors)
RowOrderedOperatorSpace::RowOrderedOperatorSpace(int number_of_operators, int number_of_qubits)
    : OperatorSpace(number_of_operators,number_of_qubits)
{ }

RowOrderedOperatorSpace::RowOrderedOperatorSpace(bool share, RowOrderedOperatorSpace& s)
    : OperatorSpace(share,s)
{ }
//@+node:gcross.20101123222425.3480: *3* copy
Space* RowOrderedOperatorSpace::copy(bool share)
{
    return new RowOrderedOperatorSpace(share,*this);
}
//@+node:gcross.20101123222425.3481: *3* postOrderingConstraint
void RowOrderedOperatorSpace::postOrderingConstraint(
    const IntVarArgs& ordering
   ,BoolVarArgs intrapair_ties_
   ,BoolVarArgs interpair_ties_
) {
    if(intrapair_ties.size() == 0) {
        assert(interpair_ties.size() == 0);
        for(int i = 0; i < number_of_pairs; ++i) {
            rel(*this,ordering[2*i] >= ordering[2*i+1]);
            intrapair_ties_[i] = expr(*this,ordering[2*i]==ordering[2*i+1]);
        }
        for(int i = 0; i < number_of_pairs-1; ++i) {
            rel(*this,
                    ordering[2*i+0] >  ordering[2*(i+1)+0]
              ||    ordering[2*i+0] == ordering[2*(i+1)+0]
                 && ordering[2*i+1] >= ordering[2*(i+1)+1]
            );
            interpair_ties_[i] = expr(*this,
                      ordering[2*i+0] == ordering[2*(i+1)+0]
                   && ordering[2*i+1] == ordering[2*(i+1)+1]
            );
        }
    } else {
        assert(interpair_ties.size() == intrapair_ties.size()-1);
        for(int i = 0; i < number_of_pairs; ++i) {
            rel(*this,intrapair_ties[i] >> (ordering[2*i] >= ordering[2*i+1]));
            intrapair_ties_[i] = expr(*this,intrapair_ties[i] && ordering[2*i]==ordering[2*i+1]);
        }
        for(int i = 0; i < number_of_pairs-1; ++i) {
            rel(*this,interpair_ties[i] >> (
                    ordering[2*i+0] >  ordering[2*(i+1)+0]
              ||    ordering[2*i+0] == ordering[2*(i+1)+0]
                 && ordering[2*i+1] >= ordering[2*(i+1)+1]
            ));
        interpair_ties_[i] =
            expr(*this,
                  interpair_ties_[i]
               && ordering[2*i+0] == ordering[2*(i+1)+0]
               && ordering[2*i+1] == ordering[2*(i+1)+1]
            );
        }
    }
    interpair_ties = interpair_ties_;
    intrapair_ties = intrapair_ties_;
}
//@-others

}
//@-leo
