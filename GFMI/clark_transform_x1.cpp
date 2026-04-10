// Automatically generated C++ file on Tue Aug  5 17:18:55 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD clark_transform_x1.cpp kernel32.lib

/* USER FUNCTION DEFS */
#include <math.h>

#include <math.h>

/* Clarke constants */
#define SQRT2        1.41421356237f
#define SQRT3        1.73205080757f
#define SQRT6        2.44948974278f

#define K1   (SQRT2 * SQRT3 / 3.0f)   // v6 / 3
#define K2   (SQRT6 / 6.0f)
#define K3   (SQRT2 / 2.0f)

void clarke(double a, double b, double c, double *alpha, double *beta);
void clarke_constant_amplitude(double a, double b, double c, double *alpha, double *beta);

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

static bool clk_state = true; // Initialize clk_state correctly
static bool FOC_FULL_CLARKE = false; // Used to MAINTAIN FULL SCALE OF INPUT OVER TRANSFORMS

// method called by Qspice once DLL is loaded

extern "C" __declspec(dllexport) void clark_transform_x1(void **opaque, double t, union uData *data)
{
   double a = data[0].d; // input
   double b = data[1].d; // input
   double c = data[2].d; // input
   double CLK = data[3].d; // input
   double &alpha = data[4].d; // output
   double &beta = data[5].d;  // output


   // will execute on rising/falling edge, generating clock frequency
   clarke_constant_amplitude(a, b, c, &alpha, &beta);


}

// reduced Clarke transform assumes that the system is balanced, making c redundant
// note: the Clarke transform from foc.c does not preserve amplitude. Consistent amplitudes are likely
//       to be important for torque / flux control.
//


void clarke(double a, double b, double c, double *alpha, double *beta)
{
    *alpha = K1 * a - K2 * b - K2 * c;
    *beta  = K3 * b - K3 * c;
}

void clarke_constant_amplitude(double a, double b, double c, double *alpha, double *beta)
{
    // Directly map abc to alpha-beta without amplification
    *alpha = a;  // No scaling factor
    *beta  = (b - c) * 0.57735026919; // Simply subtract and normalize for balance in 2D plane
}
