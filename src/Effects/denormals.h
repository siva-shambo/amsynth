// Macro for killing denormalled numbers
//
// Written by Jezar at Dreampoint, June 2000
// http://www.dreampoint.co.uk
// Based on IS_DENORMAL macro by Jon Watte
// This code is public domain

#ifndef _denormals_
#define _denormals_

#if __SSE2_MATH__

//
// The preferred way to prevent denormal processing and its associated performance penalty is to
// configure the compiler to generate SSE2 instructions for all floating point operations, and
// disable denormal processing by setting the 'Denormals Are Zero' and 'Flush to Zero' (DAZ and FZ)
// bits in the MXCSR. Note that the DAZ flag was assed in SSE2.
//
// -mfpmath=sse (This is the default choice for the x86-64 compiler)
//
// SSE is not available on all processors, though, so cannot be reiled upon.
//

#define undenormalise(x) (void)0

#else

// this macro is broken! http://music.columbia.edu/pipermail/linux-audio-user/2004-July/013489.html
// #define undenormalise(sample) if(((*(unsigned int*)(void *)&sample)&0x7f800000)==0) sample=0.0f
static inline float undenormalise(volatile float s) { s += 9.8607615E-32f; return s - 9.8607615E-32f; }

#define nuke_denormals(value) if(((*(unsigned int *)&(value))&0x7f800000)<0x08000000) value=0.0f

#endif

#endif//_denormals_

//ends
