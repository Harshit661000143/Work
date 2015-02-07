#!/bin/bash
x=100
while [ $x -le 1000 ]
do
  echo "Welcome $x times"
  x=$(( $x + 100 ))
done
