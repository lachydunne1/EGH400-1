/* park transform: taken from foc.c */

static void park(const float alpha, const float beta, const float angle_rad_0to2pi,
                 float * const d_out, float * const q_out)
{
  const float s = sinf(angle_rad_0to2pi);
  const float c = cosf(angle_rad_0to2pi);

  *d_out =  c * alpha + s * beta;
  *q_out = -s * alpha + c * beta ;
}
