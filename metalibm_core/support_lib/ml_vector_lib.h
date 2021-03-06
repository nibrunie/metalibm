#include "math.h"
#include <stdbool.h>
#include "ml_vector_format.h"
#include "ml_utils.h"


#define VECTORIZE_OP1(OP, r, x, size) {\
  unsigned i;\
  for (i = 0; i < size; ++i) (r)->_[i] = OP((x)._[i]);\
}

#define VECTORIZE_OP2(OP, r, x, y, size) {\
  unsigned i;\
  for (i = 0; i < size; ++i) r[i] = OP(x[i], y[i]);\
}
  


#define DEF_ML_VECTOR_PRIMITIVES_OP3(FUNC_NAME, VECTOR_FORMAT, SCALAR_FORMAT, VECTOR_SIZE, SCALAR_OP0, SCALAR_OP1) \
static inline void FUNC_NAME(VECTOR_FORMAT *r, VECTOR_FORMAT vop0, VECTOR_FORMAT vop1, VECTOR_FORMAT vop2) {\
  unsigned i;\
  for (i = 0; i < VECTOR_SIZE; ++i) {\
    (*r)._[i] = vop0._[i] SCALAR_OP0 vop1._[i] SCALAR_OP1 vop2._[i];\
  };\
}
#define DEF_ML_VECTOR_PRIMITIVES_FUNC3(FUNC_NAME, VECTOR_FORMAT, SCALAR_FORMAT, VECTOR_SIZE, SCALAR_FUNC, SCALAR_OP0, SCALAR_OP1, SCALAR_OP2) \
static inline void FUNC_NAME(VECTOR_FORMAT *r, VECTOR_FORMAT vop0, VECTOR_FORMAT vop1, VECTOR_FORMAT vop2) {\
  unsigned i;\
  for (i = 0; i < VECTOR_SIZE; ++i) {\
    (*r)._[i] = SCALAR_FUNC(SCALAR_OP0(vop0._[i]), SCALAR_OP1(vop1._[i]), SCALAR_OP2( vop2._[i]));\
  };\
}
#define DEF_ML_VECTOR_PRIMITIVES_OP2(FUNC_NAME, VECTOR_FORMAT, SCALAR_FORMAT, VECTOR_SIZE, SCALAR_OP) \
static inline void FUNC_NAME(VECTOR_FORMAT *r, VECTOR_FORMAT vop0, VECTOR_FORMAT vop1) {\
  unsigned i;\
  for (i = 0; i < VECTOR_SIZE; ++i) {\
    (*r)._[i] = vop0._[i] SCALAR_OP vop1._[i];\
  };\
}
#define DEF_ML_VECTOR_PRIMITIVES_OP1(FUNC_NAME, VECTOR_FORMAT, SCALAR_FORMAT, VECTOR_SIZE, SCALAR_OP) \
static inline void FUNC_NAME(VECTOR_FORMAT *r, VECTOR_FORMAT vop) {\
  unsigned i;\
  for (i = 0; i < VECTOR_SIZE; ++i) {\
    (*r)._[i] = SCALAR_OP vop._[i];\
  };\
}

#define ML_ASSEMBLE_VECTOR(vr, va, vb, size_a, size_b) {\
  int __k; \
  for(__k = 0; __k < (size_a); __k++) (vr)->_[__k] = (va)._[__k];\
  for(__k = 0; __k < (size_b); __k++) (vr)->_[__k + (size_a)] = (vb)._[__k];\
}

/** Vector Addition */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddf2, ml_float2_t, float, 2, +)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddf4, ml_float4_t, float, 4, +)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddf8, ml_float8_t, float, 8, +)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddd2, ml_double2_t, double, 2, +)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddd4, ml_double4_t, double, 4, +)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddd8, ml_double8_t, double, 8, +)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddi2, ml_int2_t, int32_t, 2, +)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddi4, ml_int4_t, int32_t, 4, +)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddi8, ml_int8_t, int32_t, 8, +)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddu2, ml_uint2_t, uint32_t, 2, +)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddu4, ml_uint4_t, uint32_t, 4, +)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vaddu8, ml_uint8_t, uint32_t, 8, +)

/** Vector Subtraction */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubf2, ml_float2_t, float, 2, -)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubf4, ml_float4_t, float, 4, -)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubf8, ml_float8_t, float, 8, -)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubd2, ml_double2_t, double, 2, -)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubd4, ml_double4_t, double, 4, -)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubd8, ml_double8_t, double, 8, -)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubi2, ml_int2_t, int32_t, 2, -)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubi4, ml_int4_t, int32_t, 4, -)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubi8, ml_int8_t, int32_t, 8, -)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubu2, ml_uint2_t, uint32_t, 2, -)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubu4, ml_uint4_t, uint32_t, 4, -)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsubu8, ml_uint8_t, uint32_t, 8, -)

