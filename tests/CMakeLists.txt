#@+leo-ver=5-thin
#@+node:gcross.20101123173026.1551: * @thin CMakeLists.txt
#@+others
#@+node:gcross.20101128153132.1775: ** (all)
add_executable(test EXCLUDE_FROM_ALL
    "column_pauli_sets.cc"
    "commutator.cc"
    "constraint_interactions.cc"
    "constraints.cc"
    "constraints/column_ordered.cc"
    "constraints/minimal_weight.cc"
    "constraints/row_ordered.cc"
    "constraints/special_case_XZ.cc"
    "constraints/XZY_ordered.cc"
    "operator_space.cc"
    "test_utils.cc"
    "test_utils_tests.cc"
)
target_link_libraries(test CodeCategorize unit-- unit--main)
set_property(TARGET test PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
#@+node:gcross.20101128153132.1776: ** constraint-interactions
add_executable(test-constraint-interactions EXCLUDE_FROM_ALL
    "constraint_interactions.cc"
    "test_utils.cc"
)
target_link_libraries(test-interactions CodeCategorize unit-- unit--main)
set_property(TARGET test-interactions PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
#@-others
#@-leo
