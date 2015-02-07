CC=gcc
CFLAGS=-O3

global:	glo
	$(CC) $(CFLAGS) -L /usr/local/cuda3.2/cuda/lib/ -l OpenCL glo -o gloho -lm
glo: glob.c
	$(CC) $(CFLAGS) -c -I /usr/local/cuda3.2/cuda/include/ glob.c  -o glo 


shared:	sha
	$(CC) $(CFLAGS) -L /usr/local/cuda3.2/cuda/lib/ -l OpenCL sha -o shaho -lm
sha: matmul.c
	$(CC) $(CFLAGS) -c -I /usr/local/cuda3.2/cuda/include/ matmul.c  -o sha 
clean:
	$(RM) glo gloho sha shaho tran tranho
cleanfile:
	$(RM) global shared trantext serial
trans: tran
	$(CC) $(CFLAGS) -L /usr/local/cuda3.2/cuda/lib/ -l OpenCL tran -o tranho -lm
tran: shared.c
	 $(CC) $(CFLAGS) -c -I /usr/local/cuda3.2/cuda/include/ shared.c -o tran
