#include "modelKernels.h"
L1_CL_MEM AT_L1_POINTER model_L1_Memory;
L2_MEM AT_L2_POINTER model_L2_Memory;
AT_HYPERRAM_POINTER model_L3_Memory;
static AT_HYPERRAM_T HyperRam;
static AT_HYPERFLASH_FS_T HyperFlash;
void S1_Op_input_1_formatter(
		unsigned char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 47952 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerNormBW_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 7]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 79056 [Tile0, 7:[324x37, 5:324x37, 324x22], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[324x37, 5:324x37, 324x22], 1]
		Tile0: [0, 11988, 11988], Tile1: [11988, 11988, 11988], Tile2; [23976, 11988, 11988]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 79056 [Tile0, 7:[324x37, 5:324x37, 324x22], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[324x37, 5:324x37, 324x22], 1]
		Tile0: [0, 11988, 11988], Tile1: [11988, 11988, 11988], Tile2; [23976, 11988, 11988]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (324);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 11988, 0, &DmaR_Evt1);
	_N_In=0;
	_C_Out=0; _SC_Out=11988;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6);
		/*================================= Prepare Tiles ===================================*/
		_SN_In = 0;
		if (!(T0Ind_Last)) {
			_N_In = _N_In + (11988); _SN_In = ((T0Ind_NextLast)?7128:11988); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+11988*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (unsigned char *__restrict__) (model_L1_Memory+0+11988*((T0Ind_Total)%2));
		KerArg0->Out = (signed char *__restrict__) (model_L1_Memory+23976+11988*((T0Ind_Total)%2));
		KerArg0->H = (unsigned short int) (T0Ind_Last?22:37);
		AT_FORK(gap_ncore(), (void *) CNN_NormBW_offset_fps, (void *) KerArg0);
		__CALL(CNN_NormBW_offset_fps, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+19360+11988*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR1);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+19360+11988*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+23976+11988*((T0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SPP_Out = _SP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T0Ind_Last)) {
			_C_Out = _C_Out + (11988); _SC_Out = ((T0Ind_NextLast)?7128:11988); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+19360+11988*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 38436 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;
	KerPool_SQ8_T S_KerArg3, *KerArg3 = &S_KerArg3;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Total=0, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 2][Tile0 Dim: 60][D0 Dim: Init: 1, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 120 logical tiles, 120 physical tiles
			Total Size: 153600 [D1, [1 x 115200, 38400]][Tile0, 60:[80x1, 58:80x1, 80x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 115200, 38400]][Tile0, 60:[80x1, 58:80x1, 80x1], 1]
		Tile0: [0, 1920, 80], Tile1: [80, 1920, 80], Tile2; [160, 1920, 80]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [1 x 96, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 96, 32]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [1 x 24, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 24, 8]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [1 x 24, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 24, 8]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: D1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 120 logical tiles, 2 physical tiles
			Total Size: 288 [D1, [1 x 216, 72]][D0, [0 x 216, 216]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 216, 72]][D0, [0 x 216, 216]]
		Tile0: [0, 216, 9], Tile1: [216, 72, 9], Tile2; [0, 216, 9]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 60 logical tiles, 60 physical tiles
			Total Size: 79056 [D0, [0 x 79056, 79056]][Tile0, 60:[324x5, 58:324x5, 324x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 60:[324x5, 58:324x5, 324x5], 1][D0, [0 x 79056, 79056]]
		Tile0: [0, 1620, 1620], Tile1: [1296, 1620, 1620], Tile2; [2592, 1620, 1620]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 120 logical tiles, 1 physical tiles
			Total Size: 2457600 [D1, [1 x 1843200, 614400]][Tile0, 60:[160x2, 58:160x2, 160x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 1843200, 614400]][Tile0, 60:[160x2, 58:160x2, 160x2], 4]
		Tile0: [0, 30720, 1280], Tile1: [0, 30720, 1280], Tile2; [0, 30720, 1280]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 60 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 60:[9x1, 58:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 60:[9x1, 58:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (model_L1_Memory+7704);
	KerArg0->W = (unsigned short int) (160);
	KerArg0->H = (unsigned short int) (2);
	KerArg1->W = (unsigned short int) (324);
	KerArg1->UsedW = (unsigned short int) (321);
	KerArg1->H = (unsigned short int) (5);
	KerArg1->UsedH = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (1);
	KerArg1->TotalInFeatures = (unsigned short int) (1);
	KerArg1->Out = (int * __restrict__) (model_L1_Memory+7704);
	KerArg1->Pad = (v4s) 0;
	KerArg2->In = (int *__restrict__) (model_L1_Memory+7704);
	KerArg2->Out = (void *__restrict__) (model_L1_Memory+7704);
	KerArg2->W = (unsigned short int) (160);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Infos = (signed char *__restrict__) (model_L1_Memory+38424);
	KerArg3->In = (signed char * __restrict__) (model_L1_Memory+7704);
	KerArg3->W = (unsigned short int) (160);
	KerArg3->UsedW = (unsigned short int) (160);
	KerArg3->H = (unsigned short int) (2);
	KerArg3->UsedH = (unsigned short int) (2);
	KerArg3->Pad = (v4s) 0;
	KerArg3->PoolMax = (unsigned char) (1);
	KerArg3->DoScale = (unsigned char) (0);
	KerArg3->Infos = (signed char * __restrict__) (model_L1_Memory+38424);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1920; _LC_Out=80;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3240), 128, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3368), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3400), 32, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3432+0), 216, 0, &DmaR_Evt4);
	_N_Filter=0;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+172960+0), 1620, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+1296), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+172960+1620), 1620, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+172960+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 1620, 0, &DmaR_Evt5);
	_NN_In=1296; _SN_In=1620;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+38424), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++, D1Ind_Total++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		/*================================= Prepare Tiles ===================================*/
		_SN_Filter = 0;
		if (!(D1Ind_Last)) {
			_N_Filter = _N_Filter + (216); _SN_Filter = ((1)?72:216); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
		if (_SN_Filter) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3432+216*((D1Ind_Total+1)%2)),
					_SN_Filter, 0, &DmaR_Evt4);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<60; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==59), T0Ind_NextLast = ((T0Ind+1)==59), T0Ind_NextNextLast = ((T0Ind+2)==59);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Feat = (unsigned short int) (D1Ind_Last?8:24);
			KerArg0->Bias = (void * __restrict__) (model_L1_Memory+3240+((D1Ind)*96));
			KerArg0->NormBias = (unsigned char) (((char *)(model_L1_Memory+38424))[5]);
			AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
			__CALL(KerParSetBiasB32_SQ8, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(T0Ind_Last)) {
					if (!(T0Ind_NextLast)) {
						_NN_In = _NN_In + (1296); _SNN_In = (1620); 
					} else if (!(D1Ind_Last)) {
						_NN_In = _NN_In + (-76464); _SNN_In = (1620); 
					}
				} else if (!((D1Ind_Last))) {
					_NN_In = _NN_In + (1296); _SNN_In = (1620); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+172960+1620*((D0Ind_Total)%2)),
							_SNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+172960+1620*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+1620*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt5);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (signed char * __restrict__) (model_L1_Memory+0+1620*((D0Ind_Total)%2));
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?8:24);
				KerArg1->Filter = (signed char * __restrict__) (model_L1_Memory+3432+216*((D1Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_SQ8, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_SQ8, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Feat = (unsigned short int) (D1Ind_Last?8:24);
			KerArg2->Scale = (unsigned char *__restrict__) (model_L1_Memory+3368+((D1Ind)*24));
			KerArg2->ScaleN = (unsigned char *__restrict__) (model_L1_Memory+3400+((D1Ind)*24));
			AT_FORK(gap_ncore(), (void *) KerParReductIO_CC_SQ8, (void *) KerArg2);
			__CALL(KerParReductIO_CC_SQ8, KerArg2);
			KerArg3->Feat = (unsigned short int) (D1Ind_Last?8:24);
			KerArg3->Out = (signed char * __restrict__) (model_L1_Memory+3864+1920*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_ReLU_SQ8, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_ReLU_SQ8, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3864+1920*((T0Ind_Total)%2)),
					_SC_Out, 4800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (80); _LC_Out = (80); _SC_Out = (((D1Ind_Last)?8:24)*_LC_Out); 
			} else if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (115200)+(-4720); _LC_Out = (80); _SC_Out = (((1)?8:24)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
		/*================================= Update Arg Pipeline =============================*/
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 46412 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;
	KerPool_SQ8_T S_KerArg3, *KerArg3 = &S_KerArg3;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Total=0, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 2][Tile0 Dim: 29][D0 Dim: Init: 32, Tiled: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 58 logical tiles, 58 physical tiles
			Total Size: 72384 [D1, [1 x 36192, 36192]][Tile0, 29:[39x1, 27:39x1, 39x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 36192, 36192]][Tile0, 29:[39x1, 27:39x1, 39x1], 1]
		Tile0: [0, 1248, 39], Tile1: [39, 1248, 39], Tile2; [78, 1248, 39]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [1 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 128, 128]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: D1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 232 logical tiles, 2 physical tiles
			Total Size: 18432 [D1, [1 x 9216, 9216]][D0, [3 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 9216]][D0, [3 x 2304, 2304]]
		Tile0: [0, 9216, 288], Tile1: [9216, 9216, 288], Tile2; [0, 9216, 288]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 116 logical tiles, 116 physical tiles
			Total Size: 153600 [D0, [3 x 38400, 38400]][Tile0, 29:[80x4, 27:80x4, 80x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 29:[80x4, 27:80x4, 80x4], 1][D0, [3 x 38400, 38400]]
		Tile0: [0, 2560, 320], Tile1: [38400, 2560, 320], Tile2; [76800, 2560, 320]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 58 logical tiles, 1 physical tiles
			Total Size: 1158144 [D1, [1 x 579072, 579072]][Tile0, 29:[78x2, 27:78x2, 78x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 579072, 579072]][Tile0, 29:[78x2, 27:78x2, 78x2], 4]
		Tile0: [0, 19968, 624], Tile1: [0, 19968, 624], Tile2; [0, 19968, 624]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 29 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 29:[9x1, 27:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 29:[9x1, 27:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (model_L1_Memory+26432);
	KerArg0->W = (unsigned short int) (78);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->Feat = (unsigned short int) (32);
	KerArg1->W = (unsigned short int) (80);
	KerArg1->UsedW = (unsigned short int) (80);
	KerArg1->H = (unsigned short int) (4);
	KerArg1->UsedH = (unsigned short int) (4);
	KerArg1->InFeatures = (unsigned short int) (8);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->TotalInFeatures = (unsigned short int) (32);
	KerArg1->Out = (int * __restrict__) (model_L1_Memory+26432);
	KerArg1->Pad = (v4s) 0;
	KerArg2->In = (int *__restrict__) (model_L1_Memory+26432);
	KerArg2->Out = (void *__restrict__) (model_L1_Memory+26432);
	KerArg2->Feat = (unsigned short int) (32);
	KerArg2->W = (unsigned short int) (78);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Infos = (signed char *__restrict__) (model_L1_Memory+46400);
	KerArg3->In = (signed char * __restrict__) (model_L1_Memory+26432);
	KerArg3->W = (unsigned short int) (78);
	KerArg3->UsedW = (unsigned short int) (78);
	KerArg3->H = (unsigned short int) (2);
	KerArg3->UsedH = (unsigned short int) (2);
	KerArg3->Feat = (unsigned short int) (32);
	KerArg3->Pad = (v4s) 0;
	KerArg3->PoolMax = (unsigned char) (1);
	KerArg3->DoScale = (unsigned char) (0);
	KerArg3->Infos = (signed char * __restrict__) (model_L1_Memory+46400);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1248; _LC_Out=39;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5120), 256, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5376), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5440), 64, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5504+0), 9216, 0, &DmaR_Evt4);
	_N_Filter=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 2560, 4800, 320, 0, &DmaR_Evt5);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+46400), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++, D1Ind_Total++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		/*================================= Prepare Tiles ===================================*/
		_SN_Filter = 0;
		if (!(D1Ind_Last)) {
			_N_Filter = _N_Filter + (9216); _SN_Filter = (9216); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
		if (_SN_Filter) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5504+9216*((D1Ind_Total+1)%2)),
					_SN_Filter, 0, &DmaR_Evt4);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<29; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==28), T0Ind_NextLast = ((T0Ind+1)==28);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (void * __restrict__) (model_L1_Memory+5120+((D1Ind)*128));
			KerArg0->NormBias = (unsigned char) (((char *)(model_L1_Memory+46400))[5]);
			AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
			__CALL(KerParSetBiasB32_SQ8, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (38400); _LN_In = (320); _SN_In = (8*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (160)+(-115200); _LN_In = (320); _SN_In = (8*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-4480)+(-115200); _LN_In = (320); _SN_In = (8*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+2560*((D0Ind_Total+1)%2)),
							_SN_In, 4800, _LN_In, 0, &DmaR_Evt5);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (signed char * __restrict__) (model_L1_Memory+0+2560*((D0Ind_Total)%2));
				KerArg1->Filter = (signed char * __restrict__) (model_L1_Memory+5504+((D0Ind)*72)+9216*((D1Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_SQ8, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_SQ8, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Scale = (unsigned char *__restrict__) (model_L1_Memory+5376+((D1Ind)*32));
			KerArg2->ScaleN = (unsigned char *__restrict__) (model_L1_Memory+5440+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParReductIO_CC_SQ8, (void *) KerArg2);
			__CALL(KerParReductIO_CC_SQ8, KerArg2);
			KerArg3->Out = (signed char * __restrict__) (model_L1_Memory+23936+1248*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_ReLU_SQ8, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_ReLU_SQ8, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+172960+1248*((T0Ind_Total+-1)%2)),
						_SP_Out, 1131, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+172960+1248*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+23936+1248*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (39); _LC_Out = (39); _SC_Out = (32*_LC_Out); 
			} else if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (36192)+(-1092); _LC_Out = (39); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
		/*================================= Update Arg Pipeline =============================*/
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+172960+1248*((T0Ind_Total+-1)%2)), _SP_Out, 1131, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S4_Linear_2x29x39x64(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 48776 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerLinear_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _LN_Filter, _LNN_Filter;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 2, Tiled: 1][Tile0 Dim: 9]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 9 logical tiles, 9 physical tiles
			Total Size: 72384 [Tile0, 9:[1x8122, 7:1x8122, 1x7408], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 9:[1x8122, 7:1x8122, 1x7408], 1]
		Tile0: [0, 8122, 8122], Tile1: [8122, 8122, 8122], Tile2; [16244, 8122, 8122]
	Ker Arg: Filter, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 9 logical tiles, 9 physical tiles
			Total Size: 144768 [D0, [0 x 144768, 144768]][Tile0, 9:[1x8122, 7:1x8122, 1x7408], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 144768, 144768]][Tile0, 9:[1x8122, 7:1x8122, 1x7408], 1]
		Tile0: [0, 16244, 8122], Tile1: [16244, 16244, 8122], Tile2; [32488, 16244, 8122]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 8 [D0, [0 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 8, 8]]
		Tile0: [0, 8, 8], Tile1: [0, 8, 8], Tile2; [0, 8, 8]
	Ker Arg: LinOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 8 [D0, [0 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 8, 8]]
		Tile0: [0, 8, 8], Tile1: [0, 8, 8], Tile2; [0, 8, 8]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [D0, [0 x 2, 2]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2, 2]]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [D0, [0 x 2, 2]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2, 2]]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [D0, [0 x 2, 2]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2, 2]]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 9 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 9:[1x1, 7:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 9:[1x1, 7:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (model_L1_Memory+48744);
	KerArg0->W = (unsigned short int) (1);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Feat = (unsigned short int) (2);
	KerArg0->Bias = (void * __restrict__) (model_L1_Memory+48736);
	KerArg1->Out = (void * __restrict__) (model_L1_Memory+48744);
	KerArg1->OutDim = (unsigned short int) (2);
	KerArg1->Infos = (signed char *__restrict__) (model_L1_Memory+48764);
	KerArg2->In = (int *__restrict__) (model_L1_Memory+48744);
	KerArg2->Out = (void *__restrict__) (model_L1_Memory+48752);
	KerArg2->Feat = (unsigned short int) (2);
	KerArg2->W = (unsigned short int) (1);
	KerArg2->H = (unsigned short int) (1);
	KerArg2->Scale = (unsigned char *__restrict__) (model_L1_Memory+48756);
	KerArg2->ScaleN = (unsigned char *__restrict__) (model_L1_Memory+48760);
	KerArg2->Infos = (signed char *__restrict__) (model_L1_Memory+48764);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+19364+0), 8122, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+8122), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+19364+8124), 8122, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+19364+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 8122, 0, &DmaR_Evt1);
	_NN_In=8122; _SN_In=8122;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+35612+0), 16244, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+16244), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+35612+16244), 16244, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+35612+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+16248+0), 16244, 0, &DmaR_Evt2);
	_NN_Filter=16244; _SN_Filter=16244;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48736), 8, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48756), 2, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48760), 2, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48764), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		/*====================== Call Kernel LOC_LOOP_PROLOG =========================*/
		KerArg0->NormBias = (unsigned char) (((char *)(model_L1_Memory+48764))[5]);
		AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
		__CALL(KerParSetBiasB32_SQ8, KerArg0);
		for (T0Ind=0; T0Ind<9; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==8), T0Ind_NextLast = ((T0Ind+1)==8), T0Ind_NextNextLast = ((T0Ind+2)==8);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In = _NN_In + (8122); _SNN_In = ((T0Ind_NextNextLast)?7408:8122); 
				} else if (!(1)) {
					_NN_In = _NN_In + (-64976); _SNN_In = (8122); 
				}
			} else if (!((1))) {
				_NN_In = _NN_In + (8122); _SNN_In = (8122); 
			}
			_SNN_Filter = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_Filter = _NN_Filter + (16244); _LNN_Filter = ((T0Ind_NextNextLast)?7408:8122); _SNN_Filter = (2*_LNN_Filter); 
				}
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
			if (_SNN_In) {
				AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+19364+8124*((T0Ind_Total)%2)),
						_SNN_In, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+19364+8124*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+8124*((T0Ind_Total+1)%2)),
						_SN_In, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read Filter */
			if (_SNN_Filter) {
				AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+35612+16244*((T0Ind_Total)%2)),
						_SNN_Filter, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
			if (_SN_Filter) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+35612+16244*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+16248+16244*((T0Ind_Total+1)%2)),
						_SN_Filter, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg1->In = (signed char * __restrict__) (model_L1_Memory+0+8124*((T0Ind_Total)%2));
			KerArg1->Weights = (signed char * __restrict__) (model_L1_Memory+16248+16244*((T0Ind_Total)%2));
			KerArg1->InDim = (unsigned short int) (T0Ind_Last?7408:8122);
			KerArg1->TotalInDim = (unsigned short int) (T0Ind_Last?7408:8122);
			AT_FORK(gap_ncore(), (void *) KerParLinearLayer_SQ8, (void *) KerArg1);
			__CALL(KerParLinearLayer_SQ8, KerArg1);
			/*================================= Update Arg Pipeline =============================*/
			_SN_In = _SNN_In;
			_SN_Filter = _SNN_Filter;_LN_Filter = _LNN_Filter;
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		AT_FORK(gap_ncore(), (void *) KerParReduct_CC_SQ8, (void *) KerArg2);
		__CALL(KerParReduct_CC_SQ8, KerArg2);
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48752), 2, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S5_SoftMax(
		signed char * __restrict__ In,
		short int * __restrict__ Out,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 20 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	KerSoftMax_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [Tile0, 1:[1x2], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x2], 1]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4 [Tile0, 1:[1x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x2], 2]
		Tile0: [0, 4, 4], Tile1: [0, 4, 4], Tile2; [0, 4, 4]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (model_L1_Memory+0);
	KerArg0->N = (unsigned short int) (2);
	KerArg0->Out = (short int *__restrict__) (model_L1_Memory+4);
	KerArg0->Infos = (signed char *__restrict__) (model_L1_Memory+8);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0), 2, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+8), 9, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->Norm = (unsigned short int) (((char *)(model_L1_Memory+8))[0]);
		AT_FORK(gap_ncore(), (void *) KerParSoftMax_SQ8, (void *) KerArg0);
		__CALL(KerParSoftMax_SQ8, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+4), 4, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
