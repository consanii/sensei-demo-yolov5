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

  if (CoreCountDynamic)
    NCore = ActiveCore;
  else
    NCore = gap_ncore();
  Log2Core = gap_fl1(NCore);
  Chunk = (X >> Log2Core) + ((X & (NCore - 1)) != 0);
  return Chunk;
}

#ifndef AT_NORM
#define AT_NORM(x, n) gap_roundnorm_reg((x), (n))
#endif
#define ATLShift(x, n) ((x) << (n))

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s18_kernel(s18_kernel_args_t *__restrict__ Args) {
  unsigned int I0 = Args->I0;
  unsigned short int *__restrict__ SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)
  unsigned char *__restrict__ expr_0_in_0 = Args->expr_0_in_0;              // (64, 64, 8) (uint8-122) 58.346 Q8
  unsigned char *__restrict__ expr_0_in_1 = Args->expr_0_in_1;              // (64, 64, 8) (uint8-2) 32.837 Q8
  unsigned char *__restrict__ expr_0_out_0 = Args->expr_0_out_0;            // (64, 64, 8) (uint8-4) 19.020 Q7
  unsigned int CoreId = gap_coreid();
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (64, 64, 8) var shapes:
  // expr_0_out_0: (64, 64, 8) expr_0_in_1: (64, 64, 8) expr_0_in_0: (64, 64,
  // 8) SigmoidLUTTable: (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_0_in_1: (uint8-2) 32.837 Q8 expr_0_in_0: (uint8-122)
    // 58.346 Q8
    // expr_0_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Cast(expr_0_in_1, int32), Norm(Mul(Norm(Mul(Sub(Cast(expr_0_in_0,
    // int32), [122]), SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_0_in_0, int32), [233]), [2]), [113704]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [227]), [14])), [221]), [8]), [-2]), 0, 255), uint8) ADD_0_20 scale arg 0 (no zp adj) -
    // (uint8-2) 32.837 Q8 -> (int32-2) 32.837 Q8
    int _SYMBOL_Cast12 = ((int)expr_0_in_1[i0]);
    // scale clip and cast - (int32-2) 65.673 Q9 -> (uint8-4) 19.020 Q7
    expr_0_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              ((_SYMBOL_Cast12 +
                gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_0_in_0[i0]) - (122)) *
                                                      SigmoidTableInline(gap_clip(((((((int)expr_0_in_0[i0]) * (233))
                                                                                     << ((unsigned char)2)) -
                                                                                    (113704))),
                                                                                  (((signed char)16))),
                                                                         SigmoidLUTTable)),
                                                     (8)) *
                                   (227)),
                                  ((unsigned char)14))) *
               (221)),
              ((unsigned char)8)) -
          (-2))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s255_kernel(s255_kernel_args_t *__restrict__ Args) {
  unsigned int I0 = Args->I0;
  signed char *__restrict__ expr_1_in_0 = Args->expr_1_in_0;   // (2, 1, 1344) int8 31.748 Q7
  unsigned char *__restrict__ expr_1_in_1 = Args->expr_1_in_1; // (2, 1, 1344) uint8 12.600 Q8
  unsigned char *__restrict__ expr_1_in_2 = Args->expr_1_in_2; // (2, 1, 1344) uint8 12.600 Q8
  signed char *__restrict__ expr_1_in_3 = Args->expr_1_in_3;   // (2, 1, 1344) int8 31.748 Q7
  signed char *__restrict__ expr_1_out_0 = Args->expr_1_out_0; // (2, 1, 1344) (int8--128) 15.894 Q7
  signed char *__restrict__ expr_1_out_1 = Args->expr_1_out_1; // (2, 1, 1344) (int8--128) 15.894 Q7
  unsigned int CoreId = gap_coreid();
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (2, 1, 1344) var shapes:
  // inter_SUB_0_245: (2, 1, 1344) expr_1_in_0: (2, 1, 1344) expr_1_in_1: (2,
  // 1, 1344) inter_ADD_0_247: (2, 1, 1344) expr_1_in_2: (2, 1, 1344)
  // expr_1_in_3: (2, 1, 1344) expr_1_out_0: (2, 1, 1344) expr_1_out_1: (2,
  // 1, 1344)
  // Iteration reduced to spaces ((0, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 2),)
  // Paralelized space (0, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_1_in_0: int8 31.748 Q7 expr_1_in_1: uint8 12.600 Q8
    // inter_SUB_0_245 = Sub(Norm(Mul(Cast(expr_1_in_0, int32), [161]), [5]), Cast(expr_1_in_1, int32))
    // SUB_0_245 scale arg 1 (equalize zp adj) - uint8 12.600 Q8 -> int32 12.600 Q8
    int _SYMBOL_Cast182 = ((int)expr_1_in_1[i0]);
    int inter_SUB_0_245 = (gap_roundnorm_reg((((int)expr_1_in_0[i0]) * (161)), ((unsigned char)5)) - _SYMBOL_Cast182);
    // inputs expr_1_in_2: uint8 12.600 Q8 expr_1_in_3: int8 31.748 Q7
    // inter_ADD_0_247 = Add(Cast(expr_1_in_2, int32), Norm(Mul(Cast(expr_1_in_3, int32), [161]), [5]))
    // ADD_0_247 scale arg 0 (equalize zp adj) - uint8 12.600 Q8 -> int32 12.600 Q8
    int _SYMBOL_Cast183 = ((int)expr_1_in_2[i0]);
    int inter_ADD_0_247 = (_SYMBOL_Cast183 + gap_roundnorm_reg((((int)expr_1_in_3[i0]) * (161)), ((unsigned char)5)));
    // inputs inter_ADD_0_247: int32 25.200 Q9 inter_SUB_0_245: int32
    // 25.200 Q9
    // expr_1_out_0 = Cast(Clip(Sub(Norm(Mul(Sub(inter_ADD_0_247, inter_SUB_0_245), [203]), [9]), [128]), -128, 127),
    // int8) scale clip and cast - int32 50.401 Q10 -> (int8--128) 15.894 Q7
    expr_1_out_0[i0] = ((signed char)gap_clip(
        ((gap_roundnorm_reg(((inter_ADD_0_247 - inter_SUB_0_245) * (203)), ((unsigned char)9)) - (128))),
        (((signed char)7))));
    // inputs inter_SUB_0_245: int32 25.200 Q9 inter_ADD_0_247: int32
    // 25.200 Q9
    // expr_1_out_1 = Cast(Clip(Sub(Norm(Mul(Mul(Add(inter_SUB_0_245, inter_ADD_0_247), [1]), [203]), [10]), [128]),
    // -128, 127), int8) scale clip and cast - int32 25.200 Q10 -> (int8--128) 15.894 Q7
    expr_1_out_1[i0] = ((signed char)gap_clip(
        ((gap_roundnorm_reg((((inter_SUB_0_245 + inter_ADD_0_247) * (1)) * (203)), ((unsigned char)10)) - (128))),
        (((signed char)7))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s37_kernel(s37_kernel_args_t *__restrict__ Args) {
  unsigned int I0 = Args->I0;
  unsigned short int *__restrict__ SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)
  unsigned char *__restrict__ expr_2_in_0 = Args->expr_2_in_0;              // (32, 32, 16) (uint8-117) 19.005 Q8
  unsigned char *__restrict__ expr_2_in_1 = Args->expr_2_in_1;              // (32, 32, 16) (uint8-9) 7.573 Q8
  unsigned char *__restrict__ expr_2_out_0 = Args->expr_2_out_0;            // (32, 32, 16) (uint8-12) 6.074 Q7
  unsigned int CoreId = gap_coreid();
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 16) var shapes:
  // expr_2_out_0: (32, 32, 16) expr_2_in_1: (32, 32, 16) expr_2_in_0: (32,
  // 32, 16) SigmoidLUTTable: (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_2_in_1: (uint8-9) 7.573 Q8 expr_2_in_0: (uint8-117)
    // 19.005 Q8
    // expr_2_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_2_in_1, int32), [204]), [2]),
    // Norm(Mul(Sub(Cast(expr_2_in_0, int32), [117]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_2_in_0, int32), [152]), [1]),
    // [35568]), SigmoidLUTTable)), [8])), [200]), [14]), [-6]), 0, 255), uint8) scale clip and cast - (int32-459)
    // 2432.700 Q22 -> (uint8-12) 6.074 Q7
    expr_2_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              ((gap_roundnorm_reg((((int)expr_2_in_1[i0]) * (204)), ((unsigned char)2)) +
                gap_roundnorm_reg(
                    ((((int)expr_2_in_0[i0]) - (117)) *
                     SigmoidTableInline((((((int)expr_2_in_0[i0]) * (152)) << ((unsigned char)1)) - (35568)),
                                        SigmoidLUTTable)),
                    (8))) *
               (200)),
              ((unsigned char)14)) -
          (-6))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s56_kernel(s56_kernel_args_t *__restrict__ Args) {
  unsigned int I0 = Args->I0;
  unsigned short int *__restrict__ SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)
  unsigned char *__restrict__ expr_3_in_0 = Args->expr_3_in_0;              // (16, 16, 28) (uint8-139) 14.727 Q8
  unsigned char *__restrict__ expr_3_in_1 = Args->expr_3_in_1;              // (16, 16, 28) (uint8-12) 5.969 Q8
  unsigned char *__restrict__ expr_3_out_0 = Args->expr_3_out_0;            // (16, 16, 28) (uint8-17) 4.126 Q7
  unsigned int CoreId = gap_coreid();
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 28) var shapes:
  // expr_3_out_0: (16, 16, 28) expr_3_in_1: (16, 16, 28) expr_3_in_0: (16,
  // 16, 28) SigmoidLUTTable: (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_3_in_1: (uint8-12) 5.969 Q8 expr_3_in_0: (uint8-139)
    // 14.727 Q8
    // expr_3_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_3_in_1, int32), [208]), [2]),
    // Norm(Mul(Sub(Cast(expr_3_in_0, int32), [139]), SigmoidLUT(Sub(Mul(Cast(expr_3_in_0, int32), [236]), [32804]),
    // SigmoidLUTTable)), [8])), [228]), [14]), [-8]), 0, 255), uint8) scale clip and cast - (int32-624) 1885.103 Q22 ->
    // (uint8-17) 4.126 Q7
    expr_3_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              ((gap_roundnorm_reg((((int)expr_3_in_1[i0]) * (208)), ((unsigned char)2)) +
                gap_roundnorm_reg(((((int)expr_3_in_0[i0]) - (139)) *
                                   SigmoidTableInline(((((int)expr_3_in_0[i0]) * (236)) - (32804)), SigmoidLUTTable)),
                                  (8))) *
               (228)),
              ((unsigned char)14)) -
          (-8))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void s76_kernel(s76_kernel_args_t *__restrict__ Args) {
  unsigned int I0 = Args->I0;
  unsigned short int *__restrict__ SigmoidLUTTable = Args->SigmoidLUTTable; // (1, 1, 256)
  unsigned char *__restrict__ expr_4_in_0 = Args->expr_4_in_0;              // (8, 8, 52)  (uint8-153) 16.303 Q8
  unsigned char *__restrict__ expr_4_in_1 = Args->expr_4_in_1;              // (8, 8, 52)  (uint8-10) 6.911 Q8
  unsigned char *__restrict__ expr_4_out_0 = Args->expr_4_out_0;            // (8, 8, 52)  (uint8-19) 7.187 Q8
  unsigned int CoreId = gap_coreid();
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 52) var shapes:
  // expr_4_out_0: (8, 8, 52) expr_4_in_1: (8, 8, 52) expr_4_in_0: (8, 8, 52)
  // SigmoidLUTTable: (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_4_in_1: (uint8-10) 6.911 Q8 expr_4_in_0: (uint8-153)
    // 16.303 Q8
    // expr_4_out_0 = Cast(Clip(Sub(Norm(Mul(Add(Norm(Mul(Cast(expr_4_in_1, int32), [217]), [2]),
    // Norm(Mul(Sub(Cast(expr_4_in_0, int32), [153]), SigmoidLUT(Sub(LShift(Mul(Cast(expr_4_in_0, int32), [130]), [1]),
    // [39780]), SigmoidLUTTable)), [8])), [145]), [13]), [-9]), 0, 255), uint8) scale clip and cast - (int32-543)
    // 2086.774 Q22 -> (uint8-19) 7.187 Q8
    expr_4_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              ((gap_roundnorm_reg((((int)expr_4_in_1[i0]) * (217)), ((unsigned char)2)) +
                gap_roundnorm_reg(
                    ((((int)expr_4_in_0[i0]) - (153)) *
                     SigmoidTableInline((((((int)expr_4_in_0[i0]) * (130)) << ((unsigned char)1)) - (39780)),
                                        SigmoidLUTTable)),
                    (8))) *
               (145)),
              ((unsigned char)13)) -
          (-9))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 2 external iteration spaces
