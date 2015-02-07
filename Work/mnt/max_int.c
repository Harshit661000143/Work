#include <CL/cl.h>
#include <stdio.h>
#include<stdlib.h>

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


// kernel
//const char *source ="__kernel void array( __global int *A,__global int *B,int size,int p)\n{\nint i=get_global_id(0);\nint j=size/p;\nint my_beg=i*j;\nint k;\n max=A[my_beg];\nfor(k=0;k<j;k++)\n{ max=max:A[my_beg+k]?max>=A[my_beg+k];\n  }\nB[i]=max;}";


const char *source ="__kernel void array( __global int *A,__global int *B,int size,int p)\n{\nint i=get_global_id(0);\nint j=size/p;B[i]=j;\n int my_beg=i*size/p;B[i]=my_beg;\n int max=A[my_beg];\nint k;\nfor(k=0;k<j;k++)\n{ if(max<A[my_beg+k])\n{max=A[my_beg+k];\n} }\nB[i]=max;}";


int main(int argc,char **argv)
{
 int n,i,thrds;
// printf("enter size of array");
//scanf("%d",&n);

n=atoi(argv[1]);
thrds=atoi(argv[2]);
printf("\nn=%d\n",n);

if(n%thrds!=0)
{
printf("\nSize of an array should be divisible by number of threads\n");
exit (0);
}
 int *A = (int*)malloc(sizeof(int)*n);
 int *B, C[1];



for(i=0;i<n;i++)
{ 
A[i]=10*(n-i);	

}

cl_ulong start=0;
cl_ulong end=0; 
cl_event event;

cl_int err;
// 1. Get a platform
cl_platform_id platform;
err=clGetPlatformIDs( 1, &platform, NULL);
if(err!=CL_SUCCESS)
{
printf("\nError in get platform");
dump_error(&err);
}
// 2. Find a gpu device.
cl_device_id device;
err=clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU,1,&device,NULL);
if(err!=CL_SUCCESS)
{
printf("\nError in get device");
dump_error(&err);
}
// 3. Create a context and command queue on that device.
cl_context context = clCreateContext( NULL,1,&device,NULL, NULL, &err);
if(err!=CL_SUCCESS)
{
printf("\nError in create context");
dump_error(&err);
}

cl_command_queue queue = clCreateCommandQueue( context,device,CL_QUEUE_PROFILING_ENABLE, &err );
if(err!=CL_SUCCESS)
{
printf("\nError in create queue");
dump_error(&err);
}
// 4. Perform runtime source compilation, and obtain kernel entry point.
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, &err );
if(err!=CL_SUCCESS)
{
printf("\nError in creation of programme");
dump_error(&err);
}
err=clBuildProgram( program, 1, &device, NULL, NULL, NULL );
if(err!=CL_SUCCESS)
{
printf("\nProblem in building programme");
dump_error(&err);
}
cl_kernel kernel = clCreateKernel( program, "array", &err );
if(err!=CL_SUCCESS)
{
printf("\nError in kernel creation");
dump_error(&err);
}
// 5. Create a data buffer.
cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,n * sizeof(int), NULL, &err);
if(err!=CL_SUCCESS)
{
printf("\nError in setting array a_mem_obj");
dump_error(&err);
}
cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,thrds* sizeof(int), NULL, &err);
if(err!=CL_SUCCESS)
{
printf("\nError in setting array b_mem_obj");
dump_error(&err);
}



cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,sizeof(int), NULL, &err);
if(err!=CL_SUCCESS)
{
printf("\nError in setting array c_mem_obj");
dump_error(&err);
}

//copy from CPU to GPU
err=clEnqueueWriteBuffer(queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, &event);
if(err!=CL_SUCCESS)
{
printf("\nError in writing array a_mem_obj");
dump_error(&err);
}


err=clEnqueueWriteBuffer(queue, b_mem_obj, CL_TRUE, 0,thrds * sizeof(int), B, 0, NULL, &event);
if(err!=CL_SUCCESS)
{
printf("\nError in writing array b_mem_obj");
dump_error(&err);
}



clWaitForEvents(1, &event);
// for measuring time
err=clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
if(err!=CL_SUCCESS)
{
printf("\nError in getting profiling info");
dump_error(&err);
}


err=clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL); 
if(err!=CL_SUCCESS)
{
printf("\nError in get event profiling info");
dump_error(&err);
}


err=clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting first kernel arg");
dump_error(&err);
}



err=clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting second kernel arg");
dump_error(&err);
}



err=clSetKernelArg(kernel, 2, sizeof(int),&n);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting third kernel arg");
dump_error(&err);
}



err=clSetKernelArg(kernel, 3, sizeof(int), &thrds);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting fourth kernel arg");
dump_error(&err);
}


// 6. Launch the kernel. Let OpenCL pick the local work size.
size_t global_work_size = thrds;
B=(int *)malloc(thrds*sizeof(int));

err=clEnqueueNDRangeKernel( queue,kernel,1,NULL,&global_work_size,&global_work_size, 0, NULL, NULL);
if(err!=CL_SUCCESS)
{printf("\nerror in launching first kernel");
dump_error(&err);
}

//second call
n=thrds;
thrds=1;
err=clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&b_mem_obj);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting first kernel arg");
dump_error(&err);
}

err=clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&c_mem_obj);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting second kernel arg");
dump_error(&err);
}


err=clSetKernelArg(kernel, 2, sizeof(int),&n);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting third kernel arg");
dump_error(&err);
}




err=clSetKernelArg(kernel, 3, sizeof(int), &thrds);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting fourth kernel arg");
dump_error(&err);
}

global_work_size=1;

err=clEnqueueNDRangeKernel( queue,kernel,1,NULL,&global_work_size,&global_work_size, 0, NULL, NULL);
if(err!=CL_SUCCESS)
{
printf("\nerror in launching the kernel");
dump_error(&err);
}

// 7. GPU to CPU copy
clEnqueueReadBuffer(queue, c_mem_obj, CL_TRUE, 0, sizeof(int), C, 0, NULL, NULL);


clFinish( queue );


printf("\nMax value=%d\n",C[0]);

//for(i=0; i < thrds; i++)
//printf("%d: %d\n", i, B[i]);
//float star=start;
//float en=end;
//printf("time of start is %f and time of end is %f\n",star,en);
//float time =((end - start)*1.0e-6f); 
//printf("time of execution is %f [ms]\n",time);

return 0;
}