int modelCNN_Construct()

{
	AT_HYPERFLASH_FS_FC_EVENT UchanHF1;
	AT_HYPERRAM_FC_EVENT UchanHR2;
	AT_HYPERRAM_CONF_T HyperRamConf;
	AT_HYPERFLASH_FS_CONF_T HyperFlashConf;
	int Error;
	AT_HYPERRAM_CONF_INIT(&HyperRamConf, AT_MEM_L3_HRAM, 0);
	AT_HYPERFLASH_FS_CONF_INIT(&HyperFlashConf, AT_MEM_L3_HFLASH, 0);
	AT_HYPERRAM_OPEN(&HyperRam, &HyperRamConf, &Error);
	if (Error) return 1;
	AT_HYPERFLASH_FS_OPEN(&HyperFlash, &HyperFlashConf, "model_L3_Flash_Const.dat", &Error);
	if (Error) return 1;
	model_L3_Memory = (AT_HYPERRAM_POINTER) AT_HYPERRAM_ALLOC(&HyperRam, 223824);
	if (model_L3_Memory == 0) return 2;
	model_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 176198);
	if (model_L2_Memory == 0) return 3;
	model_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 48776);
	if (model_L1_Memory == 0) return 4;
	/* Moving S4_Weights, size 144768 from HyperFlash at 0 to (size 144768) HyperRam at 0..144767 */
	{
		int Size = 144768, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 0+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L3_Memory + 0+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving S2_Infos, size 9 from HyperFlash at 164064 to (size 9) L2 at 19296..19304 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164064), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19296), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S2_Weights, size 288 from HyperFlash at 163200 to (size 288) L2 at 18432..18719 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 163200), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 18432), 288, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S2_Biases, size 128 from HyperFlash at 163744 to (size 128) L2 at 18976..19103 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 163744), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 18976), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S2_Mul_scale, size 32 from HyperFlash at 164000 to (size 32) L2 at 19232..19263 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164000), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19232), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S2_Mul_shift, size 32 from HyperFlash at 164032 to (size 32) L2 at 19264..19295 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164032), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19264), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Infos, size 9 from HyperFlash at 164076 to (size 9) L2 at 19308..19316 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164076), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19308), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Weights, size 18432 from HyperFlash at 144768 to (size 18432) L2 at 0..18431 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 144768), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 0), 18432, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Biases, size 256 from HyperFlash at 163488 to (size 256) L2 at 18720..18975 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 163488), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 18720), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Mul_scale, size 64 from HyperFlash at 163872 to (size 64) L2 at 19104..19167 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 163872), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19104), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Mul_shift, size 64 from HyperFlash at 163936 to (size 64) L2 at 19168..19231 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 163936), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19168), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Infos, size 9 from HyperFlash at 164088 to (size 9) L2 at 19320..19328 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164088), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19320), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Biases, size 8 from HyperFlash at 164112 to (size 8) L2 at 19344..19351 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164112), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19344), 8, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Mul_scale, size 2 from HyperFlash at 164120 to (size 2) L2 at 19352..19353 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164120), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19352), 2, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Mul_shift, size 2 from HyperFlash at 164124 to (size 2) L2 at 19356..19357 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164124), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19356), 2, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S5_Infos, size 9 from HyperFlash at 164100 to (size 9) L2 at 19332..19340 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 164100), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19332), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	return 0;
}
int modelCNN_Destruct()

