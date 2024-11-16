#include "AutoTilerLib.h"
#include "CNN_Generators.h"
#include "CNN_Generators_NE16.h"
#include "CNN_Generators_SQ8.h"
#include "ResizeGenerator.h"
#include <stdint.h>
#include <stdio.h>

#include "CNN_Copy_Generators.h"

void load_expressions_kernels() {
  LibKernelTemplate("s18_kernel_args_t",
                    CArgs(5, TCArg("unsigned int", "I0"), TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
                          TCArg("unsigned char *__restrict__ ", "expr_0_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_0_in_1"),
                          TCArg("unsigned char *__restrict__ ", "expr_0_out_0")));

  LibKernel("s18_kernel", CALL_PARALLEL, 0, "s18_kernel_args_t", 0);
  LibKernelTemplate(
      "s255_kernel_args_t",
      CArgs(7, TCArg("unsigned int", "I0"), TCArg("signed char *__restrict__ ", "expr_1_in_0"),
            TCArg("unsigned char *__restrict__ ", "expr_1_in_1"), TCArg("unsigned char *__restrict__ ", "expr_1_in_2"),
            TCArg("signed char *__restrict__ ", "expr_1_in_3"), TCArg("signed char *__restrict__ ", "expr_1_out_0"),
            TCArg("signed char *__restrict__ ", "expr_1_out_1")));

  LibKernel("s255_kernel", CALL_PARALLEL, 0, "s255_kernel_args_t", 0);
  LibKernelTemplate("s37_kernel_args_t",
                    CArgs(5, TCArg("unsigned int", "I0"), TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
                          TCArg("unsigned char *__restrict__ ", "expr_2_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_2_in_1"),
                          TCArg("unsigned char *__restrict__ ", "expr_2_out_0")));

  LibKernel("s37_kernel", CALL_PARALLEL, 0, "s37_kernel_args_t", 0);
  LibKernelTemplate("s56_kernel_args_t",
                    CArgs(5, TCArg("unsigned int", "I0"), TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
                          TCArg("unsigned char *__restrict__ ", "expr_3_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_3_in_1"),
                          TCArg("unsigned char *__restrict__ ", "expr_3_out_0")));

  LibKernel("s56_kernel", CALL_PARALLEL, 0, "s56_kernel_args_t", 0);
  LibKernelTemplate("s76_kernel_args_t",
                    CArgs(5, TCArg("unsigned int", "I0"), TCArg("unsigned short int *__restrict__ ", "SigmoidLUTTable"),
                          TCArg("unsigned char *__restrict__ ", "expr_4_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_4_in_1"),
                          TCArg("unsigned char *__restrict__ ", "expr_4_out_0")));

  LibKernel("s76_kernel", CALL_PARALLEL, 0, "s76_kernel_args_t", 0);
  LibKernelTemplate("s257_kernel_args_t", CArgs(5, TCArg("unsigned int", "I0"), TCArg("unsigned int", "I1"),
                                                TCArg("signed char *__restrict__ ", "expr_64_in_0"),
                                                TCArg("signed char *__restrict__ ", "expr_64_in_1"),
                                                TCArg("signed char *__restrict__ ", "expr_64_out_0")));

  LibKernel("s257_kernel", CALL_PARALLEL, 0, "s257_kernel_args_t", 0);
  LibKernelTemplate("expr_44_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_44_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_44_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_44", CALL_PARALLEL, 0, "expr_44_args_t", 0);
  LibKernelTemplate("expr_55_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_55_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_55_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_55", CALL_PARALLEL, 0, "expr_55_args_t", 0);
  LibKernelTemplate("expr_13_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_13_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_13_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_13", CALL_PARALLEL, 0, "expr_13_args_t", 0);
  LibKernelTemplate("expr_23_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_23_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_23_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_23", CALL_PARALLEL, 0, "expr_23_args_t", 0);
  LibKernelTemplate("expr_42_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_42_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_42_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_42", CALL_PARALLEL, 0, "expr_42_args_t", 0);
  LibKernelTemplate("expr_43_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_43_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_43_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_43", CALL_PARALLEL, 0, "expr_43_args_t", 0);
  LibKernelTemplate("expr_45_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_45_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_45_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_45", CALL_PARALLEL, 0, "expr_45_args_t", 0);
  LibKernelTemplate("expr_46_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_46_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_46_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_46", CALL_PARALLEL, 0, "expr_46_args_t", 0);
  LibKernelTemplate("expr_48_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_48_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_48_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_48", CALL_PARALLEL, 0, "expr_48_args_t", 0);
  LibKernelTemplate("expr_49_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_49_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_49_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_49", CALL_PARALLEL, 0, "expr_49_args_t", 0);
  LibKernelTemplate("expr_50_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_50_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_50_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_50", CALL_PARALLEL, 0, "expr_50_args_t", 0);
  LibKernelTemplate("expr_51_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_51_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_51_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_51", CALL_PARALLEL, 0, "expr_51_args_t", 0);
  LibKernelTemplate("expr_53_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_53_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_53_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_53", CALL_PARALLEL, 0, "expr_53_args_t", 0);
  LibKernelTemplate("expr_54_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_54_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_54_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_54", CALL_PARALLEL, 0, "expr_54_args_t", 0);
  LibKernelTemplate("expr_56_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_56_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_56_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_56", CALL_PARALLEL, 0, "expr_56_args_t", 0);
  LibKernelTemplate("expr_57_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_57_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_57_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_57", CALL_PARALLEL, 0, "expr_57_args_t", 0);
  LibKernelTemplate("expr_59_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_59_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_59_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_59", CALL_PARALLEL, 0, "expr_59_args_t", 0);
  LibKernelTemplate("expr_60_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_60_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_60_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_60", CALL_PARALLEL, 0, "expr_60_args_t", 0);
  LibKernelTemplate("expr_61_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_61_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_61_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_61", CALL_PARALLEL, 0, "expr_61_args_t", 0);
  LibKernelTemplate("expr_62_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_62_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_62_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_62", CALL_PARALLEL, 0, "expr_62_args_t", 0);
  LibKernelTemplate("expr_5_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_5_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_5_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_5", CALL_PARALLEL, 0, "expr_5_args_t", 0);
  LibKernelTemplate("expr_6_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_6_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_6_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_6", CALL_PARALLEL, 0, "expr_6_args_t", 0);
  LibKernelTemplate("expr_7_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_7_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_7_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_7", CALL_PARALLEL, 0, "expr_7_args_t", 0);
  LibKernelTemplate("expr_9_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_9_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_9_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_9", CALL_PARALLEL, 0, "expr_9_args_t", 0);
  LibKernelTemplate("expr_10_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_10_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_10_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_10", CALL_PARALLEL, 0, "expr_10_args_t", 0);
  LibKernelTemplate("expr_11_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_11_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_11_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_11", CALL_PARALLEL, 0, "expr_11_args_t", 0);
  LibKernelTemplate("expr_12_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_12_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_12_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_12", CALL_PARALLEL, 0, "expr_12_args_t", 0);
  LibKernelTemplate("expr_14_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_14_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_14_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_14", CALL_PARALLEL, 0, "expr_14_args_t", 0);
  LibKernelTemplate("expr_16_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_16_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_16_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_16", CALL_PARALLEL, 0, "expr_16_args_t", 0);
  LibKernelTemplate("expr_17_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_17_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_17_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_17", CALL_PARALLEL, 0, "expr_17_args_t", 0);
  LibKernelTemplate("expr_18_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_18_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_18_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_18", CALL_PARALLEL, 0, "expr_18_args_t", 0);
  LibKernelTemplate("expr_19_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_19_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_19_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_19", CALL_PARALLEL, 0, "expr_19_args_t", 0);
  LibKernelTemplate("expr_20_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_20_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_20_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_20", CALL_PARALLEL, 0, "expr_20_args_t", 0);
  LibKernelTemplate("expr_21_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_21_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_21_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_21", CALL_PARALLEL, 0, "expr_21_args_t", 0);
  LibKernelTemplate("expr_22_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_22_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_22_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_22", CALL_PARALLEL, 0, "expr_22_args_t", 0);
  LibKernelTemplate("expr_25_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_25_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_25_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_25", CALL_PARALLEL, 0, "expr_25_args_t", 0);
  LibKernelTemplate("expr_26_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_26_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_26_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_26", CALL_PARALLEL, 0, "expr_26_args_t", 0);
  LibKernelTemplate("expr_27_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_27_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_27_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_27", CALL_PARALLEL, 0, "expr_27_args_t", 0);
  LibKernelTemplate("expr_28_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_28_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_28_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_28", CALL_PARALLEL, 0, "expr_28_args_t", 0);
  LibKernelTemplate("expr_29_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_29_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_29_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_29", CALL_PARALLEL, 0, "expr_29_args_t", 0);
  LibKernelTemplate("expr_30_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_30_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_30_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_30", CALL_PARALLEL, 0, "expr_30_args_t", 0);
  LibKernelTemplate("expr_31_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_31_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_31_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_31", CALL_PARALLEL, 0, "expr_31_args_t", 0);
  LibKernelTemplate("expr_32_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_32_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_32_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_32", CALL_PARALLEL, 0, "expr_32_args_t", 0);
  LibKernelTemplate("expr_33_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_33_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_33_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_33", CALL_PARALLEL, 0, "expr_33_args_t", 0);
  LibKernelTemplate("expr_35_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_35_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_35_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_35", CALL_PARALLEL, 0, "expr_35_args_t", 0);
  LibKernelTemplate("expr_36_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_36_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_36_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_36", CALL_PARALLEL, 0, "expr_36_args_t", 0);
  LibKernelTemplate("expr_37_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_37_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_37_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_37", CALL_PARALLEL, 0, "expr_37_args_t", 0);
  LibKernelTemplate("expr_38_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_38_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_38_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_38", CALL_PARALLEL, 0, "expr_38_args_t", 0);
  LibKernelTemplate("expr_39_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_39_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_39_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_39", CALL_PARALLEL, 0, "expr_39_args_t", 0);
  LibKernelTemplate("expr_40_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_40_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_40_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_40", CALL_PARALLEL, 0, "expr_40_args_t", 0);
  LibKernelTemplate("expr_41_args_t",
                    CArgs(6, TCArg("unsigned char *__restrict__ ", "expr_41_in_0"),
                          TCArg("unsigned char *__restrict__ ", "expr_41_out_0"), TCArg("unsigned short int", "W"),
                          TCArg("unsigned short int", "H"), TCArg("unsigned short int", "Feat"),
                          TCArg("unsigned short * __restrict__", "SigmoidLUTTable")));

  LibKernel("expr_41", CALL_PARALLEL, 0, "expr_41_args_t", 0);
}

