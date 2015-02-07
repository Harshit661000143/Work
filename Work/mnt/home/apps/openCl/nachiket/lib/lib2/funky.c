#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<math.h>
float *saxpy(int n, float alpha, float *A, int incx, float *B, int incy,cl_device_id device_id, cl_context context,cl_command_queue command_queue,cl_mem a_mem_obj,cl_mem b_mem_obj)
{
//  const char *source ="__kernel void saxpy(int n,float alpha,__global float *A,int incx, __global float *B,int incy) {int tx=get_global_id(0);if((tx*incx<n)&&(tx*incy<n)){A[tx*incy]=A[tx*incy]+(alpha* B[tx*incx]);}}";
cl_int ret;
      cl_ulong start3,start4,end3,end4;
cl_event event3,event4;
FILE *fp;
    char *source_str;
    size_t source_size;
    const unsigned char *source;
    fp = fopen("binsax.txt", "r");
    if (!fp) {
        printf("Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(5000);
    source_size = fread( source_str, 1,5000, fp);
    fclose( fp );
source=source_str;
//cl_program program = clCreateProgramWithSource( context,1,&source,NULL,&ret  );
cl_program program=clCreateProgramWithBinary (context,1,&device_id,&source_size,&source,NULL,&ret);


//cl_program program = clCreateProgramWithSource( context,1,&source,NULL,&ret);  
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret = clBuildProgram(program,1,&device_id, NULL, NULL,NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

cl_kernel kernel = clCreateKernel(program, "saxpy",&ret); 
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret=clSetKernelArg(kernel, 0, sizeof(int),&n );
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret= clSetKernelArg(kernel, 1, sizeof(float),&alpha );
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&a_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret= clSetKernelArg(kernel, 3, sizeof(int),&incx );
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret= clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&b_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

 clSetKernelArg(kernel, 5, sizeof(int),&incy );

size_t globalWorkSize;
size_t localWorkSize;
if(n%16==0){   
 globalWorkSize = n;
 localWorkSize=16 ;
}
else{
globalWorkSize=(int)((floor(n/16)+1)*16);
localWorkSize=16;}	 
ret= clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&globalWorkSize,&localWorkSize, 0, NULL,&event3);
clWaitForEvents(1, &event3);

if(ret!=CL_SUCCESS)
{
printf("wrong");}
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start3, NULL);
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end3, NULL);

if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n*sizeof(float), A, 0, NULL,&event4);

ret=clWaitForEvents(1, &event4);



if(ret!=CL_SUCCESS)
{
printf("wrong");}


clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start4, NULL);
clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end4, NULL);

if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

float time3 =((end3 - start3)*1.0e-6f);
float time4 =((end4 - start4)*1.0e-6f);
printf("time3 time4%f\t%f\n",time3,time4);

clFinish(command_queue);
return A;
}
float *xscal(int n, float alpha, float *A, int incx,cl_device_id device_id, cl_context context,cl_command_queue command_queue,cl_mem a_mem_obj,cl_int ret)
{
 //const char *source ="__kernel void xscal(int n,float alpha,__global float *A,int incx){int k=get_global_id(0);if(k*incx<n){A[k*incx]=alpha*A[k*incx];}}";
// Create a program from the kernel source
FILE *fp;
    char *source_str;
    size_t source_size;
    const unsigned char *source;
    fp = fopen("biscal.txt", "r");
    if (!fp) {
        printf("Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(5000);
    source_size = fread( source_str, 1, 5000, fp);
    fclose( fp );
source=source_str;


// cl_program program = clCreateProgramWithSource( context,1,&source,NULL,NULL);
cl_program program=clCreateProgramWithBinary (context,1,&device_id,&source_size,&source,NULL,&ret);

 

if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

 clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

 cl_kernel kernel = clCreateKernel(program, "xscal",&ret);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

 clSetKernelArg(kernel, 0, sizeof(int),&n);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

 clSetKernelArg(kernel, 1, sizeof(float),&alpha);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

 clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&a_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}
 clSetKernelArg(kernel, 3, sizeof(int),&incx );
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}


 size_t globalWorkSize;
 size_t localWorkSize;

if(n%16==0)
{
 globalWorkSize = n;
 localWorkSize=16 ;
}
else
{
 globalWorkSize=(int)((floor(n/16)+1)*16);
localWorkSize=16;}

 ret=clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&globalWorkSize,&localWorkSize, 0, NULL,NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret= clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n*sizeof(float), A, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

 clFinish(command_queue);
 return A;
}