/** Vector Multiplication */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmulf2, ml_float2_t, float, 2, *)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmulf4, ml_float4_t, float, 4, *)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmulf8, ml_float8_t, float, 8, *)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmuld2, ml_double2_t, double, 2, *)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmuld4, ml_double4_t, double, 4, *)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmuld8, ml_double8_t, double, 8, *)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmuli2, ml_int2_t, int32_t, 2, *)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmuli4, ml_int4_t, int32_t, 4, *)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmuli8, ml_int8_t, int32_t, 8, *)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmulu2, ml_uint2_t, uint32_t, 2, *)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmulu4, ml_uint4_t, uint32_t, 4, *)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmulu8, ml_uint8_t, uint32_t, 8, *)

/** Vector Division */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivf2, ml_float2_t, float, 2, /)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivf4, ml_float4_t, float, 4, /)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivf8, ml_float8_t, float, 8, /)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivd2, ml_double2_t, double, 2, /)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivd4, ml_double4_t, double, 4, /)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivd8, ml_double8_t, double, 8, /)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivi2, ml_int2_t, int32_t, 2, /)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivi4, ml_int4_t, int32_t, 4, /)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivi8, ml_int8_t, int32_t, 8, /)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivu2, ml_uint2_t, uint32_t, 2, /)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivu4, ml_uint4_t, uint32_t, 4, /)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vdivu8, ml_uint8_t, uint32_t, 8, /)

/** Vector Modulo */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmodi2, ml_int2_t, int32_t, 2, %)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmodi4, ml_int4_t, int32_t, 4, %)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmodi8, ml_int8_t, int32_t, 8, %)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmodu2, ml_uint2_t, uint32_t, 2, %)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmodu4, ml_uint4_t, uint32_t, 4, %)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vmodu8, ml_uint8_t, uint32_t, 8, %)

/** Vector Logic Left Shift */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vslli2, ml_int2_t, int32_t, 2, <<)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vslli4, ml_int4_t, int32_t, 4, <<)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vslli8, ml_int8_t, int32_t, 8, <<)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsllu2, ml_uint2_t, uint32_t, 2, <<)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsllu4, ml_uint4_t, uint32_t, 4, <<)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsllu8, ml_uint8_t, uint32_t, 8, <<)

/** Vector Logic Right Shift */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrli2, ml_int2_t, int32_t, 2, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrli4, ml_int4_t, int32_t, 4, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrli8, ml_int8_t, int32_t, 8, >>)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrlu2, ml_uint2_t, uint32_t, 2, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrlu4, ml_uint4_t, uint32_t, 4, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrlu8, ml_uint8_t, uint32_t, 8, >>)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrll2, ml_long2_t, uint64_t, 2, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrll4, ml_long4_t, uint64_t, 4, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrll8, ml_long8_t, uint64_t, 8, >>)

/** Vector Arithmethic Right Shift */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrai2, ml_int2_t, int32_t, 2, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrai4, ml_int4_t, int32_t, 4, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrai8, ml_int8_t, int32_t, 8, >>)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrau2, ml_uint2_t, uint32_t, 2, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrau4, ml_uint4_t, uint32_t, 4, >>)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vsrau8, ml_uint8_t, uint32_t, 8, >>)

/** Vector Fused Multiply and Add */
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmaf2, ml_float2_t, float, 2, fmaf, +, +, +)
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmaf4, ml_float4_t, float, 4, fmaf, +, +, +)
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmaf8, ml_float8_t, float, 8, fmaf, +, +, +)

DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmad2, ml_double2_t, double, 2, fma, +, +, +)
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmad4, ml_double4_t, double, 4, fma, +, +, +)
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmad8, ml_double8_t, double, 8, fma, +, +, +)

DEF_ML_VECTOR_PRIMITIVES_OP3(ml_vfmai2, ml_int2_t, int32_t, 2, *, +)
DEF_ML_VECTOR_PRIMITIVES_OP3(ml_vfmai4, ml_int4_t, int32_t, 4, *, +)
DEF_ML_VECTOR_PRIMITIVES_OP3(ml_vfmai8, ml_int8_t, int32_t, 8, *, +)

DEF_ML_VECTOR_PRIMITIVES_OP3(ml_vfmau2, ml_uint2_t, uint32_t, 2, *, +)
DEF_ML_VECTOR_PRIMITIVES_OP3(ml_vfmau4, ml_uint4_t, uint32_t, 4, *, +)
DEF_ML_VECTOR_PRIMITIVES_OP3(ml_vfmau8, ml_uint8_t, uint32_t, 8, *, +)

DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmsf2, ml_float2_t, float, 2, fmaf, +, +, -)
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmsf4, ml_float4_t, float, 4, fmaf, +, +, -)
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmsf8, ml_float8_t, float, 8, fmaf, +, +, -)

DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmsd2, ml_double2_t, double, 2, fma, +, +, -)
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmsd4, ml_double4_t, double, 4, fma, +, +, -)
DEF_ML_VECTOR_PRIMITIVES_FUNC3(ml_vfmsd8, ml_double8_t, double, 8, fma, +, +, -)


