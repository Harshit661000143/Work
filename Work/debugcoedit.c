#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<math.h>
#include<string.h>

    // Create the two input vectors

main(int argc,char** argv)
{
int i;
int n=atoi(argv[1]);
int incx=atoi(argv[2]);
int incy=atoi(argv[3]);
float *A = (float*)malloc(sizeof(float)*n*2);
float *B = (float*)malloc(sizeof(float)*n*2);
int mm=n;

size_t global_item_size,local_item_size;   
if(n%16!=0)
{
global_item_size=(int)(floor(n/16)+1)*16;
local_item_size=16;
}
else
{
global_item_size=n;
local_item_size=16;
}
int x=global_item_size/local_item_size;
cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
if(ret!=CL_SUCCESS)
{
printf("platform id error");
}
ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

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
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,n *2* sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, n *2* sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("b mem error");}
for(i=0;i<n;i++)
{
A[2*i+1]=1.0;
A[2*i]=1.0;
B[2*i]=1.0;
B[2*i+1]=1.0;
}
    // Copy the lists A and B to their respective memory buffers
ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n *2* sizeof(float), A, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n *2* sizeof(float), B, 0, NULL, NULL);


float j;
  


 // Load the kernel source code into the array source_stringh  
const char *source ="__kernel void dot_pro(__global float* A, __global float* B, const int m, int incx, int incy){int xodd=get_global_id(0)*2+1;int xeven=get_global_id(0)*2;int j;float rsum=0;float csum=0;__local float asum[16];__local float bsum[16];int y=get_local_id(0);asum[y]=0;bsum[y]=0;int i; if(get_num_groups(0)>m/16){if(xodd*incx<m*2&&xeven*incy<m*2&&xeven*incx<m*2&&xodd*incy<m*2){asum[y]=A[xeven*incx]*B[xeven*incy]-A[xodd*incx]*B[xodd*incy];bsum[y]=A[xeven*incx]*B[xodd*incy]+A[xodd*incx]*B[xeven*incy];}} else {asum[y]=A[xeven];bsum[y]=A[xodd];} A[xodd]=0;A[xeven]=0;if(y==0){for(i=0;i<16;i++){rsum+=asum[i];csum+=bsum[i];}A[get_group_id(0)*2]=rsum;A[get_group_id(0)*2+1]=csum;}}";

  

// Create a program from the kernel source
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, &ret );

  if(ret!=CL_SUCCESS)
{
printf("\nError in creating program");

}
  // Build the program
    ret = clBuildProgram(program, 1, &device_id,NULL, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in building program");

}
#if 0
char *bindot= (char*)malloc(sizeof(char)*5000);
ret= clGetProgramInfo(program,CL_PROGRAM_BINARIES,5000,&bindot,NULL);
if(ret!=CL_SUCCESS)
{
printf("\nError binary ");
}


 FILE *kk;
kk=fopen("bindot.txt","w");
fwrite(bindot,1,strlen(bindot), kk);
fclose(kk);

#endif

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "dot_pro", &ret);
if(ret!=CL_SUCCESS)
{
printf("\nError in creating kernel");

}
  // Set the arguments of the kernel
   ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument1");

}
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument2");

}
  
    ret = clSetKernelArg(kernel,2, sizeof(int), &n);
    if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument4");

}

    ret = clSetKernelArg(kernel, 3, sizeof(int), &incx);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting fifth kernel arg");
        
   }

    ret = clSetKernelArg(kernel, 4, sizeof(int), &incy);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting sixth kernel arg");
        
   }
i=0;
while(mm!=0)
{

 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size,&local_item_size, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("\nNDRange kernel error");
}
if(x%16!=0)
{
global_item_size=(int)(floor(x/16)+1)*16;
}
else
{
global_item_size=x;
}
x=global_item_size/16;
mm=mm/16;


i++;
}

    // Read the memory buffer C on the device to the local variable C
    
    ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, 2* sizeof(float), A, 0, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in getting back D");
}

 

printf("\n");

//float time3 =((end3 - start3)*1.0e-6f);
for(i=0;i<1;i++){
printf("%f(r)  %f(c)\n",A[2*i],A[2*i+1] );
}
//clean up
    ret = clFlush(command_queue);
ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    return 0;
}

