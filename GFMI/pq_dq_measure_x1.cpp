// Automatically generated C++ file on Fri Apr  3 15:01:57 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD pq_dq_measure_x1.cpp kernel32.lib
static void calculate_pq_dq_power(double Vd, double Vq, double Id, double Iq, double * P, double * Q);

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

// Implement module evaluation code here:
 calculate_pq_dq_power(Vd,Vq, Id, Iq, &P, &Q);
}


// Calculate instantaneous power output using P-Q theory (H. Akagi, Instantaneous Power Theory App., p 71)
static void calculate_pq_dq_power(double Vd, double Vq, double Id, double Iq, double * P, double * Q){
   *P = 1.5 * (Vd*Id + Vq*Iq);
   *Q = 1.5 * (Vq*Id - Vd*Iq);

}
