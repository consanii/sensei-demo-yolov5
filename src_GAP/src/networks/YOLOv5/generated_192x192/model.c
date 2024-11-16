#include <stdint.h>
#include <stdio.h>
#include "AutoTilerLib.h"
#include "CNN_Generators_SQ8.h"
#include "CNN_Generators.h"
#include "CNN_Generators_NE16.h"
#include "ResizeGenerator.h"

#include "CNN_Copy_Generators.h"

void load_expressions_kernels() {
    LibKernelTemplate(
        "s18_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_0_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_0_in_1"),
            TCArg("unsigned char *__restrict__ ", "expr_0_out_0")
        )
    );
    
    LibKernel(
        "s18_kernel",
        CALL_PARALLEL,
        0,
        "s18_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s184_kernel_args_t",
        CArgs(8,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned int", "I1"),
            TCArg("unsigned int", "I2"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_1_in_0"),
            TCArg("signed char *__restrict__ ", "expr_1_in_1"),
            TCArg("signed char *__restrict__ ", "expr_1_in_2"),
            TCArg("unsigned char *__restrict__ ", "expr_1_out_0")
        )
    );
    
    LibKernel(
        "s184_kernel",
        CALL_PARALLEL,
        0,
        "s184_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s211_kernel_args_t",
        CArgs(8,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned int", "I1"),
            TCArg("unsigned int", "I2"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_2_in_0"),
            TCArg("signed char *__restrict__ ", "expr_2_in_1"),
            TCArg("signed char *__restrict__ ", "expr_2_in_2"),
            TCArg("unsigned char *__restrict__ ", "expr_2_out_0")
        )
    );
    
    LibKernel(
        "s211_kernel",
        CALL_PARALLEL,
        0,
        "s211_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s217_kernel_args_t",
        CArgs(8,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned int", "I1"),
            TCArg("unsigned int", "I2"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_3_in_0"),
            TCArg("signed char *__restrict__ ", "expr_3_in_1"),
            TCArg("signed char *__restrict__ ", "expr_3_in_2"),
            TCArg("unsigned char *__restrict__ ", "expr_3_out_0")
        )
    );
    
    LibKernel(
        "s217_kernel",
        CALL_PARALLEL,
        0,
        "s217_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s37_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_4_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_4_in_1"),
            TCArg("unsigned char *__restrict__ ", "expr_4_out_0")
        )
    );
    
    LibKernel(
        "s37_kernel",
        CALL_PARALLEL,
        0,
        "s37_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s57_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_5_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_5_in_1"),
            TCArg("unsigned char *__restrict__ ", "expr_5_out_0")
        )
    );
    
    LibKernel(
        "s57_kernel",
        CALL_PARALLEL,
        0,
        "s57_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s76_kernel_args_t",
        CArgs(5,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_6_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_6_in_1"),
            TCArg("unsigned char *__restrict__ ", "expr_6_out_0")
        )
    );
    
    LibKernel(
        "s76_kernel",
        CALL_PARALLEL,
        0,
        "s76_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s206_kernel_args_t",
        CArgs(8,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned int", "I1"),
            TCArg("unsigned int", "I2"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_32_in_0"),
            TCArg("signed char *__restrict__ ", "expr_32_in_1"),
            TCArg("signed char *__restrict__ ", "expr_32_in_2"),
            TCArg("unsigned char *__restrict__ ", "expr_32_out_0")
        )
    );
    
    LibKernel(
        "s206_kernel",
        CALL_PARALLEL,
        0,
        "s206_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s213_kernel_args_t",
        CArgs(8,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned int", "I1"),
            TCArg("unsigned int", "I2"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_34_in_0"),
            TCArg("signed char *__restrict__ ", "expr_34_in_1"),
            TCArg("signed char *__restrict__ ", "expr_34_in_2"),
            TCArg("unsigned char *__restrict__ ", "expr_34_out_0")
        )
    );
    
    LibKernel(
        "s213_kernel",
        CALL_PARALLEL,
        0,
        "s213_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "s219_kernel_args_t",
        CArgs(8,
            TCArg("unsigned int", "I0"),
            TCArg("unsigned int", "I1"),
            TCArg("unsigned int", "I2"),
            TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
            TCArg("unsigned char *__restrict__ ", "expr_35_in_0"),
            TCArg("signed char *__restrict__ ", "expr_35_in_1"),
            TCArg("signed char *__restrict__ ", "expr_35_in_2"),
            TCArg("unsigned char *__restrict__ ", "expr_35_out_0")
        )
    );
    
    LibKernel(
        "s219_kernel",
        CALL_PARALLEL,
        0,
        "s219_kernel_args_t",
        0
    );
    LibKernelTemplate(
        "expr_33_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_33_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_33_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_33",
        CALL_PARALLEL,
        0,
        "expr_33_args_t",
        0
    );
    LibKernelTemplate(
        "expr_45_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_45_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_45_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_45",
        CALL_PARALLEL,
        0,
        "expr_45_args_t",
        0
    );
    LibKernelTemplate(
        "expr_31_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_31_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_31_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_31",
        CALL_PARALLEL,
        0,
        "expr_31_args_t",
        0
    );
    LibKernelTemplate(
        "expr_13_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_13_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_13_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_13",
        CALL_PARALLEL,
        0,
        "expr_13_args_t",
        0
    );
    LibKernelTemplate(
        "expr_36_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_36_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_36_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_36",
        CALL_PARALLEL,
        0,
        "expr_36_args_t",
        0
    );
    LibKernelTemplate(
        "expr_37_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_37_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_37_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_37",
        CALL_PARALLEL,
        0,
        "expr_37_args_t",
        0
    );
    LibKernelTemplate(
        "expr_38_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_38_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_38_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_38",
        CALL_PARALLEL,
        0,
        "expr_38_args_t",
        0
    );
    LibKernelTemplate(
        "expr_39_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_39_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_39_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_39",
        CALL_PARALLEL,
        0,
        "expr_39_args_t",
        0
    );
    LibKernelTemplate(
        "expr_41_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_41_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_41_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_41",
        CALL_PARALLEL,
        0,
        "expr_41_args_t",
        0
    );
    LibKernelTemplate(
        "expr_42_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_42_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_42_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_42",
        CALL_PARALLEL,
        0,
        "expr_42_args_t",
        0
    );
    LibKernelTemplate(
        "expr_43_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_43_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_43_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_43",
        CALL_PARALLEL,
        0,
        "expr_43_args_t",
        0
    );
    LibKernelTemplate(
        "expr_44_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_44_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_44_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_44",
        CALL_PARALLEL,
        0,
        "expr_44_args_t",
        0
    );
    LibKernelTemplate(
        "expr_47_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_47_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_47_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_47",
        CALL_PARALLEL,
        0,
        "expr_47_args_t",
        0
    );
    LibKernelTemplate(
        "expr_48_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_48_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_48_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_48",
        CALL_PARALLEL,
        0,
        "expr_48_args_t",
        0
    );
    LibKernelTemplate(
        "expr_49_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_49_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_49_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_49",
        CALL_PARALLEL,
        0,
        "expr_49_args_t",
        0
    );
    LibKernelTemplate(
        "expr_50_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_50_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_50_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_50",
        CALL_PARALLEL,
        0,
        "expr_50_args_t",
        0
    );
    LibKernelTemplate(
        "expr_52_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_52_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_52_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_52",
        CALL_PARALLEL,
        0,
        "expr_52_args_t",
        0
    );
    LibKernelTemplate(
        "expr_53_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_53_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_53_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_53",
        CALL_PARALLEL,
        0,
        "expr_53_args_t",
        0
    );
    LibKernelTemplate(
        "expr_55_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_55_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_55_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_55",
        CALL_PARALLEL,
        0,
        "expr_55_args_t",
        0
    );
    LibKernelTemplate(
        "expr_56_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_56_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_56_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_56",
        CALL_PARALLEL,
        0,
        "expr_56_args_t",
        0
    );
    LibKernelTemplate(
        "expr_10_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_10_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_10_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_10",
        CALL_PARALLEL,
        0,
        "expr_10_args_t",
        0
    );
    LibKernelTemplate(
        "expr_8_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_8_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_8_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_8",
        CALL_PARALLEL,
        0,
        "expr_8_args_t",
        0
    );
    LibKernelTemplate(
        "expr_9_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_9_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_9_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_9",
        CALL_PARALLEL,
        0,
        "expr_9_args_t",
        0
    );
    LibKernelTemplate(
        "expr_11_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_11_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_11_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_11",
        CALL_PARALLEL,
        0,
        "expr_11_args_t",
        0
    );
    LibKernelTemplate(
        "expr_12_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_12_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_12_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_12",
        CALL_PARALLEL,
        0,
        "expr_12_args_t",
        0
    );
    LibKernelTemplate(
        "expr_14_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_14_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_14_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_14",
        CALL_PARALLEL,
        0,
        "expr_14_args_t",
        0
    );
    LibKernelTemplate(
        "expr_15_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_15_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_15_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_15",
        CALL_PARALLEL,
        0,
        "expr_15_args_t",
        0
    );
    LibKernelTemplate(
        "expr_16_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_16_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_16_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_16",
        CALL_PARALLEL,
        0,
        "expr_16_args_t",
        0
    );
    LibKernelTemplate(
        "expr_18_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_18_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_18_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_18",
        CALL_PARALLEL,
        0,
        "expr_18_args_t",
        0
    );
    LibKernelTemplate(
        "expr_19_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_19_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_19_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_19",
        CALL_PARALLEL,
        0,
        "expr_19_args_t",
        0
    );
    LibKernelTemplate(
        "expr_20_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_20_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_20_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_20",
        CALL_PARALLEL,
        0,
        "expr_20_args_t",
        0
    );
    LibKernelTemplate(
        "expr_21_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_21_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_21_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_21",
        CALL_PARALLEL,
        0,
        "expr_21_args_t",
        0
    );
    LibKernelTemplate(
        "expr_22_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_22_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_22_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_22",
        CALL_PARALLEL,
        0,
        "expr_22_args_t",
        0
    );
    LibKernelTemplate(
        "expr_24_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_24_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_24_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_24",
        CALL_PARALLEL,
        0,
        "expr_24_args_t",
        0
    );
    LibKernelTemplate(
        "expr_25_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_25_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_25_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_25",
        CALL_PARALLEL,
        0,
        "expr_25_args_t",
        0
    );
    LibKernelTemplate(
        "expr_26_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_26_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_26_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_26",
        CALL_PARALLEL,
        0,
        "expr_26_args_t",
        0
    );
    LibKernelTemplate(
        "expr_27_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_27_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_27_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_27",
        CALL_PARALLEL,
        0,
        "expr_27_args_t",
        0
    );
    LibKernelTemplate(
        "expr_28_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_28_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_28_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_28",
        CALL_PARALLEL,
        0,
        "expr_28_args_t",
        0
    );
    LibKernelTemplate(
        "expr_30_args_t",
        CArgs(6,
            TCArg("unsigned char *__restrict__ ", "expr_30_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_30_out_0"),
            TCArg("unsigned short int", "W"),
            TCArg("unsigned short int", "H"),
            TCArg("unsigned short int", "Feat"),
            TCArg("unsigned short * __restrict__", "SigmoidLUTTable")
        )
    );
    
    LibKernel(
        "expr_30",
        CALL_PARALLEL,
        0,
        "expr_30_args_t",
        0
    );
}



int s18_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (48, 48, 8) spaces: ((0, 1, 2),) 
        // parametric_spaces: ((0, 1, 2),) 
        // exterior_shape: (18432.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 18432, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(4,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_0_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_0_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_0_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s18_kernel", LOC_D0,
                Bindings(5,
                    K_ArgPar("expr_0_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_0_in_0", KER_ARG_TILE),
                    K_Arg("expr_0_in_1", KER_ARG_TILE),
                    K_Arg("expr_0_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_0_out_0 axes: (0,)
        // var: expr_0_in_1 axes: (0,)
        // var: expr_0_in_0 axes: (0,)
        KerArgs(4,
            KerArg("expr_0_out_0",    KerArgSpace(1, KER_ITER_D0),    O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_0_out_0"),
            KerArg("expr_0_in_1",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_0_in_1"),
            KerArg("expr_0_in_0",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_0_in_0"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 55296, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 55552, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,       2);
        AddKernelArgDimExplicit(Name, "expr_0_in_0", ARG_INT,     4, 48, 48, 8, 1);
        AddKernelArgDimExplicit(Name, "expr_0_in_1", ARG_INT,     4, 48, 48, 8, 1);
        AddKernelArgDimExplicit(Name, "expr_0_out_0", ARG_INT,    4, 48, 48, 8, 1);
    }
    return (Kernel!=0);
}
int s184_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (1, 36, 3, 2) spaces: ((1,), (2,), (3,)) 
        // fixed_spaces: ((1,),) parametric_spaces: ((2,), (3,)) 
        // exterior_shape: (36, 3, 2.0) 
        KernelIterSpace(4, IterFixedSpace(KER_ITER_D0, 36), IterParSpace(KER_ITER_D1, 3, 8), IterParSpace(KER_ITER_D2, 2, 1), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(5,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_1_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_1_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_1_in_2"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_1_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s184_kernel", LOC_D2,
                Bindings(8,
                    K_ArgPar("expr_1_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_ArgPar("expr_1_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D1),
                    K_ArgPar("expr_1_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D2),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_1_in_0", KER_ARG_TILE),
                    K_Arg("expr_1_in_1", KER_ARG_TILE),
                    K_Arg("expr_1_in_2", KER_ARG_TILE),
                    K_Arg("expr_1_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_1_out_0 axes: (0, 1, 2)
        // var: expr_1_in_0 axes: (0, 1, 2)
        // var: expr_1_in_1 axes: (0, 2)
        // var: expr_1_in_2 axes: (2,)
        KerArgs(5,
            KerArg("expr_1_out_0",    KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_1_out_0"),
            KerArg("expr_1_in_0",     KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_1_in_0"),
            KerArg("expr_1_in_1",     KerArgSpace(2, KER_ITER_D0, KER_ITER_D2),              O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_1_in_1"),
            KerArg("expr_1_in_2",     KerArgSpace(1, KER_ITER_D2),                           O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_1_in_2"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0),                        O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 1080, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 762, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,      2);
        AddKernelArgDimExplicit(Name, "expr_1_in_0", ARG_INT,     4, 36, 3, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_1_in_1", ARG_INT,     4, 36, 1, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_1_in_2", ARG_INT,     2, 2,        1);
        AddKernelArgDimExplicit(Name, "expr_1_out_0", ARG_INT,    4, 36, 3, 2, 1);
    }
    return (Kernel!=0);
}
int s211_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (1, 144, 3, 2) spaces: ((1,), (2,), (3,)) 
        // fixed_spaces: ((1,),) parametric_spaces: ((2,), (3,)) 
        // exterior_shape: (144, 3, 2.0) 
        KernelIterSpace(4, IterFixedSpace(KER_ITER_D0, 144), IterParSpace(KER_ITER_D1, 3, 8), IterParSpace(KER_ITER_D2, 2, 1), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(5,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_2_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_2_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_2_in_2"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_2_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s211_kernel", LOC_D2,
                Bindings(8,
                    K_ArgPar("expr_2_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_ArgPar("expr_2_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D1),
                    K_ArgPar("expr_2_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D2),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_2_in_0", KER_ARG_TILE),
                    K_Arg("expr_2_in_1", KER_ARG_TILE),
                    K_Arg("expr_2_in_2", KER_ARG_TILE),
                    K_Arg("expr_2_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_2_out_0 axes: (0, 1, 2)
        // var: expr_2_in_0 axes: (0, 1, 2)
        // var: expr_2_in_1 axes: (0, 2)
        // var: expr_2_in_2 axes: (2,)
        KerArgs(5,
            KerArg("expr_2_out_0",    KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_2_out_0"),
            KerArg("expr_2_in_0",     KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_2_in_0"),
            KerArg("expr_2_in_1",     KerArgSpace(2, KER_ITER_D0, KER_ITER_D2),              O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_2_in_1"),
            KerArg("expr_2_in_2",     KerArgSpace(1, KER_ITER_D2),                           O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_2_in_2"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0),                        O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 4320, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 2274, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,       2);
        AddKernelArgDimExplicit(Name, "expr_2_in_0", ARG_INT,     4, 144, 3, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_2_in_1", ARG_INT,     4, 144, 1, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_2_in_2", ARG_INT,     2, 2,         1);
        AddKernelArgDimExplicit(Name, "expr_2_out_0", ARG_INT,    4, 144, 3, 2, 1);
    }
    return (Kernel!=0);
}
int s217_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (1, 576, 3, 2) spaces: ((1,), (2,), (3,)) 
        // fixed_spaces: ((1,),) parametric_spaces: ((2,), (3,)) 
        // exterior_shape: (576, 3, 2.0) 
        KernelIterSpace(4, IterFixedSpace(KER_ITER_D0, 576), IterParSpace(KER_ITER_D1, 3, 8), IterParSpace(KER_ITER_D2, 2, 1), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(5,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_3_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_3_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_3_in_2"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_3_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s217_kernel", LOC_D2,
                Bindings(8,
                    K_ArgPar("expr_3_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_ArgPar("expr_3_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D1),
                    K_ArgPar("expr_3_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D2),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_3_in_0", KER_ARG_TILE),
                    K_Arg("expr_3_in_1", KER_ARG_TILE),
                    K_Arg("expr_3_in_2", KER_ARG_TILE),
                    K_Arg("expr_3_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_3_out_0 axes: (0, 1, 2)
        // var: expr_3_in_0 axes: (0, 1, 2)
        // var: expr_3_in_1 axes: (0, 2)
        // var: expr_3_in_2 axes: (2,)
        KerArgs(5,
            KerArg("expr_3_out_0",    KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_3_out_0"),
            KerArg("expr_3_in_0",     KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_3_in_0"),
            KerArg("expr_3_in_1",     KerArgSpace(2, KER_ITER_D0, KER_ITER_D2),              O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_3_in_1"),
            KerArg("expr_3_in_2",     KerArgSpace(1, KER_ITER_D2),                           O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_3_in_2"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0),                        O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 17280, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 8322, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,       2);
        AddKernelArgDimExplicit(Name, "expr_3_in_0", ARG_INT,     4, 576, 3, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_3_in_1", ARG_INT,     4, 576, 1, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_3_in_2", ARG_INT,     2, 2,         1);
        AddKernelArgDimExplicit(Name, "expr_3_out_0", ARG_INT,    4, 576, 3, 2, 1);
    }
    return (Kernel!=0);
}
int s37_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (24, 24, 16) spaces: ((0, 1, 2),) 
        // parametric_spaces: ((0, 1, 2),) 
        // exterior_shape: (9216.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 9216, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(4,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_4_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_4_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_4_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s37_kernel", LOC_D0,
                Bindings(5,
                    K_ArgPar("expr_4_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_4_in_0", KER_ARG_TILE),
                    K_Arg("expr_4_in_1", KER_ARG_TILE),
                    K_Arg("expr_4_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_4_out_0 axes: (0,)
        // var: expr_4_in_1 axes: (0,)
        // var: expr_4_in_0 axes: (0,)
        KerArgs(4,
            KerArg("expr_4_out_0",    KerArgSpace(1, KER_ITER_D0),    O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_4_out_0"),
            KerArg("expr_4_in_1",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_4_in_1"),
            KerArg("expr_4_in_0",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_4_in_0"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 27648, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 27904, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,        2);
        AddKernelArgDimExplicit(Name, "expr_4_in_0", ARG_INT,     4, 24, 24, 16, 1);
        AddKernelArgDimExplicit(Name, "expr_4_in_1", ARG_INT,     4, 24, 24, 16, 1);
        AddKernelArgDimExplicit(Name, "expr_4_out_0", ARG_INT,    4, 24, 24, 16, 1);
    }
    return (Kernel!=0);
}
int s57_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (12, 12, 28) spaces: ((0, 1, 2),) 
        // parametric_spaces: ((0, 1, 2),) 
        // exterior_shape: (4032.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 4032, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(4,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_5_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_5_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_5_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s57_kernel", LOC_D0,
                Bindings(5,
                    K_ArgPar("expr_5_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_5_in_0", KER_ARG_TILE),
                    K_Arg("expr_5_in_1", KER_ARG_TILE),
                    K_Arg("expr_5_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_5_out_0 axes: (0,)
        // var: expr_5_in_1 axes: (0,)
        // var: expr_5_in_0 axes: (0,)
        KerArgs(4,
            KerArg("expr_5_out_0",    KerArgSpace(1, KER_ITER_D0),    O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_5_out_0"),
            KerArg("expr_5_in_1",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_5_in_1"),
            KerArg("expr_5_in_0",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_5_in_0"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 12096, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 12352, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,        2);
        AddKernelArgDimExplicit(Name, "expr_5_in_0", ARG_INT,     4, 12, 12, 28, 1);
        AddKernelArgDimExplicit(Name, "expr_5_in_1", ARG_INT,     4, 12, 12, 28, 1);
        AddKernelArgDimExplicit(Name, "expr_5_out_0", ARG_INT,    4, 12, 12, 28, 1);
    }
    return (Kernel!=0);
}
int s76_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (6, 6, 52) spaces: ((0, 1, 2),) 
        // parametric_spaces: ((0, 1, 2),) 
        // exterior_shape: (1872.0,) 
        KernelIterSpace(2, IterParSpace(KER_ITER_D0, 1872, 8), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(4,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_6_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_6_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_6_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s76_kernel", LOC_D0,
                Bindings(5,
                    K_ArgPar("expr_6_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_6_in_0", KER_ARG_TILE),
                    K_Arg("expr_6_in_1", KER_ARG_TILE),
                    K_Arg("expr_6_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_6_out_0 axes: (0,)
        // var: expr_6_in_1 axes: (0,)
        // var: expr_6_in_0 axes: (0,)
        KerArgs(4,
            KerArg("expr_6_out_0",    KerArgSpace(1, KER_ITER_D0),    O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_6_out_0"),
            KerArg("expr_6_in_1",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_6_in_1"),
            KerArg("expr_6_in_0",     KerArgSpace(1, KER_ITER_D0),    O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_6_in_0"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 5616, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 5872, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,      2);
        AddKernelArgDimExplicit(Name, "expr_6_in_0", ARG_INT,     4, 6, 6, 52, 1);
        AddKernelArgDimExplicit(Name, "expr_6_in_1", ARG_INT,     4, 6, 6, 52, 1);
        AddKernelArgDimExplicit(Name, "expr_6_out_0", ARG_INT,    4, 6, 6, 52, 1);
    }
    return (Kernel!=0);
}
int s206_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (1, 36, 3, 2) spaces: ((1,), (2,), (3,)) 
        // fixed_spaces: ((1,),) parametric_spaces: ((2,), (3,)) 
        // exterior_shape: (36, 3, 2.0) 
        KernelIterSpace(4, IterFixedSpace(KER_ITER_D0, 36), IterParSpace(KER_ITER_D1, 3, 8), IterParSpace(KER_ITER_D2, 2, 1), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(5,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_32_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_32_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_32_in_2"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_32_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s206_kernel", LOC_D2,
                Bindings(8,
                    K_ArgPar("expr_32_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_ArgPar("expr_32_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D1),
                    K_ArgPar("expr_32_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D2),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_32_in_0", KER_ARG_TILE),
                    K_Arg("expr_32_in_1", KER_ARG_TILE),
                    K_Arg("expr_32_in_2", KER_ARG_TILE),
                    K_Arg("expr_32_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_32_in_0 axes: (0, 1, 2)
        // var: expr_32_out_0 axes: (0, 1, 2)
        // var: expr_32_in_1 axes: (1, 2)
        // var: expr_32_in_2 axes: (2,)
        KerArgs(5,
            KerArg("expr_32_in_0",    KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_32_in_0"),
            KerArg("expr_32_out_0",   KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_32_out_0"),
            KerArg("expr_32_in_1",    KerArgSpace(2, KER_ITER_D1, KER_ITER_D2),              O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_32_in_1"),
            KerArg("expr_32_in_2",    KerArgSpace(1, KER_ITER_D2),                           O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_32_in_2"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0),                        O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 864, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 696, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,      2);
        AddKernelArgDimExplicit(Name, "expr_32_in_0", ARG_INT,    4, 36, 3, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_32_in_1", ARG_INT,    3, 3, 2,     1);
        AddKernelArgDimExplicit(Name, "expr_32_in_2", ARG_INT,    2, 2,        1);
        AddKernelArgDimExplicit(Name, "expr_32_out_0", ARG_INT,   4, 36, 3, 2, 1);
    }
    return (Kernel!=0);
}
int s213_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (1, 144, 3, 2) spaces: ((1,), (2,), (3,)) 
        // fixed_spaces: ((1,),) parametric_spaces: ((2,), (3,)) 
        // exterior_shape: (144, 3, 2.0) 
        KernelIterSpace(4, IterFixedSpace(KER_ITER_D0, 144), IterParSpace(KER_ITER_D1, 3, 8), IterParSpace(KER_ITER_D2, 2, 1), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(5,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_34_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_34_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_34_in_2"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_34_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s213_kernel", LOC_D2,
                Bindings(8,
                    K_ArgPar("expr_34_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_ArgPar("expr_34_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D1),
                    K_ArgPar("expr_34_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D2),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_34_in_0", KER_ARG_TILE),
                    K_Arg("expr_34_in_1", KER_ARG_TILE),
                    K_Arg("expr_34_in_2", KER_ARG_TILE),
                    K_Arg("expr_34_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_34_in_0 axes: (0, 1, 2)
        // var: expr_34_out_0 axes: (0, 1, 2)
        // var: expr_34_in_1 axes: (1, 2)
        // var: expr_34_in_2 axes: (2,)
        KerArgs(5,
            KerArg("expr_34_in_0",    KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_34_in_0"),
            KerArg("expr_34_out_0",   KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_34_out_0"),
            KerArg("expr_34_in_1",    KerArgSpace(2, KER_ITER_D1, KER_ITER_D2),              O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_34_in_1"),
            KerArg("expr_34_in_2",    KerArgSpace(1, KER_ITER_D2),                           O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_34_in_2"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0),                        O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 3456, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 1992, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,       2);
        AddKernelArgDimExplicit(Name, "expr_34_in_0", ARG_INT,    4, 144, 3, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_34_in_1", ARG_INT,    3, 3, 2,      1);
        AddKernelArgDimExplicit(Name, "expr_34_in_2", ARG_INT,    2, 2,         1);
        AddKernelArgDimExplicit(Name, "expr_34_out_0", ARG_INT,   4, 144, 3, 2, 1);
    }
    return (Kernel!=0);
}
int s219_kernel_gen(char *Name) {
    Kernel_T *Kernel = UserKernel(
        Name,
        // shape: (1, 576, 3, 2) spaces: ((1,), (2,), (3,)) 
        // fixed_spaces: ((1,),) parametric_spaces: ((2,), (3,)) 
        // exterior_shape: (576, 3, 2.0) 
        KernelIterSpace(4, IterFixedSpace(KER_ITER_D0, 576), IterParSpace(KER_ITER_D1, 3, 8), IterParSpace(KER_ITER_D2, 2, 1), IterTiledSpace(KER_ITER_TILE0)),
        TILE_VER,
        CArgs(5,
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_35_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_35_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_35_in_2"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_35_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")
        ),
        Calls(1,
            Call("s219_kernel", LOC_D2,
                Bindings(8,
                    K_ArgPar("expr_35_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                    K_ArgPar("expr_35_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D1),
                    K_ArgPar("expr_35_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D2),
                    K_Arg("SigmoidLUTTable", KER_ARG_TILE),
                    K_Arg("expr_35_in_0", KER_ARG_TILE),
                    K_Arg("expr_35_in_1", KER_ARG_TILE),
                    K_Arg("expr_35_in_2", KER_ARG_TILE),
                    K_Arg("expr_35_out_0", KER_ARG_TILE)
                )
            )
        ),
        // var: expr_35_in_0 axes: (0, 1, 2)
        // var: expr_35_out_0 axes: (0, 1, 2)
        // var: expr_35_in_1 axes: (1, 2)
        // var: expr_35_in_2 axes: (2,)
        KerArgs(5,
            KerArg("expr_35_in_0",    KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_35_in_0"),
            KerArg("expr_35_out_0",   KerArgSpace(3, KER_ITER_D0, KER_ITER_D1, KER_ITER_D2), O_OUT|O_DB,                   1, 1, 1,   0, 0, 0, "expr_35_out_0"),
            KerArg("expr_35_in_1",    KerArgSpace(2, KER_ITER_D1, KER_ITER_D2),              O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_35_in_1"),
            KerArg("expr_35_in_2",    KerArgSpace(1, KER_ITER_D2),                           O_IN|O_DB,                    1, 1, 1,   0, 0, 0, "expr_35_in_2"),
            KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0),                        O_IN|O_BUFF|O_NTILED|O_CONST, 1, 1, 512, 0, 0, 0, "SigmoidLUTTable")
        )
    );
    if (Kernel) {
        AddKernelInfos(Name, AT_KERINFO_OPER, 13824, 0);
        AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 7176, 0);
        AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256,       2);
        AddKernelArgDimExplicit(Name, "expr_35_in_0", ARG_INT,    4, 576, 3, 2, 1);
        AddKernelArgDimExplicit(Name, "expr_35_in_1", ARG_INT,    3, 3, 2,      1);
        AddKernelArgDimExplicit(Name, "expr_35_in_2", ARG_INT,    2, 2,         1);
        AddKernelArgDimExplicit(Name, "expr_35_out_0", ARG_INT,   4, 576, 3, 2, 1);
    }
    return (Kernel!=0);
}

void YOLOv5Model(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory, unsigned int L3Flash)
{
    KernelOper_T Cop = KOP_CONV;

    // SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);
    SetSymbolDynamics();

    SetUsedFilesNames(0, 9, "at_api.h", "YOLOv5.h", "CNN_BasicKernels_SQ8.h", "CNN_BasicKernels.h", "CNN_BasicKernels_NE16.h", "ResizeBasicKernels.h", "CNN_BasicKernels_SQ8.h", "Expression_Kernels.h", "CNN_Copy.h");
    SetGeneratedFilesNames("YOLOv5Kernels.c", "YOLOv5Kernels.h");
    AT_SetGraphCtrl(AT_GRAPH_MONITOR_CYCLES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_NODE_NAMES, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_PRODUCE_OPERINFOS, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_ASYNC_FORK, AT_OPT_ON);

    SetMemoryDeviceInfos(4,
        AT_MEM_L1, L1Memory, "YOLOv5_L1_Memory", 0, 0,
        AT_MEM_L2, L2Memory, "YOLOv5_L2_Memory", 0, 1,
        AT_MEM_L3_DEFAULTRAM, L3Memory, "YOLOv5_L3_Memory", 0, 1,
        AT_MEM_L3_MRAMFLASH, L3Flash, "YOLOv5_L3_Flash", "YOLOv5_L3_Flash_Const.dat", 0
    );

    LoadCNN_SQ8_Library();
    LoadCNNLibrary();
    LoadCNN_NE16_SQ8_Library();
    LoadResizeLibrary();
    LoadCNN_Copy_Library();
    load_expressions_kernels();

    CNN_GenControl_T gen_ctrl_S3_CONV_2D_0_0_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S3_CONV_2D_0_0_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_0_fusion, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_0_fusion, "CUSTOM_ACTIVATION_NAME", "expr_33");
    CNN_ExtraActivationArgs_T gen_ctrl_S3_CONV_2D_0_0_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_0_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S3_CONV_2D_0_0_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_0_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_0_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_0_fusion
    CNN_ConvolutionNE16("S3_CONV_2D_0_0_fusion", &gen_ctrl_S3_CONV_2D_0_0_fusion,
                        -1, -1, 4, 1, 8,
                        3, 8, 192, 192,
                        KOP_CONV, 6, 6, 1, 1, 2, 2, 1, 0,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S6_CONV_2D_0_4_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S6_CONV_2D_0_4_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_4_fusion, "CUSTOM_ACTIVATION_NAME", "expr_45");
    CNN_ExtraActivationArgs_T gen_ctrl_S6_CONV_2D_0_4_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_4_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S6_CONV_2D_0_4_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_4_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_4_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_4_fusion
    CNN_ConvolutionNE16("S6_CONV_2D_0_4_fusion", &gen_ctrl_S6_CONV_2D_0_4_fusion,
                        -1, -1, 4, 1, 8,
                        8, 16, 96, 96,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 2,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S9_CONV_2D_0_7_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S9_CONV_2D_0_7_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_7_fusion, "CUSTOM_ACTIVATION_NAME", "expr_31");
    CNN_ExtraActivationArgs_T gen_ctrl_S9_CONV_2D_0_7_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_7_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S9_CONV_2D_0_7_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_7_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_7_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_7_fusion
    CNN_ConvolutionNE16("S9_CONV_2D_0_7_fusion", &gen_ctrl_S9_CONV_2D_0_7_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 48, 48,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 3,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S10_CONV_2D_0_7_split;
    CNN_InitGenCtrl(&gen_ctrl_S10_CONV_2D_0_7_split);
    CNN_SetGenCtrl(&gen_ctrl_S10_CONV_2D_0_7_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S10_CONV_2D_0_7_split", &gen_ctrl_S10_CONV_2D_0_7_split, -1, 2304, 2, KOP_SPLIT, 8,8);
    
    
    // generator for CONV_2D_0_7_split_copy_qout0
    CNN_Convert("S11_CONV_2D_0_7_split_copy_qout0", -1, -1, 18432, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S14_CONV_2D_0_10_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S14_CONV_2D_0_10_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_10_fusion, "CUSTOM_ACTIVATION_NAME", "expr_13");
    CNN_ExtraActivationArgs_T gen_ctrl_S14_CONV_2D_0_10_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_10_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S14_CONV_2D_0_10_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_10_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_10_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_10_fusion
    CNN_ConvolutionNE16("S14_CONV_2D_0_10_fusion", &gen_ctrl_S14_CONV_2D_0_10_fusion,
                        -1, -1, 4, 1, 8,
                        8, 8, 48, 48,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 11,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S17_CONV_2D_0_13;
    CNN_InitGenCtrl(&gen_ctrl_S17_CONV_2D_0_13);
    CNN_SetGenCtrl(&gen_ctrl_S17_CONV_2D_0_13, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S17_CONV_2D_0_13, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_13
    CNN_ConvolutionNE16("S17_CONV_2D_0_13", &gen_ctrl_S17_CONV_2D_0_13,
                        -1, -1, 4, 1, 8,
                        8, 8, 48, 48,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_0
    s18_kernel_gen("S18_expr_0");
    
    CNN_GenControl_T gen_ctrl_S19_CONCAT_0_20;
    CNN_InitGenCtrl(&gen_ctrl_S19_CONCAT_0_20);
    CNN_SetGenCtrl(&gen_ctrl_S19_CONCAT_0_20, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S19_CONCAT_0_20", &gen_ctrl_S19_CONCAT_0_20, -1, 2304, 2, KOP_CONCAT, 8,8);
    
    CNN_GenControl_T gen_ctrl_S22_CONV_2D_0_21_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S22_CONV_2D_0_21_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_21_fusion, "CUSTOM_ACTIVATION_NAME", "expr_36");
    CNN_ExtraActivationArgs_T gen_ctrl_S22_CONV_2D_0_21_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_21_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S22_CONV_2D_0_21_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_21_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_21_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_21_fusion
    CNN_ConvolutionNE16("S22_CONV_2D_0_21_fusion", &gen_ctrl_S22_CONV_2D_0_21_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 48, 48,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 21,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S25_CONV_2D_0_25_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S25_CONV_2D_0_25_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_25_fusion, "CUSTOM_ACTIVATION_NAME", "expr_37");
    CNN_ExtraActivationArgs_T gen_ctrl_S25_CONV_2D_0_25_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_25_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S25_CONV_2D_0_25_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_25_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_25_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_25_fusion
    CNN_ConvolutionNE16("S25_CONV_2D_0_25_fusion", &gen_ctrl_S25_CONV_2D_0_25_fusion,
                        -1, -1, 4, 1, 8,
                        16, 32, 48, 48,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 12,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S28_CONV_2D_0_28_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S28_CONV_2D_0_28_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_28_fusion, "CUSTOM_ACTIVATION_NAME", "expr_38");
    CNN_ExtraActivationArgs_T gen_ctrl_S28_CONV_2D_0_28_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_28_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S28_CONV_2D_0_28_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_28_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_28_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_28_fusion
    CNN_ConvolutionNE16("S28_CONV_2D_0_28_fusion", &gen_ctrl_S28_CONV_2D_0_28_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 24, 24,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 14,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S29_CONV_2D_0_28_split;
    CNN_InitGenCtrl(&gen_ctrl_S29_CONV_2D_0_28_split);
    CNN_SetGenCtrl(&gen_ctrl_S29_CONV_2D_0_28_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S29_CONV_2D_0_28_split", &gen_ctrl_S29_CONV_2D_0_28_split, -1, 576, 2, KOP_SPLIT, 16,16);
    
    
    // generator for CONV_2D_0_28_split_copy_qout0
    CNN_Convert("S30_CONV_2D_0_28_split_copy_qout0", -1, -1, 9216, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S33_CONV_2D_0_31_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S33_CONV_2D_0_31_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_31_fusion, "CUSTOM_ACTIVATION_NAME", "expr_39");
    CNN_ExtraActivationArgs_T gen_ctrl_S33_CONV_2D_0_31_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_31_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S33_CONV_2D_0_31_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_31_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_31_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_31_fusion
    CNN_ConvolutionNE16("S33_CONV_2D_0_31_fusion", &gen_ctrl_S33_CONV_2D_0_31_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 24, 24,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 11,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S36_CONV_2D_0_34;
    CNN_InitGenCtrl(&gen_ctrl_S36_CONV_2D_0_34);
    CNN_SetGenCtrl(&gen_ctrl_S36_CONV_2D_0_34, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S36_CONV_2D_0_34, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_34
    CNN_ConvolutionNE16("S36_CONV_2D_0_34", &gen_ctrl_S36_CONV_2D_0_34,
                        -1, -1, 4, 1, 8,
                        16, 16, 24, 24,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 15,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_4
    s37_kernel_gen("S37_expr_4");
    
    CNN_GenControl_T gen_ctrl_S38_CONCAT_0_41;
    CNN_InitGenCtrl(&gen_ctrl_S38_CONCAT_0_41);
    CNN_SetGenCtrl(&gen_ctrl_S38_CONCAT_0_41, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S38_CONCAT_0_41", &gen_ctrl_S38_CONCAT_0_41, -1, 576, 2, KOP_CONCAT, 16,16);
    
    CNN_GenControl_T gen_ctrl_S41_CONV_2D_0_42_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S41_CONV_2D_0_42_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_42_fusion, "CUSTOM_ACTIVATION_NAME", "expr_41");
    CNN_ExtraActivationArgs_T gen_ctrl_S41_CONV_2D_0_42_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_42_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S41_CONV_2D_0_42_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_42_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_42_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_42_fusion
    CNN_ConvolutionNE16("S41_CONV_2D_0_42_fusion", &gen_ctrl_S41_CONV_2D_0_42_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 24, 24,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 20,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_42_fusion_qout0
    CNN_Convert("S42_CONV_2D_0_42_fusion_qout0", -1, -1, 18432, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S45_CONV_2D_0_46_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S45_CONV_2D_0_46_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S45_CONV_2D_0_46_fusion, "CUSTOM_ACTIVATION_NAME", "expr_42");
    CNN_ExtraActivationArgs_T gen_ctrl_S45_CONV_2D_0_46_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S45_CONV_2D_0_46_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S45_CONV_2D_0_46_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S45_CONV_2D_0_46_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S45_CONV_2D_0_46_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_46_fusion
    CNN_ConvolutionNE16("S45_CONV_2D_0_46_fusion", &gen_ctrl_S45_CONV_2D_0_46_fusion,
                        -1, -1, 4, 1, 8,
                        32, 56, 24, 24,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 21,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S48_CONV_2D_0_49_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S48_CONV_2D_0_49_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S48_CONV_2D_0_49_fusion, "CUSTOM_ACTIVATION_NAME", "expr_43");
    CNN_ExtraActivationArgs_T gen_ctrl_S48_CONV_2D_0_49_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S48_CONV_2D_0_49_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S48_CONV_2D_0_49_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S48_CONV_2D_0_49_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S48_CONV_2D_0_49_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_49_fusion
    CNN_ConvolutionNE16("S48_CONV_2D_0_49_fusion", &gen_ctrl_S48_CONV_2D_0_49_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 22,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S49_CONV_2D_0_49_split;
    CNN_InitGenCtrl(&gen_ctrl_S49_CONV_2D_0_49_split);
    CNN_SetGenCtrl(&gen_ctrl_S49_CONV_2D_0_49_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S49_CONV_2D_0_49_split", &gen_ctrl_S49_CONV_2D_0_49_split, -1, 144, 2, KOP_SPLIT, 28,28);
    
    
    // generator for CONV_2D_0_49_split_copy_qout0
    CNN_Convert("S50_CONV_2D_0_49_split_copy_qout0", -1, -1, 4032, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S53_CONV_2D_0_52_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S53_CONV_2D_0_52_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S53_CONV_2D_0_52_fusion, "CUSTOM_ACTIVATION_NAME", "expr_44");
    CNN_ExtraActivationArgs_T gen_ctrl_S53_CONV_2D_0_52_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S53_CONV_2D_0_52_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S53_CONV_2D_0_52_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S53_CONV_2D_0_52_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S53_CONV_2D_0_52_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_52_fusion
    CNN_ConvolutionNE16("S53_CONV_2D_0_52_fusion", &gen_ctrl_S53_CONV_2D_0_52_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 24,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S56_CONV_2D_0_55;
    CNN_InitGenCtrl(&gen_ctrl_S56_CONV_2D_0_55);
    CNN_SetGenCtrl(&gen_ctrl_S56_CONV_2D_0_55, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S56_CONV_2D_0_55, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_55
    CNN_ConvolutionNE16("S56_CONV_2D_0_55", &gen_ctrl_S56_CONV_2D_0_55,
                        -1, -1, 4, 1, 8,
                        28, 28, 12, 12,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 27,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_5
    s57_kernel_gen("S57_expr_5");
    
    CNN_GenControl_T gen_ctrl_S58_CONCAT_0_62;
    CNN_InitGenCtrl(&gen_ctrl_S58_CONCAT_0_62);
    CNN_SetGenCtrl(&gen_ctrl_S58_CONCAT_0_62, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S58_CONCAT_0_62", &gen_ctrl_S58_CONCAT_0_62, -1, 144, 2, KOP_CONCAT, 28,28);
    
    CNN_GenControl_T gen_ctrl_S61_CONV_2D_0_63_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S61_CONV_2D_0_63_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S61_CONV_2D_0_63_fusion, "CUSTOM_ACTIVATION_NAME", "expr_47");
    CNN_ExtraActivationArgs_T gen_ctrl_S61_CONV_2D_0_63_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S61_CONV_2D_0_63_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S61_CONV_2D_0_63_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S61_CONV_2D_0_63_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S61_CONV_2D_0_63_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_63_fusion
    CNN_ConvolutionNE16("S61_CONV_2D_0_63_fusion", &gen_ctrl_S61_CONV_2D_0_63_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 42,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S64_CONV_2D_0_67_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S64_CONV_2D_0_67_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S64_CONV_2D_0_67_fusion, "CUSTOM_ACTIVATION_NAME", "expr_48");
    CNN_ExtraActivationArgs_T gen_ctrl_S64_CONV_2D_0_67_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S64_CONV_2D_0_67_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S64_CONV_2D_0_67_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S64_CONV_2D_0_67_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S64_CONV_2D_0_67_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_67_fusion
    CNN_ConvolutionNE16("S64_CONV_2D_0_67_fusion", &gen_ctrl_S64_CONV_2D_0_67_fusion,
                        -1, -1, 4, 1, 8,
                        56, 104, 12, 12,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 27,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S67_CONV_2D_0_70_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S67_CONV_2D_0_70_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S67_CONV_2D_0_70_fusion, "CUSTOM_ACTIVATION_NAME", "expr_49");
    CNN_ExtraActivationArgs_T gen_ctrl_S67_CONV_2D_0_70_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S67_CONV_2D_0_70_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S67_CONV_2D_0_70_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S67_CONV_2D_0_70_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S67_CONV_2D_0_70_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_70_fusion
    CNN_ConvolutionNE16("S67_CONV_2D_0_70_fusion", &gen_ctrl_S67_CONV_2D_0_70_fusion,
                        -1, -1, 4, 1, 8,
                        104, 104, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 29,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S68_CONV_2D_0_70_split;
    CNN_InitGenCtrl(&gen_ctrl_S68_CONV_2D_0_70_split);
    CNN_SetGenCtrl(&gen_ctrl_S68_CONV_2D_0_70_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S68_CONV_2D_0_70_split", &gen_ctrl_S68_CONV_2D_0_70_split, -1, 36, 2, KOP_SPLIT, 52,52);
    
    
    // generator for CONV_2D_0_70_split_copy_qout0
    CNN_Convert("S69_CONV_2D_0_70_split_copy_qout0", -1, -1, 1872, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S72_CONV_2D_0_73_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S72_CONV_2D_0_73_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S72_CONV_2D_0_73_fusion, "CUSTOM_ACTIVATION_NAME", "expr_50");
    CNN_ExtraActivationArgs_T gen_ctrl_S72_CONV_2D_0_73_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S72_CONV_2D_0_73_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S72_CONV_2D_0_73_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S72_CONV_2D_0_73_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S72_CONV_2D_0_73_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_73_fusion
    CNN_ConvolutionNE16("S72_CONV_2D_0_73_fusion", &gen_ctrl_S72_CONV_2D_0_73_fusion,
                        -1, -1, 4, 1, 8,
                        52, 52, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 29,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S75_CONV_2D_0_76;
    CNN_InitGenCtrl(&gen_ctrl_S75_CONV_2D_0_76);
    CNN_SetGenCtrl(&gen_ctrl_S75_CONV_2D_0_76, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S75_CONV_2D_0_76, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_76
    CNN_ConvolutionNE16("S75_CONV_2D_0_76", &gen_ctrl_S75_CONV_2D_0_76,
                        -1, -1, 4, 1, 8,
                        52, 52, 6, 6,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 25,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    
    // generator for expr_6
    s76_kernel_gen("S76_expr_6");
    
    CNN_GenControl_T gen_ctrl_S77_CONCAT_0_83;
    CNN_InitGenCtrl(&gen_ctrl_S77_CONCAT_0_83);
    CNN_SetGenCtrl(&gen_ctrl_S77_CONCAT_0_83, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S77_CONCAT_0_83", &gen_ctrl_S77_CONCAT_0_83, -1, 36, 2, KOP_CONCAT, 52,52);
    
    CNN_GenControl_T gen_ctrl_S80_CONV_2D_0_84_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S80_CONV_2D_0_84_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S80_CONV_2D_0_84_fusion, "CUSTOM_ACTIVATION_NAME", "expr_52");
    CNN_ExtraActivationArgs_T gen_ctrl_S80_CONV_2D_0_84_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S80_CONV_2D_0_84_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S80_CONV_2D_0_84_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S80_CONV_2D_0_84_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S80_CONV_2D_0_84_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_84_fusion
    CNN_ConvolutionNE16("S80_CONV_2D_0_84_fusion", &gen_ctrl_S80_CONV_2D_0_84_fusion,
                        -1, -1, 4, 1, 8,
                        104, 104, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 42,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S83_CONV_2D_0_87_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S83_CONV_2D_0_87_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S83_CONV_2D_0_87_fusion, "CUSTOM_ACTIVATION_NAME", "expr_53");
    CNN_ExtraActivationArgs_T gen_ctrl_S83_CONV_2D_0_87_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S83_CONV_2D_0_87_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S83_CONV_2D_0_87_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S83_CONV_2D_0_87_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S83_CONV_2D_0_87_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_87_fusion
    CNN_ConvolutionNE16("S83_CONV_2D_0_87_fusion", &gen_ctrl_S83_CONV_2D_0_87_fusion,
                        -1, -1, 4, 1, 8,
                        104, 52, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 26,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    
    // generator for CONV_2D_0_87_fusion_qout0
    CNN_Convert("S84_CONV_2D_0_87_fusion_qout0", -1, -1, 1872, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S85_MAX_POOL_2D_0_90;
    CNN_InitGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_90);
    CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_90, "HWC", AT_OPT_VAL(1));
    CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_90, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_90, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for MAX_POOL_2D_0_90
    CNN_PoolAct_SQ8("S85_MAX_POOL_2D_0_90", &gen_ctrl_S85_MAX_POOL_2D_0_90,
                    52, 6, 6,
                    KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                    KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S86_MAX_POOL_2D_0_91;
    CNN_InitGenCtrl(&gen_ctrl_S86_MAX_POOL_2D_0_91);
    CNN_SetGenCtrl(&gen_ctrl_S86_MAX_POOL_2D_0_91, "HWC", AT_OPT_VAL(1));
    CNN_SetGenCtrl(&gen_ctrl_S86_MAX_POOL_2D_0_91, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S86_MAX_POOL_2D_0_91, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for MAX_POOL_2D_0_91
    CNN_PoolAct_SQ8("S86_MAX_POOL_2D_0_91", &gen_ctrl_S86_MAX_POOL_2D_0_91,
                    52, 6, 6,
                    KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                    KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S87_MAX_POOL_2D_0_92;
    CNN_InitGenCtrl(&gen_ctrl_S87_MAX_POOL_2D_0_92);
    CNN_SetGenCtrl(&gen_ctrl_S87_MAX_POOL_2D_0_92, "HWC", AT_OPT_VAL(1));
    CNN_SetGenCtrl(&gen_ctrl_S87_MAX_POOL_2D_0_92, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S87_MAX_POOL_2D_0_92, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for MAX_POOL_2D_0_92
    CNN_PoolAct_SQ8("S87_MAX_POOL_2D_0_92", &gen_ctrl_S87_MAX_POOL_2D_0_92,
                    52, 6, 6,
                    KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                    KOP_NONE);
    
    
    // generator for MAX_POOL_2D_0_92_qout0
    CNN_Convert("S88_MAX_POOL_2D_0_92_qout0", -1, -1, 1872, KOP_CONVERT_FP_FP_SCALE);
    
    
    // generator for MAX_POOL_2D_0_91_qout0
    CNN_Convert("S89_MAX_POOL_2D_0_91_qout0", -1, -1, 1872, KOP_CONVERT_FP_FP_SCALE);
    
    
    // generator for MAX_POOL_2D_0_90_qout0
    CNN_Convert("S90_MAX_POOL_2D_0_90_qout0", -1, -1, 1872, KOP_CONVERT_FP_FP_SCALE);
    
    
    // generator for CONV_2D_0_87_fusion_qout0_0
    CNN_Convert("S91_CONV_2D_0_87_fusion_qout0_0", -1, -1, 1872, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S92_CONCAT_0_93;
    CNN_InitGenCtrl(&gen_ctrl_S92_CONCAT_0_93);
    CNN_SetGenCtrl(&gen_ctrl_S92_CONCAT_0_93, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S92_CONCAT_0_93", &gen_ctrl_S92_CONCAT_0_93, -1, 36, 4, KOP_CONCAT, 52,52,52,52);
    
    CNN_GenControl_T gen_ctrl_S95_CONV_2D_0_94_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S95_CONV_2D_0_94_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S95_CONV_2D_0_94_fusion, "CUSTOM_ACTIVATION_NAME", "expr_55");
    CNN_ExtraActivationArgs_T gen_ctrl_S95_CONV_2D_0_94_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S95_CONV_2D_0_94_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S95_CONV_2D_0_94_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S95_CONV_2D_0_94_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S95_CONV_2D_0_94_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_94_fusion
    CNN_ConvolutionNE16("S95_CONV_2D_0_94_fusion", &gen_ctrl_S95_CONV_2D_0_94_fusion,
                        -1, -1, 4, 1, 8,
                        208, 104, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 22,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S98_CONV_2D_0_97_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S98_CONV_2D_0_97_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S98_CONV_2D_0_97_fusion, "CUSTOM_ACTIVATION_NAME", "expr_56");
    CNN_ExtraActivationArgs_T gen_ctrl_S98_CONV_2D_0_97_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S98_CONV_2D_0_97_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S98_CONV_2D_0_97_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S98_CONV_2D_0_97_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S98_CONV_2D_0_97_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_97_fusion
    CNN_ConvolutionNE16("S98_CONV_2D_0_97_fusion", &gen_ctrl_S98_CONV_2D_0_97_fusion,
                        -1, -1, 4, 1, 8,
                        104, 56, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 20,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S99_RESIZE_NN_0_100;
    CNN_InitGenCtrl(&gen_ctrl_S99_RESIZE_NN_0_100);
    CNN_SetGenCtrl(&gen_ctrl_S99_RESIZE_NN_0_100, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    CNN_SetGenCtrl(&gen_ctrl_S99_RESIZE_NN_0_100, "HWC", AT_OPT_VAL(1));
    // generator for RESIZE_NN_0_100
    GenerateResizeMultiChannel("S99_RESIZE_NN_0_100", &gen_ctrl_S99_RESIZE_NN_0_100, 6, 6, 12, 12, 56, UNSIGNED_INOUT, KOP_NEAREST_NEIGHBOR_RESIZE);
    
    
    // generator for RESIZE_NN_0_100_qout0
    CNN_Convert("S100_RESIZE_NN_0_100_qout0", -1, -1, 8064, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S101_CONCAT_0_101;
    CNN_InitGenCtrl(&gen_ctrl_S101_CONCAT_0_101);
    CNN_SetGenCtrl(&gen_ctrl_S101_CONCAT_0_101, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S101_CONCAT_0_101", &gen_ctrl_S101_CONCAT_0_101, -1, 144, 2, KOP_CONCAT, 56,56);
    
    
    // generator for CONV_2D_0_97_fusion_qout0
    CNN_Convert("S102_CONV_2D_0_97_fusion_qout0", -1, -1, 2016, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S105_CONV_2D_0_102_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S105_CONV_2D_0_102_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S105_CONV_2D_0_102_fusion, "CUSTOM_ACTIVATION_NAME", "expr_10");
    CNN_ExtraActivationArgs_T gen_ctrl_S105_CONV_2D_0_102_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S105_CONV_2D_0_102_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S105_CONV_2D_0_102_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S105_CONV_2D_0_102_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S105_CONV_2D_0_102_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_102_fusion
    CNN_ConvolutionNE16("S105_CONV_2D_0_102_fusion", &gen_ctrl_S105_CONV_2D_0_102_fusion,
                        -1, -1, 4, 1, 8,
                        112, 56, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 27,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S106_CONV_2D_0_102_split;
    CNN_InitGenCtrl(&gen_ctrl_S106_CONV_2D_0_102_split);
    CNN_SetGenCtrl(&gen_ctrl_S106_CONV_2D_0_102_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S106_CONV_2D_0_102_split", &gen_ctrl_S106_CONV_2D_0_102_split, -1, 144, 2, KOP_SPLIT, 28,28);
    
    CNN_GenControl_T gen_ctrl_S109_CONV_2D_0_105_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S109_CONV_2D_0_105_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S109_CONV_2D_0_105_fusion, "CUSTOM_ACTIVATION_NAME", "expr_8");
    CNN_ExtraActivationArgs_T gen_ctrl_S109_CONV_2D_0_105_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S109_CONV_2D_0_105_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S109_CONV_2D_0_105_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S109_CONV_2D_0_105_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S109_CONV_2D_0_105_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_105_fusion
    CNN_ConvolutionNE16("S109_CONV_2D_0_105_fusion", &gen_ctrl_S109_CONV_2D_0_105_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 27,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S112_CONV_2D_0_108_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S112_CONV_2D_0_108_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S112_CONV_2D_0_108_fusion, "CUSTOM_ACTIVATION_NAME", "expr_9");
    CNN_ExtraActivationArgs_T gen_ctrl_S112_CONV_2D_0_108_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S112_CONV_2D_0_108_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S112_CONV_2D_0_108_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S112_CONV_2D_0_108_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S112_CONV_2D_0_108_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_108_fusion
    CNN_ConvolutionNE16("S112_CONV_2D_0_108_fusion", &gen_ctrl_S112_CONV_2D_0_108_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 12, 12,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 25,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S113_CONCAT_0_114;
    CNN_InitGenCtrl(&gen_ctrl_S113_CONCAT_0_114);
    CNN_SetGenCtrl(&gen_ctrl_S113_CONCAT_0_114, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S113_CONCAT_0_114", &gen_ctrl_S113_CONCAT_0_114, -1, 144, 2, KOP_CONCAT, 28,28);
    
    CNN_GenControl_T gen_ctrl_S116_CONV_2D_0_115_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S116_CONV_2D_0_115_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S116_CONV_2D_0_115_fusion, "CUSTOM_ACTIVATION_NAME", "expr_11");
    CNN_ExtraActivationArgs_T gen_ctrl_S116_CONV_2D_0_115_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S116_CONV_2D_0_115_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S116_CONV_2D_0_115_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S116_CONV_2D_0_115_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S116_CONV_2D_0_115_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_115_fusion
    CNN_ConvolutionNE16("S116_CONV_2D_0_115_fusion", &gen_ctrl_S116_CONV_2D_0_115_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 27,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S119_CONV_2D_0_118_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S119_CONV_2D_0_118_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S119_CONV_2D_0_118_fusion, "CUSTOM_ACTIVATION_NAME", "expr_12");
    CNN_ExtraActivationArgs_T gen_ctrl_S119_CONV_2D_0_118_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S119_CONV_2D_0_118_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S119_CONV_2D_0_118_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S119_CONV_2D_0_118_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S119_CONV_2D_0_118_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_118_fusion
    CNN_ConvolutionNE16("S119_CONV_2D_0_118_fusion", &gen_ctrl_S119_CONV_2D_0_118_fusion,
                        -1, -1, 4, 1, 8,
                        56, 32, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 24,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S120_RESIZE_NN_0_121;
    CNN_InitGenCtrl(&gen_ctrl_S120_RESIZE_NN_0_121);
    CNN_SetGenCtrl(&gen_ctrl_S120_RESIZE_NN_0_121, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    CNN_SetGenCtrl(&gen_ctrl_S120_RESIZE_NN_0_121, "HWC", AT_OPT_VAL(1));
    // generator for RESIZE_NN_0_121
    GenerateResizeMultiChannel("S120_RESIZE_NN_0_121", &gen_ctrl_S120_RESIZE_NN_0_121, 12, 12, 24, 24, 32, UNSIGNED_INOUT, KOP_NEAREST_NEIGHBOR_RESIZE);
    
    
    // generator for RESIZE_NN_0_121_qout0
    CNN_Convert("S121_RESIZE_NN_0_121_qout0", -1, -1, 18432, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S122_CONCAT_0_122;
    CNN_InitGenCtrl(&gen_ctrl_S122_CONCAT_0_122);
    CNN_SetGenCtrl(&gen_ctrl_S122_CONCAT_0_122, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S122_CONCAT_0_122", &gen_ctrl_S122_CONCAT_0_122, -1, 576, 2, KOP_CONCAT, 32,32);
    
    
    // generator for CONV_2D_0_118_fusion_qout0
    CNN_Convert("S123_CONV_2D_0_118_fusion_qout0", -1, -1, 4608, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S126_CONV_2D_0_123_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S126_CONV_2D_0_123_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S126_CONV_2D_0_123_fusion, "CUSTOM_ACTIVATION_NAME", "expr_14");
    CNN_ExtraActivationArgs_T gen_ctrl_S126_CONV_2D_0_123_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S126_CONV_2D_0_123_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S126_CONV_2D_0_123_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S126_CONV_2D_0_123_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S126_CONV_2D_0_123_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_123_fusion
    CNN_ConvolutionNE16("S126_CONV_2D_0_123_fusion", &gen_ctrl_S126_CONV_2D_0_123_fusion,
                        -1, -1, 4, 1, 8,
                        64, 32, 24, 24,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 22,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S127_CONV_2D_0_123_split;
    CNN_InitGenCtrl(&gen_ctrl_S127_CONV_2D_0_123_split);
    CNN_SetGenCtrl(&gen_ctrl_S127_CONV_2D_0_123_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S127_CONV_2D_0_123_split", &gen_ctrl_S127_CONV_2D_0_123_split, -1, 576, 2, KOP_SPLIT, 16,16);
    
    CNN_GenControl_T gen_ctrl_S130_CONV_2D_0_126_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S130_CONV_2D_0_126_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S130_CONV_2D_0_126_fusion, "CUSTOM_ACTIVATION_NAME", "expr_15");
    CNN_ExtraActivationArgs_T gen_ctrl_S130_CONV_2D_0_126_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S130_CONV_2D_0_126_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S130_CONV_2D_0_126_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S130_CONV_2D_0_126_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S130_CONV_2D_0_126_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_126_fusion
    CNN_ConvolutionNE16("S130_CONV_2D_0_126_fusion", &gen_ctrl_S130_CONV_2D_0_126_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 24, 24,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 31,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S133_CONV_2D_0_129_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S133_CONV_2D_0_129_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S133_CONV_2D_0_129_fusion, "CUSTOM_ACTIVATION_NAME", "expr_16");
    CNN_ExtraActivationArgs_T gen_ctrl_S133_CONV_2D_0_129_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S133_CONV_2D_0_129_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S133_CONV_2D_0_129_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S133_CONV_2D_0_129_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S133_CONV_2D_0_129_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_129_fusion
    CNN_ConvolutionNE16("S133_CONV_2D_0_129_fusion", &gen_ctrl_S133_CONV_2D_0_129_fusion,
                        -1, -1, 4, 1, 8,
                        16, 16, 24, 24,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 33,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S134_CONCAT_0_135;
    CNN_InitGenCtrl(&gen_ctrl_S134_CONCAT_0_135);
    CNN_SetGenCtrl(&gen_ctrl_S134_CONCAT_0_135, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S134_CONCAT_0_135", &gen_ctrl_S134_CONCAT_0_135, -1, 576, 2, KOP_CONCAT, 16,16);
    
    CNN_GenControl_T gen_ctrl_S137_CONV_2D_0_136_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S137_CONV_2D_0_136_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S137_CONV_2D_0_136_fusion, "CUSTOM_ACTIVATION_NAME", "expr_18");
    CNN_ExtraActivationArgs_T gen_ctrl_S137_CONV_2D_0_136_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S137_CONV_2D_0_136_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S137_CONV_2D_0_136_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S137_CONV_2D_0_136_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S137_CONV_2D_0_136_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_136_fusion
    CNN_ConvolutionNE16("S137_CONV_2D_0_136_fusion", &gen_ctrl_S137_CONV_2D_0_136_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 24, 24,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 31,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S140_CONV_2D_0_140_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S140_CONV_2D_0_140_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S140_CONV_2D_0_140_fusion, "CUSTOM_ACTIVATION_NAME", "expr_19");
    CNN_ExtraActivationArgs_T gen_ctrl_S140_CONV_2D_0_140_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S140_CONV_2D_0_140_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S140_CONV_2D_0_140_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S140_CONV_2D_0_140_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S140_CONV_2D_0_140_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_140_fusion
    CNN_ConvolutionNE16("S140_CONV_2D_0_140_fusion", &gen_ctrl_S140_CONV_2D_0_140_fusion,
                        -1, -1, 4, 1, 8,
                        32, 32, 24, 24,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 19,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S141_CONCAT_0_143;
    CNN_InitGenCtrl(&gen_ctrl_S141_CONCAT_0_143);
    CNN_SetGenCtrl(&gen_ctrl_S141_CONCAT_0_143, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S141_CONCAT_0_143", &gen_ctrl_S141_CONCAT_0_143, -1, 144, 2, KOP_CONCAT, 32,32);
    
    CNN_GenControl_T gen_ctrl_S144_CONV_2D_0_144_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S144_CONV_2D_0_144_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S144_CONV_2D_0_144_fusion, "CUSTOM_ACTIVATION_NAME", "expr_20");
    CNN_ExtraActivationArgs_T gen_ctrl_S144_CONV_2D_0_144_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S144_CONV_2D_0_144_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S144_CONV_2D_0_144_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S144_CONV_2D_0_144_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S144_CONV_2D_0_144_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_144_fusion
    CNN_ConvolutionNE16("S144_CONV_2D_0_144_fusion", &gen_ctrl_S144_CONV_2D_0_144_fusion,
                        -1, -1, 4, 1, 8,
                        64, 56, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 25,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S145_CONV_2D_0_144_split;
    CNN_InitGenCtrl(&gen_ctrl_S145_CONV_2D_0_144_split);
    CNN_SetGenCtrl(&gen_ctrl_S145_CONV_2D_0_144_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S145_CONV_2D_0_144_split", &gen_ctrl_S145_CONV_2D_0_144_split, -1, 144, 2, KOP_SPLIT, 28,28);
    
    
    // generator for CONV_2D_0_144_split_copy_qout0
    CNN_Convert("S146_CONV_2D_0_144_split_copy_qout0", -1, -1, 4032, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S149_CONV_2D_0_147_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S149_CONV_2D_0_147_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S149_CONV_2D_0_147_fusion, "CUSTOM_ACTIVATION_NAME", "expr_21");
    CNN_ExtraActivationArgs_T gen_ctrl_S149_CONV_2D_0_147_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S149_CONV_2D_0_147_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S149_CONV_2D_0_147_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S149_CONV_2D_0_147_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S149_CONV_2D_0_147_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_147_fusion
    CNN_ConvolutionNE16("S149_CONV_2D_0_147_fusion", &gen_ctrl_S149_CONV_2D_0_147_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 31,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S152_CONV_2D_0_150_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S152_CONV_2D_0_150_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S152_CONV_2D_0_150_fusion, "CUSTOM_ACTIVATION_NAME", "expr_22");
    CNN_ExtraActivationArgs_T gen_ctrl_S152_CONV_2D_0_150_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S152_CONV_2D_0_150_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S152_CONV_2D_0_150_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S152_CONV_2D_0_150_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S152_CONV_2D_0_150_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_150_fusion
    CNN_ConvolutionNE16("S152_CONV_2D_0_150_fusion", &gen_ctrl_S152_CONV_2D_0_150_fusion,
                        -1, -1, 4, 1, 8,
                        28, 28, 12, 12,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 33,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S153_CONCAT_0_156;
    CNN_InitGenCtrl(&gen_ctrl_S153_CONCAT_0_156);
    CNN_SetGenCtrl(&gen_ctrl_S153_CONCAT_0_156, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S153_CONCAT_0_156", &gen_ctrl_S153_CONCAT_0_156, -1, 144, 2, KOP_CONCAT, 28,28);
    
    CNN_GenControl_T gen_ctrl_S156_CONV_2D_0_157_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S156_CONV_2D_0_157_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S156_CONV_2D_0_157_fusion, "CUSTOM_ACTIVATION_NAME", "expr_24");
    CNN_ExtraActivationArgs_T gen_ctrl_S156_CONV_2D_0_157_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S156_CONV_2D_0_157_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S156_CONV_2D_0_157_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S156_CONV_2D_0_157_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S156_CONV_2D_0_157_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_157_fusion
    CNN_ConvolutionNE16("S156_CONV_2D_0_157_fusion", &gen_ctrl_S156_CONV_2D_0_157_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 31,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S159_CONV_2D_0_161_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S159_CONV_2D_0_161_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S159_CONV_2D_0_161_fusion, "CUSTOM_ACTIVATION_NAME", "expr_25");
    CNN_ExtraActivationArgs_T gen_ctrl_S159_CONV_2D_0_161_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S159_CONV_2D_0_161_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S159_CONV_2D_0_161_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S159_CONV_2D_0_161_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S159_CONV_2D_0_161_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_161_fusion
    CNN_ConvolutionNE16("S159_CONV_2D_0_161_fusion", &gen_ctrl_S159_CONV_2D_0_161_fusion,
                        -1, -1, 4, 1, 8,
                        56, 56, 12, 12,
                        KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 22,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S160_CONCAT_0_164;
    CNN_InitGenCtrl(&gen_ctrl_S160_CONCAT_0_164);
    CNN_SetGenCtrl(&gen_ctrl_S160_CONCAT_0_164, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S160_CONCAT_0_164", &gen_ctrl_S160_CONCAT_0_164, -1, 36, 2, KOP_CONCAT, 56,56);
    
    CNN_GenControl_T gen_ctrl_S163_CONV_2D_0_165_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S163_CONV_2D_0_165_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S163_CONV_2D_0_165_fusion, "CUSTOM_ACTIVATION_NAME", "expr_26");
    CNN_ExtraActivationArgs_T gen_ctrl_S163_CONV_2D_0_165_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S163_CONV_2D_0_165_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S163_CONV_2D_0_165_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S163_CONV_2D_0_165_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S163_CONV_2D_0_165_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_165_fusion
    CNN_ConvolutionNE16("S163_CONV_2D_0_165_fusion", &gen_ctrl_S163_CONV_2D_0_165_fusion,
                        -1, -1, 4, 1, 8,
                        112, 104, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 32,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S164_CONV_2D_0_165_split;
    CNN_InitGenCtrl(&gen_ctrl_S164_CONV_2D_0_165_split);
    CNN_SetGenCtrl(&gen_ctrl_S164_CONV_2D_0_165_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S164_CONV_2D_0_165_split", &gen_ctrl_S164_CONV_2D_0_165_split, -1, 36, 2, KOP_SPLIT, 52,52);
    
    CNN_GenControl_T gen_ctrl_S167_CONV_2D_0_168_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S167_CONV_2D_0_168_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S167_CONV_2D_0_168_fusion, "CUSTOM_ACTIVATION_NAME", "expr_27");
    CNN_ExtraActivationArgs_T gen_ctrl_S167_CONV_2D_0_168_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S167_CONV_2D_0_168_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S167_CONV_2D_0_168_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S167_CONV_2D_0_168_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S167_CONV_2D_0_168_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_168_fusion
    CNN_ConvolutionNE16("S167_CONV_2D_0_168_fusion", &gen_ctrl_S167_CONV_2D_0_168_fusion,
                        -1, -1, 4, 1, 8,
                        52, 52, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 39,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S170_CONV_2D_0_171_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S170_CONV_2D_0_171_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S170_CONV_2D_0_171_fusion, "CUSTOM_ACTIVATION_NAME", "expr_28");
    CNN_ExtraActivationArgs_T gen_ctrl_S170_CONV_2D_0_171_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S170_CONV_2D_0_171_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S170_CONV_2D_0_171_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S170_CONV_2D_0_171_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S170_CONV_2D_0_171_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_171_fusion
    CNN_ConvolutionNE16("S170_CONV_2D_0_171_fusion", &gen_ctrl_S170_CONV_2D_0_171_fusion,
                        -1, -1, 4, 1, 8,
                        52, 52, 6, 6,
                        KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 34,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S171_CONCAT_0_177;
    CNN_InitGenCtrl(&gen_ctrl_S171_CONCAT_0_177);
    CNN_SetGenCtrl(&gen_ctrl_S171_CONCAT_0_177, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S171_CONCAT_0_177", &gen_ctrl_S171_CONCAT_0_177, -1, 36, 2, KOP_CONCAT, 52,52);
    
    CNN_GenControl_T gen_ctrl_S174_CONV_2D_0_178_fusion;
    CNN_InitGenCtrl(&gen_ctrl_S174_CONV_2D_0_178_fusion);
    CNN_SetGenCtrl(&gen_ctrl_S174_CONV_2D_0_178_fusion, "CUSTOM_ACTIVATION_NAME", "expr_30");
    CNN_ExtraActivationArgs_T gen_ctrl_S174_CONV_2D_0_178_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
    CNN_SetGenCtrl(&gen_ctrl_S174_CONV_2D_0_178_fusion, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S174_CONV_2D_0_178_fusion_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S174_CONV_2D_0_178_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S174_CONV_2D_0_178_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_178_fusion
    CNN_ConvolutionNE16("S174_CONV_2D_0_178_fusion", &gen_ctrl_S174_CONV_2D_0_178_fusion,
                        -1, -1, 4, 1, 8,
                        104, 104, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 39,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_CUSTOM);
    
    CNN_GenControl_T gen_ctrl_S177_CONV_2D_0_181;
    CNN_InitGenCtrl(&gen_ctrl_S177_CONV_2D_0_181);
    CNN_SetGenCtrl(&gen_ctrl_S177_CONV_2D_0_181, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S177_CONV_2D_0_181, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_181
    CNN_ConvolutionNE16("S177_CONV_2D_0_181", &gen_ctrl_S177_CONV_2D_0_181,
                        -1, -1, 4, 1, 8,
                        104, 18, 6, 6,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 31,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S179_STRIDED_SLICE_0_183_split;
    CNN_InitGenCtrl(&gen_ctrl_S179_STRIDED_SLICE_0_183_split);
    CNN_SetGenCtrl(&gen_ctrl_S179_STRIDED_SLICE_0_183_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S179_STRIDED_SLICE_0_183_split", &gen_ctrl_S179_STRIDED_SLICE_0_183_split, -1, 108, 3, KOP_SPLIT, 2,2,2);
    
    CNN_GenControl_T gen_ctrl_S180_LOGISTIC_0_195;
    CNN_InitGenCtrl(&gen_ctrl_S180_LOGISTIC_0_195);
    CNN_ExtraActivationArgs_T gen_ctrl_S180_LOGISTIC_0_195_extra_activation_args = {1, {{"SigmoidLUT_u8", 128, -1}}};
    CNN_SetGenCtrl(&gen_ctrl_S180_LOGISTIC_0_195, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S180_LOGISTIC_0_195_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S180_LOGISTIC_0_195, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S180_LOGISTIC_0_195, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for LOGISTIC_0_195
    CNN_PoolAct_SQ8("S180_LOGISTIC_0_195", &gen_ctrl_S180_LOGISTIC_0_195,
                    36, 2, 3,
                    KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                    KOP_SIGMOID);
    
    
    // generator for expr_1
    s184_kernel_gen("S184_expr_1");
    
    CNN_GenControl_T gen_ctrl_S188_CONV_2D_0_198;
    CNN_InitGenCtrl(&gen_ctrl_S188_CONV_2D_0_198);
    CNN_SetGenCtrl(&gen_ctrl_S188_CONV_2D_0_198, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S188_CONV_2D_0_198, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_198
    CNN_ConvolutionNE16("S188_CONV_2D_0_198", &gen_ctrl_S188_CONV_2D_0_198,
                        -1, -1, 4, 1, 8,
                        56, 18, 12, 12,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 22,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S190_STRIDED_SLICE_0_200_split;
    CNN_InitGenCtrl(&gen_ctrl_S190_STRIDED_SLICE_0_200_split);
    CNN_SetGenCtrl(&gen_ctrl_S190_STRIDED_SLICE_0_200_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S190_STRIDED_SLICE_0_200_split", &gen_ctrl_S190_STRIDED_SLICE_0_200_split, -1, 432, 3, KOP_SPLIT, 2,2,2);
    
    CNN_GenControl_T gen_ctrl_S191_LOGISTIC_0_212;
    CNN_InitGenCtrl(&gen_ctrl_S191_LOGISTIC_0_212);
    CNN_ExtraActivationArgs_T gen_ctrl_S191_LOGISTIC_0_212_extra_activation_args = {1, {{"SigmoidLUT_u8", 128, -1}}};
    CNN_SetGenCtrl(&gen_ctrl_S191_LOGISTIC_0_212, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S191_LOGISTIC_0_212_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S191_LOGISTIC_0_212, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S191_LOGISTIC_0_212, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for LOGISTIC_0_212
    CNN_PoolAct_SQ8("S191_LOGISTIC_0_212", &gen_ctrl_S191_LOGISTIC_0_212,
                    144, 2, 3,
                    KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                    KOP_SIGMOID);
    
    
    // generator for CONCAT_0_213_reshape_2_qout0
    CNN_Convert("S193_CONCAT_0_213_reshape_2_qout0", -1, -1, 864, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S198_CONV_2D_0_215;
    CNN_InitGenCtrl(&gen_ctrl_S198_CONV_2D_0_215);
    CNN_SetGenCtrl(&gen_ctrl_S198_CONV_2D_0_215, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S198_CONV_2D_0_215, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for CONV_2D_0_215
    CNN_ConvolutionNE16("S198_CONV_2D_0_215", &gen_ctrl_S198_CONV_2D_0_215,
                        -1, -1, 4, 1, 8,
                        32, 18, 24, 24,
                        KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 19,
                        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                        KOP_NONE);
    
    CNN_GenControl_T gen_ctrl_S200_STRIDED_SLICE_0_217_split;
    CNN_InitGenCtrl(&gen_ctrl_S200_STRIDED_SLICE_0_217_split);
    CNN_SetGenCtrl(&gen_ctrl_S200_STRIDED_SLICE_0_217_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_SplitLastAxis_Generator2("S200_STRIDED_SLICE_0_217_split", &gen_ctrl_S200_STRIDED_SLICE_0_217_split, -1, 1728, 3, KOP_SPLIT, 2,2,2);
    
    CNN_GenControl_T gen_ctrl_S201_LOGISTIC_0_229;
    CNN_InitGenCtrl(&gen_ctrl_S201_LOGISTIC_0_229);
    CNN_ExtraActivationArgs_T gen_ctrl_S201_LOGISTIC_0_229_extra_activation_args = {1, {{"SigmoidLUT_u8", 128, -1}}};
    CNN_SetGenCtrl(&gen_ctrl_S201_LOGISTIC_0_229, "EXTRA_ACTIVATION_ARGS", &gen_ctrl_S201_LOGISTIC_0_229_extra_activation_args);
    CNN_SetGenCtrl(&gen_ctrl_S201_LOGISTIC_0_229, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
    CNN_SetGenCtrl(&gen_ctrl_S201_LOGISTIC_0_229, "INPUT_DATASIZE", AT_OPT_VAL(-1));
    // generator for LOGISTIC_0_229
    CNN_PoolAct_SQ8("S201_LOGISTIC_0_229", &gen_ctrl_S201_LOGISTIC_0_229,
                    576, 2, 3,
                    KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                    KOP_SIGMOID);
    
    
    // generator for expr_32
    s206_kernel_gen("S206_expr_32");
    
    CNN_GenControl_T gen_ctrl_S207_CONCAT_0_196;
    CNN_InitGenCtrl(&gen_ctrl_S207_CONCAT_0_196);
    CNN_SetGenCtrl(&gen_ctrl_S207_CONCAT_0_196, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S207_CONCAT_0_196", &gen_ctrl_S207_CONCAT_0_196, -1, 108, 3, KOP_CONCAT, 2,2,2);
    
    
    // generator for RESHAPE_0_197_qout0
    CNN_Convert("S209_RESHAPE_0_197_qout0", -1, -1, 648, KOP_CONVERT_FP_FP_SCALE);
    
    
    // generator for expr_2
    s211_kernel_gen("S211_expr_2");
    
    
    // generator for expr_34
    s213_kernel_gen("S213_expr_34");
    
    CNN_GenControl_T gen_ctrl_S214_CONCAT_0_213;
    CNN_InitGenCtrl(&gen_ctrl_S214_CONCAT_0_213);
    CNN_SetGenCtrl(&gen_ctrl_S214_CONCAT_0_213, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S214_CONCAT_0_213", &gen_ctrl_S214_CONCAT_0_213, -1, 432, 3, KOP_CONCAT, 2,2,2);
    
    
    // generator for expr_3
    s217_kernel_gen("S217_expr_3");
    
    
    // generator for expr_35
    s219_kernel_gen("S219_expr_35");
    
    CNN_GenControl_T gen_ctrl_S220_CONCAT_0_230;
    CNN_InitGenCtrl(&gen_ctrl_S220_CONCAT_0_230);
    CNN_SetGenCtrl(&gen_ctrl_S220_CONCAT_0_230, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    CNN_ConcatLastAxis_Generator2("S220_CONCAT_0_230", &gen_ctrl_S220_CONCAT_0_230, -1, 1728, 3, KOP_CONCAT, 2,2,2);
    
    
    // generator for RESHAPE_0_231_qout0
    CNN_Convert("S222_RESHAPE_0_231_qout0", -1, -1, 10368, KOP_CONVERT_FP_FP_SCALE);
    
    CNN_GenControl_T gen_ctrl_S225_CONCAT_0_232_reshape_copy;
    CNN_InitGenCtrl(&gen_ctrl_S225_CONCAT_0_232_reshape_copy);
    CNN_SetGenCtrl(&gen_ctrl_S225_CONCAT_0_232_reshape_copy, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
    
    // generator for CONCAT_0_232_reshape_copy
    CNN_Copy("S225_CONCAT_0_232_reshape_copy", &gen_ctrl_S225_CONCAT_0_232_reshape_copy, 13608, -1);
    

#define GRAPH
#ifdef GRAPH
    CreateGraph("YOLOv5CNN",
        /* Arguments either passed or globals */
            CArgs(270,
                TCArgInfo("unsigned char * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant21", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfoExpKerSize("Arith_constant21.tensor", 1, 1, 8, 0, 864)),
                TCArgInfo("signed int * __restrict__", "Arith_constant", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S3_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S3_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S3_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S3_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.26570 out: 0.11511  BIASN: 0 PRENORM: 0 NE16_PADVAL: [0] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S3_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S3_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst38", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst38.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant86", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant86.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S6_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S6_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S6_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S6_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.15076 out: 0.08054  BIASN: 0 PRENORM: 0 NE16_PADVAL: [2] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S6_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S6_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant22", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant22.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant85", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant85.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S9_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S9_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S9_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S9_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.08923 out: 0.02612  BIASN: 0 PRENORM: 0 NE16_PADVAL: [3] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S9_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S9_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.29<(u8-11.00)*0.02612432<6.37 out_q: -0.57<(u8-21.00)*0.02720781<6.37
                TCArgInfo("signed char * __restrict__", "S11_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S11_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant23", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant23.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant84", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant84.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S14_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S14_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04660 out: 0.02331  BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S14_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant24", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant24.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant83", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant83.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S17_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S17_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S17_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant26", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant26.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant81", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant81.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S22_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S22_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04725 out: 0.02377  BIASN: 0 PRENORM: 0 NE16_PADVAL: [21] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S22_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst37", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst37.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant80", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant80.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S25_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S25_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04134 out: 0.02023  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S25_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant27", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant27.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant79", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant79.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S28_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S28_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.04514 out: 0.02641  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S28_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.29<(u8-11.00)*0.02641341<6.44 out_q: -0.55<(u8-20.00)*0.02742977<6.45
                TCArgInfo("signed char * __restrict__", "S30_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S30_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant28", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant28.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant78", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant78.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S33_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S33_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03146 out: 0.01898  BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S33_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst36", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst36.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant77", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant77.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S36_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S36_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [15] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S36_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst35", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst35.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant75", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant75.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S41_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S41_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.03103 out: 0.01299  BIASN: 0 PRENORM: 0 NE16_PADVAL: [20] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S41_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.27<(u8-21.00)*0.01299385<3.04 out_q: -0.29<(u8-22.00)*0.01303558<3.04
                TCArgInfo("signed char * __restrict__", "S42_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S42_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst34", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst34.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant74", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant74.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S45_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S45_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S45_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S45_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02812 out: 0.01274  BIASN: 0 PRENORM: 0 NE16_PADVAL: [21] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S45_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S45_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst33", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst33.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant73", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant73.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S48_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S48_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S48_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S48_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02370 out: 0.01175  BIASN: 0 PRENORM: 0 NE16_PADVAL: [22] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S48_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S48_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-24.00)*0.01174527<2.71 out_q: -0.56<(u8-42.00)*0.01323155<2.82
                TCArgInfo("signed char * __restrict__", "S50_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S50_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant30", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant30.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant72", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant72.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S53_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S53_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S53_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S53_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02330 out: 0.01043  BIASN: 0 PRENORM: 0 NE16_PADVAL: [24] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S53_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S53_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst32", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst32.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant71", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant71.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S56_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S56_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S56_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S56_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [27] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S56_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S56_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst30", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst30.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant69", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant69.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S61_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S61_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S61_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S61_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02050 out: 0.01037  BIASN: 0 PRENORM: 0 NE16_PADVAL: [42] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S61_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S61_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst29", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst29.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant68", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant68.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S64_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S64_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S64_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S64_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02017 out: 0.00970  BIASN: 0 PRENORM: 0 NE16_PADVAL: [27] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S64_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S64_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst28", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst28.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant67", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant67.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S67_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S67_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S67_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S67_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01681 out: 0.00947  BIASN: 0 PRENORM: 0 NE16_PADVAL: [29] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S67_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S67_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.27<(u8-29.00)*0.00947452<2.14 out_q: -0.56<(u8-42.00)*0.01324933<2.82
                TCArgInfo("signed char * __restrict__", "S69_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S69_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst27", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst27.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant66", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant66.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S72_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S72_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S72_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S72_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02006 out: 0.01131  BIASN: 0 PRENORM: 0 NE16_PADVAL: [29] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S72_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S72_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst26", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst26.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant65", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant65.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S75_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S75_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S75_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S75_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [25] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S75_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S75_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst24", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst24.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant63", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant63.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S80_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S80_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S80_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S80_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02027 out: 0.01062  BIASN: 0 PRENORM: 0 NE16_PADVAL: [42] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S80_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S80_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst23", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst23.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant62", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant62.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S83_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S83_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S83_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S83_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02087 out: 0.01280  BIASN: 0 PRENORM: 0 NE16_PADVAL: [26] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S83_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S83_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-22.00)*0.01279965<2.98 out_q: 0.00<(u8-0.00)*0.01170763<2.99 forced
                TCArgInfo("signed char * __restrict__", "S84_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S84_Infos.tensor", 1, 1, 8, 0)),
                // no activation ACTSCALE: [1] ACTSCALEN: [0]
                TCArgInfo("signed char * __restrict__", "S85_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S85_Infos.tensor", 1, 1, 8, 0)),
                // no activation ACTSCALE: [1] ACTSCALEN: [0]
                TCArgInfo("signed char * __restrict__", "S86_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S86_Infos.tensor", 1, 1, 8, 0)),
                // no activation ACTSCALE: [1] ACTSCALEN: [0]
                TCArgInfo("signed char * __restrict__", "S87_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S87_Infos.tensor", 1, 1, 8, 0)),
                // in q: 0.00<(u8-0.00)*0.01170763<2.99 forced out_q: -0.28<(u8-22.00)*0.01281192<2.99
                TCArgInfo("signed char * __restrict__", "S88_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S88_Infos.tensor", 1, 1, 8, 0)),
                // in q: 0.00<(u8-0.00)*0.01170763<2.99 forced out_q: -0.28<(u8-22.00)*0.01281192<2.99
                TCArgInfo("signed char * __restrict__", "S89_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S89_Infos.tensor", 1, 1, 8, 0)),
                // in q: 0.00<(u8-0.00)*0.01170763<2.99 forced out_q: -0.28<(u8-22.00)*0.01281192<2.99
                TCArgInfo("signed char * __restrict__", "S90_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S90_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-22.00)*0.01279965<2.98 out_q: -0.28<(u8-22.00)*0.01281192<2.99
                TCArgInfo("signed char * __restrict__", "S91_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S91_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst22", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst22.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant61", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant61.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S95_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S95_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S95_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S95_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02652 out: 0.01411  BIASN: 0 PRENORM: 0 NE16_PADVAL: [22] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S95_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S95_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst21", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst21.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant60", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant60.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S98_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S98_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S98_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S98_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01449 out: 0.00809  BIASN: 0 PRENORM: 0 NE16_PADVAL: [20] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S98_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S98_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.27<(u8-34.00)*0.00808779<1.79 out_q: -0.28<(u8-27.00)*0.01037279<2.36
                TCArgInfo("signed char * __restrict__", "S100_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S100_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.27<(u8-34.00)*0.00808779<1.79 out_q: -0.28<(u8-32.00)*0.00859755<1.92
                TCArgInfo("signed char * __restrict__", "S102_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S102_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst20", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst20.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant59", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant59.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S105_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S105_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S105_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S105_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02232 out: 0.01050  BIASN: 0 PRENORM: 0 NE16_PADVAL: [27] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S105_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S105_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant31", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant31.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant58", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant58.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S109_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S109_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S109_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S109_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02116 out: 0.01100  BIASN: 0 PRENORM: 0 NE16_PADVAL: [27] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S109_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S109_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst19", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst19.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant57", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant57.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S112_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S112_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S112_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S112_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01598 out: 0.01050  BIASN: 0 PRENORM: 0 NE16_PADVAL: [25] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S112_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S112_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst17", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst17.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant55", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant55.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S116_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S116_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S116_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S116_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01926 out: 0.01183  BIASN: 0 PRENORM: 0 NE16_PADVAL: [27] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S116_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S116_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst16", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst16.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant54", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant54.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S119_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S119_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S119_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S119_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01814 out: 0.01050  BIASN: 0 PRENORM: 0 NE16_PADVAL: [24] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S119_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S119_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-27.00)*0.01050040<2.39 out_q: -0.29<(u8-22.00)*0.01303558<3.04
                TCArgInfo("signed char * __restrict__", "S121_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S121_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-27.00)*0.01050040<2.39 out_q: -0.29<(u8-25.00)*0.01151866<2.65
                TCArgInfo("signed char * __restrict__", "S123_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S123_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst15", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst15.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant53", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant53.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S126_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S126_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S126_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S126_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02015 out: 0.00907  BIASN: 0 PRENORM: 0 NE16_PADVAL: [22] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S126_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S126_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant32", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant32.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant52", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant52.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S130_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S130_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S130_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S130_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01735 out: 0.00836  BIASN: 0 PRENORM: 0 NE16_PADVAL: [31] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S130_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S130_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst14", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst14.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant51", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant51.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S133_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S133_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S133_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S133_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01898 out: 0.00907  BIASN: 0 PRENORM: 0 NE16_PADVAL: [33] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S133_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S133_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst12", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst12.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant49", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant49.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S137_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S137_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S137_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S137_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02442 out: 0.01449  BIASN: 0 PRENORM: 0 NE16_PADVAL: [31] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S137_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S137_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst11", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst11.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant48", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant48.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S140_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S140_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S140_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S140_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01872 out: 0.01152  BIASN: 0 PRENORM: 0 NE16_PADVAL: [19] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S140_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S140_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst10", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst10.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant47", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant47.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S144_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S144_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S144_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S144_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01798 out: 0.00896  BIASN: 0 PRENORM: 0 NE16_PADVAL: [25] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S144_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S144_Infos.tensor", 1, 1, 8, 0)),
                // in q: -0.28<(u8-31.00)*0.00896083<2.01 out_q: -0.28<(u8-31.00)*0.00896299<2.01
                TCArgInfo("signed char * __restrict__", "S146_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S146_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant33", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant33.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant46", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant46.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S149_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S149_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S149_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S149_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01597 out: 0.00836  BIASN: 0 PRENORM: 0 NE16_PADVAL: [31] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S149_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S149_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst9", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst9.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant45", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant45.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S152_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S152_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S152_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S152_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01168 out: 0.00896  BIASN: 0 PRENORM: 0 NE16_PADVAL: [33] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S152_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S152_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst7", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst7.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant43", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant43.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S156_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S156_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S156_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S156_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.02131 out: 0.01290  BIASN: 0 PRENORM: 0 NE16_PADVAL: [31] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S156_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S156_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst6", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst6.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant42", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant42.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S159_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S159_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S159_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S159_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01336 out: 0.00860  BIASN: 0 PRENORM: 0 NE16_PADVAL: [22] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S159_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S159_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst5", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst5.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant41", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant41.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S163_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S163_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S163_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S163_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01340 out: 0.00711  BIASN: 0 PRENORM: 0 NE16_PADVAL: [32] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S163_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S163_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst4", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst4.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant40", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant40.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S167_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S167_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S167_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S167_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01357 out: 0.00819  BIASN: 0 PRENORM: 0 NE16_PADVAL: [39] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S167_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S167_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst3", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst3.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant39", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant39.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S170_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S170_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S170_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S170_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01084 out: 0.00711  BIASN: 0 PRENORM: 0 NE16_PADVAL: [34] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S170_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S170_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst1", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst1.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant37", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant37.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S174_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S174_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S174_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S174_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.01734 out: 0.00902  BIASN: 0 PRENORM: 0 NE16_PADVAL: [39] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S174_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S174_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Tfl_pseudo_qconst", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Tfl_pseudo_qconst.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant36", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant36.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S177_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S177_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S177_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S177_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [31] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S177_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S177_Infos.tensor", 1, 1, 8, 0)),
                // in: 0.04913 out: 0.00392  actscale: [129] actscalen: [6] a0: [0] b0: 0 c0: 0
                TCArgInfo("signed char * __restrict__", "S180_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S180_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant18", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant18.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant20", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant20.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant19", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant19.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant88", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant88.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant35", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant35.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S188_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S188_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S188_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S188_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [22] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S188_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S188_Infos.tensor", 1, 1, 8, 0)),
                // in: 0.04913 out: 0.00392  actscale: [129] actscalen: [6] a0: [0] b0: 0 c0: 0
                TCArgInfo("signed char * __restrict__", "S191_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S191_Infos.tensor", 1, 1, 8, 0)),
                // in q: 0.00<(u8-0.00)*0.00392157<1.00 out_q: -1.02<(u8-128.00)*0.00793623<1.01 forced
                TCArgInfo("signed char * __restrict__", "S193_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S193_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant16", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant16.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant17", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant17.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "Arith_constant87", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant87.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Arith_constant34", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant34.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S198_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S198_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S198_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S198_Mul_shift.tensor", 1, 1, 8, 0)),
                // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [19] NE16_WOFFSET: [-128]
                TCArgInfo("signed char * __restrict__", "S198_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S198_Infos.tensor", 1, 1, 8, 0)),
                // in: 0.04913 out: 0.00392  actscale: [129] actscalen: [6] a0: [0] b0: 0 c0: 0
                TCArgInfo("signed char * __restrict__", "S201_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S201_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant14", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant14.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant15", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant15.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant20_1", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant20_1.tensor", 1, 1, 8, 0)),
                // in q: 0.00<(u8-0.00)*0.00392157<1.00 out_q: -1.02<(u8-128.00)*0.00793623<1.01 forced
                TCArgInfo("signed char * __restrict__", "S209_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S209_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant20_2", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant20_2.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant20_3", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant20_3.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant20_4", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant20_4.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Arith_constant20_5", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Arith_constant20_5.tensor", 1, 1, 8, 0)),
                // in q: 0.00<(u8-0.00)*0.00392157<1.00 out_q: -1.02<(u8-128.00)*0.00793623<1.01 forced
                TCArgInfo("signed char * __restrict__", "S222_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S222_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "SigmoidLUT_u8", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("SigmoidLUT_u8.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned short * __restrict__", "SigmoidLUTTable", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("SigmoidLUTTable.tensor", 1, 1, 16, 0)),
                TCArgInfo("unsigned char * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(121,
            TCArgInfo("unsigned char * __restrict__", "S3_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S6_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S9_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S10_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S10_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S11_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S14_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S17_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S18_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S19_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S22_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S25_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S28_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S29_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S29_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S30_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S33_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S36_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S37_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S38_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S41_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S42_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S45_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S48_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S49_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S49_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S50_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S53_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S56_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S57_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S58_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S61_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S64_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S67_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S68_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S68_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S69_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S72_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S75_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S76_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S77_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S80_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S83_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S84_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S85_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S86_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S87_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S88_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S89_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S90_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S91_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S92_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S95_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S98_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S99_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S100_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S101_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S102_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S105_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S106_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S106_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S109_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S112_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S113_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S116_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S119_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S120_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S121_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S122_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S123_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S126_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S127_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S127_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S130_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S133_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S134_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S137_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S140_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S141_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S144_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S145_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S145_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S146_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S149_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S152_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S153_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S156_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S159_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S160_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S163_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S164_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S164_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S167_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S170_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S171_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S174_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S177_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S179_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S179_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S179_Output_2", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S180_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S184_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S188_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S190_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S190_Output_2", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S190_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S191_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S193_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S198_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S200_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S200_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S200_Output_2", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S201_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S206_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S207_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S211_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S213_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S217_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S219_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S220_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S223_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );

    // Stacked tensors for concats and splits
    AddStackedTensors(
        "S223_Output",
        3, "S222_Output", "S214_Output", "S209_Output"
    );

    // Node S3_CONV_2D_0_0_fusion inq 0.00<(u8-0.00)*0.00392157<1.00 weightsq chan<(u8-128.00)*chan<chan outq -0.23<(u8-2.00)*0.11510530<29.12 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S3_CONV_2D_0_0_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "Input_1", 0),
            GNodeArg(GNA_IN, "Arith_constant21", 0),
            GNodeArg(GNA_IN, "Arith_constant", 0),
            GNodeArg(GNA_OUT, "S3_Output", 0),
            GNodeArg(GNA_IN, "S3_Mul_scale", 0),
            GNodeArg(GNA_IN, "S3_Mul_shift", 0),
            GNodeArg(GNA_IN, "S3_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S6_CONV_2D_0_4_fusion inq -0.23<(u8-2.00)*0.11510530<29.12 weightsq chan<(u8-128.00)*chan<chan outq -0.24<(u8-3.00)*0.08054052<20.30 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S6_CONV_2D_0_4_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S3_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst38", 0),
            GNodeArg(GNA_IN, "Arith_constant86", 0),
            GNodeArg(GNA_OUT, "S6_Output", 0),
            GNodeArg(GNA_IN, "S6_Mul_scale", 0),
            GNodeArg(GNA_IN, "S6_Mul_shift", 0),
            GNodeArg(GNA_IN, "S6_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S9_CONV_2D_0_7_fusion inq -0.24<(u8-3.00)*0.08054052<20.30 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-11.00)*0.02612432<6.37 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S9_CONV_2D_0_7_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S6_Output", 0),
            GNodeArg(GNA_IN, "Arith_constant22", 0),
            GNodeArg(GNA_IN, "Arith_constant85", 0),
            GNodeArg(GNA_OUT, "S9_Output", 0),
            GNodeArg(GNA_IN, "S9_Mul_scale", 0),
            GNodeArg(GNA_IN, "S9_Mul_shift", 0),
            GNodeArg(GNA_IN, "S9_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_7_split inq -0.29<(u8-11.00)*0.02612432<6.37 outq -0.29<(u8-11.00)*0.02612432<6.37
    AddNode("S10_CONV_2D_0_7_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S9_Output", 0),
            GNodeArg(GNA_OUT, "S10_Output_0", 0),
            GNodeArg(GNA_OUT, "S10_Output_1", 0)
        )
    );
    // Node CONV_2D_0_7_split_copy_qout0 inq -0.29<(u8-11.00)*0.02612432<6.37 outq -0.57<(u8-21.00)*0.02720781<6.37
    AddNode("S11_CONV_2D_0_7_split_copy_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S10_Output_1", 0),
            GNodeArg(GNA_OUT, "S11_Output", 0),
            GNodeArg(GNA_IN, "S11_Infos", 0)
        )
    );
    // Node S14_CONV_2D_0_10_fusion inq -0.29<(u8-11.00)*0.02612432<6.37 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-12.00)*0.02330979<5.66 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S14_CONV_2D_0_10_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S10_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant23", 0),
            GNodeArg(GNA_IN, "Arith_constant84", 0),
            GNodeArg(GNA_OUT, "S14_Output", 0),
            GNodeArg(GNA_IN, "S14_Mul_scale", 0),
            GNodeArg(GNA_IN, "S14_Mul_shift", 0),
            GNodeArg(GNA_IN, "S14_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S17_CONV_2D_0_13 inq -0.28<(u8-12.00)*0.02330979<5.66 weightsq chan<(u8-128.00)*chan<chan outq -5.52<(u8-136.00)*0.04061821<4.83 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S17_CONV_2D_0_13",
        Bindings(7,
            GNodeArg(GNA_IN, "S14_Output", 0),
            GNodeArg(GNA_IN, "Arith_constant24", 0),
            GNodeArg(GNA_IN, "Arith_constant83", 0),
            GNodeArg(GNA_OUT, "S17_Output", 0),
            GNodeArg(GNA_IN, "S17_Mul_scale", 0),
            GNodeArg(GNA_IN, "S17_Mul_shift", 0),
            GNodeArg(GNA_IN, "S17_Infos", 0)
        )
    );
    // Node expr_0 in_qs [-5.52<(u8-136.00)*0.04061821<4.83,-0.29<(u8-11.00)*0.02612432<6.37] out_qs [-0.57<(u8-21.00)*0.02720781<6.37]
    AddNode("S18_expr_0",
        Bindings(4,
            GNodeArg(GNA_IN, "S17_Output", 0),
            GNodeArg(GNA_IN, "S10_Output_0", 0),
            GNodeArg(GNA_OUT, "S18_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_20 inq -0.57<(u8-21.00)*0.02720781<6.37 outq -0.57<(u8-21.00)*0.02720781<6.37
    AddNode("S19_CONCAT_0_20",
        Bindings(3,
            GNodeArg(GNA_IN, "S18_Output", 0),
            GNodeArg(GNA_IN, "S11_Output", 0),
            GNodeArg(GNA_OUT, "S19_Output", 0)
        )
    );
    // Node S22_CONV_2D_0_21_fusion inq -0.57<(u8-21.00)*0.02720781<6.37 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-12.00)*0.02377008<5.78 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S22_CONV_2D_0_21_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S19_Output", 0),
            GNodeArg(GNA_IN, "Arith_constant26", 0),
            GNodeArg(GNA_IN, "Arith_constant81", 0),
            GNodeArg(GNA_OUT, "S22_Output", 0),
            GNodeArg(GNA_IN, "S22_Mul_scale", 0),
            GNodeArg(GNA_IN, "S22_Mul_shift", 0),
            GNodeArg(GNA_IN, "S22_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S25_CONV_2D_0_25_fusion inq -0.29<(u8-12.00)*0.02377008<5.78 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-14.00)*0.02022647<4.87 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S25_CONV_2D_0_25_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S22_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst37", 0),
            GNodeArg(GNA_IN, "Arith_constant80", 0),
            GNodeArg(GNA_OUT, "S25_Output", 0),
            GNodeArg(GNA_IN, "S25_Mul_scale", 0),
            GNodeArg(GNA_IN, "S25_Mul_shift", 0),
            GNodeArg(GNA_IN, "S25_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S28_CONV_2D_0_28_fusion inq -0.28<(u8-14.00)*0.02022647<4.87 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-11.00)*0.02641341<6.44 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S28_CONV_2D_0_28_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S25_Output", 0),
            GNodeArg(GNA_IN, "Arith_constant27", 0),
            GNodeArg(GNA_IN, "Arith_constant79", 0),
            GNodeArg(GNA_OUT, "S28_Output", 0),
            GNodeArg(GNA_IN, "S28_Mul_scale", 0),
            GNodeArg(GNA_IN, "S28_Mul_shift", 0),
            GNodeArg(GNA_IN, "S28_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_28_split inq -0.29<(u8-11.00)*0.02641341<6.44 outq -0.29<(u8-11.00)*0.02641341<6.44
    AddNode("S29_CONV_2D_0_28_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S28_Output", 0),
            GNodeArg(GNA_OUT, "S29_Output_0", 0),
            GNodeArg(GNA_OUT, "S29_Output_1", 0)
        )
    );
    // Node CONV_2D_0_28_split_copy_qout0 inq -0.29<(u8-11.00)*0.02641341<6.44 outq -0.55<(u8-20.00)*0.02742977<6.45
    AddNode("S30_CONV_2D_0_28_split_copy_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S29_Output_1", 0),
            GNodeArg(GNA_OUT, "S30_Output", 0),
            GNodeArg(GNA_IN, "S30_Infos", 0)
        )
    );
    // Node S33_CONV_2D_0_31_fusion inq -0.29<(u8-11.00)*0.02641341<6.44 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-15.00)*0.01897936<4.56 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S33_CONV_2D_0_31_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S29_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant28", 0),
            GNodeArg(GNA_IN, "Arith_constant78", 0),
            GNodeArg(GNA_OUT, "S33_Output", 0),
            GNodeArg(GNA_IN, "S33_Mul_scale", 0),
            GNodeArg(GNA_IN, "S33_Mul_shift", 0),
            GNodeArg(GNA_IN, "S33_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S36_CONV_2D_0_34 inq -0.28<(u8-15.00)*0.01897936<4.56 weightsq chan<(u8-128.00)*chan<chan outq -4.13<(u8-142.00)*0.02909165<3.29 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S36_CONV_2D_0_34",
        Bindings(7,
            GNodeArg(GNA_IN, "S33_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst36", 0),
            GNodeArg(GNA_IN, "Arith_constant77", 0),
            GNodeArg(GNA_OUT, "S36_Output", 0),
            GNodeArg(GNA_IN, "S36_Mul_scale", 0),
            GNodeArg(GNA_IN, "S36_Mul_shift", 0),
            GNodeArg(GNA_IN, "S36_Infos", 0)
        )
    );
    // Node expr_4 in_qs [-4.13<(u8-142.00)*0.02909165<3.29,-0.29<(u8-11.00)*0.02641341<6.44] out_qs [-0.55<(u8-20.00)*0.02742977<6.45]
    AddNode("S37_expr_4",
        Bindings(4,
            GNodeArg(GNA_IN, "S36_Output", 0),
            GNodeArg(GNA_IN, "S29_Output_0", 0),
            GNodeArg(GNA_OUT, "S37_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_41 inq -0.55<(u8-20.00)*0.02742977<6.45 outq -0.55<(u8-20.00)*0.02742977<6.45
    AddNode("S38_CONCAT_0_41",
        Bindings(3,
            GNodeArg(GNA_IN, "S37_Output", 0),
            GNodeArg(GNA_IN, "S30_Output", 0),
            GNodeArg(GNA_OUT, "S38_Output", 0)
        )
    );
    // Node S41_CONV_2D_0_42_fusion inq -0.55<(u8-20.00)*0.02742977<6.45 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-21.00)*0.01299385<3.04 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S41_CONV_2D_0_42_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S38_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst35", 0),
            GNodeArg(GNA_IN, "Arith_constant75", 0),
            GNodeArg(GNA_OUT, "S41_Output", 0),
            GNodeArg(GNA_IN, "S41_Mul_scale", 0),
            GNodeArg(GNA_IN, "S41_Mul_shift", 0),
            GNodeArg(GNA_IN, "S41_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_42_fusion_qout0 inq -0.27<(u8-21.00)*0.01299385<3.04 outq -0.29<(u8-22.00)*0.01303558<3.04
    AddNode("S42_CONV_2D_0_42_fusion_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S41_Output", 0),
            GNodeArg(GNA_OUT, "S42_Output", 0),
            GNodeArg(GNA_IN, "S42_Infos", 0)
        )
    );
    // Node S45_CONV_2D_0_46_fusion inq -0.27<(u8-21.00)*0.01299385<3.04 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-22.00)*0.01273682<2.97 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S45_CONV_2D_0_46_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S41_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst34", 0),
            GNodeArg(GNA_IN, "Arith_constant74", 0),
            GNodeArg(GNA_OUT, "S45_Output", 0),
            GNodeArg(GNA_IN, "S45_Mul_scale", 0),
            GNodeArg(GNA_IN, "S45_Mul_shift", 0),
            GNodeArg(GNA_IN, "S45_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S48_CONV_2D_0_49_fusion inq -0.28<(u8-22.00)*0.01273682<2.97 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-24.00)*0.01174527<2.71 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S48_CONV_2D_0_49_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S45_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst33", 0),
            GNodeArg(GNA_IN, "Arith_constant73", 0),
            GNodeArg(GNA_OUT, "S48_Output", 0),
            GNodeArg(GNA_IN, "S48_Mul_scale", 0),
            GNodeArg(GNA_IN, "S48_Mul_shift", 0),
            GNodeArg(GNA_IN, "S48_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_49_split inq -0.28<(u8-24.00)*0.01174527<2.71 outq -0.28<(u8-24.00)*0.01174527<2.71
    AddNode("S49_CONV_2D_0_49_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S48_Output", 0),
            GNodeArg(GNA_OUT, "S49_Output_0", 0),
            GNodeArg(GNA_OUT, "S49_Output_1", 0)
        )
    );
    // Node CONV_2D_0_49_split_copy_qout0 inq -0.28<(u8-24.00)*0.01174527<2.71 outq -0.56<(u8-42.00)*0.01323155<2.82
    AddNode("S50_CONV_2D_0_49_split_copy_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S49_Output_1", 0),
            GNodeArg(GNA_OUT, "S50_Output", 0),
            GNodeArg(GNA_IN, "S50_Infos", 0)
        )
    );
    // Node S53_CONV_2D_0_52_fusion inq -0.28<(u8-24.00)*0.01174527<2.71 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-27.00)*0.01042723<2.38 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S53_CONV_2D_0_52_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S49_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant30", 0),
            GNodeArg(GNA_IN, "Arith_constant72", 0),
            GNodeArg(GNA_OUT, "S53_Output", 0),
            GNodeArg(GNA_IN, "S53_Mul_scale", 0),
            GNodeArg(GNA_IN, "S53_Mul_shift", 0),
            GNodeArg(GNA_IN, "S53_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S56_CONV_2D_0_55 inq -0.28<(u8-27.00)*0.01042723<2.38 weightsq chan<(u8-128.00)*chan<chan outq -2.98<(u8-140.00)*0.02131694<2.45 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S56_CONV_2D_0_55",
        Bindings(7,
            GNodeArg(GNA_IN, "S53_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst32", 0),
            GNodeArg(GNA_IN, "Arith_constant71", 0),
            GNodeArg(GNA_OUT, "S56_Output", 0),
            GNodeArg(GNA_IN, "S56_Mul_scale", 0),
            GNodeArg(GNA_IN, "S56_Mul_shift", 0),
            GNodeArg(GNA_IN, "S56_Infos", 0)
        )
    );
    // Node expr_5 in_qs [-2.98<(u8-140.00)*0.02131694<2.45,-0.28<(u8-24.00)*0.01174527<2.71] out_qs [-0.56<(u8-42.00)*0.01323155<2.82]
    AddNode("S57_expr_5",
        Bindings(4,
            GNodeArg(GNA_IN, "S56_Output", 0),
            GNodeArg(GNA_IN, "S49_Output_0", 0),
            GNodeArg(GNA_OUT, "S57_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_62 inq -0.56<(u8-42.00)*0.01323155<2.82 outq -0.56<(u8-42.00)*0.01323155<2.82
    AddNode("S58_CONCAT_0_62",
        Bindings(3,
            GNodeArg(GNA_IN, "S57_Output", 0),
            GNodeArg(GNA_IN, "S50_Output", 0),
            GNodeArg(GNA_OUT, "S58_Output", 0)
        )
    );
    // Node S61_CONV_2D_0_63_fusion inq -0.56<(u8-42.00)*0.01323155<2.82 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-27.00)*0.01037279<2.36 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S61_CONV_2D_0_63_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S58_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst30", 0),
            GNodeArg(GNA_IN, "Arith_constant69", 0),
            GNodeArg(GNA_OUT, "S61_Output", 0),
            GNodeArg(GNA_IN, "S61_Mul_scale", 0),
            GNodeArg(GNA_IN, "S61_Mul_shift", 0),
            GNodeArg(GNA_IN, "S61_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S64_CONV_2D_0_67_fusion inq -0.28<(u8-27.00)*0.01037279<2.36 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-29.00)*0.00970420<2.19 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S64_CONV_2D_0_67_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S61_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst29", 0),
            GNodeArg(GNA_IN, "Arith_constant68", 0),
            GNodeArg(GNA_OUT, "S64_Output", 0),
            GNodeArg(GNA_IN, "S64_Mul_scale", 0),
            GNodeArg(GNA_IN, "S64_Mul_shift", 0),
            GNodeArg(GNA_IN, "S64_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S67_CONV_2D_0_70_fusion inq -0.28<(u8-29.00)*0.00970420<2.19 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-29.00)*0.00947452<2.14 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S67_CONV_2D_0_70_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S64_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst28", 0),
            GNodeArg(GNA_IN, "Arith_constant67", 0),
            GNodeArg(GNA_OUT, "S67_Output", 0),
            GNodeArg(GNA_IN, "S67_Mul_scale", 0),
            GNodeArg(GNA_IN, "S67_Mul_shift", 0),
            GNodeArg(GNA_IN, "S67_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_70_split inq -0.27<(u8-29.00)*0.00947452<2.14 outq -0.27<(u8-29.00)*0.00947452<2.14
    AddNode("S68_CONV_2D_0_70_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S67_Output", 0),
            GNodeArg(GNA_OUT, "S68_Output_0", 0),
            GNodeArg(GNA_OUT, "S68_Output_1", 0)
        )
    );
    // Node CONV_2D_0_70_split_copy_qout0 inq -0.27<(u8-29.00)*0.00947452<2.14 outq -0.56<(u8-42.00)*0.01324933<2.82
    AddNode("S69_CONV_2D_0_70_split_copy_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S68_Output_1", 0),
            GNodeArg(GNA_OUT, "S69_Output", 0),
            GNodeArg(GNA_IN, "S69_Infos", 0)
        )
    );
    // Node S72_CONV_2D_0_73_fusion inq -0.27<(u8-29.00)*0.00947452<2.14 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-25.00)*0.01130989<2.60 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S72_CONV_2D_0_73_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S68_Output_0", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst27", 0),
            GNodeArg(GNA_IN, "Arith_constant66", 0),
            GNodeArg(GNA_OUT, "S72_Output", 0),
            GNodeArg(GNA_IN, "S72_Mul_scale", 0),
            GNodeArg(GNA_IN, "S72_Mul_shift", 0),
            GNodeArg(GNA_IN, "S72_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S75_CONV_2D_0_76 inq -0.28<(u8-25.00)*0.01130989<2.60 weightsq chan<(u8-128.00)*chan<chan outq -2.35<(u8-109.00)*0.02151879<3.14 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S75_CONV_2D_0_76",
        Bindings(7,
            GNodeArg(GNA_IN, "S72_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst26", 0),
            GNodeArg(GNA_IN, "Arith_constant65", 0),
            GNodeArg(GNA_OUT, "S75_Output", 0),
            GNodeArg(GNA_IN, "S75_Mul_scale", 0),
            GNodeArg(GNA_IN, "S75_Mul_shift", 0),
            GNodeArg(GNA_IN, "S75_Infos", 0)
        )
    );
    // Node expr_6 in_qs [-2.35<(u8-109.00)*0.02151879<3.14,-0.27<(u8-29.00)*0.00947452<2.14] out_qs [-0.56<(u8-42.00)*0.01324933<2.82]
    AddNode("S76_expr_6",
        Bindings(4,
            GNodeArg(GNA_IN, "S75_Output", 0),
            GNodeArg(GNA_IN, "S68_Output_0", 0),
            GNodeArg(GNA_OUT, "S76_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_83 inq -0.56<(u8-42.00)*0.01324933<2.82 outq -0.56<(u8-42.00)*0.01324933<2.82
    AddNode("S77_CONCAT_0_83",
        Bindings(3,
            GNodeArg(GNA_IN, "S76_Output", 0),
            GNodeArg(GNA_IN, "S69_Output", 0),
            GNodeArg(GNA_OUT, "S77_Output", 0)
        )
    );
    // Node S80_CONV_2D_0_84_fusion inq -0.56<(u8-42.00)*0.01324933<2.82 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-26.00)*0.01061627<2.43 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S80_CONV_2D_0_84_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S77_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst24", 0),
            GNodeArg(GNA_IN, "Arith_constant63", 0),
            GNodeArg(GNA_OUT, "S80_Output", 0),
            GNodeArg(GNA_IN, "S80_Mul_scale", 0),
            GNodeArg(GNA_IN, "S80_Mul_shift", 0),
            GNodeArg(GNA_IN, "S80_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S83_CONV_2D_0_87_fusion inq -0.28<(u8-26.00)*0.01061627<2.43 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-22.00)*0.01279965<2.98 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S83_CONV_2D_0_87_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S80_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst23", 0),
            GNodeArg(GNA_IN, "Arith_constant62", 0),
            GNodeArg(GNA_OUT, "S83_Output", 0),
            GNodeArg(GNA_IN, "S83_Mul_scale", 0),
            GNodeArg(GNA_IN, "S83_Mul_shift", 0),
            GNodeArg(GNA_IN, "S83_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_87_fusion_qout0 inq -0.28<(u8-22.00)*0.01279965<2.98 outq 0.00<(u8-0.00)*0.01170763<2.99 forced
    AddNode("S84_CONV_2D_0_87_fusion_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S83_Output", 0),
            GNodeArg(GNA_OUT, "S84_Output", 0),
            GNodeArg(GNA_IN, "S84_Infos", 0)
        )
    );
    // Node MAX_POOL_2D_0_90 inq 0.00<(u8-0.00)*0.01170763<2.99 forced outq 0.00<(u8-0.00)*0.01170763<2.99 forced
    AddNode("S85_MAX_POOL_2D_0_90",
        Bindings(3,
            GNodeArg(GNA_IN, "S84_Output", 0),
            GNodeArg(GNA_OUT, "S85_Output", 0),
            GNodeArg(GNA_IN, "S85_Infos", 0)
        )
    );
    // Node MAX_POOL_2D_0_91 inq 0.00<(u8-0.00)*0.01170763<2.99 forced outq 0.00<(u8-0.00)*0.01170763<2.99 forced
    AddNode("S86_MAX_POOL_2D_0_91",
        Bindings(3,
            GNodeArg(GNA_IN, "S85_Output", 0),
            GNodeArg(GNA_OUT, "S86_Output", 0),
            GNodeArg(GNA_IN, "S86_Infos", 0)
        )
    );
    // Node MAX_POOL_2D_0_92 inq 0.00<(u8-0.00)*0.01170763<2.99 forced outq 0.00<(u8-0.00)*0.01170763<2.99 forced
    AddNode("S87_MAX_POOL_2D_0_92",
        Bindings(3,
            GNodeArg(GNA_IN, "S86_Output", 0),
            GNodeArg(GNA_OUT, "S87_Output", 0),
            GNodeArg(GNA_IN, "S87_Infos", 0)
        )
    );
    // Node MAX_POOL_2D_0_92_qout0 inq 0.00<(u8-0.00)*0.01170763<2.99 forced outq -0.28<(u8-22.00)*0.01281192<2.99
    AddNode("S88_MAX_POOL_2D_0_92_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S87_Output", 0),
            GNodeArg(GNA_OUT, "S88_Output", 0),
            GNodeArg(GNA_IN, "S88_Infos", 0)
        )
    );
    // Node MAX_POOL_2D_0_91_qout0 inq 0.00<(u8-0.00)*0.01170763<2.99 forced outq -0.28<(u8-22.00)*0.01281192<2.99
    AddNode("S89_MAX_POOL_2D_0_91_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S86_Output", 0),
            GNodeArg(GNA_OUT, "S89_Output", 0),
            GNodeArg(GNA_IN, "S89_Infos", 0)
        )
    );
    // Node MAX_POOL_2D_0_90_qout0 inq 0.00<(u8-0.00)*0.01170763<2.99 forced outq -0.28<(u8-22.00)*0.01281192<2.99
    AddNode("S90_MAX_POOL_2D_0_90_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S85_Output", 0),
            GNodeArg(GNA_OUT, "S90_Output", 0),
            GNodeArg(GNA_IN, "S90_Infos", 0)
        )
    );
    // Node CONV_2D_0_87_fusion_qout0_0 inq -0.28<(u8-22.00)*0.01279965<2.98 outq -0.28<(u8-22.00)*0.01281192<2.99
    AddNode("S91_CONV_2D_0_87_fusion_qout0_0",
        Bindings(3,
            GNodeArg(GNA_IN, "S83_Output", 0),
            GNodeArg(GNA_OUT, "S91_Output", 0),
            GNodeArg(GNA_IN, "S91_Infos", 0)
        )
    );
    // Node CONCAT_0_93 inq -0.28<(u8-22.00)*0.01281192<2.99 outq -0.28<(u8-22.00)*0.01281192<2.99
    AddNode("S92_CONCAT_0_93",
        Bindings(5,
            GNodeArg(GNA_IN, "S91_Output", 0),
            GNodeArg(GNA_IN, "S90_Output", 0),
            GNodeArg(GNA_IN, "S89_Output", 0),
            GNodeArg(GNA_IN, "S88_Output", 0),
            GNodeArg(GNA_OUT, "S92_Output", 0)
        )
    );
    // Node S95_CONV_2D_0_94_fusion inq -0.28<(u8-22.00)*0.01281192<2.99 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-20.00)*0.01411281<3.32 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S95_CONV_2D_0_94_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S92_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst22", 0),
            GNodeArg(GNA_IN, "Arith_constant61", 0),
            GNodeArg(GNA_OUT, "S95_Output", 0),
            GNodeArg(GNA_IN, "S95_Mul_scale", 0),
            GNodeArg(GNA_IN, "S95_Mul_shift", 0),
            GNodeArg(GNA_IN, "S95_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S98_CONV_2D_0_97_fusion inq -0.28<(u8-20.00)*0.01411281<3.32 weightsq chan<(u8-128.00)*chan<chan outq -0.27<(u8-34.00)*0.00808779<1.79 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S98_CONV_2D_0_97_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S95_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst21", 0),
            GNodeArg(GNA_IN, "Arith_constant60", 0),
            GNodeArg(GNA_OUT, "S98_Output", 0),
            GNodeArg(GNA_IN, "S98_Mul_scale", 0),
            GNodeArg(GNA_IN, "S98_Mul_shift", 0),
            GNodeArg(GNA_IN, "S98_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node RESIZE_NN_0_100 inq -0.27<(u8-34.00)*0.00808779<1.79 outq -0.27<(u8-34.00)*0.00808779<1.79
    AddNode("S99_RESIZE_NN_0_100",
        Bindings(2,
            GNodeArg(GNA_IN, "S98_Output", 0),
            GNodeArg(GNA_OUT, "S99_Output", 0)
        )
    );
    // Node RESIZE_NN_0_100_qout0 inq -0.27<(u8-34.00)*0.00808779<1.79 outq -0.28<(u8-27.00)*0.01037279<2.36
    AddNode("S100_RESIZE_NN_0_100_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S99_Output", 0),
            GNodeArg(GNA_OUT, "S100_Output", 0),
            GNodeArg(GNA_IN, "S100_Infos", 0)
        )
    );
    // Node CONCAT_0_101 inq -0.28<(u8-27.00)*0.01037279<2.36 outq -0.28<(u8-27.00)*0.01037279<2.36
    AddNode("S101_CONCAT_0_101",
        Bindings(3,
            GNodeArg(GNA_IN, "S100_Output", 0),
            GNodeArg(GNA_IN, "S61_Output", 0),
            GNodeArg(GNA_OUT, "S101_Output", 0)
        )
    );
    // Node CONV_2D_0_97_fusion_qout0 inq -0.27<(u8-34.00)*0.00808779<1.79 outq -0.28<(u8-32.00)*0.00859755<1.92
    AddNode("S102_CONV_2D_0_97_fusion_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S98_Output", 0),
            GNodeArg(GNA_OUT, "S102_Output", 0),
            GNodeArg(GNA_IN, "S102_Infos", 0)
        )
    );
    // Node S105_CONV_2D_0_102_fusion inq -0.28<(u8-27.00)*0.01037279<2.36 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-27.00)*0.01049996<2.39 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S105_CONV_2D_0_102_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S101_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst20", 0),
            GNodeArg(GNA_IN, "Arith_constant59", 0),
            GNodeArg(GNA_OUT, "S105_Output", 0),
            GNodeArg(GNA_IN, "S105_Mul_scale", 0),
            GNodeArg(GNA_IN, "S105_Mul_shift", 0),
            GNodeArg(GNA_IN, "S105_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_102_split inq -0.28<(u8-27.00)*0.01049996<2.39 outq -0.28<(u8-27.00)*0.01049996<2.39
    AddNode("S106_CONV_2D_0_102_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S105_Output", 0),
            GNodeArg(GNA_OUT, "S106_Output_0", 0),
            GNodeArg(GNA_OUT, "S106_Output_1", 0)
        )
    );
    // Node S109_CONV_2D_0_105_fusion inq -0.28<(u8-27.00)*0.01049996<2.39 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-25.00)*0.01100401<2.53 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S109_CONV_2D_0_105_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S106_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant31", 0),
            GNodeArg(GNA_IN, "Arith_constant58", 0),
            GNodeArg(GNA_OUT, "S109_Output", 0),
            GNodeArg(GNA_IN, "S109_Mul_scale", 0),
            GNodeArg(GNA_IN, "S109_Mul_shift", 0),
            GNodeArg(GNA_IN, "S109_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S112_CONV_2D_0_108_fusion inq -0.28<(u8-25.00)*0.01100401<2.53 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-27.00)*0.01049996<2.39 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S112_CONV_2D_0_108_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S109_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst19", 0),
            GNodeArg(GNA_IN, "Arith_constant57", 0),
            GNodeArg(GNA_OUT, "S112_Output", 0),
            GNodeArg(GNA_IN, "S112_Mul_scale", 0),
            GNodeArg(GNA_IN, "S112_Mul_shift", 0),
            GNodeArg(GNA_IN, "S112_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_114 inq -0.28<(u8-27.00)*0.01049996<2.39 outq -0.28<(u8-27.00)*0.01049996<2.39
    AddNode("S113_CONCAT_0_114",
        Bindings(3,
            GNodeArg(GNA_IN, "S112_Output", 0),
            GNodeArg(GNA_IN, "S106_Output_1", 0),
            GNodeArg(GNA_OUT, "S113_Output", 0)
        )
    );
    // Node S116_CONV_2D_0_115_fusion inq -0.28<(u8-27.00)*0.01049996<2.39 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-24.00)*0.01183463<2.73 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S116_CONV_2D_0_115_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S113_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst17", 0),
            GNodeArg(GNA_IN, "Arith_constant55", 0),
            GNodeArg(GNA_OUT, "S116_Output", 0),
            GNodeArg(GNA_IN, "S116_Mul_scale", 0),
            GNodeArg(GNA_IN, "S116_Mul_shift", 0),
            GNodeArg(GNA_IN, "S116_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S119_CONV_2D_0_118_fusion inq -0.28<(u8-24.00)*0.01183463<2.73 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-27.00)*0.01050040<2.39 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S119_CONV_2D_0_118_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S116_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst16", 0),
            GNodeArg(GNA_IN, "Arith_constant54", 0),
            GNodeArg(GNA_OUT, "S119_Output", 0),
            GNodeArg(GNA_IN, "S119_Mul_scale", 0),
            GNodeArg(GNA_IN, "S119_Mul_shift", 0),
            GNodeArg(GNA_IN, "S119_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node RESIZE_NN_0_121 inq -0.28<(u8-27.00)*0.01050040<2.39 outq -0.28<(u8-27.00)*0.01050040<2.39
    AddNode("S120_RESIZE_NN_0_121",
        Bindings(2,
            GNodeArg(GNA_IN, "S119_Output", 0),
            GNodeArg(GNA_OUT, "S120_Output", 0)
        )
    );
    // Node RESIZE_NN_0_121_qout0 inq -0.28<(u8-27.00)*0.01050040<2.39 outq -0.29<(u8-22.00)*0.01303558<3.04
    AddNode("S121_RESIZE_NN_0_121_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S120_Output", 0),
            GNodeArg(GNA_OUT, "S121_Output", 0),
            GNodeArg(GNA_IN, "S121_Infos", 0)
        )
    );
    // Node CONCAT_0_122 inq -0.29<(u8-22.00)*0.01303558<3.04 outq -0.29<(u8-22.00)*0.01303558<3.04
    AddNode("S122_CONCAT_0_122",
        Bindings(3,
            GNodeArg(GNA_IN, "S121_Output", 0),
            GNodeArg(GNA_IN, "S42_Output", 0),
            GNodeArg(GNA_OUT, "S122_Output", 0)
        )
    );
    // Node CONV_2D_0_118_fusion_qout0 inq -0.28<(u8-27.00)*0.01050040<2.39 outq -0.29<(u8-25.00)*0.01151866<2.65
    AddNode("S123_CONV_2D_0_118_fusion_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S119_Output", 0),
            GNodeArg(GNA_OUT, "S123_Output", 0),
            GNodeArg(GNA_IN, "S123_Infos", 0)
        )
    );
    // Node S126_CONV_2D_0_123_fusion inq -0.29<(u8-22.00)*0.01303558<3.04 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-31.00)*0.00906893<2.03 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S126_CONV_2D_0_123_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S122_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst15", 0),
            GNodeArg(GNA_IN, "Arith_constant53", 0),
            GNodeArg(GNA_OUT, "S126_Output", 0),
            GNodeArg(GNA_IN, "S126_Mul_scale", 0),
            GNodeArg(GNA_IN, "S126_Mul_shift", 0),
            GNodeArg(GNA_IN, "S126_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_123_split inq -0.28<(u8-31.00)*0.00906893<2.03 outq -0.28<(u8-31.00)*0.00906893<2.03
    AddNode("S127_CONV_2D_0_123_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S126_Output", 0),
            GNodeArg(GNA_OUT, "S127_Output_0", 0),
            GNodeArg(GNA_OUT, "S127_Output_1", 0)
        )
    );
    // Node S130_CONV_2D_0_126_fusion inq -0.28<(u8-31.00)*0.00906893<2.03 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-33.00)*0.00835805<1.86 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S130_CONV_2D_0_126_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S127_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant32", 0),
            GNodeArg(GNA_IN, "Arith_constant52", 0),
            GNodeArg(GNA_OUT, "S130_Output", 0),
            GNodeArg(GNA_IN, "S130_Mul_scale", 0),
            GNodeArg(GNA_IN, "S130_Mul_shift", 0),
            GNodeArg(GNA_IN, "S130_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S133_CONV_2D_0_129_fusion inq -0.28<(u8-33.00)*0.00835805<1.86 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-31.00)*0.00906893<2.03 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S133_CONV_2D_0_129_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S130_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst14", 0),
            GNodeArg(GNA_IN, "Arith_constant51", 0),
            GNodeArg(GNA_OUT, "S133_Output", 0),
            GNodeArg(GNA_IN, "S133_Mul_scale", 0),
            GNodeArg(GNA_IN, "S133_Mul_shift", 0),
            GNodeArg(GNA_IN, "S133_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_135 inq -0.28<(u8-31.00)*0.00906893<2.03 outq -0.28<(u8-31.00)*0.00906893<2.03
    AddNode("S134_CONCAT_0_135",
        Bindings(3,
            GNodeArg(GNA_IN, "S133_Output", 0),
            GNodeArg(GNA_IN, "S127_Output_1", 0),
            GNodeArg(GNA_OUT, "S134_Output", 0)
        )
    );
    // Node S137_CONV_2D_0_136_fusion inq -0.28<(u8-31.00)*0.00906893<2.03 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-19.00)*0.01448963<3.42 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S137_CONV_2D_0_136_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S134_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst12", 0),
            GNodeArg(GNA_IN, "Arith_constant49", 0),
            GNodeArg(GNA_OUT, "S137_Output", 0),
            GNodeArg(GNA_IN, "S137_Mul_scale", 0),
            GNodeArg(GNA_IN, "S137_Mul_shift", 0),
            GNodeArg(GNA_IN, "S137_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S140_CONV_2D_0_140_fusion inq -0.28<(u8-19.00)*0.01448963<3.42 weightsq chan<(u8-128.00)*chan<chan outq -0.29<(u8-25.00)*0.01151866<2.65 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S140_CONV_2D_0_140_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S137_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst11", 0),
            GNodeArg(GNA_IN, "Arith_constant48", 0),
            GNodeArg(GNA_OUT, "S140_Output", 0),
            GNodeArg(GNA_IN, "S140_Mul_scale", 0),
            GNodeArg(GNA_IN, "S140_Mul_shift", 0),
            GNodeArg(GNA_IN, "S140_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_143 inq -0.29<(u8-25.00)*0.01151866<2.65 outq -0.29<(u8-25.00)*0.01151866<2.65
    AddNode("S141_CONCAT_0_143",
        Bindings(3,
            GNodeArg(GNA_IN, "S140_Output", 0),
            GNodeArg(GNA_IN, "S123_Output", 0),
            GNodeArg(GNA_OUT, "S141_Output", 0)
        )
    );
    // Node S144_CONV_2D_0_144_fusion inq -0.29<(u8-25.00)*0.01151866<2.65 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-31.00)*0.00896083<2.01 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S144_CONV_2D_0_144_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S141_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst10", 0),
            GNodeArg(GNA_IN, "Arith_constant47", 0),
            GNodeArg(GNA_OUT, "S144_Output", 0),
            GNodeArg(GNA_IN, "S144_Mul_scale", 0),
            GNodeArg(GNA_IN, "S144_Mul_shift", 0),
            GNodeArg(GNA_IN, "S144_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_144_split inq -0.28<(u8-31.00)*0.00896083<2.01 outq -0.28<(u8-31.00)*0.00896083<2.01
    AddNode("S145_CONV_2D_0_144_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S144_Output", 0),
            GNodeArg(GNA_OUT, "S145_Output_0", 0),
            GNodeArg(GNA_OUT, "S145_Output_1", 0)
        )
    );
    // Node CONV_2D_0_144_split_copy_qout0 inq -0.28<(u8-31.00)*0.00896083<2.01 outq -0.28<(u8-31.00)*0.00896299<2.01
    AddNode("S146_CONV_2D_0_144_split_copy_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S145_Output_1", 0),
            GNodeArg(GNA_OUT, "S146_Output", 0),
            GNodeArg(GNA_IN, "S146_Infos", 0)
        )
    );
    // Node S149_CONV_2D_0_147_fusion inq -0.28<(u8-31.00)*0.00896083<2.01 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-33.00)*0.00835720<1.86 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S149_CONV_2D_0_147_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S145_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant33", 0),
            GNodeArg(GNA_IN, "Arith_constant46", 0),
            GNodeArg(GNA_OUT, "S149_Output", 0),
            GNodeArg(GNA_IN, "S149_Mul_scale", 0),
            GNodeArg(GNA_IN, "S149_Mul_shift", 0),
            GNodeArg(GNA_IN, "S149_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S152_CONV_2D_0_150_fusion inq -0.28<(u8-33.00)*0.00835720<1.86 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-31.00)*0.00896299<2.01 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S152_CONV_2D_0_150_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S149_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst9", 0),
            GNodeArg(GNA_IN, "Arith_constant45", 0),
            GNodeArg(GNA_OUT, "S152_Output", 0),
            GNodeArg(GNA_IN, "S152_Mul_scale", 0),
            GNodeArg(GNA_IN, "S152_Mul_shift", 0),
            GNodeArg(GNA_IN, "S152_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_156 inq -0.28<(u8-31.00)*0.00896299<2.01 outq -0.28<(u8-31.00)*0.00896299<2.01
    AddNode("S153_CONCAT_0_156",
        Bindings(3,
            GNodeArg(GNA_IN, "S152_Output", 0),
            GNodeArg(GNA_IN, "S146_Output", 0),
            GNodeArg(GNA_OUT, "S153_Output", 0)
        )
    );
    // Node S156_CONV_2D_0_157_fusion inq -0.28<(u8-31.00)*0.00896299<2.01 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-22.00)*0.01289790<3.01 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S156_CONV_2D_0_157_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S153_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst7", 0),
            GNodeArg(GNA_IN, "Arith_constant43", 0),
            GNodeArg(GNA_OUT, "S156_Output", 0),
            GNodeArg(GNA_IN, "S156_Mul_scale", 0),
            GNodeArg(GNA_IN, "S156_Mul_shift", 0),
            GNodeArg(GNA_IN, "S156_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S159_CONV_2D_0_161_fusion inq -0.28<(u8-22.00)*0.01289790<3.01 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-32.00)*0.00859755<1.92 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S159_CONV_2D_0_161_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S156_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst6", 0),
            GNodeArg(GNA_IN, "Arith_constant42", 0),
            GNodeArg(GNA_OUT, "S159_Output", 0),
            GNodeArg(GNA_IN, "S159_Mul_scale", 0),
            GNodeArg(GNA_IN, "S159_Mul_shift", 0),
            GNodeArg(GNA_IN, "S159_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_164 inq -0.28<(u8-32.00)*0.00859755<1.92 outq -0.28<(u8-32.00)*0.00859755<1.92
    AddNode("S160_CONCAT_0_164",
        Bindings(3,
            GNodeArg(GNA_IN, "S159_Output", 0),
            GNodeArg(GNA_IN, "S102_Output", 0),
            GNodeArg(GNA_OUT, "S160_Output", 0)
        )
    );
    // Node S163_CONV_2D_0_165_fusion inq -0.28<(u8-32.00)*0.00859755<1.92 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-39.00)*0.00710736<1.54 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S163_CONV_2D_0_165_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S160_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst5", 0),
            GNodeArg(GNA_IN, "Arith_constant41", 0),
            GNodeArg(GNA_OUT, "S163_Output", 0),
            GNodeArg(GNA_IN, "S163_Mul_scale", 0),
            GNodeArg(GNA_IN, "S163_Mul_shift", 0),
            GNodeArg(GNA_IN, "S163_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONV_2D_0_165_split inq -0.28<(u8-39.00)*0.00710736<1.54 outq -0.28<(u8-39.00)*0.00710736<1.54
    AddNode("S164_CONV_2D_0_165_split",
        Bindings(3,
            GNodeArg(GNA_IN, "S163_Output", 0),
            GNodeArg(GNA_OUT, "S164_Output_0", 0),
            GNodeArg(GNA_OUT, "S164_Output_1", 0)
        )
    );
    // Node S167_CONV_2D_0_168_fusion inq -0.28<(u8-39.00)*0.00710736<1.54 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-34.00)*0.00819292<1.81 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S167_CONV_2D_0_168_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S164_Output_0", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst4", 0),
            GNodeArg(GNA_IN, "Arith_constant40", 0),
            GNodeArg(GNA_OUT, "S167_Output", 0),
            GNodeArg(GNA_IN, "S167_Mul_scale", 0),
            GNodeArg(GNA_IN, "S167_Mul_shift", 0),
            GNodeArg(GNA_IN, "S167_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S170_CONV_2D_0_171_fusion inq -0.28<(u8-34.00)*0.00819292<1.81 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-39.00)*0.00710736<1.54 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S170_CONV_2D_0_171_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S167_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst3", 0),
            GNodeArg(GNA_IN, "Arith_constant39", 0),
            GNodeArg(GNA_OUT, "S170_Output", 0),
            GNodeArg(GNA_IN, "S170_Mul_scale", 0),
            GNodeArg(GNA_IN, "S170_Mul_shift", 0),
            GNodeArg(GNA_IN, "S170_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_177 inq -0.28<(u8-39.00)*0.00710736<1.54 outq -0.28<(u8-39.00)*0.00710736<1.54
    AddNode("S171_CONCAT_0_177",
        Bindings(3,
            GNodeArg(GNA_IN, "S170_Output", 0),
            GNodeArg(GNA_IN, "S164_Output_1", 0),
            GNodeArg(GNA_OUT, "S171_Output", 0)
        )
    );
    // Node S174_CONV_2D_0_178_fusion inq -0.28<(u8-39.00)*0.00710736<1.54 weightsq chan<(u8-128.00)*chan<chan outq -0.28<(u8-31.00)*0.00901974<2.02 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S174_CONV_2D_0_178_fusion",
        Bindings(8,
            GNodeArg(GNA_IN, "S171_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst1", 0),
            GNodeArg(GNA_IN, "Arith_constant37", 0),
            GNodeArg(GNA_OUT, "S174_Output", 0),
            GNodeArg(GNA_IN, "S174_Mul_scale", 0),
            GNodeArg(GNA_IN, "S174_Mul_shift", 0),
            GNodeArg(GNA_IN, "S174_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S177_CONV_2D_0_181 inq -0.28<(u8-31.00)*0.00901974<2.02 weightsq chan<(u8-128.00)*chan<chan outq -6.29<(u8-128.00)*0.04913386<6.24 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S177_CONV_2D_0_181",
        Bindings(7,
            GNodeArg(GNA_IN, "S174_Output", 0),
            GNodeArg(GNA_IN, "Tfl_pseudo_qconst", 0),
            GNodeArg(GNA_IN, "Arith_constant36", 0),
            GNodeArg(GNA_OUT, "S177_Output", 0),
            GNodeArg(GNA_IN, "S177_Mul_scale", 0),
            GNodeArg(GNA_IN, "S177_Mul_shift", 0),
            GNodeArg(GNA_IN, "S177_Infos", 0)
        )
    );
    // Node STRIDED_SLICE_0_183_split inq -6.29<(u8-128.00)*0.04913386<6.24 forced outq -6.29<(u8-128.00)*0.04913386<6.24 forced
    AddNode("S179_STRIDED_SLICE_0_183_split",
        Bindings(4,
            GNodeArg(GNA_IN, "S177_Output", 0),
            GNodeArg(GNA_OUT, "S179_Output_0", 0),
            GNodeArg(GNA_OUT, "S179_Output_1", 0),
            GNodeArg(GNA_OUT, "S179_Output_2", 0)
        )
    );
    // Node LOGISTIC_0_195 inq -6.29<(u8-128.00)*0.04913386<6.24 forced outq 0.00<(u8-0.00)*0.00392157<1.00
    AddNode("S180_LOGISTIC_0_195",
        Bindings(4,
            GNodeArg(GNA_IN, "S179_Output_2", 0),
            GNodeArg(GNA_OUT, "S180_Output", 0),
            GNodeArg(GNA_IN, "S180_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUT_u8", 0)
        )
    );
    // Node expr_1 in_qs [-6.29<(u8-128.00)*0.04913386<6.24,-4.54<(i8-0.00)*0.03543307<4.50,-0.01<(i8-0.00)*0.00004101<0.01] out_qs [0.00<(u8-0.00)*0.00392157<1.00]
    AddNode("S184_expr_1",
        Bindings(5,
            GNodeArg(GNA_IN, "S179_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant18", 0),
            GNodeArg(GNA_IN, "Arith_constant20", 0),
            GNodeArg(GNA_OUT, "S184_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node S188_CONV_2D_0_198 inq -0.28<(u8-22.00)*0.01289790<3.01 weightsq chan<(u8-128.00)*chan<chan outq -6.29<(u8-128.00)*0.04913386<6.24 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S188_CONV_2D_0_198",
        Bindings(7,
            GNodeArg(GNA_IN, "S156_Output", 0),
            GNodeArg(GNA_IN, "Arith_constant88", 0),
            GNodeArg(GNA_IN, "Arith_constant35", 0),
            GNodeArg(GNA_OUT, "S188_Output", 0),
            GNodeArg(GNA_IN, "S188_Mul_scale", 0),
            GNodeArg(GNA_IN, "S188_Mul_shift", 0),
            GNodeArg(GNA_IN, "S188_Infos", 0)
        )
    );
    // Node STRIDED_SLICE_0_200_split inq -6.29<(u8-128.00)*0.04913386<6.24 forced outq -6.29<(u8-128.00)*0.04913386<6.24 forced
    AddNode("S190_STRIDED_SLICE_0_200_split",
        Bindings(4,
            GNodeArg(GNA_IN, "S188_Output", 0),
            GNodeArg(GNA_OUT, "S190_Output_0", 0),
            GNodeArg(GNA_OUT, "S190_Output_1", 0),
            GNodeArg(GNA_OUT, "S190_Output_2", 0)
        )
    );
    // Node LOGISTIC_0_212 inq -6.29<(u8-128.00)*0.04913386<6.24 forced outq 0.00<(u8-0.00)*0.00392157<1.00
    AddNode("S191_LOGISTIC_0_212",
        Bindings(4,
            GNodeArg(GNA_IN, "S190_Output_2", 0),
            GNodeArg(GNA_OUT, "S191_Output", 0),
            GNodeArg(GNA_IN, "S191_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUT_u8", 0)
        )
    );
    // Node CONCAT_0_213_reshape_2_qout0 inq 0.00<(u8-0.00)*0.00392157<1.00 outq -1.02<(u8-128.00)*0.00793623<1.01 forced
    AddNode("S193_CONCAT_0_213_reshape_2_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S191_Output", 0),
            GNodeArg(GNA_OUT, "S193_Output", 0),
            GNodeArg(GNA_IN, "S193_Infos", 0)
        )
    );
    // Node S198_CONV_2D_0_215 inq -0.28<(u8-19.00)*0.01448963<3.42 weightsq chan<(u8-128.00)*chan<chan outq -6.29<(u8-128.00)*0.04913386<6.24 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S198_CONV_2D_0_215",
        Bindings(7,
            GNodeArg(GNA_IN, "S137_Output", 0),
            GNodeArg(GNA_IN, "Arith_constant87", 0),
            GNodeArg(GNA_IN, "Arith_constant34", 0),
            GNodeArg(GNA_OUT, "S198_Output", 0),
            GNodeArg(GNA_IN, "S198_Mul_scale", 0),
            GNodeArg(GNA_IN, "S198_Mul_shift", 0),
            GNodeArg(GNA_IN, "S198_Infos", 0)
        )
    );
    // Node STRIDED_SLICE_0_217_split inq -6.29<(u8-128.00)*0.04913386<6.24 forced outq -6.29<(u8-128.00)*0.04913386<6.24 forced
    AddNode("S200_STRIDED_SLICE_0_217_split",
        Bindings(4,
            GNodeArg(GNA_IN, "S198_Output", 0),
            GNodeArg(GNA_OUT, "S200_Output_0", 0),
            GNodeArg(GNA_OUT, "S200_Output_1", 0),
            GNodeArg(GNA_OUT, "S200_Output_2", 0)
        )
    );
    // Node LOGISTIC_0_229 inq -6.29<(u8-128.00)*0.04913386<6.24 forced outq 0.00<(u8-0.00)*0.00392157<1.00
    AddNode("S201_LOGISTIC_0_229",
        Bindings(4,
            GNodeArg(GNA_IN, "S200_Output_2", 0),
            GNodeArg(GNA_OUT, "S201_Output", 0),
            GNodeArg(GNA_IN, "S201_Infos", 0),
            GNodeArg(GNA_IN, "SigmoidLUT_u8", 0)
        )
    );
    // Node expr_32 in_qs [-6.29<(u8-128.00)*0.04913386<6.24,-264.57<(i8-0.00)*2.06692913<262.50,-0.01<(i8-0.00)*0.00004101<0.01] out_qs [0.00<(u8-0.00)*0.00392157<1.00]
    AddNode("S206_expr_32",
        Bindings(5,
            GNodeArg(GNA_IN, "S179_Output_1", 0),
            GNodeArg(GNA_IN, "Arith_constant19", 0),
            GNodeArg(GNA_IN, "Arith_constant20_1", 0),
            GNodeArg(GNA_OUT, "S206_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_196 inq 0.00<(u8-0.00)*0.00392157<1.00 outq 0.00<(u8-0.00)*0.00392157<1.00
    AddNode("S207_CONCAT_0_196",
        Bindings(4,
            GNodeArg(GNA_IN, "S184_Output", 0),
            GNodeArg(GNA_IN, "S206_Output", 0),
            GNodeArg(GNA_IN, "S180_Output", 0),
            GNodeArg(GNA_OUT, "S207_Output", 0)
        )
    );
    // Node RESHAPE_0_197_qout0 inq 0.00<(u8-0.00)*0.00392157<1.00 outq -1.02<(u8-128.00)*0.00793623<1.01 forced
    AddNode("S209_RESHAPE_0_197_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S207_Output", 0),
            GNodeArg(GNA_OUT, "S209_Output", 0),
            GNodeArg(GNA_IN, "S209_Infos", 0)
        )
    );
    // Node expr_2 in_qs [-6.29<(u8-128.00)*0.04913386<6.24,-10.58<(i8-0.00)*0.08267717<10.50,-0.01<(i8-0.00)*0.00004101<0.01] out_qs [-1.02<(u8-128.00)*0.00793623<1.01 forced]
    AddNode("S211_expr_2",
        Bindings(5,
            GNodeArg(GNA_IN, "S190_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant16", 0),
            GNodeArg(GNA_IN, "Arith_constant20_2", 0),
            GNodeArg(GNA_OUT, "S211_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node expr_34 in_qs [-6.29<(u8-128.00)*0.04913386<6.24,-83.59<(i8-0.00)*0.65305118<82.94,-0.01<(i8-0.00)*0.00004101<0.01] out_qs [-1.02<(u8-128.00)*0.00793623<1.01 forced]
    AddNode("S213_expr_34",
        Bindings(5,
            GNodeArg(GNA_IN, "S190_Output_1", 0),
            GNodeArg(GNA_IN, "Arith_constant17", 0),
            GNodeArg(GNA_IN, "Arith_constant20_3", 0),
            GNodeArg(GNA_OUT, "S213_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_213 inq -1.02<(u8-128.00)*0.00793623<1.01 forced outq -1.02<(u8-128.00)*0.00793623<1.01 forced
    AddNode("S214_CONCAT_0_213",
        Bindings(4,
            GNodeArg(GNA_IN, "S211_Output", 0),
            GNodeArg(GNA_IN, "S213_Output", 0),
            GNodeArg(GNA_IN, "S193_Output", 0),
            GNodeArg(GNA_OUT, "S214_Output", 0)
        )
    );
    // Node expr_3 in_qs [-6.29<(u8-128.00)*0.04913386<6.24,-22.68<(i8-0.00)*0.17716535<22.50,-0.01<(i8-0.00)*0.00004101<0.01] out_qs [0.00<(u8-0.00)*0.00392157<1.00]
    AddNode("S217_expr_3",
        Bindings(5,
            GNodeArg(GNA_IN, "S200_Output_0", 0),
            GNodeArg(GNA_IN, "Arith_constant14", 0),
            GNodeArg(GNA_IN, "Arith_constant20_4", 0),
            GNodeArg(GNA_OUT, "S217_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node expr_35 in_qs [-6.29<(u8-128.00)*0.04913386<6.24,-34.55<(i8-0.00)*0.26993110<34.28,-0.01<(i8-0.00)*0.00004101<0.01] out_qs [0.00<(u8-0.00)*0.00392157<1.00]
    AddNode("S219_expr_35",
        Bindings(5,
            GNodeArg(GNA_IN, "S200_Output_1", 0),
            GNodeArg(GNA_IN, "Arith_constant15", 0),
            GNodeArg(GNA_IN, "Arith_constant20_5", 0),
            GNodeArg(GNA_OUT, "S219_Output", 0),
            GNodeArg(GNA_IN, "SigmoidLUTTable", 0)
        )
    );
    // Node CONCAT_0_230 inq 0.00<(u8-0.00)*0.00392157<1.00 outq 0.00<(u8-0.00)*0.00392157<1.00
    AddNode("S220_CONCAT_0_230",
        Bindings(4,
            GNodeArg(GNA_IN, "S217_Output", 0),
            GNodeArg(GNA_IN, "S219_Output", 0),
            GNodeArg(GNA_IN, "S201_Output", 0),
            GNodeArg(GNA_OUT, "S220_Output", 0)
        )
    );
    // Node RESHAPE_0_231_qout0 inq 0.00<(u8-0.00)*0.00392157<1.00 outq -1.02<(u8-128.00)*0.00793623<1.01 forced
    AddNode("S222_RESHAPE_0_231_qout0",
        Bindings(3,
            GNodeArg(GNA_IN, "S220_Output", 0),
            GNodeArg(GNA_OUT, "S222_Output", 0),
            GNodeArg(GNA_IN, "S222_Infos", 0)
        )
    );
    // Node CONCAT_0_232_reshape_copy inq -1.02<(u8-128.00)*0.00793623<1.01 forced outq -1.02<(u8-128.00)*0.00793623<1.01 forced
    AddNode("S225_CONCAT_0_232_reshape_copy",
        Bindings(2,
            GNodeArg(GNA_IN, "S223_Output", 0),
            GNodeArg(GNA_OUT, "Output_1", 0)
        )
    );
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    YOLOv5Model(100000, 200000, 8000000, 64*1024*1024);
    GenerateTilingCode();
    return 0;
}
