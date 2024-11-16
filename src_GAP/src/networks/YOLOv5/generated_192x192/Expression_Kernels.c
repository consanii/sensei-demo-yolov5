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
    unsigned char *__restrict__  expr_0_in_0 = Args->expr_0_in_0; // (48, 48, 8) (uint8-136) 10.398 Q8
    unsigned char *__restrict__  expr_0_in_1 = Args->expr_0_in_1; // (48, 48, 8) (uint8-11) 6.688 Q8
    unsigned char *__restrict__  expr_0_out_0 = Args->expr_0_out_0; // (48, 48, 8) (uint8-21) 6.965 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (48, 48, 8) var shapes:
    // expr_0_out_0: (48, 48, 8) expr_0_in_1: (48, 48, 8) expr_0_in_0: (48, 48,
    // 8) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_0_in_1: (uint8-11) 6.688 Q8 expr_0_in_0: (uint8-136)
        // 10.398 Q8
        // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0, int32), [136]), SigmoidLUT(Sub(Mul(Cast(expr_0_in_0, int32), [166]), [22576]), SigmoidLUTTable)), [8]), [199]), [14])), [246]), [8]), [-10]), 0, 255), uint8)
        // ADD_0_16 scale arg 0 (no zp adj) - (uint8-11) 6.688 Q8 -> (int32-11) 6.688 Q8
        int _SYMBOL_Cast794 = ((int)expr_0_in_1[i0]);
        // scale clip and cast - (int32-11) 13.376 Q9 -> (uint8-21) 6.965 Q8
        expr_0_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast794+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0])-(136))*SigmoidTableInline(((((int)expr_0_in_0[i0])*(166))-(22576)), SigmoidLUTTable)), (8))*(199)), ((unsigned char)14)))*(246)), ((unsigned char)8))-(-10))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s184_kernel(s184_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_1_in_0 = Args->expr_1_in_0; // (1, 36, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_1_in_1 = Args->expr_1_in_1; // (1, 36, 1, 2)  int8 4.535 Q7
    signed char *__restrict__  expr_1_in_2 = Args->expr_1_in_2; // (1, 1, 1, 2)   int8 0.005 Q7
    unsigned char *__restrict__  expr_1_out_0 = Args->expr_1_out_0; // (1, 36, 3, 2)  uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 36, 3, 2) var shapes:
    // expr_1_out_0: (1, 36, 3, 2) expr_1_in_0: (1, 36, 3, 2) expr_1_in_1: (1,
    // 36, 1, 2) expr_1_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_1_in_0: (uint8-128) 12.578 Q8 expr_1_in_1: int8
            // 4.535 Q7 expr_1_in_2: int8 0.005 Q7
            // expr_1_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_1_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_1_in_1, int32), [145]), [2])), [1]), [1]), Cast(expr_1_in_2, int32)), [171]), [22]), 0, 255), uint8)
            // scale clip and cast - int32 0.672 Q15 -> uint8 1.004 Q8
            expr_1_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_1_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_1_in_1[i2])*(145))<<((unsigned char)2)))*(1)), (1))*((int)expr_1_in_2[i2]))*(171)), ((unsigned char)22))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_2_in_0 = Args->expr_2_in_0; // (1, 144, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_2_in_1 = Args->expr_2_in_1; // (1, 144, 1, 2) int8 10.583 Q7
    signed char *__restrict__  expr_2_in_2 = Args->expr_2_in_2; // (1, 1, 1, 2)   int8 0.005 Q7
    unsigned char *__restrict__  expr_2_out_0 = Args->expr_2_out_0; // (1, 144, 3, 2) (uint8-128) 2.032 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 144, 3, 2) var shapes:
    // expr_2_out_0: (1, 144, 3, 2) expr_2_in_0: (1, 144, 3, 2) expr_2_in_1:
    // (1, 144, 1, 2) expr_2_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_2_in_0: (uint8-128) 12.578 Q8 expr_2_in_1: int8
            // 10.583 Q7 expr_2_in_2: int8 0.005 Q7
            // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_2_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_2_in_1, int32), [169]), [3])), [1]), [1]), Cast(expr_2_in_2, int32)), [169]), [24]), [-128]), 0, 255), uint8)
            // scale clip and cast - int32 0.336 Q15 -> (uint8-128) 2.032 Q8
            expr_2_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_2_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_2_in_1[i2])*(169))<<((unsigned char)3)))*(1)), (1))*((int)expr_2_in_2[i2]))*(169)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_3_in_0 = Args->expr_3_in_0; // (1, 576, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_3_in_1 = Args->expr_3_in_1; // (1, 576, 1, 2) int8 22.677 Q7
    signed char *__restrict__  expr_3_in_2 = Args->expr_3_in_2; // (1, 1, 1, 2)   int8 0.005 Q7
    unsigned char *__restrict__  expr_3_out_0 = Args->expr_3_out_0; // (1, 576, 3, 2) uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 576, 3, 2) var shapes:
    // expr_3_out_0: (1, 576, 3, 2) expr_3_in_0: (1, 576, 3, 2) expr_3_in_1:
    // (1, 576, 1, 2) expr_3_in_2: (1, 1, 1, 2) SigmoidLUTTable: (1, 1, 1, 256)
    // Iteration reduced to spaces ((1,), (2,), (3,))
    // Fixed spaces ((1,),)
    // Parameteric spaces ((2,), (3,))
    // Paralelized space (2,)
    // Interior spaces ()
    for (int i1=First; i1<Last; i1++) {
        for (int i2=0; i2<I2; i2++) {
            // inputs expr_3_in_0: (uint8-128) 12.578 Q8 expr_3_in_1: int8
            // 22.677 Q7 expr_3_in_2: int8 0.005 Q7
            // expr_3_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Add(Mul(SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [201]), [25728]), SigmoidLUTTable), [1]), LShift(Mul(Cast(expr_3_in_1, int32), [181]), [4])), [1]), [1]), Cast(expr_3_in_2, int32)), [171]), [24]), 0, 255), uint8)
            // scale clip and cast - int32 0.168 Q15 -> uint8 1.004 Q8
            expr_3_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((((SigmoidTableInline(((((int)expr_3_in_0[(i1*I2)+i2])*(201))-(25728)), SigmoidLUTTable)*(1))+((((int)expr_3_in_1[i2])*(181))<<((unsigned char)4)))*(1)), (1))*((int)expr_3_in_2[i2]))*(171)), ((unsigned char)24))), (((signed char)8))));
        }
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_4_in_0 = Args->expr_4_in_0; // (24, 24, 16) (uint8-142) 7.447 Q8
    unsigned char *__restrict__  expr_4_in_1 = Args->expr_4_in_1; // (24, 24, 16) (uint8-11) 6.762 Q8
    unsigned char *__restrict__  expr_4_out_0 = Args->expr_4_out_0; // (24, 24, 16) (uint8-20) 7.022 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (24, 24, 16) var shapes:
    // expr_4_out_0: (24, 24, 16) expr_4_in_1: (24, 24, 16) expr_4_in_0: (24,
    // 24, 16) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_4_in_1: (uint8-11) 6.762 Q8 expr_4_in_0: (uint8-142)
        // 7.447 Q8
        // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_4_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_4_in_0, int32), [142]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_4_in_0, int32), [238]), [1]), [16898]), SigmoidLUTTable)), [8]), [141]), [14])), [247]), [8]), [-9]), 0, 255), uint8)
        // ADD_0_37 scale arg 0 (no zp adj) - (uint8-11) 6.762 Q8 -> (int32-11) 6.762 Q8
        int _SYMBOL_Cast790 = ((int)expr_4_in_1[i0]);
        // scale clip and cast - (int32-11) 13.524 Q9 -> (uint8-20) 7.022 Q8
        expr_4_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast790+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_4_in_0[i0])-(142))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_4_in_0[i0])*(238)), ((unsigned char)1))-(16898)), SigmoidLUTTable)), (8))*(141)), ((unsigned char)14)))*(247)), ((unsigned char)8))-(-9))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s57_kernel(s57_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)  
    unsigned char *__restrict__  expr_5_in_0 = Args->expr_5_in_0; // (12, 12, 28) (uint8-140) 5.457 Q8
    unsigned char *__restrict__  expr_5_in_1 = Args->expr_5_in_1; // (12, 12, 28) (uint8-24) 3.007 Q8
    unsigned char *__restrict__  expr_5_out_0 = Args->expr_5_out_0; // (12, 12, 28) (uint8-42) 1.694 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (12, 12, 28) var shapes:
    // expr_5_out_0: (12, 12, 28) expr_5_in_1: (12, 12, 28) expr_5_in_0: (12,
    // 12, 28) SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_5_in_1: (uint8-24) 3.007 Q8 expr_5_in_0: (uint8-140)
        // 5.457 Q8
        // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_5_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_5_in_0, int32), [140]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_5_in_0, int32), [175]), [1]), [12250]), SigmoidLUTTable)), [8]), [232]), [14])), [227]), [8]), [-21]), 0, 255), uint8)
        // ADD_0_58 scale arg 0 (no zp adj) - (uint8-24) 3.007 Q8 -> (int32-24) 3.007 Q8
        int _SYMBOL_Cast592 = ((int)expr_5_in_1[i0]);
        // scale clip and cast - (int32-24) 6.014 Q9 -> (uint8-42) 1.694 Q7
        expr_5_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((_SYMBOL_Cast592+gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_5_in_0[i0])-(140))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_5_in_0[i0])*(175)), ((unsigned char)1))-(12250)), SigmoidLUTTable)), (8))*(232)), ((unsigned char)14)))*(227)), ((unsigned char)8))-(-21))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s76_kernel(s76_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256) 
    unsigned char *__restrict__  expr_6_in_0 = Args->expr_6_in_0; // (6, 6, 52)  (uint8-109) 5.509 Q8
    unsigned char *__restrict__  expr_6_in_1 = Args->expr_6_in_1; // (6, 6, 52)  (uint8-29) 2.425 Q8
    unsigned char *__restrict__  expr_6_out_0 = Args->expr_6_out_0; // (6, 6, 52)  (uint8-42) 1.696 Q7
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I0);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I0);
    // Max shape: (6, 6, 52) var shapes:
    // expr_6_out_0: (6, 6, 52) expr_6_in_1: (6, 6, 52) expr_6_in_0: (6, 6, 52)
    // SigmoidLUTTable: (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_6_in_1: (uint8-29) 2.425 Q8 expr_6_in_0: (uint8-109)
        // 5.509 Q8
        // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_6_in_1, int32), [225]), [2]), Norm(Mul(Sub(Cast(expr_6_in_0, int32), [109]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_6_in_0, int32), [176]), [1]), [9592]), SigmoidLUTTable)), [8])), [208]), [14]), [-21]), 0, 255), uint8)
        // scale clip and cast - (int32-1631) 705.128 Q22 -> (uint8-42) 1.696 Q7
        expr_6_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((((int)expr_6_in_1[i0])*(225)), ((unsigned char)2))+gap_roundnorm_reg(((((int)expr_6_in_0[i0])-(109))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_6_in_0[i0])*(176)), ((unsigned char)1))-(9592)), SigmoidLUTTable)), (8)))*(208)), ((unsigned char)14))-(-21))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 3 external iteration spaces
