#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<math.h>
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

else if(err[0]==CL_INVALID_KERNEL)
{
printf("\nError in kernel launch");
}

}



int main(int argc,char **argv) {
    // Create the two input vectors
    int n,j,i;
float alpha;
   
n=atoi(argv[1]);
alpha=atoi(argv[2]);
cl_ulong start1,start2,start3,end1,end2,end3;
cl_event event1,event2,event3;
  float *A = (float*)malloc(sizeof(float)*n);
    float *B = (float*)malloc(sizeof(float)*n);



    
    for(i = 0; i < n; i++) 
{
        A[i] = 1.0;
        B[i] = 1.0;
    }

 // Load the kernel source code into the array source_str
  const char *source ="__kernel void saxpy(int n,__global float *A, __global float *B,float alpha) {__local float alphan[1];alphan[0]=alpha;int tx=get_global_id(0);if(tx<n){A[tx]=A[tx]+(alphan[0]* B[tx]);}}";

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
if(ret!=CL_SUCCESS)
{
printf("platform id error");
}
dump_error(&ret);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
dump_error(&ret);
if(ret!=CL_SUCCESS)
{
printf("device id error");
}
    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("context error");}
    // Create a command queue
   cl_command_queue command_queue = clCreateCommandQueue( context,device_id,CL_QUEUE_PROFILING_ENABLE, &ret );
if(ret!=CL_SUCCESS)
{
printf("queue error");}
    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,n * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("b mem error");}

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(float), A, 0, NULL, &event1);
ret=clWaitForEvents(1, &event1);

dump_error(&ret);
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start1, NULL);
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end1, NULL);

if(ret!=CL_SUCCESS)
{
printf("a write buffer error");}
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(float), B, 0, NULL, &event2);
dump_error(&ret);
ret=clWaitForEvents(1, &event2);

if(ret!=CL_SUCCESS)
{
printf("b write buffer error");}
clGetEventProfilingInfo(event2, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start2, NULL);
clGetEventProfilingInfo(event2, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end2, NULL);

    // Create a program from the kernel source
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL,&ret  );
if(ret!=CL_SUCCESS)
{
printf("create pgm error");}
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
dump_error(&ret);
if(ret!=CL_SUCCESS)
{
printf("build pgm error");}

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "saxpy", &ret);
if(ret!=CL_SUCCESS)
{
printf("create kernel error");}
    // Set the arguments of the kernel
ret = clSetKernelArg(kernel, 0, sizeof(int),&n );

    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&a_mem_obj);
dump_error(&ret);
if(ret!=CL_SUCCESS)
{
printf("arg 0 ");}
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&b_mem_obj);
dump_error(&ret);
if(ret!=CL_SUCCESS)
{
printf("arg1 ");}
    ret = clSetKernelArg(kernel, 3, sizeof(float),&alpha );
dump_error(&ret);
    if(ret!=CL_SUCCESS)
{
printf("arg2");}

size_t globalWorkSize;
size_t localWorkSize;
if(n%16==0){   
 globalWorkSize = n;
 localWorkSize=16 ;
}
else{
globalWorkSize=(int)((floor(n/16)+1)*16);
localWorkSize=16;}	 
   
 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&globalWorkSize,&localWorkSize, 0, NULL,&event3);
dump_error(&ret);
if(ret!=CL_SUCCESS)
{
printf("ND RANGE ERROR");}
ret=clWaitForEvents(1, &event3);
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start3, NULL);
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end3, NULL);


clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n*sizeof(float), A, 0, NULL, NULL);
clFinish(command_queue);
#if 0  
 printf("A=\t");  
  for(i = 0; i < n; i++)
{
printf("%f\t",A[i]);
}

printf("\nB=\t");  
  for(i = 0; i <n ; i++)
{
printf("%f\t",B[i]);
}


float time3 =((end3 - start3)*1.0e-6f);
printf("time of calculation is %f [ms]\n\n",time3);
#endif
return 0;
}


