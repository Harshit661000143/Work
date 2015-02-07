#include <CL/cl.h>
#include <stdio.h>
#include<stdlib.h>

// kernel
const char *source ="__kernel void array( __global long *dst ){dst[get_global_id(0)] = get_global_id(0);}";

main()
{
 int n;
 printf("enter size of array");
scanf("%d",&n);	
float *buff= (float*)malloc(sizeof(float)*n);
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
cl_mem buffer = clCreateBuffer( context,CL_MEM_WRITE_ONLY,n * sizeof(cl_long),NULL, NULL );
// 6. Launch the kernel. Let OpenCL pick the local work size.
size_t global_work_size = n;
clSetKernelArg(kernel, 0, sizeof(buffer), (void*) &buffer);
clEnqueueNDRangeKernel( queue,kernel,1,NULL,&global_work_size,NULL, 0, NULL,&event);
// for measuring time 
clWaitForEvents(1, &event);
clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL); 

clFinish( queue );
// 7. Look at the results via synchronous buffer map.

cl_long *ptr;
ptr = (cl_long *) clEnqueueMapBuffer( queue,buffer,CL_TRUE,CL_MAP_READ,0,n * sizeof(cl_long),0, NULL, NULL, NULL );
int i;

for(i=0; i < n; i++){
buff[i]=ptr[i];
printf("%d: %f\n", i, buff[i]);}
float time =((end - start)*1.0e-6f); 
printf("time of execution is %f [ms]\n",time);
}