/** Vector Negate */
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegf2, ml_float2_t, float, 2, -)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegf4, ml_float4_t, float, 4, -)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegf8, ml_float8_t, float, 8, -)

DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegd2, ml_double2_t, double, 2, -)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegd4, ml_double4_t, double, 4, -)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegd8, ml_double8_t, double, 8, -)

DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegi2, ml_int2_t, int32_t, 2, -)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegi4, ml_int4_t, int32_t, 4, -)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegi8, ml_int8_t, int32_t, 8, -)

DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegu2, ml_uint2_t, uint32_t, 2, -)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegu4, ml_uint4_t, uint32_t, 4, -)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnegu8, ml_uint8_t, uint32_t, 8, -)


/** Vector logical negation */
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnoti2, ml_int2_t, int32_t, 2, !)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnoti4, ml_int4_t, int32_t, 4, !)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnoti8, ml_int8_t, int32_t, 8, !)

DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnotu2, ml_uint2_t, uint32_t, 2, !)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnotu4, ml_uint4_t, uint32_t, 4, !)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnotu8, ml_uint8_t, uint32_t, 8, !)

DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnotb2, ml_bool2_t, uint32_t, 2, !)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnotb4, ml_bool4_t, uint32_t, 4, !)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vnotb8, ml_bool8_t, uint32_t, 8, !)


/** Vector logical and */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandi2, ml_int2_t, int32_t, 2, &&)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandi4, ml_int4_t, int32_t, 4, &&)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandi8, ml_int8_t, int32_t, 8, &&)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandu2, ml_uint2_t, int32_t, 2, &&)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandu4, ml_uint4_t, int32_t, 4, &&)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandu8, ml_uint8_t, int32_t, 8, &&)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandb2, ml_bool2_t, int32_t, 2, &&)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandb4, ml_bool4_t, int32_t, 4, &&)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vandb8, ml_bool8_t, int32_t, 8, &&)

/** Vector logical or */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vori2, ml_int2_t, int32_t, 2, ||)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vori4, ml_int4_t, int32_t, 4, ||)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vori8, ml_int8_t, int32_t, 8, ||)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_voru2, ml_uint2_t, int32_t, 2, ||)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_voru4, ml_uint4_t, int32_t, 4, ||)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_voru8, ml_uint8_t, int32_t, 8, ||)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vorb2, ml_bool2_t, int32_t, 2, ||)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vorb4, ml_bool4_t, int32_t, 4, ||)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vorb8, ml_bool8_t, int32_t, 8, ||)

/** Vector bitwise and */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandi2, ml_int2_t, int32_t, 2, &)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandi4, ml_int4_t, int32_t, 4, &)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandi8, ml_int8_t, int32_t, 8, &)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandu2, ml_uint2_t, int32_t, 2, &)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandu4, ml_uint4_t, int32_t, 4, &)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandu8, ml_uint8_t, int32_t, 8, &)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandl2, ml_long2_t, int64_t, 2, &)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandl4, ml_long4_t, int64_t, 4, &)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwandl8, ml_long8_t, int64_t, 8, &)

/** Vector bitwise or */
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwori2, ml_int2_t, int32_t, 2, |)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwori4, ml_int4_t, int32_t, 4, |)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbwori8, ml_int8_t, int32_t, 8, |)

DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbworu2, ml_uint2_t, int32_t, 2,|)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbworu4, ml_uint4_t, int32_t, 4,|)
DEF_ML_VECTOR_PRIMITIVES_OP2(ml_vbworu8, ml_uint8_t, int32_t, 8,|)

/** Vector bitwise not */
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vbwnoti2, ml_int2_t, int32_t, 2, ~)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vbwnoti4, ml_int4_t, int32_t, 4, ~)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vbwnoti8, ml_int8_t, int32_t, 8, ~)

DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vbwnotu2, ml_uint2_t, int32_t, 2,~)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vbwnotu4, ml_uint4_t, int32_t, 4,~)
DEF_ML_VECTOR_PRIMITIVES_OP1(ml_vbwnotu8, ml_uint8_t, int32_t, 8,~)

/** Comparison operations */
#define DEF_ML_VECTOR_COMPARATOR_OP2(FUNC_NAME, RESULT_FORMAT, VECTOR_FORMAT, VECTOR_SIZE, COMP_OP) \
static inline void FUNC_NAME(RESULT_FORMAT *r, VECTOR_FORMAT vop0, VECTOR_FORMAT vop1) {\
  unsigned i;\
  for (i = 0; i < VECTOR_SIZE; ++i) {\
    (*r)._[i] = vop0._[i] COMP_OP vop1._[i];\
  };\
}

