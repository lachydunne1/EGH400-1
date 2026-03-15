// Automatically generated C++ file on Fri Mar 13 13:09:13 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD spwm_controller_debug.cpp kernel32.lib
#include <cmath>

struct PwmLeg {
   double carrier_period; // Triangle wave period
   double gain;           // Scaling gain
   double offset;         // phase shift or m3 offset
   double amplitude;      // amplitude
   double time;           // sim time

   //generate PWM high/low signals for a leg
   double step(double reference, double *pa, double *pb){

      //generate triangle carrier
      double t_mod = fmod(time, carrier_period);
      double carrier = triangle_wave(t_mod/carrier_period);

      //compare ref against carrier and set PWM outputs
      if (reference >= carrier){
         *pa = 1;
         *pb = 0;
      } else{
         *pa = 0;
         *pb = 1;
      }
      return carrier;
   }

   // use SPWM
   static double triangle_wave(double t){
      double phase = fmod(t,1.0);
      return (phase < 0.5) ? (phase*4 - 1) : (3 - phase*4);
   }


};

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
#undef p1a
#undef p1b
#undef p2a
#undef p2b
#undef p3a
#undef p3b
#undef c
#undef b
#undef a
#undef CLK
#undef time
#undef tri_out
#undef sig_out

extern "C" __declspec(dllexport) void spwm_controller_debug(void **opaque, double t, union uData *data)
{
   double  c       = data[ 0].d; // input
   double  b       = data[ 1].d; // input
   double  a       = data[ 2].d; // input
   double  CLK     = data[ 3].d; // input
   double  time    = data[ 4].d; // input
   double  Fsw     = data[ 5].d; // input parameter
   double  Norm    = data[ 6].d; // input parameter
   double &p1a     = data[ 7].d; // output
   double &p1b     = data[ 8].d; // output
   double &p2a     = data[ 9].d; // output
   double &p2b     = data[10].d; // output
   double &p3a     = data[11].d; // output
   double &p3b     = data[12].d; // output
   double &tri_out = data[13].d; // output
   double &sig_out = data[14].d; // output

// Implement module evaluation code here:

   float period = 1/Fsw;
   float pi = 3.141592654;
   float phase_shift  =(2*pi)/3;
   float carrier_a = 0;
   float carrier_b = 0;
   float carrier_c = 0;

   PwmLeg PWM_LEGA;
   PWM_LEGA.carrier_period = period;
   PWM_LEGA.gain = 1.0;
   PWM_LEGA.offset = 0.0;
   PWM_LEGA.amplitude = 1.0;
   PWM_LEGA.time = time;


   PwmLeg PWM_LEGB;
   PWM_LEGB.carrier_period = period;
   PWM_LEGB.gain = 1.0;
   PWM_LEGB.offset = 0;
   PWM_LEGB.amplitude = 1.0;
   PWM_LEGB.time = time;

   PwmLeg PWM_LEGC;
   PWM_LEGC.carrier_period = period;
   PWM_LEGC.gain = 1.0;
   PWM_LEGC.offset = 0;
   PWM_LEGC.amplitude = 1.0;
   PWM_LEGC.time = time;

   carrier_a = PWM_LEGA.step(a/Norm, &p1a, &p1b);
   carrier_b = PWM_LEGB.step(b/Norm, &p2a, &p2b);
   carrier_c = PWM_LEGC.step(c/Norm, &p3a, &p3b);

   sig_out = a/Norm;
   tri_out = carrier_a;

}
