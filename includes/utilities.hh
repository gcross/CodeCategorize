//@+leo-ver=5-thin
//@+node:gcross.20101123222425.2564: * @thin utilities.hh
//@@language cplusplus

#ifndef UTILITIES_HH
#define UTILITIES_HH

//@+<< Includes >>
//@+node:gcross.20101123222425.2565: ** << Includes >>
#include <gecode/set.hh>
#include <memory>
#include <utility>
#include <vector>

#include "operator_space.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.2609: ** Functions
int choose(int n,int k);
long countSolutions(auto_ptr<OperatorSpace> space, const Search::Options& options = Search::Options::def);
//@-others

}

#endif
//@-leo
