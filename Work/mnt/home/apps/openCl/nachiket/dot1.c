#include<stdio.h>
#include<stdlib.h>
main(int argc, char **argv)
{
int i;
float j;
int n=atoi(argv[1]);
float *A = (float*)malloc(sizeof(float)*n);
    float *B = (float*)malloc(sizeof(float)*n);
    for(i = 0; i < n; i++) {
        A[i] = 1;
        B[i] = 1 ;
    }
for(i=0;i<n;i++)
{
j+=A[i]*B[i];
}
printf("%f",j);
return 0;
}