#if 1
float dot(int n,float *A,int incx, float *B, int incy,cl_device_id device_id, cl_context context,cl_command_queue command_queue,cl_mem a_mem_obj,cl_mem b_mem_obj) {
    // Create the two input vectors
    int i;
float j;
cl_int ret;   
cl_ulong start3,end3,start4,end4; 

cl_event event3,event4; 
    float *D = (float*)calloc(n,sizeof(float));


 // Load the kernel source code into the array source_stringh  
//const char *source ="__kernel void dot_pro(__global float* A, __global float* B,__global float* D, const int m, int incx, int incy){float lsum=0;__local float sum[16];sum[get_local_id(0)]=0;int i;int x=get_global_id(0);D[x]=0;if(x*incx<m&&x*incy<m){sum[get_local_id(0)]=A[x*incx]*B[x*incy];} barrier(CLK_LOCAL_MEM_FENCE);if(get_local_id(0)==0){for(i=0;i<16;i++){lsum+=sum[i]; }D[x]=lsum; }}";

  

    cl_mem d_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, n * sizeof(float), NULL, &ret);
// Create a program from the kernel source
   
//cl_program program = clCreateProgramWithSource( context,1,&source,NULL, &ret );

  if(ret!=CL_SUCCESS)
{
printf("\nError in creating program");

}
  // Build the program
//    ret = clBuildProgram(program, 1, &device_id,NULL, NULL, NULL);
FILE *fp;
    char *source_str;
    size_t source_size;
    const unsigned char *source;
    fp = fopen("bindot.txt", "r");
    if (!fp) {
        printf("Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(5000);
    source_size = fread( source_str, 1,5000, fp);
    fclose( fp );
source=source_str;
//cl_program program = clCreateProgramWithSource( context,1,&source,NULL,&ret  );
cl_program program=clCreateProgramWithBinary (context,1,&device_id,&source_size,&source,NULL,&ret);

ret = clBuildProgram(program,1,&device_id, NULL, NULL,NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}


if(ret!=CL_SUCCESS)
{
printf("\nError in building program");

}
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
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&d_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument3");

}
    ret = clSetKernelArg(kernel, 3, sizeof(int), &n);
    if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument4");

}

    ret = clSetKernelArg(kernel, 4, sizeof(int), &incx);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting fifth kernel arg");
        
   }

    ret = clSetKernelArg(kernel, 5, sizeof(int), &incy);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting sixth kernel arg");
        
   }


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

 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size,&local_item_size, 0, NULL, &event3);
if(ret!=CL_SUCCESS)
{
printf("\nNDRange kernel error");

}
ret=clWaitForEvents(1, &event3);
if(ret!=CL_SUCCESS)
{
printf("wrong3");}
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start3, NULL);
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end3, NULL); 
    // Read the memory buffer C on the device to the local variable C
    
    ret = clEnqueueReadBuffer(command_queue, d_mem_obj, CL_TRUE, 0, n* sizeof(float), D, 0, NULL, &event4);

if(ret!=CL_SUCCESS)
{
printf("\nError in getting back D");
}
ret=clWaitForEvents(1, &event4);
if(ret!=CL_SUCCESS)
{
printf("wrong4");}
clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start4, NULL);
clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end4, NULL); 
  j=0;
  for(i = 0; i < n; i++)
{
j=j+D[i];
}
printf("\n");

float time3 =((end3 - start3)*1.0e-6f);
float time4 =((end4 - start4)*1.0e-6f);
printf("%d %f\n",n,time3+time4);
//clean up
    ret = clFlush(command_queue);
ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    return j;
}
#endif
