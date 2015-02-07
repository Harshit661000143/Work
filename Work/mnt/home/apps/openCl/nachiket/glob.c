#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <math.h>

void dump_error(cl_int *err)
{

if(err[0]==CL_INVALID_PLATFORM)
{

printf("\nInvalid platform");
}

else if (err[0]==CL_INVALID_DEVICE)
{
printf("\nInvalid Device");
}

else if(err[0]==CL_INVALID_CONTEXT)
{
printf("\nInvalid Context");
}


else if(err[0]==CL_INVALID_KERNEL)
{
printf("\nInvalid kernel");
}

else if(err[0]==CL_INVALID_VALUE)
{
printf("\nInvalid value");
}

else if(err[0]==CL_INVALID_QUEUE_PROPERTIES)
{
printf("\nInvalid properties");
}

else if(err[0]==CL_OUT_OF_HOST_MEMORY)
{
printf("\nOut of host memory");
}

else if(err[0]==CL_INVALID_ARG_INDEX)
{
printf("\ninvalid arg index");
}
else if(err[0]==CL_INVALID_ARG_SIZE)
{
printf("\ninvalid arg size");
}
else if(err[0]==CL_INVALID_ARG_VALUE)
{
printf("\ninvalid arg value");
}
else if(err[0]==CL_INVALID_MEM_OBJECT)
{
printf("\ninvalid mem object");
}
else if(err[0]==CL_INVALID_KERNEL)
{
printf("\nError in kernel launch");
}
else if(err[0]==CL_BUILD_PROGRAM_FAILURE)
{
printf("\nBuild program failure");
}
else if(err[0]==CL_INVALID_PROGRAM)
{printf("invalid program");}
}


int main(int argc,char *argv[]) {
    // Create the two input vectors
    int i,n,m,j,s,temp;
   
cl_ulong start1,start2,start3,end1,end2,end3,start4,end4; 

cl_event event1,event2,event3,event4; 

m = atoi(argv[1]); 
s= atoi(argv[2]); 




 
n=m*m;
    int *A = (int*)malloc(sizeof(int)*n);
    int *B = (int*)malloc(sizeof(int)*n);
    int *C = (int*)malloc(sizeof(int)*n);
srand(m);
    for(i = 0; i < n; i++) 
{
        A[i] =rand()%10;
        B[i] = rand()%10;
}

 for ( i = 0; i < m; i++){
        for ( j = i + 1; j < m; j++){
             temp= A[m*i+j];
             A[m*i+j]=A[m*j+i];
             A[m*j+i]=temp;
}}        




 // Load the kernel source code into the array source_str
  const char *source ="__kernel void matrix_add(__global int* A, __global int* B, __global int* C,int m){int x = get_global_id(0);int y = get_global_id(1);if((x<m)&&(y<m)){int value = 0;for(int k = 0; k < m; ++k){int tA = A[k * m + y];int tB = B[k * m+ x];value += tA * tB;}C[y * m + x ] = value;}}";

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_ALL, 1, &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
   cl_command_queue command_queue = clCreateCommandQueue( context,device_id,CL_QUEUE_PROFILING_ENABLE, NULL );

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,n * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &ret);
   
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
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, &ret );

  if(ret!=CL_SUCCESS)
{
printf("\nError in creating program");
dump_error(&ret);
}
  // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in building program");
dump_error(&ret);
}
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "matrix_add", &ret);
if(ret!=CL_SUCCESS)
{
printf("\nError in creating kernel");
dump_error(&ret);
}
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument1");
dump_error(&ret);
}
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument2");
dump_error(&ret);
}
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
    if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument3");
dump_error(&ret);
}

    ret = clSetKernelArg(kernel, 3, sizeof(int), &m);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting fourth kernel arg");
        dump_error(&ret);
   }


size_t global_item_size[2],local_item_size[2];   
if(m%s!=0)
{
global_item_size[0]=(int)(floor(m/s)+1)*s;
global_item_size[1]=(int)(floor(m/s)+1)*s;
}
else
{
global_item_size[0]=(int)(floor(m/s))*s;
global_item_size[1]=(int)(floor(m/s))*s;
}


local_item_size[0]=s;
local_item_size[1]=s;

//  global_item_size[0] = m;
//  local_item_size[0] = s;
//  global_item_size[1] = m;
//local_item_size[1] = s;
 ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL,global_item_size,local_item_size, 0, NULL, &event3);
if(ret!=CL_SUCCESS)
{
printf("\nNDRange kernel error");
dump_error(&ret);
}
ret=clWaitForEvents(1, &event3);

if(ret!=CL_SUCCESS)
{
printf("wrong");}
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start3, NULL);
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end3, NULL); 
    // Read the memory buffer C on the device to the local variable C
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, n * sizeof(int), C, 0, NULL, &event4);

if(ret!=CL_SUCCESS)
{
printf("\nError in getting back c");
}


ret=clWaitForEvents(1, &event4);



if(ret!=CL_SUCCESS)
{
printf("wrong");}


clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start4, NULL);
clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end4, NULL); 
   
 // Display the result to the screen
#if 0
 printf("A=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
//for(j=0;j<m;j++)
{
//printf("%d\t",A[i*m+j]);
}
printf("%d" ,A[i]);
}

printf("\nB=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
//for(j=0;j<m;j++)
//{
//printf("%d\t",B[i*m+j]);
//}
printf("%d", B[i]);
}
#endif

printf("\n");
float time1 =((end1 - start1)*1.0e-6f);
 float time2 =((end2 - start2)*1.0e-6f);
float time3 =((end3 - start3)*1.0e-6f);
float time4 =((end4 - start4)*1.0e-6f);
printf("%d %f\n",m,time1+time2+time3+time4);


    

#if 0
printf("\nC=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
//for(j=0;j<m;j++)
//{
printf("%d\t",C[i]);

}


#endif

 // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(A);
    free(B);
    free(C);
    return 0;
}