void s257_kernel(s257_kernel_args_t *__restrict__ Args) {
  unsigned int I0 = Args->I0;
  unsigned int I1 = Args->I1;
  signed char *__restrict__ expr_64_in_0 = Args->expr_64_in_0;   // (4, 1, 1344) (int8--128) 15.894 Q7
  signed char *__restrict__ expr_64_in_1 = Args->expr_64_in_1;   // (1, 1, 1344) int8 32.252 Q7
  signed char *__restrict__ expr_64_out_0 = Args->expr_64_out_0; // (4, 1, 1344) int8 483.758 Q7
  unsigned int CoreId = gap_coreid();
  unsigned int Chunk = ChunkSize(I1);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I1);
  // Max shape: (4, 1, 1344) var shapes:
  // expr_64_out_0: (4, 1, 1344) expr_64_in_0: (4, 1, 1344) expr_64_in_1: (1,
  // 1, 1344)
  // Iteration reduced to spaces ((0,), (2,))
  // Fixed spaces ()
  // Parameteric spaces ((0,), (2,))
  // Paralelized space (2,)
  // Interior spaces ()
  for (int i0 = 0; i0 < I0; i0++) {
    for (int i1 = First; i1 < Last; i1++) {
      // inputs expr_64_in_0: (int8--128) 15.894 Q7 expr_64_in_1: int8
      // 32.252 Q7
      // expr_64_out_0 = Cast(Clip(Norm(Mul(Mul(Sub(Cast(expr_64_in_0, int32), [-128]), Cast(expr_64_in_1, int32)),
      // [136]), [14]), -128, 127), int8) scale clip and cast - int32 512.597 Q14 -> int8 483.758 Q7
      expr_64_out_0[(i0 * I1) + i1] = ((signed char)gap_clip(
          (gap_roundnorm_reg((((((int)expr_64_in_0[(i0 * I1) + i1]) - (-128)) * ((int)expr_64_in_1[i1])) * (136)),
                             ((unsigned char)14))),
          (((signed char)7))));
    }
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_44(expr_44_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_44_in_0 = Args->expr_44_in_0;
  unsigned char *__restrict__ expr_44_out_0 = Args->expr_44_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (128, 128, 8) var shapes:
  // expr_44_out_0: (128, 128, 8) expr_44_in_0: (128, 128, 8)
  // SigmoidLUTTable: (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_44_in_0: (uint8-153) 55.090 Q8
    // expr_44_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_44_in_0, int32), [153]),
    // SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_44_in_0, int32), [220]), [2]), [134640]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [158]), [13]), [-3]), 0, 255), uint8) scale clip and cast - int32 55.090 Q15 ->
    // (uint8-3) 11.153 Q7
    expr_44_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_44_in_0[i0]) - (153)) *
                                  SigmoidTableInline(
                                      gap_clip(((((((int)expr_44_in_0[i0]) * (220)) << ((unsigned char)2)) - (134640))),
                                               (((signed char)16))),
                                      SigmoidLUTTable)),
                                 (8)) *
               (158)),
              ((unsigned char)13)) -
          (-3))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_55(expr_55_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_55_in_0 = Args->expr_55_in_0;
  unsigned char *__restrict__ expr_55_out_0 = Args->expr_55_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (64, 64, 16) var shapes:
  // expr_55_out_0: (64, 64, 16) expr_55_in_0: (64, 64, 16) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_55_in_0: (uint8-147) 155.920 Q8
    // expr_55_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_55_in_0, int32), [147]),
    // SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_55_in_0, int32), [156]), [4]), [366912]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [151]), [13]), [-1]), 0, 255), uint8) scale clip and cast - int32 155.920 Q15 ->
    // (uint8-1) 33.038 Q7
    expr_55_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_55_in_0[i0]) - (147)) *
                                  SigmoidTableInline(
                                      gap_clip(((((((int)expr_55_in_0[i0]) * (156)) << ((unsigned char)4)) - (366912))),
                                               (((signed char)16))),
                                      SigmoidLUTTable)),
                                 (8)) *
               (151)),
              ((unsigned char)13)) -
          (-1))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_13(expr_13_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_13_in_0 = Args->expr_13_in_0;
  unsigned char *__restrict__ expr_13_out_0 = Args->expr_13_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (64, 64, 16) var shapes:
  // expr_13_out_0: (64, 64, 16) expr_13_in_0: (64, 64, 16) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_13_in_0: (uint8-169) 96.036 Q8
    // expr_13_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_13_in_0, int32), [169]),
    // SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_13_in_0, int32), [192]), [3]), [259584]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [187]), [13]), [-2]), 0, 255), uint8) scale clip and cast - int32 96.036 Q15 ->
    // (uint8-2) 16.418 Q7
    expr_13_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_13_in_0[i0]) - (169)) *
                                  SigmoidTableInline(
                                      gap_clip(((((((int)expr_13_in_0[i0]) * (192)) << ((unsigned char)3)) - (259584))),
                                               (((signed char)16))),
                                      SigmoidLUTTable)),
                                 (8)) *
               (187)),
              ((unsigned char)13)) -
          (-2))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_23(expr_23_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_23_in_0 = Args->expr_23_in_0;
  unsigned char *__restrict__ expr_23_out_0 = Args->expr_23_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (64, 64, 8) var shapes:
  // expr_23_out_0: (64, 64, 8) expr_23_in_0: (64, 64, 8) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_23_in_0: (uint8-144) 108.458 Q8
    // expr_23_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_23_in_0, int32), [144]),
    // SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_23_in_0, int32), [217]), [3]), [249984]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [146]), [13]), [-1]), 0, 255), uint8) scale clip and cast - int32 108.458 Q15 ->
    // (uint8-1) 23.801 Q7
    expr_23_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_23_in_0[i0]) - (144)) *
                                  SigmoidTableInline(
                                      gap_clip(((((((int)expr_23_in_0[i0]) * (217)) << ((unsigned char)3)) - (249984))),
                                               (((signed char)16))),
                                      SigmoidLUTTable)),
                                 (8)) *
               (146)),
              ((unsigned char)13)) -
          (-1))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_42(expr_42_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_42_in_0 = Args->expr_42_in_0;
  unsigned char *__restrict__ expr_42_out_0 = Args->expr_42_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (64, 64, 16) var shapes:
  // expr_42_out_0: (64, 64, 16) expr_42_in_0: (64, 64, 16) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_42_in_0: (uint8-197) 65.940 Q8
    // expr_42_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_42_in_0, int32), [197]),
    // SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_42_in_0, int32), [132]), [3]), [208032]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [138]), [12]), [-5]), 0, 255), uint8) scale clip and cast - int32 65.940 Q15 ->
    // (uint8-5) 7.630 Q7
    expr_42_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_42_in_0[i0]) - (197)) *
                                  SigmoidTableInline(
                                      gap_clip(((((((int)expr_42_in_0[i0]) * (132)) << ((unsigned char)3)) - (208032))),
                                               (((signed char)16))),
                                      SigmoidLUTTable)),
                                 (8)) *
               (138)),
              ((unsigned char)12)) -
          (-5))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_43(expr_43_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_43_in_0 = Args->expr_43_in_0;
  unsigned char *__restrict__ expr_43_out_0 = Args->expr_43_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 32) var shapes:
  // expr_43_out_0: (32, 32, 32) expr_43_in_0: (32, 32, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_43_in_0: (uint8-132) 20.836 Q8
    // expr_43_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_43_in_0, int32), [132]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_43_in_0, int32), [167]), [1]), [44088]), SigmoidLUTTable)), [8]), [129]),
    // [13]), [-7]), 0, 255), uint8) scale clip and cast - int32 20.836 Q15 -> (uint8-7) 5.183 Q7
    expr_43_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_43_in_0[i0]) - (132)) *
                    SigmoidTableInline((((((int)expr_43_in_0[i0]) * (167)) << ((unsigned char)1)) - (44088)),
                                       SigmoidLUTTable)),
                   (8)) *
               (129)),
              ((unsigned char)13)) -
          (-7))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_45(expr_45_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_45_in_0 = Args->expr_45_in_0;
  unsigned char *__restrict__ expr_45_out_0 = Args->expr_45_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 32) var shapes:
  // expr_45_out_0: (32, 32, 32) expr_45_in_0: (32, 32, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_45_in_0: (uint8-141) 16.388 Q8
    // expr_45_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_45_in_0, int32), [141]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_45_in_0, int32), [131]), [1]), [36942]), SigmoidLUTTable)), [8]), [139]),
    // [13]), [-9]), 0, 255), uint8) scale clip and cast - int32 16.388 Q15 -> (uint8-9) 3.786 Q7
    expr_45_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_45_in_0[i0]) - (141)) *
                    SigmoidTableInline((((((int)expr_45_in_0[i0]) * (131)) << ((unsigned char)1)) - (36942)),
                                       SigmoidLUTTable)),
                   (8)) *
               (139)),
              ((unsigned char)13)) -
          (-9))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_46(expr_46_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_46_in_0 = Args->expr_46_in_0;
  unsigned char *__restrict__ expr_46_out_0 = Args->expr_46_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 16) var shapes:
  // expr_46_out_0: (32, 32, 16) expr_46_in_0: (32, 32, 16) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_46_in_0: (uint8-129) 12.231 Q8
    // expr_46_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_46_in_0, int32), [129]),
    // SigmoidLUT(Sub(Mul(Cast(expr_46_in_0, int32), [196]), [25284]), SigmoidLUTTable)), [8]), [248]), [14]), [-11]),
    // 0, 255), uint8) scale clip and cast - int32 12.231 Q15 -> (uint8-11) 3.160 Q7
    expr_46_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_46_in_0[i0]) - (129)) *
                                  SigmoidTableInline(((((int)expr_46_in_0[i0]) * (196)) - (25284)), SigmoidLUTTable)),
                                 (8)) *
               (248)),
              ((unsigned char)14)) -
          (-11))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_48(expr_48_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_48_in_0 = Args->expr_48_in_0;
  unsigned char *__restrict__ expr_48_out_0 = Args->expr_48_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 32) var shapes:
  // expr_48_out_0: (32, 32, 32) expr_48_in_0: (32, 32, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_48_in_0: (uint8-137) 14.511 Q8
    // expr_48_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_48_in_0, int32), [137]),
    // SigmoidLUT(Sub(Mul(Cast(expr_48_in_0, int32), [232]), [31784]), SigmoidLUTTable)), [8]), [133]), [13]), [-10]),
    // 0, 255), uint8) scale clip and cast - int32 14.511 Q15 -> (uint8-10) 3.501 Q7
    expr_48_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_48_in_0[i0]) - (137)) *
                                  SigmoidTableInline(((((int)expr_48_in_0[i0]) * (232)) - (31784)), SigmoidLUTTable)),
                                 (8)) *
               (133)),
              ((unsigned char)13)) -
          (-10))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_49(expr_49_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_49_in_0 = Args->expr_49_in_0;
  unsigned char *__restrict__ expr_49_out_0 = Args->expr_49_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 56) var shapes:
  // expr_49_out_0: (16, 16, 56) expr_49_in_0: (16, 16, 56) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_49_in_0: (uint8-129) 12.888 Q8
    // expr_49_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_49_in_0, int32), [129]),
    // SigmoidLUT(Sub(Mul(Cast(expr_49_in_0, int32), [206]), [26574]), SigmoidLUTTable)), [8]), [248]), [14]), [-11]),
    // 0, 255), uint8) scale clip and cast - int32 12.888 Q15 -> (uint8-11) 3.329 Q7
    expr_49_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_49_in_0[i0]) - (129)) *
                                  SigmoidTableInline(((((int)expr_49_in_0[i0]) * (206)) - (26574)), SigmoidLUTTable)),
                                 (8)) *
               (248)),
              ((unsigned char)14)) -
          (-11))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_50(expr_50_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_50_in_0 = Args->expr_50_in_0;
  unsigned char *__restrict__ expr_50_out_0 = Args->expr_50_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 56) var shapes:
  // expr_50_out_0: (16, 16, 56) expr_50_in_0: (16, 16, 56) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_50_in_0: (uint8-131) 11.767 Q8
    // expr_50_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_50_in_0, int32), [131]),
    // SigmoidLUT(Sub(Mul(Cast(expr_50_in_0, int32), [188]), [24628]), SigmoidLUTTable)), [8]), [252]), [14]), [-12]),
    // 0, 255), uint8) scale clip and cast - int32 11.767 Q15 -> (uint8-12) 2.985 Q7
    expr_50_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_50_in_0[i0]) - (131)) *
                                  SigmoidTableInline(((((int)expr_50_in_0[i0]) * (188)) - (24628)), SigmoidLUTTable)),
                                 (8)) *
               (252)),
              ((unsigned char)14)) -
          (-12))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_51(expr_51_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_51_in_0 = Args->expr_51_in_0;
  unsigned char *__restrict__ expr_51_out_0 = Args->expr_51_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 28) var shapes:
  // expr_51_out_0: (16, 16, 28) expr_51_in_0: (16, 16, 28) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_51_in_0: (uint8-135) 12.598 Q8
    // expr_51_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_51_in_0, int32), [135]),
    // SigmoidLUT(Sub(Mul(Cast(expr_51_in_0, int32), [202]), [27270]), SigmoidLUTTable)), [8]), [130]), [13]), [-12]),
    // 0, 255), uint8) scale clip and cast - int32 12.598 Q15 -> (uint8-12) 3.090 Q7
    expr_51_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_51_in_0[i0]) - (135)) *
                                  SigmoidTableInline(((((int)expr_51_in_0[i0]) * (202)) - (27270)), SigmoidLUTTable)),
                                 (8)) *
               (130)),
              ((unsigned char)13)) -
          (-12))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_53(expr_53_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_53_in_0 = Args->expr_53_in_0;
  unsigned char *__restrict__ expr_53_out_0 = Args->expr_53_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 56) var shapes:
  // expr_53_out_0: (16, 16, 56) expr_53_in_0: (16, 16, 56) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_53_in_0: (uint8-140) 12.611 Q8
    // expr_53_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_53_in_0, int32), [140]),
    // SigmoidLUT(Sub(Mul(Cast(expr_53_in_0, int32), [202]), [28280]), SigmoidLUTTable)), [8]), [136]), [13]), [-12]),
    // 0, 255), uint8) scale clip and cast - int32 12.611 Q15 -> (uint8-12) 2.964 Q7
    expr_53_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_53_in_0[i0]) - (140)) *
                                  SigmoidTableInline(((((int)expr_53_in_0[i0]) * (202)) - (28280)), SigmoidLUTTable)),
                                 (8)) *
               (136)),
              ((unsigned char)13)) -
          (-12))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_54(expr_54_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_54_in_0 = Args->expr_54_in_0;
  unsigned char *__restrict__ expr_54_out_0 = Args->expr_54_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 104) var shapes:
  // expr_54_out_0: (8, 8, 104) expr_54_in_0: (8, 8, 104) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_54_in_0: (uint8-133) 12.291 Q8
    // expr_54_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_54_in_0, int32), [133]),
    // SigmoidLUT(Sub(Mul(Cast(expr_54_in_0, int32), [197]), [26201]), SigmoidLUTTable)), [8]), [128]), [13]), [-12]),
    // 0, 255), uint8) scale clip and cast - int32 12.291 Q15 -> (uint8-12) 3.072 Q7
    expr_54_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_54_in_0[i0]) - (133)) *
                                  SigmoidTableInline(((((int)expr_54_in_0[i0]) * (197)) - (26201)), SigmoidLUTTable)),
                                 (8)) *
               (128)),
              ((unsigned char)13)) -
          (-12))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_56(expr_56_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_56_in_0 = Args->expr_56_in_0;
  unsigned char *__restrict__ expr_56_out_0 = Args->expr_56_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 104) var shapes:
  // expr_56_out_0: (8, 8, 104) expr_56_in_0: (8, 8, 104) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_56_in_0: (uint8-129) 13.396 Q8
    // expr_56_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_56_in_0, int32), [129]),
    // SigmoidLUT(Sub(Mul(Cast(expr_56_in_0, int32), [214]), [27606]), SigmoidLUTTable)), [8]), [248]), [14]), [-10]),
    // 0, 255), uint8) scale clip and cast - int32 13.396 Q15 -> (uint8-10) 3.456 Q7
    expr_56_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_56_in_0[i0]) - (129)) *
                                  SigmoidTableInline(((((int)expr_56_in_0[i0]) * (214)) - (27606)), SigmoidLUTTable)),
                                 (8)) *
               (248)),
              ((unsigned char)14)) -
          (-10))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_57(expr_57_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_57_in_0 = Args->expr_57_in_0;
  unsigned char *__restrict__ expr_57_out_0 = Args->expr_57_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 52) var shapes:
  // expr_57_out_0: (8, 8, 52) expr_57_in_0: (8, 8, 52) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_57_in_0: (uint8-112) 14.710 Q8
    // expr_57_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_57_in_0, int32), [112]),
    // SigmoidLUT(Sub(Mul(Cast(expr_57_in_0, int32), [235]), [26320]), SigmoidLUTTable)), [8]), [220]), [14]), [-8]), 0,
    // 255), uint8) scale clip and cast - int32 14.710 Q15 -> (uint8-8) 4.275 Q7
    expr_57_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_57_in_0[i0]) - (112)) *
                                  SigmoidTableInline(((((int)expr_57_in_0[i0]) * (235)) - (26320)), SigmoidLUTTable)),
                                 (8)) *
               (220)),
              ((unsigned char)14)) -
          (-8))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_59(expr_59_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_59_in_0 = Args->expr_59_in_0;
  unsigned char *__restrict__ expr_59_out_0 = Args->expr_59_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 104) var shapes:
  // expr_59_out_0: (8, 8, 104) expr_59_in_0: (8, 8, 104) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_59_in_0: (uint8-157) 16.675 Q8
    // expr_59_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_59_in_0, int32), [157]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_59_in_0, int32), [133]), [1]), [41762]), SigmoidLUTTable)), [8]), [160]),
    // [13]), [-11]), 0, 255), uint8) scale clip and cast - int32 16.675 Q15 -> (uint8-11) 3.343 Q7
    expr_59_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_59_in_0[i0]) - (157)) *
                    SigmoidTableInline((((((int)expr_59_in_0[i0]) * (133)) << ((unsigned char)1)) - (41762)),
                                       SigmoidLUTTable)),
                   (8)) *
               (160)),
              ((unsigned char)13)) -
          (-11))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_60(expr_60_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_60_in_0 = Args->expr_60_in_0;
  unsigned char *__restrict__ expr_60_out_0 = Args->expr_60_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 52) var shapes:
  // expr_60_out_0: (8, 8, 52) expr_60_in_0: (8, 8, 52) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_60_in_0: (uint8-87) 11.356 Q8
    // expr_60_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_60_in_0, int32), [87]),
    // SigmoidLUT(Sub(Mul(Cast(expr_60_in_0, int32), [182]), [15834]), SigmoidLUTTable)), [8]), [187]), [14]), [-9]), 0,
    // 255), uint8) scale clip and cast - int32 11.356 Q15 -> (uint8-9) 3.888 Q7
    expr_60_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_60_in_0[i0]) - (87)) *
                                  SigmoidTableInline(((((int)expr_60_in_0[i0]) * (182)) - (15834)), SigmoidLUTTable)),
                                 (8)) *
               (187)),
              ((unsigned char)14)) -
          (-9))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_61(expr_61_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_61_in_0 = Args->expr_61_in_0;
  unsigned char *__restrict__ expr_61_out_0 = Args->expr_61_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 104) var shapes:
  // expr_61_out_0: (8, 8, 104) expr_61_in_0: (8, 8, 104) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_61_in_0: (uint8-138) 18.254 Q8
    // expr_61_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_61_in_0, int32), [138]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_61_in_0, int32), [146]), [1]), [40296]), SigmoidLUTTable)), [8]), [135]),
    // [13]), [-8]), 0, 255), uint8) scale clip and cast - int32 18.254 Q15 -> (uint8-8) 4.342 Q7
    expr_61_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_61_in_0[i0]) - (138)) *
                    SigmoidTableInline((((((int)expr_61_in_0[i0]) * (146)) << ((unsigned char)1)) - (40296)),
                                       SigmoidLUTTable)),
                   (8)) *
               (135)),
              ((unsigned char)13)) -
          (-8))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_62(expr_62_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_62_in_0 = Args->expr_62_in_0;
  unsigned char *__restrict__ expr_62_out_0 = Args->expr_62_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 56) var shapes:
  // expr_62_out_0: (8, 8, 56) expr_62_in_0: (8, 8, 56) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_62_in_0: (uint8-123) 15.371 Q8
    // expr_62_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_62_in_0, int32), [123]),
    // SigmoidLUT(Sub(Mul(Cast(expr_62_in_0, int32), [246]), [30258]), SigmoidLUTTable)), [8]), [238]), [14]), [-9]), 0,
    // 255), uint8) scale clip and cast - int32 15.371 Q15 -> (uint8-9) 4.128 Q7
    expr_62_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_62_in_0[i0]) - (123)) *
                                  SigmoidTableInline(((((int)expr_62_in_0[i0]) * (246)) - (30258)), SigmoidLUTTable)),
                                 (8)) *
               (238)),
              ((unsigned char)14)) -
          (-9))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_5(expr_5_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_5_in_0 = Args->expr_5_in_0;
  unsigned char *__restrict__ expr_5_out_0 = Args->expr_5_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 56) var shapes:
  // expr_5_out_0: (16, 16, 56) expr_5_in_0: (16, 16, 56) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_5_in_0: (uint8-138) 11.804 Q8
    // expr_5_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_5_in_0, int32), [138]),
    // SigmoidLUT(Sub(Mul(Cast(expr_5_in_0, int32), [189]), [26082]), SigmoidLUTTable)), [8]), [133]), [13]), [-13]), 0,
    // 255), uint8) scale clip and cast - int32 11.804 Q15 -> (uint8-13) 2.842 Q7
    expr_5_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_5_in_0[i0]) - (138)) *
                                  SigmoidTableInline(((((int)expr_5_in_0[i0]) * (189)) - (26082)), SigmoidLUTTable)),
                                 (8)) *
               (133)),
              ((unsigned char)13)) -
          (-13))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_6(expr_6_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_6_in_0 = Args->expr_6_in_0;
  unsigned char *__restrict__ expr_6_out_0 = Args->expr_6_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 28) var shapes:
  // expr_6_out_0: (16, 16, 28) expr_6_in_0: (16, 16, 28) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_6_in_0: (uint8-117) 9.924 Q8
    // expr_6_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_6_in_0, int32), [117]),
    // SigmoidLUT(Sub(Mul(Cast(expr_6_in_0, int32), [159]), [18603]), SigmoidLUTTable)), [8]), [225]), [14]), [-13]), 0,
    // 255), uint8) scale clip and cast - int32 9.924 Q15 -> (uint8-13) 2.820 Q7
    expr_6_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_6_in_0[i0]) - (117)) *
                                  SigmoidTableInline(((((int)expr_6_in_0[i0]) * (159)) - (18603)), SigmoidLUTTable)),
                                 (8)) *
               (225)),
              ((unsigned char)14)) -
          (-13))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_7(expr_7_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_7_in_0 = Args->expr_7_in_0;
  unsigned char *__restrict__ expr_7_out_0 = Args->expr_7_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 28) var shapes:
  // expr_7_out_0: (16, 16, 28) expr_7_in_0: (16, 16, 28) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_7_in_0: (uint8-164) 15.435 Q8
    // expr_7_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_7_in_0, int32), [164]),
    // SigmoidLUT(Sub(Mul(Cast(expr_7_in_0, int32), [247]), [40508]), SigmoidLUTTable)), [8]), [170]), [13]), [-13]), 0,
    // 255), uint8) scale clip and cast - int32 15.435 Q15 -> (uint8-13) 5.807 Q8
    expr_7_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_7_in_0[i0]) - (164)) *
                                  SigmoidTableInline(((((int)expr_7_in_0[i0]) * (247)) - (40508)), SigmoidLUTTable)),
                                 (8)) *
               (170)),
              ((unsigned char)13)) -
          (-13))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_9(expr_9_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_9_in_0 = Args->expr_9_in_0;
  unsigned char *__restrict__ expr_9_out_0 = Args->expr_9_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 56) var shapes:
  // expr_9_out_0: (16, 16, 56) expr_9_in_0: (16, 16, 56) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_9_in_0: (uint8-140) 11.609 Q8
    // expr_9_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_9_in_0, int32), [140]),
    // SigmoidLUT(Sub(Mul(Cast(expr_9_in_0, int32), [186]), [26040]), SigmoidLUTTable)), [8]), [136]), [13]), [-13]), 0,
    // 255), uint8) scale clip and cast - int32 11.609 Q15 -> (uint8-13) 2.742 Q7
    expr_9_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_9_in_0[i0]) - (140)) *
                                  SigmoidTableInline(((((int)expr_9_in_0[i0]) * (186)) - (26040)), SigmoidLUTTable)),
                                 (8)) *
               (136)),
              ((unsigned char)13)) -
          (-13))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_10(expr_10_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_10_in_0 = Args->expr_10_in_0;
  unsigned char *__restrict__ expr_10_out_0 = Args->expr_10_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 32) var shapes:
  // expr_10_out_0: (16, 16, 32) expr_10_in_0: (16, 16, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_10_in_0: (uint8-96) 8.135 Q8
    // expr_10_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_10_in_0, int32), [96]),
    // SigmoidLUT(Sub(Mul(Cast(expr_10_in_0, int32), [130]), [12480]), SigmoidLUTTable)), [8]), [196]), [14]), [-13]),
    // 0, 255), uint8) scale clip and cast - int32 8.135 Q15 -> (uint8-13) 2.658 Q7
    expr_10_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_10_in_0[i0]) - (96)) *
                                  SigmoidTableInline(((((int)expr_10_in_0[i0]) * (130)) - (12480)), SigmoidLUTTable)),
                                 (8)) *
               (196)),
              ((unsigned char)14)) -
          (-13))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_11(expr_11_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_11_in_0 = Args->expr_11_in_0;
  unsigned char *__restrict__ expr_11_out_0 = Args->expr_11_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 32) var shapes:
  // expr_11_out_0: (32, 32, 32) expr_11_in_0: (32, 32, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_11_in_0: (uint8-120) 12.115 Q8
    // expr_11_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_11_in_0, int32), [120]),
    // SigmoidLUT(Sub(Mul(Cast(expr_11_in_0, int32), [194]), [23280]), SigmoidLUTTable)), [8]), [232]), [14]), [-11]),
    // 0, 255), uint8) scale clip and cast - int32 12.115 Q15 -> (uint8-11) 3.344 Q7
    expr_11_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_11_in_0[i0]) - (120)) *
                                  SigmoidTableInline(((((int)expr_11_in_0[i0]) * (194)) - (23280)), SigmoidLUTTable)),
                                 (8)) *
               (232)),
              ((unsigned char)14)) -
          (-11))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_12(expr_12_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_12_in_0 = Args->expr_12_in_0;
  unsigned char *__restrict__ expr_12_out_0 = Args->expr_12_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 16) var shapes:
  // expr_12_out_0: (32, 32, 16) expr_12_in_0: (32, 32, 16) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_12_in_0: (uint8-120) 11.387 Q8
    // expr_12_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_12_in_0, int32), [120]),
    // SigmoidLUT(Sub(Mul(Cast(expr_12_in_0, int32), [182]), [21840]), SigmoidLUTTable)), [8]), [232]), [14]), [-11]),
    // 0, 255), uint8) scale clip and cast - int32 11.387 Q15 -> (uint8-11) 3.145 Q7
    expr_12_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_12_in_0[i0]) - (120)) *
                                  SigmoidTableInline(((((int)expr_12_in_0[i0]) * (182)) - (21840)), SigmoidLUTTable)),
                                 (8)) *
               (232)),
              ((unsigned char)14)) -
          (-11))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_14(expr_14_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_14_in_0 = Args->expr_14_in_0;
  unsigned char *__restrict__ expr_14_out_0 = Args->expr_14_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 16) var shapes:
  // expr_14_out_0: (32, 32, 16) expr_14_in_0: (32, 32, 16) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_14_in_0: (uint8-113) 13.165 Q8
    // expr_14_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_14_in_0, int32), [113]),
    // SigmoidLUT(Sub(Mul(Cast(expr_14_in_0, int32), [211]), [23843]), SigmoidLUTTable)), [8]), [220]), [14]), [-10]),
    // 0, 255), uint8) scale clip and cast - int32 13.165 Q15 -> (uint8-10) 7.645 Q8
    expr_14_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_14_in_0[i0]) - (113)) *
                                  SigmoidTableInline(((((int)expr_14_in_0[i0]) * (211)) - (23843)), SigmoidLUTTable)),
                                 (8)) *
               (220)),
              ((unsigned char)14)) -
          (-10))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_16(expr_16_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_16_in_0 = Args->expr_16_in_0;
  unsigned char *__restrict__ expr_16_out_0 = Args->expr_16_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 32) var shapes:
  // expr_16_out_0: (32, 32, 32) expr_16_in_0: (32, 32, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_16_in_0: (uint8-125) 17.544 Q8
    // expr_16_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_16_in_0, int32), [125]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_16_in_0, int32), [140]), [1]), [35000]), SigmoidLUTTable)), [8]), [244]),
    // [14]), [-8]), 0, 255), uint8) scale clip and cast - int32 17.544 Q15 -> (uint8-8) 4.605 Q7
    expr_16_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_16_in_0[i0]) - (125)) *
                    SigmoidTableInline((((((int)expr_16_in_0[i0]) * (140)) << ((unsigned char)1)) - (35000)),
                                       SigmoidLUTTable)),
                   (8)) *
               (244)),
              ((unsigned char)14)) -
          (-8))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_17(expr_17_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_17_in_0 = Args->expr_17_in_0;
  unsigned char *__restrict__ expr_17_out_0 = Args->expr_17_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 32) var shapes:
  // expr_17_out_0: (16, 16, 32) expr_17_in_0: (16, 16, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_17_in_0: (uint8-141) 11.004 Q8
    // expr_17_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_17_in_0, int32), [141]),
    // SigmoidLUT(Sub(Mul(Cast(expr_17_in_0, int32), [176]), [24816]), SigmoidLUTTable)), [8]), [132]), [13]), [-14]),
    // 0, 255), uint8) scale clip and cast - int32 11.004 Q15 -> (uint8-14) 5.327 Q8
    expr_17_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_17_in_0[i0]) - (141)) *
                                  SigmoidTableInline(((((int)expr_17_in_0[i0]) * (176)) - (24816)), SigmoidLUTTable)),
                                 (8)) *
               (132)),
              ((unsigned char)13)) -
          (-14))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_18(expr_18_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_18_in_0 = Args->expr_18_in_0;
  unsigned char *__restrict__ expr_18_out_0 = Args->expr_18_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 64) var shapes:
  // expr_18_out_0: (32, 32, 64) expr_18_in_0: (32, 32, 64) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_18_in_0: (uint8-163) 16.558 Q8
    // expr_18_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_18_in_0, int32), [163]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_18_in_0, int32), [132]), [1]), [43032]), SigmoidLUTTable)), [8]), [170]),
    // [13]), [-11]), 0, 255), uint8) scale clip and cast - int32 16.558 Q15 -> (uint8-11) 3.122 Q7
    expr_18_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_18_in_0[i0]) - (163)) *
                    SigmoidTableInline((((((int)expr_18_in_0[i0]) * (132)) << ((unsigned char)1)) - (43032)),
                                       SigmoidLUTTable)),
                   (8)) *
               (170)),
              ((unsigned char)13)) -
          (-11))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_19(expr_19_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_19_in_0 = Args->expr_19_in_0;
  unsigned char *__restrict__ expr_19_out_0 = Args->expr_19_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 64) var shapes:
  // expr_19_out_0: (32, 32, 64) expr_19_in_0: (32, 32, 64) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_19_in_0: (uint8-112) 41.593 Q8
    // expr_19_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_19_in_0, int32), [112]),
    // SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_19_in_0, int32), [166]), [2]), [74368]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [226]), [14]), [-3]), 0, 255), uint8) scale clip and cast - int32 41.593 Q15 ->
    // (uint8-3) 11.762 Q7
    expr_19_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_19_in_0[i0]) - (112)) *
                    SigmoidTableInline(gap_clip(((((((int)expr_19_in_0[i0]) * (166)) << ((unsigned char)2)) - (74368))),
                                                (((signed char)16))),
                                       SigmoidLUTTable)),
                   (8)) *
               (226)),
              ((unsigned char)14)) -
          (-3))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_20(expr_20_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_20_in_0 = Args->expr_20_in_0;
  unsigned char *__restrict__ expr_20_out_0 = Args->expr_20_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 32) var shapes:
  // expr_20_out_0: (32, 32, 32) expr_20_in_0: (32, 32, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_20_in_0: (uint8-142) 10.686 Q8
    // expr_20_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_20_in_0, int32), [142]),
    // SigmoidLUT(Sub(Mul(Cast(expr_20_in_0, int32), [171]), [24282]), SigmoidLUTTable)), [8]), [138]), [13]), [-14]),
    // 0, 255), uint8) scale clip and cast - int32 10.686 Q15 -> (uint8-14) 2.483 Q7
    expr_20_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_20_in_0[i0]) - (142)) *
                                  SigmoidTableInline(((((int)expr_20_in_0[i0]) * (171)) - (24282)), SigmoidLUTTable)),
                                 (8)) *
               (138)),
              ((unsigned char)13)) -
          (-14))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_21(expr_21_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_21_in_0 = Args->expr_21_in_0;
  unsigned char *__restrict__ expr_21_out_0 = Args->expr_21_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (32, 32, 32) var shapes:
  // expr_21_out_0: (32, 32, 32) expr_21_in_0: (32, 32, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_21_in_0: (uint8-100) 16.334 Q8
    // expr_21_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_21_in_0, int32), [100]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_21_in_0, int32), [131]), [1]), [26200]), SigmoidLUTTable)), [8]), [205]),
    // [14]), [-7]), 0, 255), uint8) scale clip and cast - int32 16.334 Q15 -> (uint8-7) 5.102 Q7
    expr_21_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_21_in_0[i0]) - (100)) *
                    SigmoidTableInline((((((int)expr_21_in_0[i0]) * (131)) << ((unsigned char)1)) - (26200)),
                                       SigmoidLUTTable)),
                   (8)) *
               (205)),
              ((unsigned char)14)) -
          (-7))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_22(expr_22_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_22_in_0 = Args->expr_22_in_0;
  unsigned char *__restrict__ expr_22_out_0 = Args->expr_22_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 56) var shapes:
  // expr_22_out_0: (16, 16, 56) expr_22_in_0: (16, 16, 56) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_22_in_0: (uint8-136) 12.219 Q8
    // expr_22_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_22_in_0, int32), [136]),
    // SigmoidLUT(Sub(Mul(Cast(expr_22_in_0, int32), [196]), [26656]), SigmoidLUTTable)), [8]), [132]), [13]), [-12]),
    // 0, 255), uint8) scale clip and cast - int32 12.219 Q15 -> (uint8-12) 2.970 Q7
    expr_22_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_22_in_0[i0]) - (136)) *
                                  SigmoidTableInline(((((int)expr_22_in_0[i0]) * (196)) - (26656)), SigmoidLUTTable)),
                                 (8)) *
               (132)),
              ((unsigned char)13)) -
          (-12))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_25(expr_25_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_25_in_0 = Args->expr_25_in_0;
  unsigned char *__restrict__ expr_25_out_0 = Args->expr_25_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 28) var shapes:
  // expr_25_out_0: (16, 16, 28) expr_25_in_0: (16, 16, 28) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_25_in_0: (uint8-116) 10.150 Q8
    // expr_25_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_25_in_0, int32), [116]),
    // SigmoidLUT(Sub(Mul(Cast(expr_25_in_0, int32), [162]), [18792]), SigmoidLUTTable)), [8]), [225]), [14]), [-12]),
    // 0, 255), uint8) scale clip and cast - int32 10.150 Q15 -> (uint8-12) 2.891 Q7
    expr_25_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_25_in_0[i0]) - (116)) *
                                  SigmoidTableInline(((((int)expr_25_in_0[i0]) * (162)) - (18792)), SigmoidLUTTable)),
                                 (8)) *
               (225)),
              ((unsigned char)14)) -
          (-12))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_26(expr_26_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_26_in_0 = Args->expr_26_in_0;
  unsigned char *__restrict__ expr_26_out_0 = Args->expr_26_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 28) var shapes:
  // expr_26_out_0: (16, 16, 28) expr_26_in_0: (16, 16, 28) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_26_in_0: (uint8-103) 18.970 Q8
    // expr_26_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_26_in_0, int32), [103]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_26_in_0, int32), [152]), [1]), [31312]), SigmoidLUTTable)), [8]), [210]),
    // [14]), [-6]), 0, 255), uint8) scale clip and cast - int32 18.970 Q15 -> (uint8-6) 11.582 Q8
    expr_26_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_26_in_0[i0]) - (103)) *
                    SigmoidTableInline((((((int)expr_26_in_0[i0]) * (152)) << ((unsigned char)1)) - (31312)),
                                       SigmoidLUTTable)),
                   (8)) *
               (210)),
              ((unsigned char)14)) -
          (-6))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_27(expr_27_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_27_in_0 = Args->expr_27_in_0;
  unsigned char *__restrict__ expr_27_out_0 = Args->expr_27_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 56) var shapes:
  // expr_27_out_0: (16, 16, 56) expr_27_in_0: (16, 16, 56) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_27_in_0: (uint8-122) 17.752 Q8
    // expr_27_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_27_in_0, int32), [122]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_27_in_0, int32), [142]), [1]), [34648]), SigmoidLUTTable)), [8]), [238]),
    // [14]), [-7]), 0, 255), uint8) scale clip and cast - int32 17.752 Q15 -> (uint8-7) 4.773 Q7
    expr_27_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_27_in_0[i0]) - (122)) *
                    SigmoidTableInline((((((int)expr_27_in_0[i0]) * (142)) << ((unsigned char)1)) - (34648)),
                                       SigmoidLUTTable)),
                   (8)) *
               (238)),
              ((unsigned char)14)) -
          (-7))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_28(expr_28_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_28_in_0 = Args->expr_28_in_0;
  unsigned char *__restrict__ expr_28_out_0 = Args->expr_28_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 56) var shapes:
  // expr_28_out_0: (8, 8, 56) expr_28_in_0: (8, 8, 56) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_28_in_0: (uint8-129) 6.293 Q8
    // expr_28_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_28_in_0, int32), [129]),
    // SigmoidLUT(Sub(Norm(Mul(Cast(expr_28_in_0, int32), [201]), [1]), [12965]), SigmoidLUTTable)), [8]), [195]),
    // [15]), [-9]), 0, 255), uint8) scale clip and cast - int32 6.293 Q15 -> (uint8-9) 8.255 Q8
    expr_28_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_28_in_0[i0]) - (129)) *
                                                SigmoidTableInline((gap_roundnorm_reg((((int)expr_28_in_0[i0]) * (201)),
                                                                                      ((unsigned char)1)) -
                                                                    (12965)),
                                                                   SigmoidLUTTable)),
                                               (8)) *
                             (195)),
                            ((unsigned char)15)) -
          (-9))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_29(expr_29_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_29_in_0 = Args->expr_29_in_0;
  unsigned char *__restrict__ expr_29_out_0 = Args->expr_29_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 64) var shapes:
  // expr_29_out_0: (16, 16, 64) expr_29_in_0: (16, 16, 64) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_29_in_0: (uint8-180) 24.421 Q8
    // expr_29_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_29_in_0, int32), [180]),
    // SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_29_in_0, int32), [195]), [1]), [70200]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [211]), [13]), [-10]), 0, 255), uint8) scale clip and cast - int32 24.421 Q15 ->
    // (uint8-10) 3.711 Q7
    expr_29_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_29_in_0[i0]) - (180)) *
                    SigmoidTableInline(gap_clip(((((((int)expr_29_in_0[i0]) * (195)) << ((unsigned char)1)) - (70200))),
                                                (((signed char)16))),
                                       SigmoidLUTTable)),
                   (8)) *
               (211)),
              ((unsigned char)13)) -
          (-10))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_30(expr_30_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_30_in_0 = Args->expr_30_in_0;
  unsigned char *__restrict__ expr_30_out_0 = Args->expr_30_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 32) var shapes:
  // expr_30_out_0: (16, 16, 32) expr_30_in_0: (16, 16, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_30_in_0: (uint8-123) 10.911 Q8
    // expr_30_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_30_in_0, int32), [123]),
    // SigmoidLUT(Sub(Mul(Cast(expr_30_in_0, int32), [175]), [21525]), SigmoidLUTTable)), [8]), [236]), [14]), [-12]),
    // 0, 255), uint8) scale clip and cast - int32 10.911 Q15 -> (uint8-12) 2.964 Q7
    expr_30_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_30_in_0[i0]) - (123)) *
                                  SigmoidTableInline(((((int)expr_30_in_0[i0]) * (175)) - (21525)), SigmoidLUTTable)),
                                 (8)) *
               (236)),
              ((unsigned char)14)) -
          (-12))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_31(expr_31_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_31_in_0 = Args->expr_31_in_0;
  unsigned char *__restrict__ expr_31_out_0 = Args->expr_31_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 64) var shapes:
  // expr_31_out_0: (16, 16, 64) expr_31_in_0: (16, 16, 64) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_31_in_0: (uint8-149) 29.318 Q8
    // expr_31_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_31_in_0, int32), [149]),
    // SigmoidLUT(Clip(Sub(LShift(Mul(Cast(expr_31_in_0, int32), [235]), [1]), [70030]), -65536, 65535),
    // SigmoidLUTTable)), [8]), [151]), [13]), [-6]), 0, 255), uint8) scale clip and cast - int32 29.318 Q15 ->
    // (uint8-6) 6.211 Q7
    expr_31_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_31_in_0[i0]) - (149)) *
                    SigmoidTableInline(gap_clip(((((((int)expr_31_in_0[i0]) * (235)) << ((unsigned char)1)) - (70030))),
                                                (((signed char)16))),
                                       SigmoidLUTTable)),
                   (8)) *
               (151)),
              ((unsigned char)13)) -
          (-6))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_32(expr_32_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_32_in_0 = Args->expr_32_in_0;
  unsigned char *__restrict__ expr_32_out_0 = Args->expr_32_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (16, 16, 32) var shapes:
  // expr_32_out_0: (16, 16, 32) expr_32_in_0: (16, 16, 32) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_32_in_0: (uint8-119) 16.183 Q8
    // expr_32_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_32_in_0, int32), [119]),
    // SigmoidLUT(Sub(LShift(Mul(Cast(expr_32_in_0, int32), [129]), [1]), [30702]), SigmoidLUTTable)), [8]), [232]),
    // [14]), [-8]), 0, 255), uint8) scale clip and cast - int32 16.183 Q15 -> (uint8-8) 4.467 Q7
    expr_32_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(
                   ((((int)expr_32_in_0[i0]) - (119)) *
                    SigmoidTableInline((((((int)expr_32_in_0[i0]) * (129)) << ((unsigned char)1)) - (30702)),
                                       SigmoidLUTTable)),
                   (8)) *
               (232)),
              ((unsigned char)14)) -
          (-8))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_33(expr_33_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_33_in_0 = Args->expr_33_in_0;
  unsigned char *__restrict__ expr_33_out_0 = Args->expr_33_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 104) var shapes:
  // expr_33_out_0: (8, 8, 104) expr_33_in_0: (8, 8, 104) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_33_in_0: (uint8-133) 6.706 Q8
    // expr_33_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_33_in_0, int32), [133]),
    // SigmoidLUT(Sub(Norm(Mul(Cast(expr_33_in_0, int32), [215]), [1]), [14298]), SigmoidLUTTable)), [8]), [256]),
    // [14]), [-21]), 0, 255), uint8) scale clip and cast - int32 6.706 Q15 -> (uint8-21) 1.678 Q7
    expr_33_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_33_in_0[i0]) - (133)) *
                                                SigmoidTableInline((gap_roundnorm_reg((((int)expr_33_in_0[i0]) * (215)),
                                                                                      ((unsigned char)1)) -
                                                                    (14298)),
                                                                   SigmoidLUTTable)),
                                               (8)) *
                             (256)),
                            ((unsigned char)14)) -
          (-21))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_35(expr_35_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_35_in_0 = Args->expr_35_in_0;
  unsigned char *__restrict__ expr_35_out_0 = Args->expr_35_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 52) var shapes:
  // expr_35_out_0: (8, 8, 52) expr_35_in_0: (8, 8, 52) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_35_in_0: (uint8-123) 7.002 Q8
    // expr_35_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_35_in_0, int32), [123]),
    // SigmoidLUT(Sub(Norm(Mul(Cast(expr_35_in_0, int32), [224]), [1]), [13776]), SigmoidLUTTable)), [8]), [235]),
    // [14]), [-19]), 0, 255), uint8) scale clip and cast - int32 7.002 Q15 -> (uint8-19) 1.906 Q7
    expr_35_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_35_in_0[i0]) - (123)) *
                                                SigmoidTableInline((gap_roundnorm_reg((((int)expr_35_in_0[i0]) * (224)),
                                                                                      ((unsigned char)1)) -
                                                                    (13776)),
                                                                   SigmoidLUTTable)),
                                               (8)) *
                             (235)),
                            ((unsigned char)14)) -
          (-19))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_36(expr_36_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_36_in_0 = Args->expr_36_in_0;
  unsigned char *__restrict__ expr_36_out_0 = Args->expr_36_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 52) var shapes:
  // expr_36_out_0: (8, 8, 52) expr_36_in_0: (8, 8, 52) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_36_in_0: (uint8-114) 8.800 Q8
    // expr_36_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_36_in_0, int32), [114]),
    // SigmoidLUT(Sub(Mul(Cast(expr_36_in_0, int32), [141]), [16074]), SigmoidLUTTable)), [8]), [221]), [14]), [-14]),
    // 0, 255), uint8) scale clip and cast - int32 8.800 Q15 -> (uint8-14) 2.549 Q7
    expr_36_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_36_in_0[i0]) - (114)) *
                                  SigmoidTableInline(((((int)expr_36_in_0[i0]) * (141)) - (16074)), SigmoidLUTTable)),
                                 (8)) *
               (221)),
              ((unsigned char)14)) -
          (-14))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_37(expr_37_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_37_in_0 = Args->expr_37_in_0;
  unsigned char *__restrict__ expr_37_out_0 = Args->expr_37_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 104) var shapes:
  // expr_37_out_0: (8, 8, 104) expr_37_in_0: (8, 8, 104) SigmoidLUTTable:
  // (1, 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_37_in_0: (uint8-126) 8.120 Q8
    // expr_37_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_37_in_0, int32), [126]),
    // SigmoidLUT(Sub(Mul(Cast(expr_37_in_0, int32), [130]), [16380]), SigmoidLUTTable)), [8]), [240]), [14]), [-16]),
    // 0, 255), uint8) scale clip and cast - int32 8.120 Q15 -> (uint8-16) 2.162 Q7
    expr_37_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_37_in_0[i0]) - (126)) *
                                  SigmoidTableInline(((((int)expr_37_in_0[i0]) * (130)) - (16380)), SigmoidLUTTable)),
                                 (8)) *
               (240)),
              ((unsigned char)14)) -
          (-16))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_38(expr_38_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_38_in_0 = Args->expr_38_in_0;
  unsigned char *__restrict__ expr_38_out_0 = Args->expr_38_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 64) var shapes:
  // expr_38_out_0: (8, 8, 64) expr_38_in_0: (8, 8, 64) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_38_in_0: (uint8-112) 0.024 Q8
    // expr_38_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_38_in_0, int32), [112]),
    // SigmoidLUT(Sub(Norm(Mul(Cast(expr_38_in_0, int32), [194]), [9]), [42]), SigmoidLUTTable)), [8]), [256]), [14]),
    // [-111]), 0, 255), uint8) scale clip and cast - int32 0.024 Q15 -> (uint8-111) 0.006 Q7
    expr_38_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_38_in_0[i0]) - (112)) *
                                  SigmoidTableInline(
                                      (gap_roundnorm_reg((((int)expr_38_in_0[i0]) * (194)), ((unsigned char)9)) - (42)),
                                      SigmoidLUTTable)),
                                 (8)) *
               (256)),
              ((unsigned char)14)) -
          (-111))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_39(expr_39_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_39_in_0 = Args->expr_39_in_0;
  unsigned char *__restrict__ expr_39_out_0 = Args->expr_39_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 32) var shapes:
  // expr_39_out_0: (8, 8, 32) expr_39_in_0: (8, 8, 32) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_39_in_0: (uint8-68) 8.901 Q8
    // expr_39_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_39_in_0, int32), [68]),
    // SigmoidLUT(Sub(Mul(Cast(expr_39_in_0, int32), [142]), [9656]), SigmoidLUTTable)), [8]), [168]), [14]), [-10]), 0,
    // 255), uint8) scale clip and cast - int32 8.901 Q15 -> (uint8-10) 3.401 Q7
    expr_39_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg(
              (gap_roundnorm_reg(((((int)expr_39_in_0[i0]) - (68)) *
                                  SigmoidTableInline(((((int)expr_39_in_0[i0]) * (142)) - (9656)), SigmoidLUTTable)),
                                 (8)) *
               (168)),
              ((unsigned char)14)) -
          (-10))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_40(expr_40_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_40_in_0 = Args->expr_40_in_0;
  unsigned char *__restrict__ expr_40_out_0 = Args->expr_40_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 64) var shapes:
  // expr_40_out_0: (8, 8, 64) expr_40_in_0: (8, 8, 64) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_40_in_0: (uint8-132) 0.000 Q8
    // expr_40_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_40_in_0, int32), [132]),
    // SigmoidLUT(Norm(Mul(Cast(expr_40_in_0, int32), [233]), [17]), SigmoidLUTTable)), [8]), [128]), [13]), [-132]), 0,
    // 255), uint8) scale clip and cast - int32 0.000 Q15 -> (uint8-132) 0.000 Q7
    expr_40_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_40_in_0[i0]) - (132)) *
                                                SigmoidTableInline(gap_roundnorm_reg((((int)expr_40_in_0[i0]) * (233)),
                                                                                     ((unsigned char)17)),
                                                                   SigmoidLUTTable)),
                                               (8)) *
                             (128)),
                            ((unsigned char)13)) -
          (-132))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

