//@+leo-ver=5-thin
//@+node:gcross.20101209224839.1982: * @thin solution_iterator.hh
//@@language cplusplus

#ifndef SOLUTION_ITERATOR_HH
#define SOLUTION_ITERATOR_HH

//@+<< Includes >>
//@+node:gcross.20101209224839.1983: ** << Includes >>
#include <boost/utility.hpp>
#include <codequest.hpp>
#include <memory>
#include <vector>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

//@+<< Usings >>
//@+node:gcross.20101209224839.1992: ** << Usings >>
using namespace Gecode;
using namespace boost;
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101209224839.1990: ** exception OutOfSolutions
struct OutOfSolutions : public std::exception {
    virtual const char* what() const throw() { return "No more solutions are available."; }
};
//@+node:gcross.20101209224839.1984: ** class SolutionIterator
template<
    class Quantum_operator = dynamic_quantum_operator,
    class Qubit_vector = typename std::vector<qubit<Quantum_operator> >,
    class Operator_vector = typename std::vector<Quantum_operator>,
    class Index_vector = typename std::vector<size_t>
> class SolutionIterator : noncopyable {

    //@+others
    //@+node:gcross.20101209224839.1989: *3* (typedefs)
    public:
        typedef Quantum_operator quantum_operator;
        typedef Qubit_vector qubit_vector;
        typedef Operator_vector operator_vector;
        typedef Index_vector index_vector;

        typedef qec<quantum_operator,qubit_vector,operator_vector,index_vector> qec_t;
    //@+node:gcross.20101209224839.1985: *3* (fields)
    protected:
        DFS<OperatorSpace> dfs;
        auto_ptr<OperatorSpace> space;
        operator_vector operators;
    //@+node:gcross.20101209224839.1986: *3* (constructors)
    public:
        SolutionIterator(auto_ptr<OperatorSpace> initial_space, const Search::Options& options = Search::Options::def)
            : dfs(initial_space.get(),options)
            , space(dfs.next())
        {
            if(*this) {
                space->initializeOperators(operators);
                space->updateOperators(operators);
            }
        }
    //@+node:gcross.20101209224839.1987: *3* (operators)
    public:
        operator bool() const throw() {
            return space.get() != NULL;
        }

        const operator_vector& operator*() const throw(OutOfSolutions) {
            assertNotOutOfSolutions();
            return operators;
        }

        const OperatorSpace* operator->() const throw(OutOfSolutions) {
            return getSpace();
        }

        const quantum_operator& operator[](int i) const throw(OutOfSolutions) {
            return (**this)[i];
        }

        SolutionIterator& operator++() throw(OutOfSolutions) {
            assertNotOutOfSolutions();
            space.reset(dfs.next());
            if(*this) {
                space->updateOperators(operators);
            }
            return *this;
        }
    //@+node:gcross.20101209224839.1991: *3* (methods)
    private:
        void assertNotOutOfSolutions() const throw(OutOfSolutions) {
            if(!(*this)) { throw OutOfSolutions(); }
        }

    public:
        auto_ptr<qec_t> computeCode() const throw(OutOfSolutions) {
            assertNotOutOfSolutions();
            return auto_ptr<qec_t>(new qec_t(operators));
        }

        const OperatorSpace* getSpace() const throw(OutOfSolutions) {
            assertNotOutOfSolutions();
            return space.get();
        }
    //@-others

};
//@-others

}

#endif
//@-leo
