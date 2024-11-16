#ifndef YOLOV5_BASIC_KERNELS_H
#define YOLOV5_BASIC_KERNELS_H
#include "at_api.h"
#include "DspLib.h"
#include "CNN_BasicKernels_SQ8.h"
#include "at_api.h"
#include "DspLib.h"

typedef struct {
    unsigned int I0;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_0_in_0;
    unsigned char *__restrict__  expr_0_in_1;
    unsigned char *__restrict__  expr_0_out_0;
} s18_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned int I1;
    unsigned int I2;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_1_in_0;
    signed char *__restrict__  expr_1_in_1;
    signed char *__restrict__  expr_1_in_2;
    unsigned char *__restrict__  expr_1_out_0;
} s184_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned int I1;
    unsigned int I2;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_2_in_0;
    signed char *__restrict__  expr_2_in_1;
    signed char *__restrict__  expr_2_in_2;
    unsigned char *__restrict__  expr_2_out_0;
} s211_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned int I1;
    unsigned int I2;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_3_in_0;
    signed char *__restrict__  expr_3_in_1;
    signed char *__restrict__  expr_3_in_2;
    unsigned char *__restrict__  expr_3_out_0;
} s217_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_4_in_0;
    unsigned char *__restrict__  expr_4_in_1;
    unsigned char *__restrict__  expr_4_out_0;
} s37_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_5_in_0;
    unsigned char *__restrict__  expr_5_in_1;
    unsigned char *__restrict__  expr_5_out_0;
} s57_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_6_in_0;
    unsigned char *__restrict__  expr_6_in_1;
    unsigned char *__restrict__  expr_6_out_0;
} s76_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned int I1;
    unsigned int I2;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_32_in_0;
    signed char *__restrict__  expr_32_in_1;
    signed char *__restrict__  expr_32_in_2;
    unsigned char *__restrict__  expr_32_out_0;
} s206_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned int I1;
    unsigned int I2;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_34_in_0;
    signed char *__restrict__  expr_34_in_1;
    signed char *__restrict__  expr_34_in_2;
    unsigned char *__restrict__  expr_34_out_0;
} s213_kernel_args_t;

typedef struct {
    unsigned int I0;
    unsigned int I1;
    unsigned int I2;
    unsigned short int *__restrict__  SigmoidLUTTable;
    unsigned char *__restrict__  expr_35_in_0;
    signed char *__restrict__  expr_35_in_1;
    signed char *__restrict__  expr_35_in_2;
    unsigned char *__restrict__  expr_35_out_0;
} s219_kernel_args_t;

