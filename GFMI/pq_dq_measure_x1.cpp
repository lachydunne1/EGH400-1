// Automatically generated C++ file on Fri Apr  3 15:01:57 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD pq_dq_measure_x1.cpp kernel32.lib
#include <cmath>

static void calculate_pq_dq_power_amplitude_invariant(double Vd, double Vq, double Id, double Iq, double * P, double * Q);
static void calculate_pq_dq_power_power_invariant(double Vd, double Vq, double Id, double Iq, double * P, double * Q);

float sqrt_3 =1.73; //scale slightly to compensate to voltage drops
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
#undef Vd
#undef Vq
#undef Id
#undef Iq
#undef P
#undef Q
#undef CLK

extern "C" __declspec(dllexport) void pq_dq_measure_x1(void **opaque, double t, union uData *data)
{
   double  Vd  = data[0].d; // input
   double  Vq  = data[1].d; // input
   double  Id  = data[2].d; // input
   double  Iq  = data[3].d; // input
   double  CLK = data[4].d; // input
   double &P   = data[5].d; // output
   double &Q   = data[6].d; // output

   // if the clock is low, and previous state was high do not execute code.
   // if the clock is high, and previous state was low execute code.
   // (rising edge)
   if (!CLK && clk_state) goto end;
      calculate_pq_dq_power_amplitude_invariant(Vd,Vq, Id, Iq, &P, &Q);
   end:
      clk_state = CLK;
}


// Calculate P-Q power references with this function is amplitude-invariant clarke is used
static void calculate_pq_dq_power_amplitude_invariant(double Vd, double Vq, double Id, double Iq, double * P, double * Q){
   *P = 1.5*(Vd*Id + Vq*Iq);
   *Q = 1.5*(Vq*Id - Vd*Iq);

}

// Calculate P-Q power references with this function is power-invariant clarke is used
static void calculate_pq_dq_power_power_invariant(double Vd, double Vq, double Id, double Iq, double * P, double * Q){
   *P = (Vd*Id + Vq*Iq);
   *Q = (Vq*Id - Vd*Iq);
}
