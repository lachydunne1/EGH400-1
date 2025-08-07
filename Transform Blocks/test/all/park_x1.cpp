// Automatically generated C++ file on Thu Aug  7 10:47:17 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD park_x1.cpp kernel32.lib

/* USER FUNCTION DEFS */

#include <cmath>

static void park(double alpha, double beta, double angle_rad_0to2pi,double * d_out, double * q_out);
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
#undef alpha
#undef beta
#undef d
#undef q
#undef CLK
#undef theta

extern "C" __declspec(dllexport) void park_x1(void **opaque, double t, union uData *data)
{
   double  alpha = data[0].d; // input
   double  beta  = data[1].d; // input
   double  CLK   = data[2].d; // input
   double  theta = data[3].d; // input
   double &d     = data[4].d; // output
   double &q     = data[5].d; // output

// Implement module evaluation code here:
   if (CLK == false || CLK == clk_state) goto end;

   // will execute on rising/falling edge, generating clock frequency
   park(alpha, beta, theta, &d, &q);

   end:
      clk_state = CLK;
}

static void park(double alpha, double beta, double angle_rad_0to2pi,double * d_out, double * q_out){

  const float s = sinf(angle_rad_0to2pi);
  const float c = cosf(angle_rad_0to2pi);

  *d_out =  c * alpha + s * beta;
  *q_out = -s * alpha + c * beta;
}
