//@+leo-ver=5-thin
//@+node:gcross.20101116210424.1511: * @thin operator_space.hh
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101116210424.1512: ** << Includes >>
#include <gecode/int.hh>
#include <gecode/search.hh>

using namespace Gecode;
//@-<< Includes >>

//@+others
//@+node:gcross.20101116210424.1513: ** struct OperatorSpace
struct OperatorSpace : public Space {

    //@+others
    //@+node:gcross.20101116210424.1674: *3* (fields)
    BoolVarArray X, Z;
    IntVarArray O;

    int number_of_operators, number_of_qubits, number_of_variables;
    //@+node:gcross.20101116210424.1675: *3* (constructors)
    OperatorSpace(int number_of_operators, int number_of_qubits);
    OperatorSpace(bool share, OperatorSpace& s);
    //@+node:gcross.20101116222338.1275: *3* copy
    virtual Space* copy(bool share);
    //@-others

};
//@-others
//@-leo
