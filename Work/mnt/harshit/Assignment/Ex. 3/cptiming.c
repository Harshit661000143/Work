#include <CL/cl.h>
#include <stdio.h>
#include<stdlib.h>
// kernel
const char *source ="__kernel void array( __global int *A )";

main()
{
 int n,i;
 printf("enter size of array");
scanf("%d",&n);
 int *A = (int*)malloc(sizeof(int)*n);
  int *B = (int*)malloc(sizeof(int)*n);

for(i=0;i<n;i++)
A[i]=i;	

cl_ulong start=0;
cl_ulong end=0; 
cl_event event;

// 1. Get a platform

cl_platform_id platform;
clGetPlatformIDs( 1, &platform, NULL);

// 2. Find a gpu device.
cl_device_id device;
clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU,1,&device,NULL);

// 3. Create a context and command queue on that device.
cl_context context = clCreateContext( NULL,1,&device,NULL, NULL, NULL);
cl_command_queue queue = clCreateCommandQueue( context,device,CL_QUEUE_PROFILING_ENABLE, NULL );

// 4. Perform runtime source compilation, and obtain kernel entry point.
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, NULL );
clBuildProgram( program, 1, &device, NULL, NULL, NULL );
cl_kernel kernel = clCreateKernel( program, "array", NULL );
// 5. Create a data buffer.
cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,n * sizeof(int), NULL, NULL);

//copy from CPU to GPU
clEnqueueWriteBuffer(queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, &event);
clWaitForEvents(1, &event);
// for measuring time
clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL); 

clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
// 6. Launch the kernel. Let OpenCL pick the local work size.
size_t global_work_size = n;
clEnqueueNDRangeKernel( queue,kernel,1,NULL,&global_work_size,NULL, 0, NULL, NULL);

// 7. GPU to CPU copy
clEnqueueReadBuffer(queue, a_mem_obj, CL_TRUE, 0, n * sizeof(int), B, 0, NULL, NULL);
clFinish( queue );




for(i=0; i < n; i++)
printf("%d: %d\n", i, B[i]);
float star=start;
float en=end;
printf("time of start is %f and time of end is %f\n",star,en);
float time =((end - start)*1.0e-6f); 
printf("time of execution is %f [ms]\n",time);
}

