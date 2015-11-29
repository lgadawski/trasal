env = Environment(CXX =
# 'clang++-3.5'
'g++'
)

env.Append(CXXFLAGS = [
'-std=c++14'
# , '-stdlib=libc++' ## need for clang compiler
])

# Add header search path
env.Append(CPPPATH = [
'/usr/include',
'/usr/local/include'
])

# Add compile-time flags
env.Append(CCFLAGS = [
'-fopenmp',
'-Wall',
'-g',
'-pedantic',
'-fdiagnostics-color=always',
'-fopenmp'
])

env.Append(LINKFLAGS = [
'-fopenmp'
])

env.Append(LINKFLAGS = [
'-fopenmp'
])

# libraries to link against
# Notice you dont need the '-l', since SCons is platform independent
env.Append(LIBS=[
'boost_program_options'
])


# Add library search path
env.Append(LIBPATH = [
'/usr/lib',
'/usr/local/lib',
'/opt/lib'
])

# Compile and link the binary
env.Program('trasal.o', [
'src/Configuration.cpp',
'src/Individual.cpp',
'src/utils.cpp',
'src/Map.cpp',
'src/Population.cpp',
'src/GeneticAlgorithm.cpp',
'src/trasal.cpp'
])
