// Automatically generated C++ file on Thu May 28 17:01:53 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD clark_transform_x1.cpp kernel32.lib


union uData
{
   bool b;
   char c;
   unsigned char uc;
   short s;
   unsigned short us;
   int i;
   unsigned int ui;
   float f;
   double d;
   long long int i64;
   unsigned long long int ui64;
   char *str;
   unsigned char *bytes;
};

#include <math.h>

/* Clarke constants  for power invariant */
#define SQRT2        1.41421356237f
#define SQRT3        1.73205080757f
#define SQRT6        2.44948974278f

#define K1   (SQRT2 * SQRT3 / 3.0f)   // v6 / 3
#define K2   (SQRT6 / 6.0f)
#define K3   (SQRT2 / 2.0f)
static bool clk_state = false; //Initialize clk_state correctly

void clarke_power_invariant(double a, double b, double c, double *alpha, double *beta, double *gamma);
void clarke_amplitude_invariant(double a, double b, double c, double *alpha, double *beta, double *gamma);

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef alpha
#undef beta
#undef a
#undef b
#undef c
#undef CLK
#undef gamma

extern "C" __declspec(dllexport) void clark_transform_x1(void **opaque, double t, union uData *data)
{
   double  a     = data[0].d; // input
   double  b     = data[1].d; // input
   double  c     = data[2].d; // input
   double  CLK   = data[3].d; // input
   double &alpha = data[4].d; // output
   double &beta  = data[5].d; // output
   double &gamma = data[6].d; // output

// Implement module evaluation code here:

   // if the clock is low, and previous state was high do not execute code.
   // if the clock is high, and previous state was low execute code.
   // (rising edge)
   if (!CLK && clk_state) goto end;
   //clarke_power_invariant(a, b, c, &alpha, &beta);
   clarke_amplitude_invariant(a, b, c, &alpha, &beta, &gamma);

   end:
      clk_state = CLK;
}

// reduced Clarke transform assumes that the system is balanced, making c redundant
// note: the Clarke transform from foc.c does not preserve amplitude. Consistent amplitudes are likely
//       to be important for torque / flux control.
//


void clarke_power_invariant(double a, double b, double c, double *alpha, double *beta, double *gamma){
    *alpha = ( 2*a -  b - c ) * (1/SQRT6);
    *beta  = ( b - c ) * (1/SQRT2);
    *gamma = (a + b + c) * (1/SQRT3);

}

void clarke_amplitude_invariant(double a, double b, double c, double *alpha, double *beta, double *gamma){
    // Directly map abc to alpha-beta without amplification
    *alpha = a;  // No scaling factor
    *beta  = (b - c) * 0.57735026919; // Simply subtract and normalize for balance in 2D plane
    *gamma = a+b+c;
}