/** 2-element vector comparison */
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_f2, ml_bool2_t, ml_float2_t, 2, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_f2, ml_bool2_t, ml_float2_t, 2, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_f2, ml_bool2_t, ml_float2_t, 2, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_f2, ml_bool2_t, ml_float2_t, 2, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_f2, ml_bool2_t, ml_float2_t, 2, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_f2, ml_bool2_t, ml_float2_t, 2, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_d2, ml_bool2_t, ml_double2_t, 2, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_d2, ml_bool2_t, ml_double2_t, 2, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_d2, ml_bool2_t, ml_double2_t, 2, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_d2, ml_bool2_t, ml_double2_t, 2, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_d2, ml_bool2_t, ml_double2_t, 2, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_d2, ml_bool2_t, ml_double2_t, 2, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_i2, ml_bool2_t, ml_int2_t, 2, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_i2, ml_bool2_t, ml_int2_t, 2, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_i2, ml_bool2_t, ml_int2_t, 2, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_i2, ml_bool2_t, ml_int2_t, 2, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_i2, ml_bool2_t, ml_int2_t, 2, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_i2, ml_bool2_t, ml_int2_t, 2, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_u2, ml_bool2_t, ml_uint2_t, 2, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_u2, ml_bool2_t, ml_uint2_t, 2, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_u2, ml_bool2_t, ml_uint2_t, 2, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_u2, ml_bool2_t, ml_uint2_t, 2, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_u2, ml_bool2_t, ml_uint2_t, 2, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_u2, ml_bool2_t, ml_uint2_t, 2, !=)

/** 4-element vector comparison */
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_f4, ml_bool4_t, ml_float4_t, 4, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_f4, ml_bool4_t, ml_float4_t, 4, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_f4, ml_bool4_t, ml_float4_t, 4, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_f4, ml_bool4_t, ml_float4_t, 4, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_f4, ml_bool4_t, ml_float4_t, 4, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_f4, ml_bool4_t, ml_float4_t, 4, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_d4, ml_bool4_t, ml_double4_t, 4, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_d4, ml_bool4_t, ml_double4_t, 4, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_d4, ml_bool4_t, ml_double4_t, 4, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_d4, ml_bool4_t, ml_double4_t, 4, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_d4, ml_bool4_t, ml_double4_t, 4, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_d4, ml_bool4_t, ml_double4_t, 4, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_i4, ml_bool4_t, ml_int4_t, 4, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_i4, ml_bool4_t, ml_int4_t, 4, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_i4, ml_bool4_t, ml_int4_t, 4, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_i4, ml_bool4_t, ml_int4_t, 4, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_i4, ml_bool4_t, ml_int4_t, 4, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_i4, ml_bool4_t, ml_int4_t, 4, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_u4, ml_bool4_t, ml_uint4_t, 4, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_u4, ml_bool4_t, ml_uint4_t, 4, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_u4, ml_bool4_t, ml_uint4_t, 4, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_u4, ml_bool4_t, ml_uint4_t, 4, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_u4, ml_bool4_t, ml_uint4_t, 4, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_u4, ml_bool4_t, ml_uint4_t, 4, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_l4, ml_bool4_t, ml_long4_t, 4, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_l4, ml_bool4_t, ml_long4_t, 4, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_l4, ml_bool4_t, ml_long4_t, 4, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_l4, ml_bool4_t, ml_long4_t, 4, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_l4, ml_bool4_t, ml_long4_t, 4, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_l4, ml_bool4_t, ml_long4_t, 4, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_ul4, ml_bool4_t, ml_ulong4_t, 4, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_ul4, ml_bool4_t, ml_ulong4_t, 4, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_ul4, ml_bool4_t, ml_ulong4_t, 4, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_ul4, ml_bool4_t, ml_ulong4_t, 4, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_ul4, ml_bool4_t, ml_ulong4_t, 4, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_ul4, ml_bool4_t, ml_ulong4_t, 4, !=)

/** 8-element vector comparison */
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_f8, ml_bool8_t, ml_float8_t, 8, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_f8, ml_bool8_t, ml_float8_t, 8, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_f8, ml_bool8_t, ml_float8_t, 8, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_f8, ml_bool8_t, ml_float8_t, 8, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_f8, ml_bool8_t, ml_float8_t, 8, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_f8, ml_bool8_t, ml_float8_t, 8, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_d8, ml_bool8_t, ml_double8_t, 8, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_d8, ml_bool8_t, ml_double8_t, 8, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_d8, ml_bool8_t, ml_double8_t, 8, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_d8, ml_bool8_t, ml_double8_t, 8, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_d8, ml_bool8_t, ml_double8_t, 8, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_d8, ml_bool8_t, ml_double8_t, 8, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_i8, ml_bool8_t, ml_int8_t, 8, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_i8, ml_bool8_t, ml_int8_t, 8, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_i8, ml_bool8_t, ml_int8_t, 8, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_i8, ml_bool8_t, ml_int8_t, 8, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_i8, ml_bool8_t, ml_int8_t, 8, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_i8, ml_bool8_t, ml_int8_t, 8, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_u8, ml_bool8_t, ml_uint8_t, 8, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_u8, ml_bool8_t, ml_uint8_t, 8, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_u8, ml_bool8_t, ml_uint8_t, 8, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_u8, ml_bool8_t, ml_uint8_t, 8, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_u8, ml_bool8_t, ml_uint8_t, 8, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_u8, ml_bool8_t, ml_uint8_t, 8, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_l8, ml_bool8_t, ml_long8_t, 8, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_l8, ml_bool8_t, ml_long8_t, 8, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_l8, ml_bool8_t, ml_long8_t, 8, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_l8, ml_bool8_t, ml_long8_t, 8, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_l8, ml_bool8_t, ml_long8_t, 8, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_l8, ml_bool8_t, ml_long8_t, 8, !=)

DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_gt_ul8, ml_bool8_t, ml_ulong8_t, 8, >)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ge_ul8, ml_bool8_t, ml_ulong8_t, 8, >=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_lt_ul8, ml_bool8_t, ml_ulong8_t, 8, <)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_le_ul8, ml_bool8_t, ml_ulong8_t, 8, <=)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_eq_ul8, ml_bool8_t, ml_ulong8_t, 8, ==)
DEF_ML_VECTOR_COMPARATOR_OP2(ml_comp_ne_ul8, ml_bool8_t, ml_ulong8_t, 8, !=)


/** Specific tests */
#define DEF_ML_VECTOR_TEST_FUNC_OP1(FUNC_NAME, RESULT_FORMAT, VECTOR_FORMAT, VECTOR_SIZE, SCALAR_TEST_FUNC) \
static inline void FUNC_NAME(RESULT_FORMAT *r, VECTOR_FORMAT vop) {\
  unsigned i;\
  for (i = 0; i < VECTOR_SIZE; ++i) {\
    (*r)._[i] = SCALAR_TEST_FUNC(vop._[i]);\
  };\
}

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf2_is_nan_or_inf, ml_bool2_t, ml_float2_t, 2, ml_is_nan_or_inff)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf4_is_nan_or_inf, ml_bool4_t, ml_float4_t, 4, ml_is_nan_or_inff)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf8_is_nan_or_inf, ml_bool8_t, ml_float8_t, 8, ml_is_nan_or_inff)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd2_is_nan_or_inf, ml_bool2_t, ml_double2_t, 2, ml_is_nan_or_inf)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd4_is_nan_or_inf, ml_bool4_t, ml_double4_t, 4, ml_is_nan_or_inf)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd8_is_nan_or_inf, ml_bool8_t, ml_double8_t, 8, ml_is_nan_or_inf)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf2_is_nan, ml_bool2_t, ml_float2_t, 2, ml_is_nanf)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf4_is_nan, ml_bool4_t, ml_float4_t, 4, ml_is_nanf)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf8_is_nan, ml_bool8_t, ml_float8_t, 8, ml_is_nanf)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd2_is_nan, ml_bool2_t, ml_double2_t, 2, ml_is_nan)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd4_is_nan, ml_bool4_t, ml_double4_t, 4, ml_is_nan)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd8_is_nan, ml_bool8_t, ml_double8_t, 8, ml_is_nan)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf2_is_inf, ml_bool2_t, ml_float2_t, 2, ml_is_inff)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf4_is_inf, ml_bool4_t, ml_float4_t, 4, ml_is_inff)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf8_is_inf, ml_bool8_t, ml_float8_t, 8, ml_is_inff)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd2_is_inf, ml_bool2_t, ml_double2_t, 2, ml_is_inf)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd4_is_inf, ml_bool4_t, ml_double4_t, 4, ml_is_inf)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd8_is_inf, ml_bool8_t, ml_double8_t, 8, ml_is_inf)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf2_is_zero, ml_bool2_t, ml_float2_t, 2, ml_is_zerof)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf4_is_zero, ml_bool4_t, ml_float4_t, 4, ml_is_zerof)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf8_is_zero, ml_bool8_t, ml_float8_t, 8, ml_is_zerof)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd2_is_zero, ml_bool2_t, ml_double2_t, 2, ml_is_zero)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd4_is_zero, ml_bool4_t, ml_double4_t, 4, ml_is_zero)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd8_is_zero, ml_bool8_t, ml_double8_t, 8, ml_is_zero)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf2_is_subnormal, ml_bool2_t, ml_float2_t, 2, ml_is_subnormalf)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf4_is_subnormal, ml_bool4_t, ml_float4_t, 4, ml_is_subnormalf)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestf8_is_subnormal, ml_bool8_t, ml_float8_t, 8, ml_is_subnormalf)

DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd2_is_subnormal, ml_bool2_t, ml_double2_t, 2, ml_is_subnormal)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd4_is_subnormal, ml_bool4_t, ml_double4_t, 4, ml_is_subnormal)
DEF_ML_VECTOR_TEST_FUNC_OP1(ml_vtestd8_is_subnormal, ml_bool8_t, ml_double8_t, 8, ml_is_subnormal)

static inline int ml_is_vmask2_zero(ml_bool2_t vop) {
  return (vop._[0] == 0) && (vop._[1] == 0);
}
static inline int ml_is_vmask4_zero(ml_bool4_t vop) {
  return (vop._[0] == 0) && 
         (vop._[1] == 0) && 
         (vop._[2] == 0) && 
         (vop._[3] == 0);
}
static inline int ml_is_vmask8_zero(ml_bool8_t vop) {
  return (vop._[0] == 0) && 
         (vop._[1] == 0) && 
         (vop._[2] == 0) && 
         (vop._[3] == 0) && 
         (vop._[4] == 0) && 
         (vop._[5] == 0) && 
         (vop._[6] == 0) && 
         (vop._[7] == 0);
}

