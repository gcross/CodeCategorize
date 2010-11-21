#@+leo-ver=5-thin
#@+node:gcross.20101116210424.1672: * @thin SConstruct
#@@language Python

env = Environment(
            #CCFLAGS="-O3 -funroll-loops"
            CCFLAGS="-g"
        )
import os
for varname in ["CPATH","CPP_INCLUDE_PATH"]:
    if varname in os.environ:
        env.AppendENVPath(varname,os.environ[varname])
env.PrependENVPath("CPATH","includes")
#env.AppendUnique(FRAMEWORKS=Split('gecode'))

#@+at
# Check to make sure that Boost is present.
#@@c
errors = []
conf = Configure(env)
#if not conf.CheckCXXHeader('boost/dynamic_bitset.hpp'):
#   errors.append('You need to download and install the Boost C++ library to use this code.')
#if not conf.CheckCXXHeader('tclap/CmdLine.h'):
#   errors.append('You need to download and install the TCLAP library to use this code.')
if errors:
    for error in errors:
        print error
    Exit(1)

#@+at
# Get our configuration options:
#@@c
opts = Variables('CodeCategorize.conf') # Change wm to the name of your app
opts.Add(PathVariable('PREFIX', 'Directory to install under', '/usr/local', PathVariable.PathIsDir))
opts.Update(env)
opts.Save('CodeCategorize.conf', env) # Save, so user doesn't have to 
                          # specify PREFIX every time
Help(opts.GenerateHelpText(env))

#@+at
# Build the programs:
#@@c
count_all_solutions = env.Program(
    'programs/count-all-solutions',[
    'sources/count-all-solutions.cc',
    'sources/constraints.cc',
    'sources/operator_space.cc',
],LIBS=[
    'gecodesearch','gecodeint','gecodekernel','gecodesupport','gecodeminimodel',
])
count_solutions = env.Program(
    'programs/count-solutions',[
    'sources/count-solutions.cc',
    'sources/constraints.cc',
    'sources/operator_space.cc',
],LIBS=[
    'gecodesearch','gecodeint','gecodekernel','gecodesupport','gecodeminimodel',
])
env.Default([
    count_solutions,
    count_all_solutions,
])

#@+at
# Perform installation:
# idir_prefix = '$PREFIX'
# idir_lib    = '$PREFIX/lib'
# idir_bin    = '$PREFIX/bin'
# idir_inc    = '$PREFIX/include'
# idir_data   = '$PREFIX/share'
# idir_man1   = '$PREFIX/share/man/man1'
# Export('env idir_prefix idir_lib idir_bin idir_inc idir_data')
# 
# env.Install(idir_bin, codequest)
# env.Install(idir_inc, ['src/codequest.hpp'])
# env.Install(idir_man1, ['doc/codequest.1'])
# env.Alias('install', idir_prefix)
#@@c

#@+at
# Testing:
#@@c
test = env.Program('tests/test',[
    'tests/constraints.cc',
    'tests/operator_space.cc',
    'tests/test_utils.cc',
    'sources/constraints.cc',
    'sources/operator_space.cc',
],LIBS=[
    'unit--','unit--main',
    'gecodesearch','gecodeint','gecodekernel','gecodesupport','gecodeminimodel',
])
env.Alias('test',test)
#@-leo
