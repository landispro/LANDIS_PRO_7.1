#ifndef FUELGLOBALFUNCS_H

#define FUELGLOBALFUNCS_H



#include "sites.h"

#include "PDP.h"



#ifdef FUELDLL_EXPORTS

#define DLLFUNC   __declspec( dllexport )

#else

#define DLLFUNC   __declspec( dllimport )

#endif



#ifdef __cplusplus

extern "C" {  // only need to export C interface if

              // used by C++ source code

#endif



DLLFUNC int			FuelInit			(PDP*, char*, int, int, char*, SITES*, int);

DLLFUNC	void		FuelProcessEvent	();

DLLFUNC void		FuelManageProcessEvents	(int);

DLLFUNC void		FuelputFuelOutput			(int, char*, int);





void	getFuelInput	(char*, int, int);

void	getFuelManage	(char*);

void	getFuelRule		(char*);



#ifdef __cplusplus

}

#endif





#undef DLLFUNC



#endif

