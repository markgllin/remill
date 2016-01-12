/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

namespace {

template <typename T>
ALWAYS_INLINE void SetFlagsLogical(State &state, T lhs, T rhs, T res) {
  state.aflag.cf = false;
  state.aflag.pf = ParityFlag(res);
  state.aflag.zf = ZeroFlag(res);
  state.aflag.sf = SignFlag(res);
  state.aflag.of = false;
}

template <typename D, typename S1, typename S2>
DEF_SEM(AND, D dst, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  const T src1 = R(src1_);
  const T src2 = R(src2_);
  const T res = src1 & src2;
  W(dst) = res;
  __mcsema_barrier_compiler();
  SetFlagsLogical(state, src1, src2, res);
}

template <typename D, typename S1, typename S2>
DEF_SEM(OR, D dst, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  const T src1 = R(src1_);
  const T src2 = R(src2_);
  const T res = src1 | src2;
  W(dst) = res;
  __mcsema_barrier_compiler();
  SetFlagsLogical(state, src1, src2, res);
}

template <typename D, typename S1, typename S2>
DEF_SEM(XOR, D dst, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  const T src1 = R(src1_);
  const T src2 = R(src2_);
  const T res = src1 ^ src2;
  W(dst) = res;
  __mcsema_barrier_compiler();
  SetFlagsLogical(state, src1, src2, res);
}

template <typename D, typename S1>
DEF_SEM(NOT, D dst_src1, S1 src1_) {
  W(dst_src1) = ~R(src1_);
}

template <typename S1, typename S2>
DEF_SEM(TEST, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  const T src1 = R(src1_);
  const T src2 = R(src2_);
  const T res = src1 & src2;
  SetFlagsLogical(state, src1, src2, res);
}

}  // namespace

DEF_ISEL(AND_MEMb_IMMb_80r4_8) = AND<M8W, M8, I8>;
DEF_ISEL(AND_GPR8_IMMb_80r4_8) = AND<R8W, R8, I8>;
DEF_ISEL_MnW_Mn_In(AND_MEMv_IMMz, AND);
DEF_ISEL_RnW_Rn_In(AND_GPRv_IMMz, AND);
DEF_ISEL(AND_MEMb_IMMb_82r4_8) = AND<M8W, M8, I8>;
DEF_ISEL(AND_GPR8_IMMb_82r4_8) = AND<R8W, R8, I8>;
DEF_ISEL_MnW_Mn_In(AND_MEMv_IMMb, AND);
DEF_ISEL_RnW_Rn_In(AND_GPRv_IMMb, AND);
DEF_ISEL(AND_MEMb_GPR8_8) = AND<M8W, M8, R8>;
DEF_ISEL(AND_GPR8_GPR8_20_8) = AND<R8W, R8, R8>;
DEF_ISEL_MnW_Mn_Rn(AND_MEMv_GPRv, AND);
DEF_ISEL_RnW_Rn_Rn(AND_GPRv_GPRv_21, AND);
DEF_ISEL(AND_GPR8_GPR8_22_8) = AND<R8W, R8, R8>;
DEF_ISEL(AND_GPR8_MEMb_8) = AND<R8W, R8, M8>;
DEF_ISEL_RnW_Rn_Rn(AND_GPRv_GPRv_23, AND);
DEF_ISEL_RnW_Rn_Mn(AND_GPRv_MEMv, AND);
DEF_ISEL(AND_AL_IMMb_8) = AND<R8W, R8, I8>;
DEF_ISEL_RnW_Rn_In(AND_OrAX_IMMz, AND);

