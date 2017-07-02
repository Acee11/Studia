#!/bin/bash
for i in `seq 1 39`;
do
	(./zadD.out < ../tests/in/$i.in) > ../tests/myans/$i.out
done