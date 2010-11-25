//@+leo-ver=5-thin
//@+node:gcross.20101123222425.3274: * @thin utilities.cc
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20101123222425.3275: ** << Includes >>
#include "utilities.hh"
//@-<< Includes >>

namespace CodeCategorize {

using namespace Gecode;

//@+others
//@+node:gcross.20101123222425.3317: ** Functions
//@+node:gcross.20101123222425.3318: *3* choose
int choose(int n,int k) {
    long total = 1;
    for(int i = n; i > n-k; --i) total *= i;
    for(int i = 1; i <= k; ++i) total /= i;
    int total_as_int = (int)total;
    assert(total_as_int == total);
    return total;
}
//@-others

}
//@-leo
