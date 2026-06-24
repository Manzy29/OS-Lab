echo "enter the value of N to find the prime numbers from 1 to N"
read N
flag=0
echo "the prime numbers from 1 to $N are:"
echo
for((i=2;i<=N;i++)); do
    for((j=2;j<=$((i/2));j++)); do
        if [ $((i%j)) == 0 ]; then
            flag=1
            break
        fi
    done
    if [ $flag == 0 ]; then
        echo -ne " $i"
    fi
    flag=0
done
