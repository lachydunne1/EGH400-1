// Automatically generated C++ file on Thu Aug  7 09:15:49 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD iclarke_x1.cpp kernel32.lib

/* USER FUNC DEFS */

static void iclarke(const double alpha, const double beta, double *a, double *b, double * c);

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


/*  reduced inverse clarke transform: taken from foc.c */

static void iclarke(const double alpha, const double beta, double *a, double *b, double * c){

  const double sqrt3_over_two = 0.866025404f;

  const double tmp1 = -0.5f * alpha;
  const double tmp2 = sqrt3_over_two * beta;

  *a = alpha;
  *b = tmp1 + tmp2;
  *c = tmp1 - tmp2;
}
