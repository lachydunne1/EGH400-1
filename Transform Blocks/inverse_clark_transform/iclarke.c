/*  reduced inverse clarke transform: taken from foc.c */

static void iclarke(const float alpha, const float beta, float * const a, float * const b, float * const c){

  const float sqrt3_over_two = 0.866025404f;

  const float tmp1 = -0.5f * alpha;
  const float tmp2 = sqrt3_over_two * beta;

  *a = alpha;
  *b = tmp1 + tmp2;
  *c = tmp1 - tmp2;
}