{
	AT_HYPERRAM_FREE(&HyperRam, model_L3_Memory, 223824);
	AT_L2_FREE(0, model_L2_Memory, 176198);
	AT_L1_FREE(0, model_L1_Memory, 48776);
	AT_HYPERRAM_CLOSE(&HyperRam);
	AT_HYPERFLASH_FS_CLOSE(&HyperFlash);
	return 0;
}
unsigned int AT_GraphPerf[5];
unsigned int AT_GraphOperInfosNames[5] = {
	79056,
	6297600,
	83748288,
	144768,
	2,
};
char *AT_GraphNodeNames[5] = {
	"S1_Op_input_1_formatter",
	"S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu",
	"S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu",
	"S4_Linear_2x29x39x64",
	"S5_SoftMax",
};
int modelCNN(
		unsigned char * __restrict__ Input_1,
		signed short * __restrict__ Output_1)

{
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	S1_Op_input_1_formatter(
		((unsigned char * __restrict__) Input_1), /* In */
		((signed char * __restrict__) (model_L3_Memory+144768)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu(
		((signed char * __restrict__) (model_L3_Memory+144768)), /* In */
		((signed char * __restrict__) (model_L2_Memory+18432)), /* Filter */
		((signed int * __restrict__) (model_L2_Memory+18976)), /* Bias */
		((signed char * __restrict__) (model_L2_Memory+19360)), /* Out */
		((unsigned char * __restrict__) (model_L2_Memory+19232)), /* Scale */
		((signed char * __restrict__) (model_L2_Memory+19264)), /* ScaleN */
		((signed char * __restrict__) (model_L2_Memory+19296)) /* Infos */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu(
		((signed char * __restrict__) (model_L2_Memory+19360)), /* In */
		((signed char * __restrict__) (model_L2_Memory+0)), /* Filter */
		((signed int * __restrict__) (model_L2_Memory+18720)), /* Bias */
		((signed char * __restrict__) (model_L3_Memory+144768)), /* Out */
		((unsigned char * __restrict__) (model_L2_Memory+19104)), /* Scale */
		((signed char * __restrict__) (model_L2_Memory+19168)), /* ScaleN */
		((signed char * __restrict__) (model_L2_Memory+19308)) /* Infos */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S4_Linear_2x29x39x64(
		((signed char * __restrict__) (model_L3_Memory+144768)), /* In */
		((signed char * __restrict__) (model_L3_Memory+0)), /* Filter */
		((signed int * __restrict__) (model_L2_Memory+19344)), /* Bias */
		((signed char * __restrict__) (model_L2_Memory+19360)), /* Out */
		((unsigned char * __restrict__) (model_L2_Memory+19352)), /* Scale */
		((signed char * __restrict__) (model_L2_Memory+19356)), /* ScaleN */
		((signed char * __restrict__) (model_L2_Memory+19320)) /* Infos */
	);
	AT_GraphPerf[3] = gap_cl_readhwtimer() - AT_GraphPerf[3];
	AT_GraphPerf[4] = gap_cl_readhwtimer();
	S5_SoftMax(
		((signed char * __restrict__) (model_L2_Memory+19360)), /* In */
		((signed short * __restrict__) Output_1), /* Out */
		((signed char * __restrict__) (model_L2_Memory+19332)) /* Infos */
	);
	AT_GraphPerf[4] = gap_cl_readhwtimer() - AT_GraphPerf[4];
	return 0;
}
