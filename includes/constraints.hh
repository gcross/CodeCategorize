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
//@+node:gcross.20101117133000.1465: ** Functions
//@+node:gcross.20101117133000.1466: *3* postFirstColumnSpecialCaseConstraint
void postFirstColumnSpecialCaseConstraint(OperatorSpace& m);
//@-others
//@-leo
