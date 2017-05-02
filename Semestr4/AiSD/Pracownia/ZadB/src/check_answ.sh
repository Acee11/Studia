#!/bin/bash
for i in `seq 1 48`; do
	./zadB.out < ../tests/in/$i.in && cat ../tests/out/$i.out
	echo '\n'
done