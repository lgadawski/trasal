mpi = ARGUMENTS.get('mpi', 0)
if int(mpi) :
	env = Environment(CXX =
	'mpic++'
	
	)
else :
	env = Environment(CXX =
	'g++'
	)

omp = ARGUMENTS.get('omp', 0)

env.Append(CXXFLAGS = [
'-std=c++14'
# , '-stdlib=libc++' ## need for clang compiler
])

# Add header search path
env.Append(CPPPATH = [
'/usr/include',
'/usr/local/include'
])

env.Append(CCFLAGS = [
	'-Wall',
	'-g',
	'-pedantic',
	'-fdiagnostics-color=always',
	])

# Add compile-time flags
if int(omp):
	env.Append(CCFLAGS = [
	'-fopenmp',
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
