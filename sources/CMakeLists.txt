#@+leo-ver=5-thin
#@+node:gcross.20101123173026.1549: * @thin CMakeLists.txt
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

add_executable(count-solutions count-solutions.cc)
target_link_libraries(count-solutions CodeCategorize)
set_property(TARGET count-solutions PROPERTY RUNTIME_OUTPUT_DIRECTORY ../programs)

add_executable(count-all-solutions count-all-solutions.cc)
target_link_libraries(count-all-solutions CodeCategorize)
set_property(TARGET count-all-solutions PROPERTY RUNTIME_OUTPUT_DIRECTORY ../programs)

add_executable(print-solutions print-solutions.cc)
target_link_libraries(print-solutions CodeCategorize)
set_property(TARGET print-solutions PROPERTY RUNTIME_OUTPUT_DIRECTORY ../programs)
#@-leo
