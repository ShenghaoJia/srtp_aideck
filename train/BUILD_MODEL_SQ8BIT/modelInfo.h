#ifndef MODEL_GRAPHINFO_H
#define MODEL_GRAPHINFO_H
// Quantized scales can be used round_norm(val * QSCALE, QNORM) giving the real value in Q8

// S0_Op_input_1
#define S0_Op_input_1_OUT_SCALE	1
#define S0_Op_input_1_OUT_QSCALE	0
#define S0_Op_input_1_OUT_QNORM	0
// S1_Op_input_1_formatter
#define S1_Op_input_1_formatter_OUT_SCALE	0.0078125
#define S1_Op_input_1_formatter_OUT_QSCALE	64
#define S1_Op_input_1_formatter_OUT_QNORM	13
// S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu
#define S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu_OUT_SCALE	0.004521584138274193
#define S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu_OUT_QSCALE	74
#define S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu_OUT_QNORM	14
// S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu
#define S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu_OUT_SCALE	0.00634034676477313
#define S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu_OUT_QSCALE	104
#define S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu_OUT_QNORM	14
// S4_Linear_2x29x39x64
#define S4_Linear_2x29x39x64_OUT_SCALE	0.0625
#define S4_Linear_2x29x39x64_OUT_QSCALE	64
#define S4_Linear_2x29x39x64_OUT_QNORM	10
// S5_SoftMax
#define S5_SoftMax_OUT_SCALE	3.0517578125e-05
#define S5_SoftMax_OUT_QSCALE	64
#define S5_SoftMax_OUT_QNORM	21
// S6_Op_output_1
#define S6_Op_output_1_OUT_SCALE	3.0517578125e-05
#define S6_Op_output_1_OUT_QSCALE	64
#define S6_Op_output_1_OUT_QNORM	21
#endif //MODEL_GRAPHINFO_H