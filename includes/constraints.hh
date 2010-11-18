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
//@+node:gcross.20101117133000.1607: *3* Row ordering constraints
//@+node:gcross.20101117133000.1502: *4* struct RowOrderedOperatorSpace
struct RowOrderedOperatorSpace : public virtual OperatorSpace {

    //@+others
    //@+node:gcross.20101117133000.1503: *5* (fields)
    BoolVarArray *intrapair_ties, *interpair_ties;
    int number_of_pairs;
    //@+node:gcross.20101117133000.1504: *5* (constructors)
    RowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    RowOrderedOperatorSpace(bool share, RowOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1510: *5* (methods)
    virtual Space* copy(bool share);
    void postOrderingConstraint(IntVarArgs ordering,BoolVarArray* interpair_ties_,BoolVarArray* intrapair_ties_);
    //@-others

};
//@+node:gcross.20101117133000.1519: *4* struct WeightRowOrderedOperatorSpace
struct WeightRowOrderedOperatorSpace : public virtual RowOrderedOperatorSpace {

    //@+others
    //@+node:gcross.20101117133000.1520: *5* (fields)
    IntVarArray weights;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101117133000.1521: *5* (constructors)
    WeightRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits, bool exclude_first_column);
    WeightRowOrderedOperatorSpace(bool share, WeightRowOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1522: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101117133000.1551: *4* struct FirstColumnXRowOrderedOperatorSpace
struct FirstColumnXRowOrderedOperatorSpace : public virtual RowOrderedOperatorSpace {

    //@+others
    //@+node:gcross.20101117133000.1552: *5* (fields)
    IntVarArray first_column_X;
    BoolVarArray interpair_ties, intrapair_ties;
    //@+node:gcross.20101117133000.1553: *5* (constructors)
    FirstColumnXRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    FirstColumnXRowOrderedOperatorSpace(bool share, FirstColumnXRowOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1554: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101117133000.1576: *4* struct WeightAndFirstColumnXRowOrderedOperatorSpace
struct WeightAndFirstColumnXRowOrderedOperatorSpace
    : public WeightRowOrderedOperatorSpace
    , public FirstColumnXRowOrderedOperatorSpace
{

    //@+others
    //@+node:gcross.20101117133000.1578: *5* (constructors)
    WeightAndFirstColumnXRowOrderedOperatorSpace(int number_of_operators, int number_of_qubits);
    WeightAndFirstColumnXRowOrderedOperatorSpace(bool share, WeightAndFirstColumnXRowOrderedOperatorSpace& s);
    //@+node:gcross.20101117133000.1580: *5* (methods)
    virtual Space* copy(bool share);
    //@-others

};
//@+node:gcross.20101117133000.1465: ** Functions
//@+node:gcross.20101117133000.1466: *3* postFirstColumnSpecialCaseConstraint
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m);
//@-others
//@-leo
