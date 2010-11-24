#@+leo-ver=5-thin
#@+node:gcross.20101123173026.1551: * @thin CMakeLists.txt
add_executable(test EXCLUDE_FROM_ALL
    test_utils.cc
    constraints.cc
    operator_space.cc
)
target_link_libraries(test CodeCategorize unit-- unit--main)
set_property(TARGET test PROPERTY RUNTIME_OUTPUT_DIRECTORY ..)
#@-leo