DEF_ISEL(OR_MEMb_IMMb_80r1_8) = OR<M8W, M8, I8>;
DEF_ISEL(OR_GPR8_IMMb_80r1_8) = OR<R8W, R8, I8>;
DEF_ISEL_MnW_Mn_In(OR_MEMv_IMMz, OR);
DEF_ISEL_RnW_Rn_In(OR_GPRv_IMMz, OR);
DEF_ISEL(OR_MEMb_IMMb_82r1_8) = OR<M8W, M8, I8>;
DEF_ISEL(OR_GPR8_IMMb_82r1_8) = OR<R8W, R8, I8>;
DEF_ISEL_MnW_Mn_In(OR_MEMv_IMMb, OR);
DEF_ISEL_RnW_Rn_In(OR_GPRv_IMMb, OR);
DEF_ISEL(OR_MEMb_GPR8_8) = OR<M8W, M8, R8>;
DEF_ISEL(OR_GPR8_GPR8_08_8) = OR<R8W, R8, R8>;
DEF_ISEL_MnW_Mn_Rn(OR_MEMv_GPRv, OR);
DEF_ISEL_RnW_Rn_Rn(OR_GPRv_GPRv_09, OR);
DEF_ISEL(OR_GPR8_MEMb_8) = OR<R8W, R8, M8>;
DEF_ISEL(OR_GPR8_GPR8_0A_8) = OR<R8W, R8, R8>;
DEF_ISEL_RnW_Rn_Mn(OR_GPRv_MEMv, OR);
DEF_ISEL_RnW_Rn_Rn(OR_GPRv_GPRv_0B, OR);
DEF_ISEL(OR_AL_IMMb_8) = OR<R8W, R8, I8>;
DEF_ISEL_RnW_Rn_In(OR_OrAX_IMMz, OR);

DEF_ISEL(XOR_MEMb_IMMb_80r6_8) = XOR<M8W, M8, I8>;
DEF_ISEL(XOR_GPR8_IMMb_80r6_8) = XOR<R8W, R8, I8>;
DEF_ISEL_MnW_Mn_In(XOR_MEMv_IMMz, XOR);
DEF_ISEL_RnW_Rn_In(XOR_GPRv_IMMz, XOR);
DEF_ISEL(XOR_MEMb_IMMb_82r6_8) = XOR<M8W, M8, I8>;
DEF_ISEL(XOR_GPR8_IMMb_82r6_8) = XOR<R8W, R8, I8>;
DEF_ISEL_MnW_Mn_In(XOR_MEMv_IMMb, XOR);
DEF_ISEL_RnW_Rn_In(XOR_GPRv_IMMb, XOR);
DEF_ISEL(XOR_MEMb_GPR8_8) = XOR<M8W, M8, R8>;
DEF_ISEL(XOR_GPR8_GPR8_30_8) = XOR<R8W, R8, R8>;
DEF_ISEL_MnW_Mn_Rn(XOR_MEMv_GPRv, XOR);
DEF_ISEL_RnW_Rn_Rn(XOR_GPRv_GPRv_31, XOR);
DEF_ISEL(XOR_GPR8_GPR8_32_8) = XOR<R8W, R8, R8>;
DEF_ISEL(XOR_GPR8_MEMb_8) = XOR<R8W, R8, M8>;
DEF_ISEL_RnW_Rn_Rn(XOR_GPRv_GPRv_33, XOR);
DEF_ISEL_RnW_Rn_Mn(XOR_GPRv_MEMv, XOR);
DEF_ISEL(XOR_AL_IMMb_8) = XOR<R8W, R8, I8>;
DEF_ISEL_RnW_Rn_In(XOR_OrAX_IMMz, XOR);

DEF_ISEL(NOT_MEMb_8) = NOT<M8W, M8>;
DEF_ISEL(NOT_GPR8_8) = NOT<R8W, R8>;
DEF_ISEL_MnW_Mn(NOT_MEMv, NOT);
DEF_ISEL_RnW_Rn(NOT_GPRv, NOT);

