//@+leo-ver=5-thin
//@+node:gcross.20101117133000.1340: * @thin row_ordered.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117133000.1341: ** << Includes >>
#include <boost/foreach.hpp>
#include <gecode/int.hh>
#include <iostream>
#include <unit--.hpp>

#include "constraints/row_ordered.hh"

#include "test_utils.hh"

using namespace std;
using namespace Gecode;
using namespace CodeCategorize;
//@-<< Includes >>

//@+others
//@+node:gcross.20101117133000.1531: ** Tests
testSuite(Constraints) { subSuite(RowOrdered) {

//@+<< Helpers >>
//@+node:gcross.20101128193219.1809: *3* << Helpers >>
//@+others
//@+node:gcross.20101128193219.1811: *4* TestClass
template<int number_of_pairs_,int number_of_constraints> struct TestClass : public RowOrderedOperatorSpace {
    IntVarArray ordering;
    BoolVarArray interpair_ties, intrapair_ties;

    TestClass(const int ordering_values[number_of_constraints][2*number_of_pairs_])
        : OperatorSpace(2*number_of_pairs_,1)
        , RowOrderedOperatorSpace(2*number_of_pairs_,1)
        , ordering(*this,number_of_constraints*2*number_of_pairs,0,1)
        , intrapair_ties(*this,number_of_constraints* number_of_pairs_   ,0,1)
        , interpair_ties(*this,number_of_constraints*(number_of_pairs_-1),0,1)
    {
        IntMatrix ordering_matrix(ordering,2*number_of_pairs,number_of_constraints);
        BoolMatrix intrapair_ties_matrix(intrapair_ties,number_of_pairs_  ,number_of_constraints),
                   interpair_ties_matrix(interpair_ties,number_of_pairs_-1,number_of_constraints);
        rel(*this,O,IRT_EQ,0);
        for(int i = 0; i < number_of_constraints; ++i) {
            for(int j = 0; j < 2*number_of_pairs_; ++j) {
                rel(*this,ordering_matrix(j,i),IRT_EQ,ordering_values[i][j]);
            }
            postOrderingConstraint(ordering_matrix.row(i),intrapair_ties_matrix.row(i),interpair_ties_matrix.row(i));
        }
    }

    TestClass(bool share,TestClass& s)
        : OperatorSpace(share,s)
        , RowOrderedOperatorSpace(share,s)
    {
        ordering.update(*this,share,s.ordering);
        interpair_ties.update(*this,share,s.interpair_ties);
        intrapair_ties.update(*this,share,s.intrapair_ties);
    }

    virtual Space* copy(bool share) { return new TestClass(share,*this); }
};
//@+node:gcross.20101128193219.1810: *4* createTest
#define createTest(test_name,number_of_pairs,number_of_constraints,correct_number_of_solutions,...) \
    testCase(test_name) { \
        int ordering_values[number_of_constraints][2*number_of_pairs] = {__VA_ARGS__}; \
        assertEqual(correct_number_of_solutions,countSolutions(new TestClass<number_of_pairs,number_of_constraints>(ordering_values))); \
    }
//@-others
//@-<< Helpers >>

//@+others
//@+node:gcross.20101128193219.1803: *3* 1 pair
subSuite(_1_pair) {

    subSuite(_1_constraint) {
        createTest(in_order,1,1,1
            ,1,0
        );
        createTest(out_of_order,1,1,0
            ,0,1
        );
    }

    subSuite(_2_constraints) {
        createTest(in_order_and_in_order,1,2,1
            ,1,0
            ,1,0
        );
        createTest(in_order_and_tied,1,2,1
            ,1,0
            ,0,0
        );
        createTest(in_order_and_out_of_order,1,2,1
            ,1,0
            ,0,1
        );
        createTest(tied_and_in_order,1,2,1
            ,0,0
            ,1,0
        );
        createTest(tied_and_tied,1,2,1
            ,0,0
            ,0,0
        );
        createTest(tied_and_out_of_order,1,2,0
            ,0,0
            ,0,1
        );
        createTest(out_of_order_and_in_order,1,2,0
            ,0,1
            ,1,0
        );
        createTest(out_of_order_and_tied,1,2,0
            ,0,1
            ,0,0
        );
        createTest(out_of_order_and_out_of_order,1,2,0
            ,0,1
            ,0,1
        );
    }
}
//@-others

} }
//@-others
//@-leo
