// Automatically generated C++ file on Thu Aug  7 12:07:51 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD ipark_x1.cpp kernel32.lib

#include <cmath>
static void ipark(double d, double q, double angle_rad_0to2pi, double * alpha, double *  beta);
static bool clk_state = false; // Initialize clk_state correctly


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

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef d
#undef q
#undef theta
#undef alpha
#undef beta
#undef CLK

extern "C" __declspec(dllexport) void ipark_x1(void **opaque, double t, union uData *data)
{
   double  d     = data[0].d; // input
   double  q     = data[1].d; // input
   double  theta = data[2].d; // input
   double  CLK   = data[3].d; // input
   double &alpha = data[4].d; // output
   double &beta  = data[5].d; // output

// Implement module evaluation code here:
   if (CLK == false || CLK == clk_state) goto end;

   // will execute on rising/falling edge, generating clock frequency
   ipark(d, q, theta, &alpha, &beta);

   end:
      clk_state = CLK;

}

/* inverse transform: taken from foc.c */

static void ipark(double d, double q, double angle_rad_0to2pi, double * alpha, double *  beta){
  const float s = sinf(angle_rad_0to2pi);
  const float c = cosf(angle_rad_0to2pi);

  *alpha = c * d - s * q;
  *beta  = s * d + c * q;
}
