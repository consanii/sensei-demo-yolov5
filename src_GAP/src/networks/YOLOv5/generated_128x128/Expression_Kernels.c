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
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (32, 32, 8) (uint8-136) 8.615 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (32, 32, 8) (uint8-9) 7.766 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (32, 32, 8) (uint8-17) 8.040 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (32, 32, 8) var shapes:
    // expr_0_out_0: (32, 32, 8) expr_0_in_1: (32, 32, 8) expr_0_in_0: (32, 32,
    // 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-9) 7.766 Q8 expr_0_in_0: (uint8-136)
        // 8.615 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [136]), SigmoidLUT(Sub(Mul(Cast(expr_0_in_0, int32), [138]), [18768]), SigmoidLUTTable)), [8]), [142]), [14])), [247]), [8]), [-8]), 0, 255), uint8)
        // ADD_0_16 scale arg 0 (no zp adj) - (uint8-9) 7.766 Q8 -> (int32-9) 7.766 Q8
        int _SYMBOL_Cast1075 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-9) 15.531 Q9 -> (uint8-17) 8.040 Q8
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast1075+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(136))*SigmoidTableInline(((((int)expr_0_in_0[i0])*(138))-(18768)), SigmoidLUTTable)), (8))*(142)), ((unsigned char)14)))*(247)), ((unsigned char)8))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s185_kernel(s185_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (1, 16, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (1, 16, 1, 2)  int8 2.520 Q7
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (1, 1, 1, 2)   int8 0.008 Q7
    unsigned char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (1, 16, 3, 2)  (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 16, 3, 2) var shapes:
    // expr_1_out_0: (1, 16, 3, 2) expr_1_in_0: (1, 16, 3, 2) expr_1_in_1: (1,
    // 16, 1, 2) expr_1_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_1_in_0: (uint8-128) 12.578 Q8 expr_1_in_1: int8
            // 2.520 Q7 expr_1_in_2: int8 0.008 Q7
            // expr_1_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_1_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_1_in_1, int32), [161]), [1])), [1]), [1]), Cast(expr_1_in_2, int32)), [15]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 1.008 Q15 -> (uint8-128) 2.016 Q8
            expr_1_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_1_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_1_in_1[i2])*(161))<<((unsigned char)1)))*(1)), (1))*((int)expr_1_in_2[i2])), ((unsigned char)15))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s210_kernel(s210_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (1, 64, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (1, 64, 1, 2)  int8 6.551 Q7
    signed char *__restrict__  expr_2_in_2 = Args->expr_2_in_2; // (1, 1, 1, 2)   int8 0.008 Q7
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (1, 64, 3, 2)  (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 64, 3, 2) var shapes:
    // expr_2_out_0: (1, 64, 3, 2) expr_2_in_0: (1, 64, 3, 2) expr_2_in_1: (1,
    // 64, 1, 2) expr_2_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_2_in_0: (uint8-128) 12.578 Q8 expr_2_in_1: int8
            // 6.551 Q7 expr_2_in_2: int8 0.008 Q7
            // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_2_in_1, int32), [210]), [2])), [1]), [1]), Cast(expr_2_in_2, int32)), [16]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.504 Q15 -> (uint8-128) 2.016 Q8
            expr_2_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_2_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_2_in_1[i2])*(210))<<((unsigned char)2)))*(1)), (1))*((int)expr_2_in_2[i2])), ((unsigned char)16))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s216_kernel(s216_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (1, 256, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (1, 256, 1, 2) int8 14.614 Q7
    signed char *__restrict__  expr_3_in_2 = Args->expr_3_in_2; // (1, 1, 1, 2)   int8 0.008 Q7
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (1, 256, 3, 2) (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 256, 3, 2) var shapes:
    // expr_3_out_0: (1, 256, 3, 2) expr_3_in_0: (1, 256, 3, 2) expr_3_in_1:
    // (1, 256, 1, 2) expr_3_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_3_in_0: (uint8-128) 12.578 Q8 expr_3_in_1: int8
            // 14.614 Q7 expr_3_in_2: int8 0.008 Q7
            // expr_3_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_3_in_1, int32), [234]), [3])), [1]), [1]), Cast(expr_3_in_2, int32)), [17]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.252 Q15 -> (uint8-128) 2.016 Q8
            expr_3_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_3_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_3_in_1[i2])*(234))<<((unsigned char)3)))*(1)), (1))*((int)expr_3_in_2[i2])), ((unsigned char)17))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (16, 16, 16) (uint8-127) 6.490 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (16, 16, 16) (uint8-17) 4.262 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (16, 16, 16) (uint8-29) 2.419 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (16, 16, 16) var shapes:
    // expr_4_out_0: (16, 16, 16) expr_4_in_1: (16, 16, 16) expr_4_in_0: (16,
    // 16, 16) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-17) 4.262 Q8 expr_4_in_0: (uint8-127)
        // 6.490 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_4_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_4_in_0, int32), [127]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_4_in_0, int32), [208]), [1]), [13208]), SigmoidLUTTable)), [8]), [195]), [14])), [226]), [8]), [-14]), 0, 255), uint8)
        // ADD_0_37 scale arg 0 (no zp adj) - (uint8-17) 4.262 Q8 -> (int32-17) 4.262 Q8
        int _SYMBOL_Cast866 = ((int)expr_4_in_1[i0]);
        // scale clip and cast - (int32-17) 8.525 Q9 -> (uint8-29) 2.419 Q7
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast866+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(127))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_4_in_0[i0])*(208)), ((unsigned char)1))-(13208)), SigmoidLUTTable)), (8))*(195)), ((unsigned char)14)))*(226)), ((unsigned char)8))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s57_kernel(s57_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0; // (8, 8, 28)  (uint8-139) 6.195 Q8
    unsigned char *__restrict__  expr_5_in_1 = Args->expr_5_in_1; // (8, 8, 28)  (uint8-23) 3.063 Q8
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (8, 8, 28)  (uint8-31) 2.267 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (8, 8, 28) var shapes:
    // expr_5_out_0: (8, 8, 28) expr_5_in_1: (8, 8, 28) expr_5_in_0: (8, 8, 28)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_1: (uint8-23) 3.063 Q8 expr_5_in_0: (uint8-139)
        // 6.195 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_5_in_1, int32), [253]), [2]), Norm(Mul(Sub(Cast(expr_5_in_0, int32), [139]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_5_in_0, int32), [198]), [1]), [13761]), SigmoidLUTTable)), [8])), [175]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - (int32-1455) 792.919 Q22 -> (uint8-31) 2.267 Q7
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_5_in_1[i0])*(253)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(139))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_5_in_0[i0])*(198)), ((unsigned char)1))-(13761)), SigmoidLUTTable)), (8)))*(175)), ((unsigned char)14))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s76_kernel(s76_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0; // (4, 4, 52)  (uint8-92) 5.850 Q8
    unsigned char *__restrict__  expr_6_in_1 = Args->expr_6_in_1; // (4, 4, 52)  (uint8-28) 2.565 Q8
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (4, 4, 52)  (uint8-29) 2.417 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (4, 4, 52) var shapes:
    // expr_6_out_0: (4, 4, 52) expr_6_in_1: (4, 4, 52) expr_6_in_0: (4, 4, 52)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_1: (uint8-28) 2.565 Q8 expr_6_in_0: (uint8-92)
        // 5.850 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_6_in_1, int32), [225]), [2]), Norm(Mul(Sub(Cast(expr_6_in_0, int32), [92]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_6_in_0, int32), [187]), [1]), [8602]), SigmoidLUTTable)), [8])), [155]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - (int32-1575) 748.761 Q22 -> (uint8-29) 2.417 Q7
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_6_in_1[i0])*(225)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_6_in_0[i0])-(92))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_6_in_0[i0])*(187)), ((unsigned char)1))-(8602)), SigmoidLUTTable)), (8)))*(155)), ((unsigned char)14))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s206_kernel(s206_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0; // (1, 16, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_32_in_1 = Args->expr_32_in_1; // (1, 1, 3, 2)   int8 182.299 Q7
    signed char *__restrict__  expr_32_in_2 = Args->expr_32_in_2; // (1, 1, 1, 2)   int8 0.008 Q7
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 16, 3, 2)  (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 16, 3, 2) var shapes:
    // inter_LOGISTIC_0_190: (1, 16, 3, 2) expr_32_in_0: (1, 16, 3, 2)
    // expr_32_out_0: (1, 16, 3, 2) expr_32_in_1: (1, 1, 3, 2) expr_32_in_2:
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
            // 182.299 Q7 expr_32_in_2: int8 0.008 Q7
            // expr_32_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_190), Cast(expr_32_in_1, int32)), [7]), Cast(expr_32_in_2, int32)), [182]), [22]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_190 = inter_LOGISTIC_0_190;
            // scale clip and cast - int32 1.435 Q15 -> (uint8-128) 2.016 Q8
            expr_32_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_190)*((int)expr_32_in_1[(i1*I2)+i2])), (7))*((int)expr_32_in_2[i2]))*(182)), ((unsigned char)22))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s212_kernel(s212_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_34_in_0 = Args->expr_34_in_0; // (1, 64, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_34_in_1 = Args->expr_34_in_1; // (1, 1, 3, 2)   int8 54.016 Q7
    signed char *__restrict__  expr_34_in_2 = Args->expr_34_in_2; // (1, 1, 1, 2)   int8 0.008 Q7
    unsigned char *__restrict__  expr_34_out_0 = Args->expr_34_out_0; // (1, 64, 3, 2)  (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 64, 3, 2) var shapes:
    // inter_LOGISTIC_0_207: (1, 64, 3, 2) expr_34_in_0: (1, 64, 3, 2)
    // expr_34_out_0: (1, 64, 3, 2) expr_34_in_1: (1, 1, 3, 2) expr_34_in_2:
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
            // 54.016 Q7 expr_34_in_2: int8 0.008 Q7
            // expr_34_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_207), Cast(expr_34_in_1, int32)), [7]), Cast(expr_34_in_2, int32)), [216]), [24]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_207 = inter_LOGISTIC_0_207;
            // scale clip and cast - int32 0.425 Q15 -> (uint8-128) 2.016 Q8
            expr_34_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_207)*((int)expr_34_in_1[(i1*I2)+i2])), (7))*((int)expr_34_in_2[i2]))*(216)), ((unsigned char)24))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s218_kernel(s218_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0; // (1, 256, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_35_in_1 = Args->expr_35_in_1; // (1, 1, 3, 2)   int8 24.063 Q7
    signed char *__restrict__  expr_35_in_2 = Args->expr_35_in_2; // (1, 1, 1, 2)   int8 0.008 Q7
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 256, 3, 2) (uint8-128) 2.016 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 256, 3, 2) var shapes:
    // inter_LOGISTIC_0_224: (1, 256, 3, 2) expr_35_in_0: (1, 256, 3, 2)
    // expr_35_out_0: (1, 256, 3, 2) expr_35_in_1: (1, 1, 3, 2) expr_35_in_2:
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
            // 24.063 Q7 expr_35_in_2: int8 0.008 Q7
            // expr_35_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_224), Cast(expr_35_in_1, int32)), [7]), Cast(expr_35_in_2, int32)), [193]), [25]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_224 = inter_LOGISTIC_0_224;
            // scale clip and cast - int32 0.189 Q15 -> (uint8-128) 2.016 Q8
            expr_35_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_224)*((int)expr_35_in_1[(i1*I2)+i2])), (7))*((int)expr_35_in_2[i2]))*(193)), ((unsigned char)25))-(-128))), (((signed char)8))));
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
    // Max shape: (64, 64, 8) var shapes:
    // expr_33_out_0: (64, 64, 8) expr_33_in_0: (64, 64, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-133) 46.636 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [133]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_33_in_0, int32), [187]), [2]), [99484]), -65536, 65535), SigmoidLUTTable)), [8]), [132]), [13]), [-3]), 0, 255), uint8)
        // scale clip and cast - int32 46.636 Q15 -> (uint8-3) 11.326 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(133))*SigmoidTableInline(gap_clip(((((((int)expr_33_in_0[i0])*(187))<<((unsigned char)2))-(99484))), (((signed char)16))), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-3))), (((signed char)8))));
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
    // Max shape: (32, 32, 16) var shapes:
    // expr_45_out_0: (32, 32, 16) expr_45_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-148) 34.859 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [148]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [139]), [2]), [82288]), -65536, 65535), SigmoidLUTTable)), [8]), [149]), [13]), [-5]), 0, 255), uint8)
        // scale clip and cast - int32 34.859 Q15 -> (uint8-5) 7.472 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(148))*SigmoidTableInline(gap_clip(((((((int)expr_45_in_0[i0])*(139))<<((unsigned char)2))-(82288))), (((signed char)16))), SigmoidLUTTable)), (8))*(149)), ((unsigned char)13))-(-5))), (((signed char)8))));
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
    // Max shape: (32, 32, 16) var shapes:
    // expr_31_out_0: (32, 32, 16) expr_31_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-171) 22.631 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [171]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [181]), [1]), [61902]), SigmoidLUTTable)), [8]), [187]), [13]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 22.631 Q15 -> (uint8-9) 3.883 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(171))*SigmoidTableInline((((((int)expr_31_in_0[i0])*(181))<<((unsigned char)1))-(61902)), SigmoidLUTTable)), (8))*(187)), ((unsigned char)13))-(-9))), (((signed char)8))));
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
    // Max shape: (32, 32, 8) var shapes:
    // expr_13_out_0: (32, 32, 8) expr_13_in_0: (32, 32, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-145) 14.758 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [145]), SigmoidLUT(Sub(Mul(Cast(expr_13_in_0, int32), [236]), [34220]), SigmoidLUTTable)), [8]), [142]), [13]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 14.758 Q15 -> (uint8-11) 3.322 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(145))*SigmoidTableInline(((((int)expr_13_in_0[i0])*(236))-(34220)), SigmoidLUTTable)), (8))*(142)), ((unsigned char)13))-(-11))), (((signed char)8))));
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
    // Max shape: (32, 32, 16) var shapes:
    // expr_36_out_0: (32, 32, 16) expr_36_in_0: (32, 32, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-164) 13.340 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [164]), SigmoidLUT(Sub(Mul(Cast(expr_36_in_0, int32), [213]), [34932]), SigmoidLUTTable)), [8]), [171]), [13]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 13.340 Q15 -> (uint8-14) 2.501 Q7
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(164))*SigmoidTableInline(((((int)expr_36_in_0[i0])*(213))-(34932)), SigmoidLUTTable)), (8))*(171)), ((unsigned char)13))-(-14))), (((signed char)8))));
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
    // Max shape: (16, 16, 32) var shapes:
    // expr_37_out_0: (16, 16, 32) expr_37_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-135) 10.210 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [135]), SigmoidLUT(Sub(Mul(Cast(expr_37_in_0, int32), [163]), [22005]), SigmoidLUTTable)), [8]), [130]), [13]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 10.210 Q15 -> (uint8-14) 2.520 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(135))*SigmoidTableInline(((((int)expr_37_in_0[i0])*(163))-(22005)), SigmoidLUTTable)), (8))*(130)), ((unsigned char)13))-(-14))), (((signed char)8))));
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
    // Max shape: (16, 16, 32) var shapes:
    // expr_38_out_0: (16, 16, 32) expr_38_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-131) 8.332 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [131]), SigmoidLUT(Sub(Mul(Cast(expr_38_in_0, int32), [133]), [17423]), SigmoidLUTTable)), [8]), [250]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 8.332 Q15 -> (uint8-17) 2.131 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(131))*SigmoidTableInline(((((int)expr_38_in_0[i0])*(133))-(17423)), SigmoidLUTTable)), (8))*(250)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (16, 16, 16) var shapes:
    // expr_39_out_0: (16, 16, 16) expr_39_in_0: (16, 16, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-125) 7.010 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [125]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_39_in_0, int32), [224]), [1]), [14000]), SigmoidLUTTable)), [8]), [238]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 7.010 Q15 -> (uint8-19) 1.884 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(125))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_39_in_0[i0])*(224)), ((unsigned char)1))-(14000)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (16, 16, 32) var shapes:
    // expr_41_out_0: (16, 16, 32) expr_41_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-123) 7.081 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_41_in_0, int32), [227]), [1]), [13961]), SigmoidLUTTable)), [8]), [235]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.081 Q15 -> (uint8-18) 1.928 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_41_in_0[i0])*(227)), ((unsigned char)1))-(13961)), SigmoidLUTTable)), (8))*(235)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_42_out_0: (8, 8, 56) expr_42_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-121) 7.157 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [121]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_42_in_0, int32), [229]), [1]), [13855]), SigmoidLUTTable)), [8]), [231]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.157 Q15 -> (uint8-18) 1.983 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(121))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_42_in_0[i0])*(229)), ((unsigned char)1))-(13855)), SigmoidLUTTable)), (8))*(231)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_43_out_0: (8, 8, 56) expr_43_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-137) 6.330 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [137]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_43_in_0, int32), [203]), [1]), [13906]), SigmoidLUTTable)), [8]), [132]), [13]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 6.330 Q15 -> (uint8-23) 1.531 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(137))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_43_in_0[i0])*(203)), ((unsigned char)1))-(13906)), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-23))), (((signed char)8))));
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
    // Max shape: (8, 8, 28) var shapes:
    // expr_44_out_0: (8, 8, 28) expr_44_in_0: (8, 8, 28) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-114) 6.759 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [114]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_44_in_0, int32), [216]), [1]), [12312]), SigmoidLUTTable)), [8]), [221]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 6.759 Q15 -> (uint8-18) 1.962 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(114))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_44_in_0[i0])*(216)), ((unsigned char)1))-(12312)), SigmoidLUTTable)), (8))*(221)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_47_out_0: (8, 8, 56) expr_47_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_47_in_0: (uint8-144) 6.748 Q8
        // expr_47_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_47_in_0, int32), [144]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_47_in_0, int32), [216]), [1]), [15552]), SigmoidLUTTable)), [8]), [141]), [13]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 6.748 Q15 -> (uint8-23) 1.529 Q7
        expr_47_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_47_in_0[i0])-(144))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_47_in_0[i0])*(216)), ((unsigned char)1))-(15552)), SigmoidLUTTable)), (8))*(141)), ((unsigned char)13))-(-23))), (((signed char)8))));
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
    // Max shape: (4, 4, 104) var shapes:
    // expr_48_out_0: (4, 4, 104) expr_48_in_0: (4, 4, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-143) 5.621 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [143]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_48_in_0, int32), [180]), [1]), [12870]), SigmoidLUTTable)), [8]), [141]), [13]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 5.621 Q15 -> (uint8-28) 1.279 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(143))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_48_in_0[i0])*(180)), ((unsigned char)1))-(12870)), SigmoidLUTTable)), (8))*(141)), ((unsigned char)13))-(-28))), (((signed char)8))));
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
    // Max shape: (4, 4, 104) var shapes:
    // expr_49_out_0: (4, 4, 104) expr_49_in_0: (4, 4, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-116) 4.540 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_49_in_0, int32), [145]), [1]), [8410]), SigmoidLUTTable)), [8]), [227]), [14]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 4.540 Q15 -> (uint8-28) 1.283 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_49_in_0[i0])*(145)), ((unsigned char)1))-(8410)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-28))), (((signed char)8))));
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
    // Max shape: (4, 4, 52) var shapes:
    // expr_50_out_0: (4, 4, 52) expr_50_in_0: (4, 4, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-123) 4.841 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_50_in_0, int32), [155]), [1]), [9533]), SigmoidLUTTable)), [8]), [238]), [14]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 4.841 Q15 -> (uint8-27) 1.302 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_50_in_0[i0])*(155)), ((unsigned char)1))-(9533)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-27))), (((signed char)8))));
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
    // Max shape: (4, 4, 104) var shapes:
    // expr_52_out_0: (4, 4, 104) expr_52_in_0: (4, 4, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_52_in_0: (uint8-126) 4.393 Q8
        // expr_52_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_52_in_0, int32), [126]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_52_in_0, int32), [141]), [1]), [8883]), SigmoidLUTTable)), [8]), [246]), [14]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 4.393 Q15 -> (uint8-31) 1.142 Q7
        expr_52_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_52_in_0[i0])-(126))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_52_in_0[i0])*(141)), ((unsigned char)1))-(8883)), SigmoidLUTTable)), (8))*(246)), ((unsigned char)14))-(-31))), (((signed char)8))));
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
    // Max shape: (4, 4, 52) var shapes:
    // expr_53_out_0: (4, 4, 52) expr_53_in_0: (4, 4, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-109) 4.963 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [109]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_53_in_0, int32), [159]), [1]), [8666]), SigmoidLUTTable)), [8]), [215]), [14]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 4.963 Q15 -> (uint8-24) 1.476 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(109))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_53_in_0[i0])*(159)), ((unsigned char)1))-(8666)), SigmoidLUTTable)), (8))*(215)), ((unsigned char)14))-(-24))), (((signed char)8))));
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
    // Max shape: (4, 4, 104) var shapes:
    // expr_55_out_0: (4, 4, 104) expr_55_in_0: (4, 4, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-82) 4.309 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [82]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_55_in_0, int32), [138]), [1]), [5658]), SigmoidLUTTable)), [8]), [181]), [14]), [-23]), 0, 255), uint8)
        // scale clip and cast - int32 4.309 Q15 -> (uint8-23) 1.522 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_55_in_0[i0])-(82))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_55_in_0[i0])*(138)), ((unsigned char)1))-(5658)), SigmoidLUTTable)), (8))*(181)), ((unsigned char)14))-(-23))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_56_out_0: (4, 4, 56) expr_56_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-89) 2.428 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [89]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_56_in_0, int32), [155]), [2]), [3449]), SigmoidLUTTable)), [8]), [199]), [14]), [-41]), 0, 255), uint8)
        // scale clip and cast - int32 2.428 Q15 -> (uint8-41) 0.783 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(89))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_56_in_0[i0])*(155)), ((unsigned char)2))-(3449)), SigmoidLUTTable)), (8))*(199)), ((unsigned char)14))-(-41))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_10_out_0: (8, 8, 56) expr_10_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-132) 4.804 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [132]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_10_in_0, int32), [154]), [1]), [10164]), SigmoidLUTTable)), [8]), [128]), [13]), [-30]), 0, 255), uint8)
        // scale clip and cast - int32 4.804 Q15 -> (uint8-30) 1.197 Q7
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_10_in_0[i0])-(132))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_10_in_0[i0])*(154)), ((unsigned char)1))-(10164)), SigmoidLUTTable)), (8))*(128)), ((unsigned char)13))-(-30))), (((signed char)8))));
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
    // Max shape: (8, 8, 28) var shapes:
    // expr_8_out_0: (8, 8, 28) expr_8_in_0: (8, 8, 28) SigmoidLUTTable: (1, 1,
    // 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_8_in_0: (uint8-115) 4.977 Q8
        // expr_8_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_8_in_0, int32), [115]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_8_in_0, int32), [159]), [1]), [9143]), SigmoidLUTTable)), [8]), [224]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 4.977 Q15 -> (uint8-25) 1.421 Q7
        expr_8_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_8_in_0[i0])-(115))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_8_in_0[i0])*(159)), ((unsigned char)1))-(9143)), SigmoidLUTTable)), (8))*(224)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (8, 8, 28) var shapes:
    // expr_9_out_0: (8, 8, 28) expr_9_in_0: (8, 8, 28) SigmoidLUTTable: (1, 1,
    // 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-162) 5.806 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [162]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_9_in_0, int32), [186]), [1]), [15066]), SigmoidLUTTable)), [8]), [155]), [13]), [-30]), 0, 255), uint8)
        // scale clip and cast - int32 5.806 Q15 -> (uint8-30) 2.395 Q8
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(162))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_9_in_0[i0])*(186)), ((unsigned char)1))-(15066)), SigmoidLUTTable)), (8))*(155)), ((unsigned char)13))-(-30))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_11_out_0: (8, 8, 56) expr_11_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-112) 4.433 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [112]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_11_in_0, int32), [142]), [1]), [7952]), SigmoidLUTTable)), [8]), [221]), [14]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 4.433 Q15 -> (uint8-28) 1.284 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(112))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_11_in_0[i0])*(142)), ((unsigned char)1))-(7952)), SigmoidLUTTable)), (8))*(221)), ((unsigned char)14))-(-28))), (((signed char)8))));
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
    // Max shape: (8, 8, 32) var shapes:
    // expr_12_out_0: (8, 8, 32) expr_12_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-139) 5.325 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [139]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_12_in_0, int32), [170]), [1]), [11815]), SigmoidLUTTable)), [8]), [136]), [13]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 5.325 Q15 -> (uint8-28) 1.257 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_12_in_0[i0])-(139))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_12_in_0[i0])*(170)), ((unsigned char)1))-(11815)), SigmoidLUTTable)), (8))*(136)), ((unsigned char)13))-(-28))), (((signed char)8))));
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
    // Max shape: (16, 16, 32) var shapes:
    // expr_14_out_0: (16, 16, 32) expr_14_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-149) 5.481 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [149]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_14_in_0, int32), [175]), [1]), [13038]), SigmoidLUTTable)), [8]), [150]), [13]), [-30]), 0, 255), uint8)
        // scale clip and cast - int32 5.481 Q15 -> (uint8-30) 1.170 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_14_in_0[i0])-(149))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_14_in_0[i0])*(175)), ((unsigned char)1))-(13038)), SigmoidLUTTable)), (8))*(150)), ((unsigned char)13))-(-30))), (((signed char)8))));
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
    // Max shape: (16, 16, 16) var shapes:
    // expr_15_out_0: (16, 16, 16) expr_15_in_0: (16, 16, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_15_in_0: (uint8-97) 3.946 Q8
        // expr_15_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_15_in_0, int32), [97]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_15_in_0, int32), [253]), [2]), [6135]), SigmoidLUTTable)), [8]), [200]), [14]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 3.946 Q15 -> (uint8-28) 1.260 Q7
        expr_15_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_15_in_0[i0])-(97))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_15_in_0[i0])*(253)), ((unsigned char)2))-(6135)), SigmoidLUTTable)), (8))*(200)), ((unsigned char)14))-(-28))), (((signed char)8))));
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
    // Max shape: (16, 16, 16) var shapes:
    // expr_16_out_0: (16, 16, 16) expr_16_in_0: (16, 16, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-149) 6.110 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [149]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_16_in_0, int32), [196]), [1]), [14602]), SigmoidLUTTable)), [8]), [148]), [13]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 6.110 Q15 -> (uint8-27) 1.321 Q7
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_16_in_0[i0])-(149))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_16_in_0[i0])*(196)), ((unsigned char)1))-(14602)), SigmoidLUTTable)), (8))*(148)), ((unsigned char)13))-(-27))), (((signed char)8))));
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
    // Max shape: (16, 16, 32) var shapes:
    // expr_18_out_0: (16, 16, 32) expr_18_in_0: (16, 16, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-114) 7.541 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [114]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_18_in_0, int32), [241]), [1]), [13737]), SigmoidLUTTable)), [8]), [220]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 7.541 Q15 -> (uint8-16) 2.194 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(114))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_18_in_0[i0])*(241)), ((unsigned char)1))-(13737)), SigmoidLUTTable)), (8))*(220)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (8, 8, 32) var shapes:
    // expr_19_out_0: (8, 8, 32) expr_19_in_0: (8, 8, 32) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-127) 3.890 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [127]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_19_in_0, int32), [249]), [2]), [7906]), SigmoidLUTTable)), [8]), [198]), [14]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 3.890 Q15 -> (uint8-28) 2.518 Q8
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(127))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_19_in_0[i0])*(249)), ((unsigned char)2))-(7906)), SigmoidLUTTable)), (8))*(198)), ((unsigned char)14))-(-28))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_20_out_0: (8, 8, 56) expr_20_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-120) 4.602 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_20_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_20_in_0, int32), [147]), [1]), [8820]), SigmoidLUTTable)), [8]), [233]), [14]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 4.602 Q15 -> (uint8-28) 1.264 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_20_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_20_in_0[i0])*(147)), ((unsigned char)1))-(8820)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14))-(-28))), (((signed char)8))));
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
    // Max shape: (8, 8, 28) var shapes:
    // expr_21_out_0: (8, 8, 28) expr_21_in_0: (8, 8, 28) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-114) 3.630 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [114]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_21_in_0, int32), [232]), [2]), [6612]), SigmoidLUTTable)), [8]), [226]), [14]), [-35]), 0, 255), uint8)
        // scale clip and cast - int32 3.630 Q15 -> (uint8-35) 1.027 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(114))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_21_in_0[i0])*(232)), ((unsigned char)2))-(6612)), SigmoidLUTTable)), (8))*(226)), ((unsigned char)14))-(-35))), (((signed char)8))));
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
    // Max shape: (8, 8, 28) var shapes:
    // expr_22_out_0: (8, 8, 28) expr_22_in_0: (8, 8, 28) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-128) 3.269 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_22_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_22_in_0, int32), [209]), [2]), [6688]), SigmoidLUTTable)), [8]), [166]), [14]), [-28]), 0, 255), uint8)
        // scale clip and cast - int32 3.269 Q15 -> (uint8-28) 2.528 Q8
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_22_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_22_in_0[i0])*(209)), ((unsigned char)2))-(6688)), SigmoidLUTTable)), (8))*(166)), ((unsigned char)14))-(-28))), (((signed char)8))));
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
    // Max shape: (8, 8, 56) var shapes:
    // expr_24_out_0: (8, 8, 56) expr_24_in_0: (8, 8, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_24_in_0: (uint8-101) 5.733 Q8
        // expr_24_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_24_in_0, int32), [101]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_24_in_0, int32), [183]), [1]), [9242]), SigmoidLUTTable)), [8]), [202]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 5.733 Q15 -> (uint8-20) 1.818 Q7
        expr_24_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_24_in_0[i0])-(101))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_24_in_0[i0])*(183)), ((unsigned char)1))-(9242)), SigmoidLUTTable)), (8))*(202)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (4, 4, 56) var shapes:
    // expr_25_out_0: (4, 4, 56) expr_25_in_0: (4, 4, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-111) 3.471 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [111]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_25_in_0, int32), [222]), [2]), [6161]), SigmoidLUTTable)), [8]), [222]), [14]), [-36]), 0, 255), uint8)
        // scale clip and cast - int32 3.471 Q15 -> (uint8-36) 0.999 Q7
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(111))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_25_in_0[i0])*(222)), ((unsigned char)2))-(6161)), SigmoidLUTTable)), (8))*(222)), ((unsigned char)14))-(-36))), (((signed char)8))));
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
    // Max shape: (4, 4, 104) var shapes:
    // expr_26_out_0: (4, 4, 104) expr_26_in_0: (4, 4, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-119) 3.070 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [119]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_26_in_0, int32), [196]), [2]), [5831]), SigmoidLUTTable)), [8]), [238]), [14]), [-43]), 0, 255), uint8)
        // scale clip and cast - int32 3.070 Q15 -> (uint8-43) 0.825 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(119))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_26_in_0[i0])*(196)), ((unsigned char)2))-(5831)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-43))), (((signed char)8))));
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
    // Max shape: (4, 4, 52) var shapes:
    // expr_27_out_0: (4, 4, 52) expr_27_in_0: (4, 4, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-123) 3.292 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [123]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_27_in_0, int32), [211]), [2]), [6488]), SigmoidLUTTable)), [8]), [245]), [14]), [-41]), 0, 255), uint8)
        // scale clip and cast - int32 3.292 Q15 -> (uint8-41) 0.861 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_27_in_0[i0])-(123))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_27_in_0[i0])*(211)), ((unsigned char)2))-(6488)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-41))), (((signed char)8))));
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
    // Max shape: (4, 4, 52) var shapes:
    // expr_28_out_0: (4, 4, 52) expr_28_in_0: (4, 4, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-119) 2.798 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [119]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_28_in_0, int32), [179]), [2]), [5325]), SigmoidLUTTable)), [8]), [216]), [14]), [-44]), 0, 255), uint8)
        // scale clip and cast - int32 2.798 Q15 -> (uint8-44) 1.655 Q8
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(119))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_28_in_0[i0])*(179)), ((unsigned char)2))-(5325)), SigmoidLUTTable)), (8))*(216)), ((unsigned char)14))-(-44))), (((signed char)8))));
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
    // Max shape: (4, 4, 104) var shapes:
    // expr_30_out_0: (4, 4, 104) expr_30_in_0: (4, 4, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-106) 3.947 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [106]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_30_in_0, int32), [253]), [2]), [6705]), SigmoidLUTTable)), [8]), [213]), [14]), [-30]), 0, 255), uint8)
        // scale clip and cast - int32 3.947 Q15 -> (uint8-30) 1.185 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_30_in_0[i0])-(106))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_30_in_0[i0])*(253)), ((unsigned char)2))-(6705)), SigmoidLUTTable)), (8))*(213)), ((unsigned char)14))-(-30))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop