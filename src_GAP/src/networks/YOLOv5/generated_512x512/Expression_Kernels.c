#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wpointer-sign"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "Expression_Kernels.h"

static int CoreCountDynamic = 1;
static int ActiveCore = gap_ncore();

static inline unsigned int __attribute__((always_inline)) ChunkSize(unsigned int X)

{
	unsigned int NCore;
	unsigned int Log2Core;
	unsigned int Chunk;

	if (CoreCountDynamic) NCore = ActiveCore; else NCore = gap_ncore();
	Log2Core = gap_fl1(NCore);
	Chunk = (X>>Log2Core) + ((X&(NCore-1))!=0);
	return Chunk;
}

#ifndef AT_NORM
#define AT_NORM(x, n)   gap_roundnorm_reg((x), (n))
#endif
#define ATLShift(x, n)  ((x) << (n))

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s18_kernel(s18_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)   
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (128, 128, 8) (uint8-120) 7.691 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (128, 128, 8) (uint8-4) 18.863 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (128, 128, 8) (uint8-8) 19.140 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (128, 128, 8) var shapes:
    // expr_0_out_0: (128, 128, 8) expr_0_in_1: (128, 128, 8) expr_0_in_0:
    // (128, 128, 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-4) 18.863 Q8 expr_0_in_0: (uint8-120)
        // 7.691 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_0_in_0, int32), [246]), [1]), [14760]), SigmoidLUTTable)), [8]), [209]), [16])), [252]), [8]), [-4]), 0, 255), uint8)
        // ADD_0_16 scale arg 0 (no zp adj) - (uint8-4) 18.863 Q8 -> (int32-4) 18.863 Q8
        int _SYMBOL_Cast517 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-4) 37.726 Q9 -> (uint8-8) 19.140 Q8
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast517+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_0_in_0[i0])*(246)), ((unsigned char)1))-(14760)), SigmoidLUTTable)), (8))*(209)), ((unsigned char)16)))*(252)), ((unsigned char)8))-(-4))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s183_kernel(s183_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (1, 256, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (1, 256, 1, 2) int8 14.614 Q7
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (1, 1, 1, 2)   int8 0.002 Q7
    unsigned char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (1, 256, 3, 2) uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 256, 3, 2) var shapes:
    // expr_1_out_0: (1, 256, 3, 2) expr_1_in_0: (1, 256, 3, 2) expr_1_in_1:
    // (1, 256, 1, 2) expr_1_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_1_in_0: (uint8-128) 12.578 Q8 expr_1_in_1: int8
            // 14.614 Q7 expr_1_in_2: int8 0.002 Q7
            // expr_1_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_1_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_1_in_1, int32), [234]), [3])), [1]), [1]), Cast(expr_1_in_2, int32)), [129]), [23]), 0, 255), uint8)
            // scale clip and cast - int32 0.252 Q15 -> uint8 1.004 Q8
            expr_1_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_1_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_1_in_1[i2])*(234))<<((unsigned char)3)))*(1)), (1))*((int)expr_1_in_2[i2]))*(129)), ((unsigned char)23))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s211_kernel(s211_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256)  
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (1, 1024, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (1, 1024, 1, 2) int8 30.740 Q7
    signed char *__restrict__  expr_2_in_2 = Args->expr_2_in_2; // (1, 1, 1, 2)    int8 0.002 Q7
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (1, 1024, 3, 2) (uint8-128) 2.026 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 1024, 3, 2) var shapes:
    // expr_2_out_0: (1, 1024, 3, 2) expr_2_in_0: (1, 1024, 3, 2) expr_2_in_1:
    // (1, 1024, 1, 2) expr_2_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1,
    // 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_2_in_0: (uint8-128) 12.578 Q8 expr_2_in_1: int8
            // 30.740 Q7 expr_2_in_2: int8 0.002 Q7
            // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_2_in_1, int32), [246]), [4])), [1]), [1]), Cast(expr_2_in_2, int32)), [255]), [26]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.126 Q15 -> (uint8-128) 2.026 Q8
            expr_2_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_2_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_2_in_1[i2])*(246))<<((unsigned char)4)))*(1)), (1))*((int)expr_2_in_2[i2]))*(255)), ((unsigned char)26))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s217_kernel(s217_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256)  
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (1, 4096, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (1, 4096, 1, 2) int8 62.992 Q7
    signed char *__restrict__  expr_3_in_2 = Args->expr_3_in_2; // (1, 1, 1, 2)    int8 0.002 Q7
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (1, 4096, 3, 2) (uint8-128) 2.026 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 4096, 3, 2) var shapes:
    // expr_3_out_0: (1, 4096, 3, 2) expr_3_in_0: (1, 4096, 3, 2) expr_3_in_1:
    // (1, 4096, 1, 2) expr_3_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1,
    // 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_3_in_0: (uint8-128) 12.578 Q8 expr_3_in_1: int8
            // 62.992 Q7 expr_3_in_2: int8 0.002 Q7
            // expr_3_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_3_in_1, int32), [252]), [5])), [1]), [1]), Cast(expr_3_in_2, int32)), [255]), [27]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.063 Q15 -> (uint8-128) 2.026 Q8
            expr_3_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_3_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_3_in_1[i2])*(252))<<((unsigned char)5)))*(1)), (1))*((int)expr_3_in_2[i2]))*(255)), ((unsigned char)27))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (64, 64, 16) (uint8-143) 9.090 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (64, 64, 16) (uint8-11) 6.602 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (64, 64, 16) (uint8-21) 6.882 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 16) var shapes:
    // expr_4_out_0: (64, 64, 16) expr_4_in_1: (64, 64, 16) expr_4_in_0: (64,
    // 64, 16) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-11) 6.602 Q8 expr_4_in_0: (uint8-143)
        // 9.090 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_4_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_4_in_0, int32), [143]), SigmoidLUT(Sub(Mul(Cast(expr_4_in_0, int32), [145]), [20735]), SigmoidLUTTable)), [8]), [176]), [14])), [246]), [8]), [-10]), 0, 255), uint8)
        // ADD_0_37 scale arg 0 (no zp adj) - (uint8-11) 6.602 Q8 -> (int32-11) 6.602 Q8
        int _SYMBOL_Cast513 = ((int)expr_4_in_1[i0]);
        // scale clip and cast - (int32-11) 13.205 Q9 -> (uint8-21) 6.882 Q8
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast513+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(143))*SigmoidTableInline(((((int)expr_4_in_0[i0])*(145))-(20735)), SigmoidLUTTable)), (8))*(176)), ((unsigned char)14)))*(246)), ((unsigned char)8))-(-10))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s57_kernel(s57_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0; // (32, 32, 28) (uint8-131) 7.451 Q8
    unsigned char *__restrict__  expr_5_in_1 = Args->expr_5_in_1; // (32, 32, 28) (uint8-17) 4.128 Q8
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (32, 32, 28) (uint8-27) 2.687 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 28) var shapes:
    // expr_5_out_0: (32, 32, 28) expr_5_in_1: (32, 32, 28) expr_5_in_0: (32,
    // 32, 28) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_1: (uint8-17) 4.128 Q8 expr_5_in_0: (uint8-131)
        // 7.451 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_5_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_5_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_5_in_0, int32), [238]), [1]), [15589]), SigmoidLUTTable)), [8]), [231]), [14])), [197]), [8]), [-14]), 0, 255), uint8)
        // ADD_0_58 scale arg 0 (no zp adj) - (uint8-17) 4.128 Q8 -> (int32-17) 4.128 Q8
        int _SYMBOL_Cast314 = ((int)expr_5_in_1[i0]);
        // scale clip and cast - (int32-17) 8.256 Q9 -> (uint8-27) 2.687 Q7
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast314+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_5_in_0[i0])*(238)), ((unsigned char)1))-(15589)), SigmoidLUTTable)), (8))*(231)), ((unsigned char)14)))*(197)), ((unsigned char)8))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s77_kernel(s77_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0; // (16, 16, 52) (uint8-101) 8.382 Q8
    unsigned char *__restrict__  expr_6_in_1 = Args->expr_6_in_1; // (16, 16, 52) (uint8-19) 3.770 Q8
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (16, 16, 52) (uint8-26) 2.733 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 52) var shapes:
    // expr_6_out_0: (16, 16, 52) expr_6_in_1: (16, 16, 52) expr_6_in_0: (16,
    // 16, 52) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_1: (uint8-19) 3.770 Q8 expr_6_in_0: (uint8-101)
        // 8.382 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_6_in_1, int32), [230]), [2]), Norm(Mul(Sub(Cast(expr_6_in_0, int32), [101]), SigmoidLUT(Sub(Mul(Cast(expr_6_in_0, int32), [134]), [13534]), SigmoidLUTTable)), [8])), [196]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - (int32-1093) 1072.919 Q22 -> (uint8-26) 2.733 Q7
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_6_in_1[i0])*(230)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_6_in_0[i0])-(101))*SigmoidTableInline(((((int)expr_6_in_0[i0])*(134))-(13534)), SigmoidLUTTable)), (8)))*(196)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s206_kernel(s206_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0; // (1, 256, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_32_in_1 = Args->expr_32_in_1; // (1, 1, 3, 2)   int8 1503.748 Q7
    signed char *__restrict__  expr_32_in_2 = Args->expr_32_in_2; // (1, 1, 1, 2)   int8 0.002 Q7
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 256, 3, 2) uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 256, 3, 2) var shapes:
    // inter_LOGISTIC_0_190: (1, 256, 3, 2) expr_32_in_0: (1, 256, 3, 2)
    // expr_32_out_0: (1, 256, 3, 2) expr_32_in_1: (1, 1, 3, 2) expr_32_in_2:
    // (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_32_in_0: (uint8-128) 12.578 Q8
            // inter_LOGISTIC_0_190 = SigmoidLUT(Sub(Mul(Cast(expr_32_in_0, int32), [201]), [25728]), SigmoidLUTTable)
            int inter_LOGISTIC_0_190 = SigmoidTableInline(((((int)expr_32_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable);
            // inputs inter_LOGISTIC_0_190: int32 1.000 Q15 expr_32_in_1: int8
            // 1503.748 Q7 expr_32_in_2: int8 0.002 Q7
            // expr_32_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_190), Cast(expr_32_in_1, int32)), [7]), Cast(expr_32_in_2, int32)), [189]), [20]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_190 = inter_LOGISTIC_0_190;
            // scale clip and cast - int32 2.960 Q15 -> uint8 1.004 Q8
            expr_32_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_190)*((int)expr_32_in_1[(i1*I2)+i2])), (7))*((int)expr_32_in_2[i2]))*(189)), ((unsigned char)20))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s213_kernel(s213_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256)  
    unsigned char *__restrict__  expr_34_in_0 = Args->expr_34_in_0; // (1, 1024, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_34_in_1 = Args->expr_34_in_1; // (1, 1, 3, 2)    int8 479.748 Q7
    signed char *__restrict__  expr_34_in_2 = Args->expr_34_in_2; // (1, 1, 1, 2)    int8 0.002 Q7
    unsigned char *__restrict__  expr_34_out_0 = Args->expr_34_out_0; // (1, 1024, 3, 2) (uint8-128) 2.026 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 1024, 3, 2) var shapes:
    // inter_LOGISTIC_0_207: (1, 1024, 3, 2) expr_34_in_0: (1, 1024, 3, 2)
    // expr_34_out_0: (1, 1024, 3, 2) expr_34_in_1: (1, 1, 3, 2) expr_34_in_2:
    // (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_34_in_0: (uint8-128) 12.578 Q8
            // inter_LOGISTIC_0_207 = SigmoidLUT(Sub(Mul(Cast(expr_34_in_0, int32), [201]), [25728]), SigmoidLUTTable)
            int inter_LOGISTIC_0_207 = SigmoidTableInline(((((int)expr_34_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable);
            // inputs inter_LOGISTIC_0_207: int32 1.000 Q15 expr_34_in_1: int8
            // 479.748 Q7 expr_34_in_2: int8 0.002 Q7
            // expr_34_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_207), Cast(expr_34_in_1, int32)), [7]), Cast(expr_34_in_2, int32)), [239]), [23]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_207 = inter_LOGISTIC_0_207;
            // scale clip and cast - int32 0.944 Q15 -> (uint8-128) 2.026 Q8
            expr_34_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_207)*((int)expr_34_in_1[(i1*I2)+i2])), (7))*((int)expr_34_in_2[i2]))*(239)), ((unsigned char)23))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s219_kernel(s219_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256)  
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0; // (1, 4096, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_35_in_1 = Args->expr_35_in_1; // (1, 1, 3, 2)    int8 133.039 Q7
    signed char *__restrict__  expr_35_in_2 = Args->expr_35_in_2; // (1, 1, 1, 2)    int8 0.002 Q7
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 4096, 3, 2) (uint8-128) 2.026 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 4096, 3, 2) var shapes:
    // inter_LOGISTIC_0_224: (1, 4096, 3, 2) expr_35_in_0: (1, 4096, 3, 2)
    // expr_35_out_0: (1, 4096, 3, 2) expr_35_in_1: (1, 1, 3, 2) expr_35_in_2:
    // (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_35_in_0: (uint8-128) 12.578 Q8
            // inter_LOGISTIC_0_224 = SigmoidLUT(Sub(Mul(Cast(expr_35_in_0, int32), [201]), [25728]), SigmoidLUTTable)
            int inter_LOGISTIC_0_224 = SigmoidTableInline(((((int)expr_35_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable);
            // inputs inter_LOGISTIC_0_224: int32 1.000 Q15 expr_35_in_1: int8
            // 133.039 Q7 expr_35_in_2: int8 0.002 Q7
            // expr_35_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_224), Cast(expr_35_in_1, int32)), [7]), Cast(expr_35_in_2, int32)), [132]), [24]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_224 = inter_LOGISTIC_0_224;
            // scale clip and cast - int32 0.262 Q15 -> (uint8-128) 2.026 Q8
            expr_35_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_224)*((int)expr_35_in_1[(i1*I2)+i2])), (7))*((int)expr_35_in_2[i2]))*(132)), ((unsigned char)24))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_33(expr_33_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_33_in_0 = Args->expr_33_in_0;
    unsigned char *__restrict__  expr_33_out_0 = Args->expr_33_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (256, 256, 8) var shapes:
    // expr_33_out_0: (256, 256, 8) expr_33_in_0: (256, 256, 8)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-127) 28.115 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [127]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_33_in_0, int32), [225]), [1]), [57150]), SigmoidLUTTable)), [8]), [251]), [14]), [-5]), 0, 255), uint8)
        // scale clip and cast - int32 28.115 Q15 -> (uint8-5) 7.182 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(127))*SigmoidTableInline((((((int)expr_33_in_0[i0])*(225))<<((unsigned char)1))-(57150)), SigmoidLUTTable)), (8))*(251)), ((unsigned char)14))-(-5))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_45(expr_45_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_45_in_0 = Args->expr_45_in_0;
    unsigned char *__restrict__  expr_45_out_0 = Args->expr_45_out_0; // (1, 1, 256)    
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (128, 128, 16) var shapes:
    // expr_45_out_0: (128, 128, 16) expr_45_in_0: (128, 128, 16)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-154) 24.250 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [154]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [194]), [1]), [59752]), SigmoidLUTTable)), [8]), [157]), [13]), [-7]), 0, 255), uint8)
        // scale clip and cast - int32 24.250 Q15 -> (uint8-7) 4.950 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(154))*SigmoidTableInline((((((int)expr_45_in_0[i0])*(194))<<((unsigned char)1))-(59752)), SigmoidLUTTable)), (8))*(157)), ((unsigned char)13))-(-7))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_31(expr_31_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_31_in_0 = Args->expr_31_in_0;
    unsigned char *__restrict__  expr_31_out_0 = Args->expr_31_out_0; // (1, 1, 256)    
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (128, 128, 16) var shapes:
    // expr_31_out_0: (128, 128, 16) expr_31_in_0: (128, 128, 16)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-100) 30.546 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [100]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [244]), [1]), [48800]), -65536, 65535), SigmoidLUTTable)), [8]), [207]), [14]), [-4]), 0, 255), uint8)
        // scale clip and cast - int32 30.546 Q15 -> (uint8-4) 9.431 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(100))*SigmoidTableInline(gap_clip(((((((int)expr_31_in_0[i0])*(244))<<((unsigned char)1))-(48800))), (((signed char)16))), SigmoidLUTTable)), (8))*(207)), ((unsigned char)14))-(-4))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_13(expr_13_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_13_in_0 = Args->expr_13_in_0;
    unsigned char *__restrict__  expr_13_out_0 = Args->expr_13_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (128, 128, 8) var shapes:
    // expr_13_out_0: (128, 128, 8) expr_13_in_0: (128, 128, 8)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-158) 15.216 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [158]), SigmoidLUT(Sub(Mul(Cast(expr_13_in_0, int32), [243]), [38394]), SigmoidLUTTable)), [8]), [161]), [13]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 15.216 Q15 -> (uint8-12) 3.023 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(158))*SigmoidTableInline(((((int)expr_13_in_0[i0])*(243))-(38394)), SigmoidLUTTable)), (8))*(161)), ((unsigned char)13))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_36(expr_36_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_36_in_0 = Args->expr_36_in_0;
    unsigned char *__restrict__  expr_36_out_0 = Args->expr_36_out_0; // (1, 1, 256)    
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (128, 128, 16) var shapes:
    // expr_36_out_0: (128, 128, 16) expr_36_in_0: (128, 128, 16)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-186) 24.879 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [186]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_36_in_0, int32), [199]), [1]), [74028]), -65536, 65535), SigmoidLUTTable)), [8]), [229]), [13]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 24.879 Q15 -> (uint8-10) 3.477 Q7
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(186))*SigmoidTableInline(gap_clip(((((((int)expr_36_in_0[i0])*(199))<<((unsigned char)1))-(74028))), (((signed char)16))), SigmoidLUTTable)), (8))*(229)), ((unsigned char)13))-(-10))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_37(expr_37_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_37_in_0 = Args->expr_37_in_0;
    unsigned char *__restrict__  expr_37_out_0 = Args->expr_37_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 32) var shapes:
    // expr_37_out_0: (64, 64, 32) expr_37_in_0: (64, 64, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-129) 10.471 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [129]), SigmoidLUT(Sub(Mul(Cast(expr_37_in_0, int32), [168]), [21672]), SigmoidLUTTable)), [8]), [247]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 10.471 Q15 -> (uint8-13) 2.710 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(129))*SigmoidTableInline(((((int)expr_37_in_0[i0])*(168))-(21672)), SigmoidLUTTable)), (8))*(247)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_38(expr_38_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_38_in_0 = Args->expr_38_in_0;
    unsigned char *__restrict__  expr_38_out_0 = Args->expr_38_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 32) var shapes:
    // expr_38_out_0: (64, 64, 32) expr_38_in_0: (64, 64, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-129) 12.849 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [129]), SigmoidLUT(Sub(Mul(Cast(expr_38_in_0, int32), [206]), [26574]), SigmoidLUTTable)), [8]), [249]), [14]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 12.849 Q15 -> (uint8-11) 3.301 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(129))*SigmoidTableInline(((((int)expr_38_in_0[i0])*(206))-(26574)), SigmoidLUTTable)), (8))*(249)), ((unsigned char)14))-(-11))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_39(expr_39_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_39_in_0 = Args->expr_39_in_0;
    unsigned char *__restrict__  expr_39_out_0 = Args->expr_39_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 16) var shapes:
    // expr_39_out_0: (64, 64, 16) expr_39_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-148) 8.519 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [148]), SigmoidLUT(Sub(Mul(Cast(expr_39_in_0, int32), [136]), [20128]), SigmoidLUTTable)), [8]), [145]), [13]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 8.519 Q15 -> (uint8-19) 1.875 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(148))*SigmoidTableInline(((((int)expr_39_in_0[i0])*(136))-(20128)), SigmoidLUTTable)), (8))*(145)), ((unsigned char)13))-(-19))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_41(expr_41_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_41_in_0 = Args->expr_41_in_0;
    unsigned char *__restrict__  expr_41_out_0 = Args->expr_41_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 32) var shapes:
    // expr_41_out_0: (64, 64, 32) expr_41_in_0: (64, 64, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-152) 8.904 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [152]), SigmoidLUT(Sub(Mul(Cast(expr_41_in_0, int32), [142]), [21584]), SigmoidLUTTable)), [8]), [151]), [13]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 8.904 Q15 -> (uint8-19) 1.883 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(152))*SigmoidTableInline(((((int)expr_41_in_0[i0])*(142))-(21584)), SigmoidLUTTable)), (8))*(151)), ((unsigned char)13))-(-19))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_42(expr_42_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_42_in_0 = Args->expr_42_in_0;
    unsigned char *__restrict__  expr_42_out_0 = Args->expr_42_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 56) var shapes:
    // expr_42_out_0: (32, 32, 56) expr_42_in_0: (32, 32, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-124) 8.106 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [124]), SigmoidLUT(Sub(Mul(Cast(expr_42_in_0, int32), [130]), [16120]), SigmoidLUTTable)), [8]), [238]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.106 Q15 -> (uint8-16) 2.182 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(124))*SigmoidTableInline(((((int)expr_42_in_0[i0])*(130))-(16120)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-16))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_43(expr_43_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_43_in_0 = Args->expr_43_in_0;
    unsigned char *__restrict__  expr_43_out_0 = Args->expr_43_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 56) var shapes:
    // expr_43_out_0: (32, 32, 56) expr_43_in_0: (32, 32, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-112) 7.003 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [112]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_43_in_0, int32), [224]), [1]), [12544]), SigmoidLUTTable)), [8]), [217]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.003 Q15 -> (uint8-17) 2.064 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(112))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_43_in_0[i0])*(224)), ((unsigned char)1))-(12544)), SigmoidLUTTable)), (8))*(217)), ((unsigned char)14))-(-17))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_44(expr_44_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_44_in_0 = Args->expr_44_in_0;
    unsigned char *__restrict__  expr_44_out_0 = Args->expr_44_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 28) var shapes:
    // expr_44_out_0: (32, 32, 28) expr_44_in_0: (32, 32, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-119) 7.303 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [119]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_44_in_0, int32), [234]), [1]), [13923]), SigmoidLUTTable)), [8]), [227]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.303 Q15 -> (uint8-17) 2.055 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(119))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_44_in_0[i0])*(234)), ((unsigned char)1))-(13923)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-17))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_47(expr_47_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_47_in_0 = Args->expr_47_in_0;
    unsigned char *__restrict__  expr_47_out_0 = Args->expr_47_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 56) var shapes:
    // expr_47_out_0: (32, 32, 56) expr_47_in_0: (32, 32, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_47_in_0: (uint8-128) 7.397 Q8
        // expr_47_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_47_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_47_in_0, int32), [237]), [1]), [15168]), SigmoidLUTTable)), [8]), [245]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.397 Q15 -> (uint8-18) 1.935 Q7
        expr_47_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_47_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_47_in_0[i0])*(237)), ((unsigned char)1))-(15168)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_48(expr_48_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_48_in_0 = Args->expr_48_in_0;
    unsigned char *__restrict__  expr_48_out_0 = Args->expr_48_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 104) var shapes:
    // expr_48_out_0: (16, 16, 104) expr_48_in_0: (16, 16, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-113) 8.006 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [113]), SigmoidLUT(Sub(Mul(Cast(expr_48_in_0, int32), [128]), [14464]), SigmoidLUTTable)), [8]), [218]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 8.006 Q15 -> (uint8-15) 2.345 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(113))*SigmoidTableInline(((((int)expr_48_in_0[i0])*(128))-(14464)), SigmoidLUTTable)), (8))*(218)), ((unsigned char)14))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_49(expr_49_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_49_in_0 = Args->expr_49_in_0;
    unsigned char *__restrict__  expr_49_out_0 = Args->expr_49_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 104) var shapes:
    // expr_49_out_0: (16, 16, 104) expr_49_in_0: (16, 16, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-120) 6.795 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_49_in_0, int32), [217]), [1]), [13020]), SigmoidLUTTable)), [8]), [231]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 6.795 Q15 -> (uint8-19) 1.885 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_49_in_0[i0])*(217)), ((unsigned char)1))-(13020)), SigmoidLUTTable)), (8))*(231)), ((unsigned char)14))-(-19))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_50(expr_50_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_50_in_0 = Args->expr_50_in_0;
    unsigned char *__restrict__  expr_50_out_0 = Args->expr_50_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 52) var shapes:
    // expr_50_out_0: (16, 16, 52) expr_50_in_0: (16, 16, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-112) 6.726 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [112]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_50_in_0, int32), [215]), [1]), [12040]), SigmoidLUTTable)), [8]), [217]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 6.726 Q15 -> (uint8-18) 1.988 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(112))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_50_in_0[i0])*(215)), ((unsigned char)1))-(12040)), SigmoidLUTTable)), (8))*(217)), ((unsigned char)14))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_52(expr_52_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_52_in_0 = Args->expr_52_in_0;
    unsigned char *__restrict__  expr_52_out_0 = Args->expr_52_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 104) var shapes:
    // expr_52_out_0: (16, 16, 104) expr_52_in_0: (16, 16, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_52_in_0: (uint8-120) 7.498 Q8
        // expr_52_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_52_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_52_in_0, int32), [240]), [1]), [14400]), SigmoidLUTTable)), [8]), [230]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.498 Q15 -> (uint8-17) 2.089 Q7
        expr_52_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_52_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_52_in_0[i0])*(240)), ((unsigned char)1))-(14400)), SigmoidLUTTable)), (8))*(230)), ((unsigned char)14))-(-17))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_53(expr_53_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_53_in_0 = Args->expr_53_in_0;
    unsigned char *__restrict__  expr_53_out_0 = Args->expr_53_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 52) var shapes:
    // expr_53_out_0: (16, 16, 52) expr_53_in_0: (16, 16, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-129) 7.742 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [129]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_53_in_0, int32), [248]), [1]), [15996]), SigmoidLUTTable)), [8]), [246]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.742 Q15 -> (uint8-18) 2.014 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(129))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_53_in_0[i0])*(248)), ((unsigned char)1))-(15996)), SigmoidLUTTable)), (8))*(246)), ((unsigned char)14))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_55(expr_55_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_55_in_0 = Args->expr_55_in_0;
    unsigned char *__restrict__  expr_55_out_0 = Args->expr_55_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 104) var shapes:
    // expr_55_out_0: (16, 16, 104) expr_55_in_0: (16, 16, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-117) 7.062 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [117]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_55_in_0, int32), [226]), [1]), [13221]), SigmoidLUTTable)), [8]), [225]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.062 Q15 -> (uint8-18) 2.013 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_55_in_0[i0])-(117))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_55_in_0[i0])*(226)), ((unsigned char)1))-(13221)), SigmoidLUTTable)), (8))*(225)), ((unsigned char)14))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_56(expr_56_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_56_in_0 = Args->expr_56_in_0;
    unsigned char *__restrict__  expr_56_out_0 = Args->expr_56_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_56_out_0: (16, 16, 56) expr_56_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-120) 7.411 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_56_in_0, int32), [237]), [1]), [14220]), SigmoidLUTTable)), [8]), [229]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.411 Q15 -> (uint8-17) 2.069 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_56_in_0[i0])*(237)), ((unsigned char)1))-(14220)), SigmoidLUTTable)), (8))*(229)), ((unsigned char)14))-(-17))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_10(expr_10_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_10_in_0 = Args->expr_10_in_0;
    unsigned char *__restrict__  expr_10_out_0 = Args->expr_10_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 56) var shapes:
    // expr_10_out_0: (32, 32, 56) expr_10_in_0: (32, 32, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-139) 6.363 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [139]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_10_in_0, int32), [204]), [1]), [14178]), SigmoidLUTTable)), [8]), [135]), [13]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 6.363 Q15 -> (uint8-24) 1.506 Q7
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_10_in_0[i0])-(139))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_10_in_0[i0])*(204)), ((unsigned char)1))-(14178)), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-24))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_8(expr_8_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_8_in_0 = Args->expr_8_in_0;
    unsigned char *__restrict__  expr_8_out_0 = Args->expr_8_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 28) var shapes:
    // expr_8_out_0: (32, 32, 28) expr_8_in_0: (32, 32, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_8_in_0: (uint8-105) 6.270 Q8
        // expr_8_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_8_in_0, int32), [105]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_8_in_0, int32), [201]), [1]), [10553]), SigmoidLUTTable)), [8]), [207]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 6.270 Q15 -> (uint8-18) 1.940 Q7
        expr_8_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_8_in_0[i0])-(105))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_8_in_0[i0])*(201)), ((unsigned char)1))-(10553)), SigmoidLUTTable)), (8))*(207)), ((unsigned char)14))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_9(expr_9_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_9_in_0 = Args->expr_9_in_0;
    unsigned char *__restrict__  expr_9_out_0 = Args->expr_9_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 28) var shapes:
    // expr_9_out_0: (32, 32, 28) expr_9_in_0: (32, 32, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-124) 6.675 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [124]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_9_in_0, int32), [214]), [1]), [13268]), SigmoidLUTTable)), [8]), [238]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.675 Q15 -> (uint8-20) 3.597 Q8
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(124))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_9_in_0[i0])*(214)), ((unsigned char)1))-(13268)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-20))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_11(expr_11_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_11_in_0 = Args->expr_11_in_0;
    unsigned char *__restrict__  expr_11_out_0 = Args->expr_11_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 56) var shapes:
    // expr_11_out_0: (32, 32, 56) expr_11_in_0: (32, 32, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-133) 6.478 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [133]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_11_in_0, int32), [207]), [1]), [13766]), SigmoidLUTTable)), [8]), [255]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 6.478 Q15 -> (uint8-22) 1.628 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(133))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_11_in_0[i0])*(207)), ((unsigned char)1))-(13766)), SigmoidLUTTable)), (8))*(255)), ((unsigned char)14))-(-22))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_12(expr_12_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_12_in_0 = Args->expr_12_in_0;
    unsigned char *__restrict__  expr_12_out_0 = Args->expr_12_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_12_out_0: (32, 32, 32) expr_12_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-116) 5.561 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_12_in_0, int32), [178]), [1]), [10324]), SigmoidLUTTable)), [8]), [225]), [14]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 5.561 Q15 -> (uint8-23) 1.582 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_12_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_12_in_0[i0])*(178)), ((unsigned char)1))-(10324)), SigmoidLUTTable)), (8))*(225)), ((unsigned char)14))-(-23))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_14(expr_14_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_14_in_0 = Args->expr_14_in_0;
    unsigned char *__restrict__  expr_14_out_0 = Args->expr_14_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 32) var shapes:
    // expr_14_out_0: (64, 64, 32) expr_14_in_0: (64, 64, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-138) 5.105 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [138]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_14_in_0, int32), [163]), [1]), [11247]), SigmoidLUTTable)), [8]), [135]), [13]), [-30]), 0, 255), uint8)
        // scale clip and cast - int32 5.105 Q15 -> (uint8-30) 1.206 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_14_in_0[i0])-(138))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_14_in_0[i0])*(163)), ((unsigned char)1))-(11247)), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-30))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_15(expr_15_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_15_in_0 = Args->expr_15_in_0;
    unsigned char *__restrict__  expr_15_out_0 = Args->expr_15_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 16) var shapes:
    // expr_15_out_0: (64, 64, 16) expr_15_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_15_in_0: (uint8-125) 5.754 Q8
        // expr_15_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_15_in_0, int32), [125]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_15_in_0, int32), [184]), [1]), [11500]), SigmoidLUTTable)), [8]), [241]), [14]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 5.754 Q15 -> (uint8-23) 1.529 Q7
        expr_15_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_15_in_0[i0])-(125))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_15_in_0[i0])*(184)), ((unsigned char)1))-(11500)), SigmoidLUTTable)), (8))*(241)), ((unsigned char)14))-(-23))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_16(expr_16_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_16_in_0 = Args->expr_16_in_0;
    unsigned char *__restrict__  expr_16_out_0 = Args->expr_16_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 16) var shapes:
    // expr_16_out_0: (64, 64, 16) expr_16_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-150) 5.413 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [150]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_16_in_0, int32), [173]), [1]), [12975]), SigmoidLUTTable)), [8]), [144]), [13]), [-30]), 0, 255), uint8)
        // scale clip and cast - int32 5.413 Q15 -> (uint8-30) 2.412 Q8
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_16_in_0[i0])-(150))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_16_in_0[i0])*(173)), ((unsigned char)1))-(12975)), SigmoidLUTTable)), (8))*(144)), ((unsigned char)13))-(-30))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_18(expr_18_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_18_in_0 = Args->expr_18_in_0;
    unsigned char *__restrict__  expr_18_out_0 = Args->expr_18_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 32) var shapes:
    // expr_18_out_0: (64, 64, 32) expr_18_in_0: (64, 64, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-137) 8.280 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [137]), SigmoidLUT(Sub(Mul(Cast(expr_18_in_0, int32), [132]), [18084]), SigmoidLUTTable)), [8]), [132]), [13]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 8.280 Q15 -> (uint8-18) 2.008 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(137))*SigmoidTableInline(((((int)expr_18_in_0[i0])*(132))-(18084)), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_19(expr_19_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_19_in_0 = Args->expr_19_in_0;
    unsigned char *__restrict__  expr_19_out_0 = Args->expr_19_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 32) var shapes:
    // expr_19_out_0: (32, 32, 32) expr_19_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-123) 5.560 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_19_in_0, int32), [178]), [1]), [10947]), SigmoidLUTTable)), [8]), [225]), [14]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 5.560 Q15 -> (uint8-23) 3.163 Q8
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_19_in_0[i0])*(178)), ((unsigned char)1))-(10947)), SigmoidLUTTable)), (8))*(225)), ((unsigned char)14))-(-23))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_20(expr_20_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_20_in_0 = Args->expr_20_in_0;
    unsigned char *__restrict__  expr_20_out_0 = Args->expr_20_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 56) var shapes:
    // expr_20_out_0: (32, 32, 56) expr_20_in_0: (32, 32, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-115) 6.301 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_20_in_0, int32), [115]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_20_in_0, int32), [202]), [1]), [11615]), SigmoidLUTTable)), [8]), [222]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.301 Q15 -> (uint8-20) 1.819 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_20_in_0[i0])-(115))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_20_in_0[i0])*(202)), ((unsigned char)1))-(11615)), SigmoidLUTTable)), (8))*(222)), ((unsigned char)14))-(-20))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_21(expr_21_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_21_in_0 = Args->expr_21_in_0;
    unsigned char *__restrict__  expr_21_out_0 = Args->expr_21_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 28) var shapes:
    // expr_21_out_0: (32, 32, 28) expr_21_in_0: (32, 32, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-118) 7.177 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [118]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_21_in_0, int32), [230]), [1]), [13570]), SigmoidLUTTable)), [8]), [227]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.177 Q15 -> (uint8-18) 2.026 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(118))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_21_in_0[i0])*(230)), ((unsigned char)1))-(13570)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_22(expr_22_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_22_in_0 = Args->expr_22_in_0;
    unsigned char *__restrict__  expr_22_out_0 = Args->expr_22_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 28) var shapes:
    // expr_22_out_0: (32, 32, 28) expr_22_in_0: (32, 32, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-123) 6.099 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_22_in_0, int32), [195]), [1]), [11993]), SigmoidLUTTable)), [8]), [215]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.099 Q15 -> (uint8-20) 3.639 Q8
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_22_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_22_in_0[i0])*(195)), ((unsigned char)1))-(11993)), SigmoidLUTTable)), (8))*(215)), ((unsigned char)14))-(-20))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_24(expr_24_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_24_in_0 = Args->expr_24_in_0;
    unsigned char *__restrict__  expr_24_out_0 = Args->expr_24_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 56) var shapes:
    // expr_24_out_0: (32, 32, 56) expr_24_in_0: (32, 32, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_24_in_0: (uint8-119) 8.380 Q8
        // expr_24_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_24_in_0, int32), [119]), SigmoidLUT(Sub(Mul(Cast(expr_24_in_0, int32), [134]), [15946]), SigmoidLUTTable)), [8]), [228]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 8.380 Q15 -> (uint8-15) 2.350 Q7
        expr_24_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_24_in_0[i0])-(119))*SigmoidTableInline(((((int)expr_24_in_0[i0])*(134))-(15946)), SigmoidLUTTable)), (8))*(228)), ((unsigned char)14))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_25(expr_25_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_25_in_0 = Args->expr_25_in_0;
    unsigned char *__restrict__  expr_25_out_0 = Args->expr_25_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 56) var shapes:
    // expr_25_out_0: (16, 16, 56) expr_25_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-82) 7.537 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [82]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_25_in_0, int32), [241]), [1]), [9881]), SigmoidLUTTable)), [8]), [180]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 7.537 Q15 -> (uint8-13) 5.366 Q8
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(82))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_25_in_0[i0])*(241)), ((unsigned char)1))-(9881)), SigmoidLUTTable)), (8))*(180)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_26(expr_26_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_26_in_0 = Args->expr_26_in_0;
    unsigned char *__restrict__  expr_26_out_0 = Args->expr_26_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 104) var shapes:
    // expr_26_out_0: (16, 16, 104) expr_26_in_0: (16, 16, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-119) 7.897 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [119]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_26_in_0, int32), [253]), [1]), [15054]), SigmoidLUTTable)), [8]), [229]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 7.897 Q15 -> (uint8-16) 2.208 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(119))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_26_in_0[i0])*(253)), ((unsigned char)1))-(15054)), SigmoidLUTTable)), (8))*(229)), ((unsigned char)14))-(-16))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_27(expr_27_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_27_in_0 = Args->expr_27_in_0;
    unsigned char *__restrict__  expr_27_out_0 = Args->expr_27_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 52) var shapes:
    // expr_27_out_0: (16, 16, 52) expr_27_in_0: (16, 16, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-131) 7.377 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_27_in_0, int32), [236]), [1]), [15458]), SigmoidLUTTable)), [8]), [250]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 7.377 Q15 -> (uint8-19) 1.888 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_27_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_27_in_0[i0])*(236)), ((unsigned char)1))-(15458)), SigmoidLUTTable)), (8))*(250)), ((unsigned char)14))-(-19))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_28(expr_28_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_28_in_0 = Args->expr_28_in_0;
    unsigned char *__restrict__  expr_28_out_0 = Args->expr_28_out_0; // (1, 1, 256)  
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 52) var shapes:
    // expr_28_out_0: (16, 16, 52) expr_28_in_0: (16, 16, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-114) 7.474 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [114]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_28_in_0, int32), [239]), [1]), [13623]), SigmoidLUTTable)), [8]), [217]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 7.474 Q15 -> (uint8-16) 4.417 Q8
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(114))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_28_in_0[i0])*(239)), ((unsigned char)1))-(13623)), SigmoidLUTTable)), (8))*(217)), ((unsigned char)14))-(-16))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_30(expr_30_args_t * __restrict__ Args) {
    unsigned char *__restrict__  expr_30_in_0 = Args->expr_30_in_0;
    unsigned char *__restrict__  expr_30_out_0 = Args->expr_30_out_0; // (1, 1, 256)   
    unsigned short * __restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
    unsigned int CoreId = gap_coreid();
    unsigned int I0 = Args->W*Args->H*Args->Feat;
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 104) var shapes:
    // expr_30_out_0: (16, 16, 104) expr_30_in_0: (16, 16, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-113) 7.044 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [113]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_30_in_0, int32), [225]), [1]), [12713]), SigmoidLUTTable)), [8]), [219]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.044 Q15 -> (uint8-17) 2.059 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_30_in_0[i0])-(113))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_30_in_0[i0])*(225)), ((unsigned char)1))-(12713)), SigmoidLUTTable)), (8))*(219)), ((unsigned char)14))-(-17))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop