from sys import argv

number_of_qubits = int(argv[1])
number_of_operators = int(argv[2])

try:
    maximum_weight = int(argv[3])
    job_name = "scan-{number_of_qubits}-{number_of_operators}-{maximum_weight}".format(**locals())
except ValueError:
    maximum_weight = ""
    job_name = "scan-{number_of_qubits}-{number_of_operators}".format(**locals())

print """\
#PBS -d /home/gcross/Projects/QC/CodeQuest/CodeCategorize
#PBS -N {job_name}
#PBS -e logs/err/{job_name}
#PBS -o logs/out/{job_name}

programs/scan {number_of_qubits} {number_of_operators} {maximum_weight}
""".format(**locals())