typedef struct {
    unsigned char *__restrict__  expr_33_in_0;
    unsigned char *__restrict__  expr_33_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_33_args_t;

typedef struct {
    unsigned char *__restrict__  expr_45_in_0;
    unsigned char *__restrict__  expr_45_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_45_args_t;

typedef struct {
    unsigned char *__restrict__  expr_31_in_0;
    unsigned char *__restrict__  expr_31_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_31_args_t;

typedef struct {
    unsigned char *__restrict__  expr_13_in_0;
    unsigned char *__restrict__  expr_13_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_13_args_t;

typedef struct {
    unsigned char *__restrict__  expr_36_in_0;
    unsigned char *__restrict__  expr_36_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_36_args_t;

typedef struct {
    unsigned char *__restrict__  expr_37_in_0;
    unsigned char *__restrict__  expr_37_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_37_args_t;

typedef struct {
    unsigned char *__restrict__  expr_38_in_0;
    unsigned char *__restrict__  expr_38_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_38_args_t;

typedef struct {
    unsigned char *__restrict__  expr_39_in_0;
    unsigned char *__restrict__  expr_39_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_39_args_t;

typedef struct {
    unsigned char *__restrict__  expr_41_in_0;
    unsigned char *__restrict__  expr_41_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_41_args_t;

typedef struct {
    unsigned char *__restrict__  expr_42_in_0;
    unsigned char *__restrict__  expr_42_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_42_args_t;

typedef struct {
    unsigned char *__restrict__  expr_43_in_0;
    unsigned char *__restrict__  expr_43_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_43_args_t;

typedef struct {
    unsigned char *__restrict__  expr_44_in_0;
    unsigned char *__restrict__  expr_44_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_44_args_t;

typedef struct {
    unsigned char *__restrict__  expr_47_in_0;
    unsigned char *__restrict__  expr_47_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_47_args_t;

typedef struct {
    unsigned char *__restrict__  expr_48_in_0;
    unsigned char *__restrict__  expr_48_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_48_args_t;

typedef struct {
    unsigned char *__restrict__  expr_49_in_0;
    unsigned char *__restrict__  expr_49_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_49_args_t;

typedef struct {
    unsigned char *__restrict__  expr_50_in_0;
    unsigned char *__restrict__  expr_50_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_50_args_t;

typedef struct {
    unsigned char *__restrict__  expr_52_in_0;
    unsigned char *__restrict__  expr_52_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_52_args_t;

typedef struct {
    unsigned char *__restrict__  expr_53_in_0;
    unsigned char *__restrict__  expr_53_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_53_args_t;

typedef struct {
    unsigned char *__restrict__  expr_55_in_0;
    unsigned char *__restrict__  expr_55_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_55_args_t;

typedef struct {
    unsigned char *__restrict__  expr_56_in_0;
    unsigned char *__restrict__  expr_56_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_56_args_t;

typedef struct {
    unsigned char *__restrict__  expr_10_in_0;
    unsigned char *__restrict__  expr_10_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_10_args_t;

typedef struct {
    unsigned char *__restrict__  expr_8_in_0;
    unsigned char *__restrict__  expr_8_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_8_args_t;

typedef struct {
    unsigned char *__restrict__  expr_9_in_0;
    unsigned char *__restrict__  expr_9_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_9_args_t;

typedef struct {
    unsigned char *__restrict__  expr_11_in_0;
    unsigned char *__restrict__  expr_11_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_11_args_t;

typedef struct {
    unsigned char *__restrict__  expr_12_in_0;
    unsigned char *__restrict__  expr_12_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_12_args_t;

typedef struct {
    unsigned char *__restrict__  expr_14_in_0;
    unsigned char *__restrict__  expr_14_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_14_args_t;

typedef struct {
    unsigned char *__restrict__  expr_15_in_0;
    unsigned char *__restrict__  expr_15_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_15_args_t;

typedef struct {
    unsigned char *__restrict__  expr_16_in_0;
    unsigned char *__restrict__  expr_16_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_16_args_t;

typedef struct {
    unsigned char *__restrict__  expr_18_in_0;
    unsigned char *__restrict__  expr_18_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_18_args_t;

typedef struct {
    unsigned char *__restrict__  expr_19_in_0;
    unsigned char *__restrict__  expr_19_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_19_args_t;

typedef struct {
    unsigned char *__restrict__  expr_20_in_0;
    unsigned char *__restrict__  expr_20_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_20_args_t;

typedef struct {
    unsigned char *__restrict__  expr_21_in_0;
    unsigned char *__restrict__  expr_21_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_21_args_t;

typedef struct {
    unsigned char *__restrict__  expr_22_in_0;
    unsigned char *__restrict__  expr_22_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_22_args_t;

typedef struct {
    unsigned char *__restrict__  expr_24_in_0;
    unsigned char *__restrict__  expr_24_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_24_args_t;

typedef struct {
    unsigned char *__restrict__  expr_25_in_0;
    unsigned char *__restrict__  expr_25_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_25_args_t;

typedef struct {
    unsigned char *__restrict__  expr_26_in_0;
    unsigned char *__restrict__  expr_26_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_26_args_t;

typedef struct {
    unsigned char *__restrict__  expr_27_in_0;
    unsigned char *__restrict__  expr_27_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_27_args_t;

typedef struct {
    unsigned char *__restrict__  expr_28_in_0;
    unsigned char *__restrict__  expr_28_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_28_args_t;

typedef struct {
    unsigned char *__restrict__  expr_30_in_0;
    unsigned char *__restrict__  expr_30_out_0;
    unsigned short int W;
    unsigned short int H;
    unsigned short int Feat;
    unsigned short * __restrict__ SigmoidLUTTable;
} expr_30_args_t;


void s18_kernel(s18_kernel_args_t *Args);

void s184_kernel(s184_kernel_args_t *Args);

void s211_kernel(s211_kernel_args_t *Args);

void s217_kernel(s217_kernel_args_t *Args);

void s37_kernel(s37_kernel_args_t *Args);

void s57_kernel(s57_kernel_args_t *Args);

void s76_kernel(s76_kernel_args_t *Args);

void s206_kernel(s206_kernel_args_t *Args);

void s213_kernel(s213_kernel_args_t *Args);

void s219_kernel(s219_kernel_args_t *Args);

void expr_33(expr_33_args_t *Args);

void expr_45(expr_45_args_t *Args);

void expr_31(expr_31_args_t *Args);

void expr_13(expr_13_args_t *Args);

void expr_36(expr_36_args_t *Args);

void expr_37(expr_37_args_t *Args);

void expr_38(expr_38_args_t *Args);

void expr_39(expr_39_args_t *Args);

void expr_41(expr_41_args_t *Args);

void expr_42(expr_42_args_t *Args);

void expr_43(expr_43_args_t *Args);

void expr_44(expr_44_args_t *Args);

void expr_47(expr_47_args_t *Args);

void expr_48(expr_48_args_t *Args);

void expr_49(expr_49_args_t *Args);

void expr_50(expr_50_args_t *Args);

void expr_52(expr_52_args_t *Args);

void expr_53(expr_53_args_t *Args);

void expr_55(expr_55_args_t *Args);

void expr_56(expr_56_args_t *Args);

void expr_10(expr_10_args_t *Args);

void expr_8(expr_8_args_t *Args);

void expr_9(expr_9_args_t *Args);

void expr_11(expr_11_args_t *Args);

void expr_12(expr_12_args_t *Args);

void expr_14(expr_14_args_t *Args);

void expr_15(expr_15_args_t *Args);

void expr_16(expr_16_args_t *Args);

void expr_18(expr_18_args_t *Args);

void expr_19(expr_19_args_t *Args);

void expr_20(expr_20_args_t *Args);

void expr_21(expr_21_args_t *Args);

void expr_22(expr_22_args_t *Args);

void expr_24(expr_24_args_t *Args);

void expr_25(expr_25_args_t *Args);

void expr_26(expr_26_args_t *Args);

void expr_27(expr_27_args_t *Args);

void expr_28(expr_28_args_t *Args);

void expr_30(expr_30_args_t *Args);


#endif // YOLOV5_BASIC_KERNELS_H