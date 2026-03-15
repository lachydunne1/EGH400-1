// Automatically generated C++ file on Fri Jan 23 14:08:47 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD phase_align_x1.cpp kernel32.lib

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

static void phase_align(double theta_PLL, double * theta_PLL_aligned);
static bool clk_state = false; // Initialize clk_state correctly

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef d
#undef theta_PLL
#undef theta_PLL_aligned
#undef CLK

extern "C" __declspec(dllexport) void phase_align_x1(void **opaque, double t, union uData *data)
{
   double  d                 = data[0].d; // input
   double  theta_PLL         = data[1].d; // input
   double  CLK               = data[2].d; // input
   double  &theta_PLL_aligned = data[3].d; // output

// Implement module evaluation code here:
// Implement module evaluation code here:
   if (CLK == false || CLK == clk_state) goto end;

   // will execute on rising/falling edge, generating clock frequency
   if(d < 0){
       phase_align(theta_PLL, &theta_PLL_aligned);
   }
   end:
      clk_state = CLK;
}

static void phase_align(double theta_PLL, double * theta_PLL_aligned){

   *theta_PLL_aligned = theta_PLL + 3.14159;

}
