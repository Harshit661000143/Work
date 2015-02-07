#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
int main(int argc,char *argv[]) {
    // Create the two input vectors
    int i,n,m,j;
   
 

m = atoi(argv[1]);   
n=m*m;
    int *A = (int*)malloc(sizeof(int)*n);
    int *B = (int*)malloc(sizeof(int)*n);
    srand(m*10);
    for(i = 0; i < n; i++) 
{
        A[i] = 1;
        B[i] = 1 ;
    }
cl_ulong start=0;
cl_ulong end=0; 
cl_event event; 
 // Load the kernel source code into the array source_str
  const char *source ="__kernel void matrix_add(__global int *A, __global int *B, __global int *C) {int i = get_global_id(0);int m=get_global_size(0);int l=0;int k=0;float value=0;for(k=0;k<m;k++){for(l=0;l<m;l++){value+= A[i*m+l]*B[l*m+k];}C[i*m+k]=value;value=0;}}";

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
   cl_command_queue command_queue = clCreateCommandQueue( context,device_id,0, NULL );

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,n * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, n * sizeof(int), NULL, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, NULL);

    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(int), B, 0, NULL, NULL);
    // Create a program from the kernel source
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, NULL );

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "matrix_add", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
    
    // Execute the OpenCL kernel on the list
    size_t global_item_size = m; // Process the entire lists
  size_t local_item_size = m;//  Process one item at a time
   
 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size, &local_item_size, 0, NULL, NULL);



    // Read the memory buffer C on the device to the local variable C
    int *C = (int*)malloc(sizeof(int)*n);
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, n * sizeof(int), C, 0, NULL, NULL);

    // Display the result to the screen

 printf("A=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
for(j=0;j<m;j++)
{
printf("%d\t",A[i*m+j]);
}}

printf("\nB=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
for(j=0;j<m;j++)
{
printf("%d\t",B[i*m+j]);
}}

printf("\nC=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
for(j=0;j<m;j++)
{
printf("%d\t",C[i*m+j]);
}}
printf("\n");
 
    return 0;
}

