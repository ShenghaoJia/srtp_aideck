#include <stdint.h>
#include <stdio.h>
#include "AutoTilerLib.h"
#include "CNN_Generators_SQ8.h"
#include "RNN_Generators_SQ8.h"

#include "nntool_extra_generators.h"





void modelModel(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory, unsigned int L3Flash)
{
    KernelOper_T Cop = KOP_CONV;

    // SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);
    SetSymbolDynamics();

    SetUsedFilesNames(0, 3, "nntool_extra_kernels.h", "CNN_BasicKernels_SQ8.h", "model.h");
    SetGeneratedFilesNames("modelKernels.c", "modelKernels.h");
    AT_SetGraphCtrl(AT_GRAPH_MONITOR_CYCLES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_NODE_NAMES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_OPERINFOS, AT_OPT_ON);

    SetMemoryDeviceInfos(4,
        AT_MEM_L1, L1Memory, "model_L1_Memory", 0, 0,
        AT_MEM_L2, L2Memory, "model_L2_Memory", 0, 1,
        AT_MEM_L3_HRAM, L3Memory, "model_L3_Memory", 0, 0,
        AT_MEM_L3_HFLASH, L3Flash, "model_L3_Flash", "model_L3_Flash_Const.dat", 0
    );

    LoadCNN_SQ8_Library();
    Load_RNN_SQ8_Library();

    LoadNNTools_Extra_Library();

    // generator for input_1_formatter
    CNN_Norm("S1_Op_input_1_formatter", 324, 244, 1, NNTOOL_KOP_BW);
    // generator for DEPTHWISE_CONV_2D_0_0_fusion
    CNN_ConvolutionPoolAct_SQ8("S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu", 0, 4, 1, 1, 32, 324, 244,
        KOP_CONV, 3, 3, 1, 1, 2, 2, 0,
        KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
        KOP_RELU);
    // generator for CONV_2D_0_2_fusion
    CNN_ConvolutionPoolAct_SQ8("S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu", 0, 4, 1, 32, 64, 80, 60,
        KOP_CONV, 3, 3, 1, 1, 1, 1, 0,
        KOP_MAXPOOL, 2, 2, 1, 1, 2, 2, 0,
        KOP_RELU);
    // generator for FULLY_CONNECTED_0_4
    CNN_LinearAct_SQ8("S4_Linear_2x29x39x64", 0, 4, 1, 72384, 2, KOP_LINEAR, KOP_NONE);
    // generator for SOFTMAX_0_5
    CNN_SoftMax_SQ8("S5_SoftMax", 0, 2, KOP_SOFTMAX);

#define GRAPH
#ifdef GRAPH
    CreateGraph("modelCNN",
        /* Arguments either passed or globals */
            CArgs(18,
                TCArgInfo("unsigned char * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                // all 0
                TCArgInfo("signed char * __restrict__", "S2_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S2_Infos.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed char * __restrict__", "S2_Weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S2_Weights.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed int * __restrict__", "S2_Biases", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S2_Biases.tensor", 1, 1, 4, 0)),
                TCArgInfo("unsigned char * __restrict__", "S2_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S2_Mul_scale.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed char * __restrict__", "S2_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S2_Mul_shift.tensor", 1, 1, 1, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S3_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S3_Infos.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed char * __restrict__", "S3_Weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S3_Weights.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed int * __restrict__", "S3_Biases", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S3_Biases.tensor", 1, 1, 4, 0)),
                TCArgInfo("unsigned char * __restrict__", "S3_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S3_Mul_scale.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed char * __restrict__", "S3_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S3_Mul_shift.tensor", 1, 1, 1, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S4_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S4_Infos.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed char * __restrict__", "S4_Weights", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S4_Weights.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed int * __restrict__", "S4_Biases", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S4_Biases.tensor", 1, 1, 4, 0)),
                TCArgInfo("unsigned char * __restrict__", "S4_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S4_Mul_scale.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed char * __restrict__", "S4_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S4_Mul_shift.tensor", 1, 1, 1, 0)),
                // in: 0.062500 out: 0.000031 NORM: 11
                TCArgInfo("signed char * __restrict__", "S5_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_SQ8BIT/tensors/S5_Infos.tensor", 1, 1, 1, 0)),
                TCArgInfo("signed short * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(4,
            TCArgInfo("signed char * __restrict__", "S1_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S2_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S3_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S4_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );

    /* Stacked tensors - Concats */
    // no concats in graph so not stacked tensors created

    // Node input_1_formatter inq unkn<(u8-0.00)*1.00000000<unkn outq -1.00<i8*0.00781250<0.99
    AddNode("S1_Op_input_1_formatter", Bindings(2, GNodeArg(GNA_IN, "Input_1", 0), GNodeArg(GNA_OUT, "S1_Output", 0)));
    // Node S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu inq -1.00<i8*0.00781250<0.99 weightsq chan<i8*chan<chan outq -0.58<i8*0.00452158<0.57 biasesq i32*chan
    AddNode("S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu", Bindings(7, GNodeArg(GNA_IN, "S1_Output", 0), GNodeArg(GNA_IN, "S2_Weights", 0), GNodeArg(GNA_IN, "S2_Biases", 0), GNodeArg(GNA_OUT, "S2_Output", 0), GNodeArg(GNA_IN, "S2_Mul_scale", 0), GNodeArg(GNA_IN, "S2_Mul_shift", 0), GNodeArg(GNA_IN, "S2_Infos", 0)));
    // Node S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu inq -0.58<i8*0.00452158<0.57 weightsq chan<i8*chan<chan outq -0.81<i8*0.00634035<0.81 biasesq i32*chan
    AddNode("S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu", Bindings(7, GNodeArg(GNA_IN, "S2_Output", 0), GNodeArg(GNA_IN, "S3_Weights", 0), GNodeArg(GNA_IN, "S3_Biases", 0), GNodeArg(GNA_OUT, "S3_Output", 0), GNodeArg(GNA_IN, "S3_Mul_scale", 0), GNodeArg(GNA_IN, "S3_Mul_shift", 0), GNodeArg(GNA_IN, "S3_Infos", 0)));
    // Node FULLY_CONNECTED_0_4 inq -0.81<i8*0.00634035<0.81 weightsq chan<i8*chan<chan outq -7.99<i8*0.06250000<7.93
    AddNode("S4_Linear_2x29x39x64", Bindings(7, GNodeArg(GNA_IN, "S3_Output", 0), GNodeArg(GNA_IN, "S4_Weights", 0), GNodeArg(GNA_IN, "S4_Biases", 0), GNodeArg(GNA_OUT, "S4_Output", 0), GNodeArg(GNA_IN, "S4_Mul_scale", 0), GNodeArg(GNA_IN, "S4_Mul_shift", 0), GNodeArg(GNA_IN, "S4_Infos", 0)));
    // Node SOFTMAX_0_5 inq 4 outq 15
    AddNode("S5_SoftMax", Bindings(3, GNodeArg(GNA_IN, "S4_Output", 0), GNodeArg(GNA_OUT, "Output_1", 0), GNodeArg(GNA_IN, "S5_Infos", 0)));
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    modelModel(52000, 300*1024, 8*1024*1024, 20*1024*1024);
    GenerateTilingCode();
    return 0;
}
