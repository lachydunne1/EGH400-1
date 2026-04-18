// Automatically generated C++ file on Fri Apr 17 11:49:30 2026
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD digital_lowpass_x1.cpp kernel32.lib

void FIR_filter(double in, double in1, double in2, double in3, double *OUT, double *OUT1, double *OUT2, double *OUT3);

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
#undef IN
#undef OUT
#undef CLK
#undef OUT1
#undef OUT2
#undef OUT3
#undef IN1
#undef IN2
#undef IN3

bool clk_state = false;
extern "C" __declspec(dllexport) void digital_lowpass_x1(void **opaque, double t, union uData *data)
{
   double  IN   = data[0].d; // input
   bool    CLK  = data[1].b; // input
   double  IN1  = data[2].d; // input
   double  IN2  = data[3].d; // input
   double  IN3  = data[4].d; // input
   double &OUT  = data[5].d; // output
   double &OUT1 = data[6].d; // output
   double &OUT2 = data[7].d; // output
   double &OUT3 = data[8].d; // output

// Implement module evaluation code here:
   if (CLK == false || CLK == clk_state){
      goto end;
   }
   FIR_filter( IN, IN1, IN2, IN3, &OUT, &OUT1, &OUT2, &OUT3);


   end:
      clk_state = CLK;
}

void FIR_filter(double in, double in1, double in2, double in3, double *OUT, double *OUT1, double *OUT2, double *OUT3){
   // outputs of Matlab FilterDesigner
   const float b0 = -0.0613f;
   const float b1 = 0.5631f;
   const float b2 = 0.5631f;
   const float b3 = -0.0613f;


   *OUT = (b0 * in) + (b1 * in1) + ( b2 * in2) + ( b3 * in3);

   *OUT1 = in;
   *OUT2 = in1;
   *OUT3 = in2;

}
