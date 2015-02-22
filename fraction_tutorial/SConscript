# define environment
env = Environment()   # Create an environmnet
env = Environment(CCFLAGS='-std=c++11') # use C++ standard 2011
env.Append(CXXFLAGS = ['-g3'])

# define install directory
src_dir = Dir('.').srcnode().abspath
instdir = src_dir + "/install"

# call scons for the sources with export arguments:
# - env: environment above defined
# - instdir: installation directory above defined
SConscript('src/SConscript', exports=['env', 'instdir'])

# call scons for the test with export argument:
# env: environment above defined
SConscript('test/SConscript', exports=['env'])
