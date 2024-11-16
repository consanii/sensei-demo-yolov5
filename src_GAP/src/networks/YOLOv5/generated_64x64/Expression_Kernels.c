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
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (16, 16, 8) (uint8-118) 9.666 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (16, 16, 8) (uint8-10) 7.070 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (16, 16, 8) (uint8-20) 7.359 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 8) var shapes:
    // expr_0_out_0: (16, 16, 8) expr_0_in_1: (16, 16, 8) expr_0_in_0: (16, 16,
    // 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-10) 7.070 Q8 expr_0_in_0: (uint8-118)
        // 9.666 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [118]), SigmoidLUT(Sub(Mul(Cast(expr_0_in_0, int32), [155]), [18290]), SigmoidLUTTable)), [8]), [175]), [14])), [246]), [8]), [-10]), 0, 255), uint8)
        // ADD_0_16 scale arg 0 (no zp adj) - (uint8-10) 7.070 Q8 -> (int32-10) 7.070 Q8
        int _SYMBOL_Cast240 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-10) 14.139 Q9 -> (uint8-20) 7.359 Q8
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast240+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(118))*SigmoidTableInline(((((int)expr_0_in_0[i0])*(155))-(18290)), SigmoidLUTTable)), (8))*(175)), ((unsigned char)14)))*(246)), ((unsigned char)8))-(-10))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s188_kernel(s188_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (1, 4, 3, 2)   (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (1, 4, 1, 2)   int8 0.504 Q7
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (1, 1, 1, 2)   int8 0.016 Q7
    unsigned char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (1, 4, 3, 2)   (uint8-128) 3.011 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 4, 3, 2) var shapes:
    // expr_1_out_0: (1, 4, 3, 2) expr_1_in_0: (1, 4, 3, 2) expr_1_in_1: (1, 4,
    // 1, 2) expr_1_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_1_in_0: (uint8-128) 12.578 Q8 expr_1_in_1: int8
            // 0.504 Q7 expr_1_in_2: int8 0.016 Q7
            // expr_1_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_1_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), Norm(Mul(Cast(expr_1_in_1, int32), [129]), [1])), [1]), [1]), Cast(expr_1_in_2, int32)), [171]), [22]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 2.016 Q15 -> (uint8-128) 3.011 Q8
            expr_1_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_1_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+gap_roundnorm_reg((((int)expr_1_in_1[i2])*(129)), ((unsigned char)1)))*(1)), (1))*((int)expr_1_in_2[i2]))*(171)), ((unsigned char)22))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (1, 16, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (1, 16, 1, 2)  int8 2.520 Q7
    signed char *__restrict__  expr_2_in_2 = Args->expr_2_in_2; // (1, 1, 1, 2)   int8 0.016 Q7
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (1, 16, 3, 2)  uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 16, 3, 2) var shapes:
    // expr_2_out_0: (1, 16, 3, 2) expr_2_in_0: (1, 16, 3, 2) expr_2_in_1: (1,
    // 16, 1, 2) expr_2_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_2_in_0: (uint8-128) 12.578 Q8 expr_2_in_1: int8
            // 2.520 Q7 expr_2_in_2: int8 0.016 Q7
            // expr_2_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_2_in_1, int32), [161]), [1])), [1]), [1]), Cast(expr_2_in_2, int32)), [129]), [21]), 0, 255), uint8)
            // scale clip and cast - int32 1.008 Q15 -> uint8 1.004 Q8
            expr_2_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_2_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_2_in_1[i2])*(161))<<((unsigned char)1)))*(1)), (1))*((int)expr_2_in_2[i2]))*(129)), ((unsigned char)21))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s220_kernel(s220_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (1, 64, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (1, 64, 1, 2)  int8 6.551 Q7
    signed char *__restrict__  expr_3_in_2 = Args->expr_3_in_2; // (1, 1, 1, 2)   int8 0.016 Q7
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (1, 64, 3, 2)  uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 64, 3, 2) var shapes:
    // expr_3_out_0: (1, 64, 3, 2) expr_3_in_0: (1, 64, 3, 2) expr_3_in_1: (1,
    // 64, 1, 2) expr_3_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_3_in_0: (uint8-128) 12.578 Q8 expr_3_in_1: int8
            // 6.551 Q7 expr_3_in_2: int8 0.016 Q7
            // expr_3_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_3_in_1, int32), [210]), [2])), [1]), [1]), Cast(expr_3_in_2, int32)), [129]), [22]), 0, 255), uint8)
            // scale clip and cast - int32 0.504 Q15 -> uint8 1.004 Q8
            expr_3_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_3_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_3_in_1[i2])*(210))<<((unsigned char)2)))*(1)), (1))*((int)expr_3_in_2[i2]))*(129)), ((unsigned char)22))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (8, 8, 16)  (uint8-123) 4.778 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (8, 8, 16)  (uint8-24) 2.913 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (8, 8, 16)  (uint8-39) 1.807 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 16) var shapes:
    // expr_4_out_0: (8, 8, 16) expr_4_in_1: (8, 8, 16) expr_4_in_0: (8, 8, 16)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-24) 2.913 Q8 expr_4_in_0: (uint8-123)
        // 4.778 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_4_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_4_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_4_in_0, int32), [153]), [1]), [9410]), SigmoidLUTTable)), [8]), [210]), [14])), [206]), [8]), [-20]), 0, 255), uint8)
        // ADD_0_37 scale arg 0 (no zp adj) - (uint8-24) 2.913 Q8 -> (int32-24) 2.913 Q8
        int _SYMBOL_Cast28 = ((int)expr_4_in_1[i0]);
        // scale clip and cast - (int32-24) 5.827 Q9 -> (uint8-39) 1.807 Q7
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast28+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_4_in_0[i0])*(153)), ((unsigned char)1))-(9410)), SigmoidLUTTable)), (8))*(210)), ((unsigned char)14)))*(206)), ((unsigned char)8))-(-20))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s57_kernel(s57_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0; // (4, 4, 28)  (uint8-100) 4.458 Q8
    unsigned char *__restrict__  expr_5_in_1 = Args->expr_5_in_1; // (4, 4, 28)  (uint8-25) 2.843 Q8
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (4, 4, 28)  (uint8-36) 2.006 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (4, 4, 28) var shapes:
    // expr_5_out_0: (4, 4, 28) expr_5_in_1: (4, 4, 28) expr_5_in_0: (4, 4, 28)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_1: (uint8-25) 2.843 Q8 expr_5_in_0: (uint8-100)
        // 4.458 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_5_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_5_in_0, int32), [100]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_5_in_0, int32), [143]), [1]), [7150]), SigmoidLUTTable)), [8]), [201]), [14])), [181]), [8]), [-18]), 0, 255), uint8)
        // ADD_0_58 scale arg 0 (no zp adj) - (uint8-25) 2.843 Q8 -> (int32-25) 2.843 Q8
        int _SYMBOL_Cast44 = ((int)expr_5_in_1[i0]);
        // scale clip and cast - (int32-25) 5.685 Q9 -> (uint8-36) 2.006 Q7
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast44+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(100))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_5_in_0[i0])*(143)), ((unsigned char)1))-(7150)), SigmoidLUTTable)), (8))*(201)), ((unsigned char)14)))*(181)), ((unsigned char)8))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s76_kernel(s76_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0; // (2, 2, 52)  (uint8-127) 4.096 Q8
    unsigned char *__restrict__  expr_6_in_1 = Args->expr_6_in_1; // (2, 2, 52)  (uint8-23) 3.157 Q8
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (2, 2, 52)  (uint8-39) 3.391 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (2, 2, 52) var shapes:
    // expr_6_out_0: (2, 2, 52) expr_6_in_1: (2, 2, 52) expr_6_in_0: (2, 2, 52)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_1: (uint8-23) 3.157 Q8 expr_6_in_0: (uint8-127)
        // 4.096 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_6_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_6_in_0, int32), [127]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_6_in_0, int32), [131]), [1]), [8319]), SigmoidLUTTable)), [8]), [166]), [14])), [238]), [8]), [-18]), 0, 255), uint8)
        // ADD_0_79 scale arg 0 (no zp adj) - (uint8-23) 3.157 Q8 -> (int32-23) 3.157 Q8
        int _SYMBOL_Cast233 = ((int)expr_6_in_1[i0]);
        // scale clip and cast - (int32-23) 6.314 Q9 -> (uint8-39) 3.391 Q8
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast233+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_6_in_0[i0])-(127))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_6_in_0[i0])*(131)), ((unsigned char)1))-(8319)), SigmoidLUTTable)), (8))*(166)), ((unsigned char)14)))*(238)), ((unsigned char)8))-(-18))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s209_kernel(s209_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0; // (1, 4, 3, 2)   (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_32_in_1 = Args->expr_32_in_1; // (1, 1, 3, 2)   int8 96.504 Q7
    signed char *__restrict__  expr_32_in_2 = Args->expr_32_in_2; // (1, 1, 1, 2)   int8 0.016 Q7
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 4, 3, 2)   (uint8-128) 3.011 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 4, 3, 2) var shapes:
    // inter_LOGISTIC_0_190: (1, 4, 3, 2) expr_32_in_0: (1, 4, 3, 2)
    // expr_32_out_0: (1, 4, 3, 2) expr_32_in_1: (1, 1, 3, 2) expr_32_in_2: (1,
    // 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
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
            // 96.504 Q7 expr_32_in_2: int8 0.016 Q7
            // expr_32_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_190), Cast(expr_32_in_1, int32)), [7]), Cast(expr_32_in_2, int32)), [129]), [22]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_190 = inter_LOGISTIC_0_190;
            // scale clip and cast - int32 1.520 Q15 -> (uint8-128) 3.011 Q8
            expr_32_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_190)*((int)expr_32_in_1[(i1*I2)+i2])), (7))*((int)expr_32_in_2[i2]))*(129)), ((unsigned char)22))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s215_kernel(s215_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_34_in_0 = Args->expr_34_in_0; // (1, 16, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_34_in_1 = Args->expr_34_in_1; // (1, 1, 3, 2)   int8 30.630 Q7
    signed char *__restrict__  expr_34_in_2 = Args->expr_34_in_2; // (1, 1, 1, 2)   int8 0.016 Q7
    unsigned char *__restrict__  expr_34_out_0 = Args->expr_34_out_0; // (1, 16, 3, 2)  uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 16, 3, 2) var shapes:
    // inter_LOGISTIC_0_207: (1, 16, 3, 2) expr_34_in_0: (1, 16, 3, 2)
    // expr_34_out_0: (1, 16, 3, 2) expr_34_in_1: (1, 1, 3, 2) expr_34_in_2:
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
            // 30.630 Q7 expr_34_in_2: int8 0.016 Q7
            // expr_34_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_207), Cast(expr_34_in_1, int32)), [7]), Cast(expr_34_in_2, int32)), [246]), [23]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_207 = inter_LOGISTIC_0_207;
            // scale clip and cast - int32 0.482 Q15 -> uint8 1.004 Q8
            expr_34_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_207)*((int)expr_34_in_1[(i1*I2)+i2])), (7))*((int)expr_34_in_2[i2]))*(246)), ((unsigned char)23))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s222_kernel(s222_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0; // (1, 64, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_35_in_1 = Args->expr_35_in_1; // (1, 1, 3, 2)   int8 14.110 Q7
    signed char *__restrict__  expr_35_in_2 = Args->expr_35_in_2; // (1, 1, 1, 2)   int8 0.016 Q7
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 64, 3, 2)  uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 64, 3, 2) var shapes:
    // inter_LOGISTIC_0_224: (1, 64, 3, 2) expr_35_in_0: (1, 64, 3, 2)
    // expr_35_out_0: (1, 64, 3, 2) expr_35_in_1: (1, 1, 3, 2) expr_35_in_2:
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
            // 14.110 Q7 expr_35_in_2: int8 0.016 Q7
            // expr_35_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_224), Cast(expr_35_in_1, int32)), [7]), Cast(expr_35_in_2, int32)), [227]), [24]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_224 = inter_LOGISTIC_0_224;
            // scale clip and cast - int32 0.222 Q15 -> uint8 1.004 Q8
            expr_35_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_224)*((int)expr_35_in_1[(i1*I2)+i2])), (7))*((int)expr_35_in_2[i2]))*(227)), ((unsigned char)24))), (((signed char)8))));
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
    // Max shape: (32, 32, 8) var shapes:
    // expr_33_out_0: (32, 32, 8) expr_33_in_0: (32, 32, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-118) 37.588 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [118]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_33_in_0, int32), [150]), [2]), [70800]), -65536, 65535), SigmoidLUTTable)), [8]), [234]), [14]), [-3]), 0, 255), uint8)
        // scale clip and cast - int32 37.588 Q15 -> (uint8-3) 10.273 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(118))*SigmoidTableInline(gap_clip(((((((int)expr_33_in_0[i0])*(150))<<((unsigned char)2))-(70800))), (((signed char)16))), SigmoidLUTTable)), (8))*(234)), ((unsigned char)14))-(-3))), (((signed char)8))));
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
    // Max shape: (16, 16, 16) var shapes:
    // expr_45_out_0: (16, 16, 16) expr_45_in_0: (16, 16, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-160) 29.624 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [160]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [237]), [1]), [75840]), -65536, 65535), SigmoidLUTTable)), [8]), [167]), [13]), [-6]), 0, 255), uint8)
        // scale clip and cast - int32 29.624 Q15 -> (uint8-6) 5.682 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(160))*SigmoidTableInline(gap_clip(((((((int)expr_45_in_0[i0])*(237))<<((unsigned char)1))-(75840))), (((signed char)16))), SigmoidLUTTable)), (8))*(167)), ((unsigned char)13))-(-6))), (((signed char)8))));
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
    // Max shape: (16, 16, 16) var shapes:
    // expr_31_out_0: (16, 16, 16) expr_31_in_0: (16, 16, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-168) 19.887 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [168]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [159]), [1]), [53424]), SigmoidLUTTable)), [8]), [180]), [13]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 19.887 Q15 -> (uint8-10) 3.535 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(168))*SigmoidTableInline((((((int)expr_31_in_0[i0])*(159))<<((unsigned char)1))-(53424)), SigmoidLUTTable)), (8))*(180)), ((unsigned char)13))-(-10))), (((signed char)8))));
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
    // Max shape: (16, 16, 8) var shapes:
    // expr_13_out_0: (16, 16, 8) expr_13_in_0: (16, 16, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-137) 9.673 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [137]), SigmoidLUT(Sub(Mul(Cast(expr_13_in_0, int32), [155]), [21235]), SigmoidLUTTable)), [8]), [132]), [13]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 9.673 Q15 -> (uint8-15) 2.353 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(137))*SigmoidTableInline(((((int)expr_13_in_0[i0])*(155))-(21235)), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-15))), (((signed char)8))));
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
    // Max shape: (16, 16, 16) var shapes:
    // expr_36_out_0: (16, 16, 16) expr_36_in_0: (16, 16, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-146) 11.053 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [146]), SigmoidLUT(Sub(Mul(Cast(expr_36_in_0, int32), [177]), [25842]), SigmoidLUTTable)), [8]), [142]), [13]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 11.053 Q15 -> (uint8-14) 2.486 Q7
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(146))*SigmoidTableInline(((((int)expr_36_in_0[i0])*(177))-(25842)), SigmoidLUTTable)), (8))*(142)), ((unsigned char)13))-(-14))), (((signed char)8))));
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
    // Max shape: (8, 8, 32) var shapes:
    // expr_37_out_0: (8, 8, 32) expr_37_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-157) 7.459 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [157]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_37_in_0, int32), [239]), [1]), [18762]), SigmoidLUTTable)), [8]), [159]), [13]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 7.459 Q15 -> (uint8-24) 1.499 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(157))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_37_in_0[i0])*(239)), ((unsigned char)1))-(18762)), SigmoidLUTTable)), (8))*(159)), ((unsigned char)13))-(-24))), (((signed char)8))));
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
    // Max shape: (8, 8, 32) var shapes:
    // expr_38_out_0: (8, 8, 32) expr_38_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-155) 7.118 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [155]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_38_in_0, int32), [228]), [1]), [17670]), SigmoidLUTTable)), [8]), [156]), [13]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 7.118 Q15 -> (uint8-24) 1.457 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(155))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_38_in_0[i0])*(228)), ((unsigned char)1))-(17670)), SigmoidLUTTable)), (8))*(156)), ((unsigned char)13))-(-24))), (((signed char)8))));
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
    // Max shape: (8, 8, 16) var shapes:
    // expr_39_out_0: (8, 8, 16) expr_39_in_0: (8, 8, 16) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-131) 6.451 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_39_in_0, int32), [206]), [1]), [13493]), SigmoidLUTTable)), [8]), [252]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 6.451 Q15 -> (uint8-22) 1.636 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_39_in_0[i0])*(206)), ((unsigned char)1))-(13493)), SigmoidLUTTable)), (8))*(252)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (8, 8, 32) var shapes:
    // expr_41_out_0: (8, 8, 32) expr_41_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-100) 6.192 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [100]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_41_in_0, int32), [198]), [1]), [9900]), SigmoidLUTTable)), [8]), [200]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 6.192 Q15 -> (uint8-18) 1.979 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(100))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_41_in_0[i0])*(198)), ((unsigned char)1))-(9900)), SigmoidLUTTable)), (8))*(200)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_42_out_0: (4, 4, 56) expr_42_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-106) 5.795 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [106]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_42_in_0, int32), [185]), [1]), [9805]), SigmoidLUTTable)), [8]), [209]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 5.795 Q15 -> (uint8-20) 1.774 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(106))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_42_in_0[i0])*(185)), ((unsigned char)1))-(9805)), SigmoidLUTTable)), (8))*(209)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_43_out_0: (4, 4, 56) expr_43_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-112) 4.878 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [112]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_43_in_0, int32), [156]), [1]), [8736]), SigmoidLUTTable)), [8]), [220]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 4.878 Q15 -> (uint8-25) 1.421 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(112))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_43_in_0[i0])*(156)), ((unsigned char)1))-(8736)), SigmoidLUTTable)), (8))*(220)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (4, 4, 28) var shapes:
    // expr_44_out_0: (4, 4, 28) expr_44_in_0: (4, 4, 28) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-112) 5.045 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [112]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_44_in_0, int32), [161]), [1]), [9016]), SigmoidLUTTable)), [8]), [218]), [14]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 5.045 Q15 -> (uint8-24) 1.480 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(112))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_44_in_0[i0])*(161)), ((unsigned char)1))-(9016)), SigmoidLUTTable)), (8))*(218)), ((unsigned char)14))-(-24))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_47_out_0: (4, 4, 56) expr_47_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_47_in_0: (uint8-137) 5.208 Q8
        // expr_47_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_47_in_0, int32), [137]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_47_in_0, int32), [167]), [1]), [11440]), SigmoidLUTTable)), [8]), [134]), [13]), [-29]), 0, 255), uint8)
        // scale clip and cast - int32 5.208 Q15 -> (uint8-29) 1.248 Q7
        expr_47_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_47_in_0[i0])-(137))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_47_in_0[i0])*(167)), ((unsigned char)1))-(11440)), SigmoidLUTTable)), (8))*(134)), ((unsigned char)13))-(-29))), (((signed char)8))));
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
    // Max shape: (2, 2, 104) var shapes:
    // expr_48_out_0: (2, 2, 104) expr_48_in_0: (2, 2, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-132) 4.695 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [132]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_48_in_0, int32), [150]), [1]), [9900]), SigmoidLUTTable)), [8]), [129]), [13]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 4.695 Q15 -> (uint8-31) 1.161 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(132))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_48_in_0[i0])*(150)), ((unsigned char)1))-(9900)), SigmoidLUTTable)), (8))*(129)), ((unsigned char)13))-(-31))), (((signed char)8))));
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
    // Max shape: (2, 2, 104) var shapes:
    // expr_49_out_0: (2, 2, 104) expr_49_in_0: (2, 2, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-109) 5.278 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [109]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_49_in_0, int32), [169]), [1]), [9211]), SigmoidLUTTable)), [8]), [214]), [14]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 5.278 Q15 -> (uint8-23) 1.579 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(109))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_49_in_0[i0])*(169)), ((unsigned char)1))-(9211)), SigmoidLUTTable)), (8))*(214)), ((unsigned char)14))-(-23))), (((signed char)8))));
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
    // Max shape: (2, 2, 52) var shapes:
    // expr_50_out_0: (2, 2, 52) expr_50_in_0: (2, 2, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-117) 4.078 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [117]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_50_in_0, int32), [131]), [1]), [7664]), SigmoidLUTTable)), [8]), [230]), [14]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 4.078 Q15 -> (uint8-31) 1.136 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(117))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_50_in_0[i0])*(131)), ((unsigned char)1))-(7664)), SigmoidLUTTable)), (8))*(230)), ((unsigned char)14))-(-31))), (((signed char)8))));
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
    // Max shape: (2, 2, 104) var shapes:
    // expr_52_out_0: (2, 2, 104) expr_52_in_0: (2, 2, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_52_in_0: (uint8-131) 5.648 Q8
        // expr_52_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_52_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_52_in_0, int32), [181]), [1]), [11856]), SigmoidLUTTable)), [8]), [254]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.648 Q15 -> (uint8-25) 1.425 Q7
        expr_52_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_52_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_52_in_0[i0])*(181)), ((unsigned char)1))-(11856)), SigmoidLUTTable)), (8))*(254)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (2, 2, 52) var shapes:
    // expr_53_out_0: (2, 2, 52) expr_53_in_0: (2, 2, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-101) 5.447 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [101]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_53_in_0, int32), [174]), [1]), [8787]), SigmoidLUTTable)), [8]), [202]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 5.447 Q15 -> (uint8-21) 1.728 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(101))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_53_in_0[i0])*(174)), ((unsigned char)1))-(8787)), SigmoidLUTTable)), (8))*(202)), ((unsigned char)14))-(-21))), (((signed char)8))));
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
    // Max shape: (2, 2, 104) var shapes:
    // expr_55_out_0: (2, 2, 104) expr_55_in_0: (2, 2, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-101) 3.747 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [101]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_55_in_0, int32), [240]), [2]), [6060]), SigmoidLUTTable)), [8]), [206]), [14]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 3.747 Q15 -> (uint8-31) 1.165 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_55_in_0[i0])-(101))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_55_in_0[i0])*(240)), ((unsigned char)2))-(6060)), SigmoidLUTTable)), (8))*(206)), ((unsigned char)14))-(-31))), (((signed char)8))));
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
    // Max shape: (2, 2, 56) var shapes:
    // expr_56_out_0: (2, 2, 56) expr_56_in_0: (2, 2, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-108) 2.042 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [108]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_56_in_0, int32), [131]), [2]), [3537]), SigmoidLUTTable)), [8]), [226]), [14]), [-56]), 0, 255), uint8)
        // scale clip and cast - int32 2.042 Q15 -> (uint8-56) 0.579 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(108))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_56_in_0[i0])*(131)), ((unsigned char)2))-(3537)), SigmoidLUTTable)), (8))*(226)), ((unsigned char)14))-(-56))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_10_out_0: (4, 4, 56) expr_10_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-96) 4.338 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [96]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_10_in_0, int32), [139]), [1]), [6672]), SigmoidLUTTable)), [8]), [198]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 4.338 Q15 -> (uint8-25) 1.404 Q7
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_10_in_0[i0])-(96))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_10_in_0[i0])*(139)), ((unsigned char)1))-(6672)), SigmoidLUTTable)), (8))*(198)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (4, 4, 28) var shapes:
    // expr_8_out_0: (4, 4, 28) expr_8_in_0: (4, 4, 28) SigmoidLUTTable: (1, 1,
    // 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_8_in_0: (uint8-128) 5.231 Q8
        // expr_8_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_8_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_8_in_0, int32), [167]), [1]), [10688]), SigmoidLUTTable)), [8]), [248]), [14]), [-26]), 0, 255), uint8)
        // scale clip and cast - int32 5.231 Q15 -> (uint8-26) 1.347 Q7
        expr_8_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_8_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_8_in_0[i0])*(167)), ((unsigned char)1))-(10688)), SigmoidLUTTable)), (8))*(248)), ((unsigned char)14))-(-26))), (((signed char)8))));
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
    // Max shape: (4, 4, 28) var shapes:
    // expr_9_out_0: (4, 4, 28) expr_9_in_0: (4, 4, 28) SigmoidLUTTable: (1, 1,
    // 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-130) 5.014 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [130]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_9_in_0, int32), [160]), [1]), [10400]), SigmoidLUTTable)), [8]), [228]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.014 Q15 -> (uint8-25) 2.811 Q8
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(130))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_9_in_0[i0])*(160)), ((unsigned char)1))-(10400)), SigmoidLUTTable)), (8))*(228)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_11_out_0: (4, 4, 56) expr_11_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-123) 5.508 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_11_in_0, int32), [176]), [1]), [10824]), SigmoidLUTTable)), [8]), [238]), [14]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 5.508 Q15 -> (uint8-24) 1.483 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_11_in_0[i0])*(176)), ((unsigned char)1))-(10824)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-24))), (((signed char)8))));
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
    // Max shape: (4, 4, 32) var shapes:
    // expr_12_out_0: (4, 4, 32) expr_12_in_0: (4, 4, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-138) 3.766 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [138]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_12_in_0, int32), [241]), [2]), [8315]), SigmoidLUTTable)), [8]), [138]), [13]), [-41]), 0, 255), uint8)
        // scale clip and cast - int32 3.766 Q15 -> (uint8-41) 0.871 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_12_in_0[i0])-(138))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_12_in_0[i0])*(241)), ((unsigned char)2))-(8315)), SigmoidLUTTable)), (8))*(138)), ((unsigned char)13))-(-41))), (((signed char)8))));
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
    // Max shape: (8, 8, 32) var shapes:
    // expr_14_out_0: (8, 8, 32) expr_14_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-120) 5.985 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_14_in_0, int32), [192]), [1]), [11520]), SigmoidLUTTable)), [8]), [230]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 5.985 Q15 -> (uint8-21) 1.664 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_14_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_14_in_0[i0])*(192)), ((unsigned char)1))-(11520)), SigmoidLUTTable)), (8))*(230)), ((unsigned char)14))-(-21))), (((signed char)8))));
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
    // Max shape: (8, 8, 16) var shapes:
    // expr_15_out_0: (8, 8, 16) expr_15_in_0: (8, 8, 16) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_15_in_0: (uint8-131) 7.939 Q8
        // expr_15_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_15_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_15_in_0, int32), [254]), [1]), [16637]), SigmoidLUTTable)), [8]), [251]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.939 Q15 -> (uint8-18) 2.024 Q7
        expr_15_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_15_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_15_in_0[i0])*(254)), ((unsigned char)1))-(16637)), SigmoidLUTTable)), (8))*(251)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (8, 8, 16) var shapes:
    // expr_16_out_0: (8, 8, 16) expr_16_in_0: (8, 8, 16) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-137) 9.363 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [137]), SigmoidLUT(Sub(Mul(Cast(expr_16_in_0, int32), [150]), [20550]), SigmoidLUTTable)), [8]), [132]), [13]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 9.363 Q15 -> (uint8-16) 2.271 Q7
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_16_in_0[i0])-(137))*SigmoidTableInline(((((int)expr_16_in_0[i0])*(150))-(20550)), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-16))), (((signed char)8))));
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
    // Max shape: (8, 8, 32) var shapes:
    // expr_18_out_0: (8, 8, 32) expr_18_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-123) 9.922 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [123]), SigmoidLUT(Sub(Mul(Cast(expr_18_in_0, int32), [159]), [19557]), SigmoidLUTTable)), [8]), [235]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 9.922 Q15 -> (uint8-13) 2.702 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(123))*SigmoidTableInline(((((int)expr_18_in_0[i0])*(159))-(19557)), SigmoidLUTTable)), (8))*(235)), ((unsigned char)14))-(-13))), (((signed char)8))));
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
    // Max shape: (4, 4, 32) var shapes:
    // expr_19_out_0: (4, 4, 32) expr_19_in_0: (4, 4, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-115) 5.602 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [115]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_19_in_0, int32), [179]), [1]), [10293]), SigmoidLUTTable)), [8]), [223]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 5.602 Q15 -> (uint8-22) 3.210 Q8
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(115))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_19_in_0[i0])*(179)), ((unsigned char)1))-(10293)), SigmoidLUTTable)), (8))*(223)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_20_out_0: (4, 4, 56) expr_20_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-129) 4.894 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_20_in_0, int32), [129]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_20_in_0, int32), [157]), [1]), [10127]), SigmoidLUTTable)), [8]), [250]), [14]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 4.894 Q15 -> (uint8-28) 1.251 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_20_in_0[i0])-(129))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_20_in_0[i0])*(157)), ((unsigned char)1))-(10127)), SigmoidLUTTable)), (8))*(250)), ((unsigned char)14))-(-28))), (((signed char)8))));
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
    // Max shape: (4, 4, 28) var shapes:
    // expr_21_out_0: (4, 4, 28) expr_21_in_0: (4, 4, 28) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-124) 5.530 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [124]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_21_in_0, int32), [177]), [1]), [10974]), SigmoidLUTTable)), [8]), [239]), [14]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 5.530 Q15 -> (uint8-24) 1.479 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(124))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_21_in_0[i0])*(177)), ((unsigned char)1))-(10974)), SigmoidLUTTable)), (8))*(239)), ((unsigned char)14))-(-24))), (((signed char)8))));
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
    // Max shape: (4, 4, 28) var shapes:
    // expr_22_out_0: (4, 4, 28) expr_22_in_0: (4, 4, 28) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-111) 6.014 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [111]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_22_in_0, int32), [192]), [1]), [10656]), SigmoidLUTTable)), [8]), [217]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.014 Q15 -> (uint8-20) 1.776 Q7
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_22_in_0[i0])-(111))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_22_in_0[i0])*(192)), ((unsigned char)1))-(10656)), SigmoidLUTTable)), (8))*(217)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_24_out_0: (4, 4, 56) expr_24_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_24_in_0: (uint8-92) 5.706 Q8
        // expr_24_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_24_in_0, int32), [92]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_24_in_0, int32), [183]), [1]), [8418]), SigmoidLUTTable)), [8]), [190]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 5.706 Q15 -> (uint8-19) 1.919 Q7
        expr_24_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_24_in_0[i0])-(92))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_24_in_0[i0])*(183)), ((unsigned char)1))-(8418)), SigmoidLUTTable)), (8))*(190)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (2, 2, 56) var shapes:
    // expr_25_out_0: (2, 2, 56) expr_25_in_0: (2, 2, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-133) 5.248 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [133]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_25_in_0, int32), [168]), [1]), [11172]), SigmoidLUTTable)), [8]), [129]), [13]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 5.248 Q15 -> (uint8-27) 1.302 Q7
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(133))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_25_in_0[i0])*(168)), ((unsigned char)1))-(11172)), SigmoidLUTTable)), (8))*(129)), ((unsigned char)13))-(-27))), (((signed char)8))));
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
    // Max shape: (2, 2, 104) var shapes:
    // expr_26_out_0: (2, 2, 104) expr_26_in_0: (2, 2, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-118) 6.251 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [118]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_26_in_0, int32), [200]), [1]), [11800]), SigmoidLUTTable)), [8]), [227]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.251 Q15 -> (uint8-20) 1.761 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(118))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_26_in_0[i0])*(200)), ((unsigned char)1))-(11800)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (2, 2, 52) var shapes:
    // expr_27_out_0: (2, 2, 52) expr_27_in_0: (2, 2, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-117) 4.240 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [117]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_27_in_0, int32), [136]), [1]), [7956]), SigmoidLUTTable)), [8]), [230]), [14]), [-30]), 0, 255), uint8)
        // scale clip and cast - int32 4.240 Q15 -> (uint8-30) 1.178 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_27_in_0[i0])-(117))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_27_in_0[i0])*(136)), ((unsigned char)1))-(7956)), SigmoidLUTTable)), (8))*(230)), ((unsigned char)14))-(-30))), (((signed char)8))));
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
    // Max shape: (2, 2, 52) var shapes:
    // expr_28_out_0: (2, 2, 52) expr_28_in_0: (2, 2, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-131) 4.800 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_28_in_0, int32), [154]), [1]), [10087]), SigmoidLUTTable)), [8]), [174]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 4.800 Q15 -> (uint8-20) 3.528 Q8
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_28_in_0[i0])*(154)), ((unsigned char)1))-(10087)), SigmoidLUTTable)), (8))*(174)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (2, 2, 104) var shapes:
    // expr_30_out_0: (2, 2, 104) expr_30_in_0: (2, 2, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-125) 5.331 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [125]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_30_in_0, int32), [171]), [1]), [10688]), SigmoidLUTTable)), [8]), [242]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.331 Q15 -> (uint8-25) 1.411 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_30_in_0[i0])-(125))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_30_in_0[i0])*(171)), ((unsigned char)1))-(10688)), SigmoidLUTTable)), (8))*(242)), ((unsigned char)14))-(-25))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop