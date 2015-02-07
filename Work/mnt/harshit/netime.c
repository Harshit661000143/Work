#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
int main(int argc,char *argv[]) {
    // Create the two input vectors
    int i,n,m,j;
   
cl_ulong start1,start2,start3,end1,end2,end3,start4,end4; 

cl_event event1,event2,event3,event4; 

m = atoi(argv[1]);   
n=m*m;
    int *A = (int*)malloc(sizeof(int)*n);
    int *B = (int*)malloc(sizeof(int)*n);
    int *S = (int*)malloc(sizeof(int)*m);

    for(i = 0; i < n; i++) 
    
        A[i] = 1;
        B[i] = 1;
    }

 // Load the kernel source code into the array source_str
  const char *source ="__kernel void matrix_add(__global int *A, __global int *B, __global int *C,__local int *S) {int i = get_global_id(0);int x=get_global_id(1);int m=get_global_size(0);int l=0;float value=0;for(l=0;l<m;l++){value+= A[x*m+l]*B[l*m+i];}C[x*m+i]=value;}";

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
   cl_command_queue command_queue = clCreateCommandQueue( context,device_id,CL_QUEUE_PROFILING_ENABLE, NULL );

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,n * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, n * sizeof(int), NULL, &ret);

    cl_mem s_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, m * sizeof(int), NULL, &ret);
    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, &event1);
ret=clWaitForEvents(1, &event1);
if(ret!=CL_SUCCESS)
{
printf("wrong");}
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start1, NULL);
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end1, NULL); 

ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(int), B, 0, NULL, &event2);
 ret=clWaitForEvents(1, &event2);
if(ret!=CL_SUCCESS)
{
printf("wrong");}
clGetEventProfilingInfo(event2, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start2, NULL);
clGetEventProfilingInfo(event2, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end2, NULL); 
   
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
    ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), NULL);
    
    // Execute the OpenCL kernel on the list
    size_t globalWorkSize[2];
//ze_t localWorkSize[2];
// localWorkSize[0]=m;
   // localWorkSize[1]=2;
    globalWorkSize[0]=m;
    globalWorkSize[1]=m;
 // Process the entire lists
//  size_t local_item_size = 1;//  Process one item at a time
   
 ret = clEnqueueNDRangeKernel(command_queue, kernel,2, NULL,globalWorkSize,globalWorkSize, 0, NULL, &event3);

ret=clWaitForEvents(1, &event3);
if(ret!=CL_SUCCESS)
{
printf("wrong");}
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start3, NULL);
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end3, NULL); 
    // Read the memory buffer C on the device to the local variable C
    int *C = (int*)malloc(sizeof(int)*n);
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, n * sizeof(int), C, 0, NULL, &event4);
ret=clWaitForEvents(1, &event4);
if(ret!=CL_SUCCESS)
{
printf("wrong");}
clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start4, NULL);
clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end4, NULL); 
   
 // Display the result to the screen
#ifdef PRINT
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
#endif
printf("\n");
 float time1 =((end1 - start1)*1.0e-6f); 
printf("time of copying A is %f [ms]\n",time1);
 float time2 =((end2 - start2)*1.0e-6f); 
printf("time of copying B is %f [ms]\n",time2);
float time3 =((end3 - start3)*1.0e-6f); 
printf("time of calculation is %f [ms]\n",time3);
float time4 =((end4 - start4)*1.0e-6f); 
printf("time of copying C is %f [ms]\n",time4);
printf("time of overall execution is %f [ms]\n",time1+time2+time3+time4);
    return 0;
}

