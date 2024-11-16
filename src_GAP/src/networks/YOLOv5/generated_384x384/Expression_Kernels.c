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
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (96, 96, 8) (uint8-126) 12.778 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (96, 96, 8) (uint8-11) 6.489 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (96, 96, 8) (uint8-20) 3.503 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (96, 96, 8) var shapes:
    // expr_0_out_0: (96, 96, 8) expr_0_in_1: (96, 96, 8) expr_0_in_0: (96, 96,
    // 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-11) 6.489 Q8 expr_0_in_0: (uint8-126)
        // 12.778 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_0_in_0, int32), [204]), [25704]), SigmoidLUTTable)), [8]), [252]), [14])), [237]), [8]), [-10]), 0, 255), uint8)
        // ADD_0_16 scale arg 0 (no zp adj) - (uint8-11) 6.489 Q8 -> (int32-11) 6.489 Q8
        int _SYMBOL_Cast12 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-11) 12.978 Q9 -> (uint8-20) 3.503 Q7
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast12+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(126))*SigmoidTableInline(((((int)expr_0_in_0[i0])*(204))-(25704)), SigmoidLUTTable)), (8))*(252)), ((unsigned char)14)))*(237)), ((unsigned char)8))-(-10))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s187_kernel(s187_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (1, 144, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (1, 144, 1, 2) int8 10.583 Q7
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (1, 1, 1, 2)   int8 0.003 Q7
    unsigned char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (1, 144, 3, 2) (uint8-128) 2.029 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 144, 3, 2) var shapes:
    // expr_1_out_0: (1, 144, 3, 2) expr_1_in_0: (1, 144, 3, 2) expr_1_in_1:
    // (1, 144, 1, 2) expr_1_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_1_in_0: (uint8-128) 12.578 Q8 expr_1_in_1: int8
            // 10.583 Q7 expr_1_in_2: int8 0.003 Q7
            // expr_1_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_1_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_1_in_1, int32), [169]), [3])), [1]), [1]), Cast(expr_1_in_2, int32)), [170]), [24]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.336 Q15 -> (uint8-128) 2.029 Q8
            expr_1_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_1_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_1_in_1[i2])*(169))<<((unsigned char)3)))*(1)), (1))*((int)expr_1_in_2[i2]))*(170)), ((unsigned char)24))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s214_kernel(s214_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (1, 576, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (1, 576, 1, 2) int8 22.677 Q7
    signed char *__restrict__  expr_2_in_2 = Args->expr_2_in_2; // (1, 1, 1, 2)   int8 0.003 Q7
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (1, 576, 3, 2) (uint8-128) 2.029 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 576, 3, 2) var shapes:
    // expr_2_out_0: (1, 576, 3, 2) expr_2_in_0: (1, 576, 3, 2) expr_2_in_1:
    // (1, 576, 1, 2) expr_2_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_2_in_0: (uint8-128) 12.578 Q8 expr_2_in_1: int8
            // 22.677 Q7 expr_2_in_2: int8 0.003 Q7
            // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_2_in_1, int32), [181]), [4])), [1]), [1]), Cast(expr_2_in_2, int32)), [170]), [25]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.168 Q15 -> (uint8-128) 2.029 Q8
            expr_2_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_2_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_2_in_1[i2])*(181))<<((unsigned char)4)))*(1)), (1))*((int)expr_2_in_2[i2]))*(170)), ((unsigned char)25))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (1, 2304, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (1, 2304, 1, 2) int8 46.866 Q7
    signed char *__restrict__  expr_3_in_2 = Args->expr_3_in_2; // (1, 1, 1, 2)    int8 0.003 Q7
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (1, 2304, 3, 2) (uint8-128) 2.029 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 2304, 3, 2) var shapes:
    // expr_3_out_0: (1, 2304, 3, 2) expr_3_in_0: (1, 2304, 3, 2) expr_3_in_1:
    // (1, 2304, 1, 2) expr_3_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1,
    // 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_3_in_0: (uint8-128) 12.578 Q8 expr_3_in_1: int8
            // 46.866 Q7 expr_3_in_2: int8 0.003 Q7
            // expr_3_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_3_in_1, int32), [187]), [5])), [1]), [1]), Cast(expr_3_in_2, int32)), [170]), [26]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.084 Q15 -> (uint8-128) 2.029 Q8
            expr_3_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_3_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_3_in_1[i2])*(187))<<((unsigned char)5)))*(1)), (1))*((int)expr_3_in_2[i2]))*(170)), ((unsigned char)26))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (48, 48, 16) (uint8-134) 8.429 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (48, 48, 16) (uint8-15) 4.634 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (48, 48, 16) (uint8-24) 2.916 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (48, 48, 16) var shapes:
    // expr_4_out_0: (48, 48, 16) expr_4_in_1: (48, 48, 16) expr_4_in_0: (48,
    // 48, 16) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-15) 4.634 Q8 expr_4_in_0: (uint8-134)
        // 8.429 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_4_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_4_in_0, int32), [134]), SigmoidLUT(Sub(Mul(Cast(expr_4_in_0, int32), [135]), [18090]), SigmoidLUTTable)), [8]), [233]), [14])), [203]), [8]), [-12]), 0, 255), uint8)
        // ADD_0_37 scale arg 0 (no zp adj) - (uint8-15) 4.634 Q8 -> (int32-15) 4.634 Q8
        int _SYMBOL_Cast28 = ((int)expr_4_in_1[i0]);
        // scale clip and cast - (int32-15) 9.267 Q9 -> (uint8-24) 2.916 Q7
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast28+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(134))*SigmoidTableInline(((((int)expr_4_in_0[i0])*(135))-(18090)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14)))*(203)), ((unsigned char)8))-(-12))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s57_kernel(s57_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0; // (24, 24, 28) (uint8-134) 7.514 Q8
    unsigned char *__restrict__  expr_5_in_1 = Args->expr_5_in_1; // (24, 24, 28) (uint8-19) 3.672 Q8
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (24, 24, 28) (uint8-29) 2.432 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (24, 24, 28) var shapes:
    // expr_5_out_0: (24, 24, 28) expr_5_in_1: (24, 24, 28) expr_5_in_0: (24,
    // 24, 28) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_1: (uint8-19) 3.672 Q8 expr_5_in_0: (uint8-134)
        // 7.514 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_5_in_1, int32), [250]), [2]), Norm(Mul(Sub(Cast(expr_5_in_0, int32), [134]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_5_in_0, int32), [240]), [1]), [16080]), SigmoidLUTTable)), [8])), [198]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - (int32-1188) 961.842 Q22 -> (uint8-29) 2.432 Q7
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_5_in_1[i0])*(250)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(134))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_5_in_0[i0])*(240)), ((unsigned char)1))-(16080)), SigmoidLUTTable)), (8)))*(198)), ((unsigned char)14))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s76_kernel(s76_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0; // (12, 12, 52) (uint8-111) 6.965 Q8
    unsigned char *__restrict__  expr_6_in_1 = Args->expr_6_in_1; // (12, 12, 52) (uint8-21) 3.324 Q8
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (12, 12, 52) (uint8-28) 2.510 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (12, 12, 52) var shapes:
    // expr_6_out_0: (12, 12, 52) expr_6_in_1: (12, 12, 52) expr_6_in_0: (12,
    // 12, 52) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_1: (uint8-21) 3.324 Q8 expr_6_in_0: (uint8-111)
        // 6.965 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_6_in_1, int32), [244]), [2]), Norm(Mul(Sub(Cast(expr_6_in_0, int32), [111]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_6_in_0, int32), [223]), [1]), [12377]), SigmoidLUTTable)), [8])), [178]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - (int32-1281) 891.483 Q22 -> (uint8-28) 2.510 Q7
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_6_in_1[i0])*(244)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_6_in_0[i0])-(111))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_6_in_0[i0])*(223)), ((unsigned char)1))-(12377)), SigmoidLUTTable)), (8)))*(178)), ((unsigned char)14))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s210_kernel(s210_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0; // (1, 144, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_32_in_1 = Args->expr_32_in_1; // (1, 1, 3, 2)   int8 1503.748 Q7
    signed char *__restrict__  expr_32_in_2 = Args->expr_32_in_2; // (1, 1, 1, 2)   int8 0.003 Q7
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 144, 3, 2) (uint8-128) 2.029 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 144, 3, 2) var shapes:
    // inter_LOGISTIC_0_190: (1, 144, 3, 2) expr_32_in_0: (1, 144, 3, 2)
    // expr_32_out_0: (1, 144, 3, 2) expr_32_in_1: (1, 1, 3, 2) expr_32_in_2:
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
            // expr_32_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_190), Cast(expr_32_in_1, int32)), [7]), Cast(expr_32_in_2, int32)), [249]), [21]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_190 = inter_LOGISTIC_0_190;
            // scale clip and cast - int32 3.947 Q15 -> (uint8-128) 2.029 Q8
            expr_32_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_190)*((int)expr_32_in_1[(i1*I2)+i2])), (7))*((int)expr_32_in_2[i2]))*(249)), ((unsigned char)21))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_34_in_0 = Args->expr_34_in_0; // (1, 576, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_34_in_1 = Args->expr_34_in_1; // (1, 1, 3, 2)   int8 479.748 Q7
    signed char *__restrict__  expr_34_in_2 = Args->expr_34_in_2; // (1, 1, 1, 2)   int8 0.003 Q7
    unsigned char *__restrict__  expr_34_out_0 = Args->expr_34_out_0; // (1, 576, 3, 2) (uint8-128) 2.029 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 576, 3, 2) var shapes:
    // inter_LOGISTIC_0_207: (1, 576, 3, 2) expr_34_in_0: (1, 576, 3, 2)
    // expr_34_out_0: (1, 576, 3, 2) expr_34_in_1: (1, 1, 3, 2) expr_34_in_2:
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
            // expr_34_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_207), Cast(expr_34_in_1, int32)), [7]), Cast(expr_34_in_2, int32)), [159]), [22]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_207 = inter_LOGISTIC_0_207;
            // scale clip and cast - int32 1.259 Q15 -> (uint8-128) 2.029 Q8
            expr_34_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_207)*((int)expr_34_in_1[(i1*I2)+i2])), (7))*((int)expr_34_in_2[i2]))*(159)), ((unsigned char)22))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0; // (1, 2304, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_35_in_1 = Args->expr_35_in_1; // (1, 1, 3, 2)    int8 133.039 Q7
    signed char *__restrict__  expr_35_in_2 = Args->expr_35_in_2; // (1, 1, 1, 2)    int8 0.003 Q7
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 2304, 3, 2) (uint8-128) 2.029 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 2304, 3, 2) var shapes:
    // inter_LOGISTIC_0_224: (1, 2304, 3, 2) expr_35_in_0: (1, 2304, 3, 2)
    // expr_35_out_0: (1, 2304, 3, 2) expr_35_in_1: (1, 1, 3, 2) expr_35_in_2:
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
            // expr_35_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_224), Cast(expr_35_in_1, int32)), [7]), Cast(expr_35_in_2, int32)), [176]), [24]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_224 = inter_LOGISTIC_0_224;
            // scale clip and cast - int32 0.349 Q15 -> (uint8-128) 2.029 Q8
            expr_35_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_224)*((int)expr_35_in_1[(i1*I2)+i2])), (7))*((int)expr_35_in_2[i2]))*(176)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    // Max shape: (192, 192, 8) var shapes:
    // expr_33_out_0: (192, 192, 8) expr_33_in_0: (192, 192, 8)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-136) 32.753 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [136]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_33_in_0, int32), [131]), [2]), [71264]), -65536, 65535), SigmoidLUTTable)), [8]), [135]), [13]), [-5]), 0, 255), uint8)
        // scale clip and cast - int32 32.753 Q15 -> (uint8-5) 7.774 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(136))*SigmoidTableInline(gap_clip(((((((int)expr_33_in_0[i0])*(131))<<((unsigned char)2))-(71264))), (((signed char)16))), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-5))), (((signed char)8))));
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
    // Max shape: (96, 96, 16) var shapes:
    // expr_45_out_0: (96, 96, 16) expr_45_in_0: (96, 96, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-158) 68.931 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [158]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [138]), [3]), [174432]), -65536, 65535), SigmoidLUTTable)), [8]), [166]), [13]), [-3]), 0, 255), uint8)
        // scale clip and cast - int32 68.931 Q15 -> (uint8-3) 13.290 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(158))*SigmoidTableInline(gap_clip(((((((int)expr_45_in_0[i0])*(138))<<((unsigned char)3))-(174432))), (((signed char)16))), SigmoidLUTTable)), (8))*(166)), ((unsigned char)13))-(-3))), (((signed char)8))));
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
    // Max shape: (96, 96, 16) var shapes:
    // expr_31_out_0: (96, 96, 16) expr_31_in_0: (96, 96, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-194) 25.853 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [194]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [207]), [1]), [80316]), -65536, 65535), SigmoidLUTTable)), [8]), [255]), [13]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 25.853 Q15 -> (uint8-11) 3.244 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(194))*SigmoidTableInline(gap_clip(((((((int)expr_31_in_0[i0])*(207))<<((unsigned char)1))-(80316))), (((signed char)16))), SigmoidLUTTable)), (8))*(255)), ((unsigned char)13))-(-11))), (((signed char)8))));
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
    // Max shape: (96, 96, 8) var shapes:
    // expr_13_out_0: (96, 96, 8) expr_13_in_0: (96, 96, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-113) 8.790 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [113]), SigmoidLUT(Sub(Mul(Cast(expr_13_in_0, int32), [141]), [15933]), SigmoidLUTTable)), [8]), [219]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 8.790 Q15 -> (uint8-14) 2.574 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(113))*SigmoidTableInline(((((int)expr_13_in_0[i0])*(141))-(15933)), SigmoidLUTTable)), (8))*(219)), ((unsigned char)14))-(-14))), (((signed char)8))));
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
    // Max shape: (96, 96, 16) var shapes:
    // expr_36_out_0: (96, 96, 16) expr_36_in_0: (96, 96, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-146) 12.101 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [146]), SigmoidLUT(Sub(Mul(Cast(expr_36_in_0, int32), [194]), [28324]), SigmoidLUTTable)), [8]), [143]), [13]), [-13]), 0, 255), uint8)
        // scale clip and cast - int32 12.101 Q15 -> (uint8-13) 2.707 Q7
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(146))*SigmoidTableInline(((((int)expr_36_in_0[i0])*(194))-(28324)), SigmoidLUTTable)), (8))*(143)), ((unsigned char)13))-(-13))), (((signed char)8))));
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
    // Max shape: (48, 48, 32) var shapes:
    // expr_37_out_0: (48, 48, 32) expr_37_in_0: (48, 48, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-124) 8.324 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [124]), SigmoidLUT(Sub(Mul(Cast(expr_37_in_0, int32), [133]), [16492]), SigmoidLUTTable)), [8]), [237]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.324 Q15 -> (uint8-16) 2.244 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(124))*SigmoidTableInline(((((int)expr_37_in_0[i0])*(133))-(16492)), SigmoidLUTTable)), (8))*(237)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (48, 48, 32) var shapes:
    // expr_38_out_0: (48, 48, 32) expr_38_in_0: (48, 48, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-116) 8.106 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [116]), SigmoidLUT(Sub(Mul(Cast(expr_38_in_0, int32), [130]), [15080]), SigmoidLUTTable)), [8]), [224]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 8.106 Q15 -> (uint8-15) 2.317 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(116))*SigmoidTableInline(((((int)expr_38_in_0[i0])*(130))-(15080)), SigmoidLUTTable)), (8))*(224)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (48, 48, 16) var shapes:
    // expr_39_out_0: (48, 48, 16) expr_39_in_0: (48, 48, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-109) 7.722 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [109]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_39_in_0, int32), [247]), [1]), [13462]), SigmoidLUTTable)), [8]), [213]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 7.722 Q15 -> (uint8-15) 2.316 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(109))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_39_in_0[i0])*(247)), ((unsigned char)1))-(13462)), SigmoidLUTTable)), (8))*(213)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (48, 48, 32) var shapes:
    // expr_41_out_0: (48, 48, 32) expr_41_in_0: (48, 48, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-148) 8.544 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [148]), SigmoidLUT(Sub(Mul(Cast(expr_41_in_0, int32), [137]), [20276]), SigmoidLUTTable)), [8]), [146]), [13]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 8.544 Q15 -> (uint8-19) 1.878 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(148))*SigmoidTableInline(((((int)expr_41_in_0[i0])*(137))-(20276)), SigmoidLUTTable)), (8))*(146)), ((unsigned char)13))-(-19))), (((signed char)8))));
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
    // Max shape: (24, 24, 56) var shapes:
    // expr_42_out_0: (24, 24, 56) expr_42_in_0: (24, 24, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-140) 8.226 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [140]), SigmoidLUT(Sub(Mul(Cast(expr_42_in_0, int32), [132]), [18480]), SigmoidLUTTable)), [8]), [135]), [13]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 8.226 Q15 -> (uint8-18) 1.952 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(140))*SigmoidTableInline(((((int)expr_42_in_0[i0])*(132))-(18480)), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-18))), (((signed char)8))));
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
    // Max shape: (24, 24, 56) var shapes:
    // expr_43_out_0: (24, 24, 56) expr_43_in_0: (24, 24, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-159) 9.315 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [159]), SigmoidLUT(Sub(Mul(Cast(expr_43_in_0, int32), [149]), [23691]), SigmoidLUTTable)), [8]), [162]), [13]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 9.315 Q15 -> (uint8-19) 1.836 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(159))*SigmoidTableInline(((((int)expr_43_in_0[i0])*(149))-(23691)), SigmoidLUTTable)), (8))*(162)), ((unsigned char)13))-(-19))), (((signed char)8))));
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
    // Max shape: (24, 24, 28) var shapes:
    // expr_44_out_0: (24, 24, 28) expr_44_in_0: (24, 24, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-131) 7.002 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_44_in_0, int32), [224]), [1]), [14672]), SigmoidLUTTable)), [8]), [250]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 7.002 Q15 -> (uint8-20) 1.791 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_44_in_0[i0])*(224)), ((unsigned char)1))-(14672)), SigmoidLUTTable)), (8))*(250)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (24, 24, 56) var shapes:
    // expr_47_out_0: (24, 24, 56) expr_47_in_0: (24, 24, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_47_in_0: (uint8-120) 7.488 Q8
        // expr_47_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_47_in_0, int32), [120]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_47_in_0, int32), [240]), [1]), [14400]), SigmoidLUTTable)), [8]), [229]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.488 Q15 -> (uint8-17) 2.090 Q7
        expr_47_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_47_in_0[i0])-(120))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_47_in_0[i0])*(240)), ((unsigned char)1))-(14400)), SigmoidLUTTable)), (8))*(229)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (12, 12, 104) var shapes:
    // expr_48_out_0: (12, 12, 104) expr_48_in_0: (12, 12, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-132) 7.415 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [132]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_48_in_0, int32), [237]), [1]), [15642]), SigmoidLUTTable)), [8]), [253]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 7.415 Q15 -> (uint8-19) 1.876 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(132))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_48_in_0[i0])*(237)), ((unsigned char)1))-(15642)), SigmoidLUTTable)), (8))*(253)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (12, 12, 104) var shapes:
    // expr_49_out_0: (12, 12, 104) expr_49_in_0: (12, 12, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-129) 6.408 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [129]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_49_in_0, int32), [205]), [1]), [13223]), SigmoidLUTTable)), [8]), [247]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 6.408 Q15 -> (uint8-21) 1.662 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(129))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_49_in_0[i0])*(205)), ((unsigned char)1))-(13223)), SigmoidLUTTable)), (8))*(247)), ((unsigned char)14))-(-21))), (((signed char)8))));
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
    // Max shape: (12, 12, 52) var shapes:
    // expr_50_out_0: (12, 12, 52) expr_50_in_0: (12, 12, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-122) 6.928 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [122]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_50_in_0, int32), [222]), [1]), [13542]), SigmoidLUTTable)), [8]), [233]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 6.928 Q15 -> (uint8-19) 1.900 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(122))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_50_in_0[i0])*(222)), ((unsigned char)1))-(13542)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (12, 12, 104) var shapes:
    // expr_52_out_0: (12, 12, 104) expr_52_in_0: (12, 12, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_52_in_0: (uint8-130) 6.424 Q8
        // expr_52_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_52_in_0, int32), [130]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_52_in_0, int32), [206]), [1]), [13390]), SigmoidLUTTable)), [8]), [248]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 6.424 Q15 -> (uint8-22) 1.655 Q7
        expr_52_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_52_in_0[i0])-(130))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_52_in_0[i0])*(206)), ((unsigned char)1))-(13390)), SigmoidLUTTable)), (8))*(248)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (12, 12, 52) var shapes:
    // expr_53_out_0: (12, 12, 52) expr_53_in_0: (12, 12, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-133) 7.162 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [133]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_53_in_0, int32), [229]), [1]), [15229]), SigmoidLUTTable)), [8]), [255]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 7.162 Q15 -> (uint8-20) 1.796 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(133))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_53_in_0[i0])*(229)), ((unsigned char)1))-(15229)), SigmoidLUTTable)), (8))*(255)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (12, 12, 104) var shapes:
    // expr_55_out_0: (12, 12, 104) expr_55_in_0: (12, 12, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-121) 7.379 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [121]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_55_in_0, int32), [236]), [1]), [14278]), SigmoidLUTTable)), [8]), [232]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.379 Q15 -> (uint8-17) 2.038 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_55_in_0[i0])-(121))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_55_in_0[i0])*(236)), ((unsigned char)1))-(14278)), SigmoidLUTTable)), (8))*(232)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_56_out_0: (12, 12, 56) expr_56_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-121) 7.119 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [121]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_56_in_0, int32), [228]), [1]), [13794]), SigmoidLUTTable)), [8]), [232]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.119 Q15 -> (uint8-18) 1.966 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(121))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_56_in_0[i0])*(228)), ((unsigned char)1))-(13794)), SigmoidLUTTable)), (8))*(232)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (24, 24, 56) var shapes:
    // expr_10_out_0: (24, 24, 56) expr_10_in_0: (24, 24, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-128) 6.898 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_10_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_10_in_0, int32), [221]), [1]), [14144]), SigmoidLUTTable)), [8]), [246]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.898 Q15 -> (uint8-20) 1.797 Q7
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_10_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_10_in_0[i0])*(221)), ((unsigned char)1))-(14144)), SigmoidLUTTable)), (8))*(246)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (24, 24, 28) var shapes:
    // expr_8_out_0: (24, 24, 28) expr_8_in_0: (24, 24, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_8_in_0: (uint8-122) 6.166 Q8
        // expr_8_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_8_in_0, int32), [122]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_8_in_0, int32), [197]), [1]), [12017]), SigmoidLUTTable)), [8]), [234]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 6.166 Q15 -> (uint8-21) 1.690 Q7
        expr_8_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_8_in_0[i0])-(122))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_8_in_0[i0])*(197)), ((unsigned char)1))-(12017)), SigmoidLUTTable)), (8))*(234)), ((unsigned char)14))-(-21))), (((signed char)8))));
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
    // Max shape: (24, 24, 28) var shapes:
    // expr_9_out_0: (24, 24, 28) expr_9_in_0: (24, 24, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-117) 6.314 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [117]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_9_in_0, int32), [202]), [1]), [11817]), SigmoidLUTTable)), [8]), [225]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.314 Q15 -> (uint8-20) 3.594 Q8
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(117))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_9_in_0[i0])*(202)), ((unsigned char)1))-(11817)), SigmoidLUTTable)), (8))*(225)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (24, 24, 56) var shapes:
    // expr_11_out_0: (24, 24, 56) expr_11_in_0: (24, 24, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-118) 6.538 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [118]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_11_in_0, int32), [209]), [1]), [12331]), SigmoidLUTTable)), [8]), [227]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 6.538 Q15 -> (uint8-19) 1.845 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(118))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_11_in_0[i0])*(209)), ((unsigned char)1))-(12331)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (24, 24, 32) var shapes:
    // expr_12_out_0: (24, 24, 32) expr_12_in_0: (24, 24, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-106) 7.578 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [106]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_12_in_0, int32), [243]), [1]), [12879]), SigmoidLUTTable)), [8]), [208]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 7.578 Q15 -> (uint8-15) 2.335 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_12_in_0[i0])-(106))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_12_in_0[i0])*(243)), ((unsigned char)1))-(12879)), SigmoidLUTTable)), (8))*(208)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (48, 48, 32) var shapes:
    // expr_14_out_0: (48, 48, 32) expr_14_in_0: (48, 48, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-124) 7.036 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [124]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_14_in_0, int32), [225]), [1]), [13950]), SigmoidLUTTable)), [8]), [238]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 7.036 Q15 -> (uint8-19) 1.895 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_14_in_0[i0])-(124))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_14_in_0[i0])*(225)), ((unsigned char)1))-(13950)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (48, 48, 16) var shapes:
    // expr_15_out_0: (48, 48, 16) expr_15_in_0: (48, 48, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_15_in_0: (uint8-117) 8.245 Q8
        // expr_15_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_15_in_0, int32), [117]), SigmoidLUT(Sub(Mul(Cast(expr_15_in_0, int32), [132]), [15444]), SigmoidLUTTable)), [8]), [224]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 8.245 Q15 -> (uint8-15) 2.353 Q7
        expr_15_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_15_in_0[i0])-(117))*SigmoidTableInline(((((int)expr_15_in_0[i0])*(132))-(15444)), SigmoidLUTTable)), (8))*(224)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (48, 48, 16) var shapes:
    // expr_16_out_0: (48, 48, 16) expr_16_in_0: (48, 48, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-126) 9.040 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [126]), SigmoidLUT(Sub(Mul(Cast(expr_16_in_0, int32), [145]), [18270]), SigmoidLUTTable)), [8]), [242]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 9.040 Q15 -> (uint8-15) 4.788 Q8
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_16_in_0[i0])-(126))*SigmoidTableInline(((((int)expr_16_in_0[i0])*(145))-(18270)), SigmoidLUTTable)), (8))*(242)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (48, 48, 32) var shapes:
    // expr_18_out_0: (48, 48, 32) expr_18_in_0: (48, 48, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-123) 10.995 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [123]), SigmoidLUT(Sub(Mul(Cast(expr_18_in_0, int32), [176]), [21648]), SigmoidLUTTable)), [8]), [237]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.995 Q15 -> (uint8-12) 2.974 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(123))*SigmoidTableInline(((((int)expr_18_in_0[i0])*(176))-(21648)), SigmoidLUTTable)), (8))*(237)), ((unsigned char)14))-(-12))), (((signed char)8))));
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
    // Max shape: (24, 24, 32) var shapes:
    // expr_19_out_0: (24, 24, 32) expr_19_in_0: (24, 24, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-113) 6.743 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [113]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_19_in_0, int32), [216]), [1]), [12204]), SigmoidLUTTable)), [8]), [185]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 6.743 Q15 -> (uint8-15) 4.674 Q8
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(113))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_19_in_0[i0])*(216)), ((unsigned char)1))-(12204)), SigmoidLUTTable)), (8))*(185)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (24, 24, 56) var shapes:
    // expr_20_out_0: (24, 24, 56) expr_20_in_0: (24, 24, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-132) 8.377 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_20_in_0, int32), [132]), SigmoidLUT(Sub(Mul(Cast(expr_20_in_0, int32), [134]), [17688]), SigmoidLUTTable)), [8]), [252]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 8.377 Q15 -> (uint8-17) 2.127 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_20_in_0[i0])-(132))*SigmoidTableInline(((((int)expr_20_in_0[i0])*(134))-(17688)), SigmoidLUTTable)), (8))*(252)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (24, 24, 28) var shapes:
    // expr_21_out_0: (24, 24, 28) expr_21_in_0: (24, 24, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-120) 8.055 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [120]), SigmoidLUT(Sub(Mul(Cast(expr_21_in_0, int32), [129]), [15480]), SigmoidLUTTable)), [8]), [230]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.055 Q15 -> (uint8-16) 2.240 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(120))*SigmoidTableInline(((((int)expr_21_in_0[i0])*(129))-(15480)), SigmoidLUTTable)), (8))*(230)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (24, 24, 28) var shapes:
    // expr_22_out_0: (24, 24, 28) expr_22_in_0: (24, 24, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-155) 7.746 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [155]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_22_in_0, int32), [248]), [1]), [19220]), SigmoidLUTTable)), [8]), [233]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.746 Q15 -> (uint8-17) 4.255 Q8
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_22_in_0[i0])-(155))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_22_in_0[i0])*(248)), ((unsigned char)1))-(19220)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (24, 24, 56) var shapes:
    // expr_24_out_0: (24, 24, 56) expr_24_in_0: (24, 24, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_24_in_0: (uint8-131) 8.439 Q8
        // expr_24_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_24_in_0, int32), [131]), SigmoidLUT(Sub(Mul(Cast(expr_24_in_0, int32), [135]), [17685]), SigmoidLUTTable)), [8]), [251]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 8.439 Q15 -> (uint8-17) 2.154 Q7
        expr_24_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_24_in_0[i0])-(131))*SigmoidTableInline(((((int)expr_24_in_0[i0])*(135))-(17685)), SigmoidLUTTable)), (8))*(251)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_25_out_0: (12, 12, 56) expr_25_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-104) 6.589 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [104]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_25_in_0, int32), [211]), [1]), [10972]), SigmoidLUTTable)), [8]), [205]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 6.589 Q15 -> (uint8-17) 4.113 Q8
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(104))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_25_in_0[i0])*(211)), ((unsigned char)1))-(10972)), SigmoidLUTTable)), (8))*(205)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (12, 12, 104) var shapes:
    // expr_26_out_0: (12, 12, 104) expr_26_in_0: (12, 12, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-100) 6.794 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [100]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_26_in_0, int32), [217]), [1]), [10850]), SigmoidLUTTable)), [8]), [200]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 6.794 Q15 -> (uint8-16) 2.173 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(100))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_26_in_0[i0])*(217)), ((unsigned char)1))-(10850)), SigmoidLUTTable)), (8))*(200)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (12, 12, 52) var shapes:
    // expr_27_out_0: (12, 12, 52) expr_27_in_0: (12, 12, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-128) 6.939 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_27_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_27_in_0, int32), [222]), [1]), [14208]), SigmoidLUTTable)), [8]), [244]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.939 Q15 -> (uint8-20) 1.818 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_27_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_27_in_0[i0])*(222)), ((unsigned char)1))-(14208)), SigmoidLUTTable)), (8))*(244)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (12, 12, 52) var shapes:
    // expr_28_out_0: (12, 12, 52) expr_28_in_0: (12, 12, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-118) 4.911 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [118]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_28_in_0, int32), [157]), [1]), [9263]), SigmoidLUTTable)), [8]), [144]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 4.911 Q15 -> (uint8-16) 4.353 Q8
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(118))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_28_in_0[i0])*(157)), ((unsigned char)1))-(9263)), SigmoidLUTTable)), (8))*(144)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (12, 12, 104) var shapes:
    // expr_30_out_0: (12, 12, 104) expr_30_in_0: (12, 12, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-125) 6.137 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [125]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_30_in_0, int32), [196]), [1]), [12250]), SigmoidLUTTable)), [8]), [239]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 6.137 Q15 -> (uint8-22) 1.641 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_30_in_0[i0])-(125))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_30_in_0[i0])*(196)), ((unsigned char)1))-(12250)), SigmoidLUTTable)), (8))*(239)), ((unsigned char)14))-(-22))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop