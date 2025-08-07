// Automatically generated C++ file on Tue Aug  5 17:18:55 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD clark_transform_x1.cpp kernel32.lib

/* USER FUNCTION DEFS */

static void clarke(const double a, const double b, const double c, double *alpha, double *beta);

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
static bool FOC_FULL_CLARKE = true; // Used to MAINTAIN FULL SCALE OF INPUT OVER TRANSFORMS

// method called by Qspice once DLL is loaded

extern "C" __declspec(dllexport) void clark_transform_x1(void **opaque, double t, union uData *data)
{
   double a = data[0].d; // input
   double b = data[1].d; // input
   double c = data[2].d; // input
   double CLK = data[3].d; // input
   double &alpha = data[4].d; // output
   double &beta = data[5].d;  // output

   // Implement module evaluation code here:

   if (CLK == false || CLK == clk_state) goto end;

   // will execute on rising/falling edge, generating clock frequency
   clarke(a, b, c, &alpha, &beta);

end:
   clk_state = CLK;
}

// reduced Clarke transform assumes that the system is balanced, making c redundant
// note: the Clarke transform from foc.c does not preserve amplitude. Consistent amplitudes are likely
//       to be important for torque / flux control.
//

static void clarke(const double a, const double b, const double c, double *alpha, double *beta){
  (void) c;
  const double one_over_sqrt3 = 0.577350269f;
   // dereference pointer to change value. No need to return alpha, beta.
  if (FOC_FULL_CLARKE == true){
      const float k = 2.0f/3.0f;
      *alpha = k* a - (k/2.0f) * b - (k /2.0f) * c; //test
      *beta = one_over_sqrt3 * (b-c);
  } else {
      *alpha = a;
      *beta = one_over_sqrt3 * a + 2.0f * one_over_sqrt3 * b;
   }

}
