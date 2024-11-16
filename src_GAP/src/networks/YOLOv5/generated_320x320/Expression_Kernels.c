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
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (80, 80, 8) (uint8-131) 11.084 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (80, 80, 8) (uint8-3) 25.144 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (80, 80, 8) (uint8-5) 25.382 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (80, 80, 8) var shapes:
    // expr_0_out_0: (80, 80, 8) expr_0_in_1: (80, 80, 8) expr_0_in_0: (80, 80,
    // 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-3) 25.144 Q8 expr_0_in_0: (uint8-131)
        // 11.084 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [131]), SigmoidLUT(Sub(Mul(Cast(expr_0_in_0, int32), [177]), [23187]), SigmoidLUTTable)), [8]), [226]), [16])), [254]), [8]), [-2]), 0, 255), uint8)
        // ADD_0_16 scale arg 0 (no zp adj) - (uint8-3) 25.144 Q8 -> (int32-3) 25.144 Q8
        int _SYMBOL_Cast251 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-3) 50.287 Q9 -> (uint8-5) 25.382 Q8
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast251+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(131))*SigmoidTableInline(((((int)expr_0_in_0[i0])*(177))-(23187)), SigmoidLUTTable)), (8))*(226)), ((unsigned char)16)))*(254)), ((unsigned char)8))-(-2))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s186_kernel(s186_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (1, 100, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (1, 100, 1, 2) int8 8.567 Q7
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (1, 1, 1, 2)   int8 0.003 Q7
    unsigned char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (1, 100, 3, 2) (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 100, 3, 2) var shapes:
    // expr_1_out_0: (1, 100, 3, 2) expr_1_in_0: (1, 100, 3, 2) expr_1_in_1:
    // (1, 100, 1, 2) expr_1_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_1_in_0: (uint8-128) 12.578 Q8 expr_1_in_1: int8
            // 8.567 Q7 expr_1_in_2: int8 0.003 Q7
            // expr_1_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_1_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_1_in_1, int32), [137]), [3])), [1]), [1]), Cast(expr_1_in_2, int32)), [205]), [24]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.403 Q15 -> (uint8-128) 2.016 Q8
            expr_1_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_1_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_1_in_1[i2])*(137))<<((unsigned char)3)))*(1)), (1))*((int)expr_1_in_2[i2]))*(205)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (1, 400, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (1, 400, 1, 2) int8 18.646 Q7
    signed char *__restrict__  expr_2_in_2 = Args->expr_2_in_2; // (1, 1, 1, 2)   int8 0.003 Q7
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (1, 400, 3, 2) (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 400, 3, 2) var shapes:
    // expr_2_out_0: (1, 400, 3, 2) expr_2_in_0: (1, 400, 3, 2) expr_2_in_1:
    // (1, 400, 1, 2) expr_2_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_2_in_0: (uint8-128) 12.578 Q8 expr_2_in_1: int8
            // 18.646 Q7 expr_2_in_2: int8 0.003 Q7
            // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_2_in_1, int32), [149]), [4])), [1]), [1]), Cast(expr_2_in_2, int32)), [205]), [25]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.202 Q15 -> (uint8-128) 2.016 Q8
            expr_2_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_2_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_2_in_1[i2])*(149))<<((unsigned char)4)))*(1)), (1))*((int)expr_2_in_2[i2]))*(205)), ((unsigned char)25))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (1, 1600, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (1, 1600, 1, 2) int8 38.803 Q7
    signed char *__restrict__  expr_3_in_2 = Args->expr_3_in_2; // (1, 1, 1, 2)    int8 0.003 Q7
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (1, 1600, 3, 2) (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 1600, 3, 2) var shapes:
    // expr_3_out_0: (1, 1600, 3, 2) expr_3_in_0: (1, 1600, 3, 2) expr_3_in_1:
    // (1, 1600, 1, 2) expr_3_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1,
    // 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_3_in_0: (uint8-128) 12.578 Q8 expr_3_in_1: int8
            // 38.803 Q7 expr_3_in_2: int8 0.003 Q7
            // expr_3_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_3_in_1, int32), [155]), [5])), [1]), [1]), Cast(expr_3_in_2, int32)), [205]), [26]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.101 Q15 -> (uint8-128) 2.016 Q8
            expr_3_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_3_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_3_in_1[i2])*(155))<<((unsigned char)5)))*(1)), (1))*((int)expr_3_in_2[i2]))*(205)), ((unsigned char)26))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (40, 40, 16) (uint8-120) 8.321 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (40, 40, 16) (uint8-15) 4.670 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (40, 40, 16) (uint8-24) 2.998 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (40, 40, 16) var shapes:
    // expr_4_out_0: (40, 40, 16) expr_4_in_1: (40, 40, 16) expr_4_in_0: (40,
    // 40, 16) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-15) 4.670 Q8 expr_4_in_0: (uint8-120)
        // 8.321 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_4_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_4_in_0, int32), [120]), SigmoidLUT(Sub(Mul(Cast(expr_4_in_0, int32), [133]), [15960]), SigmoidLUTTable)), [8]), [228]), [14])), [199]), [8]), [-12]), 0, 255), uint8)
        // ADD_0_37 scale arg 0 (no zp adj) - (uint8-15) 4.670 Q8 -> (int32-15) 4.670 Q8
        int _SYMBOL_Cast28 = ((int)expr_4_in_1[i0]);
        // scale clip and cast - (int32-15) 9.340 Q9 -> (uint8-24) 2.998 Q7
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast28+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(120))*SigmoidTableInline(((((int)expr_4_in_0[i0])*(133))-(15960)), SigmoidLUTTable)), (8))*(228)), ((unsigned char)14)))*(199)), ((unsigned char)8))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s57_kernel(s57_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0; // (20, 20, 28) (uint8-116) 7.636 Q8
    unsigned char *__restrict__  expr_5_in_1 = Args->expr_5_in_1; // (20, 20, 28) (uint8-20) 3.525 Q8
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (20, 20, 28) (uint8-26) 2.729 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (20, 20, 28) var shapes:
    // expr_5_out_0: (20, 20, 28) expr_5_in_1: (20, 20, 28) expr_5_in_0: (20,
    // 20, 28) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_1: (uint8-20) 3.525 Q8 expr_5_in_0: (uint8-116)
        // 7.636 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_5_in_1, int32), [236]), [2]), Norm(Mul(Sub(Cast(expr_5_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_5_in_0, int32), [244]), [1]), [14152]), SigmoidLUTTable)), [8])), [179]), [14]), [-13]), 0, 255), uint8)
        // scale clip and cast - (int32-1180) 977.454 Q22 -> (uint8-26) 2.729 Q7
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_5_in_1[i0])*(236)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_5_in_0[i0])*(244)), ((unsigned char)1))-(14152)), SigmoidLUTTable)), (8)))*(179)), ((unsigned char)14))-(-13))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s77_kernel(s77_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0; // (10, 10, 52) (uint8-98) 6.119 Q8
    unsigned char *__restrict__  expr_6_in_1 = Args->expr_6_in_1; // (10, 10, 52) (uint8-16) 4.378 Q8
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (10, 10, 52) (uint8-28) 2.548 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (10, 10, 52) var shapes:
    // expr_6_out_0: (10, 10, 52) expr_6_in_1: (10, 10, 52) expr_6_in_0: (10,
    // 10, 52) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_1: (uint8-16) 4.378 Q8 expr_6_in_0: (uint8-98)
        // 6.119 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_6_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_6_in_0, int32), [98]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_6_in_0, int32), [196]), [1]), [9604]), SigmoidLUTTable)), [8]), [179]), [14])), [220]), [8]), [-14]), 0, 255), uint8)
        // ADD_0_79 scale arg 0 (no zp adj) - (uint8-16) 4.378 Q8 -> (int32-16) 4.378 Q8
        int _SYMBOL_Cast60 = ((int)expr_6_in_1[i0]);
        // scale clip and cast - (int32-16) 8.756 Q9 -> (uint8-28) 2.548 Q7
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast60+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_6_in_0[i0])-(98))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_6_in_0[i0])*(196)), ((unsigned char)1))-(9604)), SigmoidLUTTable)), (8))*(179)), ((unsigned char)14)))*(220)), ((unsigned char)8))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s207_kernel(s207_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0; // (1, 100, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_32_in_1 = Args->expr_32_in_1; // (1, 1, 3, 2)   int8 1503.748 Q7
    signed char *__restrict__  expr_32_in_2 = Args->expr_32_in_2; // (1, 1, 1, 2)   int8 0.003 Q7
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 100, 3, 2) (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 100, 3, 2) var shapes:
    // inter_LOGISTIC_0_190: (1, 100, 3, 2) expr_32_in_0: (1, 100, 3, 2)
    // expr_32_out_0: (1, 100, 3, 2) expr_32_in_1: (1, 1, 3, 2) expr_32_in_2:
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
            // 1503.748 Q7 expr_32_in_2: int8 0.003 Q7
            // expr_32_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_190), Cast(expr_32_in_1, int32)), [7]), Cast(expr_32_in_2, int32)), [150]), [20]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_190 = inter_LOGISTIC_0_190;
            // scale clip and cast - int32 4.736 Q15 -> (uint8-128) 2.016 Q8
            expr_32_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_190)*((int)expr_32_in_1[(i1*I2)+i2])), (7))*((int)expr_32_in_2[i2]))*(150)), ((unsigned char)20))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_34_in_0 = Args->expr_34_in_0; // (1, 400, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_34_in_1 = Args->expr_34_in_1; // (1, 1, 3, 2)   int8 479.748 Q7
    signed char *__restrict__  expr_34_in_2 = Args->expr_34_in_2; // (1, 1, 1, 2)   int8 0.003 Q7
    unsigned char *__restrict__  expr_34_out_0 = Args->expr_34_out_0; // (1, 400, 3, 2) (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 400, 3, 2) var shapes:
    // inter_LOGISTIC_0_207: (1, 400, 3, 2) expr_34_in_0: (1, 400, 3, 2)
    // expr_34_out_0: (1, 400, 3, 2) expr_34_in_1: (1, 1, 3, 2) expr_34_in_2:
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
            // 479.748 Q7 expr_34_in_2: int8 0.003 Q7
            // expr_34_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_207), Cast(expr_34_in_1, int32)), [7]), Cast(expr_34_in_2, int32)), [192]), [22]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_207 = inter_LOGISTIC_0_207;
            // scale clip and cast - int32 1.511 Q15 -> (uint8-128) 2.016 Q8
            expr_34_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_207)*((int)expr_34_in_1[(i1*I2)+i2])), (7))*((int)expr_34_in_2[i2]))*(192)), ((unsigned char)22))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0; // (1, 1600, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_35_in_1 = Args->expr_35_in_1; // (1, 1, 3, 2)    int8 133.039 Q7
    signed char *__restrict__  expr_35_in_2 = Args->expr_35_in_2; // (1, 1, 1, 2)    int8 0.003 Q7
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 1600, 3, 2) (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 1600, 3, 2) var shapes:
    // inter_LOGISTIC_0_224: (1, 1600, 3, 2) expr_35_in_0: (1, 1600, 3, 2)
    // expr_35_out_0: (1, 1600, 3, 2) expr_35_in_1: (1, 1, 3, 2) expr_35_in_2:
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
            // 133.039 Q7 expr_35_in_2: int8 0.003 Q7
            // expr_35_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_224), Cast(expr_35_in_1, int32)), [7]), Cast(expr_35_in_2, int32)), [213]), [24]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_224 = inter_LOGISTIC_0_224;
            // scale clip and cast - int32 0.419 Q15 -> (uint8-128) 2.016 Q8
            expr_35_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_224)*((int)expr_35_in_1[(i1*I2)+i2])), (7))*((int)expr_35_in_2[i2]))*(213)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    // Max shape: (160, 160, 8) var shapes:
    // expr_33_out_0: (160, 160, 8) expr_33_in_0: (160, 160, 8)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-119) 32.882 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [119]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_33_in_0, int32), [132]), [2]), [62832]), -65536, 65535), SigmoidLUTTable)), [8]), [237]), [14]), [-4]), 0, 255), uint8)
        // scale clip and cast - int32 32.882 Q15 -> (uint8-4) 8.882 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(119))*SigmoidTableInline(gap_clip(((((((int)expr_33_in_0[i0])*(132))<<((unsigned char)2))-(62832))), (((signed char)16))), SigmoidLUTTable)), (8))*(237)), ((unsigned char)14))-(-4))), (((signed char)8))));
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
    // Max shape: (80, 80, 16) var shapes:
    // expr_45_out_0: (80, 80, 16) expr_45_in_0: (80, 80, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-121) 29.264 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [121]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [234]), [1]), [56628]), SigmoidLUTTable)), [8]), [239]), [14]), [-5]), 0, 255), uint8)
        // scale clip and cast - int32 29.264 Q15 -> (uint8-5) 7.844 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(121))*SigmoidTableInline((((((int)expr_45_in_0[i0])*(234))<<((unsigned char)1))-(56628)), SigmoidLUTTable)), (8))*(239)), ((unsigned char)14))-(-5))), (((signed char)8))));
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
    // Max shape: (80, 80, 16) var shapes:
    // expr_31_out_0: (80, 80, 16) expr_31_in_0: (80, 80, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-100) 40.969 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [100]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [164]), [2]), [65600]), -65536, 65535), SigmoidLUTTable)), [8]), [209]), [14]), [-3]), 0, 255), uint8)
        // scale clip and cast - int32 40.969 Q15 -> (uint8-3) 12.572 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(100))*SigmoidTableInline(gap_clip(((((((int)expr_31_in_0[i0])*(164))<<((unsigned char)2))-(65600))), (((signed char)16))), SigmoidLUTTable)), (8))*(209)), ((unsigned char)14))-(-3))), (((signed char)8))));
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
    // Max shape: (80, 80, 8) var shapes:
    // expr_13_out_0: (80, 80, 8) expr_13_in_0: (80, 80, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-177) 11.780 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [177]), SigmoidLUT(Sub(Mul(Cast(expr_13_in_0, int32), [188]), [33276]), SigmoidLUTTable)), [8]), [198]), [13]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 11.780 Q15 -> (uint8-19) 1.905 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(177))*SigmoidTableInline(((((int)expr_13_in_0[i0])*(188))-(33276)), SigmoidLUTTable)), (8))*(198)), ((unsigned char)13))-(-19))), (((signed char)8))));
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
    // Max shape: (80, 80, 16) var shapes:
    // expr_36_out_0: (80, 80, 16) expr_36_in_0: (80, 80, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-170) 26.226 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [170]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_36_in_0, int32), [210]), [1]), [71400]), -65536, 65535), SigmoidLUTTable)), [8]), [185]), [13]), [-8]), 0, 255), uint8)
        // scale clip and cast - int32 26.226 Q15 -> (uint8-8) 4.533 Q7
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(170))*SigmoidTableInline(gap_clip(((((((int)expr_36_in_0[i0])*(210))<<((unsigned char)1))-(71400))), (((signed char)16))), SigmoidLUTTable)), (8))*(185)), ((unsigned char)13))-(-8))), (((signed char)8))));
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
    // Max shape: (40, 40, 32) var shapes:
    // expr_37_out_0: (40, 40, 32) expr_37_in_0: (40, 40, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-147) 9.258 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [147]), SigmoidLUT(Sub(Mul(Cast(expr_37_in_0, int32), [148]), [21756]), SigmoidLUTTable)), [8]), [144]), [13]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 9.258 Q15 -> (uint8-17) 2.059 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(147))*SigmoidTableInline(((((int)expr_37_in_0[i0])*(148))-(21756)), SigmoidLUTTable)), (8))*(144)), ((unsigned char)13))-(-17))), (((signed char)8))));
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
    // Max shape: (40, 40, 32) var shapes:
    // expr_38_out_0: (40, 40, 32) expr_38_in_0: (40, 40, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-126) 8.790 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_38_in_0, int32), [141]), [17766]), SigmoidLUTTable)), [8]), [241]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 8.790 Q15 -> (uint8-15) 2.335 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(126))*SigmoidTableInline(((((int)expr_38_in_0[i0])*(141))-(17766)), SigmoidLUTTable)), (8))*(241)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (40, 40, 16) var shapes:
    // expr_39_out_0: (40, 40, 16) expr_39_in_0: (40, 40, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-118) 7.465 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [118]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_39_in_0, int32), [239]), [1]), [14101]), SigmoidLUTTable)), [8]), [227]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.465 Q15 -> (uint8-17) 2.107 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(118))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_39_in_0[i0])*(239)), ((unsigned char)1))-(14101)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (40, 40, 32) var shapes:
    // expr_41_out_0: (40, 40, 32) expr_41_in_0: (40, 40, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-133) 6.288 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [133]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_41_in_0, int32), [201]), [1]), [13367]), SigmoidLUTTable)), [8]), [128]), [13]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 6.288 Q15 -> (uint8-23) 1.570 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(133))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_41_in_0[i0])*(201)), ((unsigned char)1))-(13367)), SigmoidLUTTable)), (8))*(128)), ((unsigned char)13))-(-23))), (((signed char)8))));
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
    // Max shape: (20, 20, 56) var shapes:
    // expr_42_out_0: (20, 20, 56) expr_42_in_0: (20, 20, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-122) 6.626 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [122]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_42_in_0, int32), [212]), [1]), [12932]), SigmoidLUTTable)), [8]), [233]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.626 Q15 -> (uint8-20) 1.821 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(122))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_42_in_0[i0])*(212)), ((unsigned char)1))-(12932)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (20, 20, 56) var shapes:
    // expr_43_out_0: (20, 20, 56) expr_43_in_0: (20, 20, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-127) 6.692 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [127]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_43_in_0, int32), [214]), [1]), [13589]), SigmoidLUTTable)), [8]), [243]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.692 Q15 -> (uint8-20) 1.762 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(127))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_43_in_0[i0])*(214)), ((unsigned char)1))-(13589)), SigmoidLUTTable)), (8))*(243)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (20, 20, 28) var shapes:
    // expr_44_out_0: (20, 20, 28) expr_44_in_0: (20, 20, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-134) 6.685 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [134]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_44_in_0, int32), [214]), [1]), [14338]), SigmoidLUTTable)), [8]), [128]), [13]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 6.685 Q15 -> (uint8-21) 1.665 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(134))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_44_in_0[i0])*(214)), ((unsigned char)1))-(14338)), SigmoidLUTTable)), (8))*(128)), ((unsigned char)13))-(-21))), (((signed char)8))));
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
    // Max shape: (20, 20, 56) var shapes:
    // expr_47_out_0: (20, 20, 56) expr_47_in_0: (20, 20, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_47_in_0: (uint8-125) 7.224 Q8
        // expr_47_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_47_in_0, int32), [125]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_47_in_0, int32), [231]), [1]), [14438]), SigmoidLUTTable)), [8]), [239]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.224 Q15 -> (uint8-18) 1.938 Q7
        expr_47_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_47_in_0[i0])-(125))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_47_in_0[i0])*(231)), ((unsigned char)1))-(14438)), SigmoidLUTTable)), (8))*(239)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (10, 10, 104) var shapes:
    // expr_48_out_0: (10, 10, 104) expr_48_in_0: (10, 10, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-109) 7.005 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [109]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_48_in_0, int32), [224]), [1]), [12208]), SigmoidLUTTable)), [8]), [213]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.005 Q15 -> (uint8-17) 2.108 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(109))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_48_in_0[i0])*(224)), ((unsigned char)1))-(12208)), SigmoidLUTTable)), (8))*(213)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (10, 10, 104) var shapes:
    // expr_49_out_0: (10, 10, 104) expr_49_in_0: (10, 10, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-126) 8.227 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_49_in_0, int32), [132]), [16632]), SigmoidLUTTable)), [8]), [241]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.227 Q15 -> (uint8-16) 2.189 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(126))*SigmoidTableInline(((((int)expr_49_in_0[i0])*(132))-(16632)), SigmoidLUTTable)), (8))*(241)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (10, 10, 52) var shapes:
    // expr_50_out_0: (10, 10, 52) expr_50_in_0: (10, 10, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-123) 5.370 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_50_in_0, int32), [172]), [1]), [10578]), SigmoidLUTTable)), [8]), [237]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.370 Q15 -> (uint8-25) 1.452 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_50_in_0[i0])*(172)), ((unsigned char)1))-(10578)), SigmoidLUTTable)), (8))*(237)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (10, 10, 104) var shapes:
    // expr_52_out_0: (10, 10, 104) expr_52_in_0: (10, 10, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_52_in_0: (uint8-128) 6.288 Q8
        // expr_52_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_52_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_52_in_0, int32), [201]), [1]), [12864]), SigmoidLUTTable)), [8]), [246]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 6.288 Q15 -> (uint8-22) 1.636 Q7
        expr_52_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_52_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_52_in_0[i0])*(201)), ((unsigned char)1))-(12864)), SigmoidLUTTable)), (8))*(246)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (10, 10, 52) var shapes:
    // expr_53_out_0: (10, 10, 52) expr_53_in_0: (10, 10, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-105) 5.885 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [105]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_53_in_0, int32), [188]), [1]), [9870]), SigmoidLUTTable)), [8]), [207]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 5.885 Q15 -> (uint8-20) 1.820 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(105))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_53_in_0[i0])*(188)), ((unsigned char)1))-(9870)), SigmoidLUTTable)), (8))*(207)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (10, 10, 104) var shapes:
    // expr_55_out_0: (10, 10, 104) expr_55_in_0: (10, 10, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-128) 6.376 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_55_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_55_in_0, int32), [204]), [1]), [13056]), SigmoidLUTTable)), [8]), [245]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 6.376 Q15 -> (uint8-21) 1.664 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_55_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_55_in_0[i0])*(204)), ((unsigned char)1))-(13056)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-21))), (((signed char)8))));
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
    // Max shape: (10, 10, 56) var shapes:
    // expr_56_out_0: (10, 10, 56) expr_56_in_0: (10, 10, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-137) 5.785 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [137]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_56_in_0, int32), [185]), [1]), [12673]), SigmoidLUTTable)), [8]), [133]), [13]), [-26]), 0, 255), uint8)
        // scale clip and cast - int32 5.785 Q15 -> (uint8-26) 1.396 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(137))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_56_in_0[i0])*(185)), ((unsigned char)1))-(12673)), SigmoidLUTTable)), (8))*(133)), ((unsigned char)13))-(-26))), (((signed char)8))));
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
    // Max shape: (20, 20, 56) var shapes:
    // expr_10_out_0: (20, 20, 56) expr_10_in_0: (20, 20, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-136) 6.171 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [136]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_10_in_0, int32), [197]), [1]), [13396]), SigmoidLUTTable)), [8]), [131]), [13]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 6.171 Q15 -> (uint8-24) 1.502 Q7
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_10_in_0[i0])-(136))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_10_in_0[i0])*(197)), ((unsigned char)1))-(13396)), SigmoidLUTTable)), (8))*(131)), ((unsigned char)13))-(-24))), (((signed char)8))));
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
    // Max shape: (20, 20, 28) var shapes:
    // expr_8_out_0: (20, 20, 28) expr_8_in_0: (20, 20, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_8_in_0: (uint8-122) 7.262 Q8
        // expr_8_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_8_in_0, int32), [122]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_8_in_0, int32), [232]), [1]), [14152]), SigmoidLUTTable)), [8]), [234]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.262 Q15 -> (uint8-18) 1.983 Q7
        expr_8_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_8_in_0[i0])-(122))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_8_in_0[i0])*(232)), ((unsigned char)1))-(14152)), SigmoidLUTTable)), (8))*(234)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (20, 20, 28) var shapes:
    // expr_9_out_0: (20, 20, 28) expr_9_in_0: (20, 20, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-136) 7.933 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [136]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_9_in_0, int32), [254]), [1]), [17272]), SigmoidLUTTable)), [8]), [131]), [13]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 7.933 Q15 -> (uint8-19) 3.887 Q8
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(136))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_9_in_0[i0])*(254)), ((unsigned char)1))-(17272)), SigmoidLUTTable)), (8))*(131)), ((unsigned char)13))-(-19))), (((signed char)8))));
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
    // Max shape: (20, 20, 56) var shapes:
    // expr_11_out_0: (20, 20, 56) expr_11_in_0: (20, 20, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-125) 6.961 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [125]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_11_in_0, int32), [223]), [1]), [13938]), SigmoidLUTTable)), [8]), [238]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 6.961 Q15 -> (uint8-19) 1.869 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(125))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_11_in_0[i0])*(223)), ((unsigned char)1))-(13938)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (20, 20, 32) var shapes:
    // expr_12_out_0: (20, 20, 32) expr_12_in_0: (20, 20, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-91) 5.880 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [91]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_12_in_0, int32), [188]), [1]), [8554]), SigmoidLUTTable)), [8]), [189]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 5.880 Q15 -> (uint8-18) 1.992 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_12_in_0[i0])-(91))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_12_in_0[i0])*(188)), ((unsigned char)1))-(8554)), SigmoidLUTTable)), (8))*(189)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (40, 40, 32) var shapes:
    // expr_14_out_0: (40, 40, 32) expr_14_in_0: (40, 40, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-128) 5.187 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_14_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_14_in_0, int32), [166]), [1]), [10624]), SigmoidLUTTable)), [8]), [248]), [14]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 5.187 Q15 -> (uint8-27) 1.341 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_14_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_14_in_0[i0])*(166)), ((unsigned char)1))-(10624)), SigmoidLUTTable)), (8))*(248)), ((unsigned char)14))-(-27))), (((signed char)8))));
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
    // Max shape: (40, 40, 16) var shapes:
    // expr_15_out_0: (40, 40, 16) expr_15_in_0: (40, 40, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_15_in_0: (uint8-141) 6.000 Q8
        // expr_15_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_15_in_0, int32), [141]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_15_in_0, int32), [192]), [1]), [13536]), SigmoidLUTTable)), [8]), [138]), [13]), [-26]), 0, 255), uint8)
        // scale clip and cast - int32 6.000 Q15 -> (uint8-26) 1.390 Q7
        expr_15_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_15_in_0[i0])-(141))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_15_in_0[i0])*(192)), ((unsigned char)1))-(13536)), SigmoidLUTTable)), (8))*(138)), ((unsigned char)13))-(-26))), (((signed char)8))));
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
    // Max shape: (40, 40, 16) var shapes:
    // expr_16_out_0: (40, 40, 16) expr_16_in_0: (40, 40, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-126) 5.589 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [126]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_16_in_0, int32), [179]), [1]), [11277]), SigmoidLUTTable)), [8]), [243]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.589 Q15 -> (uint8-25) 2.948 Q8
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_16_in_0[i0])-(126))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_16_in_0[i0])*(179)), ((unsigned char)1))-(11277)), SigmoidLUTTable)), (8))*(243)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (40, 40, 32) var shapes:
    // expr_18_out_0: (40, 40, 32) expr_18_in_0: (40, 40, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-138) 9.640 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [138]), SigmoidLUT(Sub(Mul(Cast(expr_18_in_0, int32), [154]), [21252]), SigmoidLUTTable)), [8]), [132]), [13]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 9.640 Q15 -> (uint8-15) 2.333 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(138))*SigmoidTableInline(((((int)expr_18_in_0[i0])*(154))-(21252)), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-15))), (((signed char)8))));
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
    // Max shape: (20, 20, 32) var shapes:
    // expr_19_out_0: (20, 20, 32) expr_19_in_0: (20, 20, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-138) 9.848 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [138]), SigmoidLUT(Sub(Mul(Cast(expr_19_in_0, int32), [158]), [21804]), SigmoidLUTTable)), [8]), [133]), [13]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 9.848 Q15 -> (uint8-15) 4.739 Q8
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(138))*SigmoidTableInline(((((int)expr_19_in_0[i0])*(158))-(21804)), SigmoidLUTTable)), (8))*(133)), ((unsigned char)13))-(-15))), (((signed char)8))));
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
    // Max shape: (20, 20, 56) var shapes:
    // expr_20_out_0: (20, 20, 56) expr_20_in_0: (20, 20, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-128) 7.567 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_20_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_20_in_0, int32), [242]), [1]), [15488]), SigmoidLUTTable)), [8]), [245]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.567 Q15 -> (uint8-18) 1.974 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_20_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_20_in_0[i0])*(242)), ((unsigned char)1))-(15488)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (20, 20, 28) var shapes:
    // expr_21_out_0: (20, 20, 28) expr_21_in_0: (20, 20, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-108) 8.317 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [108]), SigmoidLUT(Sub(Mul(Cast(expr_21_in_0, int32), [133]), [14364]), SigmoidLUTTable)), [8]), [212]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 8.317 Q15 -> (uint8-14) 2.511 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(108))*SigmoidTableInline(((((int)expr_21_in_0[i0])*(133))-(14364)), SigmoidLUTTable)), (8))*(212)), ((unsigned char)14))-(-14))), (((signed char)8))));
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
    // Max shape: (20, 20, 28) var shapes:
    // expr_22_out_0: (20, 20, 28) expr_22_in_0: (20, 20, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-139) 8.079 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [139]), SigmoidLUT(Sub(Mul(Cast(expr_22_in_0, int32), [129]), [17931]), SigmoidLUTTable)), [8]), [131]), [13]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 8.079 Q15 -> (uint8-18) 3.948 Q8
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_22_in_0[i0])-(139))*SigmoidTableInline(((((int)expr_22_in_0[i0])*(129))-(17931)), SigmoidLUTTable)), (8))*(131)), ((unsigned char)13))-(-18))), (((signed char)8))));
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
    // Max shape: (20, 20, 56) var shapes:
    // expr_24_out_0: (20, 20, 56) expr_24_in_0: (20, 20, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_24_in_0: (uint8-124) 8.280 Q8
        // expr_24_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_24_in_0, int32), [124]), SigmoidLUT(Sub(Mul(Cast(expr_24_in_0, int32), [132]), [16368]), SigmoidLUTTable)), [8]), [237]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.280 Q15 -> (uint8-16) 2.232 Q7
        expr_24_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_24_in_0[i0])-(124))*SigmoidTableInline(((((int)expr_24_in_0[i0])*(132))-(16368)), SigmoidLUTTable)), (8))*(237)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (10, 10, 56) var shapes:
    // expr_25_out_0: (10, 10, 56) expr_25_in_0: (10, 10, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-109) 7.832 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [109]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_25_in_0, int32), [251]), [1]), [13680]), SigmoidLUTTable)), [8]), [213]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 7.832 Q15 -> (uint8-15) 4.708 Q8
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(109))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_25_in_0[i0])*(251)), ((unsigned char)1))-(13680)), SigmoidLUTTable)), (8))*(213)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (10, 10, 104) var shapes:
    // expr_26_out_0: (10, 10, 104) expr_26_in_0: (10, 10, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-130) 7.768 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [130]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_26_in_0, int32), [249]), [1]), [16185]), SigmoidLUTTable)), [8]), [248]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.768 Q15 -> (uint8-18) 2.006 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(130))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_26_in_0[i0])*(249)), ((unsigned char)1))-(16185)), SigmoidLUTTable)), (8))*(248)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (10, 10, 52) var shapes:
    // expr_27_out_0: (10, 10, 52) expr_27_in_0: (10, 10, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-120) 8.015 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [120]), SigmoidLUT(Sub(Mul(Cast(expr_27_in_0, int32), [128]), [15360]), SigmoidLUTTable)), [8]), [230]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.015 Q15 -> (uint8-16) 2.233 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_27_in_0[i0])-(120))*SigmoidTableInline(((((int)expr_27_in_0[i0])*(128))-(15360)), SigmoidLUTTable)), (8))*(230)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (10, 10, 52) var shapes:
    // expr_28_out_0: (10, 10, 52) expr_28_in_0: (10, 10, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-121) 7.065 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [121]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_28_in_0, int32), [226]), [1]), [13673]), SigmoidLUTTable)), [8]), [225]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.065 Q15 -> (uint8-18) 4.012 Q8
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(121))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_28_in_0[i0])*(226)), ((unsigned char)1))-(13673)), SigmoidLUTTable)), (8))*(225)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (10, 10, 104) var shapes:
    // expr_30_out_0: (10, 10, 104) expr_30_in_0: (10, 10, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-151) 7.286 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [151]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_30_in_0, int32), [233]), [1]), [17592]), SigmoidLUTTable)), [8]), [150]), [13]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 7.286 Q15 -> (uint8-23) 1.552 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_30_in_0[i0])-(151))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_30_in_0[i0])*(233)), ((unsigned char)1))-(17592)), SigmoidLUTTable)), (8))*(150)), ((unsigned char)13))-(-23))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop