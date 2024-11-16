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
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (112, 112, 8) (uint8-120) 14.923 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (112, 112, 8) (uint8-9) 7.773 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (112, 112, 8) (uint8-16) 4.352 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (112, 112, 8) var shapes:
    // expr_0_out_0: (112, 112, 8) expr_0_in_1: (112, 112, 8) expr_0_in_0:
    // (112, 112, 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-9) 7.773 Q8 expr_0_in_0: (uint8-120)
        // 14.923 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [120]), SigmoidLUT(Sub(Mul(Cast(expr_0_in_0, int32), [239]), [28680]), SigmoidLUTTable)), [8]), [246]), [14])), [229]), [8]), [-8]), 0, 255), uint8)
        // ADD_0_16 scale arg 0 (no zp adj) - (uint8-9) 7.773 Q8 -> (int32-9) 7.773 Q8
        int _SYMBOL_Cast12 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-9) 15.546 Q9 -> (uint8-16) 4.352 Q7
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast12+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(120))*SigmoidTableInline(((((int)expr_0_in_0[i0])*(239))-(28680)), SigmoidLUTTable)), (8))*(246)), ((unsigned char)14)))*(229)), ((unsigned char)8))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s186_kernel(s186_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (1, 196, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (1, 196, 1, 2) int8 12.598 Q7
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (1, 1, 1, 2)   int8 0.002 Q7
    unsigned char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (1, 196, 3, 2) (uint8-128) 2.069 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 196, 3, 2) var shapes:
    // expr_1_out_0: (1, 196, 3, 2) expr_1_in_0: (1, 196, 3, 2) expr_1_in_1:
    // (1, 196, 1, 2) expr_1_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_1_in_0: (uint8-128) 12.578 Q8 expr_1_in_1: int8
            // 12.598 Q7 expr_1_in_2: int8 0.002 Q7
            // expr_1_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_1_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_1_in_1, int32), [202]), [3])), [1]), [1]), Cast(expr_1_in_2, int32)), [143]), [24]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.288 Q15 -> (uint8-128) 2.069 Q8
            expr_1_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_1_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_1_in_1[i2])*(202))<<((unsigned char)3)))*(1)), (1))*((int)expr_1_in_2[i2]))*(143)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (1, 784, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (1, 784, 1, 2) int8 26.709 Q7
    signed char *__restrict__  expr_2_in_2 = Args->expr_2_in_2; // (1, 1, 1, 2)   int8 0.002 Q7
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (1, 784, 3, 2) (uint8-128) 2.069 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 784, 3, 2) var shapes:
    // expr_2_out_0: (1, 784, 3, 2) expr_2_in_0: (1, 784, 3, 2) expr_2_in_1:
    // (1, 784, 1, 2) expr_2_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_2_in_0: (uint8-128) 12.578 Q8 expr_2_in_1: int8
            // 26.709 Q7 expr_2_in_2: int8 0.002 Q7
            // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_2_in_1, int32), [214]), [4])), [1]), [1]), Cast(expr_2_in_2, int32)), [143]), [25]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.144 Q15 -> (uint8-128) 2.069 Q8
            expr_2_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_2_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_2_in_1[i2])*(214))<<((unsigned char)4)))*(1)), (1))*((int)expr_2_in_2[i2]))*(143)), ((unsigned char)25))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (1, 3136, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (1, 3136, 1, 2) int8 54.929 Q7
    signed char *__restrict__  expr_3_in_2 = Args->expr_3_in_2; // (1, 1, 1, 2)    int8 0.002 Q7
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (1, 3136, 3, 2) (uint8-128) 2.069 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 3136, 3, 2) var shapes:
    // expr_3_out_0: (1, 3136, 3, 2) expr_3_in_0: (1, 3136, 3, 2) expr_3_in_1:
    // (1, 3136, 1, 2) expr_3_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1,
    // 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_3_in_0: (uint8-128) 12.578 Q8 expr_3_in_1: int8
            // 54.929 Q7 expr_3_in_2: int8 0.002 Q7
            // expr_3_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_3_in_1, int32), [220]), [5])), [1]), [1]), Cast(expr_3_in_2, int32)), [143]), [26]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.072 Q15 -> (uint8-128) 2.069 Q8
            expr_3_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_3_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_3_in_1[i2])*(220))<<((unsigned char)5)))*(1)), (1))*((int)expr_3_in_2[i2]))*(143)), ((unsigned char)26))-(-128))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (56, 56, 16) (uint8-105) 8.326 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (56, 56, 16) (uint8-17) 4.114 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (56, 56, 16) (uint8-27) 2.671 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (56, 56, 16) var shapes:
    // expr_4_out_0: (56, 56, 16) expr_4_in_1: (56, 56, 16) expr_4_in_0: (56,
    // 56, 16) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-17) 4.114 Q8 expr_4_in_0: (uint8-105)
        // 8.326 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_4_in_1, int32), [253]), [2]), Norm(Mul(Sub(Cast(expr_4_in_0, int32), [105]), SigmoidLUT(Sub(Mul(Cast(expr_4_in_0, int32), [133]), [13965]), SigmoidLUTTable)), [8])), [199]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - (int32-1075) 1065.710 Q22 -> (uint8-27) 2.671 Q7
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_4_in_1[i0])*(253)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(105))*SigmoidTableInline(((((int)expr_4_in_0[i0])*(133))-(13965)), SigmoidLUTTable)), (8)))*(199)), ((unsigned char)14))-(-14))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s57_kernel(s57_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0; // (28, 28, 28) (uint8-137) 6.968 Q8
    unsigned char *__restrict__  expr_5_in_1 = Args->expr_5_in_1; // (28, 28, 28) (uint8-15) 4.653 Q8
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (28, 28, 28) (uint8-29) 4.944 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (28, 28, 28) var shapes:
    // expr_5_out_0: (28, 28, 28) expr_5_in_1: (28, 28, 28) expr_5_in_0: (28,
    // 28, 28) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_1: (uint8-15) 4.653 Q8 expr_5_in_0: (uint8-137)
        // 6.968 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_5_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_5_in_0, int32), [137]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_5_in_0, int32), [223]), [1]), [15276]), SigmoidLUTTable)), [8]), [192]), [14])), [241]), [8]), [-15]), 0, 255), uint8)
        // ADD_0_58 scale arg 0 (no zp adj) - (uint8-15) 4.653 Q8 -> (int32-15) 4.653 Q8
        int _SYMBOL_Cast237 = ((int)expr_5_in_1[i0]);
        // scale clip and cast - (int32-15) 9.305 Q9 -> (uint8-29) 4.944 Q8
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast237+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(137))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_5_in_0[i0])*(223)), ((unsigned char)1))-(15276)), SigmoidLUTTable)), (8))*(192)), ((unsigned char)14)))*(241)), ((unsigned char)8))-(-15))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s77_kernel(s77_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0; // (14, 14, 52) (uint8-118) 9.581 Q8
    unsigned char *__restrict__  expr_6_in_1 = Args->expr_6_in_1; // (14, 14, 52) (uint8-15) 4.641 Q8
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (14, 14, 52) (uint8-18) 3.866 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (14, 14, 52) var shapes:
    // expr_6_out_0: (14, 14, 52) expr_6_in_1: (14, 14, 52) expr_6_in_0: (14,
    // 14, 52) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_1: (uint8-15) 4.641 Q8 expr_6_in_0: (uint8-118)
        // 9.581 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_6_in_1, int32), [248]), [2]), Norm(Mul(Sub(Cast(expr_6_in_0, int32), [118]), SigmoidLUT(Sub(Mul(Cast(expr_6_in_0, int32), [153]), [18054]), SigmoidLUTTable)), [8])), [159]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - (int32-930) 1226.429 Q22 -> (uint8-18) 3.866 Q7
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_6_in_1[i0])*(248)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_6_in_0[i0])-(118))*SigmoidTableInline(((((int)expr_6_in_0[i0])*(153))-(18054)), SigmoidLUTTable)), (8)))*(159)), ((unsigned char)14))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s209_kernel(s209_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0; // (1, 196, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_32_in_1 = Args->expr_32_in_1; // (1, 1, 3, 2)   int8 1503.748 Q7
    signed char *__restrict__  expr_32_in_2 = Args->expr_32_in_2; // (1, 1, 1, 2)   int8 0.002 Q7
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 196, 3, 2) (uint8-128) 2.069 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 196, 3, 2) var shapes:
    // inter_LOGISTIC_0_190: (1, 196, 3, 2) expr_32_in_0: (1, 196, 3, 2)
    // expr_32_out_0: (1, 196, 3, 2) expr_32_in_1: (1, 1, 3, 2) expr_32_in_2:
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
            // expr_32_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_190), Cast(expr_32_in_1, int32)), [7]), Cast(expr_32_in_2, int32)), [209]), [21]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_190 = inter_LOGISTIC_0_190;
            // scale clip and cast - int32 3.383 Q15 -> (uint8-128) 2.069 Q8
            expr_32_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_190)*((int)expr_32_in_1[(i1*I2)+i2])), (7))*((int)expr_32_in_2[i2]))*(209)), ((unsigned char)21))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_34_in_0 = Args->expr_34_in_0; // (1, 784, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_34_in_1 = Args->expr_34_in_1; // (1, 1, 3, 2)   int8 479.748 Q7
    signed char *__restrict__  expr_34_in_2 = Args->expr_34_in_2; // (1, 1, 1, 2)   int8 0.002 Q7
    unsigned char *__restrict__  expr_34_out_0 = Args->expr_34_out_0; // (1, 784, 3, 2) (uint8-128) 2.069 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 784, 3, 2) var shapes:
    // inter_LOGISTIC_0_207: (1, 784, 3, 2) expr_34_in_0: (1, 784, 3, 2)
    // expr_34_out_0: (1, 784, 3, 2) expr_34_in_1: (1, 1, 3, 2) expr_34_in_2:
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
            // expr_34_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_207), Cast(expr_34_in_1, int32)), [7]), Cast(expr_34_in_2, int32)), [134]), [22]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_207 = inter_LOGISTIC_0_207;
            // scale clip and cast - int32 1.079 Q15 -> (uint8-128) 2.069 Q8
            expr_34_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_207)*((int)expr_34_in_1[(i1*I2)+i2])), (7))*((int)expr_34_in_2[i2]))*(134)), ((unsigned char)22))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0; // (1, 3136, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_35_in_1 = Args->expr_35_in_1; // (1, 1, 3, 2)    int8 133.039 Q7
    signed char *__restrict__  expr_35_in_2 = Args->expr_35_in_2; // (1, 1, 1, 2)    int8 0.002 Q7
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 3136, 3, 2) (uint8-128) 2.069 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 3136, 3, 2) var shapes:
    // inter_LOGISTIC_0_224: (1, 3136, 3, 2) expr_35_in_0: (1, 3136, 3, 2)
    // expr_35_out_0: (1, 3136, 3, 2) expr_35_in_1: (1, 1, 3, 2) expr_35_in_2:
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
            // expr_35_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_224), Cast(expr_35_in_1, int32)), [7]), Cast(expr_35_in_2, int32)), [148]), [24]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_224 = inter_LOGISTIC_0_224;
            // scale clip and cast - int32 0.299 Q15 -> (uint8-128) 2.069 Q8
            expr_35_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_224)*((int)expr_35_in_1[(i1*I2)+i2])), (7))*((int)expr_35_in_2[i2]))*(148)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    // Max shape: (224, 224, 8) var shapes:
    // expr_33_out_0: (224, 224, 8) expr_33_in_0: (224, 224, 8)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-125) 26.810 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [125]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_33_in_0, int32), [214]), [1]), [53500]), SigmoidLUTTable)), [8]), [247]), [14]), [-5]), 0, 255), uint8)
        // scale clip and cast - int32 26.810 Q15 -> (uint8-5) 6.950 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(125))*SigmoidTableInline((((((int)expr_33_in_0[i0])*(214))<<((unsigned char)1))-(53500)), SigmoidLUTTable)), (8))*(247)), ((unsigned char)14))-(-5))), (((signed char)8))));
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
    // Max shape: (112, 112, 16) var shapes:
    // expr_45_out_0: (112, 112, 16) expr_45_in_0: (112, 112, 16)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-85) 42.912 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [85]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [172]), [2]), [58480]), -65536, 65535), SigmoidLUTTable)), [8]), [191]), [14]), [-2]), 0, 255), uint8)
        // scale clip and cast - int32 42.912 Q15 -> (uint8-2) 14.407 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(85))*SigmoidTableInline(gap_clip(((((((int)expr_45_in_0[i0])*(172))<<((unsigned char)2))-(58480))), (((signed char)16))), SigmoidLUTTable)), (8))*(191)), ((unsigned char)14))-(-2))), (((signed char)8))));
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
    // Max shape: (112, 112, 16) var shapes:
    // expr_31_out_0: (112, 112, 16) expr_31_in_0: (112, 112, 16)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-178) 24.759 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [178]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [198]), [1]), [70488]), -65536, 65535), SigmoidLUTTable)), [8]), [204]), [13]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 24.759 Q15 -> (uint8-9) 3.887 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(178))*SigmoidTableInline(gap_clip(((((((int)expr_31_in_0[i0])*(198))<<((unsigned char)1))-(70488))), (((signed char)16))), SigmoidLUTTable)), (8))*(204)), ((unsigned char)13))-(-9))), (((signed char)8))));
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
    // Max shape: (112, 112, 8) var shapes:
    // expr_13_out_0: (112, 112, 8) expr_13_in_0: (112, 112, 8)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-150) 10.320 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [150]), SigmoidLUT(Sub(Mul(Cast(expr_13_in_0, int32), [165]), [24750]), SigmoidLUTTable)), [8]), [148]), [13]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 10.320 Q15 -> (uint8-16) 2.224 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(150))*SigmoidTableInline(((((int)expr_13_in_0[i0])*(165))-(24750)), SigmoidLUTTable)), (8))*(148)), ((unsigned char)13))-(-16))), (((signed char)8))));
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
    // Max shape: (112, 112, 16) var shapes:
    // expr_36_out_0: (112, 112, 16) expr_36_in_0: (112, 112, 16)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-144) 13.541 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [144]), SigmoidLUT(Sub(Mul(Cast(expr_36_in_0, int32), [217]), [31248]), SigmoidLUTTable)), [8]), [141]), [13]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 13.541 Q15 -> (uint8-12) 3.072 Q7
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(144))*SigmoidTableInline(((((int)expr_36_in_0[i0])*(217))-(31248)), SigmoidLUTTable)), (8))*(141)), ((unsigned char)13))-(-12))), (((signed char)8))));
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
    // Max shape: (56, 56, 32) var shapes:
    // expr_37_out_0: (56, 56, 32) expr_37_in_0: (56, 56, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-137) 9.220 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [137]), SigmoidLUT(Sub(Mul(Cast(expr_37_in_0, int32), [148]), [20276]), SigmoidLUTTable)), [8]), [132]), [13]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 9.220 Q15 -> (uint8-16) 2.235 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(137))*SigmoidTableInline(((((int)expr_37_in_0[i0])*(148))-(20276)), SigmoidLUTTable)), (8))*(132)), ((unsigned char)13))-(-16))), (((signed char)8))));
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
    // Max shape: (56, 56, 32) var shapes:
    // expr_38_out_0: (56, 56, 32) expr_38_in_0: (56, 56, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-121) 7.432 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [121]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_38_in_0, int32), [238]), [1]), [14399]), SigmoidLUTTable)), [8]), [231]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.432 Q15 -> (uint8-17) 2.057 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(121))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_38_in_0[i0])*(238)), ((unsigned char)1))-(14399)), SigmoidLUTTable)), (8))*(231)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (56, 56, 16) var shapes:
    // expr_39_out_0: (56, 56, 16) expr_39_in_0: (56, 56, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-122) 7.368 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [122]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_39_in_0, int32), [236]), [1]), [14396]), SigmoidLUTTable)), [8]), [233]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.368 Q15 -> (uint8-18) 2.023 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(122))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_39_in_0[i0])*(236)), ((unsigned char)1))-(14396)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (56, 56, 32) var shapes:
    // expr_41_out_0: (56, 56, 32) expr_41_in_0: (56, 56, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-140) 7.712 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [140]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_41_in_0, int32), [247]), [1]), [17290]), SigmoidLUTTable)), [8]), [135]), [13]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 7.712 Q15 -> (uint8-19) 1.833 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(140))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_41_in_0[i0])*(247)), ((unsigned char)1))-(17290)), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-19))), (((signed char)8))));
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
    // Max shape: (28, 28, 56) var shapes:
    // expr_42_out_0: (28, 28, 56) expr_42_in_0: (28, 28, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-124) 6.784 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [124]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_42_in_0, int32), [217]), [1]), [13454]), SigmoidLUTTable)), [8]), [237]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 6.784 Q15 -> (uint8-19) 1.832 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(124))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_42_in_0[i0])*(217)), ((unsigned char)1))-(13454)), SigmoidLUTTable)), (8))*(237)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (28, 28, 56) var shapes:
    // expr_43_out_0: (28, 28, 56) expr_43_in_0: (28, 28, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-113) 7.961 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [113]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_43_in_0, int32), [255]), [1]), [14408]), SigmoidLUTTable)), [8]), [219]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 7.961 Q15 -> (uint8-15) 2.326 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(113))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_43_in_0[i0])*(255)), ((unsigned char)1))-(14408)), SigmoidLUTTable)), (8))*(219)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (28, 28, 28) var shapes:
    // expr_44_out_0: (28, 28, 28) expr_44_in_0: (28, 28, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-132) 6.851 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [132]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_44_in_0, int32), [219]), [1]), [14454]), SigmoidLUTTable)), [8]), [253]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 6.851 Q15 -> (uint8-21) 1.736 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(132))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_44_in_0[i0])*(219)), ((unsigned char)1))-(14454)), SigmoidLUTTable)), (8))*(253)), ((unsigned char)14))-(-21))), (((signed char)8))));
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
    // Max shape: (28, 28, 56) var shapes:
    // expr_47_out_0: (28, 28, 56) expr_47_in_0: (28, 28, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_47_in_0: (uint8-117) 7.382 Q8
        // expr_47_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_47_in_0, int32), [117]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_47_in_0, int32), [236]), [1]), [13806]), SigmoidLUTTable)), [8]), [225]), [14]), [-17]), 0, 255), uint8)
        // scale clip and cast - int32 7.382 Q15 -> (uint8-17) 2.100 Q7
        expr_47_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_47_in_0[i0])-(117))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_47_in_0[i0])*(236)), ((unsigned char)1))-(13806)), SigmoidLUTTable)), (8))*(225)), ((unsigned char)14))-(-17))), (((signed char)8))));
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
    // Max shape: (14, 14, 104) var shapes:
    // expr_48_out_0: (14, 14, 104) expr_48_in_0: (14, 14, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-119) 6.899 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [119]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_48_in_0, int32), [221]), [1]), [13150]), SigmoidLUTTable)), [8]), [228]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 6.899 Q15 -> (uint8-18) 1.935 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(119))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_48_in_0[i0])*(221)), ((unsigned char)1))-(13150)), SigmoidLUTTable)), (8))*(228)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (14, 14, 104) var shapes:
    // expr_49_out_0: (14, 14, 104) expr_49_in_0: (14, 14, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-106) 7.578 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [106]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_49_in_0, int32), [243]), [1]), [12879]), SigmoidLUTTable)), [8]), [209]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 7.578 Q15 -> (uint8-15) 2.321 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(106))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_49_in_0[i0])*(243)), ((unsigned char)1))-(12879)), SigmoidLUTTable)), (8))*(209)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (14, 14, 52) var shapes:
    // expr_50_out_0: (14, 14, 52) expr_50_in_0: (14, 14, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-111) 8.144 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [111]), SigmoidLUT(Sub(Mul(Cast(expr_50_in_0, int32), [130]), [14430]), SigmoidLUTTable)), [8]), [216]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 8.144 Q15 -> (uint8-15) 2.413 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(111))*SigmoidTableInline(((((int)expr_50_in_0[i0])*(130))-(14430)), SigmoidLUTTable)), (8))*(216)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (14, 14, 104) var shapes:
    // expr_52_out_0: (14, 14, 104) expr_52_in_0: (14, 14, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_52_in_0: (uint8-116) 7.913 Q8
        // expr_52_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_52_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_52_in_0, int32), [253]), [1]), [14674]), SigmoidLUTTable)), [8]), [223]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 7.913 Q15 -> (uint8-16) 2.271 Q7
        expr_52_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_52_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_52_in_0[i0])*(253)), ((unsigned char)1))-(14674)), SigmoidLUTTable)), (8))*(223)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (14, 14, 52) var shapes:
    // expr_53_out_0: (14, 14, 52) expr_53_in_0: (14, 14, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-130) 7.734 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [130]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_53_in_0, int32), [248]), [1]), [16120]), SigmoidLUTTable)), [8]), [248]), [14]), [-18]), 0, 255), uint8)
        // scale clip and cast - int32 7.734 Q15 -> (uint8-18) 1.998 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(130))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_53_in_0[i0])*(248)), ((unsigned char)1))-(16120)), SigmoidLUTTable)), (8))*(248)), ((unsigned char)14))-(-18))), (((signed char)8))));
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
    // Max shape: (14, 14, 104) var shapes:
    // expr_55_out_0: (14, 14, 104) expr_55_in_0: (14, 14, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-127) 8.596 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [127]), SigmoidLUT(Sub(Mul(Cast(expr_55_in_0, int32), [138]), [17526]), SigmoidLUTTable)), [8]), [242]), [14]), [-16]), 0, 255), uint8)
        // scale clip and cast - int32 8.596 Q15 -> (uint8-16) 2.273 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_55_in_0[i0])-(127))*SigmoidTableInline(((((int)expr_55_in_0[i0])*(138))-(17526)), SigmoidLUTTable)), (8))*(242)), ((unsigned char)14))-(-16))), (((signed char)8))));
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
    // Max shape: (14, 14, 56) var shapes:
    // expr_56_out_0: (14, 14, 56) expr_56_in_0: (14, 14, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-124) 9.405 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [124]), SigmoidLUT(Sub(Mul(Cast(expr_56_in_0, int32), [150]), [18600]), SigmoidLUTTable)), [8]), [238]), [14]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 9.405 Q15 -> (uint8-14) 2.530 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(124))*SigmoidTableInline(((((int)expr_56_in_0[i0])*(150))-(18600)), SigmoidLUTTable)), (8))*(238)), ((unsigned char)14))-(-14))), (((signed char)8))));
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
    // Max shape: (28, 28, 56) var shapes:
    // expr_10_out_0: (28, 28, 56) expr_10_in_0: (28, 28, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-140) 10.016 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [140]), SigmoidLUT(Sub(Mul(Cast(expr_10_in_0, int32), [160]), [22400]), SigmoidLUTTable)), [8]), [135]), [13]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 10.016 Q15 -> (uint8-15) 2.381 Q7
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_10_in_0[i0])-(140))*SigmoidTableInline(((((int)expr_10_in_0[i0])*(160))-(22400)), SigmoidLUTTable)), (8))*(135)), ((unsigned char)13))-(-15))), (((signed char)8))));
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
    // Max shape: (28, 28, 28) var shapes:
    // expr_8_out_0: (28, 28, 28) expr_8_in_0: (28, 28, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_8_in_0: (uint8-112) 10.342 Q8
        // expr_8_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_8_in_0, int32), [112]), SigmoidLUT(Sub(Mul(Cast(expr_8_in_0, int32), [165]), [18480]), SigmoidLUTTable)), [8]), [218]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.342 Q15 -> (uint8-12) 3.038 Q7
        expr_8_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_8_in_0[i0])-(112))*SigmoidTableInline(((((int)expr_8_in_0[i0])*(165))-(18480)), SigmoidLUTTable)), (8))*(218)), ((unsigned char)14))-(-12))), (((signed char)8))));
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
    // Max shape: (28, 28, 28) var shapes:
    // expr_9_out_0: (28, 28, 28) expr_9_in_0: (28, 28, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-121) 11.530 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [121]), SigmoidLUT(Sub(Mul(Cast(expr_9_in_0, int32), [184]), [22264]), SigmoidLUTTable)), [8]), [233]), [14]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 11.530 Q15 -> (uint8-11) 6.326 Q8
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(121))*SigmoidTableInline(((((int)expr_9_in_0[i0])*(184))-(22264)), SigmoidLUTTable)), (8))*(233)), ((unsigned char)14))-(-11))), (((signed char)8))));
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
    // Max shape: (28, 28, 56) var shapes:
    // expr_11_out_0: (28, 28, 56) expr_11_in_0: (28, 28, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-144) 12.597 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [144]), SigmoidLUT(Sub(Mul(Cast(expr_11_in_0, int32), [202]), [29088]), SigmoidLUTTable)), [8]), [141]), [13]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 12.597 Q15 -> (uint8-12) 2.862 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(144))*SigmoidTableInline(((((int)expr_11_in_0[i0])*(202))-(29088)), SigmoidLUTTable)), (8))*(141)), ((unsigned char)13))-(-12))), (((signed char)8))));
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
    // Max shape: (28, 28, 32) var shapes:
    // expr_12_out_0: (28, 28, 32) expr_12_in_0: (28, 28, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-123) 13.380 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [123]), SigmoidLUT(Sub(Mul(Cast(expr_12_in_0, int32), [214]), [26322]), SigmoidLUTTable)), [8]), [239]), [14]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 13.380 Q15 -> (uint8-10) 3.587 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_12_in_0[i0])-(123))*SigmoidTableInline(((((int)expr_12_in_0[i0])*(214))-(26322)), SigmoidLUTTable)), (8))*(239)), ((unsigned char)14))-(-10))), (((signed char)8))));
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
    // Max shape: (56, 56, 32) var shapes:
    // expr_14_out_0: (56, 56, 32) expr_14_in_0: (56, 56, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-125) 12.959 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [125]), SigmoidLUT(Sub(Mul(Cast(expr_14_in_0, int32), [207]), [25875]), SigmoidLUTTable)), [8]), [242]), [14]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 12.959 Q15 -> (uint8-10) 3.433 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_14_in_0[i0])-(125))*SigmoidTableInline(((((int)expr_14_in_0[i0])*(207))-(25875)), SigmoidLUTTable)), (8))*(242)), ((unsigned char)14))-(-10))), (((signed char)8))));
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
    // Max shape: (56, 56, 16) var shapes:
    // expr_15_out_0: (56, 56, 16) expr_15_in_0: (56, 56, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_15_in_0: (uint8-127) 10.901 Q8
        // expr_15_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_15_in_0, int32), [127]), SigmoidLUT(Sub(Mul(Cast(expr_15_in_0, int32), [174]), [22098]), SigmoidLUTTable)), [8]), [243]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.901 Q15 -> (uint8-12) 2.872 Q7
        expr_15_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_15_in_0[i0])-(127))*SigmoidTableInline(((((int)expr_15_in_0[i0])*(174))-(22098)), SigmoidLUTTable)), (8))*(243)), ((unsigned char)14))-(-12))), (((signed char)8))));
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
    // Max shape: (56, 56, 16) var shapes:
    // expr_16_out_0: (56, 56, 16) expr_16_in_0: (56, 56, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-154) 9.221 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [154]), SigmoidLUT(Sub(Mul(Cast(expr_16_in_0, int32), [148]), [22792]), SigmoidLUTTable)), [8]), [172]), [14]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 9.221 Q15 -> (uint8-10) 6.869 Q8
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_16_in_0[i0])-(154))*SigmoidTableInline(((((int)expr_16_in_0[i0])*(148))-(22792)), SigmoidLUTTable)), (8))*(172)), ((unsigned char)14))-(-10))), (((signed char)8))));
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
    // Max shape: (56, 56, 32) var shapes:
    // expr_18_out_0: (56, 56, 32) expr_18_in_0: (56, 56, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-133) 13.894 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [133]), SigmoidLUT(Sub(Mul(Cast(expr_18_in_0, int32), [222]), [29526]), SigmoidLUTTable)), [8]), [128]), [13]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 13.894 Q15 -> (uint8-10) 3.471 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(133))*SigmoidTableInline(((((int)expr_18_in_0[i0])*(222))-(29526)), SigmoidLUTTable)), (8))*(128)), ((unsigned char)13))-(-10))), (((signed char)8))));
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
    // Max shape: (28, 28, 32) var shapes:
    // expr_19_out_0: (28, 28, 32) expr_19_in_0: (28, 28, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-113) 10.078 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [113]), SigmoidLUT(Sub(Mul(Cast(expr_19_in_0, int32), [161]), [18193]), SigmoidLUTTable)), [8]), [180]), [14]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 10.078 Q15 -> (uint8-10) 7.174 Q8
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(113))*SigmoidTableInline(((((int)expr_19_in_0[i0])*(161))-(18193)), SigmoidLUTTable)), (8))*(180)), ((unsigned char)14))-(-10))), (((signed char)8))));
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
    // Max shape: (28, 28, 56) var shapes:
    // expr_20_out_0: (28, 28, 56) expr_20_in_0: (28, 28, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-128) 11.533 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_20_in_0, [128]), int8), int32), SigmoidLUT(Sub(Mul(Cast(expr_20_in_0, int32), [185]), [23680]), SigmoidLUTTable)), [8]), [245]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 11.533 Q15 -> (uint8-12) 3.007 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_20_in_0[i0]+((unsigned char)128))))*SigmoidTableInline(((((int)expr_20_in_0[i0])*(185))-(23680)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-12))), (((signed char)8))));
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
    // Max shape: (28, 28, 28) var shapes:
    // expr_21_out_0: (28, 28, 28) expr_21_in_0: (28, 28, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-123) 10.606 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [123]), SigmoidLUT(Sub(Mul(Cast(expr_21_in_0, int32), [170]), [20910]), SigmoidLUTTable)), [8]), [235]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.606 Q15 -> (uint8-12) 2.883 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(123))*SigmoidTableInline(((((int)expr_21_in_0[i0])*(170))-(20910)), SigmoidLUTTable)), (8))*(235)), ((unsigned char)14))-(-12))), (((signed char)8))));
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
    // Max shape: (28, 28, 28) var shapes:
    // expr_22_out_0: (28, 28, 28) expr_22_in_0: (28, 28, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-110) 10.024 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [110]), SigmoidLUT(Sub(Mul(Cast(expr_22_in_0, int32), [160]), [17600]), SigmoidLUTTable)), [8]), [213]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 10.024 Q15 -> (uint8-12) 6.015 Q8
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_22_in_0[i0])-(110))*SigmoidTableInline(((((int)expr_22_in_0[i0])*(160))-(17600)), SigmoidLUTTable)), (8))*(213)), ((unsigned char)14))-(-12))), (((signed char)8))));
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
    // Max shape: (28, 28, 56) var shapes:
    // expr_24_out_0: (28, 28, 56) expr_24_in_0: (28, 28, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_24_in_0: (uint8-127) 12.398 Q8
        // expr_24_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_24_in_0, int32), [127]), SigmoidLUT(Sub(Mul(Cast(expr_24_in_0, int32), [198]), [25146]), SigmoidLUTTable)), [8]), [245]), [14]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 12.398 Q15 -> (uint8-11) 3.237 Q7
        expr_24_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_24_in_0[i0])-(127))*SigmoidTableInline(((((int)expr_24_in_0[i0])*(198))-(25146)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-11))), (((signed char)8))));
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
    // Max shape: (14, 14, 56) var shapes:
    // expr_25_out_0: (14, 14, 56) expr_25_in_0: (14, 14, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-87) 11.175 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [87]), SigmoidLUT(Sub(Mul(Cast(expr_25_in_0, int32), [179]), [15573]), SigmoidLUTTable)), [8]), [187]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 11.175 Q15 -> (uint8-9) 7.629 Q8
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(87))*SigmoidTableInline(((((int)expr_25_in_0[i0])*(179))-(15573)), SigmoidLUTTable)), (8))*(187)), ((unsigned char)14))-(-9))), (((signed char)8))));
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
    // Max shape: (14, 14, 104) var shapes:
    // expr_26_out_0: (14, 14, 104) expr_26_in_0: (14, 14, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-122) 13.334 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [122]), SigmoidLUT(Sub(Mul(Cast(expr_26_in_0, int32), [213]), [25986]), SigmoidLUTTable)), [8]), [235]), [14]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 13.334 Q15 -> (uint8-10) 3.624 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(122))*SigmoidTableInline(((((int)expr_26_in_0[i0])*(213))-(25986)), SigmoidLUTTable)), (8))*(235)), ((unsigned char)14))-(-10))), (((signed char)8))));
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
    // Max shape: (14, 14, 52) var shapes:
    // expr_27_out_0: (14, 14, 52) expr_27_in_0: (14, 14, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-131) 13.978 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [131]), SigmoidLUT(Sub(Mul(Cast(expr_27_in_0, int32), [224]), [29344]), SigmoidLUTTable)), [8]), [252]), [14]), [-10]), 0, 255), uint8)
        // scale clip and cast - int32 13.978 Q15 -> (uint8-10) 3.545 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_27_in_0[i0])-(131))*SigmoidTableInline(((((int)expr_27_in_0[i0])*(224))-(29344)), SigmoidLUTTable)), (8))*(252)), ((unsigned char)14))-(-10))), (((signed char)8))));
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
    // Max shape: (14, 14, 52) var shapes:
    // expr_28_out_0: (14, 14, 52) expr_28_in_0: (14, 14, 52) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-113) 14.267 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [113]), SigmoidLUT(Sub(Mul(Cast(expr_28_in_0, int32), [228]), [25764]), SigmoidLUTTable)), [8]), [222]), [14]), [-9]), 0, 255), uint8)
        // scale clip and cast - int32 14.267 Q15 -> (uint8-9) 4.114 Q7
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(113))*SigmoidTableInline(((((int)expr_28_in_0[i0])*(228))-(25764)), SigmoidLUTTable)), (8))*(222)), ((unsigned char)14))-(-9))), (((signed char)8))));
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
    // Max shape: (14, 14, 104) var shapes:
    // expr_30_out_0: (14, 14, 104) expr_30_in_0: (14, 14, 104)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-128) 16.323 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_30_in_0, [128]), int8), int32), SigmoidLUT(Sub(LShift(Mul(Cast(expr_30_in_0, int32), [131]), [1]), [33536]), SigmoidLUTTable)), [8]), [249]), [14]), [-8]), 0, 255), uint8)
        // scale clip and cast - int32 16.323 Q15 -> (uint8-8) 4.195 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_30_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((((((int)expr_30_in_0[i0])*(131))<<((unsigned char)1))-(33536)), SigmoidLUTTable)), (8))*(249)), ((unsigned char)14))-(-8))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop