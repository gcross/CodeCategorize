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

    //@+others
    //@+node:gcross.20101128193219.1812: *4* 1 constraint
    subSuite(_1_constraint) {
        createTest(_10,1,1,1
            ,1,0
        );
        createTest(_01,1,1,0
            ,0,1
        );
    }
    //@+node:gcross.20101128193219.1813: *4* 2 constraints
    subSuite(_2_constraints) {
        createTest(_10_10,1,2,1
            ,1,0
            ,1,0
        );
        createTest(_10_00,1,2,1
            ,1,0
            ,0,0
        );
        createTest(_10_01,1,2,1
            ,1,0
            ,0,1
        );
        createTest(_00_10,1,2,1
            ,0,0
            ,1,0
        );
        createTest(_00_00,1,2,1
            ,0,0
            ,0,0
        );
        createTest(_00_01,1,2,0
            ,0,0
            ,0,1
        );
        createTest(_01_10,1,2,0
            ,0,1
            ,1,0
        );
        createTest(_01_00,1,2,0
            ,0,1
            ,0,0
        );
        createTest(_01_01,1,2,0
            ,0,1
            ,0,1
        );
    }
    //@+node:gcross.20101128193219.1814: *4* 3 constraints
    subSuite(_3_constraints) {
        createTest(_00_00_10,1,3,1
            ,0,0
            ,0,0
            ,1,0
        );
        createTest(_00_00_00,1,3,1
            ,0,0
            ,0,0
            ,0,0
        );
        createTest(_00_00_01,1,3,0
            ,0,0
            ,0,0
            ,0,1
        );
        createTest(_01_00_10,1,3,0
            ,0,1
            ,0,0
            ,1,0
        );
    }
    //@-others

}
//@+node:gcross.20101128193219.1815: *3* 2 pairs
subSuite(_2_pairs) {

    //@+others
    //@+node:gcross.20101128193219.1817: *4* 1 constraint
    subSuite(_1_constraint) {
        createTest(_1010,2,1,1
            ,1,0,1,0
        );
        createTest(_1000,2,1,1
            ,1,0,0,0
        );
        createTest(_1001,2,1,0
            ,1,0,0,1
        );
        createTest(_0010,2,1,0
            ,0,0,1,0
        );
        createTest(_0000,2,1,1
            ,0,0,0,0
        );
        createTest(_0001,2,1,0
            ,0,0,0,1
        );
        createTest(_0110,2,1,0
            ,0,1,1,0
        );
        createTest(_0100,2,1,0
            ,0,1,0,0
        );
        createTest(_0101,2,1,0
            ,0,1,0,1
        );
    }
    //@+node:gcross.20101128193219.1819: *4* 2 constraints
    subSuite(_2_constraints) {
        createTest(_1010_0101,2,2,1
            ,1,0,1,0
            ,0,1,0,1
        );
        createTest(_1010_0110,2,2,0
            ,1,0,1,0
            ,0,1,1,0
        );
        createTest(_1010_1010,2,2,1
            ,1,0,1,0
            ,1,0,1,0
        );
        createTest(_1010_1001,2,2,1
            ,1,0,1,0
            ,1,0,0,1
        );
        createTest(_0000_0101,2,2,0
            ,0,0,0,0
            ,0,1,0,1
        );
        createTest(_0000_1010,2,2,1
            ,0,0,0,0
            ,1,0,1,0
        );
        createTest(_1110_0101,2,2,0
            ,1,1,1,0
            ,0,1,0,1
        );
        createTest(_1110_0001,2,2,1
            ,1,1,1,0
            ,0,0,0,1
        );
        createTest(_1110_1011,2,2,1
            ,1,1,1,0
            ,1,0,1,1
        );
    }
    //@+node:gcross.20101128193219.1821: *4* 3 constraints
    subSuite(_3_constraints) {
        createTest(_1010_0101_0100,2,3,1
            ,1,0,1,0
            ,0,1,0,1
            ,0,1,0,0
        );
        createTest(_1010_0101_0001,2,3,0
            ,1,0,1,0
            ,0,1,0,1
            ,0,0,0,1
        );
        createTest(_1010_0101_1000,2,3,1
            ,1,0,1,0
            ,0,1,0,1
            ,1,0,0,0
        );
        createTest(_1010_1001_0001,2,3,1
            ,1,0,1,0
            ,1,0,0,1
            ,0,0,0,1
        );
    }
    //@-others

}
//@+node:gcross.20101128193219.1822: *3* 3 pairs
subSuite(_3_pairs) {

    //@+others
    //@+node:gcross.20101128193219.1824: *4* 1 constraint
    subSuite(_1_constraint) {
        createTest(_111000,3,1,1
            ,1,1,1,0,0,0
        );
        createTest(_111100,3,1,1
            ,1,1,1,1,0,0
        );
        createTest(_110010,3,1,0
            ,1,1,0,0,1,0
        );
    }
    //@+node:gcross.20101128193219.1826: *4* 2 constraints
    subSuite(_2_constraints) {
        createTest(_111000_011011,3,2,0
            ,1,1,1,0,0,0
            ,0,1,1,0,1,1
        );
        createTest(_101000_011011,3,2,0
            ,1,0,1,0,0,0
            ,0,1,1,0,1,1
        );
        createTest(_101000_010111,3,2,1
            ,1,0,1,0,0,0
            ,0,1,0,1,1,1
        );
        createTest(_011000_010111,3,2,0
            ,0,1,1,0,0,0
            ,0,1,0,1,1,1
        );
        createTest(_111000_010111,3,2,0
            ,1,1,1,0,0,0
            ,0,1,0,1,1,1
        );
        createTest(_111000_010101,3,2,0
            ,1,1,1,0,0,0
            ,0,1,0,1,0,1
        );
        createTest(_111000_010110,3,2,0
            ,1,1,1,0,0,0
            ,0,1,0,1,1,0
        );
        createTest(_111000_100110,3,2,1
            ,1,1,1,0,0,0
            ,1,0,0,1,1,0
        );
    }
    //@+node:gcross.20101128193219.1828: *4* 3 constraints
    subSuite(_3_constraints) {
        createTest(_111000_011011_111000,3,3,0
            ,1,1,1,0,0,0
            ,0,1,1,0,1,1
            ,1,1,1,0,0,0
        );
        createTest(_110000_011011_111000,3,3,0
            ,1,1,0,0,0,0
            ,0,1,1,0,1,1
            ,1,1,1,0,0,0
        );
        createTest(_110000_011110_111000,3,3,0
            ,1,1,0,0,0,0
            ,0,1,1,1,1,0
            ,1,1,1,0,0,0
        );
        createTest(_110000_101110_111000,3,3,1
            ,1,1,0,0,0,0
            ,1,0,1,1,1,0
            ,1,1,1,0,0,0
        );
        createTest(_110000_101110_110100,3,3,0
            ,1,1,0,0,0,0
            ,1,0,1,1,1,0
            ,1,1,0,1,0,0
        );
        createTest(_110000_111010_110100,3,3,1
            ,1,1,0,0,0,0
            ,1,1,1,0,1,0
            ,1,1,0,1,0,0
        );
        createTest(_110000_011010_111010,3,3,0
            ,1,1,0,0,0,0
            ,0,1,1,0,1,0
            ,1,1,0,0,1,0
        );
    }
    //@-others

}
//@-others

} }
//@-others
//@-leo