static inline int ml_is_vmask2_any_zero(ml_bool2_t vop) {
  return (vop._[0] == 0) || (vop._[1] == 0);
}
static inline int ml_is_vmask4_any_zero(ml_bool4_t vop) {
  return (vop._[0] == 0) || 
         (vop._[1] == 0) || 
         (vop._[2] == 0) || 
         (vop._[3] == 0);
}
static inline int ml_is_vmask8_any_zero(ml_bool8_t vop) {
  return (vop._[0] == 0) || 
         (vop._[1] == 0) || 
         (vop._[2] == 0) || 
         (vop._[3] == 0) || 
         (vop._[4] == 0) || 
         (vop._[5] == 0) || 
         (vop._[6] == 0) || 
         (vop._[7] == 0);
}

static inline int ml_is_vmask2_not_any_zero(ml_bool2_t vop) {
  return (vop._[0] != 0) && (vop._[1] != 0);
}
static inline int ml_is_vmask4_not_any_zero(ml_bool4_t vop) {
  return (vop._[0] != 0) && 
         (vop._[1] != 0) && 
         (vop._[2] != 0) && 
         (vop._[3] != 0);
}
static inline int ml_is_vmask8_not_any_zero(ml_bool8_t vop) {
  return (vop._[0] != 0) && 
         (vop._[1] != 0) && 
         (vop._[2] != 0) && 
         (vop._[3] != 0) && 
         (vop._[4] != 0) && 
         (vop._[5] != 0) && 
         (vop._[6] != 0) && 
         (vop._[7] != 0);
}

static inline int ml_is_vmask2_not_all_zero(ml_bool2_t vop) {
  return (vop._[0] != 0) || (vop._[1] != 0);
}
static inline int ml_is_vmask4_not_all_zero(ml_bool4_t vop) {
  return (vop._[0] != 0) || 
         (vop._[1] != 0) || 
         (vop._[2] != 0) || 
         (vop._[3] != 0);
}
static inline int ml_is_vmask8_not_all_zero(ml_bool8_t vop) {
  return (vop._[0] != 0) || 
         (vop._[1] != 0) || 
         (vop._[2] != 0) || 
         (vop._[3] != 0) || 
         (vop._[4] != 0) || 
         (vop._[5] != 0) || 
         (vop._[6] != 0) || 
         (vop._[7] != 0);
}

/** Vector Assembling functions **/
#define DEF_ML_VECTOR_ASSEMBLY_FUNC_1_2(FUNC_NAME, RESULT_FORMAT, SCALAR_FORMAT) \
static inline void FUNC_NAME(RESULT_FORMAT *r, SCALAR_FORMAT op1, SCALAR_FORMAT op2) {\
    (*r)._[0] = op1; (*r)._[1] = op2;\
}

#define DEF_ML_VECTOR_ASSEMBLY_FUNC_1_4(FUNC_NAME, RESULT_FORMAT, SCALAR_FORMAT) \
static inline void FUNC_NAME(RESULT_FORMAT *r, SCALAR_FORMAT op1, SCALAR_FORMAT op2, SCALAR_FORMAT op3, SCALAR_FORMAT op4) {\
    (*r)._[0] = op1; (*r)._[1] = op2; (*r)._[2] = op3; (*r)._[3] = op4;\
}

#define DEF_ML_VECTOR_ASSEMBLY_FUNC_2_4(FUNC_NAME, RESULT_FORMAT, VECTOR_FORMAT) \
static inline void FUNC_NAME(RESULT_FORMAT *r, VECTOR_FORMAT vop1, VECTOR_FORMAT vop2) {\
  (*r)._[0] = vop1._[0]; (*r)._[1] = vop1._[1] ; (*r)._[2] = vop2._[0] ; (*r)._[3] = vop2._[1] ;\
}

#define DEF_ML_VECTOR_ASSEMBLY_FUNC_2_8(FUNC_NAME, RESULT_FORMAT, VECTOR_FORMAT) \
static inline void FUNC_NAME(RESULT_FORMAT *r, VECTOR_FORMAT vop1, VECTOR_FORMAT vop2, VECTOR_FORMAT vop3, VECTOR_FORMAT vop4) {\
  (*r)._[0] = vop1._[0]; (*r)._[1] = vop1._[1] ; (*r)._[2] = vop2._[0] ; (*r)._[3] = vop2._[1] ;\
  (*r)._[4] = vop3._[0]; (*r)._[5] = vop3._[1] ; (*r)._[6] = vop4._[0] ; (*r)._[7] = vop4._[1] ;\
}

