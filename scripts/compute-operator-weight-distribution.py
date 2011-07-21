#!/usr/bin/python
#@+leo-ver=5-thin
#@+node:gcross.20110707131524.1811: * @thin compute-operator-weight-distribution.py
#@@first
import sys, yaml
for filename in sys.argv[1:]:
    print filename
    with open(filename,"r") as f:
        codes = yaml.load_all(f.read())
    bins = {}
    for code in codes:
        operators = code["Operators"]
        weights = []
        for operator in operators:
            weight = 0
            for c in operator:
                if c != '.': weight += 1
            weights.append(weight)
            del weight
        weights.sort()
        weights.reverse()
        weights = tuple(weights)
        try:
            bin = bins[weights]
        except KeyError:
            bin = []
            bins[weights] = bin
        bin.append(code)
        del bin, weights
    for weights in sorted(bins.keys()):
        for weight in weights: print weight, " ",
        print "| ", len(bins[weights])
#@-leo
