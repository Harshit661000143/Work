#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int main(int argc,char *argv[])
{
int m= atoi(argv[1]);
int n=m*m,j,k,i;
    int *A = (int*)malloc(sizeof(int)*n);
    int *B = (int*)malloc(sizeof(int)*n);
    int *C = (int*)malloc(sizeof(int)*n);

      struct timeval start,stop;
       
     for(i=0;i<n;i++)
            {
               A[i]=rand()%10;
               B[i]=rand()%10;                
            }
        
gettimeofday(&start,0);
       
        for(i=0;i<m;i++)
        {
            for(j=0;j<m;j++)
            {
                for(k=0;k<m;k++)
                {
                    C[i*m+j]+=A[i*m+k]*B[k*m+j];
                
                } 
             }
        }
gettimeofday(&stop,0);
printf("%d %.6f\n",m,(stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
 
/*printf("\nA matrix\n");   
   for(i=0;i<n;i++)
 {
   printf("%d\t",A[i]);   
 if((i+1)%m==0)
        printf("\n");
 
 }
printf("\nB matrix\n");
   for(i=0;i<n;i++)
 {
       
    printf("%d\t",B[i]); 
if((i+1)%m==0)
        printf("\n");
 }
printf("\nC matrix\n");
   for(i=0;i<n;i++)
 {
      
    printf("%d\t",C[i]); 
if((i+1)%m==0)
        printf("\n");

 }
*/
}
