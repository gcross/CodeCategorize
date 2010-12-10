#@+leo-ver=5-thin
#@+node:gcross.20101129164055.1922: * @thin compatibility/make-compatibility-tests.py
from __future__ import print_function
from itertools import combinations_with_replacement

tests = [
    ("FirstColumnXZ","first_column_XZ","OddRows"),
    ("AntiCommutatorCountOrdered","row_ordered/anti_commutator_count",""),
    ("AntiCommutatorCountMinusLastOrdered","row_ordered/anti_commutator_count_minus_last",""),
    ("AntiCommutatorQubitCountSequenceOrdered","row_ordered/anti_commutator_qubit_count_sequence",""),
    ("AntiCommutatorLastOperatorSequenceOrdered","row_ordered/anti_commutator_last_operator_sequence","OddRows"),
    ("FirstColumnXRowOrdered","row_ordered/first_column","OddRows"),
    ("PauliGroupsRowOrdered","row_ordered/pauli_groups",""),
    ("WeightRowOrdered","row_ordered/weight",""),
    ("ColumnOrdered","column_ordered",""),
    ("MinimalWeight","minimal_weight",""),
    ("NonTrivial","non_trivial",""),
    ("XZYOrdered","XZY_ordered",""),
    ]

sources = []

for ((constraint1,file1,subset1),(constraint2,file2,subset2)) in combinations_with_replacement(tests,2):
    if constraint1 == constraint2: continue
    is_row1 = file1.find("row_ordered") > -1
    is_row2 = file2.find("row_ordered") > -1
    if(is_row1 and is_row2): continue
    subset = subset1 or subset2
    source = "{constraint1}-{constraint2}.cc".format(**locals())
    sources.append(source)
    if constraint1 == "FirstColumnXZ":
        command = "runOddRowsCompatibilityTestsForFirstColumnXZAnd({constraint2});"
    else:
        command = "run{subset}CompatibilityTestsFor({constraint1},{constraint2});"
    with open(source,"w") as f: print(("""\
#include "constraints/interactions.hh"
#include "constraints/{file1}.hh"
#include "constraints/{file2}.hh"

"""+command).format(**locals()),file=f)

with open("CMakeLists.txt","w") as f:
    print("set(COMPATIBILITY_SOURCES",file=f)
    for source in sources:
        print("    constraints/compatibility/{}".format(source),file=f)
    print("     PARENT_SCOPE",file=f)
    print(")",file=f)
#@-leo
