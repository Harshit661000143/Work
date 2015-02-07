#include <CL/cl.h>
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

typedef float real_dt;

#if 1
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

#endif





int main(int argc,char **argv)
{
 int n,i,bsize,m,j;
// printf("enter size of array");
//scanf("%d",&n);

n=atoi(argv[1]);
bsize=atoi(argv[2]);
//printf("\nn=%d\n",n);
m=n;
 real_dt *A =(real_dt*)calloc(n*n,sizeof(real_dt));
 real_dt *B=(real_dt *)calloc(n*n,sizeof(real_dt));
 real_dt *C =(real_dt*)calloc(n*n,sizeof(real_dt));


//Initialize A and B

for(i=0;i<n*n;i++)
{
A[i]=1;
B[i]=1;

}  

#if 1
cl_ulong start=0;
cl_ulong end=0; 
cl_event event;

cl_event kernel_event;

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
#endif
//Reading program from file
FILE *fp;
    char *source_str;
    size_t source_size;
    const char *source;	
    fp = fopen("mat_kernel.c", "r");
    if (!fp) {
        printf("Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(50000);
    source_size = fread( source_str, 1, 5000, fp);
    fclose( fp );
source=source_str;
//printf("\nRead check:\n%s",source_str);


#if 1
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
cl_kernel kernel = clCreateKernel( program, "matmul", &err );
if(err!=CL_SUCCESS)
{
printf("\nError in kernel creation");
dump_error(&err);
}
// 5. Create a data buffer.
cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,n*n * sizeof(real_dt), NULL, &err);
if(err!=CL_SUCCESS)
{
printf("\nError in setting array a_mem_obj");
dump_error(&err);
}
cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,n*n* sizeof(real_dt), NULL, &err);
if(err!=CL_SUCCESS)
{
printf("\nError in setting array b_mem_obj");
dump_error(&err);
}

cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,n*n*sizeof(real_dt), NULL, &err);
if(err!=CL_SUCCESS)
{
printf("\nError in setting array c_mem_obj");
dump_error(&err);
}

//copy from CPU to GPU
err=clEnqueueWriteBuffer(queue, a_mem_obj, CL_TRUE, 0,n *n* sizeof(real_dt), A, 0, NULL, &event);
if(err!=CL_SUCCESS)
{
printf("\nError in writing array a_mem_obj");
dump_error(&err);
}


err=clEnqueueWriteBuffer(queue, b_mem_obj, CL_TRUE, 0,n*n * sizeof(real_dt), B, 0, NULL, &event);
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

err=clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting third kernel arg");
dump_error(&err);
}


err=clSetKernelArg(kernel, 3, sizeof(int), &n);
if(err!=CL_SUCCESS)
{
printf("\nerror in setting fourth kernel arg");
dump_error(&err);
}


// 6. Launch the kernel. Let OpenCL pick the local work size.
size_t global_work_size[2];
size_t local_work_size[2];

if(n%bsize!=0)
{
global_work_size[0]=(int)(floor(n/bsize)+1)*bsize;
global_work_size[1]=(int)(floor(n/bsize)+1)*bsize;
}
else
{
global_work_size[0]=(int)(floor(n/bsize))*bsize;
global_work_size[1]=(int)(floor(n/bsize))*bsize;
}
local_work_size[0]=bsize;
local_work_size[1]=bsize;

err=clEnqueueNDRangeKernel( queue,kernel,2,NULL,global_work_size,local_work_size, 0, NULL, &kernel_event);
if(err!=CL_SUCCESS)
{printf("\nerror in launching first kernel");
dump_error(&err);
}
err=clWaitForEvents(1,&kernel_event);
if(err!=CL_SUCCESS)
{printf("\nerror in measuring time for first kernel");
dump_error(&err);
}

err=clGetEventProfilingInfo(kernel_event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
if(err!=CL_SUCCESS)
{
printf("\nError in getting kernel event profiling info");
dump_error(&err);
}


err=clGetEventProfilingInfo(kernel_event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL); 
if(err!=CL_SUCCESS)
{
printf("\nError in get kernel event profiling info");
dump_error(&err);
}


float time=(end-start)*1.0e-06f;
printf("\n%d\t%f",n,time);


// 7. GPU to CPU copy
clEnqueueReadBuffer(queue, c_mem_obj, CL_TRUE, 0, n*n*sizeof(int), C, 0, NULL, NULL);


clFinish( queue );
#ifdef PRINT 
 printf("A=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
for(j=0;j<m;j++)
{
printf("%f\t",A[i*m+j]);
}
}

printf("\nB=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
for(j=0;j<m;j++)
{
printf("%f\t",B[i*m+j]);
}
}
printf("\nC=\t");  
  for(i = 0; i < m; i++)
{
printf("\n");
for(j=0;j<m;j++)
{
printf("%f\t",C[i*m+j]);
}
}
#endif
#endif
//for(i=0; i < thrds; i++)
//printf("%d: %d\n", i, B[i]);
//float star=start;
//float en=end;
//printf("time of start is %f and time of end is %f\n",star,en);
//float time =((end - start)*1.0e-6f); 
//printf("time of execution is %f [ms]\n",time);

return 0;
}