#define DEF_ML_VECTOR_ASSEMBLY_FUNC_4_8(FUNC_NAME, RESULT_FORMAT, VECTOR_FORMAT) \
static inline void FUNC_NAME(RESULT_FORMAT *r, VECTOR_FORMAT vop1, VECTOR_FORMAT vop2) {\
  (*r)._[0] = vop1._[0]; (*r)._[1] = vop1._[1] ; (*r)._[2] = vop1._[2] ; (*r)._[3] = vop1._[3] ;\
  (*r)._[4] = vop2._[0]; (*r)._[5] = vop2._[1] ; (*r)._[6] = vop2._[2] ; (*r)._[7] = vop2._[3] ;\
}

DEF_ML_VECTOR_ASSEMBLY_FUNC_1_2(ml_vec_assembling_1_2_float, ml_float2_t, float)
DEF_ML_VECTOR_ASSEMBLY_FUNC_1_2(ml_vec_assembling_1_2_int, ml_int2_t, int32_t)
DEF_ML_VECTOR_ASSEMBLY_FUNC_1_2(ml_vec_assembling_1_2_bool, ml_bool2_t, bool)

DEF_ML_VECTOR_ASSEMBLY_FUNC_1_4(ml_vec_assembling_1_4_float, ml_float4_t, float)
DEF_ML_VECTOR_ASSEMBLY_FUNC_1_4(ml_vec_assembling_1_4_int, ml_int4_t, int32_t)
DEF_ML_VECTOR_ASSEMBLY_FUNC_1_4(ml_vec_assembling_1_4_bool, ml_bool4_t, bool)
DEF_ML_VECTOR_ASSEMBLY_FUNC_1_4(ml_vec_assembling_1_4_double, ml_double4_t, double)

DEF_ML_VECTOR_ASSEMBLY_FUNC_2_4(ml_vec_assembling_2_4_float, ml_float4_t, ml_float2_t)
DEF_ML_VECTOR_ASSEMBLY_FUNC_2_4(ml_vec_assembling_2_4_int, ml_int4_t, ml_int2_t)
DEF_ML_VECTOR_ASSEMBLY_FUNC_2_4(ml_vec_assembling_2_4_bool, ml_bool4_t, ml_bool2_t)

DEF_ML_VECTOR_ASSEMBLY_FUNC_2_8(ml_vec_assembling_2_8_float, ml_float8_t, ml_float2_t)
DEF_ML_VECTOR_ASSEMBLY_FUNC_2_8(ml_vec_assembling_2_8_int, ml_int8_t, ml_int2_t)
DEF_ML_VECTOR_ASSEMBLY_FUNC_2_8(ml_vec_assembling_2_8_bool, ml_bool8_t, ml_bool2_t)

DEF_ML_VECTOR_ASSEMBLY_FUNC_4_8(ml_vec_assembling_4_8_float, ml_float8_t, ml_float4_t)
DEF_ML_VECTOR_ASSEMBLY_FUNC_4_8(ml_vec_assembling_4_8_int, ml_int8_t, ml_int4_t)
DEF_ML_VECTOR_ASSEMBLY_FUNC_4_8(ml_vec_assembling_4_8_bool, ml_bool8_t, ml_bool4_t)

DEF_ML_VECTOR_ASSEMBLY_FUNC_4_8(ml_vec_assembling_4_8_double, ml_double8_t, ml_double4_t)

/** Single Argument function with non-uniform formats */
#define DEF_ML_VECTOR_NONUN_FUNC_OP1(FUNC_NAME, RESULT_FORMAT, VECTOR_FORMAT, VECTOR_SIZE, SCALAR_TEST_FUNC) \
static inline void FUNC_NAME(RESULT_FORMAT *r, VECTOR_FORMAT vop) {\
  unsigned i;\
  for (i = 0; i < VECTOR_SIZE; ++i) {\
    (*r)._[i] = SCALAR_TEST_FUNC(vop._[i]);\
  };\
}

DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vnearbyintd2, ml_long2_t, ml_double2_t, 2, nearbyint)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vnearbyintd4, ml_long4_t, ml_double4_t, 4, nearbyint)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vnearbyintd8, ml_long8_t, ml_double8_t, 8, nearbyint)

#ifdef __k1__
static inline void ml_vnearbyintf2(ml_int2_t *r, ml_float2_t vop) {
  unsigned i;
  for (i = 0; i < 2; ++i) {
    (*r)._[i] = __builtin_k1_fixed(_K1_FPU_NEAREST_EVEN, vop._[i], 0);
  };
}
static inline void ml_vnearbyintf4(ml_int4_t *r, ml_float4_t vop) {
  unsigned i;
  for (i = 0; i < 4; ++i) {
    (*r)._[i] = __builtin_k1_fixed(_K1_FPU_NEAREST_EVEN, vop._[i], 0);
  };
}
static inline void ml_vnearbyintf8(ml_int8_t *r, ml_float8_t vop) {
  unsigned i;
  for (i = 0; i < 8; ++i) {
    (*r)._[i] = __builtin_k1_fixed(_K1_FPU_NEAREST_EVEN, vop._[i], 0);
  };
}

