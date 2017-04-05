#!/bin/bash

g++ a.cpp -o a -O2
for i in {1..19}
do
	echo $i
	./a < in/${i}.in > out/${i}.out
done
