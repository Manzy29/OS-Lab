#!/bin/bash
read -p "Enter n: " n
n1=0
n2=1
echo -e "the fibonacci series:\n$n1\n$n2"
for((i=2;i<=n;i++)); do
    n3=$((n1+n2))
echo $n3
n1=$n2
n2=$n3
done
