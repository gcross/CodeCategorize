#@+leo-ver=5-thin
#@+node:gcross.20101129164055.1921: * @thin commutation/make-commutation-tests.py
from __future__ import print_function
from itertools import combinations_with_replacement

tests = [
    ("AntiCommutatorCountOrdered","row_ordered/anti_commutator_count",""),
    ("AntiCommutatorCountMinusLastOrdered","row_ordered/anti_commutator_count_minus_last","OddRows"),
    ("AntiCommutatorQubitCountSequenceOrdered","row_ordered/anti_commutator_qubit_count_sequence",""),
    ("AntiCommutatorLastOperatorSequenceOrdered","row_ordered/anti_commutator_last_operator_sequence","OddRows"),
    ("FirstColumnXRowOrdered","row_ordered/first_column","OddRows"),
    ("PauliGroupsRowOrdered","row_ordered/pauli_groups",""),
    ("WeightRowOrdered","row_ordered/weight",""),
    ]

sources = []

for ((constraint1,file1,subset1),(constraint2,file2,subset2)) in combinations_with_replacement(tests,2):
    if constraint1 == constraint2: continue
    subset = subset1 or subset2
    if subset and subset1 != subset2: continue
    source = "{constraint1}-{constraint2}.cc".format(**locals())
    sources.append(source);
    with open(source,"w") as f: print("""\
#include "constraints/interactions.hh"
#include "constraints/{file1}.hh"
#include "constraints/{file2}.hh"

run{subset}CommutationTestsFor({constraint1},{constraint2});
""".format(**locals()),file=f)

with open("CMakeLists.txt","w") as f:
    print("set(COMMUTATION_SOURCES",file=f)
    for source in sources:
        print("    constraints/commutation/{}".format(source),file=f)
    print("     PARENT_SCOPE",file=f)
    print(")",file=f)
#@-leo
