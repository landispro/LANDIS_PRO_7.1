#include "Fire.h"



#ifdef FIREDLL_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



DLLCLASS CFIRE* GetFire(char* strfn, int mode, SITES* outsites, LANDUNITS* outlus, 

						SPECIESATTRS*  outsa, PDP* ppdp, int nFNOI,

						char * strOutput,int randSeed);



DLLCLASS void GetFireACTIVATE(CFIRE*, int itr, int* freq);





#undef DLLCLASS