/* inverse transform: taken from foc.c */

static void ipark(const float d, const float q, const float angle_rad_0to2pi,
                     float * const alpha, float * const beta)
{
  const float s = sinf(angle_rad_0to2pi);
  const float c = cosf(angle_rad_0to2pi);

  *alpha = c * d - s * q;
  *beta  = s * d + c * q;
}
