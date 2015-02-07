#ifndef NSAMPLE_H
#define NSAMPLE_H
#include <CL/cl.h>
float *saxpy(int , float , float* , int , float* , int ,cl_device_id , cl_context ,cl_command_queue ,cl_mem ,cl_mem ,cl_int  );
//float *scalar(int, float, float*,int );
float *xscal(int, float, float*,int,cl_device_id , cl_context ,cl_command_queue ,cl_mem,cl_int);
//float dot(int, float*,int,float*,int);

float dot(int , float* , int , float* , int ,cl_device_id , cl_context ,cl_command_queue ,cl_mem ,cl_mem  );

#endif


