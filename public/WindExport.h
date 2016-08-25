#include "Wind.h"



#ifdef WINDDLL_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



DLLCLASS WIND* GetWind();



DLLCLASS void GetWindACTIVATE (Wind*, int, int freq[], CGrid*, SPECIESATTRS*, int, int, int, int, int);



#undef DLLCLASS

