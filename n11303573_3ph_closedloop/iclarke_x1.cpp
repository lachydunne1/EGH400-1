// Automatically generated C++ file on Thu Aug  7 09:15:49 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD iclarke_x1.cpp kernel32.lib

/* USER FUNC DEFS */

#include <math.h>

/* Clarke constants */
#define SQRT2        1.41421356237f
#define SQRT3        1.73205080757f
#define SQRT6        2.44948974278f

#define K1   (SQRT2 * SQRT3 / 3.0f)   // v6 / 3
#define K2   (SQRT6 / 6.0f)
#define K3   (SQRT2 / 2.0f)

void iclarke(const double alpha, const double beta, double *a, double *b, double * c);

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
#undef a
#undef b
#undef c
#undef CLK

static bool clk_state = false; // Initialize clk_state correctly

extern "C" __declspec(dllexport) void iclarke_x1(void **opaque, double t, union uData *data)
{
   double  alpha = data[0].d; // input
   double  beta  = data[1].d; // input
   bool    CLK   = data[2].b; // input
   double &a     = data[3].d; // output
   double &b     = data[4].d; // output
   double &c     = data[5].d; // output

// Implement module evaluation code here:
   if (CLK == false || CLK == clk_state) goto end;

   // will execute on rising/falling edge, generating clock frequency
   iclarke(alpha,beta,&a,&b,&c);

   end:
      clk_state = CLK;
}


void iclarke(const double alpha, const double beta, double *a, double *b, double * c)
{
    *a = K1 * alpha;

    *b = K3 * beta - K2 * alpha;

    *c = -K2 * alpha - K3 * beta;
}
