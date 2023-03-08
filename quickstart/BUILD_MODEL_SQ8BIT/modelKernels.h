#ifndef __MODELKERNEL_H__
#define __MODELKERNEL_H__

#include "AutoTilerLibTypes.h"
#include "nntool_extra_kernels.h"
#include "CNN_BasicKernels_SQ8.h"
#include "model.h"
#define _model_L1_Memory_SIZE 48776
#define _model_L2_Memory_SIZE 0
extern char *model_L1_Memory; /* Size given for generation: 48804 bytes, used: 48776 bytes */
extern char *model_L2_Memory; /* Size used for generation: 0 bytes */
extern void S1_Op_input_1_formatter(
		unsigned char * __restrict__ In,
		signed char * __restrict__ Out);
extern void S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos);
extern void S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos);
extern void S4_Linear_2x29x39x64(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos);
extern void S5_SoftMax(
		signed char * __restrict__ In,
		short int * __restrict__ Out,
		signed char * __restrict__ Infos);
extern int modelCNN_Construct();
extern int modelCNN_Destruct();
extern int modelCNN(
		unsigned char * __restrict__ Input_1,
		signed short * __restrict__ Output_1);
extern unsigned int AT_GraphPerf[5];
extern char * AT_GraphNodeNames[5];
extern unsigned int AT_GraphOperInfosNames[5];
#endif
