#@+leo-ver=5-thin
#@+node:gcross.20101123222425.2237: * @thin CMakeLists.txt
macro(makeProgram program-name)
    add_executable(${program-name} ${program-name}.cc)
    target_link_libraries(${program-name} CodeCategorize)
    set_property(TARGET ${program-name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ../../programs)
endmacro(makeProgram)

makeProgram(count-solutions)
makeProgram(count-all-solutions)
makeProgram(print-solutions)
#@-leo
