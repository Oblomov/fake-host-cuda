/* This header file can be used to allow pseudo-compilation of CUDA source files
 * with a host compiler, with the aim to allow the use of clang syntax checking
 * et similia when working on CUDA source files (think YouCompleteMe).
 *
 * To use it, pre-include this header at compiler invokation time. e.g.:
 * 
 * 	clang++ -x c++ -include fake_host_cuda.h source.cu
 */

/* The attributes used by nvcc are not interesting for clang, so, for a cleaner
 * compilation, we also disable the ignored-attributes warning */
#if defined(__CLANG__)
#pragma GCC diagnostic ignored "-Wignored-attributes"
#else
#pragma GCC diagnostic ignored "-Wattributes"
#endif

/* The key point is including 'cuda_runtime.h', which is done automatically
 * by nvcc. We need to pretend we are nvcc though, so also define __CUDACC__
 */

#define __CUDACC__

/* OTOH the asm syntax used by nvcc for the intrinsics isn't supported by clang,
 * so we need to avoid inclusion of files that use it, which we do by
 * pre-defining their inclusion fences.
 * TODO we should declare those intrinsics here.
 */
#define __SM_30_INTRINSICS_H__
#define __SM_32_INTRINSICS_H__
#define __TEXTURE_INDIRECT_FUNCTIONS_H__
#define __SURFACE_INDIRECT_FUNCTIONS_H__

#include "cuda_runtime.h"

/* TODO FIXME Now the only obstacle is the launch grid syntax:
 *
 * 	kernelname<<<blocks, threads[, optional shmem [,optional stream]>>>(....);
 *
 */

