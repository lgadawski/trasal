env = Environment()

#       Add header search path
env.Append(CPPPATH = ['/usr/include', '/usr/local/include'])

#       Add compile-time flags
env.Append(CCFLAGS=['-Wall', '-g', '-pedantic'])

# libraries to link against
# Notice you dont need the '-l', since SCons is platform independent
# env.Append(LIBS=['boost_regex'])

env.Append(CXXFLAGS="-std=c++1y")

#       Add library search path
env.Append(LIBPATH = ['/usr/lib','/usr/local/lib', '/opt/lib'])

# Compile and link the binary
env.Program('trasal',
['src/BitsUtil.h', 'src/Configuration.h', 'src/Configuration.cpp',
'src/Individual.h', 'src/Map.h', 'src/Map.cpp', 'src/trasal.cpp'])
