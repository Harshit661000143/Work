#!/bin/bash
i=100
while [ $i -le 10000 ]
do
./shaho $i 16 >>dashared
./gloho $i 16 >>datrans
./tranho $i 16 >>dabasic
  i=$(( $i + 100 ))
done

