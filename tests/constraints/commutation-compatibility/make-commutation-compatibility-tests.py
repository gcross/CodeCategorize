#@+leo-ver=5-thin
#@+node:gcross.20101209010739.1843: * @thin commutation-compatibility/make-commutation-compatibility-tests.py
from __future__ import print_function
from itertools import combinations_with_replacement, product

normal_constraints = [
    ("ColumnOrdered","column_ordered",""),
    ("FirstColumnXZ","first_column_XZ","OddRows"),
    ("MinimalWeight","minimal_weight",""),
    ("NonTrivial","non_trivial",""),
    ("XZYOrdered","XZY_ordered",""),
    ]

ordering_constraints = [
    ("AntiCommutatorCountOrdered","row_ordered/anti_commutator_count",""),
    ("AntiCommutatorCountMinusLastOrdered","row_ordered/anti_commutator_count_minus_last","OddRows"),
    ("AntiCommutatorQubitCountSequenceOrdered","row_ordered/anti_commutator_qubit_count_sequence",""),
    ("AntiCommutatorLastOperatorSequenceOrdered","row_ordered/anti_commutator_last_operator_sequence","OddRows"),
    ("FirstColumnXRowOrdered","row_ordered/first_column","OddRows"),
    ("PauliGroupsRowOrdered","row_ordered/pauli_groups",""),
    ("WeightRowOrdered","row_ordered/weight",""),
    ]

sources = []

for ((constraint1,file1,subset1),((constraint2,file2,subset2),(constraint3,file3,subset3))) in product(normal_constraints,combinations_with_replacement(ordering_constraints,2)):
    if constraint2 == constraint3: continue
    subset = subset1 or subset2 or subset3
    source = "{constraint1}-{constraint2}-{constraint3}.cc".format(**locals())
    sources.append(source);
    if constraint1 == "FirstColumnXZ":
        command = "runOddRowsCommutationCompatibilityTestsForFirstColumnXZAnd({constraint2},{constraint3});"
    else:
        command = "run{subset}CommutationCompatibilityTestsFor({constraint1},{constraint2},{constraint3});"
    with open(source,"w") as f: print(("""\
#include "constraints/interactions.hh"
#include "constraints/{file1}.hh"
#include "constraints/{file2}.hh"
#include "constraints/{file3}.hh"

"""+command).format(**locals()),file=f)

with open("CMakeLists.txt","w") as f:
    print("set(COMMUTATION_COMPATIBILITY_SOURCES",file=f)
    for source in sources:
        print("    constraints/commutation-compatibility/{}".format(source),file=f)
    print("     PARENT_SCOPE",file=f)
    print(")",file=f)
#@-leo
