#!/bin/bash
for i in {1..30}
do
   ./zadF.out < ../tests/in/$i.in > ../tests/myout/$i.out
done