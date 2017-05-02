#!/bin/bash
for i in `seq 1 $1`;
do
	echo i = $i
	echo my answers:
	./zadC.out < ../tests/in/gra$i.in
	echo correct answers:
	cat ../tests/out/gra$i.out
	printf '\n\n'
done