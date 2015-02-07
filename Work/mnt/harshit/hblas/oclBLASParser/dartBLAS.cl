/* 
* sAXPY OpenCL Kernel Function for Level 1 BLAS xAXPY y<-ax+y
* Copyright (C) 2009 Wendell Rodrigues <wendell.rodrigues@inria.fr>
* Author(s): Wendell Rodrigues
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without event the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Sofware
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

__kernel void sAXPY(
  __global const unsigned int    N,  
  __global const 	  float  ALPHA,  
  __global const          float* X,
  __global const unsigned int INCX,
  __global                float* Y,
  __global const unsigned int INCY
)
{
    // get index into global data array
    unsigned int tid = get_global_id(0);

    if (tid < N)
      Y[tid*INCY] = ALPHA*X[tid*INCX] + Y[tid*INCY];
}

/* 
* sDOT OpenCL Kernel Function for Level 1 BLAS Dot Product dot<-xy
* Copyright (C) 2009 Wendell Rodrigues <wendell.rodrigues@inria.fr>
* Author(s): Wendell Rodrigues
*/

__kernel void sDOT(
  __global const unsigned int  N,  
  __global const        float* X, 
  __global const unsigned int INCX,
  __global const        float* Y,
  __global const unsigned int INCY,
  __global 	        float* DOT,
  __local		float* sdata
)
{
    // get index into global data array
    unsigned int tid = get_local_id(0);
    unsigned int blockSize = get_local_size(0);
    unsigned int i = get_group_id(0)*(get_local_size(0)*2) + get_local_id(0);

    sdata[tid] = (i<N) ? X[i*INCX]*Y[i*INCY] : 0;

    if ((i + blockSize) < N)
      sdata[tid] += X[i*INCX + blockSize]*Y[i*INCY + blockSize];

    barrier(CLK_LOCAL_MEM_FENCE);

    if (blockSize >= 512) {if (tid < 256) { sdata[tid] += sdata[tid + 256];} barrier(CLK_LOCAL_MEM_FENCE); }
    if (blockSize >= 256) {if (tid < 128) { sdata[tid] += sdata[tid + 128];} barrier(CLK_LOCAL_MEM_FENCE); }
    if (blockSize >= 128) {if (tid <  64) { sdata[tid] += sdata[tid +  64];} barrier(CLK_LOCAL_MEM_FENCE); }

    if (tid < 32) {
     if (blockSize >= 64) { sdata[tid] += sdata[tid +  32]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >= 32) { sdata[tid] += sdata[tid +  16]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >= 16) { sdata[tid] += sdata[tid +   8]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >=  8) { sdata[tid] += sdata[tid +   4]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >=  4) { sdata[tid] += sdata[tid +   2]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >=  2) { sdata[tid] += sdata[tid +   1]; barrier(CLK_LOCAL_MEM_FENCE); }
    }

    if ( tid==0 ) DOT[0] = sdata[0];

}
/* 
* sNRM2 OpenCL Kernel Function for Level 1 BLAS Dot Product nrm2<-||x||^2
* Copyright (C) 2009 Wendell Rodrigues <wendell.rodrigues@inria.fr>
* Author(s): Wendell Rodrigues
*/

__kernel void sNRM2(
  __global const unsigned int  N,  
  __global const        float* X,
  __global const unsigned int INCX,
  __global 	        float* NRM2,
  __local		float* sdata
)
{
    // get index into global data array
    unsigned int tid = get_local_id(0);
    unsigned int blockSize = get_local_size(0);
    unsigned int i = get_group_id(0)*(get_local_size(0)*2) + get_local_id(0);

    sdata[tid] = (i<N) ? X[i*INCX]*X[i*INCX] : 0;

    if ((i + blockSize) < N)
      sdata[tid] += X[i*INCX + blockSize]*X[i*INCX + blockSize];

    barrier(CLK_LOCAL_MEM_FENCE);

    if (blockSize >= 512) {if (tid < 256) { sdata[tid] += sdata[tid + 256];} barrier(CLK_LOCAL_MEM_FENCE); }
    if (blockSize >= 256) {if (tid < 128) { sdata[tid] += sdata[tid + 128];} barrier(CLK_LOCAL_MEM_FENCE); }
    if (blockSize >= 128) {if (tid <  64) { sdata[tid] += sdata[tid +  64];} barrier(CLK_LOCAL_MEM_FENCE); }

    if (tid < 32) {
     if (blockSize >= 64) { sdata[tid] += sdata[tid +  32]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >= 32) { sdata[tid] += sdata[tid +  16]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >= 16) { sdata[tid] += sdata[tid +   8]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >=  8) { sdata[tid] += sdata[tid +   4]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >=  4) { sdata[tid] += sdata[tid +   2]; barrier(CLK_LOCAL_MEM_FENCE); }
     if (blockSize >=  2) { sdata[tid] += sdata[tid +   1]; barrier(CLK_LOCAL_MEM_FENCE); }
    }

    if ( tid==0 ) NRM2[0] = sqrt(sdata[0]);

}
/* 
* sSCAL OpenCL Kernel Function for Level 1 BLAS SCALAR product x<-a*x
* Copyright (C) 2009 Wendell Rodrigues <wendell.rodrigues@inria.fr>
* Author(s): Wendell Rodrigues
*/

__kernel void sSCAL(
  __global const unsigned int    N,  
  __global const 	  float  ALPHA,  
  __global                float* X,
  __global const unsigned int INCX
)
{
    // get index into global data array
    unsigned int tid = get_global_id(0);

    if (tid < N)
      X[tid*INCX] = ALPHA*X[tid*INCX];
}
