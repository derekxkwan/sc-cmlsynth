#include "SC_PlugIn.h"

#define CMLMIN 1
#define CMLMAX 240000
#define T_PI 6.283185307179586


static InterfaceTable *ft;

struct CmlSynth : public Unit {
  int bufsize, phase;

  float * bufr;
}

extern "C" {
  
  void load(InterfaceTable *inTable);  
  void CmlSynth_Ctor(CmlSynth* unit);
  void CmlSynth_Dtor(CmlSynth* unit);
}

void CmlSynth_Ctor(CmlSynth* unit) {
  float * bufr;
  int bufsize = IN0(0); //bufsize in samples
  RGen& rgen = *unit->mParent->mRGen;
  
  bufsize = bufsize < CMLMIN ? CMLMIN : (bufsize > CMLMAX ? CMLMAX : bufsize);

  unit->bufsize = bufsize;
  bufr = (float *)RTAlloc(unit->mWorld, unit->bufsize * sizeof(float));

  //init buf to random numbers
  for(int i=0; i < bufsize; i++)
      bufr[i] = rgen.frand() * 2.0 - 1.0;

  unit->bufr = bufr;
  SETCALC(CmlSynth_next);

  CmlSynth_next(unit, bufsize);
}

// this must be named PluginName_Dtor.
void CmlSynth_Dtor(CmlSynth* unit) {
    // Free the memory.
    RTFree(unit->mWorld, unit->buf);
}

void CmlSynth_next(CmlSynth *unit, int inNumSamples)
{
  RGen& rgen = *unit->mParent->mRGen;
  float eps = IN(1);
  float omega = IN(2);
  float k = IN(3);
  float mul = IN(4);
  float add = IN(5);
  int bufsize = unit->bufsize;

  float *out = OUT(0);

  for(int i=0; i < FULLBUFLENGTH; i++)
    {

    };
}


PluginLoad(CmlSynth)
{
    ft = inTable;
    // ATTENTION! This has changed!
    // In the previous examples this was DefineSimpleUnit.
    DefineDtorUnit(CmlSynth);
}
