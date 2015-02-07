__kernel void max( __global int *A,__global int *max)
{
int i = get_global_id(0); 
A[i]=i;
}
