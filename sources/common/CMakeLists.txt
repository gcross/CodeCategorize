#@+leo-ver=5-thin
#@+node:gcross.20101123222425.2239: * @thin CMakeLists.txt
add_library(CodeCategorize
    constraints
    operator_space
)
target_link_libraries(CodeCategorize
    gecodesearch
    gecodeint
    gecodekernel
    gecodesupport
    gecodeminimodel
)
#@-leo