void s206_kernel(s206_kernel_args_t * __restrict__ Args) {
    unsigned int I0 = Args->I0;
    unsigned int I1 = Args->I1;
    unsigned int I2 = Args->I2;
    unsigned short int *__restrict__  SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 1, 256) 
    unsigned char *__restrict__  expr_32_in_0 = Args->expr_32_in_0; // (1, 36, 3, 2)  (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_32_in_1 = Args->expr_32_in_1; // (1, 1, 3, 2)   int8 264.567 Q7
    signed char *__restrict__  expr_32_in_2 = Args->expr_32_in_2; // (1, 1, 1, 2)   int8 0.005 Q7
    unsigned char *__restrict__  expr_32_out_0 = Args->expr_32_out_0; // (1, 36, 3, 2)  uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 36, 3, 2) var shapes:
    // inter_LOGISTIC_0_190: (1, 36, 3, 2) expr_32_in_0: (1, 36, 3, 2)
    // expr_32_out_0: (1, 36, 3, 2) expr_32_in_1: (1, 1, 3, 2) expr_32_in_2:
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
            // 264.567 Q7 expr_32_in_2: int8 0.005 Q7
            // expr_32_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_190), Cast(expr_32_in_1, int32)), [7]), Cast(expr_32_in_2, int32)), [177]), [21]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_190 = inter_LOGISTIC_0_190;
            // scale clip and cast - int32 1.389 Q15 -> uint8 1.004 Q8
            expr_32_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_190)*((int)expr_32_in_1[(i1*I2)+i2])), (7))*((int)expr_32_in_2[i2]))*(177)), ((unsigned char)21))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_34_in_0 = Args->expr_34_in_0; // (1, 144, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_34_in_1 = Args->expr_34_in_1; // (1, 1, 3, 2)   int8 83.591 Q7
    signed char *__restrict__  expr_34_in_2 = Args->expr_34_in_2; // (1, 1, 1, 2)   int8 0.005 Q7
    unsigned char *__restrict__  expr_34_out_0 = Args->expr_34_out_0; // (1, 144, 3, 2) (uint8-128) 2.032 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 144, 3, 2) var shapes:
    // inter_LOGISTIC_0_207: (1, 144, 3, 2) expr_34_in_0: (1, 144, 3, 2)
    // expr_34_out_0: (1, 144, 3, 2) expr_34_in_1: (1, 1, 3, 2) expr_34_in_2:
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
            // 83.591 Q7 expr_34_in_2: int8 0.005 Q7
            // expr_34_out_0 = Cast(Clip(Sub(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_207), Cast(expr_34_in_1, int32)), [7]), Cast(expr_34_in_2, int32)), [221]), [24]), [-128]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_207 = inter_LOGISTIC_0_207;
            // scale clip and cast - int32 0.439 Q15 -> (uint8-128) 2.032 Q8
            expr_34_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu(((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_207)*((int)expr_34_in_1[(i1*I2)+i2])), (7))*((int)expr_34_in_2[i2]))*(221)), ((unsigned char)24))-(-128))), (((signed char)8))));
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
    unsigned char *__restrict__  expr_35_in_0 = Args->expr_35_in_0; // (1, 576, 3, 2) (uint8-128) 12.578 Q8
    signed char *__restrict__  expr_35_in_1 = Args->expr_35_in_1; // (1, 1, 3, 2)   int8 34.551 Q7
    signed char *__restrict__  expr_35_in_2 = Args->expr_35_in_2; // (1, 1, 1, 2)   int8 0.005 Q7
    unsigned char *__restrict__  expr_35_out_0 = Args->expr_35_out_0; // (1, 576, 3, 2) uint8 1.004 Q8
    unsigned int CoreId = gap_coreid();
    unsigned int Chunk = ChunkSize(I1);
    unsigned int First = Chunk*CoreId;
    unsigned int Last = gap_min(First+Chunk, I1);
    // Max shape: (1, 576, 3, 2) var shapes:
    // inter_LOGISTIC_0_224: (1, 576, 3, 2) expr_35_in_0: (1, 576, 3, 2)
    // expr_35_out_0: (1, 576, 3, 2) expr_35_in_1: (1, 1, 3, 2) expr_35_in_2:
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
            // 34.551 Q7 expr_35_in_2: int8 0.005 Q7
            // expr_35_out_0 = Cast(Clip(Norm(Mul(Mul(Norm(Mul(Square1715(inter_LOGISTIC_0_224), Cast(expr_35_in_1, int32)), [7]), Cast(expr_35_in_2, int32)), [185]), [24]), 0, 255), uint8)
            int _SYMBOL_inter_LOGISTIC_0_224 = inter_LOGISTIC_0_224;
            // scale clip and cast - int32 0.181 Q15 -> uint8 1.004 Q8
            expr_35_out_0[(i1*I2)+i2] = ((unsigned char)gap_clipu((gap_roundnorm_reg(((gap_roundnorm_reg((square_17_15(_SYMBOL_inter_LOGISTIC_0_224)*((int)expr_35_in_1[(i1*I2)+i2])), (7))*((int)expr_35_in_2[i2]))*(185)), ((unsigned char)24))), (((signed char)8))));
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
    // Max shape: (96, 96, 8) var shapes:
    // expr_33_out_0: (96, 96, 8) expr_33_in_0: (96, 96, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_33_in_0: (uint8-146) 68.020 Q8
        // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [146]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_33_in_0, int32), [136]), [3]), [158848]), -65536, 65535), SigmoidLUTTable)), [8]), [148]), [13]), [-2]), 0, 255), uint8)
        // scale clip and cast - int32 68.020 Q15 -> (uint8-2) 14.733 Q7
        expr_33_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0])-(146))*SigmoidTableInline(gap_clip(((((((int)expr_33_in_0[i0])*(136))<<((unsigned char)3))-(158848))), (((signed char)16))), SigmoidLUTTable)), (8))*(148)), ((unsigned char)13))-(-2))), (((signed char)8))));
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
    // Max shape: (48, 48, 16) var shapes:
    // expr_45_out_0: (48, 48, 16) expr_45_in_0: (48, 48, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_45_in_0: (uint8-121) 38.594 Q8
        // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [121]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [154]), [2]), [74536]), -65536, 65535), SigmoidLUTTable)), [8]), [240]), [14]), [-3]), 0, 255), uint8)
        // scale clip and cast - int32 38.594 Q15 -> (uint8-3) 10.309 Q7
        expr_45_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_45_in_0[i0])-(121))*SigmoidTableInline(gap_clip(((((((int)expr_45_in_0[i0])*(154))<<((unsigned char)2))-(74536))), (((signed char)16))), SigmoidLUTTable)), (8))*(240)), ((unsigned char)14))-(-3))), (((signed char)8))));
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
    // Max shape: (48, 48, 16) var shapes:
    // expr_31_out_0: (48, 48, 16) expr_31_in_0: (48, 48, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_31_in_0: (uint8-183) 22.843 Q8
        // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [183]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [183]), [1]), [66978]), -65536, 65535), SigmoidLUTTable)), [8]), [219]), [13]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 22.843 Q15 -> (uint8-11) 3.344 Q7
        expr_31_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_31_in_0[i0])-(183))*SigmoidTableInline(gap_clip(((((((int)expr_31_in_0[i0])*(183))<<((unsigned char)1))-(66978))), (((signed char)16))), SigmoidLUTTable)), (8))*(219)), ((unsigned char)13))-(-11))), (((signed char)8))));
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
    // Max shape: (48, 48, 8) var shapes:
    // expr_13_out_0: (48, 48, 8) expr_13_in_0: (48, 48, 8) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_13_in_0: (uint8-133) 11.929 Q8
        // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [133]), SigmoidLUT(Sub(Mul(Cast(expr_13_in_0, int32), [191]), [25403]), SigmoidLUTTable)), [8]), [256]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 11.929 Q15 -> (uint8-12) 2.984 Q7
        expr_13_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_13_in_0[i0])-(133))*SigmoidTableInline(((((int)expr_13_in_0[i0])*(191))-(25403)), SigmoidLUTTable)), (8))*(256)), ((unsigned char)14))-(-12))), (((signed char)8))));
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
    // Max shape: (48, 48, 16) var shapes:
    // expr_36_out_0: (48, 48, 16) expr_36_in_0: (48, 48, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_36_in_0: (uint8-132) 12.097 Q8
        // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [132]), SigmoidLUT(Sub(Mul(Cast(expr_36_in_0, int32), [194]), [25608]), SigmoidLUTTable)), [8]), [254]), [14]), [-12]), 0, 255), uint8)
        // scale clip and cast - int32 12.097 Q15 -> (uint8-12) 3.043 Q7
        expr_36_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_36_in_0[i0])-(132))*SigmoidTableInline(((((int)expr_36_in_0[i0])*(194))-(25608)), SigmoidLUTTable)), (8))*(254)), ((unsigned char)14))-(-12))), (((signed char)8))));
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
    // Max shape: (24, 24, 32) var shapes:
    // expr_37_out_0: (24, 24, 32) expr_37_in_0: (24, 24, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_37_in_0: (uint8-136) 10.583 Q8
        // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [136]), SigmoidLUT(Sub(Mul(Cast(expr_37_in_0, int32), [169]), [22984]), SigmoidLUTTable)), [8]), [131]), [13]), [-14]), 0, 255), uint8)
        // scale clip and cast - int32 10.583 Q15 -> (uint8-14) 2.589 Q7
        expr_37_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_37_in_0[i0])-(136))*SigmoidTableInline(((((int)expr_37_in_0[i0])*(169))-(22984)), SigmoidLUTTable)), (8))*(131)), ((unsigned char)13))-(-14))), (((signed char)8))));
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
    // Max shape: (24, 24, 32) var shapes:
    // expr_38_out_0: (24, 24, 32) expr_38_in_0: (24, 24, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_38_in_0: (uint8-112) 11.555 Q8
        // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [112]), SigmoidLUT(Sub(Mul(Cast(expr_38_in_0, int32), [185]), [20720]), SigmoidLUTTable)), [8]), [219]), [14]), [-11]), 0, 255), uint8)
        // scale clip and cast - int32 11.555 Q15 -> (uint8-11) 3.381 Q7
        expr_38_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_38_in_0[i0])-(112))*SigmoidTableInline(((((int)expr_38_in_0[i0])*(185))-(20720)), SigmoidLUTTable)), (8))*(219)), ((unsigned char)14))-(-11))), (((signed char)8))));
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
    // Max shape: (24, 24, 16) var shapes:
    // expr_39_out_0: (24, 24, 16) expr_39_in_0: (24, 24, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_39_in_0: (uint8-109) 8.054 Q8
        // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [109]), SigmoidLUT(Sub(Mul(Cast(expr_39_in_0, int32), [129]), [14061]), SigmoidLUTTable)), [8]), [212]), [14]), [-15]), 0, 255), uint8)
        // scale clip and cast - int32 8.054 Q15 -> (uint8-15) 2.429 Q7
        expr_39_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_39_in_0[i0])-(109))*SigmoidTableInline(((((int)expr_39_in_0[i0])*(129))-(14061)), SigmoidLUTTable)), (8))*(212)), ((unsigned char)14))-(-15))), (((signed char)8))));
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
    // Max shape: (24, 24, 32) var shapes:
    // expr_41_out_0: (24, 24, 32) expr_41_in_0: (24, 24, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_41_in_0: (uint8-153) 7.943 Q8
        // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [153]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_41_in_0, int32), [254]), [1]), [19431]), SigmoidLUTTable)), [8]), [153]), [13]), [-21]), 0, 255), uint8)
        // scale clip and cast - int32 7.943 Q15 -> (uint8-21) 1.663 Q7
        expr_41_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0])-(153))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_41_in_0[i0])*(254)), ((unsigned char)1))-(19431)), SigmoidLUTTable)), (8))*(153)), ((unsigned char)13))-(-21))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_42_out_0: (12, 12, 56) expr_42_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_42_in_0: (uint8-145) 7.198 Q8
        // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [145]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_42_in_0, int32), [230]), [1]), [16675]), SigmoidLUTTable)), [8]), [141]), [13]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 7.198 Q15 -> (uint8-22) 1.630 Q7
        expr_42_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_42_in_0[i0])-(145))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_42_in_0[i0])*(230)), ((unsigned char)1))-(16675)), SigmoidLUTTable)), (8))*(141)), ((unsigned char)13))-(-22))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_43_out_0: (12, 12, 56) expr_43_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_43_in_0: (uint8-134) 6.067 Q8
        // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [134]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_43_in_0, int32), [194]), [1]), [12998]), SigmoidLUTTable)), [8]), [129]), [13]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 6.067 Q15 -> (uint8-24) 1.503 Q7
        expr_43_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_43_in_0[i0])-(134))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_43_in_0[i0])*(194)), ((unsigned char)1))-(12998)), SigmoidLUTTable)), (8))*(129)), ((unsigned char)13))-(-24))), (((signed char)8))));
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
    // Max shape: (12, 12, 28) var shapes:
    // expr_44_out_0: (12, 12, 28) expr_44_in_0: (12, 12, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_44_in_0: (uint8-145) 5.965 Q8
        // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [145]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_44_in_0, int32), [191]), [1]), [13848]), SigmoidLUTTable)), [8]), [143]), [13]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 5.965 Q15 -> (uint8-27) 1.335 Q7
        expr_44_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_44_in_0[i0])-(145))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_44_in_0[i0])*(191)), ((unsigned char)1))-(13848)), SigmoidLUTTable)), (8))*(143)), ((unsigned char)13))-(-27))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_47_out_0: (12, 12, 56) expr_47_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_47_in_0: (uint8-131) 5.247 Q8
        // expr_47_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_47_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_47_in_0, int32), [168]), [1]), [11004]), SigmoidLUTTable)), [8]), [253]), [14]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 5.247 Q15 -> (uint8-27) 1.328 Q7
        expr_47_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_47_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_47_in_0[i0])*(168)), ((unsigned char)1))-(11004)), SigmoidLUTTable)), (8))*(253)), ((unsigned char)14))-(-27))), (((signed char)8))));
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
    // Max shape: (6, 6, 104) var shapes:
    // expr_48_out_0: (6, 6, 104) expr_48_in_0: (6, 6, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_48_in_0: (uint8-136) 5.163 Q8
        // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [136]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_48_in_0, int32), [165]), [1]), [11220]), SigmoidLUTTable)), [8]), [133]), [13]), [-29]), 0, 255), uint8)
        // scale clip and cast - int32 5.163 Q15 -> (uint8-29) 1.242 Q7
        expr_48_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_48_in_0[i0])-(136))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_48_in_0[i0])*(165)), ((unsigned char)1))-(11220)), SigmoidLUTTable)), (8))*(133)), ((unsigned char)13))-(-29))), (((signed char)8))));
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
    // Max shape: (6, 6, 104) var shapes:
    // expr_49_out_0: (6, 6, 104) expr_49_in_0: (6, 6, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_49_in_0: (uint8-116) 4.303 Q8
        // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_49_in_0, int32), [138]), [1]), [8004]), SigmoidLUTTable)), [8]), [227]), [14]), [-29]), 0, 255), uint8)
        // scale clip and cast - int32 4.303 Q15 -> (uint8-29) 1.213 Q7
        expr_49_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_49_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_49_in_0[i0])*(138)), ((unsigned char)1))-(8004)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-29))), (((signed char)8))));
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
    // Max shape: (6, 6, 52) var shapes:
    // expr_50_out_0: (6, 6, 52) expr_50_in_0: (6, 6, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_50_in_0: (uint8-117) 5.135 Q8
        // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [117]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_50_in_0, int32), [164]), [1]), [9594]), SigmoidLUTTable)), [8]), [227]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.135 Q15 -> (uint8-25) 1.448 Q7
        expr_50_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_50_in_0[i0])-(117))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_50_in_0[i0])*(164)), ((unsigned char)1))-(9594)), SigmoidLUTTable)), (8))*(227)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (6, 6, 104) var shapes:
    // expr_52_out_0: (6, 6, 104) expr_52_in_0: (6, 6, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_52_in_0: (uint8-126) 5.190 Q8
        // expr_52_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_52_in_0, int32), [126]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_52_in_0, int32), [166]), [1]), [10458]), SigmoidLUTTable)), [8]), [244]), [14]), [-26]), 0, 255), uint8)
        // scale clip and cast - int32 5.190 Q15 -> (uint8-26) 1.359 Q7
        expr_52_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_52_in_0[i0])-(126))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_52_in_0[i0])*(166)), ((unsigned char)1))-(10458)), SigmoidLUTTable)), (8))*(244)), ((unsigned char)14))-(-26))), (((signed char)8))));
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
    // Max shape: (6, 6, 52) var shapes:
    // expr_53_out_0: (6, 6, 52) expr_53_in_0: (6, 6, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_53_in_0: (uint8-106) 5.344 Q8
        // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [106]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_53_in_0, int32), [171]), [1]), [9063]), SigmoidLUTTable)), [8]), [209]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 5.344 Q15 -> (uint8-22) 1.638 Q7
        expr_53_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_53_in_0[i0])-(106))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_53_in_0[i0])*(171)), ((unsigned char)1))-(9063)), SigmoidLUTTable)), (8))*(209)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (6, 6, 104) var shapes:
    // expr_55_out_0: (6, 6, 104) expr_55_in_0: (6, 6, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_55_in_0: (uint8-126) 6.788 Q8
        // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [126]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_55_in_0, int32), [217]), [1]), [13671]), SigmoidLUTTable)), [8]), [240]), [14]), [-20]), 0, 255), uint8)
        // scale clip and cast - int32 6.788 Q15 -> (uint8-20) 1.806 Q7
        expr_55_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_55_in_0[i0])-(126))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_55_in_0[i0])*(217)), ((unsigned char)1))-(13671)), SigmoidLUTTable)), (8))*(240)), ((unsigned char)14))-(-20))), (((signed char)8))));
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
    // Max shape: (6, 6, 56) var shapes:
    // expr_56_out_0: (6, 6, 56) expr_56_in_0: (6, 6, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_56_in_0: (uint8-116) 3.710 Q8
        // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [116]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_56_in_0, int32), [237]), [2]), [6873]), SigmoidLUTTable)), [8]), [229]), [14]), [-34]), 0, 255), uint8)
        // scale clip and cast - int32 3.710 Q15 -> (uint8-34) 1.035 Q7
        expr_56_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_56_in_0[i0])-(116))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_56_in_0[i0])*(237)), ((unsigned char)2))-(6873)), SigmoidLUTTable)), (8))*(229)), ((unsigned char)14))-(-34))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_10_out_0: (12, 12, 56) expr_10_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_10_in_0: (uint8-139) 5.715 Q8
        // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [139]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_10_in_0, int32), [183]), [1]), [12719]), SigmoidLUTTable)), [8]), [136]), [13]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 5.715 Q15 -> (uint8-27) 1.344 Q7
        expr_10_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_10_in_0[i0])-(139))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_10_in_0[i0])*(183)), ((unsigned char)1))-(12719)), SigmoidLUTTable)), (8))*(136)), ((unsigned char)13))-(-27))), (((signed char)8))));
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
    // Max shape: (12, 12, 28) var shapes:
    // expr_8_out_0: (12, 12, 28) expr_8_in_0: (12, 12, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_8_in_0: (uint8-128) 5.417 Q8
        // expr_8_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Cast(Cast(Add(expr_8_in_0, [128]), int8), int32), SigmoidLUT(Sub(Norm(Mul(Cast(expr_8_in_0, int32), [173]), [1]), [11072]), SigmoidLUTTable)), [8]), [246]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 5.417 Q15 -> (uint8-25) 1.409 Q7
        expr_8_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg((((int)((signed char)(expr_8_in_0[i0]+((unsigned char)128))))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_8_in_0[i0])*(173)), ((unsigned char)1))-(11072)), SigmoidLUTTable)), (8))*(246)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (12, 12, 28) var shapes:
    // expr_9_out_0: (12, 12, 28) expr_9_in_0: (12, 12, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_9_in_0: (uint8-125) 4.090 Q8
        // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [125]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_9_in_0, int32), [131]), [1]), [8188]), SigmoidLUTTable)), [8]), [195]), [14]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 4.090 Q15 -> (uint8-27) 2.688 Q8
        expr_9_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_9_in_0[i0])-(125))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_9_in_0[i0])*(131)), ((unsigned char)1))-(8188)), SigmoidLUTTable)), (8))*(195)), ((unsigned char)14))-(-27))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_11_out_0: (12, 12, 56) expr_11_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_11_in_0: (uint8-105) 4.931 Q8
        // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [105]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_11_in_0, int32), [158]), [1]), [8295]), SigmoidLUTTable)), [8]), [208]), [14]), [-24]), 0, 255), uint8)
        // scale clip and cast - int32 4.931 Q15 -> (uint8-24) 1.515 Q7
        expr_11_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_11_in_0[i0])-(105))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_11_in_0[i0])*(158)), ((unsigned char)1))-(8295)), SigmoidLUTTable)), (8))*(208)), ((unsigned char)14))-(-24))), (((signed char)8))));
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
    // Max shape: (12, 12, 32) var shapes:
    // expr_12_out_0: (12, 12, 32) expr_12_in_0: (12, 12, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_12_in_0: (uint8-113) 4.643 Q8
        // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [113]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_12_in_0, int32), [149]), [1]), [8419]), SigmoidLUTTable)), [8]), [221]), [14]), [-27]), 0, 255), uint8)
        // scale clip and cast - int32 4.643 Q15 -> (uint8-27) 1.344 Q7
        expr_12_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_12_in_0[i0])-(113))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_12_in_0[i0])*(149)), ((unsigned char)1))-(8419)), SigmoidLUTTable)), (8))*(221)), ((unsigned char)14))-(-27))), (((signed char)8))));
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
    // Max shape: (24, 24, 32) var shapes:
    // expr_14_out_0: (24, 24, 32) expr_14_in_0: (24, 24, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_14_in_0: (uint8-143) 5.159 Q8
        // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [143]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_14_in_0, int32), [165]), [1]), [11798]), SigmoidLUTTable)), [8]), [142]), [13]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 5.159 Q15 -> (uint8-31) 1.161 Q7
        expr_14_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_14_in_0[i0])-(143))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_14_in_0[i0])*(165)), ((unsigned char)1))-(11798)), SigmoidLUTTable)), (8))*(142)), ((unsigned char)13))-(-31))), (((signed char)8))));
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
    // Max shape: (24, 24, 16) var shapes:
    // expr_15_out_0: (24, 24, 16) expr_15_in_0: (24, 24, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_15_in_0: (uint8-135) 4.442 Q8
        // expr_15_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_15_in_0, int32), [135]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_15_in_0, int32), [142]), [1]), [9585]), SigmoidLUTTable)), [8]), [133]), [13]), [-33]), 0, 255), uint8)
        // scale clip and cast - int32 4.442 Q15 -> (uint8-33) 1.070 Q7
        expr_15_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_15_in_0[i0])-(135))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_15_in_0[i0])*(142)), ((unsigned char)1))-(9585)), SigmoidLUTTable)), (8))*(133)), ((unsigned char)13))-(-33))), (((signed char)8))));
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
    // Max shape: (24, 24, 16) var shapes:
    // expr_16_out_0: (24, 24, 16) expr_16_in_0: (24, 24, 16) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_16_in_0: (uint8-138) 4.860 Q8
        // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [138]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_16_in_0, int32), [156]), [1]), [10764]), SigmoidLUTTable)), [8]), [134]), [13]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 4.860 Q15 -> (uint8-31) 2.322 Q8
        expr_16_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_16_in_0[i0])-(138))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_16_in_0[i0])*(156)), ((unsigned char)1))-(10764)), SigmoidLUTTable)), (8))*(134)), ((unsigned char)13))-(-31))), (((signed char)8))));
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
    // Max shape: (24, 24, 32) var shapes:
    // expr_18_out_0: (24, 24, 32) expr_18_in_0: (24, 24, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_18_in_0: (uint8-111) 6.250 Q8
        // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [111]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_18_in_0, int32), [200]), [1]), [11100]), SigmoidLUTTable)), [8]), [216]), [14]), [-19]), 0, 255), uint8)
        // scale clip and cast - int32 6.250 Q15 -> (uint8-19) 1.855 Q7
        expr_18_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_18_in_0[i0])-(111))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_18_in_0[i0])*(200)), ((unsigned char)1))-(11100)), SigmoidLUTTable)), (8))*(216)), ((unsigned char)14))-(-19))), (((signed char)8))));
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
    // Max shape: (12, 12, 32) var shapes:
    // expr_19_out_0: (12, 12, 32) expr_19_in_0: (12, 12, 32) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_19_in_0: (uint8-105) 4.793 Q8
        // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [105]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_19_in_0, int32), [153]), [1]), [8033]), SigmoidLUTTable)), [8]), [208]), [14]), [-25]), 0, 255), uint8)
        // scale clip and cast - int32 4.793 Q15 -> (uint8-25) 2.949 Q8
        expr_19_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_19_in_0[i0])-(105))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_19_in_0[i0])*(153)), ((unsigned char)1))-(8033)), SigmoidLUTTable)), (8))*(208)), ((unsigned char)14))-(-25))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_20_out_0: (12, 12, 56) expr_20_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_20_in_0: (uint8-131) 4.604 Q8
        // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_20_in_0, int32), [131]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_20_in_0, int32), [147]), [1]), [9629]), SigmoidLUTTable)), [8]), [128]), [13]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 4.604 Q15 -> (uint8-31) 1.147 Q7
        expr_20_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_20_in_0[i0])-(131))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_20_in_0[i0])*(147)), ((unsigned char)1))-(9629)), SigmoidLUTTable)), (8))*(128)), ((unsigned char)13))-(-31))), (((signed char)8))));
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
    // Max shape: (12, 12, 28) var shapes:
    // expr_21_out_0: (12, 12, 28) expr_21_in_0: (12, 12, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_21_in_0: (uint8-125) 4.088 Q8
        // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [125]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_21_in_0, int32), [131]), [1]), [8188]), SigmoidLUTTable)), [8]), [245]), [14]), [-33]), 0, 255), uint8)
        // scale clip and cast - int32 4.088 Q15 -> (uint8-33) 1.070 Q7
        expr_21_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_21_in_0[i0])-(125))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_21_in_0[i0])*(131)), ((unsigned char)1))-(8188)), SigmoidLUTTable)), (8))*(245)), ((unsigned char)14))-(-33))), (((signed char)8))));
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
    // Max shape: (12, 12, 28) var shapes:
    // expr_22_out_0: (12, 12, 28) expr_22_in_0: (12, 12, 28) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_22_in_0: (uint8-108) 2.990 Q8
        // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [108]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_22_in_0, int32), [191]), [2]), [5157]), SigmoidLUTTable)), [8]), [167]), [14]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 2.990 Q15 -> (uint8-31) 2.295 Q8
        expr_22_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_22_in_0[i0])-(108))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_22_in_0[i0])*(191)), ((unsigned char)2))-(5157)), SigmoidLUTTable)), (8))*(167)), ((unsigned char)14))-(-31))), (((signed char)8))));
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
    // Max shape: (12, 12, 56) var shapes:
    // expr_24_out_0: (12, 12, 56) expr_24_in_0: (12, 12, 56) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_24_in_0: (uint8-108) 5.454 Q8
        // expr_24_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_24_in_0, int32), [108]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_24_in_0, int32), [175]), [1]), [9450]), SigmoidLUTTable)), [8]), [211]), [14]), [-22]), 0, 255), uint8)
        // scale clip and cast - int32 5.454 Q15 -> (uint8-22) 1.651 Q7
        expr_24_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_24_in_0[i0])-(108))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_24_in_0[i0])*(175)), ((unsigned char)1))-(9450)), SigmoidLUTTable)), (8))*(211)), ((unsigned char)14))-(-22))), (((signed char)8))));
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
    // Max shape: (6, 6, 56) var shapes:
    // expr_25_out_0: (6, 6, 56) expr_25_in_0: (6, 6, 56) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_25_in_0: (uint8-95) 3.421 Q8
        // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [95]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_25_in_0, int32), [219]), [2]), [5201]), SigmoidLUTTable)), [8]), [199]), [14]), [-32]), 0, 255), uint8)
        // scale clip and cast - int32 3.421 Q15 -> (uint8-32) 1.100 Q7
        expr_25_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_25_in_0[i0])-(95))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_25_in_0[i0])*(219)), ((unsigned char)2))-(5201)), SigmoidLUTTable)), (8))*(199)), ((unsigned char)14))-(-32))), (((signed char)8))));
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
    // Max shape: (6, 6, 104) var shapes:
    // expr_26_out_0: (6, 6, 104) expr_26_in_0: (6, 6, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_26_in_0: (uint8-121) 3.430 Q8
        // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [121]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_26_in_0, int32), [220]), [2]), [6655]), SigmoidLUTTable)), [8]), [241]), [14]), [-39]), 0, 255), uint8)
        // scale clip and cast - int32 3.430 Q15 -> (uint8-39) 0.910 Q7
        expr_26_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_26_in_0[i0])-(121))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_26_in_0[i0])*(220)), ((unsigned char)2))-(6655)), SigmoidLUTTable)), (8))*(241)), ((unsigned char)14))-(-39))), (((signed char)8))));
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
    // Max shape: (6, 6, 52) var shapes:
    // expr_27_out_0: (6, 6, 52) expr_27_in_0: (6, 6, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_27_in_0: (uint8-104) 3.475 Q8
        // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [104]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_27_in_0, int32), [222]), [2]), [5772]), SigmoidLUTTable)), [8]), [212]), [14]), [-34]), 0, 255), uint8)
        // scale clip and cast - int32 3.475 Q15 -> (uint8-34) 1.049 Q7
        expr_27_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_27_in_0[i0])-(104))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_27_in_0[i0])*(222)), ((unsigned char)2))-(5772)), SigmoidLUTTable)), (8))*(212)), ((unsigned char)14))-(-34))), (((signed char)8))));
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
    // Max shape: (6, 6, 52) var shapes:
    // expr_28_out_0: (6, 6, 52) expr_28_in_0: (6, 6, 52) SigmoidLUTTable: (1,
    // 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_28_in_0: (uint8-99) 2.775 Q8
        // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [99]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_28_in_0, int32), [178]), [2]), [4406]), SigmoidLUTTable)), [8]), [195]), [14]), [-39]), 0, 255), uint8)
        // scale clip and cast - int32 2.775 Q15 -> (uint8-39) 1.819 Q8
        expr_28_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0])-(99))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_28_in_0[i0])*(178)), ((unsigned char)2))-(4406)), SigmoidLUTTable)), (8))*(195)), ((unsigned char)14))-(-39))), (((signed char)8))));
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
    // Max shape: (6, 6, 104) var shapes:
    // expr_30_out_0: (6, 6, 104) expr_30_in_0: (6, 6, 104) SigmoidLUTTable:
    // (1, 1, 256)
    // Iteration reduced to spaces ((0, 1, 2),)
    // Fixed spaces ()
    // Parameteric spaces ((0, 1, 2),)
    // Paralelized space (0, 1, 2)
    // Interior spaces ()
    for (int i0=First; i0<Last; i0++) {
        // inputs expr_30_in_0: (uint8-126) 4.439 Q8
        // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [126]), SigmoidLUT(Sub(Norm(Mul(Cast(expr_30_in_0, int32), [142]), [1]), [8946]), SigmoidLUTTable)), [8]), [246]), [14]), [-31]), 0, 255), uint8)
        // scale clip and cast - int32 4.439 Q15 -> (uint8-31) 1.155 Q7
        expr_30_out_0[i0] = ((unsigned char)gap_clipu(((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_30_in_0[i0])-(126))*SigmoidTableInline((gap_roundnorm_reg((((int)expr_30_in_0[i0])*(142)), ((unsigned char)1))-(8946)), SigmoidLUTTable)), (8))*(246)), ((unsigned char)14))-(-31))), (((signed char)8))));
    }
    gap_waitbarrier(0);
}


#pragma GCC diagnostic pop