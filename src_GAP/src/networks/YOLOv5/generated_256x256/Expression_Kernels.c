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
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (64, 64, 8) (uint8-126) 13.611 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (64, 64, 8) (uint8-8) 8.818 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (64, 64, 8) (uint8-16) 9.103 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (64, 64, 8) var shapes:
    // expr_0_out_0: (64, 64, 8) expr_0_in_1: (64, 64, 8) expr_0_in_0: (64, 64,
    // 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-8) 8.818 Q8 expr_0_in_0: (uint8-126)
        // 13.611 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_0_in_0, int32), [218]), [27468]), SigmoidLUTTable)), [8]), [198]), [14])), [248]), [8]), [-8]), 0, 255), uint8)
        // ADD_0_16 scale arg 0 (no zp adj) - (uint8-8) 8.818 Q8 -> (int32-8) 8.818 Q8
        int _SYMBOL_Cast238 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-8) 17.636 Q9 -> (uint8-16) 9.103 Q8
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast238+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(126))*SigmoidTableInline(((((int)expr_0_in_0[i0])*(218))-(27468)), SigmoidLUTTable)), (8))*(198)), ((unsigned char)14)))*(248)), ((unsigned char)8))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s188_kernel(s188_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (1, 64, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (1, 64, 1, 2)  int8 6.551 Q7
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (1, 1, 1, 2)   int8 0.004 Q7
    unsigned char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (1, 64, 3, 2)  (uint8-128) 2.343 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 64, 3, 2) var shapes:
    // expr_1_out_0: (1, 64, 3, 2) expr_1_in_0: (1, 64, 3, 2) expr_1_in_1: (1,
    // 64, 1, 2) expr_1_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_1_in_0: (uint8-128) 12.578 Q8 expr_1_in_1: int8
            // 6.551 Q7 expr_1_in_2: int8 0.004 Q7
            // expr_1_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_1_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_1_in_1, int32), [210]), [2])), [1]), [1]), Cast(expr_1_in_2, int32)), [220]), [24]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.504 Q15 -> (uint8-128) 2.343 Q8
            expr_1_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_1_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_1_in_1[i2])*(210))<<((unsigned char)2)))*(1)), (1))*((int)expr_1_in_2[i2]))*(220)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (1, 256, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (1, 256, 1, 2) int8 14.614 Q7
    signed char *__restrict__  expr_2_in_2 = Args->expr_2_in_2; // (1, 1, 1, 2)   int8 0.004 Q7
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (1, 256, 3, 2) (uint8-128) 2.343 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 256, 3, 2) var shapes:
    // expr_2_out_0: (1, 256, 3, 2) expr_2_in_0: (1, 256, 3, 2) expr_2_in_1:
    // (1, 256, 1, 2) expr_2_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_2_in_0: (uint8-128) 12.578 Q8 expr_2_in_1: int8
            // 14.614 Q7 expr_2_in_2: int8 0.004 Q7
            // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_2_in_1, int32), [234]), [3])), [1]), [1]), Cast(expr_2_in_2, int32)), [220]), [25]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.252 Q15 -> (uint8-128) 2.343 Q8
            expr_2_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_2_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_2_in_1[i2])*(234))<<((unsigned char)3)))*(1)), (1))*((int)expr_2_in_2[i2]))*(220)), ((unsigned char)25))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s221_kernel(s221_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256)  
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (1, 1024, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (1, 1024, 1, 2) int8 30.740 Q7
    signed char *__restrict__  expr_3_in_2 = Args->expr_3_in_2; // (1, 1, 1, 2)    int8 0.004 Q7
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (1, 1024, 3, 2) (uint8-128) 2.343 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 1024, 3, 2) var shapes:
    // expr_3_out_0: (1, 1024, 3, 2) expr_3_in_0: (1, 1024, 3, 2) expr_3_in_1:
    // (1, 1024, 1, 2) expr_3_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1,
    // 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_3_in_0: (uint8-128) 12.578 Q8 expr_3_in_1: int8
            // 30.740 Q7 expr_3_in_2: int8 0.004 Q7
            // expr_3_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_3_in_1, int32), [246]), [4])), [1]), [1]), Cast(expr_3_in_2, int32)), [220]), [26]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.126 Q15 -> (uint8-128) 2.343 Q8
            expr_3_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_3_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_3_in_1[i2])*(246))<<((unsigned char)4)))*(1)), (1))*((int)expr_3_in_2[i2]))*(220)), ((unsigned char)26))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (32, 32, 16) (uint8-127) 8.409 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (32, 32, 16) (uint8-16) 4.529 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (32, 32, 16) (uint8-29) 2.501 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 16) var shapes:
    // expr_4_out_0: (32, 32, 16) expr_4_in_1: (32, 32, 16) expr_4_in_0: (32,
    // 32, 16) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-16) 4.529 Q8 expr_4_in_0: (uint8-127)
        // 8.409 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_4_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_4_in_0, int32), [127]), SigmoidLUT(Sub(Mul(Cast(expr_4_in_0, int32), [135]), [17145]), SigmoidLUTTable)), [8]), [238]), [14])), [232]), [8]), [-14]), 0, 255), uint8)
        // ADD_0_37 scale arg 0 (no zp adj) - (uint8-16) 4.529 Q8 -> (int32-16) 4.529 Q8
        int _SYMBOL_Cast28 = ((int)expr_4_in_1[i0]);
        // scale clip and cast - (int32-16) 9.057 Q9 -> (uint8-29) 2.501 Q7
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast28+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(127))*SigmoidTableInline(((((int)expr_4_in_0[i0])*(135))-(17145)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14)))*(232)), ((unsigned char)8))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s57_kernel(s57_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0; // (16, 16, 28) (uint8-116) 6.943 Q8
    unsigned char *__restrict__  expr_5_in_1 = Args->expr_5_in_1; // (16, 16, 28) (uint8-20) 3.495 Q8
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (16, 16, 28) (uint8-24) 2.964 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 28) var shapes:
    // expr_5_out_0: (16, 16, 28) expr_5_in_1: (16, 16, 28) expr_5_in_0: (16,
    // 16, 28) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_1: (uint8-20) 3.495 Q8 expr_5_in_0: (uint8-116)
        // 6.943 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_5_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_5_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_5_in_0, int32), [222]), [1]), [12876]), SigmoidLUTTable)), [8]), [254]), [14])), [151]), [8]), [-12]), 0, 255), uint8)
        // ADD_0_58 scale arg 0 (no zp adj) - (uint8-20) 3.495 Q8 -> (int32-20) 3.495 Q8
        int _SYMBOL_Cast44 = ((int)expr_5_in_1[i0]);
        // scale clip and cast - (int32-20) 6.989 Q9 -> (uint8-24) 2.964 Q7
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast44+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_5_in_0[i0])*(222)), ((unsigned char)1))-(12876)), SigmoidLUTTable)), (8))*(254)), ((unsigned char)14)))*(151)), ((unsigned char)8))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s77_kernel(s77_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0; // (8, 8, 52)  (uint8-140) 5.848 Q8
    unsigned char *__restrict__  expr_6_in_1 = Args->expr_6_in_1; // (8, 8, 52)  (uint8-22) 3.212 Q8
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (8, 8, 52)  (uint8-38) 1.897 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 52) var shapes:
    // expr_6_out_0: (8, 8, 52) expr_6_in_1: (8, 8, 52) expr_6_in_0: (8, 8, 52)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_1: (uint8-22) 3.212 Q8 expr_6_in_0: (uint8-140)
        // 5.848 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_6_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_6_in_0, int32), [140]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_6_in_0, int32), [187]), [1]), [13090]), SigmoidLUTTable)), [8]), [233]), [14])), [217]), [8]), [-19]), 0, 255), uint8)
        // ADD_0_79 scale arg 0 (no zp adj) - (uint8-22) 3.212 Q8 -> (int32-22) 3.212 Q8
        int _SYMBOL_Cast60 = ((int)expr_6_in_1[i0]);
        // scale clip and cast - (int32-22) 6.424 Q9 -> (uint8-38) 1.897 Q7
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast60+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_6_in_0[i0])-(140))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_6_in_0[i0])*(187)), ((unsigned char)1))-(13090)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14)))*(217)), ((unsigned char)8))-(-19))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s211_kernel(s211_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0; // (1, 64, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_32_in_1 = Args->expr_32_in_1; // (1, 1, 3, 2)   int8 1503.748 Q7
    signed char *__restrict__  expr_32_in_2 = Args->expr_32_in_2; // (1, 1, 1, 2)   int8 0.004 Q7
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 64, 3, 2)  (uint8-128) 2.343 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 64, 3, 2) var shapes:
    // inter_LOGISTIC_0_190: (1, 64, 3, 2) expr_32_in_0: (1, 64, 3, 2)
    // expr_32_out_0: (1, 64, 3, 2) expr_32_in_1: (1, 1, 3, 2) expr_32_in_2:
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
            // 1503.748 Q7 expr_32_in_2: int8 0.004 Q7
            // expr_32_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_190), Cast(expr_32_in_1, int32)), [7]), Cast(expr_32_in_2, int32)), [162]), [20]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_190 = inter_LOGISTIC_0_190;
            // scale clip and cast - int32 5.920 Q15 -> (uint8-128) 2.343 Q8
            expr_32_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_190)*((int)expr_32_in_1[(i1*I2)+i2])), (7))*((int)expr_32_in_2[i2]))*(162)), ((unsigned char)20))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_34_in_0 = Args->expr_34_in_0; // (1, 256, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_34_in_1 = Args->expr_34_in_1; // (1, 1, 3, 2)   int8 479.748 Q7
    signed char *__restrict__  expr_34_in_2 = Args->expr_34_in_2; // (1, 1, 1, 2)   int8 0.004 Q7
    unsigned char *__restrict__  expr_34_out_0 = Args->expr_34_out_0; // (1, 256, 3, 2) (uint8-128) 2.343 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 256, 3, 2) var shapes:
    // inter_LOGISTIC_0_207: (1, 256, 3, 2) expr_34_in_0: (1, 256, 3, 2)
    // expr_34_out_0: (1, 256, 3, 2) expr_34_in_1: (1, 1, 3, 2) expr_34_in_2:
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
            // 479.748 Q7 expr_34_in_2: int8 0.004 Q7
            // expr_34_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_207), Cast(expr_34_in_1, int32)), [7]), Cast(expr_34_in_2, int32)), [206]), [22]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_207 = inter_LOGISTIC_0_207;
            // scale clip and cast - int32 1.889 Q15 -> (uint8-128) 2.343 Q8
            expr_34_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_207)*((int)expr_34_in_1[(i1*I2)+i2])), (7))*((int)expr_34_in_2[i2]))*(206)), ((unsigned char)22))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s223_kernel(s223_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256)  
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0; // (1, 1024, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_35_in_1 = Args->expr_35_in_1; // (1, 1, 3, 2)    int8 133.039 Q7
    signed char *__restrict__  expr_35_in_2 = Args->expr_35_in_2; // (1, 1, 1, 2)    int8 0.004 Q7
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 1024, 3, 2) (uint8-128) 2.343 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 1024, 3, 2) var shapes:
    // inter_LOGISTIC_0_224: (1, 1024, 3, 2) expr_35_in_0: (1, 1024, 3, 2)
    // expr_35_out_0: (1, 1024, 3, 2) expr_35_in_1: (1, 1, 3, 2) expr_35_in_2:
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
            // 133.039 Q7 expr_35_in_2: int8 0.004 Q7
            // expr_35_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_224), Cast(expr_35_in_1, int32)), [7]), Cast(expr_35_in_2, int32)), [229]), [24]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_224 = inter_LOGISTIC_0_224;
            // scale clip and cast - int32 0.524 Q15 -> (uint8-128) 2.343 Q8
            expr_35_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_224)*((int)expr_35_in_1[(i1*I2)+i2])), (7))*((int)expr_35_in_2[i2]))*(229)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    // Max shape: (128, 128, 8) var shapes:
    // expr_33_out_0: (128, 128, 8) expr_33_in_0: (128, 128, 8)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-148) 50.185 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [148]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_33_in_0, int32), [201]), [2]), [118992]), -65536, 65535), SigmoidLUTTable)), [8]), [150]), [13]), [-3]), 0, 255), uint8)
        // scale clip and cast - int32 50.185 Q15 -> (uint8-3) 10.684 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(148))*SigmoidTableInline(gap_clip(((((((int)expr_33_in_0[i0])*(201))<<((unsigned char)2))-(118992))), (((signed char)16))), SigmoidLUTTable)), (8))*(150)), ((unsigned char)13))-(-3))), (((signed char)8))));
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
    // Max shape: (64, 64, 16) var shapes:
    // expr_45_out_0: (64, 64, 16) expr_45_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-162) 51.616 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [162]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [206]), [2]), [133488]), -65536, 65535), SigmoidLUTTable)), [8]), [172]), [13]), [-4]), 0, 255), uint8)
        // scale clip and cast - int32 51.616 Q15 -> (uint8-4) 9.579 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(162))*SigmoidTableInline(gap_clip(((((((int)expr_45_in_0[i0])*(206))<<((unsigned char)2))-(133488))), (((signed char)16))), SigmoidLUTTable)), (8))*(172)), ((unsigned char)13))-(-4))), (((signed char)8))));
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
    // Max shape: (64, 64, 16) var shapes:
    // expr_31_out_0: (64, 64, 16) expr_31_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-155) 21.748 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [155]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [174]), [1]), [53940]), SigmoidLUTTable)), [8]), [158]), [13]), [-8]), 0, 255), uint8)
        // scale clip and cast - int32 21.748 Q15 -> (uint8-8) 4.409 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(155))*SigmoidTableInline((((((int)expr_31_in_0[i0])*(174))<<((unsigned char)1))-(53940)), SigmoidLUTTable)), (8))*(158)), ((unsigned char)13))-(-8))), (((signed char)8))));
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
    // Max shape: (64, 64, 8) var shapes:
    // expr_13_out_0: (64, 64, 8) expr_13_in_0: (64, 64, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-154) 12.415 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [154]), SigmoidLUT(Sub(Mul(Cast(expr_13_in_0, int32), [199]), [30646]), SigmoidLUTTable)), [8]), [155]), [13]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 12.415 Q15 -> (uint8-14) 2.568 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(154))*SigmoidTableInline(((((int)expr_13_in_0[i0])*(199))-(30646)), SigmoidLUTTable)), (8))*(155)), ((unsigned char)13))-(-14))), (((signed char)8))));
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
    // Max shape: (64, 64, 16) var shapes:
    // expr_36_out_0: (64, 64, 16) expr_36_in_0: (64, 64, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-151) 12.993 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [151]), SigmoidLUT(Sub(Mul(Cast(expr_36_in_0, int32), [208]), [31408]), SigmoidLUTTable)), [8]), [150]), [13]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 12.993 Q15 -> (uint8-13) 2.776 Q7
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(151))*SigmoidTableInline(((((int)expr_36_in_0[i0])*(208))-(31408)), SigmoidLUTTable)), (8))*(150)), ((unsigned char)13))-(-13))), (((signed char)8))));
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
    // Max shape: (32, 32, 32) var shapes:
    // expr_37_out_0: (32, 32, 32) expr_37_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-121) 9.318 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [121]), SigmoidLUT(Sub(Mul(Cast(expr_37_in_0, int32), [149]), [18029]), SigmoidLUTTable)), [8]), [232]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 9.318 Q15 -> (uint8-14) 2.575 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(121))*SigmoidTableInline(((((int)expr_37_in_0[i0])*(149))-(18029)), SigmoidLUTTable)), (8))*(232)), ((unsigned char)14))-(-14))), (((signed char)8))));
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
    // Max shape: (32, 32, 32) var shapes:
    // expr_38_out_0: (32, 32, 32) expr_38_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-126) 8.506 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_38_in_0, int32), [136]), [17136]), SigmoidLUTTable)), [8]), [240]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.506 Q15 -> (uint8-16) 2.264 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(126))*SigmoidTableInline(((((int)expr_38_in_0[i0])*(136))-(17136)), SigmoidLUTTable)), (8))*(240)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (32, 32, 16) var shapes:
    // expr_39_out_0: (32, 32, 16) expr_39_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-140) 8.758 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [140]), SigmoidLUT(Sub(Mul(Cast(expr_39_in_0, int32), [140]), [19600]), SigmoidLUTTable)), [8]), [135]), [13]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 8.758 Q15 -> (uint8-17) 2.077 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(140))*SigmoidTableInline(((((int)expr_39_in_0[i0])*(140))-(19600)), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-17))), (((signed char)8))));
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
    // Max shape: (32, 32, 32) var shapes:
    // expr_41_out_0: (32, 32, 32) expr_41_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-123) 6.472 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_41_in_0, int32), [207]), [1]), [12731]), SigmoidLUTTable)), [8]), [236]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.472 Q15 -> (uint8-20) 1.756 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_41_in_0[i0])*(207)), ((unsigned char)1))-(12731)), SigmoidLUTTable)), (8))*(236)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (16, 16, 56) var shapes:
    // expr_42_out_0: (16, 16, 56) expr_42_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-140) 7.843 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [140]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_42_in_0, int32), [251]), [1]), [17570]), SigmoidLUTTable)), [8]), [135]), [13]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 7.843 Q15 -> (uint8-19) 1.854 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(140))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_42_in_0[i0])*(251)), ((unsigned char)1))-(17570)), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-19))), (((signed char)8))));
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
    // Max shape: (16, 16, 56) var shapes:
    // expr_43_out_0: (16, 16, 56) expr_43_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-131) 6.841 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_43_in_0, int32), [219]), [1]), [14345]), SigmoidLUTTable)), [8]), [251]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.841 Q15 -> (uint8-20) 1.747 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_43_in_0[i0])*(219)), ((unsigned char)1))-(14345)), SigmoidLUTTable)), (8))*(251)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (16, 16, 28) var shapes:
    // expr_44_out_0: (16, 16, 28) expr_44_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-137) 6.658 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [137]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_44_in_0, int32), [213]), [1]), [14591]), SigmoidLUTTable)), [8]), [132]), [13]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 6.658 Q15 -> (uint8-22) 1.618 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(137))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_44_in_0[i0])*(213)), ((unsigned char)1))-(14591)), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-22))), (((signed char)8))));
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
    // Max shape: (16, 16, 56) var shapes:
    // expr_47_out_0: (16, 16, 56) expr_47_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_47_in_0: (uint8-130) 6.633 Q8
        // expr_47_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_47_in_0, int32), [130]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_47_in_0, int32), [212]), [1]), [13780]), SigmoidLUTTable)), [8]), [250]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 6.633 Q15 -> (uint8-21) 1.700 Q7
        expr_47_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_47_in_0[i0])-(130))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_47_in_0[i0])*(212)), ((unsigned char)1))-(13780)), SigmoidLUTTable)), (8))*(250)), ((unsigned char)14))-(-21))), (((signed char)8))));
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
    // Max shape: (8, 8, 104) var shapes:
    // expr_48_out_0: (8, 8, 104) expr_48_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-132) 6.185 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [132]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_48_in_0, int32), [198]), [1]), [13068]), SigmoidLUTTable)), [8]), [254]), [14]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 6.185 Q15 -> (uint8-23) 1.556 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(132))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_48_in_0[i0])*(198)), ((unsigned char)1))-(13068)), SigmoidLUTTable)), (8))*(254)), ((unsigned char)14))-(-23))), (((signed char)8))));
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
    // Max shape: (8, 8, 104) var shapes:
    // expr_49_out_0: (8, 8, 104) expr_49_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-122) 5.895 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [122]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_49_in_0, int32), [189]), [1]), [11529]), SigmoidLUTTable)), [8]), [235]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 5.895 Q15 -> (uint8-22) 1.606 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(122))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_49_in_0[i0])*(189)), ((unsigned char)1))-(11529)), SigmoidLUTTable)), (8))*(235)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (8, 8, 52) var shapes:
    // expr_50_out_0: (8, 8, 52) expr_50_in_0: (8, 8, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-121) 5.273 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [121]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_50_in_0, int32), [169]), [1]), [10225]), SigmoidLUTTable)), [8]), [234]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.273 Q15 -> (uint8-25) 1.442 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(121))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_50_in_0[i0])*(169)), ((unsigned char)1))-(10225)), SigmoidLUTTable)), (8))*(234)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (8, 8, 104) var shapes:
    // expr_52_out_0: (8, 8, 104) expr_52_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_52_in_0: (uint8-120) 5.532 Q8
        // expr_52_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_52_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_52_in_0, int32), [177]), [1]), [10620]), SigmoidLUTTable)), [8]), [231]), [14]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 5.532 Q15 -> (uint8-23) 1.533 Q7
        expr_52_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_52_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_52_in_0[i0])*(177)), ((unsigned char)1))-(10620)), SigmoidLUTTable)), (8))*(231)), ((unsigned char)14))-(-23))), (((signed char)8))));
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
    // Max shape: (8, 8, 52) var shapes:
    // expr_53_out_0: (8, 8, 52) expr_53_in_0: (8, 8, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-106) 6.411 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [106]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_53_in_0, int32), [205]), [1]), [10865]), SigmoidLUTTable)), [8]), [209]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 6.411 Q15 -> (uint8-18) 1.964 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(106))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_53_in_0[i0])*(205)), ((unsigned char)1))-(10865)), SigmoidLUTTable)), (8))*(209)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (8, 8, 104) var shapes:
    // expr_55_out_0: (8, 8, 104) expr_55_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-126) 7.505 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [126]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_55_in_0, int32), [240]), [1]), [15120]), SigmoidLUTTable)), [8]), [241]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.505 Q15 -> (uint8-18) 1.990 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_55_in_0[i0])-(126))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_55_in_0[i0])*(240)), ((unsigned char)1))-(15120)), SigmoidLUTTable)), (8))*(241)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_56_out_0: (8, 8, 56) expr_56_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-110) 4.907 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [110]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_56_in_0, int32), [157]), [1]), [8635]), SigmoidLUTTable)), [8]), [216]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 4.907 Q15 -> (uint8-25) 1.453 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(110))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_56_in_0[i0])*(157)), ((unsigned char)1))-(8635)), SigmoidLUTTable)), (8))*(216)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (16, 16, 56) var shapes:
    // expr_10_out_0: (16, 16, 56) expr_10_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-124) 5.969 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [124]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_10_in_0, int32), [191]), [1]), [11842]), SigmoidLUTTable)), [8]), [239]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 5.969 Q15 -> (uint8-22) 1.599 Q7
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_10_in_0[i0])-(124))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_10_in_0[i0])*(191)), ((unsigned char)1))-(11842)), SigmoidLUTTable)), (8))*(239)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (16, 16, 28) var shapes:
    // expr_8_out_0: (16, 16, 28) expr_8_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_8_in_0: (uint8-124) 5.719 Q8
        // expr_8_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_8_in_0, int32), [124]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_8_in_0, int32), [183]), [1]), [11346]), SigmoidLUTTable)), [8]), [239]), [14]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 5.719 Q15 -> (uint8-23) 1.529 Q7
        expr_8_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_8_in_0[i0])-(124))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_8_in_0[i0])*(183)), ((unsigned char)1))-(11346)), SigmoidLUTTable)), (8))*(239)), ((unsigned char)14))-(-23))), (((signed char)8))));
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
    // Max shape: (16, 16, 28) var shapes:
    // expr_9_out_0: (16, 16, 28) expr_9_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-132) 5.492 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [132]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_9_in_0, int32), [176]), [1]), [11616]), SigmoidLUTTable)), [8]), [220]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 5.492 Q15 -> (uint8-22) 3.202 Q8
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(132))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_9_in_0[i0])*(176)), ((unsigned char)1))-(11616)), SigmoidLUTTable)), (8))*(220)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (16, 16, 56) var shapes:
    // expr_11_out_0: (16, 16, 56) expr_11_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-110) 6.119 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [110]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_11_in_0, int32), [196]), [1]), [10780]), SigmoidLUTTable)), [8]), [215]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.119 Q15 -> (uint8-20) 1.824 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(110))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_11_in_0[i0])*(196)), ((unsigned char)1))-(10780)), SigmoidLUTTable)), (8))*(215)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (16, 16, 32) var shapes:
    // expr_12_out_0: (16, 16, 32) expr_12_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-138) 5.477 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [138]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_12_in_0, int32), [175]), [1]), [12075]), SigmoidLUTTable)), [8]), [135]), [13]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 5.477 Q15 -> (uint8-28) 1.295 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_12_in_0[i0])-(138))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_12_in_0[i0])*(175)), ((unsigned char)1))-(12075)), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-28))), (((signed char)8))));
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
    // Max shape: (32, 32, 32) var shapes:
    // expr_14_out_0: (32, 32, 32) expr_14_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-135) 5.031 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [135]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_14_in_0, int32), [161]), [1]), [10868]), SigmoidLUTTable)), [8]), [132]), [13]), [-29]), 0, 255), uint8)
        // scale clip and cast - int32 5.031 Q15 -> (uint8-29) 1.216 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_14_in_0[i0])-(135))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_14_in_0[i0])*(161)), ((unsigned char)1))-(10868)), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-29))), (((signed char)8))));
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
    // Max shape: (32, 32, 16) var shapes:
    // expr_15_out_0: (32, 32, 16) expr_15_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_15_in_0: (uint8-120) 4.934 Q8
        // expr_15_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_15_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_15_in_0, int32), [158]), [1]), [9480]), SigmoidLUTTable)), [8]), [234]), [14]), [-26]), 0, 255), uint8)
        // scale clip and cast - int32 4.934 Q15 -> (uint8-26) 1.352 Q7
        expr_15_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_15_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_15_in_0[i0])*(158)), ((unsigned char)1))-(9480)), SigmoidLUTTable)), (8))*(234)), ((unsigned char)14))-(-26))), (((signed char)8))));
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
    // Max shape: (32, 32, 16) var shapes:
    // expr_16_out_0: (32, 32, 16) expr_16_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-116) 6.304 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_16_in_0, int32), [202]), [1]), [11716]), SigmoidLUTTable)), [8]), [224]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.304 Q15 -> (uint8-20) 1.804 Q7
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_16_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_16_in_0[i0])*(202)), ((unsigned char)1))-(11716)), SigmoidLUTTable)), (8))*(224)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (32, 32, 32) var shapes:
    // expr_18_out_0: (32, 32, 32) expr_18_in_0: (32, 32, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-136) 8.109 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [136]), SigmoidLUT(Sub(Mul(Cast(expr_18_in_0, int32), [130]), [17680]), SigmoidLUTTable)), [8]), [130]), [13]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 8.109 Q15 -> (uint8-18) 1.990 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(136))*SigmoidTableInline(((((int)expr_18_in_0[i0])*(130))-(17680)), SigmoidLUTTable)), (8))*(130)), ((unsigned char)13))-(-18))), (((signed char)8))));
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
    // Max shape: (16, 16, 32) var shapes:
    // expr_19_out_0: (16, 16, 32) expr_19_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-114) 7.392 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [114]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_19_in_0, int32), [237]), [1]), [13509]), SigmoidLUTTable)), [8]), [220]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.392 Q15 -> (uint8-17) 2.155 Q7
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(114))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_19_in_0[i0])*(237)), ((unsigned char)1))-(13509)), SigmoidLUTTable)), (8))*(220)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (16, 16, 56) var shapes:
    // expr_20_out_0: (16, 16, 56) expr_20_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-117) 5.897 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_20_in_0, int32), [117]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_20_in_0, int32), [189]), [1]), [11057]), SigmoidLUTTable)), [8]), [226]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 5.897 Q15 -> (uint8-21) 1.672 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_20_in_0[i0])-(117))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_20_in_0[i0])*(189)), ((unsigned char)1))-(11057)), SigmoidLUTTable)), (8))*(226)), ((unsigned char)14))-(-21))), (((signed char)8))));
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
    // Max shape: (16, 16, 28) var shapes:
    // expr_21_out_0: (16, 16, 28) expr_21_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-127) 5.751 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [127]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_21_in_0, int32), [184]), [1]), [11684]), SigmoidLUTTable)), [8]), [244]), [14]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 5.751 Q15 -> (uint8-24) 1.507 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(127))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_21_in_0[i0])*(184)), ((unsigned char)1))-(11684)), SigmoidLUTTable)), (8))*(244)), ((unsigned char)14))-(-24))), (((signed char)8))));
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
    // Max shape: (16, 16, 28) var shapes:
    // expr_22_out_0: (16, 16, 28) expr_22_in_0: (16, 16, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-115) 5.263 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [115]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_22_in_0, int32), [168]), [1]), [9660]), SigmoidLUTTable)), [8]), [201]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 5.263 Q15 -> (uint8-22) 3.352 Q8
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_22_in_0[i0])-(115))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_22_in_0[i0])*(168)), ((unsigned char)1))-(9660)), SigmoidLUTTable)), (8))*(201)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (16, 16, 56) var shapes:
    // expr_24_out_0: (16, 16, 56) expr_24_in_0: (16, 16, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_24_in_0: (uint8-121) 7.197 Q8
        // expr_24_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_24_in_0, int32), [121]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_24_in_0, int32), [230]), [1]), [13915]), SigmoidLUTTable)), [8]), [231]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.197 Q15 -> (uint8-18) 1.990 Q7
        expr_24_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_24_in_0[i0])-(121))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_24_in_0[i0])*(230)), ((unsigned char)1))-(13915)), SigmoidLUTTable)), (8))*(231)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_25_out_0: (8, 8, 56) expr_25_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-90) 6.443 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [90]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_25_in_0, int32), [206]), [1]), [9270]), SigmoidLUTTable)), [8]), [188]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 6.443 Q15 -> (uint8-17) 4.392 Q8
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(90))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_25_in_0[i0])*(206)), ((unsigned char)1))-(9270)), SigmoidLUTTable)), (8))*(188)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (8, 8, 104) var shapes:
    // expr_26_out_0: (8, 8, 104) expr_26_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-116) 6.759 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_26_in_0, int32), [216]), [1]), [12528]), SigmoidLUTTable)), [8]), [224]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 6.759 Q15 -> (uint8-18) 1.929 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_26_in_0[i0])*(216)), ((unsigned char)1))-(12528)), SigmoidLUTTable)), (8))*(224)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (8, 8, 52) var shapes:
    // expr_27_out_0: (8, 8, 52) expr_27_in_0: (8, 8, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-119) 9.121 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [119]), SigmoidLUT(Sub(Mul(Cast(expr_27_in_0, int32), [146]), [17374]), SigmoidLUTTable)), [8]), [228]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 9.121 Q15 -> (uint8-14) 2.560 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_27_in_0[i0])-(119))*SigmoidTableInline(((((int)expr_27_in_0[i0])*(146))-(17374)), SigmoidLUTTable)), (8))*(228)), ((unsigned char)14))-(-14))), (((signed char)8))));
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
    // Max shape: (8, 8, 52) var shapes:
    // expr_28_out_0: (8, 8, 52) expr_28_in_0: (8, 8, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-102) 6.081 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [102]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_28_in_0, int32), [195]), [1]), [9945]), SigmoidLUTTable)), [8]), [201]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 6.081 Q15 -> (uint8-19) 3.873 Q8
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(102))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_28_in_0[i0])*(195)), ((unsigned char)1))-(9945)), SigmoidLUTTable)), (8))*(201)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (8, 8, 104) var shapes:
    // expr_30_out_0: (8, 8, 104) expr_30_in_0: (8, 8, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-137) 5.408 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [137]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_30_in_0, int32), [173]), [1]), [11851]), SigmoidLUTTable)), [8]), [134]), [13]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 5.408 Q15 -> (uint8-28) 1.294 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_30_in_0[i0])-(137))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_30_in_0[i0])*(173)), ((unsigned char)1))-(11851)), SigmoidLUTTable)), (8))*(134)), ((unsigned char)13))-(-28))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop