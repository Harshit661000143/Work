/* execute the program by using these two commands:

gcc -c -I <path where toolkit is installed> buff.c -o buff
gcc -L <path where toolkit is installed> -l OpenCL buff -o host

Example:
gcc -c -I /home/ajay/Downloads/AMD-APP-SDK-v2.4-lnx32/include/ buff.c -o buff
gcc -L /home/ajay/Downloads/AMD-APP-SDK-v2.4-lnx32/lib/x86/ -l OpenCL buff -o host
*/
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
 


// 1. Get a platform

cl_platform_id platform;
clGetPlatformIDs( 1, &platform, NULL);

// 2. Find a gpu device.
cl_device_id device;
clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU,1,&device,NULL);

// 3. Create a context and command queue on that device.
cl_context context = clCreateContext( NULL,1,&device,NULL, NULL, NULL);
cl_command_queue queue = clCreateCommandQueue( context,device,0, NULL );

// 4. Perform runtime source compilation
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, NULL );
clBuildProgram( program, 1, &device, NULL, NULL, NULL );
cl_kernel kernel = clCreateKernel( program, "array", NULL );
// 5. Create a data buffer.
cl_mem buffer = clCreateBuffer( context,CL_MEM_WRITE_ONLY,n * sizeof(cl_long),NULL, NULL );
// 6. Launch the kernel
size_t global_work_size = n;
clSetKernelArg(kernel, 0, sizeof(buffer), (void*) &buffer);
clEnqueueNDRangeKernel( queue,kernel,1,NULL,&global_work_size,NULL, 0, NULL, NULL);
clFinish( queue );
// 7. Look at the results by using buffer map.
cl_long *ptr;
ptr = (cl_long *) clEnqueueMapBuffer( queue,buffer,CL_TRUE,CL_MAP_READ,0,n * sizeof(cl_long),0, NULL, NULL, NULL );
int i;

for(i=0; i < n; i++){
buff[i]=ptr[i];
printf("%d: %f\n", i, buff[i]);
}
}