DEF_ISEL(TEST_MEMb_IMMb_F6r0_8) = TEST<M8, I8>;
DEF_ISEL(TEST_MEMb_IMMb_F6r1_8) = TEST<M8, I8>;
DEF_ISEL(TEST_GPR8_IMMb_F6r0_8) = TEST<R8, I8>;
DEF_ISEL(TEST_GPR8_IMMb_F6r1_8) = TEST<R8, I8>;
DEF_ISEL_Mn_In(TEST_MEMv_IMMz_F7r0, TEST);
DEF_ISEL_Mn_In(TEST_MEMv_IMMz_F7r1, TEST);
DEF_ISEL_Rn_In(TEST_GPRv_IMMz_F7r0, TEST);
DEF_ISEL_Rn_In(TEST_GPRv_IMMz_F7r1, TEST);
DEF_ISEL(TEST_MEMb_GPR8_8) = TEST<M8, R8>;
DEF_ISEL(TEST_GPR8_GPR8_8) = TEST<R8, R8>;
DEF_ISEL_Mn_Rn(TEST_MEMv_GPRv, TEST);
DEF_ISEL_Rn_Rn(TEST_GPRv_GPRv, TEST);
DEF_ISEL(TEST_AL_IMMb_8) = TEST<R8, I8>;
DEF_ISEL_Rn_In(TEST_OrAX_IMMz, TEST);

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PAND, D dst, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  typedef typename BaseType<D>::Type DT;  // Note: sizeof(DT) >= sizeof(T).
  const DT src1 = R(src1_);
  const DT src2 = R(src2_);
  W(dst) = src1.iwords & src2.iwords;
}

template <typename D, typename S1, typename S2>
DEF_SEM(PANDN, D dst, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  typedef typename BaseType<D>::Type DT;  // Note: sizeof(DT) >= sizeof(T).
  const DT src1 = R(src1_);
  const DT src2 = R(src2_);
  W(dst) = (~src1.iwords) & src2.iwords;
}
template <typename D, typename S1, typename S2>
DEF_SEM(POR, D dst, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  typedef typename BaseType<D>::Type DT;  // Note: sizeof(DT) >= sizeof(T).
  const DT src1 = R(src1_);
  const DT src2 = R(src2_);
  W(dst) = src1.iwords | src2.iwords;
}
template <typename D, typename S1, typename S2>
DEF_SEM(PXOR, D dst, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  typedef typename BaseType<D>::Type DT;  // Note: sizeof(DT) >= sizeof(T).
  const DT src1 = R(src1_);
  const DT src2 = R(src2_);
  W(dst) = src1.iwords ^ src2.iwords;
}

template <typename S1, typename S2>
DEF_SEM(PTEST, S1 src1_, S2 src2_) {
  typedef typename BaseType<S1>::Type T;
  const T src1 = R(src1_);
  const T src2 = R(src2_);

  __mcsema_barrier_compiler();

  T zero;
  zero.iwords = {0};

  T and_res;
  and_res.iwords = src1.iwords & src2.iwords;
  //state.aflag.zf = and_res.iwords == zero.iwords;

  T andn_res;
  andn_res.iwords = (~src1.iwords) & src2.iwords;
  //state.aflag.cf = andn_res.iwords == zero.iwords;

  state.aflag.pf = false;
  state.aflag.af = false;
  state.aflag.sf = false;
  state.aflag.of = false;
}

}  // namespace

DEF_ISEL(PXORq_MEMq_64) = PXOR<V64W, V64, MV64>;
DEF_ISEL(PXORqq_64) = PXOR<V64W, V64, V64>;
DEF_ISEL(PXOR_XMMdq_MEMdq_32) = PXOR<V128W, V128, MV128>;
DEF_ISEL(PXOR_XMMdq_XMMdq_32) = PXOR<V128W, V128, V128>;
IF_AVX( DEF_ISEL(VPXOR_XMMdq_XMMdq_MEMdq_128) = PXOR<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VPXOR_XMMdq_XMMdq_XMMdq_128) = PXOR<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VPXOR_YMMqq_YMMqq_MEMqq_256) = PXOR<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VPXOR_YMMqq_YMMqq_YMMqq_256) = PXOR<VV256W, VV256, VV256>; )

