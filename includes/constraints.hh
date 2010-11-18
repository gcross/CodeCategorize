//@+leo-ver=5-thin
//@+node:gcross.20101117113704.1320: * @thin constraints.hh
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101117113704.1321: ** << Includes >>
#include <gecode/set.hh>

#include "operator_space.hh"
//@-<< Includes >>

//@+others
//@+node:gcross.20101117113704.1325: ** Classes
//@+node:gcross.20101117113704.1326: *3* struct CompleteColumnsOperatorSpace
struct CompleteColumnsOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101117113704.1328: *4* (fields)
    SetVarArray column_operator_sets;
    //@+node:gcross.20101117113704.1330: *4* (constructors)
    CompleteColumnsOperatorSpace(int number_of_operators, int number_of_qubits);
    CompleteColumnsOperatorSpace(bool share, CompleteColumnsOperatorSpace& s);
    //@+node:gcross.20101117113704.1332: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101117133000.1502: *3* struct OrderedOperatorSpace
struct OrderedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101117133000.1503: *4* (fields)
    BoolVarArray *intrapair_ties, *interpair_ties;
    int number_of_pairs;
    //@+node:gcross.20101117133000.1504: *4* (constructors)
    OrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    OrderedOperatorSpace(bool share, OrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1510: *4* (methods)
    virtual Space* copy(bool share);
    void postOrderingConstraint(IntVarArgs ordering,BoolVarArray* interpair_ties_,BoolVarArray* intrapair_ties_);
    //@-others

};
//@+node:gcross.20101117133000.1519: *3* struct WeightOrderedOperatorSpace
struct WeightOrderedOperatorSpace : public virtual OrderedOperatorSpace {

    //@+others
    //@+node:gcross.20101117133000.1520: *4* (fields)
    IntVarArray weights;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101117133000.1521: *4* (constructors)
    WeightOrderedOperatorSpace(int number_of_operators, int number_of_qubits, bool exclude_first_column);
    WeightOrderedOperatorSpace(bool share, WeightOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1522: *4* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101117133000.1465: ** Functions
//@+node:gcross.20101117133000.1466: *3* postFirstColumnSpecialCaseConstraint
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m);
//@-others
//@-leo
