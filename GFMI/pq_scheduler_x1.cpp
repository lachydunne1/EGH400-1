// Automatically generated C++ file on Sun May 24 17:55:08 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD pq_scheduler_x1.cpp kernel32.lib
#include <cmath>

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

#undef time
#undef P
#undef Q

double sqrt_3 = 1.73;
double P_current = 0.0;
double Q_current = 0.0;


static bool L1_done = false;
static bool L2_done = false;


void PQ_load_step(double P_in, double Q_in, double Q_rated, double P_rated, double *P_out, double *Q_out);

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef time
#undef P
#undef Q

extern "C" __declspec(dllexport) void pq_scheduler_x1(void **opaque, double t, union uData *data)
{
   double  time    = data[ 0].d; // input
   double  time_L1 = data[ 1].d; // input parameter
   double  time_L2 = data[ 2].d; // input parameter
   double  L1_P    = data[ 3].d; // input parameter
   double  L1_Q    = data[ 4].d; // input parameter
   double  L2_P    = data[ 5].d; // input parameter
   double  L2_Q    = data[ 6].d; // input parameter
   double  Q_rated = data[ 7].d; // input parameter
   double  P_rated = data[ 8].d; // input parameter
   double &P       = data[ 9].d; // output
   double &Q       = data[10].d; // output

// Implement module evaluation code here:
//should only execute once.
   if ((fabs(time - time_L1) < 1e-4)&& !L1_done){
      Q_current = sqrt_3*L1_Q;
      P_current = sqrt_3*L1_P;
      L1_done = true;
   }

   if ((fabs(time - time_L2) < 1e-4) && !L2_done){
      Q_current = sqrt_3*L2_Q;
      P_current = sqrt_3*L2_P;
      L2_done = true;
   }

  PQ_load_step(P_current, Q_current, P_rated, Q_rated, &P, &Q);

}

void PQ_load_step(double P_in, double Q_in, double Q_rated, double P_rated, double *P_out, double *Q_out){
   *P_out = P_in/P_rated;
   *Q_out = Q_in/Q_rated;
}