DEF_ISEL(XORPD_XMMpd_MEMpd_64) = PXOR<V128W, V128, MV128>;
DEF_ISEL(XORPD_XMMpd_XMMpd_64) = PXOR<V128W, V128, V128>;
DEF_ISEL(XORPS_XMMps_MEMps_32) = PXOR<V128W, V128, MV128>;
DEF_ISEL(XORPS_XMMps_XMMps_32) = PXOR<V128W, V128, V128>;
IF_AVX( DEF_ISEL(VXORPD_XMMdq_XMMdq_MEMdq_64) = PXOR<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VXORPD_XMMdq_XMMdq_XMMdq_64) = PXOR<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VXORPD_YMMqq_YMMqq_MEMqq_64) = PXOR<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VXORPD_YMMqq_YMMqq_YMMqq_64) = PXOR<VV256W, VV256, VV256>; )
IF_AVX( DEF_ISEL(VXORPS_XMMdq_XMMdq_MEMdq_32) = PXOR<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VXORPS_XMMdq_XMMdq_XMMdq_32) = PXOR<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VXORPS_YMMqq_YMMqq_MEMqq_32) = PXOR<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VXORPS_YMMqq_YMMqq_YMMqq_32) = PXOR<VV256W, VV256, VV256>; )

DEF_ISEL(PANDq_MEMq_64) = PAND<V64W, V64, MV64>;
DEF_ISEL(PANDqq_64) = PAND<V64W, V64, V64>;
DEF_ISEL(PAND_XMMdq_MEMdq_32) = PAND<V128W, V128, MV128>;
DEF_ISEL(PAND_XMMdq_XMMdq_32) = PAND<V128W, V128, V128>;
IF_AVX( DEF_ISEL(VPAND_XMMdq_XMMdq_MEMdq_128) = PAND<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VPAND_XMMdq_XMMdq_XMMdq_128) = PAND<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VPAND_YMMqq_YMMqq_MEMqq_256) = PAND<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VPAND_YMMqq_YMMqq_YMMqq_256) = PAND<VV256W, VV256, VV256>; )

DEF_ISEL(ANDPD_XMMpd_MEMpd_64) = PAND<V128W, V128, MV128>;
DEF_ISEL(ANDPD_XMMpd_XMMpd_64) = PAND<V128W, V128, V128>;
DEF_ISEL(ANDPS_XMMps_MEMps_32) = PAND<V128W, V128, MV128>;
DEF_ISEL(ANDPS_XMMps_XMMps_32) = PAND<V128W, V128, V128>;
IF_AVX( DEF_ISEL(VANDPD_XMMdq_XMMdq_MEMdq_64) = PAND<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VANDPD_XMMdq_XMMdq_XMMdq_64) = PAND<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VANDPD_YMMqq_YMMqq_MEMqq_64) = PAND<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VANDPD_YMMqq_YMMqq_YMMqq_64) = PAND<VV256W, VV256, VV256>; )
IF_AVX( DEF_ISEL(VANDPS_XMMdq_XMMdq_MEMdq_32) = PAND<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VANDPS_XMMdq_XMMdq_XMMdq_32) = PAND<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VANDPS_YMMqq_YMMqq_MEMqq_32) = PAND<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VANDPS_YMMqq_YMMqq_YMMqq_32) = PAND<VV256W, VV256, VV256>; )

DEF_ISEL(PANDNq_MEMq_64) = PANDN<V64W, V64, MV64>;
DEF_ISEL(PANDNqq_64) = PANDN<V64W, V64, V64>;
DEF_ISEL(PANDN_XMMdq_MEMdq_32) = PANDN<V128W, V128, MV128>;
DEF_ISEL(PANDN_XMMdq_XMMdq_32) = PANDN<V128W, V128, V128>;
IF_AVX( DEF_ISEL(VPANDN_XMMdq_XMMdq_MEMdq_128) = PANDN<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VPANDN_XMMdq_XMMdq_XMMdq_128) = PANDN<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VPANDN_YMMqq_YMMqq_MEMqq_256) = PANDN<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VPANDN_YMMqq_YMMqq_YMMqq_256) = PANDN<VV256W, VV256, VV256>; )

