#@+leo-ver=5-thin
#@+node:gcross.20101123222425.2237: * @thin CMakeLists.txt
add_executable(count-solutions count-solutions.cc)
target_link_libraries(count-solutions CodeCategorize)
set_property(TARGET count-solutions PROPERTY RUNTIME_OUTPUT_DIRECTORY ../../programs)

add_executable(count-all-solutions count-all-solutions.cc)
target_link_libraries(count-all-solutions CodeCategorize)
set_property(TARGET count-all-solutions PROPERTY RUNTIME_OUTPUT_DIRECTORY ../../programs)

add_executable(print-solutions print-solutions.cc)
target_link_libraries(print-solutions CodeCategorize)
set_property(TARGET print-solutions PROPERTY RUNTIME_OUTPUT_DIRECTORY ../../programs)
#@-leo