int s18_kernel_gen(char *Name) {
  Kernel_T *Kernel = UserKernel(
      Name,
      // shape: (64, 64, 8) spaces: ((0, 1, 2),)
      // parametric_spaces: ((0, 1, 2),)
      // exterior_shape: (32768.0,)
      KernelIterSpace(2, IterParSpace(KER_ITER_D0, 32768, 8), IterTiledSpace(KER_ITER_TILE0)), TILE_VER,
      CArgs(4, TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_0_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_0_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_0_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")),
      Calls(1, Call("s18_kernel", LOC_D0,
                    Bindings(5, K_ArgPar("expr_0_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                             K_Arg("SigmoidLUTTable", KER_ARG_TILE), K_Arg("expr_0_in_0", KER_ARG_TILE),
                             K_Arg("expr_0_in_1", KER_ARG_TILE), K_Arg("expr_0_out_0", KER_ARG_TILE)))),
      // var: expr_0_out_0 axes: (0,)
      // var: expr_0_in_1 axes: (0,)
      // var: expr_0_in_0 axes: (0,)
      KerArgs(4, KerArg("expr_0_out_0", KerArgSpace(1, KER_ITER_D0), O_OUT | O_DB, 1, 1, 1, 0, 0, 0, "expr_0_out_0"),
              KerArg("expr_0_in_1", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_0_in_1"),
              KerArg("expr_0_in_0", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_0_in_0"),
              KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN | O_BUFF | O_NTILED | O_CONST, 1, 1, 512,
                     0, 0, 0, "SigmoidLUTTable")));
  if (Kernel) {
    AddKernelInfos(Name, AT_KERINFO_OPER, 98304, 0);
    AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 98560, 0);
    AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256, 2);
    AddKernelArgDimExplicit(Name, "expr_0_in_0", ARG_INT, 4, 64, 64, 8, 1);
    AddKernelArgDimExplicit(Name, "expr_0_in_1", ARG_INT, 4, 64, 64, 8, 1);
    AddKernelArgDimExplicit(Name, "expr_0_out_0", ARG_INT, 4, 64, 64, 8, 1);
  }
  return (Kernel != 0);
}
int s255_kernel_gen(char *Name) {
  Kernel_T *Kernel = UserKernel(
      Name,
      // shape: (2, 1, 1344) spaces: ((0, 2),)
      // parametric_spaces: ((0, 2),)
      // exterior_shape: (2688.0,)
      KernelIterSpace(2, IterParSpace(KER_ITER_D0, 2688, 8), IterTiledSpace(KER_ITER_TILE0)), TILE_VER,
      CArgs(6, TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_1_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_1_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_1_in_2"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_1_in_3"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_1_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_1_out_1")),
      Calls(1, Call("s255_kernel", LOC_D0,
                    Bindings(7, K_ArgPar("expr_1_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                             K_Arg("expr_1_in_0", KER_ARG_TILE), K_Arg("expr_1_in_1", KER_ARG_TILE),
                             K_Arg("expr_1_in_2", KER_ARG_TILE), K_Arg("expr_1_in_3", KER_ARG_TILE),
                             K_Arg("expr_1_out_0", KER_ARG_TILE), K_Arg("expr_1_out_1", KER_ARG_TILE)))),
      // var: expr_1_in_0 axes: (0,)
      // var: expr_1_in_1 axes: (0,)
      // var: expr_1_in_2 axes: (0,)
      // var: expr_1_in_3 axes: (0,)
      // var: expr_1_out_0 axes: (0,)
      // var: expr_1_out_1 axes: (0,)
      KerArgs(6, KerArg("expr_1_in_0", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_1_in_0"),
              KerArg("expr_1_in_1", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_1_in_1"),
              KerArg("expr_1_in_2", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_1_in_2"),
              KerArg("expr_1_in_3", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_1_in_3"),
              KerArg("expr_1_out_0", KerArgSpace(1, KER_ITER_D0), O_OUT | O_DB, 1, 1, 1, 0, 0, 0, "expr_1_out_0"),
              KerArg("expr_1_out_1", KerArgSpace(1, KER_ITER_D0), O_OUT | O_DB, 1, 1, 1, 0, 0, 0, "expr_1_out_1")));
  if (Kernel) {
    AddKernelInfos(Name, AT_KERINFO_OPER, 26880, 0);
    AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 16128, 0);
    AddKernelArgDimExplicit(Name, "expr_1_in_0", ARG_INT, 4, 2, 1, 1344, 1);
    AddKernelArgDimExplicit(Name, "expr_1_in_1", ARG_INT, 4, 2, 1, 1344, 1);
    AddKernelArgDimExplicit(Name, "expr_1_in_2", ARG_INT, 4, 2, 1, 1344, 1);
    AddKernelArgDimExplicit(Name, "expr_1_in_3", ARG_INT, 4, 2, 1, 1344, 1);
    AddKernelArgDimExplicit(Name, "expr_1_out_0", ARG_INT, 4, 2, 1, 1344, 1);
    AddKernelArgDimExplicit(Name, "expr_1_out_1", ARG_INT, 4, 2, 1, 1344, 1);
  }
  return (Kernel != 0);
}
int s37_kernel_gen(char *Name) {
  Kernel_T *Kernel = UserKernel(
      Name,
      // shape: (32, 32, 16) spaces: ((0, 1, 2),)
      // parametric_spaces: ((0, 1, 2),)
      // exterior_shape: (16384.0,)
      KernelIterSpace(2, IterParSpace(KER_ITER_D0, 16384, 8), IterTiledSpace(KER_ITER_TILE0)), TILE_VER,
      CArgs(4, TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_2_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_2_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_2_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")),
      Calls(1, Call("s37_kernel", LOC_D0,
                    Bindings(5, K_ArgPar("expr_2_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                             K_Arg("SigmoidLUTTable", KER_ARG_TILE), K_Arg("expr_2_in_0", KER_ARG_TILE),
                             K_Arg("expr_2_in_1", KER_ARG_TILE), K_Arg("expr_2_out_0", KER_ARG_TILE)))),
      // var: expr_2_out_0 axes: (0,)
      // var: expr_2_in_1 axes: (0,)
      // var: expr_2_in_0 axes: (0,)
      KerArgs(4, KerArg("expr_2_out_0", KerArgSpace(1, KER_ITER_D0), O_OUT | O_DB, 1, 1, 1, 0, 0, 0, "expr_2_out_0"),
              KerArg("expr_2_in_1", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_2_in_1"),
              KerArg("expr_2_in_0", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_2_in_0"),
              KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN | O_BUFF | O_NTILED | O_CONST, 1, 1, 512,
                     0, 0, 0, "SigmoidLUTTable")));
  if (Kernel) {
    AddKernelInfos(Name, AT_KERINFO_OPER, 49152, 0);
    AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 49408, 0);
    AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256, 2);
    AddKernelArgDimExplicit(Name, "expr_2_in_0", ARG_INT, 4, 32, 32, 16, 1);
    AddKernelArgDimExplicit(Name, "expr_2_in_1", ARG_INT, 4, 32, 32, 16, 1);
    AddKernelArgDimExplicit(Name, "expr_2_out_0", ARG_INT, 4, 32, 32, 16, 1);
  }
  return (Kernel != 0);
}
int s56_kernel_gen(char *Name) {
  Kernel_T *Kernel = UserKernel(
      Name,
      // shape: (16, 16, 28) spaces: ((0, 1, 2),)
      // parametric_spaces: ((0, 1, 2),)
      // exterior_shape: (7168.0,)
      KernelIterSpace(2, IterParSpace(KER_ITER_D0, 7168, 8), IterTiledSpace(KER_ITER_TILE0)), TILE_VER,
      CArgs(4, TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_3_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_3_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_3_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")),
      Calls(1, Call("s56_kernel", LOC_D0,
                    Bindings(5, K_ArgPar("expr_3_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                             K_Arg("SigmoidLUTTable", KER_ARG_TILE), K_Arg("expr_3_in_0", KER_ARG_TILE),
                             K_Arg("expr_3_in_1", KER_ARG_TILE), K_Arg("expr_3_out_0", KER_ARG_TILE)))),
      // var: expr_3_out_0 axes: (0,)
      // var: expr_3_in_1 axes: (0,)
      // var: expr_3_in_0 axes: (0,)
      KerArgs(4, KerArg("expr_3_out_0", KerArgSpace(1, KER_ITER_D0), O_OUT | O_DB, 1, 1, 1, 0, 0, 0, "expr_3_out_0"),
              KerArg("expr_3_in_1", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_3_in_1"),
              KerArg("expr_3_in_0", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_3_in_0"),
              KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN | O_BUFF | O_NTILED | O_CONST, 1, 1, 512,
                     0, 0, 0, "SigmoidLUTTable")));
  if (Kernel) {
    AddKernelInfos(Name, AT_KERINFO_OPER, 21504, 0);
    AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 21760, 0);
    AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256, 2);
    AddKernelArgDimExplicit(Name, "expr_3_in_0", ARG_INT, 4, 16, 16, 28, 1);
    AddKernelArgDimExplicit(Name, "expr_3_in_1", ARG_INT, 4, 16, 16, 28, 1);
    AddKernelArgDimExplicit(Name, "expr_3_out_0", ARG_INT, 4, 16, 16, 28, 1);
  }
  return (Kernel != 0);
}
int s76_kernel_gen(char *Name) {
  Kernel_T *Kernel = UserKernel(
      Name,
      // shape: (8, 8, 52) spaces: ((0, 1, 2),)
      // parametric_spaces: ((0, 1, 2),)
      // exterior_shape: (3328.0,)
      KernelIterSpace(2, IterParSpace(KER_ITER_D0, 3328, 8), IterTiledSpace(KER_ITER_TILE0)), TILE_VER,
      CArgs(4, TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_4_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_4_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(-1, 1, 1, ARG_INT), "expr_4_out_0"),
            TCArg(CNN_ArgDataTypeExplicit(-2, 1, 1, ARG_INT), "SigmoidLUTTable")),
      Calls(1, Call("s76_kernel", LOC_D0,
                    Bindings(5, K_ArgPar("expr_4_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                             K_Arg("SigmoidLUTTable", KER_ARG_TILE), K_Arg("expr_4_in_0", KER_ARG_TILE),
                             K_Arg("expr_4_in_1", KER_ARG_TILE), K_Arg("expr_4_out_0", KER_ARG_TILE)))),
      // var: expr_4_out_0 axes: (0,)
      // var: expr_4_in_1 axes: (0,)
      // var: expr_4_in_0 axes: (0,)
      KerArgs(4, KerArg("expr_4_out_0", KerArgSpace(1, KER_ITER_D0), O_OUT | O_DB, 1, 1, 1, 0, 0, 0, "expr_4_out_0"),
              KerArg("expr_4_in_1", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_4_in_1"),
              KerArg("expr_4_in_0", KerArgSpace(1, KER_ITER_D0), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_4_in_0"),
              KerArg("SigmoidLUTTable", KerArgSpace(1, KER_ITER_TILE0), O_IN | O_BUFF | O_NTILED | O_CONST, 1, 1, 512,
                     0, 0, 0, "SigmoidLUTTable")));
  if (Kernel) {
    AddKernelInfos(Name, AT_KERINFO_OPER, 9984, 0);
    AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 10240, 0);
    AddKernelArgDimExplicit(Name, "SigmoidLUTTable", ARG_INT, 2, 256, 2);
    AddKernelArgDimExplicit(Name, "expr_4_in_0", ARG_INT, 4, 8, 8, 52, 1);
    AddKernelArgDimExplicit(Name, "expr_4_in_1", ARG_INT, 4, 8, 8, 52, 1);
    AddKernelArgDimExplicit(Name, "expr_4_out_0", ARG_INT, 4, 8, 8, 52, 1);
  }
  return (Kernel != 0);
}
int s257_kernel_gen(char *Name) {
  Kernel_T *Kernel = UserKernel(
      Name,
      // shape: (4, 1, 1344) spaces: ((0,), (2,))
      // parametric_spaces: ((0,), (2,))
      // exterior_shape: (4, 1344.0)
      KernelIterSpace(3, IterParSpace(KER_ITER_D0, 4, 1), IterParSpace(KER_ITER_D1, 1344, 8),
                      IterTiledSpace(KER_ITER_TILE0)),
      TILE_VER,
      CArgs(3, TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_64_in_0"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_64_in_1"),
            TCArg(CNN_ArgDataTypeExplicit(1, 1, 1, ARG_INT), "expr_64_out_0")),
      Calls(1, Call("s257_kernel", LOC_D1,
                    Bindings(5, K_ArgPar("expr_64_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D0),
                             K_ArgPar("expr_64_out_0", KER_ARG_PARTILE_SIZE, KER_ITER_D1),
                             K_Arg("expr_64_in_0", KER_ARG_TILE), K_Arg("expr_64_in_1", KER_ARG_TILE),
                             K_Arg("expr_64_out_0", KER_ARG_TILE)))),
      // var: expr_64_out_0 axes: (0, 1)
      // var: expr_64_in_0 axes: (0, 1)
      // var: expr_64_in_1 axes: (1,)
      KerArgs(3,
              KerArg("expr_64_out_0", KerArgSpace(2, KER_ITER_D0, KER_ITER_D1), O_OUT | O_DB, 1, 1, 1, 0, 0, 0,
                     "expr_64_out_0"),
              KerArg("expr_64_in_0", KerArgSpace(2, KER_ITER_D0, KER_ITER_D1), O_IN | O_DB, 1, 1, 1, 0, 0, 0,
                     "expr_64_in_0"),
              KerArg("expr_64_in_1", KerArgSpace(1, KER_ITER_D1), O_IN | O_DB, 1, 1, 1, 0, 0, 0, "expr_64_in_1")));
  if (Kernel) {
    AddKernelInfos(Name, AT_KERINFO_OPER, 5376, 0);
    AddKernelInfos(Name, AT_KERINFO_BANDWIDTH, 12096, 0);
    AddKernelArgDimExplicit(Name, "expr_64_in_0", ARG_INT, 4, 4, 1, 1344, 1);
    AddKernelArgDimExplicit(Name, "expr_64_in_1", ARG_INT, 2, 1344, 1);
    AddKernelArgDimExplicit(Name, "expr_64_out_0", ARG_INT, 4, 4, 1, 1344, 1);
  }
  return (Kernel != 0);
}

void YOLOv5Model(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory, unsigned int L3Flash) {
  KernelOper_T Cop = KOP_CONV;

  // SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);
  SetSymbolDynamics();

  SetUsedFilesNames(0, 8, "at_api.h", "YOLOv5.h", "CNN_BasicKernels_SQ8.h", "CNN_BasicKernels.h",
                    "CNN_BasicKernels_NE16.h", "ResizeBasicKernels.h", "CNN_BasicKernels_SQ8.h",
                    "Expression_Kernels.h");
  SetGeneratedFilesNames("YOLOv5Kernels.c", "YOLOv5Kernels.h");
  AT_SetGraphCtrl(AT_GRAPH_MONITOR_CYCLES, AT_OPT_ON);
  AT_SetGraphCtrl(AT_GRAPH_PRODUCE_NODE_NAMES, AT_OPT_ON);
  AT_SetGraphCtrl(AT_GRAPH_PRODUCE_OPERINFOS, AT_OPT_ON);
  AT_SetGraphCtrl(AT_GRAPH_ASYNC_FORK, AT_OPT_ON);

  SetMemoryDeviceInfos(4, AT_MEM_L1, L1Memory, "YOLOv5_L1_Memory", 0, 0, AT_MEM_L2, L2Memory, "YOLOv5_L2_Memory", 0, 1,
                       AT_MEM_L3_DEFAULTRAM, L3Memory, "YOLOv5_L3_Memory", 0, 0, AT_MEM_L3_MRAMFLASH, L3Flash,
                       "YOLOv5_L3_Flash", "YOLOv5_L3_Flash_Const.dat", 0);

  LoadCNN_SQ8_Library();
  LoadCNNLibrary();
  LoadCNN_NE16_SQ8_Library();
  LoadResizeLibrary();
  LoadCNN_Copy_Library();
  load_expressions_kernels();

  CNN_GenControl_T gen_ctrl_S3_CONV_2D_0_1_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "ENABLEIM2COL", AT_OPT_VAL(1));
  CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "CUSTOM_ACTIVATION_NAME", "expr_44");
  CNN_ExtraActivationArgs_T gen_ctrl_S3_CONV_2D_0_1_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S3_CONV_2D_0_1_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S3_CONV_2D_0_1_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_1_fusion
  CNN_ConvolutionNE16("S3_CONV_2D_0_1_fusion", &gen_ctrl_S3_CONV_2D_0_1_fusion, -1, -1, 4, 1, 8, 3, 8, 256, 256,
                      KOP_CONV, 6, 6, 1, 1, 2, 2, 1, 0, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S6_CONV_2D_0_5_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion, "CUSTOM_ACTIVATION_NAME", "expr_55");
  CNN_ExtraActivationArgs_T gen_ctrl_S6_CONV_2D_0_5_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S6_CONV_2D_0_5_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S6_CONV_2D_0_5_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_5_fusion
  CNN_ConvolutionNE16("S6_CONV_2D_0_5_fusion", &gen_ctrl_S6_CONV_2D_0_5_fusion, -1, -1, 4, 1, 8, 8, 16, 128, 128,
                      KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 3, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S9_CONV_2D_0_8_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion, "CUSTOM_ACTIVATION_NAME", "expr_13");
  CNN_ExtraActivationArgs_T gen_ctrl_S9_CONV_2D_0_8_fusion_extra_activation_args = {1, {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S9_CONV_2D_0_8_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S9_CONV_2D_0_8_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_8_fusion
  CNN_ConvolutionNE16("S9_CONV_2D_0_8_fusion", &gen_ctrl_S9_CONV_2D_0_8_fusion, -1, -1, 4, 1, 8, 16, 16, 64, 64,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 1, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S10_CONV_2D_0_8_split;
  CNN_InitGenCtrl(&gen_ctrl_S10_CONV_2D_0_8_split);
  CNN_SetGenCtrl(&gen_ctrl_S10_CONV_2D_0_8_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S10_CONV_2D_0_8_split", &gen_ctrl_S10_CONV_2D_0_8_split, -1, 4096, 2, KOP_SPLIT, 8, 8);

  // generator for CONV_2D_0_8_split_copy_qout0
  CNN_Convert("S11_CONV_2D_0_8_split_copy_qout0", -1, -1, 32768, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S14_CONV_2D_0_14_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion, "CUSTOM_ACTIVATION_NAME", "expr_23");
  CNN_ExtraActivationArgs_T gen_ctrl_S14_CONV_2D_0_14_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S14_CONV_2D_0_14_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S14_CONV_2D_0_14_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_14_fusion
  CNN_ConvolutionNE16("S14_CONV_2D_0_14_fusion", &gen_ctrl_S14_CONV_2D_0_14_fusion, -1, -1, 4, 1, 8, 8, 8, 64, 64,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 2, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S17_CONV_2D_0_17;
  CNN_InitGenCtrl(&gen_ctrl_S17_CONV_2D_0_17);
  CNN_SetGenCtrl(&gen_ctrl_S17_CONV_2D_0_17, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S17_CONV_2D_0_17, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_17
  CNN_ConvolutionNE16("S17_CONV_2D_0_17", &gen_ctrl_S17_CONV_2D_0_17, -1, -1, 4, 1, 8, 8, 8, 64, 64, KOP_CONV, 3, 3, 1,
                      1, 1, 1, 1, 1, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  // generator for expr_0
  s18_kernel_gen("S18_expr_0");

  CNN_GenControl_T gen_ctrl_S19_CONCAT_0_21;
  CNN_InitGenCtrl(&gen_ctrl_S19_CONCAT_0_21);
  CNN_SetGenCtrl(&gen_ctrl_S19_CONCAT_0_21, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S19_CONCAT_0_21", &gen_ctrl_S19_CONCAT_0_21, -1, 4096, 2, KOP_CONCAT, 8, 8);

  CNN_GenControl_T gen_ctrl_S22_CONV_2D_0_22_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion, "CUSTOM_ACTIVATION_NAME", "expr_42");
  CNN_ExtraActivationArgs_T gen_ctrl_S22_CONV_2D_0_22_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S22_CONV_2D_0_22_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S22_CONV_2D_0_22_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_22_fusion
  CNN_ConvolutionNE16("S22_CONV_2D_0_22_fusion", &gen_ctrl_S22_CONV_2D_0_22_fusion, -1, -1, 4, 1, 8, 16, 16, 64, 64,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 4, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S25_CONV_2D_0_26_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion, "CUSTOM_ACTIVATION_NAME", "expr_43");
  CNN_ExtraActivationArgs_T gen_ctrl_S25_CONV_2D_0_26_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S25_CONV_2D_0_26_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S25_CONV_2D_0_26_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_26_fusion
  CNN_ConvolutionNE16("S25_CONV_2D_0_26_fusion", &gen_ctrl_S25_CONV_2D_0_26_fusion, -1, -1, 4, 1, 8, 16, 32, 64, 64,
                      KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 5, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S28_CONV_2D_0_29_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion, "CUSTOM_ACTIVATION_NAME", "expr_45");
  CNN_ExtraActivationArgs_T gen_ctrl_S28_CONV_2D_0_29_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S28_CONV_2D_0_29_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S28_CONV_2D_0_29_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_29_fusion
  CNN_ConvolutionNE16("S28_CONV_2D_0_29_fusion", &gen_ctrl_S28_CONV_2D_0_29_fusion, -1, -1, 4, 1, 8, 32, 32, 32, 32,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 7, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S29_CONV_2D_0_29_split;
  CNN_InitGenCtrl(&gen_ctrl_S29_CONV_2D_0_29_split);
  CNN_SetGenCtrl(&gen_ctrl_S29_CONV_2D_0_29_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S29_CONV_2D_0_29_split", &gen_ctrl_S29_CONV_2D_0_29_split, -1, 1024, 2, KOP_SPLIT, 16,
                               16);

  // generator for CONV_2D_0_29_split_copy_qout0
  CNN_Convert("S30_CONV_2D_0_29_split_copy_qout0", -1, -1, 16384, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S33_CONV_2D_0_32_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion, "CUSTOM_ACTIVATION_NAME", "expr_46");
  CNN_ExtraActivationArgs_T gen_ctrl_S33_CONV_2D_0_32_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S33_CONV_2D_0_32_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S33_CONV_2D_0_32_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_32_fusion
  CNN_ConvolutionNE16("S33_CONV_2D_0_32_fusion", &gen_ctrl_S33_CONV_2D_0_32_fusion, -1, -1, 4, 1, 8, 16, 16, 32, 32,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 9, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S36_CONV_2D_0_35;
  CNN_InitGenCtrl(&gen_ctrl_S36_CONV_2D_0_35);
  CNN_SetGenCtrl(&gen_ctrl_S36_CONV_2D_0_35, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S36_CONV_2D_0_35, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_35
  CNN_ConvolutionNE16("S36_CONV_2D_0_35", &gen_ctrl_S36_CONV_2D_0_35, -1, -1, 4, 1, 8, 16, 16, 32, 32, KOP_CONV, 3, 3,
                      1, 1, 1, 1, 1, 11, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  // generator for expr_2
  s37_kernel_gen("S37_expr_2");

  CNN_GenControl_T gen_ctrl_S38_CONCAT_0_42;
  CNN_InitGenCtrl(&gen_ctrl_S38_CONCAT_0_42);
  CNN_SetGenCtrl(&gen_ctrl_S38_CONCAT_0_42, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S38_CONCAT_0_42", &gen_ctrl_S38_CONCAT_0_42, -1, 1024, 2, KOP_CONCAT, 16, 16);

  CNN_GenControl_T gen_ctrl_S41_CONV_2D_0_43_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion, "CUSTOM_ACTIVATION_NAME", "expr_48");
  CNN_ExtraActivationArgs_T gen_ctrl_S41_CONV_2D_0_43_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S41_CONV_2D_0_43_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S41_CONV_2D_0_43_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_43_fusion
  CNN_ConvolutionNE16("S41_CONV_2D_0_43_fusion", &gen_ctrl_S41_CONV_2D_0_43_fusion, -1, -1, 4, 1, 8, 32, 32, 32, 32,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S44_CONV_2D_0_47_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion, "CUSTOM_ACTIVATION_NAME", "expr_49");
  CNN_ExtraActivationArgs_T gen_ctrl_S44_CONV_2D_0_47_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S44_CONV_2D_0_47_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S44_CONV_2D_0_47_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_47_fusion
  CNN_ConvolutionNE16("S44_CONV_2D_0_47_fusion", &gen_ctrl_S44_CONV_2D_0_47_fusion, -1, -1, 4, 1, 8, 32, 56, 32, 32,
                      KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 10, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S47_CONV_2D_0_50_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion, "CUSTOM_ACTIVATION_NAME", "expr_50");
  CNN_ExtraActivationArgs_T gen_ctrl_S47_CONV_2D_0_50_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S47_CONV_2D_0_50_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S47_CONV_2D_0_50_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_50_fusion
  CNN_ConvolutionNE16("S47_CONV_2D_0_50_fusion", &gen_ctrl_S47_CONV_2D_0_50_fusion, -1, -1, 4, 1, 8, 56, 56, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 11, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S48_CONV_2D_0_50_split;
  CNN_InitGenCtrl(&gen_ctrl_S48_CONV_2D_0_50_split);
  CNN_SetGenCtrl(&gen_ctrl_S48_CONV_2D_0_50_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S48_CONV_2D_0_50_split", &gen_ctrl_S48_CONV_2D_0_50_split, -1, 256, 2, KOP_SPLIT, 28,
                               28);

  // generator for CONV_2D_0_50_split_copy_qout0
  CNN_Convert("S49_CONV_2D_0_50_split_copy_qout0", -1, -1, 7168, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S52_CONV_2D_0_53_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion, "CUSTOM_ACTIVATION_NAME", "expr_51");
  CNN_ExtraActivationArgs_T gen_ctrl_S52_CONV_2D_0_53_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S52_CONV_2D_0_53_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S52_CONV_2D_0_53_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_53_fusion
  CNN_ConvolutionNE16("S52_CONV_2D_0_53_fusion", &gen_ctrl_S52_CONV_2D_0_53_fusion, -1, -1, 4, 1, 8, 28, 28, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S55_CONV_2D_0_56;
  CNN_InitGenCtrl(&gen_ctrl_S55_CONV_2D_0_56);
  CNN_SetGenCtrl(&gen_ctrl_S55_CONV_2D_0_56, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S55_CONV_2D_0_56, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_56
  CNN_ConvolutionNE16("S55_CONV_2D_0_56", &gen_ctrl_S55_CONV_2D_0_56, -1, -1, 4, 1, 8, 28, 28, 16, 16, KOP_CONV, 3, 3,
                      1, 1, 1, 1, 1, 12, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  // generator for expr_3
  s56_kernel_gen("S56_expr_3");

  CNN_GenControl_T gen_ctrl_S57_CONCAT_0_63;
  CNN_InitGenCtrl(&gen_ctrl_S57_CONCAT_0_63);
  CNN_SetGenCtrl(&gen_ctrl_S57_CONCAT_0_63, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S57_CONCAT_0_63", &gen_ctrl_S57_CONCAT_0_63, -1, 256, 2, KOP_CONCAT, 28, 28);

  CNN_GenControl_T gen_ctrl_S60_CONV_2D_0_64_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion, "CUSTOM_ACTIVATION_NAME", "expr_53");
  CNN_ExtraActivationArgs_T gen_ctrl_S60_CONV_2D_0_64_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S60_CONV_2D_0_64_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S60_CONV_2D_0_64_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_64_fusion
  CNN_ConvolutionNE16("S60_CONV_2D_0_64_fusion", &gen_ctrl_S60_CONV_2D_0_64_fusion, -1, -1, 4, 1, 8, 56, 56, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 17, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  // generator for CONV_2D_0_64_fusion_qout0
  CNN_Convert("S61_CONV_2D_0_64_fusion_qout0", -1, -1, 14336, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S64_CONV_2D_0_68_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S64_CONV_2D_0_68_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S64_CONV_2D_0_68_fusion, "CUSTOM_ACTIVATION_NAME", "expr_54");
  CNN_ExtraActivationArgs_T gen_ctrl_S64_CONV_2D_0_68_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S64_CONV_2D_0_68_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S64_CONV_2D_0_68_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S64_CONV_2D_0_68_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S64_CONV_2D_0_68_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_68_fusion
  CNN_ConvolutionNE16("S64_CONV_2D_0_68_fusion", &gen_ctrl_S64_CONV_2D_0_68_fusion, -1, -1, 4, 1, 8, 56, 104, 16, 16,
                      KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 12, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S67_CONV_2D_0_71_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S67_CONV_2D_0_71_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S67_CONV_2D_0_71_fusion, "CUSTOM_ACTIVATION_NAME", "expr_56");
  CNN_ExtraActivationArgs_T gen_ctrl_S67_CONV_2D_0_71_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S67_CONV_2D_0_71_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S67_CONV_2D_0_71_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S67_CONV_2D_0_71_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S67_CONV_2D_0_71_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_71_fusion
  CNN_ConvolutionNE16("S67_CONV_2D_0_71_fusion", &gen_ctrl_S67_CONV_2D_0_71_fusion, -1, -1, 4, 1, 8, 104, 104, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S68_CONV_2D_0_71_split;
  CNN_InitGenCtrl(&gen_ctrl_S68_CONV_2D_0_71_split);
  CNN_SetGenCtrl(&gen_ctrl_S68_CONV_2D_0_71_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S68_CONV_2D_0_71_split", &gen_ctrl_S68_CONV_2D_0_71_split, -1, 64, 2, KOP_SPLIT, 52,
                               52);

  // generator for CONV_2D_0_71_split_copy_qout0
  CNN_Convert("S69_CONV_2D_0_71_split_copy_qout0", -1, -1, 3328, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S72_CONV_2D_0_74_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S72_CONV_2D_0_74_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S72_CONV_2D_0_74_fusion, "CUSTOM_ACTIVATION_NAME", "expr_57");
  CNN_ExtraActivationArgs_T gen_ctrl_S72_CONV_2D_0_74_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S72_CONV_2D_0_74_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S72_CONV_2D_0_74_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S72_CONV_2D_0_74_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S72_CONV_2D_0_74_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_74_fusion
  CNN_ConvolutionNE16("S72_CONV_2D_0_74_fusion", &gen_ctrl_S72_CONV_2D_0_74_fusion, -1, -1, 4, 1, 8, 52, 52, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 10, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S75_CONV_2D_0_77;
  CNN_InitGenCtrl(&gen_ctrl_S75_CONV_2D_0_77);
  CNN_SetGenCtrl(&gen_ctrl_S75_CONV_2D_0_77, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S75_CONV_2D_0_77, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_77
  CNN_ConvolutionNE16("S75_CONV_2D_0_77", &gen_ctrl_S75_CONV_2D_0_77, -1, -1, 4, 1, 8, 52, 52, 8, 8, KOP_CONV, 3, 3, 1,
                      1, 1, 1, 1, 8, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  // generator for expr_4
  s76_kernel_gen("S76_expr_4");

  CNN_GenControl_T gen_ctrl_S77_CONCAT_0_84;
  CNN_InitGenCtrl(&gen_ctrl_S77_CONCAT_0_84);
  CNN_SetGenCtrl(&gen_ctrl_S77_CONCAT_0_84, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S77_CONCAT_0_84", &gen_ctrl_S77_CONCAT_0_84, -1, 64, 2, KOP_CONCAT, 52, 52);

  CNN_GenControl_T gen_ctrl_S80_CONV_2D_0_85_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S80_CONV_2D_0_85_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S80_CONV_2D_0_85_fusion, "CUSTOM_ACTIVATION_NAME", "expr_59");
  CNN_ExtraActivationArgs_T gen_ctrl_S80_CONV_2D_0_85_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S80_CONV_2D_0_85_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S80_CONV_2D_0_85_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S80_CONV_2D_0_85_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S80_CONV_2D_0_85_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_85_fusion
  CNN_ConvolutionNE16("S80_CONV_2D_0_85_fusion", &gen_ctrl_S80_CONV_2D_0_85_fusion, -1, -1, 4, 1, 8, 104, 104, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 19, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S83_CONV_2D_0_88_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S83_CONV_2D_0_88_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S83_CONV_2D_0_88_fusion, "CUSTOM_ACTIVATION_NAME", "expr_60");
  CNN_ExtraActivationArgs_T gen_ctrl_S83_CONV_2D_0_88_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S83_CONV_2D_0_88_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S83_CONV_2D_0_88_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S83_CONV_2D_0_88_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S83_CONV_2D_0_88_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_88_fusion
  CNN_ConvolutionNE16("S83_CONV_2D_0_88_fusion", &gen_ctrl_S83_CONV_2D_0_88_fusion, -1, -1, 4, 1, 8, 104, 52, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 11, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  // generator for CONV_2D_0_88_fusion_qout0
  CNN_Convert("S84_CONV_2D_0_88_fusion_qout0", -1, -1, 3328, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S85_MAX_POOL_2D_0_91;
  CNN_InitGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_91);
  CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_91, "HWC", AT_OPT_VAL(1));
  CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_91, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S85_MAX_POOL_2D_0_91, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for MAX_POOL_2D_0_91
  CNN_PoolAct_SQ8("S85_MAX_POOL_2D_0_91", &gen_ctrl_S85_MAX_POOL_2D_0_91, 52, 8, 8, KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                  KOP_NONE);

  CNN_GenControl_T gen_ctrl_S86_MAX_POOL_2D_0_92;
  CNN_InitGenCtrl(&gen_ctrl_S86_MAX_POOL_2D_0_92);
  CNN_SetGenCtrl(&gen_ctrl_S86_MAX_POOL_2D_0_92, "HWC", AT_OPT_VAL(1));
  CNN_SetGenCtrl(&gen_ctrl_S86_MAX_POOL_2D_0_92, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S86_MAX_POOL_2D_0_92, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for MAX_POOL_2D_0_92
  CNN_PoolAct_SQ8("S86_MAX_POOL_2D_0_92", &gen_ctrl_S86_MAX_POOL_2D_0_92, 52, 8, 8, KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                  KOP_NONE);

  CNN_GenControl_T gen_ctrl_S87_MAX_POOL_2D_0_93;
  CNN_InitGenCtrl(&gen_ctrl_S87_MAX_POOL_2D_0_93);
  CNN_SetGenCtrl(&gen_ctrl_S87_MAX_POOL_2D_0_93, "HWC", AT_OPT_VAL(1));
  CNN_SetGenCtrl(&gen_ctrl_S87_MAX_POOL_2D_0_93, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S87_MAX_POOL_2D_0_93, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for MAX_POOL_2D_0_93
  CNN_PoolAct_SQ8("S87_MAX_POOL_2D_0_93", &gen_ctrl_S87_MAX_POOL_2D_0_93, 52, 8, 8, KOP_MAXPOOL, 5, 5, 1, 1, 1, 1, 1,
                  KOP_NONE);

  // generator for MAX_POOL_2D_0_93_qout0
  CNN_Convert("S88_MAX_POOL_2D_0_93_qout0", -1, -1, 3328, KOP_CONVERT_FP_FP_SCALE);

  // generator for MAX_POOL_2D_0_92_qout0
  CNN_Convert("S89_MAX_POOL_2D_0_92_qout0", -1, -1, 3328, KOP_CONVERT_FP_FP_SCALE);

  // generator for MAX_POOL_2D_0_91_qout0
  CNN_Convert("S90_MAX_POOL_2D_0_91_qout0", -1, -1, 3328, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S91_CONCAT_0_94;
  CNN_InitGenCtrl(&gen_ctrl_S91_CONCAT_0_94);
  CNN_SetGenCtrl(&gen_ctrl_S91_CONCAT_0_94, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S91_CONCAT_0_94", &gen_ctrl_S91_CONCAT_0_94, -1, 64, 4, KOP_CONCAT, 52, 52, 52, 52);

  CNN_GenControl_T gen_ctrl_S94_CONV_2D_0_95_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S94_CONV_2D_0_95_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S94_CONV_2D_0_95_fusion, "CUSTOM_ACTIVATION_NAME", "expr_61");
  CNN_ExtraActivationArgs_T gen_ctrl_S94_CONV_2D_0_95_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S94_CONV_2D_0_95_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S94_CONV_2D_0_95_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S94_CONV_2D_0_95_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S94_CONV_2D_0_95_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_95_fusion
  CNN_ConvolutionNE16("S94_CONV_2D_0_95_fusion", &gen_ctrl_S94_CONV_2D_0_95_fusion, -1, -1, 4, 1, 8, 208, 104, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 9, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S97_CONV_2D_0_98_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S97_CONV_2D_0_98_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S97_CONV_2D_0_98_fusion, "CUSTOM_ACTIVATION_NAME", "expr_62");
  CNN_ExtraActivationArgs_T gen_ctrl_S97_CONV_2D_0_98_fusion_extra_activation_args = {1,
                                                                                      {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S97_CONV_2D_0_98_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S97_CONV_2D_0_98_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S97_CONV_2D_0_98_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S97_CONV_2D_0_98_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_98_fusion
  CNN_ConvolutionNE16("S97_CONV_2D_0_98_fusion", &gen_ctrl_S97_CONV_2D_0_98_fusion, -1, -1, 4, 1, 8, 104, 56, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 8, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S98_RESIZE_NN_0_101;
  CNN_InitGenCtrl(&gen_ctrl_S98_RESIZE_NN_0_101);
  CNN_SetGenCtrl(&gen_ctrl_S98_RESIZE_NN_0_101, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
  CNN_SetGenCtrl(&gen_ctrl_S98_RESIZE_NN_0_101, "HWC", AT_OPT_VAL(1));
  // generator for RESIZE_NN_0_101
  GenerateResizeMultiChannel("S98_RESIZE_NN_0_101", &gen_ctrl_S98_RESIZE_NN_0_101, 8, 8, 16, 16, 56, UNSIGNED_INOUT,
                             KOP_NEAREST_NEIGHBOR_RESIZE);

  CNN_GenControl_T gen_ctrl_S99_CONCAT_0_102;
  CNN_InitGenCtrl(&gen_ctrl_S99_CONCAT_0_102);
  CNN_SetGenCtrl(&gen_ctrl_S99_CONCAT_0_102, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S99_CONCAT_0_102", &gen_ctrl_S99_CONCAT_0_102, -1, 256, 2, KOP_CONCAT, 56, 56);

  CNN_GenControl_T gen_ctrl_S102_CONV_2D_0_103_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S102_CONV_2D_0_103_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S102_CONV_2D_0_103_fusion, "CUSTOM_ACTIVATION_NAME", "expr_5");
  CNN_ExtraActivationArgs_T gen_ctrl_S102_CONV_2D_0_103_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S102_CONV_2D_0_103_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S102_CONV_2D_0_103_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S102_CONV_2D_0_103_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S102_CONV_2D_0_103_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_103_fusion
  CNN_ConvolutionNE16("S102_CONV_2D_0_103_fusion", &gen_ctrl_S102_CONV_2D_0_103_fusion, -1, -1, 4, 1, 8, 112, 56, 16,
                      16, KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 9, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S103_CONV_2D_0_103_split;
  CNN_InitGenCtrl(&gen_ctrl_S103_CONV_2D_0_103_split);
  CNN_SetGenCtrl(&gen_ctrl_S103_CONV_2D_0_103_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S103_CONV_2D_0_103_split", &gen_ctrl_S103_CONV_2D_0_103_split, -1, 256, 2, KOP_SPLIT,
                               28, 28);

  // generator for CONV_2D_0_103_split_copy_qout0
  CNN_Convert("S104_CONV_2D_0_103_split_copy_qout0", -1, -1, 7168, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S107_CONV_2D_0_106_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S107_CONV_2D_0_106_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S107_CONV_2D_0_106_fusion, "CUSTOM_ACTIVATION_NAME", "expr_6");
  CNN_ExtraActivationArgs_T gen_ctrl_S107_CONV_2D_0_106_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S107_CONV_2D_0_106_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S107_CONV_2D_0_106_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S107_CONV_2D_0_106_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S107_CONV_2D_0_106_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_106_fusion
  CNN_ConvolutionNE16("S107_CONV_2D_0_106_fusion", &gen_ctrl_S107_CONV_2D_0_106_fusion, -1, -1, 4, 1, 8, 28, 28, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 13, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S110_CONV_2D_0_109_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S110_CONV_2D_0_109_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S110_CONV_2D_0_109_fusion, "CUSTOM_ACTIVATION_NAME", "expr_7");
  CNN_ExtraActivationArgs_T gen_ctrl_S110_CONV_2D_0_109_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S110_CONV_2D_0_109_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S110_CONV_2D_0_109_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S110_CONV_2D_0_109_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S110_CONV_2D_0_109_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_109_fusion
  CNN_ConvolutionNE16("S110_CONV_2D_0_109_fusion", &gen_ctrl_S110_CONV_2D_0_109_fusion, -1, -1, 4, 1, 8, 28, 28, 16, 16,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 13, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S111_CONCAT_0_115;
  CNN_InitGenCtrl(&gen_ctrl_S111_CONCAT_0_115);
  CNN_SetGenCtrl(&gen_ctrl_S111_CONCAT_0_115, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S111_CONCAT_0_115", &gen_ctrl_S111_CONCAT_0_115, -1, 256, 2, KOP_CONCAT, 28, 28);

  CNN_GenControl_T gen_ctrl_S114_CONV_2D_0_116_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S114_CONV_2D_0_116_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S114_CONV_2D_0_116_fusion, "CUSTOM_ACTIVATION_NAME", "expr_9");
  CNN_ExtraActivationArgs_T gen_ctrl_S114_CONV_2D_0_116_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S114_CONV_2D_0_116_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S114_CONV_2D_0_116_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S114_CONV_2D_0_116_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S114_CONV_2D_0_116_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_116_fusion
  CNN_ConvolutionNE16("S114_CONV_2D_0_116_fusion", &gen_ctrl_S114_CONV_2D_0_116_fusion, -1, -1, 4, 1, 8, 56, 56, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 13, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S117_CONV_2D_0_119_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S117_CONV_2D_0_119_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S117_CONV_2D_0_119_fusion, "CUSTOM_ACTIVATION_NAME", "expr_10");
  CNN_ExtraActivationArgs_T gen_ctrl_S117_CONV_2D_0_119_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S117_CONV_2D_0_119_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S117_CONV_2D_0_119_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S117_CONV_2D_0_119_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S117_CONV_2D_0_119_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_119_fusion
  CNN_ConvolutionNE16("S117_CONV_2D_0_119_fusion", &gen_ctrl_S117_CONV_2D_0_119_fusion, -1, -1, 4, 1, 8, 56, 32, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 13, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S118_RESIZE_NN_0_122;
  CNN_InitGenCtrl(&gen_ctrl_S118_RESIZE_NN_0_122);
  CNN_SetGenCtrl(&gen_ctrl_S118_RESIZE_NN_0_122, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));
  CNN_SetGenCtrl(&gen_ctrl_S118_RESIZE_NN_0_122, "HWC", AT_OPT_VAL(1));
  // generator for RESIZE_NN_0_122
  GenerateResizeMultiChannel("S118_RESIZE_NN_0_122", &gen_ctrl_S118_RESIZE_NN_0_122, 16, 16, 32, 32, 32, UNSIGNED_INOUT,
                             KOP_NEAREST_NEIGHBOR_RESIZE);

  // generator for RESIZE_NN_0_122_qout0
  CNN_Convert("S119_RESIZE_NN_0_122_qout0", -1, -1, 32768, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S120_CONCAT_0_123;
  CNN_InitGenCtrl(&gen_ctrl_S120_CONCAT_0_123);
  CNN_SetGenCtrl(&gen_ctrl_S120_CONCAT_0_123, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S120_CONCAT_0_123", &gen_ctrl_S120_CONCAT_0_123, -1, 1024, 2, KOP_CONCAT, 32, 32);

  // generator for CONV_2D_0_119_fusion_qout0
  CNN_Convert("S121_CONV_2D_0_119_fusion_qout0", -1, -1, 8192, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S124_CONV_2D_0_124_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S124_CONV_2D_0_124_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S124_CONV_2D_0_124_fusion, "CUSTOM_ACTIVATION_NAME", "expr_11");
  CNN_ExtraActivationArgs_T gen_ctrl_S124_CONV_2D_0_124_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S124_CONV_2D_0_124_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S124_CONV_2D_0_124_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S124_CONV_2D_0_124_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S124_CONV_2D_0_124_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_124_fusion
  CNN_ConvolutionNE16("S124_CONV_2D_0_124_fusion", &gen_ctrl_S124_CONV_2D_0_124_fusion, -1, -1, 4, 1, 8, 64, 32, 32, 32,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 10, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S125_CONV_2D_0_124_split;
  CNN_InitGenCtrl(&gen_ctrl_S125_CONV_2D_0_124_split);
  CNN_SetGenCtrl(&gen_ctrl_S125_CONV_2D_0_124_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S125_CONV_2D_0_124_split", &gen_ctrl_S125_CONV_2D_0_124_split, -1, 1024, 2, KOP_SPLIT,
                               16, 16);

  // generator for CONV_2D_0_124_split_copy_qout0
  CNN_Convert("S126_CONV_2D_0_124_split_copy_qout0", -1, -1, 16384, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S129_CONV_2D_0_127_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S129_CONV_2D_0_127_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S129_CONV_2D_0_127_fusion, "CUSTOM_ACTIVATION_NAME", "expr_12");
  CNN_ExtraActivationArgs_T gen_ctrl_S129_CONV_2D_0_127_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S129_CONV_2D_0_127_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S129_CONV_2D_0_127_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S129_CONV_2D_0_127_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S129_CONV_2D_0_127_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_127_fusion
  CNN_ConvolutionNE16("S129_CONV_2D_0_127_fusion", &gen_ctrl_S129_CONV_2D_0_127_fusion, -1, -1, 4, 1, 8, 16, 16, 32, 32,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 11, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S132_CONV_2D_0_130_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S132_CONV_2D_0_130_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S132_CONV_2D_0_130_fusion, "CUSTOM_ACTIVATION_NAME", "expr_14");
  CNN_ExtraActivationArgs_T gen_ctrl_S132_CONV_2D_0_130_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S132_CONV_2D_0_130_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S132_CONV_2D_0_130_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S132_CONV_2D_0_130_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S132_CONV_2D_0_130_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_130_fusion
  CNN_ConvolutionNE16("S132_CONV_2D_0_130_fusion", &gen_ctrl_S132_CONV_2D_0_130_fusion, -1, -1, 4, 1, 8, 16, 16, 32, 32,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 11, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S133_CONCAT_0_136;
  CNN_InitGenCtrl(&gen_ctrl_S133_CONCAT_0_136);
  CNN_SetGenCtrl(&gen_ctrl_S133_CONCAT_0_136, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S133_CONCAT_0_136", &gen_ctrl_S133_CONCAT_0_136, -1, 1024, 2, KOP_CONCAT, 16, 16);

  CNN_GenControl_T gen_ctrl_S136_CONV_2D_0_137_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S136_CONV_2D_0_137_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S136_CONV_2D_0_137_fusion, "CUSTOM_ACTIVATION_NAME", "expr_16");
  CNN_ExtraActivationArgs_T gen_ctrl_S136_CONV_2D_0_137_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S136_CONV_2D_0_137_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S136_CONV_2D_0_137_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S136_CONV_2D_0_137_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S136_CONV_2D_0_137_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_137_fusion
  CNN_ConvolutionNE16("S136_CONV_2D_0_137_fusion", &gen_ctrl_S136_CONV_2D_0_137_fusion, -1, -1, 4, 1, 8, 32, 32, 32, 32,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 10, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S139_CONV_2D_0_141_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S139_CONV_2D_0_141_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S139_CONV_2D_0_141_fusion, "CUSTOM_ACTIVATION_NAME", "expr_17");
  CNN_ExtraActivationArgs_T gen_ctrl_S139_CONV_2D_0_141_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S139_CONV_2D_0_141_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S139_CONV_2D_0_141_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S139_CONV_2D_0_141_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S139_CONV_2D_0_141_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_141_fusion
  CNN_ConvolutionNE16("S139_CONV_2D_0_141_fusion", &gen_ctrl_S139_CONV_2D_0_141_fusion, -1, -1, 4, 1, 8, 32, 32, 32, 32,
                      KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 8, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S140_CONCAT_0_144;
  CNN_InitGenCtrl(&gen_ctrl_S140_CONCAT_0_144);
  CNN_SetGenCtrl(&gen_ctrl_S140_CONCAT_0_144, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S140_CONCAT_0_144", &gen_ctrl_S140_CONCAT_0_144, -1, 256, 2, KOP_CONCAT, 32, 32);

  CNN_GenControl_T gen_ctrl_S143_CONV_2D_0_145_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S143_CONV_2D_0_145_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S143_CONV_2D_0_145_fusion, "CUSTOM_ACTIVATION_NAME", "expr_18");
  CNN_ExtraActivationArgs_T gen_ctrl_S143_CONV_2D_0_145_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S143_CONV_2D_0_145_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S143_CONV_2D_0_145_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S143_CONV_2D_0_145_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S143_CONV_2D_0_145_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_145_fusion
  CNN_ConvolutionNE16("S143_CONV_2D_0_145_fusion", &gen_ctrl_S143_CONV_2D_0_145_fusion, -1, -1, 4, 1, 8, 32, 64, 32, 32,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 8, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S146_CONV_2D_0_148_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S146_CONV_2D_0_148_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S146_CONV_2D_0_148_fusion, "CUSTOM_ACTIVATION_NAME", "expr_19");
  CNN_ExtraActivationArgs_T gen_ctrl_S146_CONV_2D_0_148_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S146_CONV_2D_0_148_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S146_CONV_2D_0_148_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S146_CONV_2D_0_148_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S146_CONV_2D_0_148_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_148_fusion
  CNN_ConvolutionNE16("S146_CONV_2D_0_148_fusion", &gen_ctrl_S146_CONV_2D_0_148_fusion, -1, -1, 4, 1, 8, 64, 64, 32, 32,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 11, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S149_CONV_2D_0_151_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S149_CONV_2D_0_151_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S149_CONV_2D_0_151_fusion, "CUSTOM_ACTIVATION_NAME", "expr_20");
  CNN_ExtraActivationArgs_T gen_ctrl_S149_CONV_2D_0_151_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S149_CONV_2D_0_151_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S149_CONV_2D_0_151_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S149_CONV_2D_0_151_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S149_CONV_2D_0_151_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_151_fusion
  CNN_ConvolutionNE16("S149_CONV_2D_0_151_fusion", &gen_ctrl_S149_CONV_2D_0_151_fusion, -1, -1, 4, 1, 8, 32, 32, 32, 32,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 8, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S152_CONV_2D_0_154_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S152_CONV_2D_0_154_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S152_CONV_2D_0_154_fusion, "CUSTOM_ACTIVATION_NAME", "expr_21");
  CNN_ExtraActivationArgs_T gen_ctrl_S152_CONV_2D_0_154_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S152_CONV_2D_0_154_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S152_CONV_2D_0_154_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S152_CONV_2D_0_154_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S152_CONV_2D_0_154_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_154_fusion
  CNN_ConvolutionNE16("S152_CONV_2D_0_154_fusion", &gen_ctrl_S152_CONV_2D_0_154_fusion, -1, -1, 4, 1, 8, 32, 32, 32, 32,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 14, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S155_CONV_2D_0_157_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S155_CONV_2D_0_157_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S155_CONV_2D_0_157_fusion, "CUSTOM_ACTIVATION_NAME", "expr_22");
  CNN_ExtraActivationArgs_T gen_ctrl_S155_CONV_2D_0_157_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S155_CONV_2D_0_157_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S155_CONV_2D_0_157_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S155_CONV_2D_0_157_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S155_CONV_2D_0_157_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_157_fusion
  CNN_ConvolutionNE16("S155_CONV_2D_0_157_fusion", &gen_ctrl_S155_CONV_2D_0_157_fusion, -1, -1, 4, 1, 8, 64, 56, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 14, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S156_CONV_2D_0_157_split;
  CNN_InitGenCtrl(&gen_ctrl_S156_CONV_2D_0_157_split);
  CNN_SetGenCtrl(&gen_ctrl_S156_CONV_2D_0_157_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S156_CONV_2D_0_157_split", &gen_ctrl_S156_CONV_2D_0_157_split, -1, 256, 2, KOP_SPLIT,
                               28, 28);

  // generator for CONV_2D_0_157_split_copy_qout0
  CNN_Convert("S157_CONV_2D_0_157_split_copy_qout0", -1, -1, 7168, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S160_CONV_2D_0_163;
  CNN_InitGenCtrl(&gen_ctrl_S160_CONV_2D_0_163);
  CNN_SetGenCtrl(&gen_ctrl_S160_CONV_2D_0_163, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S160_CONV_2D_0_163, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_163
  CNN_ConvolutionNE16("S160_CONV_2D_0_163", &gen_ctrl_S160_CONV_2D_0_163, -1, -1, 4, 1, 8, 64, 64, 32, 32, KOP_CONV, 1,
                      1, 1, 1, 1, 1, 0, 3, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  CNN_GenControl_T gen_ctrl_S163_CONV_2D_0_164;
  CNN_InitGenCtrl(&gen_ctrl_S163_CONV_2D_0_164);
  CNN_SetGenCtrl(&gen_ctrl_S163_CONV_2D_0_164, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S163_CONV_2D_0_164, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_164
  CNN_ConvolutionNE16("S163_CONV_2D_0_164", &gen_ctrl_S163_CONV_2D_0_164, -1, -1, 4, 1, 8, 32, 13, 32, 32, KOP_CONV, 1,
                      1, 1, 1, 1, 1, 0, 7, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  CNN_GenControl_T gen_ctrl_S164_CONCAT_0_165;
  CNN_InitGenCtrl(&gen_ctrl_S164_CONCAT_0_165);
  CNN_SetGenCtrl(&gen_ctrl_S164_CONCAT_0_165, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S164_CONCAT_0_165", &gen_ctrl_S164_CONCAT_0_165, -1, 1024, 2, KOP_CONCAT, 64, 13);

  CNN_GenControl_T gen_ctrl_S168_CONV_2D_0_167_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S168_CONV_2D_0_167_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S168_CONV_2D_0_167_fusion, "CUSTOM_ACTIVATION_NAME", "expr_25");
  CNN_ExtraActivationArgs_T gen_ctrl_S168_CONV_2D_0_167_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S168_CONV_2D_0_167_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S168_CONV_2D_0_167_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S168_CONV_2D_0_167_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S168_CONV_2D_0_167_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_167_fusion
  CNN_ConvolutionNE16("S168_CONV_2D_0_167_fusion", &gen_ctrl_S168_CONV_2D_0_167_fusion, -1, -1, 4, 1, 8, 28, 28, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 12, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S171_CONV_2D_0_170_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S171_CONV_2D_0_170_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S171_CONV_2D_0_170_fusion, "CUSTOM_ACTIVATION_NAME", "expr_26");
  CNN_ExtraActivationArgs_T gen_ctrl_S171_CONV_2D_0_170_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S171_CONV_2D_0_170_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S171_CONV_2D_0_170_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S171_CONV_2D_0_170_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S171_CONV_2D_0_170_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_170_fusion
  CNN_ConvolutionNE16("S171_CONV_2D_0_170_fusion", &gen_ctrl_S171_CONV_2D_0_170_fusion, -1, -1, 4, 1, 8, 28, 28, 16, 16,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 12, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S172_CONCAT_0_173;
  CNN_InitGenCtrl(&gen_ctrl_S172_CONCAT_0_173);
  CNN_SetGenCtrl(&gen_ctrl_S172_CONCAT_0_173, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S172_CONCAT_0_173", &gen_ctrl_S172_CONCAT_0_173, -1, 256, 2, KOP_CONCAT, 28, 28);

  CNN_GenControl_T gen_ctrl_S175_CONV_2D_0_174_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S175_CONV_2D_0_174_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S175_CONV_2D_0_174_fusion, "CUSTOM_ACTIVATION_NAME", "expr_27");
  CNN_ExtraActivationArgs_T gen_ctrl_S175_CONV_2D_0_174_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S175_CONV_2D_0_174_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S175_CONV_2D_0_174_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S175_CONV_2D_0_174_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S175_CONV_2D_0_174_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_174_fusion
  CNN_ConvolutionNE16("S175_CONV_2D_0_174_fusion", &gen_ctrl_S175_CONV_2D_0_174_fusion, -1, -1, 4, 1, 8, 56, 56, 16, 16,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 6, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S178_CONV_2D_0_178_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S178_CONV_2D_0_178_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S178_CONV_2D_0_178_fusion, "CUSTOM_ACTIVATION_NAME", "expr_28");
  CNN_ExtraActivationArgs_T gen_ctrl_S178_CONV_2D_0_178_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S178_CONV_2D_0_178_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S178_CONV_2D_0_178_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S178_CONV_2D_0_178_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S178_CONV_2D_0_178_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_178_fusion
  CNN_ConvolutionNE16("S178_CONV_2D_0_178_fusion", &gen_ctrl_S178_CONV_2D_0_178_fusion, -1, -1, 4, 1, 8, 56, 56, 16, 16,
                      KOP_CONV, 3, 3, 1, 1, 2, 2, 1, 7, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S179_CONCAT_0_181;
  CNN_InitGenCtrl(&gen_ctrl_S179_CONCAT_0_181);
  CNN_SetGenCtrl(&gen_ctrl_S179_CONCAT_0_181, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S179_CONCAT_0_181", &gen_ctrl_S179_CONCAT_0_181, -1, 64, 2, KOP_CONCAT, 56, 56);

  CNN_GenControl_T gen_ctrl_S182_CONV_2D_0_182_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S182_CONV_2D_0_182_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S182_CONV_2D_0_182_fusion, "CUSTOM_ACTIVATION_NAME", "expr_29");
  CNN_ExtraActivationArgs_T gen_ctrl_S182_CONV_2D_0_182_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S182_CONV_2D_0_182_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S182_CONV_2D_0_182_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S182_CONV_2D_0_182_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S182_CONV_2D_0_182_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_182_fusion
  CNN_ConvolutionNE16("S182_CONV_2D_0_182_fusion", &gen_ctrl_S182_CONV_2D_0_182_fusion, -1, -1, 4, 1, 8, 56, 64, 16, 16,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 7, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S185_CONV_2D_0_185_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S185_CONV_2D_0_185_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S185_CONV_2D_0_185_fusion, "CUSTOM_ACTIVATION_NAME", "expr_30");
  CNN_ExtraActivationArgs_T gen_ctrl_S185_CONV_2D_0_185_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S185_CONV_2D_0_185_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S185_CONV_2D_0_185_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S185_CONV_2D_0_185_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S185_CONV_2D_0_185_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_185_fusion
  CNN_ConvolutionNE16("S185_CONV_2D_0_185_fusion", &gen_ctrl_S185_CONV_2D_0_185_fusion, -1, -1, 4, 1, 8, 56, 32, 16, 16,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 7, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S188_CONV_2D_0_188_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S188_CONV_2D_0_188_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S188_CONV_2D_0_188_fusion, "CUSTOM_ACTIVATION_NAME", "expr_31");
  CNN_ExtraActivationArgs_T gen_ctrl_S188_CONV_2D_0_188_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S188_CONV_2D_0_188_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S188_CONV_2D_0_188_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S188_CONV_2D_0_188_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S188_CONV_2D_0_188_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_188_fusion
  CNN_ConvolutionNE16("S188_CONV_2D_0_188_fusion", &gen_ctrl_S188_CONV_2D_0_188_fusion, -1, -1, 4, 1, 8, 64, 64, 16, 16,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 10, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S191_CONV_2D_0_191_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S191_CONV_2D_0_191_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S191_CONV_2D_0_191_fusion, "CUSTOM_ACTIVATION_NAME", "expr_32");
  CNN_ExtraActivationArgs_T gen_ctrl_S191_CONV_2D_0_191_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S191_CONV_2D_0_191_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S191_CONV_2D_0_191_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S191_CONV_2D_0_191_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S191_CONV_2D_0_191_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_191_fusion
  CNN_ConvolutionNE16("S191_CONV_2D_0_191_fusion", &gen_ctrl_S191_CONV_2D_0_191_fusion, -1, -1, 4, 1, 8, 32, 32, 16, 16,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 12, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S194_CONV_2D_0_194_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S194_CONV_2D_0_194_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S194_CONV_2D_0_194_fusion, "CUSTOM_ACTIVATION_NAME", "expr_33");
  CNN_ExtraActivationArgs_T gen_ctrl_S194_CONV_2D_0_194_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S194_CONV_2D_0_194_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S194_CONV_2D_0_194_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S194_CONV_2D_0_194_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S194_CONV_2D_0_194_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_194_fusion
  CNN_ConvolutionNE16("S194_CONV_2D_0_194_fusion", &gen_ctrl_S194_CONV_2D_0_194_fusion, -1, -1, 4, 1, 8, 112, 104, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 9, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S195_CONV_2D_0_194_split;
  CNN_InitGenCtrl(&gen_ctrl_S195_CONV_2D_0_194_split);
  CNN_SetGenCtrl(&gen_ctrl_S195_CONV_2D_0_194_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S195_CONV_2D_0_194_split", &gen_ctrl_S195_CONV_2D_0_194_split, -1, 64, 2, KOP_SPLIT, 52,
                               52);

  // generator for CONV_2D_0_194_split_copy_qout0
  CNN_Convert("S196_CONV_2D_0_194_split_copy_qout0", -1, -1, 3328, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S199_CONV_2D_0_200;
  CNN_InitGenCtrl(&gen_ctrl_S199_CONV_2D_0_200);
  CNN_SetGenCtrl(&gen_ctrl_S199_CONV_2D_0_200, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S199_CONV_2D_0_200, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_200
  CNN_ConvolutionNE16("S199_CONV_2D_0_200", &gen_ctrl_S199_CONV_2D_0_200, -1, -1, 4, 1, 8, 64, 64, 16, 16, KOP_CONV, 1,
                      1, 1, 1, 1, 1, 0, 6, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  CNN_GenControl_T gen_ctrl_S202_CONV_2D_0_201;
  CNN_InitGenCtrl(&gen_ctrl_S202_CONV_2D_0_201);
  CNN_SetGenCtrl(&gen_ctrl_S202_CONV_2D_0_201, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S202_CONV_2D_0_201, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_201
  CNN_ConvolutionNE16("S202_CONV_2D_0_201", &gen_ctrl_S202_CONV_2D_0_201, -1, -1, 4, 1, 8, 32, 13, 16, 16, KOP_CONV, 1,
                      1, 1, 1, 1, 1, 0, 8, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  CNN_GenControl_T gen_ctrl_S203_CONCAT_0_202;
  CNN_InitGenCtrl(&gen_ctrl_S203_CONCAT_0_202);
  CNN_SetGenCtrl(&gen_ctrl_S203_CONCAT_0_202, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S203_CONCAT_0_202", &gen_ctrl_S203_CONCAT_0_202, -1, 256, 2, KOP_CONCAT, 64, 13);

  CNN_GenControl_T gen_ctrl_S207_CONV_2D_0_204_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S207_CONV_2D_0_204_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S207_CONV_2D_0_204_fusion, "CUSTOM_ACTIVATION_NAME", "expr_35");
  CNN_ExtraActivationArgs_T gen_ctrl_S207_CONV_2D_0_204_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S207_CONV_2D_0_204_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S207_CONV_2D_0_204_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S207_CONV_2D_0_204_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S207_CONV_2D_0_204_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_204_fusion
  CNN_ConvolutionNE16("S207_CONV_2D_0_204_fusion", &gen_ctrl_S207_CONV_2D_0_204_fusion, -1, -1, 4, 1, 8, 52, 52, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 21, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S210_CONV_2D_0_207_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S210_CONV_2D_0_207_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S210_CONV_2D_0_207_fusion, "CUSTOM_ACTIVATION_NAME", "expr_36");
  CNN_ExtraActivationArgs_T gen_ctrl_S210_CONV_2D_0_207_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S210_CONV_2D_0_207_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S210_CONV_2D_0_207_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S210_CONV_2D_0_207_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S210_CONV_2D_0_207_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_207_fusion
  CNN_ConvolutionNE16("S210_CONV_2D_0_207_fusion", &gen_ctrl_S210_CONV_2D_0_207_fusion, -1, -1, 4, 1, 8, 52, 52, 8, 8,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 19, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S211_CONCAT_0_210;
  CNN_InitGenCtrl(&gen_ctrl_S211_CONCAT_0_210);
  CNN_SetGenCtrl(&gen_ctrl_S211_CONCAT_0_210, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S211_CONCAT_0_210", &gen_ctrl_S211_CONCAT_0_210, -1, 64, 2, KOP_CONCAT, 52, 52);

  CNN_GenControl_T gen_ctrl_S214_CONV_2D_0_211_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S214_CONV_2D_0_211_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S214_CONV_2D_0_211_fusion, "CUSTOM_ACTIVATION_NAME", "expr_37");
  CNN_ExtraActivationArgs_T gen_ctrl_S214_CONV_2D_0_211_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S214_CONV_2D_0_211_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S214_CONV_2D_0_211_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S214_CONV_2D_0_211_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S214_CONV_2D_0_211_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_211_fusion
  CNN_ConvolutionNE16("S214_CONV_2D_0_211_fusion", &gen_ctrl_S214_CONV_2D_0_211_fusion, -1, -1, 4, 1, 8, 104, 104, 8, 8,
                      KOP_CONV, 1, 1, 1, 1, 1, 1, 0, 14, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S217_CONV_2D_0_214_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S217_CONV_2D_0_214_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S217_CONV_2D_0_214_fusion, "CUSTOM_ACTIVATION_NAME", "expr_38");
  CNN_ExtraActivationArgs_T gen_ctrl_S217_CONV_2D_0_214_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S217_CONV_2D_0_214_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S217_CONV_2D_0_214_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S217_CONV_2D_0_214_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S217_CONV_2D_0_214_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_214_fusion
  CNN_ConvolutionNE16("S217_CONV_2D_0_214_fusion", &gen_ctrl_S217_CONV_2D_0_214_fusion, -1, -1, 4, 1, 8, 104, 64, 8, 8,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 16, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S220_CONV_2D_0_217_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S220_CONV_2D_0_217_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S220_CONV_2D_0_217_fusion, "CUSTOM_ACTIVATION_NAME", "expr_39");
  CNN_ExtraActivationArgs_T gen_ctrl_S220_CONV_2D_0_217_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S220_CONV_2D_0_217_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S220_CONV_2D_0_217_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S220_CONV_2D_0_217_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S220_CONV_2D_0_217_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_217_fusion
  CNN_ConvolutionNE16("S220_CONV_2D_0_217_fusion", &gen_ctrl_S220_CONV_2D_0_217_fusion, -1, -1, 4, 1, 8, 104, 32, 8, 8,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 16, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S223_CONV_2D_0_220_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S223_CONV_2D_0_220_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S223_CONV_2D_0_220_fusion, "CUSTOM_ACTIVATION_NAME", "expr_40");
  CNN_ExtraActivationArgs_T gen_ctrl_S223_CONV_2D_0_220_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S223_CONV_2D_0_220_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S223_CONV_2D_0_220_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S223_CONV_2D_0_220_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S223_CONV_2D_0_220_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_220_fusion
  CNN_ConvolutionNE16("S223_CONV_2D_0_220_fusion", &gen_ctrl_S223_CONV_2D_0_220_fusion, -1, -1, 4, 1, 8, 64, 64, 8, 8,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 111, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S226_CONV_2D_0_223_fusion;
  CNN_InitGenCtrl(&gen_ctrl_S226_CONV_2D_0_223_fusion);
  CNN_SetGenCtrl(&gen_ctrl_S226_CONV_2D_0_223_fusion, "CUSTOM_ACTIVATION_NAME", "expr_41");
  CNN_ExtraActivationArgs_T gen_ctrl_S226_CONV_2D_0_223_fusion_extra_activation_args = {1,
                                                                                        {{"SigmoidLUTTable", 256, -2}}};
  CNN_SetGenCtrl(&gen_ctrl_S226_CONV_2D_0_223_fusion, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S226_CONV_2D_0_223_fusion_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S226_CONV_2D_0_223_fusion, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S226_CONV_2D_0_223_fusion, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_223_fusion
  CNN_ConvolutionNE16("S226_CONV_2D_0_223_fusion", &gen_ctrl_S226_CONV_2D_0_223_fusion, -1, -1, 4, 1, 8, 32, 32, 8, 8,
                      KOP_CONV, 3, 3, 1, 1, 1, 1, 1, 10, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_CUSTOM);

  CNN_GenControl_T gen_ctrl_S229_CONV_2D_0_226;
  CNN_InitGenCtrl(&gen_ctrl_S229_CONV_2D_0_226);
  CNN_SetGenCtrl(&gen_ctrl_S229_CONV_2D_0_226, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S229_CONV_2D_0_226, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_226
  CNN_ConvolutionNE16("S229_CONV_2D_0_226", &gen_ctrl_S229_CONV_2D_0_226, -1, -1, 4, 1, 8, 64, 64, 8, 8, KOP_CONV, 1, 1,
                      1, 1, 1, 1, 0, 132, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  CNN_GenControl_T gen_ctrl_S232_CONV_2D_0_227;
  CNN_InitGenCtrl(&gen_ctrl_S232_CONV_2D_0_227);
  CNN_SetGenCtrl(&gen_ctrl_S232_CONV_2D_0_227, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S232_CONV_2D_0_227, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_227
  CNN_ConvolutionNE16("S232_CONV_2D_0_227", &gen_ctrl_S232_CONV_2D_0_227, -1, -1, 4, 1, 8, 32, 13, 8, 8, KOP_CONV, 1, 1,
                      1, 1, 1, 1, 0, 32, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  CNN_GenControl_T gen_ctrl_S233_CONCAT_0_228;
  CNN_InitGenCtrl(&gen_ctrl_S233_CONCAT_0_228);
  CNN_SetGenCtrl(&gen_ctrl_S233_CONCAT_0_228, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_ConcatLastAxis_Generator2("S233_CONCAT_0_228", &gen_ctrl_S233_CONCAT_0_228, -1, 64, 2, KOP_CONCAT, 64, 13);

  CNN_GenControl_T gen_ctrl_S236_STRIDED_SLICE_0_234_split;
  CNN_InitGenCtrl(&gen_ctrl_S236_STRIDED_SLICE_0_234_split);
  CNN_SetGenCtrl(&gen_ctrl_S236_STRIDED_SLICE_0_234_split, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  CNN_SplitLastAxis_Generator2("S236_STRIDED_SLICE_0_234_split", &gen_ctrl_S236_STRIDED_SLICE_0_234_split, -1, 1344, 2,
                               KOP_SPLIT, 64, 13);

  // generator for TRANSPOSE_0_236_qout0
  CNN_Convert("S238_TRANSPOSE_0_236_qout0", -1, 1, 86016, KOP_CONVERT_FP_FP_SCALE);

  // generator for SOFTMAX_0_237
  CNN_SoftMax2D_SQ8("S239_SOFTMAX_0_237", 0, 5376, 16, KOP_SOFTMAX);

  // generator for TRANSPOSE_0_238_qout0
  CNN_Convert("S240_TRANSPOSE_0_238_qout0", 2, -1, 86016, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S241_CONV_2D_0_240_trans;
  CNN_InitGenCtrl(&gen_ctrl_S241_CONV_2D_0_240_trans);
  CNN_SetGenCtrl(&gen_ctrl_S241_CONV_2D_0_240_trans, "ARG_DTYPE", AT_OPT_VAL(ARG_INT));

  // generator for CONV_2D_0_240_trans Transpose 1344x4x16 -> 4x1344x16 ((1, 0, 2))
  CNN_3DTensorPermute("S241_CONV_2D_0_240_trans", &gen_ctrl_S241_CONV_2D_0_240_trans, -1, 1344, 16, 4,
                      KOP_MATPERM_CHW2HCW);

  // generator for STRIDED_SLICE_0_234_split_qout1
  CNN_Convert("S242_STRIDED_SLICE_0_234_split_qout1", -1, -1, 17472, KOP_CONVERT_FP_FP_SCALE);

  CNN_GenControl_T gen_ctrl_S243_LOGISTIC_0_243;
  CNN_InitGenCtrl(&gen_ctrl_S243_LOGISTIC_0_243);
  CNN_ExtraActivationArgs_T gen_ctrl_S243_LOGISTIC_0_243_extra_activation_args = {1, {{"SigmoidLUT_u8", 128, -1}}};
  CNN_SetGenCtrl(&gen_ctrl_S243_LOGISTIC_0_243, "EXTRA_ACTIVATION_ARGS",
                 &gen_ctrl_S243_LOGISTIC_0_243_extra_activation_args);
  CNN_SetGenCtrl(&gen_ctrl_S243_LOGISTIC_0_243, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S243_LOGISTIC_0_243, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for LOGISTIC_0_243
  CNN_PoolAct_SQ8("S243_LOGISTIC_0_243", &gen_ctrl_S243_LOGISTIC_0_243, 1, 13, 1344, KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
                  KOP_SIGMOID);

  CNN_GenControl_T gen_ctrl_S247_CONV_2D_0_240;
  CNN_InitGenCtrl(&gen_ctrl_S247_CONV_2D_0_240);
  CNN_SetGenCtrl(&gen_ctrl_S247_CONV_2D_0_240, "INPUT_DATASIZE", AT_OPT_VAL(-1));
  CNN_SetGenCtrl(&gen_ctrl_S247_CONV_2D_0_240, "OUTPUT_DATASIZE", AT_OPT_VAL(-1));
  // generator for CONV_2D_0_240
  CNN_ConvolutionNE16("S247_CONV_2D_0_240", &gen_ctrl_S247_CONV_2D_0_240, -1, -1, 4, 1, 8, 16, 1, 1344, 4, KOP_CONV, 1,
                      1, 1, 1, 1, 1, 0, 0, KOP_NONE, 0, 0, 0, 0, 0, 0, 0, KOP_NONE);

  // generator for expr_1
  s255_kernel_gen("S255_expr_1");

  // generator for expr_64
  s257_kernel_gen("S257_expr_64");

#define GRAPH
#ifdef GRAPH
  CreateGraph(
      "YOLOv5CNN",
      /* Arguments either passed or globals */
      CArgs(
          341, TCArgInfo("unsigned char * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_con", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfoExpKerSize("Model_37_tf_nn_convolution_con.tensor", 1, 1, 8, 0, 864)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_tf_math_add_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S3_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S3_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S3_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S3_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.21520 out: 0.08713  BIASN: 0 PRENORM: 0 NE16_PADVAL: [0] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S3_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH,
                    AT_MEM_UNDEF, ConstInfo("S3_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_1_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_1_c.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_1_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_1_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S6_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S6_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S6_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S6_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.60906 out: 0.25811  BIASN: 0 PRENORM: 0 NE16_PADVAL: [3] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S6_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH,
                    AT_MEM_UNDEF, ConstInfo("S6_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_2_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_2_c.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_2_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_2_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S9_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S9_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S9_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S9_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.37514 out: 0.12827  BIASN: 0 PRENORM: 0 NE16_PADVAL: [1] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S9_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH,
                    AT_MEM_UNDEF, ConstInfo("S9_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.26<(u8-2.00)*0.12826827<32.45 out_q: -0.59<(u8-4.00)*0.14859165<37.30
          TCArgInfo("signed char * __restrict__", "S11_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S11_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_4_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_4_c.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_4_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_4_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S14_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S14_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.42366 out: 0.18595  BIASN: 0 PRENORM: 0 NE16_PADVAL: [2] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S14_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S14_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_5_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_5_c.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_5_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_5_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S17_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S17_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [1] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S17_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S17_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_6_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_6_c.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_8_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_8_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S22_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S22_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.25758 out: 0.05961  BIASN: 0 PRENORM: 0 NE16_PADVAL: [4] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S22_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S22_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_7_c", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_7_c.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_9_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_9_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S25_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S25_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.08139 out: 0.04049  BIASN: 0 PRENORM: 0 NE16_PADVAL: [5] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S25_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S25_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_10_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_10_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_12_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_12_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S28_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S28_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06402 out: 0.02958  BIASN: 0 PRENORM: 0 NE16_PADVAL: [7] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S28_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S28_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.27<(u8-9.00)*0.02958170<7.28 out_q: -0.57<(u8-12.00)*0.04745247<11.53
          TCArgInfo("signed char * __restrict__", "S30_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S30_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_14_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_14_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_16_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_16_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S33_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S33_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04778 out: 0.02469  BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S33_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S33_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_15_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_15_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_17_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_17_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S36_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S36_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S36_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S36_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_18_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_18_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_22_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_22_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S41_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S41_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.05669 out: 0.02735  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S41_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S41_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_26_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_26_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_30_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_30_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S44_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S44_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S44_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S44_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.05035 out: 0.02601  BIASN: 0 PRENORM: 0 NE16_PADVAL: [10] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S44_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S44_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_27_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_27_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_31_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_31_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S47_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S47_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S47_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S47_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04596 out: 0.02332  BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S47_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S47_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.28<(u8-12.00)*0.02331822<5.67 out_q: -0.55<(u8-17.00)*0.03223196<7.67
          TCArgInfo("signed char * __restrict__", "S49_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S49_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_29_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_29_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_33_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_33_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S52_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S52_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S52_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S52_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04921 out: 0.02414  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S52_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S52_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_30_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_30_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_34_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_34_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S55_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S55_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S55_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S55_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S55_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S55_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_31_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_31_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_37_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_37_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S60_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S60_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S60_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S60_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04926 out: 0.02315  BIASN: 0 PRENORM: 0 NE16_PADVAL: [17] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S60_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S60_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.28<(u8-12.00)*0.02315437<5.63 out_q: -0.29<(u8-9.00)*0.03224707<7.93
          TCArgInfo("signed char * __restrict__", "S61_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S61_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_32_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_32_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_38_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_38_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S64_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S64_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S64_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S64_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04801 out: 0.02400  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S64_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S64_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_33_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_33_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_39_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_39_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S67_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S67_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S67_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S67_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.05233 out: 0.02700  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S67_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S67_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.27<(u8-10.00)*0.02699653<6.61 out_q: -0.53<(u8-19.00)*0.02807462<6.63
          TCArgInfo("signed char * __restrict__", "S69_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S69_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_35_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_35_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_41_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_41_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S72_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S72_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S72_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S72_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.05746 out: 0.03339  BIASN: 0 PRENORM: 0 NE16_PADVAL: [10] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S72_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S72_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_36_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_36_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_42_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_42_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S75_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S75_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S75_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S75_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S75_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S75_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_37_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_37_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_45_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_45_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S80_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S80_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S80_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S80_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06514 out: 0.02612  BIASN: 0 PRENORM: 0 NE16_PADVAL: [19] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S80_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S80_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_38_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_38_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_46_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_46_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S83_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S83_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S83_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S83_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04436 out: 0.03037  BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S83_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S83_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.27<(u8-9.00)*0.03037225<7.47 out_q: 0.00<(u8-0.00)*0.02928024<7.47 forced
          TCArgInfo("signed char * __restrict__", "S84_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S84_Infos.tensor", 1, 1, 8, 0)),
          // no activation ACTSCALE: [1] ACTSCALEN: [0]
          TCArgInfo("signed char * __restrict__", "S85_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S85_Infos.tensor", 1, 1, 8, 0)),
          // no activation ACTSCALE: [1] ACTSCALEN: [0]
          TCArgInfo("signed char * __restrict__", "S86_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S86_Infos.tensor", 1, 1, 8, 0)),
          // no activation ACTSCALE: [1] ACTSCALEN: [0]
          TCArgInfo("signed char * __restrict__", "S87_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S87_Infos.tensor", 1, 1, 8, 0)),
          // in q: 0.00<(u8-0.00)*0.02928024<7.47 forced out_q: -0.27<(u8-9.00)*0.03037225<7.47
          TCArgInfo("signed char * __restrict__", "S88_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S88_Infos.tensor", 1, 1, 8, 0)),
          // in q: 0.00<(u8-0.00)*0.02928024<7.47 forced out_q: -0.27<(u8-9.00)*0.03037225<7.47
          TCArgInfo("signed char * __restrict__", "S89_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S89_Infos.tensor", 1, 1, 8, 0)),
          // in q: 0.00<(u8-0.00)*0.02928024<7.47 forced out_q: -0.27<(u8-9.00)*0.03037225<7.47
          TCArgInfo("signed char * __restrict__", "S90_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S90_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_39_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_39_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_47_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_47_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S94_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S94_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S94_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S94_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.07130 out: 0.03392  BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S94_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S94_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_40_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_40_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_48_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_48_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S97_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S97_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S97_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S97_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06004 out: 0.03225  BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S97_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S97_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_41_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_41_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_49_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_49_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S102_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S102_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S102_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S102_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04611 out: 0.02220  BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S102_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S102_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.29<(u8-13.00)*0.02220040<5.37 out_q: -0.29<(u8-13.00)*0.02268319<5.49
          TCArgInfo("signed char * __restrict__", "S104_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S104_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_43_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_43_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_51_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_51_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S107_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S107_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S107_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S107_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.03877 out: 0.02203  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S107_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S107_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_44_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_44_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_52_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_52_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S110_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S110_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S110_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S110_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06029 out: 0.02268  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S110_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S110_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_45_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_45_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_53_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_53_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S114_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S114_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S114_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S114_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04535 out: 0.02142  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S114_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S114_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_46_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_46_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_54_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_54_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S117_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S117_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S117_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S117_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.03178 out: 0.02076  BIASN: 0 PRENORM: 0 NE16_PADVAL: [13] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S117_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S117_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.27<(u8-13.00)*0.02076319<5.02 out_q: -0.27<(u8-10.00)*0.02734894<6.70
          TCArgInfo("signed char * __restrict__", "S119_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S119_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.27<(u8-13.00)*0.02076319<5.02 out_q: -0.29<(u8-14.00)*0.02080764<5.01
          TCArgInfo("signed char * __restrict__", "S121_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S121_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_47_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_47_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_55_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_55_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S124_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S124_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S124_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S124_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04732 out: 0.02612  BIASN: 0 PRENORM: 0 NE16_PADVAL: [10] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S124_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S124_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.29<(u8-11.00)*0.02612390<6.37 out_q: -0.30<(u8-10.00)*0.02986316<7.32
          TCArgInfo("signed char * __restrict__", "S126_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S126_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_49_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_49_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_57_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_57_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S129_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S129_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S129_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S129_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04448 out: 0.02457  BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S129_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S129_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_50_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_50_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_58_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_58_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S132_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S132_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S132_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S132_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.05143 out: 0.02986  BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S132_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S132_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_53_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_53_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_61_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_61_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S136_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S136_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S136_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S136_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06853 out: 0.03598  BIASN: 0 PRENORM: 0 NE16_PADVAL: [10] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S136_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S136_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_61_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_61_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_69_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_69_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S139_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S139_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S139_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S139_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04299 out: 0.02081  BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S139_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S139_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_64_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_64_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_72_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_72_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S143_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S143_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S143_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S143_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06468 out: 0.02439  BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S143_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S143_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_68_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_68_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_76_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_76_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S146_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S146_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S146_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S146_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.16247 out: 0.09189  BIASN: 0 PRENORM: 0 NE16_PADVAL: [11] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S146_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S146_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_67_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_67_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_75_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_75_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S149_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S149_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S149_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S149_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04174 out: 0.01940  BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S149_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S149_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_71_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_71_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_79_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_79_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S152_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S152_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S152_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S152_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06380 out: 0.03986  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S152_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S152_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_72_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_72_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_80_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_80_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S155_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S155_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S155_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S155_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04773 out: 0.02320  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S155_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S155_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.28<(u8-12.00)*0.02320002<5.64 out_q: -0.27<(u8-6.00)*0.04524090<11.26
          TCArgInfo("signed char * __restrict__", "S157_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S157_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_74_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_74_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_82_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_82_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S160_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S160_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S160_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S160_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [3] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S160_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S160_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_77_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_77_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_85_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_85_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S163_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S163_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S163_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S163_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [7] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S163_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S163_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_78_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_78_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_86_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_86_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S168_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S168_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S168_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S168_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.03965 out: 0.02259  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S168_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S168_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_79_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_79_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_87_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_87_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S171_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S171_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S171_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S171_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.07410 out: 0.04524  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S171_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S171_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_80_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_80_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_88_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_88_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S175_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S175_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S175_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S175_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06934 out: 0.03729  BIASN: 0 PRENORM: 0 NE16_PADVAL: [6] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S175_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S175_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_81_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_81_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_89_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_89_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S178_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S178_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S178_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S178_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.02458 out: 0.03225  BIASN: 0 PRENORM: 0 NE16_PADVAL: [7] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S178_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S178_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_82_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_82_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_90_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_90_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S182_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S182_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S182_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S182_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.09540 out: 0.02900  BIASN: 0 PRENORM: 0 NE16_PADVAL: [7] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S182_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S182_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_83_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_83_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_91_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_91_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S185_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S185_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S185_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S185_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.04262 out: 0.02315  BIASN: 0 PRENORM: 0 NE16_PADVAL: [7] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S185_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S185_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_84_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_84_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_92_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_92_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S188_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S188_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S188_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S188_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.11452 out: 0.04853  BIASN: 0 PRENORM: 0 NE16_PADVAL: [10] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S188_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S188_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_85_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_85_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_93_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_93_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S191_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S191_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S191_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S191_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.06321 out: 0.03490  BIASN: 0 PRENORM: 0 NE16_PADVAL: [12] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S191_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S191_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_86_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_86_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_94_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_94_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S194_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S194_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S194_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S194_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.02620 out: 0.01311  BIASN: 0 PRENORM: 0 NE16_PADVAL: [9] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S194_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S194_Infos.tensor", 1, 1, 8, 0)),
          // in q: -0.28<(u8-21.00)*0.01311130<3.07 out_q: -0.28<(u8-14.00)*0.01991241<4.80
          TCArgInfo("signed char * __restrict__", "S196_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S196_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_88_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_88_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_96_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_96_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S199_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S199_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S199_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S199_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [6] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S199_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S199_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_89_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_89_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_97_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_97_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S202_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S202_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S202_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S202_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [8] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S202_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S202_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_90_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_90_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_98_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_98_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S207_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S207_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S207_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S207_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.02735 out: 0.01489  BIASN: 0 PRENORM: 0 NE16_PADVAL: [21] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S207_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S207_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_91_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_91_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_99_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_99_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S210_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S210_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S210_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S210_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.03438 out: 0.01991  BIASN: 0 PRENORM: 0 NE16_PADVAL: [19] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S210_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S210_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_92_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_92_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_100_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_100_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S214_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S214_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S214_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S214_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.03172 out: 0.01689  BIASN: 0 PRENORM: 0 NE16_PADVAL: [14] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S214_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S214_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_93_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_93_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_101_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_101_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S217_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S217_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S217_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S217_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.00009 out: 0.00005  BIASN: 0 PRENORM: 0 NE16_PADVAL: [16] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S217_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S217_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_94_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_94_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_102_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_102_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S220_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S220_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S220_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S220_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.03477 out: 0.02657  BIASN: 0 PRENORM: 0 NE16_PADVAL: [16] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S220_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S220_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_95_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_95_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_103_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_103_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S223_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S223_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S223_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S223_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.00000 out: 0.00000  BIASN: 0 PRENORM: 0 NE16_PADVAL: [111] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S223_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S223_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_96_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_96_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_104_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_104_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S226_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S226_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S226_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S226_Mul_shift.tensor", 1, 1, 8, 0)),
          // in: 0.01443 out: 0.00875  BIASN: 0 PRENORM: 0 NE16_PADVAL: [10] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S226_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S226_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_97_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_97_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_105_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_105_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S229_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S229_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S229_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S229_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [132] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S229_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S229_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_98_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_98_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_math_add_106_add_y", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_add_106_add_y.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S232_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S232_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S232_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S232_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [32] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S232_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S232_Infos.tensor", 1, 1, 8, 0)),
          // in q: -19.79<(u8-134.00)*0.14768411<17.87 out_q: -32.00<(i8-0.00)*0.25000000<31.75 forced
          TCArgInfo("signed char * __restrict__", "S238_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S238_Infos.tensor", 1, 1, 8, 0)),
          // in: 0.25000 out: 0.00003  BIASL_SM: [13]
          TCArgInfo("signed char * __restrict__", "S239_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S239_Infos.tensor", 1, 1, 8, 0)),
          // in q: -1.00<(i16-0.00)*0.00003052<1.00 out_q: 0.00<(u8-0.00)*0.00373763<0.95
          TCArgInfo("signed char * __restrict__", "S240_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S240_Infos.tensor", 1, 1, 8, 0)),
          // in q: -19.79<(u8-134.00)*0.14768411<17.87 out_q: -6.29<(u8-128.00)*0.04913386<6.24 forced
          TCArgInfo("signed char * __restrict__", "S242_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S242_Infos.tensor", 1, 1, 8, 0)),
          // in: 0.04913 out: 0.00787  actscale: [1] actscalen: [0] a0: [128] b0: 0 c0: 0
          TCArgInfo("signed char * __restrict__", "S243_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S243_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned char * __restrict__", "Model_37_tf_nn_convolution_99__15e5e2e5_0", ARG_SCOPE_GLOBAL,
                    ARG_DIR_CONSTIN, AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_99__15e5e2e5_0.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed int * __restrict__", "Model_37_tf_nn_convolution_99_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_nn_convolution_99_.tensor", 1, 1, 32, 0)),
          TCArgInfo("unsigned char * __restrict__", "S247_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S247_Mul_scale.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "S247_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S247_Mul_shift.tensor", 1, 1, 8, 0)),
          // no activation BIASN: 0 PRENORM: 0 NE16_PADVAL: [0] NE16_WOFFSET: [-128]
          TCArgInfo("signed char * __restrict__", "S247_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("S247_Infos.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "Model_37_6790", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_6790.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "Model_37_tf_math_multiply_201_", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF,
                    ConstInfo("Model_37_tf_math_multiply_201_.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "Model_37_6790_1", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("Model_37_6790_1.tensor", 1, 1, 8, 0)),
          TCArgInfo("unsigned short * __restrict__", "SigmoidLUTTable", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("SigmoidLUTTable.tensor", 1, 1, 16, 0)),
          TCArgInfo("unsigned char * __restrict__", "SigmoidLUT_u8", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN,
                    AT_MEM_L3_DEFAULTFLASH, AT_MEM_UNDEF, ConstInfo("SigmoidLUT_u8.tensor", 1, 1, 8, 0)),
          TCArgInfo("signed char * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0),
          TCArgInfo("unsigned char * __restrict__", "Output_2", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0)),
      /* Locals, allocated dynamically */
      CArgs(124,
            TCArgInfo("unsigned char * __restrict__", "S3_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S6_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S9_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S10_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S10_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S11_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S14_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S17_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S18_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S19_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S22_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S25_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S28_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S29_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S29_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S30_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S33_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S36_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S37_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S38_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S41_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S44_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S47_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S48_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S48_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S49_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S52_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S55_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S56_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S57_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S60_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S61_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S64_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S67_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S68_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S68_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S69_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S72_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S75_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S76_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S77_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S80_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S83_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S84_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S85_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S86_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S87_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S88_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S89_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S90_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S91_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S94_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S97_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S98_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S99_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S102_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S103_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S103_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S104_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S107_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S110_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S111_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S114_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S117_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S118_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S119_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S120_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S121_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S124_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S125_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S125_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S126_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S129_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S132_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S133_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S136_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S139_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S140_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S143_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S146_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S149_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S152_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S155_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S156_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S156_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S157_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S160_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S163_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S168_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S171_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S172_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S175_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S178_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S179_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S182_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S185_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S188_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S191_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S194_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S195_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S195_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S196_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S199_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S202_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S207_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S210_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S211_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S214_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S217_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S220_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S223_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S226_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S229_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S232_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S235_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S236_Output_1", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S236_Output_0", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S238_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("signed short * __restrict__", "S239_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S240_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S241_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S242_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("unsigned char * __restrict__", "S247_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S256_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF,
                      AT_MEM_UNDEF, 0)));

  // Stacked tensors for concats and splits
  AddStackedTensors("S235_Output", 3, "S164_Output", "S203_Output", "S233_Output");
  AddStackedTensors("S256_Output", 2, "S255_Output_1", "S255_Output_0");
  AddStackedTensors("S247_Output", 2, "S249_Output_0", "S249_Output_1");

  // Node S3_CONV_2D_0_1_fusion inq 0.00<(u8-0.00)*0.00392157<1.00 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.26<(u8-3.00)*0.08712974<21.96 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S3_CONV_2D_0_1_fusion",
          Bindings(8, GNodeArg(GNA_IN, "Input_1", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_con", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_add_y", 0), GNodeArg(GNA_OUT, "S3_Output", 0),
                   GNodeArg(GNA_IN, "S3_Mul_scale", 0), GNodeArg(GNA_IN, "S3_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S3_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S6_CONV_2D_0_5_fusion inq -0.26<(u8-3.00)*0.08712974<21.96 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.26<(u8-1.00)*0.25811303<65.56 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S6_CONV_2D_0_5_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S3_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_1_c", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_1_add_y", 0), GNodeArg(GNA_OUT, "S6_Output", 0),
                   GNodeArg(GNA_IN, "S6_Mul_scale", 0), GNodeArg(GNA_IN, "S6_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S6_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S9_CONV_2D_0_8_fusion inq -0.26<(u8-1.00)*0.25811303<65.56 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.26<(u8-2.00)*0.12826827<32.45 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S9_CONV_2D_0_8_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S6_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_2_c", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_2_add_y", 0), GNodeArg(GNA_OUT, "S9_Output", 0),
                   GNodeArg(GNA_IN, "S9_Mul_scale", 0), GNodeArg(GNA_IN, "S9_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S9_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_8_split inq -0.26<(u8-2.00)*0.12826827<32.45 outq -0.26<(u8-2.00)*0.12826827<32.45
  AddNode("S10_CONV_2D_0_8_split", Bindings(3, GNodeArg(GNA_IN, "S9_Output", 0), GNodeArg(GNA_OUT, "S10_Output_0", 0),
                                            GNodeArg(GNA_OUT, "S10_Output_1", 0)));
  // Node CONV_2D_0_8_split_copy_qout0 inq -0.26<(u8-2.00)*0.12826827<32.45 outq -0.59<(u8-4.00)*0.14859165<37.30
  AddNode("S11_CONV_2D_0_8_split_copy_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S10_Output_1", 0), GNodeArg(GNA_OUT, "S11_Output", 0),
                   GNodeArg(GNA_IN, "S11_Infos", 0)));
  // Node S14_CONV_2D_0_14_fusion inq -0.26<(u8-2.00)*0.12826827<32.45 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.19<(u8-1.00)*0.18594822<47.23 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S14_CONV_2D_0_14_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S10_Output_0", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_4_c", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_4_add_y", 0), GNodeArg(GNA_OUT, "S14_Output", 0),
                   GNodeArg(GNA_IN, "S14_Mul_scale", 0), GNodeArg(GNA_IN, "S14_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S14_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S17_CONV_2D_0_17 inq -0.19<(u8-1.00)*0.18594822<47.23 weightsq chan<(u8-128.00)*chan<chan outq
  // -27.81<(u8-122.00)*0.22791430<30.31 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S17_CONV_2D_0_17",
          Bindings(7, GNodeArg(GNA_IN, "S14_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_5_c", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_5_add_y", 0), GNodeArg(GNA_OUT, "S17_Output", 0),
                   GNodeArg(GNA_IN, "S17_Mul_scale", 0), GNodeArg(GNA_IN, "S17_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S17_Infos", 0)));
  // Node expr_0 in_qs [-27.81<(u8-122.00)*0.22791430<30.31,-0.26<(u8-2.00)*0.12826827<32.45] out_qs
  // [-0.59<(u8-4.00)*0.14859165<37.30]
  AddNode("S18_expr_0", Bindings(4, GNodeArg(GNA_IN, "S17_Output", 0), GNodeArg(GNA_IN, "S10_Output_0", 0),
                                 GNodeArg(GNA_OUT, "S18_Output", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_21 inq -0.59<(u8-4.00)*0.14859165<37.30 outq -0.59<(u8-4.00)*0.14859165<37.30
  AddNode("S19_CONCAT_0_21", Bindings(3, GNodeArg(GNA_IN, "S18_Output", 0), GNodeArg(GNA_IN, "S11_Output", 0),
                                      GNodeArg(GNA_OUT, "S19_Output", 0)));
  // Node S22_CONV_2D_0_22_fusion inq -0.59<(u8-4.00)*0.14859165<37.30 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.30<(u8-5.00)*0.05960839<14.90 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S22_CONV_2D_0_22_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S19_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_6_c", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_8_add_y", 0), GNodeArg(GNA_OUT, "S22_Output", 0),
                   GNodeArg(GNA_IN, "S22_Mul_scale", 0), GNodeArg(GNA_IN, "S22_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S22_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S25_CONV_2D_0_26_fusion inq -0.30<(u8-5.00)*0.05960839<14.90 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-7.00)*0.04049354<10.04 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S25_CONV_2D_0_26_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S22_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_7_c", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_9_add_y", 0), GNodeArg(GNA_OUT, "S25_Output", 0),
                   GNodeArg(GNA_IN, "S25_Mul_scale", 0), GNodeArg(GNA_IN, "S25_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S25_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S28_CONV_2D_0_29_fusion inq -0.28<(u8-7.00)*0.04049354<10.04 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-9.00)*0.02958170<7.28 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S28_CONV_2D_0_29_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S25_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_10_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_12_add_y", 0), GNodeArg(GNA_OUT, "S28_Output", 0),
                   GNodeArg(GNA_IN, "S28_Mul_scale", 0), GNodeArg(GNA_IN, "S28_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S28_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_29_split inq -0.27<(u8-9.00)*0.02958170<7.28 outq -0.27<(u8-9.00)*0.02958170<7.28
  AddNode("S29_CONV_2D_0_29_split", Bindings(3, GNodeArg(GNA_IN, "S28_Output", 0), GNodeArg(GNA_OUT, "S29_Output_0", 0),
                                             GNodeArg(GNA_OUT, "S29_Output_1", 0)));
  // Node CONV_2D_0_29_split_copy_qout0 inq -0.27<(u8-9.00)*0.02958170<7.28 outq -0.57<(u8-12.00)*0.04745247<11.53
  AddNode("S30_CONV_2D_0_29_split_copy_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S29_Output_1", 0), GNodeArg(GNA_OUT, "S30_Output", 0),
                   GNodeArg(GNA_IN, "S30_Infos", 0)));
  // Node S33_CONV_2D_0_32_fusion inq -0.27<(u8-9.00)*0.02958170<7.28 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-11.00)*0.02468630<6.02 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S33_CONV_2D_0_32_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S29_Output_0", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_14_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_16_add_y", 0), GNodeArg(GNA_OUT, "S33_Output", 0),
                   GNodeArg(GNA_IN, "S33_Mul_scale", 0), GNodeArg(GNA_IN, "S33_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S33_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S36_CONV_2D_0_35 inq -0.27<(u8-11.00)*0.02468630<6.02 weightsq chan<(u8-128.00)*chan<chan outq
  // -8.69<(u8-117.00)*0.07424011<10.25 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S36_CONV_2D_0_35",
          Bindings(7, GNodeArg(GNA_IN, "S33_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_15_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_17_add_y", 0), GNodeArg(GNA_OUT, "S36_Output", 0),
                   GNodeArg(GNA_IN, "S36_Mul_scale", 0), GNodeArg(GNA_IN, "S36_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S36_Infos", 0)));
  // Node expr_2 in_qs [-8.69<(u8-117.00)*0.07424011<10.25,-0.27<(u8-9.00)*0.02958170<7.28] out_qs
  // [-0.57<(u8-12.00)*0.04745247<11.53]
  AddNode("S37_expr_2", Bindings(4, GNodeArg(GNA_IN, "S36_Output", 0), GNodeArg(GNA_IN, "S29_Output_0", 0),
                                 GNodeArg(GNA_OUT, "S37_Output", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_42 inq -0.57<(u8-12.00)*0.04745247<11.53 outq -0.57<(u8-12.00)*0.04745247<11.53
  AddNode("S38_CONCAT_0_42", Bindings(3, GNodeArg(GNA_IN, "S37_Output", 0), GNodeArg(GNA_IN, "S30_Output", 0),
                                      GNodeArg(GNA_OUT, "S38_Output", 0)));
  // Node S41_CONV_2D_0_43_fusion inq -0.57<(u8-12.00)*0.04745247<11.53 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-10.00)*0.02734894<6.70 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S41_CONV_2D_0_43_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S38_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_18_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_22_add_y", 0), GNodeArg(GNA_OUT, "S41_Output", 0),
                   GNodeArg(GNA_IN, "S41_Mul_scale", 0), GNodeArg(GNA_IN, "S41_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S41_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S44_CONV_2D_0_47_fusion inq -0.27<(u8-10.00)*0.02734894<6.70 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-11.00)*0.02601145<6.35 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S44_CONV_2D_0_47_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S41_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_26_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_30_add_y", 0), GNodeArg(GNA_OUT, "S44_Output", 0),
                   GNodeArg(GNA_IN, "S44_Mul_scale", 0), GNodeArg(GNA_IN, "S44_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S44_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S47_CONV_2D_0_50_fusion inq -0.29<(u8-11.00)*0.02601145<6.35 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-12.00)*0.02331822<5.67 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S47_CONV_2D_0_50_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S44_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_27_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_31_add_y", 0), GNodeArg(GNA_OUT, "S47_Output", 0),
                   GNodeArg(GNA_IN, "S47_Mul_scale", 0), GNodeArg(GNA_IN, "S47_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S47_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_50_split inq -0.28<(u8-12.00)*0.02331822<5.67 outq -0.28<(u8-12.00)*0.02331822<5.67
  AddNode("S48_CONV_2D_0_50_split", Bindings(3, GNodeArg(GNA_IN, "S47_Output", 0), GNodeArg(GNA_OUT, "S48_Output_0", 0),
                                             GNodeArg(GNA_OUT, "S48_Output_1", 0)));
  // Node CONV_2D_0_50_split_copy_qout0 inq -0.28<(u8-12.00)*0.02331822<5.67 outq -0.55<(u8-17.00)*0.03223196<7.67
  AddNode("S49_CONV_2D_0_50_split_copy_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S48_Output_1", 0), GNodeArg(GNA_OUT, "S49_Output", 0),
                   GNodeArg(GNA_IN, "S49_Infos", 0)));
  // Node S52_CONV_2D_0_53_fusion inq -0.28<(u8-12.00)*0.02331822<5.67 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-12.00)*0.02413978<5.87 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S52_CONV_2D_0_53_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S48_Output_0", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_29_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_33_add_y", 0), GNodeArg(GNA_OUT, "S52_Output", 0),
                   GNodeArg(GNA_IN, "S52_Mul_scale", 0), GNodeArg(GNA_IN, "S52_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S52_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S55_CONV_2D_0_56 inq -0.29<(u8-12.00)*0.02413978<5.87 weightsq chan<(u8-128.00)*chan<chan outq
  // -8.00<(u8-139.00)*0.05752878<6.67 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S55_CONV_2D_0_56",
          Bindings(7, GNodeArg(GNA_IN, "S52_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_30_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_34_add_y", 0), GNodeArg(GNA_OUT, "S55_Output", 0),
                   GNodeArg(GNA_IN, "S55_Mul_scale", 0), GNodeArg(GNA_IN, "S55_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S55_Infos", 0)));
  // Node expr_3 in_qs [-8.00<(u8-139.00)*0.05752878<6.67,-0.28<(u8-12.00)*0.02331822<5.67] out_qs
  // [-0.55<(u8-17.00)*0.03223196<7.67]
  AddNode("S56_expr_3", Bindings(4, GNodeArg(GNA_IN, "S55_Output", 0), GNodeArg(GNA_IN, "S48_Output_0", 0),
                                 GNodeArg(GNA_OUT, "S56_Output", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_63 inq -0.55<(u8-17.00)*0.03223196<7.67 outq -0.55<(u8-17.00)*0.03223196<7.67
  AddNode("S57_CONCAT_0_63", Bindings(3, GNodeArg(GNA_IN, "S56_Output", 0), GNodeArg(GNA_IN, "S49_Output", 0),
                                      GNodeArg(GNA_OUT, "S57_Output", 0)));
  // Node S60_CONV_2D_0_64_fusion inq -0.55<(u8-17.00)*0.03223196<7.67 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-12.00)*0.02315437<5.63 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S60_CONV_2D_0_64_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S57_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_31_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_37_add_y", 0), GNodeArg(GNA_OUT, "S60_Output", 0),
                   GNodeArg(GNA_IN, "S60_Mul_scale", 0), GNodeArg(GNA_IN, "S60_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S60_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_64_fusion_qout0 inq -0.28<(u8-12.00)*0.02315437<5.63 outq -0.29<(u8-9.00)*0.03224707<7.93
  AddNode("S61_CONV_2D_0_64_fusion_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S60_Output", 0), GNodeArg(GNA_OUT, "S61_Output", 0),
                   GNodeArg(GNA_IN, "S61_Infos", 0)));
  // Node S64_CONV_2D_0_68_fusion inq -0.28<(u8-12.00)*0.02315437<5.63 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-12.00)*0.02399731<5.83 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S64_CONV_2D_0_68_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S60_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_32_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_38_add_y", 0), GNodeArg(GNA_OUT, "S64_Output", 0),
                   GNodeArg(GNA_IN, "S64_Mul_scale", 0), GNodeArg(GNA_IN, "S64_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S64_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S67_CONV_2D_0_71_fusion inq -0.29<(u8-12.00)*0.02399731<5.83 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-10.00)*0.02699653<6.61 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S67_CONV_2D_0_71_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S64_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_33_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_39_add_y", 0), GNodeArg(GNA_OUT, "S67_Output", 0),
                   GNodeArg(GNA_IN, "S67_Mul_scale", 0), GNodeArg(GNA_IN, "S67_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S67_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_71_split inq -0.27<(u8-10.00)*0.02699653<6.61 outq -0.27<(u8-10.00)*0.02699653<6.61
  AddNode("S68_CONV_2D_0_71_split", Bindings(3, GNodeArg(GNA_IN, "S67_Output", 0), GNodeArg(GNA_OUT, "S68_Output_0", 0),
                                             GNodeArg(GNA_OUT, "S68_Output_1", 0)));
  // Node CONV_2D_0_71_split_copy_qout0 inq -0.27<(u8-10.00)*0.02699653<6.61 outq -0.53<(u8-19.00)*0.02807462<6.63
  AddNode("S69_CONV_2D_0_71_split_copy_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S68_Output_1", 0), GNodeArg(GNA_OUT, "S69_Output", 0),
                   GNodeArg(GNA_IN, "S69_Infos", 0)));
  // Node S72_CONV_2D_0_74_fusion inq -0.27<(u8-10.00)*0.02699653<6.61 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-8.00)*0.03339461<8.25 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S72_CONV_2D_0_74_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S68_Output_0", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_35_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_41_add_y", 0), GNodeArg(GNA_OUT, "S72_Output", 0),
                   GNodeArg(GNA_IN, "S72_Mul_scale", 0), GNodeArg(GNA_IN, "S72_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S72_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S75_CONV_2D_0_77 inq -0.27<(u8-8.00)*0.03339461<8.25 weightsq chan<(u8-128.00)*chan<chan outq
  // -9.74<(u8-153.00)*0.06368329<6.50 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S75_CONV_2D_0_77",
          Bindings(7, GNodeArg(GNA_IN, "S72_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_36_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_42_add_y", 0), GNodeArg(GNA_OUT, "S75_Output", 0),
                   GNodeArg(GNA_IN, "S75_Mul_scale", 0), GNodeArg(GNA_IN, "S75_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S75_Infos", 0)));
  // Node expr_4 in_qs [-9.74<(u8-153.00)*0.06368329<6.50,-0.27<(u8-10.00)*0.02699653<6.61] out_qs
  // [-0.53<(u8-19.00)*0.02807462<6.63]
  AddNode("S76_expr_4", Bindings(4, GNodeArg(GNA_IN, "S75_Output", 0), GNodeArg(GNA_IN, "S68_Output_0", 0),
                                 GNodeArg(GNA_OUT, "S76_Output", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_84 inq -0.53<(u8-19.00)*0.02807462<6.63 outq -0.53<(u8-19.00)*0.02807462<6.63
  AddNode("S77_CONCAT_0_84", Bindings(3, GNodeArg(GNA_IN, "S76_Output", 0), GNodeArg(GNA_IN, "S69_Output", 0),
                                      GNodeArg(GNA_OUT, "S77_Output", 0)));
  // Node S80_CONV_2D_0_85_fusion inq -0.53<(u8-19.00)*0.02807462<6.63 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-11.00)*0.02611692<6.37 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S80_CONV_2D_0_85_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S77_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_37_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_45_add_y", 0), GNodeArg(GNA_OUT, "S80_Output", 0),
                   GNodeArg(GNA_IN, "S80_Mul_scale", 0), GNodeArg(GNA_IN, "S80_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S80_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S83_CONV_2D_0_88_fusion inq -0.29<(u8-11.00)*0.02611692<6.37 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-9.00)*0.03037225<7.47 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S83_CONV_2D_0_88_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S80_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_38_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_46_add_y", 0), GNodeArg(GNA_OUT, "S83_Output", 0),
                   GNodeArg(GNA_IN, "S83_Mul_scale", 0), GNodeArg(GNA_IN, "S83_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S83_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_88_fusion_qout0 inq -0.27<(u8-9.00)*0.03037225<7.47 outq 0.00<(u8-0.00)*0.02928024<7.47 forced
  AddNode("S84_CONV_2D_0_88_fusion_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S83_Output", 0), GNodeArg(GNA_OUT, "S84_Output", 0),
                   GNodeArg(GNA_IN, "S84_Infos", 0)));
  // Node MAX_POOL_2D_0_91 inq 0.00<(u8-0.00)*0.02928024<7.47 forced outq 0.00<(u8-0.00)*0.02928024<7.47 forced
  AddNode("S85_MAX_POOL_2D_0_91", Bindings(3, GNodeArg(GNA_IN, "S84_Output", 0), GNodeArg(GNA_OUT, "S85_Output", 0),
                                           GNodeArg(GNA_IN, "S85_Infos", 0)));
  // Node MAX_POOL_2D_0_92 inq 0.00<(u8-0.00)*0.02928024<7.47 forced outq 0.00<(u8-0.00)*0.02928024<7.47 forced
  AddNode("S86_MAX_POOL_2D_0_92", Bindings(3, GNodeArg(GNA_IN, "S85_Output", 0), GNodeArg(GNA_OUT, "S86_Output", 0),
                                           GNodeArg(GNA_IN, "S86_Infos", 0)));
  // Node MAX_POOL_2D_0_93 inq 0.00<(u8-0.00)*0.02928024<7.47 forced outq 0.00<(u8-0.00)*0.02928024<7.47 forced
  AddNode("S87_MAX_POOL_2D_0_93", Bindings(3, GNodeArg(GNA_IN, "S86_Output", 0), GNodeArg(GNA_OUT, "S87_Output", 0),
                                           GNodeArg(GNA_IN, "S87_Infos", 0)));
  // Node MAX_POOL_2D_0_93_qout0 inq 0.00<(u8-0.00)*0.02928024<7.47 forced outq -0.27<(u8-9.00)*0.03037225<7.47
  AddNode("S88_MAX_POOL_2D_0_93_qout0", Bindings(3, GNodeArg(GNA_IN, "S87_Output", 0),
                                                 GNodeArg(GNA_OUT, "S88_Output", 0), GNodeArg(GNA_IN, "S88_Infos", 0)));
  // Node MAX_POOL_2D_0_92_qout0 inq 0.00<(u8-0.00)*0.02928024<7.47 forced outq -0.27<(u8-9.00)*0.03037225<7.47
  AddNode("S89_MAX_POOL_2D_0_92_qout0", Bindings(3, GNodeArg(GNA_IN, "S86_Output", 0),
                                                 GNodeArg(GNA_OUT, "S89_Output", 0), GNodeArg(GNA_IN, "S89_Infos", 0)));
  // Node MAX_POOL_2D_0_91_qout0 inq 0.00<(u8-0.00)*0.02928024<7.47 forced outq -0.27<(u8-9.00)*0.03037225<7.47
  AddNode("S90_MAX_POOL_2D_0_91_qout0", Bindings(3, GNodeArg(GNA_IN, "S85_Output", 0),
                                                 GNodeArg(GNA_OUT, "S90_Output", 0), GNodeArg(GNA_IN, "S90_Infos", 0)));
  // Node CONCAT_0_94 inq -0.27<(u8-9.00)*0.03037225<7.47 outq -0.27<(u8-9.00)*0.03037225<7.47
  AddNode("S91_CONCAT_0_94", Bindings(5, GNodeArg(GNA_IN, "S83_Output", 0), GNodeArg(GNA_IN, "S90_Output", 0),
                                      GNodeArg(GNA_IN, "S89_Output", 0), GNodeArg(GNA_IN, "S88_Output", 0),
                                      GNodeArg(GNA_OUT, "S91_Output", 0)));
  // Node S94_CONV_2D_0_95_fusion inq -0.27<(u8-9.00)*0.03037225<7.47 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-8.00)*0.03392030<8.38 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S94_CONV_2D_0_95_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S91_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_39_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_47_add_y", 0), GNodeArg(GNA_OUT, "S94_Output", 0),
                   GNodeArg(GNA_IN, "S94_Mul_scale", 0), GNodeArg(GNA_IN, "S94_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S94_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S97_CONV_2D_0_98_fusion inq -0.27<(u8-8.00)*0.03392030<8.38 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-9.00)*0.03224707<7.93 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S97_CONV_2D_0_98_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S94_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_40_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_48_add_y", 0), GNodeArg(GNA_OUT, "S97_Output", 0),
                   GNodeArg(GNA_IN, "S97_Mul_scale", 0), GNodeArg(GNA_IN, "S97_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S97_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node RESIZE_NN_0_101 inq -0.29<(u8-9.00)*0.03224707<7.93 outq -0.29<(u8-9.00)*0.03224707<7.93
  AddNode("S98_RESIZE_NN_0_101", Bindings(2, GNodeArg(GNA_IN, "S97_Output", 0), GNodeArg(GNA_OUT, "S98_Output", 0)));
  // Node CONCAT_0_102 inq -0.29<(u8-9.00)*0.03224707<7.93 outq -0.29<(u8-9.00)*0.03224707<7.93
  AddNode("S99_CONCAT_0_102", Bindings(3, GNodeArg(GNA_IN, "S98_Output", 0), GNodeArg(GNA_IN, "S61_Output", 0),
                                       GNodeArg(GNA_OUT, "S99_Output", 0)));
  // Node S102_CONV_2D_0_103_fusion inq -0.29<(u8-9.00)*0.03224707<7.93 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-13.00)*0.02220040<5.37 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S102_CONV_2D_0_103_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S99_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_41_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_49_add_y", 0), GNodeArg(GNA_OUT, "S102_Output", 0),
                   GNodeArg(GNA_IN, "S102_Mul_scale", 0), GNodeArg(GNA_IN, "S102_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S102_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_103_split inq -0.29<(u8-13.00)*0.02220040<5.37 outq -0.29<(u8-13.00)*0.02220040<5.37
  AddNode("S103_CONV_2D_0_103_split",
          Bindings(3, GNodeArg(GNA_IN, "S102_Output", 0), GNodeArg(GNA_OUT, "S103_Output_0", 0),
                   GNodeArg(GNA_OUT, "S103_Output_1", 0)));
  // Node CONV_2D_0_103_split_copy_qout0 inq -0.29<(u8-13.00)*0.02220040<5.37 outq -0.29<(u8-13.00)*0.02268319<5.49
  AddNode("S104_CONV_2D_0_103_split_copy_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S103_Output_1", 0), GNodeArg(GNA_OUT, "S104_Output", 0),
                   GNodeArg(GNA_IN, "S104_Infos", 0)));
  // Node S107_CONV_2D_0_106_fusion inq -0.29<(u8-13.00)*0.02220040<5.37 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-13.00)*0.02203220<5.33 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S107_CONV_2D_0_106_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S103_Output_0", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_43_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_51_add_y", 0), GNodeArg(GNA_OUT, "S107_Output", 0),
                   GNodeArg(GNA_IN, "S107_Mul_scale", 0), GNodeArg(GNA_IN, "S107_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S107_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S110_CONV_2D_0_109_fusion inq -0.29<(u8-13.00)*0.02203220<5.33 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-13.00)*0.02268319<5.49 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S110_CONV_2D_0_109_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S107_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_44_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_52_add_y", 0), GNodeArg(GNA_OUT, "S110_Output", 0),
                   GNodeArg(GNA_IN, "S110_Mul_scale", 0), GNodeArg(GNA_IN, "S110_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S110_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_115 inq -0.29<(u8-13.00)*0.02268319<5.49 outq -0.29<(u8-13.00)*0.02268319<5.49
  AddNode("S111_CONCAT_0_115", Bindings(3, GNodeArg(GNA_IN, "S110_Output", 0), GNodeArg(GNA_IN, "S104_Output", 0),
                                        GNodeArg(GNA_OUT, "S111_Output", 0)));
  // Node S114_CONV_2D_0_116_fusion inq -0.29<(u8-13.00)*0.02268319<5.49 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-13.00)*0.02141804<5.18 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S114_CONV_2D_0_116_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S111_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_45_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_53_add_y", 0), GNodeArg(GNA_OUT, "S114_Output", 0),
                   GNodeArg(GNA_IN, "S114_Mul_scale", 0), GNodeArg(GNA_IN, "S114_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S114_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S117_CONV_2D_0_119_fusion inq -0.28<(u8-13.00)*0.02141804<5.18 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-13.00)*0.02076319<5.02 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S117_CONV_2D_0_119_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S114_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_46_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_54_add_y", 0), GNodeArg(GNA_OUT, "S117_Output", 0),
                   GNodeArg(GNA_IN, "S117_Mul_scale", 0), GNodeArg(GNA_IN, "S117_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S117_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node RESIZE_NN_0_122 inq -0.27<(u8-13.00)*0.02076319<5.02 outq -0.27<(u8-13.00)*0.02076319<5.02
  AddNode("S118_RESIZE_NN_0_122", Bindings(2, GNodeArg(GNA_IN, "S117_Output", 0), GNodeArg(GNA_OUT, "S118_Output", 0)));
  // Node RESIZE_NN_0_122_qout0 inq -0.27<(u8-13.00)*0.02076319<5.02 outq -0.27<(u8-10.00)*0.02734894<6.70
  AddNode("S119_RESIZE_NN_0_122_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S118_Output", 0), GNodeArg(GNA_OUT, "S119_Output", 0),
                   GNodeArg(GNA_IN, "S119_Infos", 0)));
  // Node CONCAT_0_123 inq -0.27<(u8-10.00)*0.02734894<6.70 outq -0.27<(u8-10.00)*0.02734894<6.70
  AddNode("S120_CONCAT_0_123", Bindings(3, GNodeArg(GNA_IN, "S119_Output", 0), GNodeArg(GNA_IN, "S41_Output", 0),
                                        GNodeArg(GNA_OUT, "S120_Output", 0)));
  // Node CONV_2D_0_119_fusion_qout0 inq -0.27<(u8-13.00)*0.02076319<5.02 outq -0.29<(u8-14.00)*0.02080764<5.01
  AddNode("S121_CONV_2D_0_119_fusion_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S117_Output", 0), GNodeArg(GNA_OUT, "S121_Output", 0),
                   GNodeArg(GNA_IN, "S121_Infos", 0)));
  // Node S124_CONV_2D_0_124_fusion inq -0.27<(u8-10.00)*0.02734894<6.70 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-11.00)*0.02612390<6.37 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S124_CONV_2D_0_124_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S120_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_47_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_55_add_y", 0), GNodeArg(GNA_OUT, "S124_Output", 0),
                   GNodeArg(GNA_IN, "S124_Mul_scale", 0), GNodeArg(GNA_IN, "S124_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S124_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_124_split inq -0.29<(u8-11.00)*0.02612390<6.37 outq -0.29<(u8-11.00)*0.02612390<6.37
  AddNode("S125_CONV_2D_0_124_split",
          Bindings(3, GNodeArg(GNA_IN, "S124_Output", 0), GNodeArg(GNA_OUT, "S125_Output_0", 0),
                   GNodeArg(GNA_OUT, "S125_Output_1", 0)));
  // Node CONV_2D_0_124_split_copy_qout0 inq -0.29<(u8-11.00)*0.02612390<6.37 outq -0.30<(u8-10.00)*0.02986316<7.32
  AddNode("S126_CONV_2D_0_124_split_copy_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S125_Output_1", 0), GNodeArg(GNA_OUT, "S126_Output", 0),
                   GNodeArg(GNA_IN, "S126_Infos", 0)));
  // Node S129_CONV_2D_0_127_fusion inq -0.29<(u8-11.00)*0.02612390<6.37 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-11.00)*0.02457360<6.00 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S129_CONV_2D_0_127_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S125_Output_0", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_49_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_57_add_y", 0), GNodeArg(GNA_OUT, "S129_Output", 0),
                   GNodeArg(GNA_IN, "S129_Mul_scale", 0), GNodeArg(GNA_IN, "S129_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S129_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S132_CONV_2D_0_130_fusion inq -0.27<(u8-11.00)*0.02457360<6.00 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.30<(u8-10.00)*0.02986316<7.32 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S132_CONV_2D_0_130_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S129_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_50_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_58_add_y", 0), GNodeArg(GNA_OUT, "S132_Output", 0),
                   GNodeArg(GNA_IN, "S132_Mul_scale", 0), GNodeArg(GNA_IN, "S132_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S132_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_136 inq -0.30<(u8-10.00)*0.02986316<7.32 outq -0.30<(u8-10.00)*0.02986316<7.32
  AddNode("S133_CONCAT_0_136", Bindings(3, GNodeArg(GNA_IN, "S132_Output", 0), GNodeArg(GNA_IN, "S126_Output", 0),
                                        GNodeArg(GNA_OUT, "S133_Output", 0)));
  // Node S136_CONV_2D_0_137_fusion inq -0.30<(u8-10.00)*0.02986316<7.32 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-8.00)*0.03597898<8.89 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S136_CONV_2D_0_137_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S133_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_53_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_61_add_y", 0), GNodeArg(GNA_OUT, "S136_Output", 0),
                   GNodeArg(GNA_IN, "S136_Mul_scale", 0), GNodeArg(GNA_IN, "S136_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S136_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S139_CONV_2D_0_141_fusion inq -0.29<(u8-8.00)*0.03597898<8.89 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-14.00)*0.02080764<5.01 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S139_CONV_2D_0_141_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S136_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_61_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_69_add_y", 0), GNodeArg(GNA_OUT, "S139_Output", 0),
                   GNodeArg(GNA_IN, "S139_Mul_scale", 0), GNodeArg(GNA_IN, "S139_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S139_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_144 inq -0.29<(u8-14.00)*0.02080764<5.01 outq -0.29<(u8-14.00)*0.02080764<5.01
  AddNode("S140_CONCAT_0_144", Bindings(3, GNodeArg(GNA_IN, "S139_Output", 0), GNodeArg(GNA_IN, "S121_Output", 0),
                                        GNodeArg(GNA_OUT, "S140_Output", 0)));
  // Node S143_CONV_2D_0_145_fusion inq -0.29<(u8-8.00)*0.03597898<8.89 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-11.00)*0.02439452<5.95 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S143_CONV_2D_0_145_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S136_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_64_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_72_add_y", 0), GNodeArg(GNA_OUT, "S143_Output", 0),
                   GNodeArg(GNA_IN, "S143_Mul_scale", 0), GNodeArg(GNA_IN, "S143_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S143_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S146_CONV_2D_0_148_fusion inq -0.27<(u8-11.00)*0.02439452<5.95 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-3.00)*0.09189220<23.16 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S146_CONV_2D_0_148_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S143_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_68_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_76_add_y", 0), GNodeArg(GNA_OUT, "S146_Output", 0),
                   GNodeArg(GNA_IN, "S146_Mul_scale", 0), GNodeArg(GNA_IN, "S146_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S146_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S149_CONV_2D_0_151_fusion inq -0.29<(u8-8.00)*0.03597898<8.89 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-14.00)*0.01939965<4.68 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S149_CONV_2D_0_151_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S136_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_67_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_75_add_y", 0), GNodeArg(GNA_OUT, "S149_Output", 0),
                   GNodeArg(GNA_IN, "S149_Mul_scale", 0), GNodeArg(GNA_IN, "S149_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S149_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S152_CONV_2D_0_154_fusion inq -0.27<(u8-14.00)*0.01939965<4.68 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-7.00)*0.03986241<9.89 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S152_CONV_2D_0_154_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S149_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_71_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_79_add_y", 0), GNodeArg(GNA_OUT, "S152_Output", 0),
                   GNodeArg(GNA_IN, "S152_Mul_scale", 0), GNodeArg(GNA_IN, "S152_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S152_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S155_CONV_2D_0_157_fusion inq -0.29<(u8-14.00)*0.02080764<5.01 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-12.00)*0.02320002<5.64 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S155_CONV_2D_0_157_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S140_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_72_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_80_add_y", 0), GNodeArg(GNA_OUT, "S155_Output", 0),
                   GNodeArg(GNA_IN, "S155_Mul_scale", 0), GNodeArg(GNA_IN, "S155_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S155_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_157_split inq -0.28<(u8-12.00)*0.02320002<5.64 outq -0.28<(u8-12.00)*0.02320002<5.64
  AddNode("S156_CONV_2D_0_157_split",
          Bindings(3, GNodeArg(GNA_IN, "S155_Output", 0), GNodeArg(GNA_OUT, "S156_Output_0", 0),
                   GNodeArg(GNA_OUT, "S156_Output_1", 0)));
  // Node CONV_2D_0_157_split_copy_qout0 inq -0.28<(u8-12.00)*0.02320002<5.64 outq -0.27<(u8-6.00)*0.04524090<11.26
  AddNode("S157_CONV_2D_0_157_split_copy_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S156_Output_1", 0), GNodeArg(GNA_OUT, "S157_Output", 0),
                   GNodeArg(GNA_IN, "S157_Infos", 0)));
  // Node S160_CONV_2D_0_163 inq -0.28<(u8-3.00)*0.09189220<23.16 weightsq chan<(u8-128.00)*chan<chan outq
  // -19.79<(u8-134.00)*0.14768411<17.87 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S160_CONV_2D_0_163",
          Bindings(7, GNodeArg(GNA_IN, "S146_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_74_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_82_add_y", 0), GNodeArg(GNA_OUT, "S160_Output", 0),
                   GNodeArg(GNA_IN, "S160_Mul_scale", 0), GNodeArg(GNA_IN, "S160_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S160_Infos", 0)));
  // Node S163_CONV_2D_0_164 inq -0.28<(u8-7.00)*0.03986241<9.89 weightsq chan<(u8-128.00)*chan<chan outq
  // -19.79<(u8-134.00)*0.14768411<17.87 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S163_CONV_2D_0_164",
          Bindings(7, GNodeArg(GNA_IN, "S152_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_77_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_85_add_y", 0), GNodeArg(GNA_OUT, "S163_Output", 0),
                   GNodeArg(GNA_IN, "S163_Mul_scale", 0), GNodeArg(GNA_IN, "S163_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S163_Infos", 0)));
  // Node CONCAT_0_165 inq -19.79<(u8-134.00)*0.14768411<17.87 outq -19.79<(u8-134.00)*0.14768411<17.87
  AddNode("S164_CONCAT_0_165", Bindings(3, GNodeArg(GNA_IN, "S160_Output", 0), GNodeArg(GNA_IN, "S163_Output", 0),
                                        GNodeArg(GNA_OUT, "S164_Output", 0)));
  // Node S168_CONV_2D_0_167_fusion inq -0.28<(u8-12.00)*0.02320002<5.64 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-12.00)*0.02258740<5.49 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S168_CONV_2D_0_167_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S156_Output_0", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_78_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_86_add_y", 0), GNodeArg(GNA_OUT, "S168_Output", 0),
                   GNodeArg(GNA_IN, "S168_Mul_scale", 0), GNodeArg(GNA_IN, "S168_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S168_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S171_CONV_2D_0_170_fusion inq -0.27<(u8-12.00)*0.02258740<5.49 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-6.00)*0.04524090<11.26 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S171_CONV_2D_0_170_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S168_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_79_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_87_add_y", 0), GNodeArg(GNA_OUT, "S171_Output", 0),
                   GNodeArg(GNA_IN, "S171_Mul_scale", 0), GNodeArg(GNA_IN, "S171_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S171_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_173 inq -0.27<(u8-6.00)*0.04524090<11.26 outq -0.27<(u8-6.00)*0.04524090<11.26
  AddNode("S172_CONCAT_0_173", Bindings(3, GNodeArg(GNA_IN, "S171_Output", 0), GNodeArg(GNA_IN, "S157_Output", 0),
                                        GNodeArg(GNA_OUT, "S172_Output", 0)));
  // Node S175_CONV_2D_0_174_fusion inq -0.27<(u8-6.00)*0.04524090<11.26 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.26<(u8-7.00)*0.03728715<9.25 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S175_CONV_2D_0_174_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S172_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_80_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_88_add_y", 0), GNodeArg(GNA_OUT, "S175_Output", 0),
                   GNodeArg(GNA_IN, "S175_Mul_scale", 0), GNodeArg(GNA_IN, "S175_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S175_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S178_CONV_2D_0_178_fusion inq -0.26<(u8-7.00)*0.03728715<9.25 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-9.00)*0.03224707<7.93 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S178_CONV_2D_0_178_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S175_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_81_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_89_add_y", 0), GNodeArg(GNA_OUT, "S178_Output", 0),
                   GNodeArg(GNA_IN, "S178_Mul_scale", 0), GNodeArg(GNA_IN, "S178_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S178_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_181 inq -0.29<(u8-9.00)*0.03224707<7.93 outq -0.29<(u8-9.00)*0.03224707<7.93
  AddNode("S179_CONCAT_0_181", Bindings(3, GNodeArg(GNA_IN, "S178_Output", 0), GNodeArg(GNA_IN, "S97_Output", 0),
                                        GNodeArg(GNA_OUT, "S179_Output", 0)));
  // Node S182_CONV_2D_0_182_fusion inq -0.26<(u8-7.00)*0.03728715<9.25 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-10.00)*0.02899599<7.10 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S182_CONV_2D_0_182_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S175_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_82_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_90_add_y", 0), GNodeArg(GNA_OUT, "S182_Output", 0),
                   GNodeArg(GNA_IN, "S182_Mul_scale", 0), GNodeArg(GNA_IN, "S182_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S182_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S185_CONV_2D_0_185_fusion inq -0.26<(u8-7.00)*0.03728715<9.25 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-12.00)*0.02315426<5.63 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S185_CONV_2D_0_185_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S175_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_83_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_91_add_y", 0), GNodeArg(GNA_OUT, "S185_Output", 0),
                   GNodeArg(GNA_IN, "S185_Mul_scale", 0), GNodeArg(GNA_IN, "S185_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S185_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S188_CONV_2D_0_188_fusion inq -0.29<(u8-10.00)*0.02899599<7.10 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.29<(u8-6.00)*0.04852516<12.08 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S188_CONV_2D_0_188_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S182_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_84_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_92_add_y", 0), GNodeArg(GNA_OUT, "S188_Output", 0),
                   GNodeArg(GNA_IN, "S188_Mul_scale", 0), GNodeArg(GNA_IN, "S188_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S188_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S191_CONV_2D_0_191_fusion inq -0.28<(u8-12.00)*0.02315426<5.63 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-8.00)*0.03490086<8.62 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S191_CONV_2D_0_191_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S185_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_85_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_93_add_y", 0), GNodeArg(GNA_OUT, "S191_Output", 0),
                   GNodeArg(GNA_IN, "S191_Mul_scale", 0), GNodeArg(GNA_IN, "S191_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S191_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S194_CONV_2D_0_194_fusion inq -0.29<(u8-9.00)*0.03224707<7.93 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-21.00)*0.01311130<3.07 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S194_CONV_2D_0_194_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S179_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_86_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_94_add_y", 0), GNodeArg(GNA_OUT, "S194_Output", 0),
                   GNodeArg(GNA_IN, "S194_Mul_scale", 0), GNodeArg(GNA_IN, "S194_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S194_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONV_2D_0_194_split inq -0.28<(u8-21.00)*0.01311130<3.07 outq -0.28<(u8-21.00)*0.01311130<3.07
  AddNode("S195_CONV_2D_0_194_split",
          Bindings(3, GNodeArg(GNA_IN, "S194_Output", 0), GNodeArg(GNA_OUT, "S195_Output_0", 0),
                   GNodeArg(GNA_OUT, "S195_Output_1", 0)));
  // Node CONV_2D_0_194_split_copy_qout0 inq -0.28<(u8-21.00)*0.01311130<3.07 outq -0.28<(u8-14.00)*0.01991241<4.80
  AddNode("S196_CONV_2D_0_194_split_copy_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S195_Output_1", 0), GNodeArg(GNA_OUT, "S196_Output", 0),
                   GNodeArg(GNA_IN, "S196_Infos", 0)));
  // Node S199_CONV_2D_0_200 inq -0.29<(u8-6.00)*0.04852516<12.08 weightsq chan<(u8-128.00)*chan<chan outq
  // -19.79<(u8-134.00)*0.14768411<17.87 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S199_CONV_2D_0_200",
          Bindings(7, GNodeArg(GNA_IN, "S188_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_88_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_96_add_y", 0), GNodeArg(GNA_OUT, "S199_Output", 0),
                   GNodeArg(GNA_IN, "S199_Mul_scale", 0), GNodeArg(GNA_IN, "S199_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S199_Infos", 0)));
  // Node S202_CONV_2D_0_201 inq -0.28<(u8-8.00)*0.03490086<8.62 weightsq chan<(u8-128.00)*chan<chan outq
  // -19.79<(u8-134.00)*0.14768411<17.87 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S202_CONV_2D_0_201",
          Bindings(7, GNodeArg(GNA_IN, "S191_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_89_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_97_add_y", 0), GNodeArg(GNA_OUT, "S202_Output", 0),
                   GNodeArg(GNA_IN, "S202_Mul_scale", 0), GNodeArg(GNA_IN, "S202_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S202_Infos", 0)));
  // Node CONCAT_0_202 inq -19.79<(u8-134.00)*0.14768411<17.87 outq -19.79<(u8-134.00)*0.14768411<17.87
  AddNode("S203_CONCAT_0_202", Bindings(3, GNodeArg(GNA_IN, "S199_Output", 0), GNodeArg(GNA_IN, "S202_Output", 0),
                                        GNodeArg(GNA_OUT, "S203_Output", 0)));
  // Node S207_CONV_2D_0_204_fusion inq -0.28<(u8-21.00)*0.01311130<3.07 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-19.00)*0.01488788<3.51 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S207_CONV_2D_0_204_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S195_Output_0", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_90_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_98_add_y", 0), GNodeArg(GNA_OUT, "S207_Output", 0),
                   GNodeArg(GNA_IN, "S207_Mul_scale", 0), GNodeArg(GNA_IN, "S207_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S207_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S210_CONV_2D_0_207_fusion inq -0.28<(u8-19.00)*0.01488788<3.51 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-14.00)*0.01991241<4.80 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S210_CONV_2D_0_207_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S207_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_91_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_99_add_y", 0), GNodeArg(GNA_OUT, "S210_Output", 0),
                   GNodeArg(GNA_IN, "S210_Mul_scale", 0), GNodeArg(GNA_IN, "S210_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S210_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node CONCAT_0_210 inq -0.28<(u8-14.00)*0.01991241<4.80 outq -0.28<(u8-14.00)*0.01991241<4.80
  AddNode("S211_CONCAT_0_210", Bindings(3, GNodeArg(GNA_IN, "S210_Output", 0), GNodeArg(GNA_IN, "S196_Output", 0),
                                        GNodeArg(GNA_OUT, "S211_Output", 0)));
  // Node S214_CONV_2D_0_211_fusion inq -0.28<(u8-14.00)*0.01991241<4.80 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-16.00)*0.01689279<4.04 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S214_CONV_2D_0_211_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S211_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_92_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_100_add_y", 0), GNodeArg(GNA_OUT, "S214_Output", 0),
                   GNodeArg(GNA_IN, "S214_Mul_scale", 0), GNodeArg(GNA_IN, "S214_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S214_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S217_CONV_2D_0_214_fusion inq -0.27<(u8-16.00)*0.01689279<4.04 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.01<(u8-111.00)*0.00004634<0.01 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S217_CONV_2D_0_214_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S214_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_93_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_101_add_y", 0), GNodeArg(GNA_OUT, "S217_Output", 0),
                   GNodeArg(GNA_IN, "S217_Mul_scale", 0), GNodeArg(GNA_IN, "S217_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S217_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S220_CONV_2D_0_217_fusion inq -0.27<(u8-16.00)*0.01689279<4.04 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.27<(u8-10.00)*0.02656894<6.51 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S220_CONV_2D_0_217_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S214_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_94_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_102_add_y", 0), GNodeArg(GNA_OUT, "S220_Output", 0),
                   GNodeArg(GNA_IN, "S220_Mul_scale", 0), GNodeArg(GNA_IN, "S220_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S220_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S223_CONV_2D_0_220_fusion inq -0.01<(u8-111.00)*0.00004634<0.01 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.00<(u8-132.00)*0.00000022<0.00 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S223_CONV_2D_0_220_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S217_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_95_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_103_add_y", 0), GNodeArg(GNA_OUT, "S223_Output", 0),
                   GNodeArg(GNA_IN, "S223_Mul_scale", 0), GNodeArg(GNA_IN, "S223_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S223_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S226_CONV_2D_0_223_fusion inq -0.27<(u8-10.00)*0.02656894<6.51 weightsq chan<(u8-128.00)*chan<chan outq
  // -0.28<(u8-32.00)*0.00875222<1.95 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S226_CONV_2D_0_223_fusion",
          Bindings(8, GNodeArg(GNA_IN, "S220_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_96_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_104_add_y", 0), GNodeArg(GNA_OUT, "S226_Output", 0),
                   GNodeArg(GNA_IN, "S226_Mul_scale", 0), GNodeArg(GNA_IN, "S226_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S226_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUTTable", 0)));
  // Node S229_CONV_2D_0_226 inq -0.00<(u8-132.00)*0.00000022<0.00 weightsq chan<(u8-128.00)*chan<chan outq
  // -19.79<(u8-134.00)*0.14768411<17.87 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S229_CONV_2D_0_226",
          Bindings(7, GNodeArg(GNA_IN, "S223_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_97_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_105_add_y", 0), GNodeArg(GNA_OUT, "S229_Output", 0),
                   GNodeArg(GNA_IN, "S229_Mul_scale", 0), GNodeArg(GNA_IN, "S229_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S229_Infos", 0)));
  // Node S232_CONV_2D_0_227 inq -0.28<(u8-32.00)*0.00875222<1.95 weightsq chan<(u8-128.00)*chan<chan outq
  // -19.79<(u8-134.00)*0.14768411<17.87 biasesq chan<(i32-0.00)*chan<chan
  AddNode("S232_CONV_2D_0_227",
          Bindings(7, GNodeArg(GNA_IN, "S226_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_98_", 0),
                   GNodeArg(GNA_IN, "Model_37_tf_math_add_106_add_y", 0), GNodeArg(GNA_OUT, "S232_Output", 0),
                   GNodeArg(GNA_IN, "S232_Mul_scale", 0), GNodeArg(GNA_IN, "S232_Mul_shift", 0),
                   GNodeArg(GNA_IN, "S232_Infos", 0)));
  // Node CONCAT_0_228 inq -19.79<(u8-134.00)*0.14768411<17.87 outq -19.79<(u8-134.00)*0.14768411<17.87
  AddNode("S233_CONCAT_0_228", Bindings(3, GNodeArg(GNA_IN, "S229_Output", 0), GNodeArg(GNA_IN, "S232_Output", 0),
                                        GNodeArg(GNA_OUT, "S233_Output", 0)));
  // Node STRIDED_SLICE_0_234_split inq -19.79<(u8-134.00)*0.14768411<17.87 outq -19.79<(u8-134.00)*0.14768411<17.87
  AddNode("S236_STRIDED_SLICE_0_234_split",
          Bindings(3, GNodeArg(GNA_IN, "S235_Output", 0), GNodeArg(GNA_OUT, "S236_Output_0", 0),
                   GNodeArg(GNA_OUT, "S236_Output_1", 0)));
  // Node TRANSPOSE_0_236_qout0 inq -19.79<(u8-134.00)*0.14768411<17.87 outq -32.00<(i8-0.00)*0.25000000<31.75 forced
  AddNode("S238_TRANSPOSE_0_236_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S236_Output_0", 0), GNodeArg(GNA_OUT, "S238_Output", 0),
                   GNodeArg(GNA_IN, "S238_Infos", 0)));
  // Node SOFTMAX_0_237 inq -32.00<(i8-0.00)*0.25000000<31.75 forced outq -1.00<(i16-0.00)*0.00003052<1.00
  AddNode("S239_SOFTMAX_0_237", Bindings(3, GNodeArg(GNA_IN, "S238_Output", 0), GNodeArg(GNA_OUT, "S239_Output", 0),
                                         GNodeArg(GNA_IN, "S239_Infos", 0)));
  // Node TRANSPOSE_0_238_qout0 inq -1.00<(i16-0.00)*0.00003052<1.00 outq 0.00<(u8-0.00)*0.00373763<0.95
  AddNode("S240_TRANSPOSE_0_238_qout0",
          Bindings(3, GNodeArg(GNA_IN, "S239_Output", 0), GNodeArg(GNA_OUT, "S240_Output", 0),
                   GNodeArg(GNA_IN, "S240_Infos", 0)));
  // Node CONV_2D_0_240_trans inq 0.00<(u8-0.00)*0.00373763<0.95 outq 0.00<(u8-0.00)*0.00373763<0.95
  AddNode("S241_CONV_2D_0_240_trans",
          Bindings(2, GNodeArg(GNA_IN, "S240_Output", 0), GNodeArg(GNA_OUT, "S241_Output", 0)));
  // Node STRIDED_SLICE_0_234_split_qout1 inq -19.79<(u8-134.00)*0.14768411<17.87 outq -6.29<(u8-128.00)*0.04913386<6.24
  // forced
  AddNode("S242_STRIDED_SLICE_0_234_split_qout1",
          Bindings(3, GNodeArg(GNA_IN, "S236_Output_1", 0), GNodeArg(GNA_OUT, "S242_Output", 0),
                   GNodeArg(GNA_IN, "S242_Infos", 0)));
  // Node LOGISTIC_0_243 inq -6.29<(u8-128.00)*0.04913386<6.24 forced outq -1.01<(u8-128.00)*0.00787402<1.00 forced
  AddNode("S243_LOGISTIC_0_243", Bindings(4, GNodeArg(GNA_IN, "S242_Output", 0), GNodeArg(GNA_OUT, "Output_2", 0),
                                          GNodeArg(GNA_IN, "S243_Infos", 0), GNodeArg(GNA_IN, "SigmoidLUT_u8", 0)));
  // Node S247_CONV_2D_0_240 inq 0.00<(u8-0.00)*0.00373763<0.95 weightsq -15.00<(u8-128.00)*0.11811024<15.00 outq
  // 0.00<(u8-0.00)*0.04921964<12.55 biasesq -948010.69<(i32-0.00)*0.00044145<948010.69
  AddNode("S247_CONV_2D_0_240", Bindings(7, GNodeArg(GNA_IN, "S241_Output", 0),
                                         GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_99__15e5e2e5_0", 0),
                                         GNodeArg(GNA_IN, "Model_37_tf_nn_convolution_99_", 0),
                                         GNodeArg(GNA_OUT, "S247_Output", 0), GNodeArg(GNA_IN, "S247_Mul_scale", 0),
                                         GNodeArg(GNA_IN, "S247_Mul_shift", 0), GNodeArg(GNA_IN, "S247_Infos", 0)));
  // Node expr_1 in_qs
  // [-31.75<(i8-0.00)*0.24803150<31.50,0.00<(u8-0.00)*0.04921964<12.55,0.00<(u8-0.00)*0.04921964<12.55,-31.75<(i8-0.00)*0.24803150<31.50]
  // out_qs [0.00<(i8--128.00)*0.12416799<31.66,0.00<(i8--128.00)*0.12416799<31.66]
  AddNode("S255_expr_1", Bindings(6, GNodeArg(GNA_IN, "Model_37_6790", 0), GNodeArg(GNA_IN, "S249_Output_0", 0),
                                  GNodeArg(GNA_IN, "S249_Output_1", 0), GNodeArg(GNA_IN, "Model_37_6790_1", 0),
                                  GNodeArg(GNA_OUT, "S255_Output_0", 0), GNodeArg(GNA_OUT, "S255_Output_1", 0)));
  // Node expr_64 in_qs [0.00<(i8--128.00)*0.12416799<31.66,-32.25<(i8-0.00)*0.25196850<32.00] out_qs
  // [-483.76<(i8-0.00)*3.77935791<479.98 forced]
  AddNode("S257_expr_64",
          Bindings(3, GNodeArg(GNA_IN, "S256_Output", 0), GNodeArg(GNA_IN, "Model_37_tf_math_multiply_201_", 0),
                   GNodeArg(GNA_OUT, "Output_1", 0)));
  CloseGraph();
#endif
}

int main(int argc, char **argv)

{
  if (TilerParseOptions(argc, argv)) {
    printf("Failed to initialize or incorrect output arguments directory.\n");
    return 1;
  }
  YOLOv5Model(120000, 300000, 8000000, 64 * 1024 * 1024);
  GenerateTilingCode();
  return 0;
}