DEF_ISEL(ANDNPD_XMMpd_MEMpd_64) = PANDN<V128W, V128, MV128>;
DEF_ISEL(ANDNPD_XMMpd_XMMpd_64) = PANDN<V128W, V128, V128>;
DEF_ISEL(ANDNPS_XMMps_MEMps_32) = PANDN<V128W, V128, MV128>;
DEF_ISEL(ANDNPS_XMMps_XMMps_32) = PANDN<V128W, V128, V128>;
IF_AVX( DEF_ISEL(VANDNPD_XMMdq_XMMdq_MEMdq_64) = PANDN<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VANDNPD_XMMdq_XMMdq_XMMdq_64) = PANDN<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VANDNPD_YMMqq_YMMqq_MEMqq_64) = PANDN<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VANDNPD_YMMqq_YMMqq_YMMqq_64) = PANDN<VV256W, VV256, VV256>; )
IF_AVX( DEF_ISEL(VANDNPS_XMMdq_XMMdq_MEMdq_32) = PANDN<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VANDNPS_XMMdq_XMMdq_XMMdq_32) = PANDN<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VANDNPS_YMMqq_YMMqq_MEMqq_32) = PANDN<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VANDNPS_YMMqq_YMMqq_YMMqq_32) = PANDN<VV256W, VV256, VV256>; )

DEF_ISEL(PORq_MEMq_64) = POR<V64W, V64, MV64>;
DEF_ISEL(PORqq_64) = POR<V64W, V64, V64>;
DEF_ISEL(POR_XMMdq_MEMdq_32) = POR<V128W, V128, MV128>;
DEF_ISEL(POR_XMMdq_XMMdq_32) = POR<V128W, V128, V128>;
IF_AVX( DEF_ISEL(VPOR_XMMdq_XMMdq_MEMdq_128) = POR<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VPOR_XMMdq_XMMdq_XMMdq_128) = POR<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VPOR_YMMqq_YMMqq_MEMqq_256) = POR<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VPOR_YMMqq_YMMqq_YMMqq_256) = POR<VV256W, VV256, VV256>; )

DEF_ISEL(ORPD_XMMpd_MEMpd_64) = POR<V128W, V128, MV128>;
DEF_ISEL(ORPD_XMMpd_XMMpd_64) = POR<V128W, V128, V128>;
DEF_ISEL(ORPS_XMMps_MEMps_32) = POR<V128W, V128, MV128>;
DEF_ISEL(ORPS_XMMps_XMMps_32) = POR<V128W, V128, V128>;
IF_AVX( DEF_ISEL(VORPD_XMMdq_XMMdq_MEMdq_64) = POR<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VORPD_XMMdq_XMMdq_XMMdq_64) = POR<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VORPD_YMMqq_YMMqq_MEMqq_64) = POR<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VORPD_YMMqq_YMMqq_YMMqq_64) = POR<VV256W, VV256, VV256>; )
IF_AVX( DEF_ISEL(VORPS_XMMdq_XMMdq_MEMdq_32) = POR<VV128W, VV128, MV128>; )
IF_AVX( DEF_ISEL(VORPS_XMMdq_XMMdq_XMMdq_32) = POR<VV128W, VV128, VV128>; )
IF_AVX( DEF_ISEL(VORPS_YMMqq_YMMqq_MEMqq_32) = POR<VV256W, VV256, MV256>; )
IF_AVX( DEF_ISEL(VORPS_YMMqq_YMMqq_YMMqq_32) = POR<VV256W, VV256, VV256>; )

DEF_ISEL(PTEST_XMMdq_MEMdq_32) = PTEST<V128, MV128>;
DEF_ISEL(PTEST_XMMdq_XMMdq_32) = PTEST<V128, V128>;
IF_AVX( DEF_ISEL(VPTEST_XMMdq_MEMdq_32) = PTEST<VV128, MV128>; )
IF_AVX( DEF_ISEL(VPTEST_XMMdq_XMMdq_32) = PTEST<VV128, VV128>; )
IF_AVX( DEF_ISEL(VPTEST_YMMqq_MEMqq_32) = PTEST<VV256, MV256>; )
IF_AVX( DEF_ISEL(VPTEST_YMMqq_YMMqq_32) = PTEST<VV256, VV256>; )

/*
1737 XTEST XTEST LOGICAL RTM RTM ATTRIBUTES:
 */