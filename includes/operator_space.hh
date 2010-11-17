//@+leo-ver=4-thin
//@+node:gcross.20101116210424.1511:@thin operator_space.hh
//@@language cplusplus

//@<< Includes >>
//@+node:gcross.20101116210424.1512:<< Includes >>
#include <gecode/int.hh>
#include <gecode/search.hh>

using namespace Gecode;
//@nonl
//@-node:gcross.20101116210424.1512:<< Includes >>
//@nl

//@+others
//@+node:gcross.20101116210424.1513:struct OperatorSpace
struct OperatorSpace : public Space {

    //@    @+others
    //@+node:gcross.20101116210424.1674:(fields)
    BoolVarArray X, Z;

    int number_of_operators, number_of_qubits;
    //@nonl
    //@-node:gcross.20101116210424.1674:(fields)
    //@+node:gcross.20101116210424.1675:(constructor)
    OperatorSpace(int number_of_operators, int number_of_qubits);
    //@nonl
    //@-node:gcross.20101116210424.1675:(constructor)
    //@-others

};
//@nonl
//@-node:gcross.20101116210424.1513:struct OperatorSpace
//@-others
//@nonl
//@-node:gcross.20101116210424.1511:@thin operator_space.hh
//@-leo
