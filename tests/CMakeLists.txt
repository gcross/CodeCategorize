#@+leo-ver=5-thin
#@+node:gcross.20101123173026.1551: * @thin CMakeLists.txt
add_subdirectory("constraints/interactions")

#@+others
#@+node:gcross.20101128153132.1775: ** test
set(test-SOURCES
    column_pauli_sets.cc
    commutator.cc
    constraints.cc
    constraints/column_ordered.cc
    constraints/minimal_weight.cc
    constraints/row_ordered.cc
    constraints/row_ordered/anti_commutator_count.cc
    constraints/row_ordered/anti_commutator_count_minus_last.cc
    constraints/row_ordered/anti_commutator_last_operator_sequence.cc
    constraints/row_ordered/first_column.cc
    constraints/row_ordered/pauli_groups.cc
    constraints/row_ordered/weight.cc
    constraints/row_ordered/weight_and_first_column.cc
    constraints/special_case_XZ.cc
    constraints/XZY_ordered.cc
    operator_space.cc
    test_utils.cc
    test_utils_tests.cc
)

add_executable(test EXCLUDE_FROM_ALL ${test-SOURCES})
target_link_libraries(test CodeCategorize unit-- unit--main interactions)
set_property(TARGET test PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
#@+node:gcross.20101128153132.1776: ** test-constraint-interactions
set(test-constraint-interactions-SOURCES
    ${INTERACTIONS_SOURCES} 
    test_utils.cc
)

add_executable(test-constraint-interactions EXCLUDE_FROM_ALL ${test-constraint-interactions-SOURCES})
target_link_libraries(test-constraint-interactions CodeCategorize unit-- unit--main)
set_property(TARGET test-constraint-interactions PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
#@+node:gcross.20101128173348.1867: ** test-constraints-row-ordered
set(test-constraints-row-ordered-SOURCES
    constraints/row_ordered.cc
    constraints/row_ordered/anti_commutator_count.cc
    constraints/row_ordered/anti_commutator_count_minus_last.cc
    constraints/row_ordered/anti_commutator_last_operator_sequence.cc
    constraints/row_ordered/first_column.cc
    constraints/row_ordered/pauli_groups.cc
    constraints/row_ordered/weight.cc
    constraints/row_ordered/weight_and_first_column.cc
    test_utils.cc
)

add_executable(test-constraints-row-ordered EXCLUDE_FROM_ALL ${test-constraints-row-ordered-SOURCES})
target_link_libraries(test-constraints-row-ordered CodeCategorize unit-- unit--main)
set_property(TARGET test-constraints-row-ordered PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
#@-others
#@-leo
