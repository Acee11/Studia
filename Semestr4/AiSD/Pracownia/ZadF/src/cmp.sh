#!/bin/bash
for i in {1..30}
do
   cmp ../tests/out/$i.out ../tests/myout/$i.out
done