y='100 200 500 1000 2000 5000 7000 8000 '
for i in $y
do
 echo "size=$i" >> data1 
./matmul $i 16 >>data1
echo "size=$i" >> data2
./matmul_tr $i 16 >>data2
done

