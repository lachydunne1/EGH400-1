// Automatically generated C++ file on Sun May 17 15:33:25 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD spwm_controller_translate.cpp kernel32.lib

#include <malloc.h>
#include <cmath>

#define PI 3.1415926

static bool clk_state = false; // Initialize clk_state correctly
float phase = 0.0;
float ma = 0.8125;
void Qspice_Interrupt_SPWM(double phase, double vpu, double *duty_A, double *duty_B, double *duty_C);
void Qspice_Interrupt_SVPWM(double time,double phase, double *duty_A, double *duty_B,double *duty_C, double *sig_out);

extern "C" __declspec(dllexport) void (*bzero)(void *ptr, unsigned int count)   = 0;

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
#undef duty_A
#undef duty_B
#undef duty_C
#undef CLK
#undef time
#undef sig_out
#undef phase
#undef V

struct sSPWM_CONTROLLER_TRANSLATE
{
  // declare the structure here
};

extern "C" __declspec(dllexport) void spwm_controller_translate(struct sSPWM_CONTROLLER_TRANSLATE **opaque, double t, union uData *data)
{
   double  CLK     = data[0].d; // input
   double  time    = data[1].d; // input
   double  phase   = data[2].d; // input
   double  V       = data[3].d; // input
   double  Fsw     = data[4].d; // input parameter
   double  Norm    = data[5].d; // input parameter
   double &duty_A  = data[6].d; // output
   double &duty_B  = data[7].d; // output
   double &duty_C  = data[8].d; // output
   double &sig_out = data[9].d; // output

   double v_set_pu = V;

   if(!*opaque)
   {
      *opaque = (struct sSPWM_CONTROLLER_TRANSLATE *) malloc(sizeof(struct sSPWM_CONTROLLER_TRANSLATE));
      bzero(*opaque, sizeof(struct sSPWM_CONTROLLER_TRANSLATE));
   }
   struct sSPWM_CONTROLLER_TRANSLATE *inst = *opaque;

   // if the clock is low, and previous state was high do not execute code.
   // if the clock is high, and previous state was low execute code.
   // (rising edge)
   if (!CLK && clk_state) goto end;
      Qspice_Interrupt_SPWM(phase, v_set_pu, &duty_A, &duty_B, &duty_C);
   end:
      clk_state = CLK;

}


void Qspice_Interrupt_SPWM(double phase, double vpu, double *duty_A, double *duty_B, double *duty_C){

   float va = sin(phase);
   float vb = sin(phase - 2.0*PI/3);
   float vc = sin(phase + 2.0*PI/3);

   *duty_A = (vpu*ma*va*0.5 + 0.5);
   *duty_B = (vpu*ma*vb*0.5 + 0.5);
   *duty_C = (vpu*ma*vc*0.5 + 0.5);
}


void Qspice_Interrupt_SVPWM(double time,double phase, double *duty_A, double *duty_B,double *duty_C, double *sig_out)
{
   float va = sin(phase);
   float vb = sin(phase - 2.0 * PI / 3.0);
   float vc = sin(phase + 2.0 * PI / 3.0);

    // SVPWM zero-sequence injection
   float vmax = va;
   if (vb > vmax) vmax = vb;
   if (vc > vmax) vmax = vc;

   float vmin = va;
   if (vb < vmin) vmin = vb;
   if (vc < vmin) vmin = vc;
   float vzero = -0.5f * (vmax + vmin);

   va += vzero;
   vb += vzero;
   vc += vzero;

   // Convert to duty cycles
   *duty_A = 0.5f + 0.5f * ma * va;
   *duty_B = 0.5f + 0.5f * ma * vb;
   *duty_C = 0.5f + 0.5f * ma * vc;

   *sig_out = va;
}

extern "C" __declspec(dllexport) void Destroy(struct sSPWM_CONTROLLER_TRANSLATE *inst)
{
   free(inst);
}
