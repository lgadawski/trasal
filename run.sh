#!/bin/bash
#for i in {1..10}
#do
#   	echo `mpiexec -n 1 -host localhost trasal.o >> wyniki1.txt`
#   	echo $i st loop round finished
#done

#for i in {1..10}
#do
#   	echo `mpiexec -n 2 -host localhost trasal.o >> wyniki2.txt`
#	echo $i st loop round finished
#done

#for i in {1..10}
#do
#   	echo `mpiexec -n 4 -host localhost trasal.o >> wyniki4.txt`
#	echo $i st loop round finished
#done

#for i in {1..10}
#do
#   	echo `mpiexec -n 8 -host localhost trasal.o >> wyniki8.txt`
#	echo $i st loop round finished
#done

#for i in {1..10}
#do
#   	echo `mpiexec -n 16 -host localhost trasal.o >> wyniki16.txt`
#	echo $i st loop round finished
#done

echo `mpiexec -n $1 -host localhost trasal.o
