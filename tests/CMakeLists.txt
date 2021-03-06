#@+leo-ver=5-thin
#@+node:gcross.20101123173026.1551: * @thin CMakeLists.txt
#@+<< Macros >>
#@+node:gcross.20101128193219.1847: ** << Macros >>
macro(makeTestProgram program-name)
    add_executable(${program-name} EXCLUDE_FROM_ALL ${${program-name}-SOURCES})
    target_link_libraries(${program-name} CodeCategorize illuminate-main illuminate ${Boost_LIBRARIES})
    set_property(TARGET ${program-name} PROPERTY RUNTIME_OUTPUT_DIRECTORY .)
endmacro(makeTestProgram)
#@-<< Macros >>

#@+<< Includes >>
#@+node:gcross.20101128193219.1850: ** << Includes >>
add_subdirectory("constraints/compatibility")
add_subdirectory("constraints/commutation")
add_subdirectory("constraints/commutation-compatibility")
include_directories(".")
#@-<< Includes >>

#@+others
#@+node:gcross.20101128153132.1775: ** test
set(test-SOURCES
    column_pauli_sets.cc
    commutator.cc
    constraints/column_ordered.cc
    constraints/first_column_XZ.cc
    constraints/minimal_weight.cc
    constraints/non_trivial.cc
    constraints/row_ordered.cc
    constraints/row_ordered/anti_commutator_count.cc
    constraints/row_ordered/anti_commutator_count_minus_last.cc
    constraints/row_ordered/anti_commutator_last_operator_sequence.cc
    constraints/row_ordered/first_column.cc
    constraints/row_ordered/pauli_groups.cc
    constraints/row_ordered/weight.cc
    constraints/XZY_ordered.cc
    operator_space.cc
    test_utils.cc
    test_utils_tests.cc
)

makeTestProgram(test)
#@+node:gcross.20101128153132.1776: ** test-constraint-compatibility
set(test-constraint-compatibility-SOURCES
    ${COMPATIBILITY_SOURCES} 
    test_utils.cc
)

makeTestProgram(test-constraint-compatibility)
#@+node:gcross.20101128193219.1849: ** test-constraint-commutation
set(test-constraint-commutation-SOURCES
    ${COMMUTATION_SOURCES} 
    test_utils.cc
)

makeTestProgram(test-constraint-commutation)
#@+node:gcross.20101209010739.1845: ** test-constraint-commutation-compatability
set(test-constraint-commutation-compatibility-SOURCES
    ${COMMUTATION_COMPATIBILITY_SOURCES}
    test_utils.cc
)

makeTestProgram(test-constraint-commutation-compatibility)
#@+node:gcross.20101128173348.1867: ** test-constraints-row-ordered
set(test-constraints-row-ordered-SOURCES
    constraints/row_ordered.cc
    constraints/row_ordered/anti_commutator_count.cc
    constraints/row_ordered/anti_commutator_count_minus_last.cc
    constraints/row_ordered/anti_commutator_last_operator_sequence.cc
    constraints/row_ordered/first_column.cc
    constraints/row_ordered/pauli_groups.cc
    constraints/row_ordered/weight.cc
    test_utils.cc
)

makeTestProgram(test-constraints-row-ordered)
#@-others
#@-leo