static inline void ml_vrintf2(ml_float2_t *r, ml_float2_t vop) {
  unsigned i;
  for (i = 0; i < 2; ++i) {
    (*r)._[i] = __builtin_k1_float(_K1_FPU_NEAREST_EVEN, __builtin_k1_fixed(_K1_FPU_NEAREST_EVEN, vop._[i], 0), 0);
  };
}
static inline void ml_vrintf4(ml_float4_t *r, ml_float4_t vop) {
  unsigned i;
  for (i = 0; i < 4; ++i) {
    (*r)._[i] = __builtin_k1_float(_K1_FPU_NEAREST_EVEN, __builtin_k1_fixed(_K1_FPU_NEAREST_EVEN, vop._[i], 0), 0);
  };
}
static inline void ml_vrintf8(ml_float8_t *r, ml_float8_t vop) {
  unsigned i;
  for (i = 0; i < 8; ++i) {
    (*r)._[i] = __builtin_k1_float(_K1_FPU_NEAREST_EVEN, __builtin_k1_fixed(_K1_FPU_NEAREST_EVEN, vop._[i], 0), 0);
  };
}

#else
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vnearbyintf2, ml_int2_t, ml_float2_t, 2, nearbyintf)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vnearbyintf4, ml_int4_t, ml_float4_t, 4, nearbyintf)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vnearbyintf8, ml_int8_t, ml_float8_t, 8, nearbyintf)

DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vrintf2, ml_float2_t, ml_float2_t, 2, rintf)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vrintf4, ml_float4_t, ml_float4_t, 4, rintf)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vrintf8, ml_float8_t, ml_float8_t, 8, rintf)
#endif

DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vrintd2, ml_double2_t, ml_double2_t, 2, rint)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vrintd4, ml_double4_t, ml_double4_t, 4, rint)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vrintd8, ml_double8_t, ml_double8_t, 8, rint)

/** Exponent insertion */
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_insertion_f2, ml_float2_t, ml_int2_t, 2, ml_exp_insertion_fp32)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_insertion_f4, ml_float4_t, ml_int4_t, 4, ml_exp_insertion_fp32)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_insertion_f8, ml_float8_t, ml_int8_t, 8, ml_exp_insertion_fp32)

DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_insertion_d2, ml_double2_t, ml_long2_t, 2, ml_exp_insertion_fp64)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_insertion_d4, ml_double4_t, ml_long4_t, 4, ml_exp_insertion_fp64)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_insertion_d8, ml_double8_t, ml_long8_t, 8, ml_exp_insertion_fp64)

/** Exponent extraction */
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_extraction_f2, ml_int2_t, ml_float2_t, 2, ml_exp_extraction_dirty_fp32)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_extraction_f4, ml_int4_t, ml_float4_t, 4, ml_exp_extraction_dirty_fp32)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_extraction_f8, ml_int8_t, ml_float8_t, 8, ml_exp_extraction_dirty_fp32)

DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_extraction_d2, ml_int2_t, ml_double2_t, 2, ml_exp_extraction_dirty_fp64)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_extraction_d4, ml_int4_t, ml_double4_t, 4, ml_exp_extraction_dirty_fp64)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vexp_extraction_d8, ml_int8_t, ml_double8_t, 8, ml_exp_extraction_dirty_fp64)

/** Mantissa extraction */
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vmantissa_extraction_f2, ml_float2_t, ml_float2_t, 2, ml_mantissa_extraction_fp32)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vmantissa_extraction_f4, ml_float4_t, ml_float4_t, 4, ml_mantissa_extraction_fp32)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vmantissa_extraction_f8, ml_float8_t, ml_float8_t, 8, ml_mantissa_extraction_fp32)

DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vmantissa_extraction_d2, ml_double2_t, ml_double2_t, 2, ml_mantissa_extraction_fp64)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vmantissa_extraction_d4, ml_double4_t, ml_double4_t, 4, ml_mantissa_extraction_fp64)
DEF_ML_VECTOR_NONUN_FUNC_OP1(ml_vmantissa_extraction_d8, ml_double8_t, ml_double8_t, 8, ml_mantissa_extraction_fp64)


/** Vector element-wise selection */
#define ML_VSELECT(result,test,op0,op1,size) {\
  unsigned __k; for (__k = 0; __k < size; ++__k) (result)->_[__k] = (test)._[__k] ? (op0)._[__k] : (op1)._[__k]; };

/** Vector element-wise load (gather) */
#define ML_VLOAD(result,table,addr,size) {\
  unsigned __k; for (__k = 0; __k < size; ++__k) (result)->_[__k] = table[(addr)._[__k]]; };
/** Vector element-wise load (gather) for 2D table */
#define ML_VLOAD2D(result,table,addr0,addr1,size) {\
  unsigned __k; for (__k = 0; __k < size; ++__k) (result)->_[__k] = table[(addr0)._[__k]][(addr1)._[__k]]; };
/** Implicit vector conversion */
#define ML_VCONV(dst,src,size) {\
  unsigned __k; for (__k = 0; __k < size; ++__k) (dst)->_[__k] = (src)._[__k]; };
