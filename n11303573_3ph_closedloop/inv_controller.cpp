// Automatically generated C++ file on Thu Aug 14 17:37:36 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD inv_controller.cpp kernel32.lib
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

static bool clk_state = false; // Initialize clk_state correctly
float clock_freq = 88000.0; // TODO: FIX HARDCODE

struct PwmLeg {
   double carrier_period; // Triangle wave period
   double gain;           // Scaling gain
   double offset;         // phase shift or m3 offset
   double amplitude;      // amplitude
   double time;           // sim time

   //generate PWM high/low signals for a leg
   void step(double reference, double *pa, double *pb){

      //generate triangle carrier
      double t_mod = fmod(time, carrier_period);
      double carrier = triangle_wave(t_mod);

      //compare ref against carrier and set PWM outputs
      if (reference >= carrier){
         *pa = 1;
         *pb = 0;
      } else{
         *pa = 0;
         *pb = 1;
      }
      time += 1/clock_freq; // incrememt timestep with each clock cycle
   }

   // use SPWM
   static double triangle_wave(double t){
      double phase = fmod(t, 1.0);
      return (phase < 0.5) ? phase * 2.0 : 2.0 - phase * 2.0;
   }


};

extern "C" __declspec(dllexport) void inv_controller(void **opaque, double t, union uData *data)
{
   double  c     = data[ 0].d; // input
   double  b     = data[ 1].d; // input
   double  a     = data[ 2].d; // input
   double  CLK   = data[ 3].d; // input
   double  dtime = data[ 4].d; // input parameter
   double  Fsw   = data[ 5].d; // input parameter
   double &p1a   = data[ 6].d; // output
   double &p1b   = data[ 7].d; // output
   double &p2a   = data[ 8].d; // output
   double &p2b   = data[ 9].d; // output
   double &p3a   = data[10].d; // output
   double &p3b   = data[11].d; // output

// Implement module evaluation code here:


   float period = 1/Fsw;
   float pi = 3.141592654;
   float phase_shift  =(2*pi)/3;
   float L_phase_shift = 0; //testing

   PwmLeg PWM_LEGA;
   PWM_LEGA.carrier_period = period;
   PWM_LEGA.gain = 1.0;
   PWM_LEGA.offset = 0.0+L_phase_shift;
   PWM_LEGA.amplitude = 1.0;
   PWM_LEGA.time = 0.0;


   PwmLeg PWM_LEGB;
   PWM_LEGB.carrier_period = period;
   PWM_LEGB.gain = 1.0;
   PWM_LEGB.offset = phase_shift;
   PWM_LEGB.amplitude = 1.0;
   PWM_LEGB.time = 0.0;

   PwmLeg PWM_LEGC;
   PWM_LEGC.carrier_period = period;
   PWM_LEGC.gain = 1.0;
   PWM_LEGC.offset = 2*phase_shift;
   PWM_LEGC.amplitude = 1.0;
   PWM_LEGC.time = 0.0;


   if (CLK == false || CLK == clk_state) goto end;

   PWM_LEGA.step(a, &p1a, &p1b);
   PWM_LEGB.step(b, &p2a, &p2b);
   PWM_LEGC.step(c, &p3a, &p3b);

   end:
      clk_state = CLK;

}