// Output iteration space reduced to 0 internal and 1 external iteration spaces
void expr_41(expr_41_args_t *__restrict__ Args) {
  unsigned char *__restrict__ expr_41_in_0 = Args->expr_41_in_0;
  unsigned char *__restrict__ expr_41_out_0 = Args->expr_41_out_0; // (1, 1, 256)
  unsigned short *__restrict__ SigmoidLUTTable = (unsigned short *)Args->SigmoidLUTTable;
  unsigned int CoreId = gap_coreid();
  unsigned int I0 = Args->W * Args->H * Args->Feat;
  unsigned int Chunk = ChunkSize(I0);
  unsigned int First = Chunk * CoreId;
  unsigned int Last = gap_min(First + Chunk, I0);
  // Max shape: (8, 8, 32) var shapes:
  // expr_41_out_0: (8, 8, 32) expr_41_in_0: (8, 8, 32) SigmoidLUTTable: (1,
  // 1, 256)
  // Iteration reduced to spaces ((0, 1, 2),)
  // Fixed spaces ()
  // Parameteric spaces ((0, 1, 2),)
  // Paralelized space (0, 1, 2)
  // Interior spaces ()
  for (int i0 = First; i0 < Last; i0++) {
    // inputs expr_41_in_0: (uint8-104) 3.694 Q8
    // expr_41_out_0 = Cast(Clip(Sub(Norm(Mul(Norm(Mul(Sub(Cast(expr_41_in_0, int32), [104]),
    // SigmoidLUT(Sub(Norm(Mul(Cast(expr_41_in_0, int32), [236]), [2]), [6136]), SigmoidLUTTable)), [8]), [211]), [14]),
    // [-32]), 0, 255), uint8) scale clip and cast - int32 3.694 Q15 -> (uint8-32) 1.120 Q7
    expr_41_out_0[i0] = ((unsigned char)gap_clipu(
        ((gap_roundnorm_reg((gap_roundnorm_reg(((((int)expr_41_in_0[i0]) - (104)) *
                                                SigmoidTableInline((gap_roundnorm_reg((((int)expr_41_in_0[i0]) * (236)),
                                                                                      ((unsigned char)2)) -
                                                                    (6136)),
                                                                   SigmoidLUTTable)),
                                               (8)) *
                             (211)),
                            ((unsigned char)14)) -
          (-32))),
        (((signed char)8))));
  }
  gap_waitbarrier(0);
}

#pragma GCC diagnostic pop