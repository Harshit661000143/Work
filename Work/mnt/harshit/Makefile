CC=gcc
CFLAGS=-O3

matmul_tr:	buff
	$(CC) $(CFLAGS) -L /usr/local/cuda3.2/cuda/lib/ -l OpenCL buff -o matmul_tr -lm
buff: sharedr.c
	$(CC) $(CFLAGS) -c -I /usr/local/cuda3.2/cuda/include/ sharedr.c  -o buff 


matmul:	buff1
	$(CC) $(CFLAGS) -L /usr/local/cuda3.2/cuda/lib/ -l OpenCL buff1 -o matmul -lm
buff1: shared.c
	$(CC) $(CFLAGS) -c -I /usr/local/cuda3.2/cuda/include/ shared.c  -o buff1 
clean:
	$(RM) buff buff1 matmul matmul_tr 
