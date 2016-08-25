/*******************************************************

BDASExport.h: interface for the BDAS class.

Last Modify:    Nov. 20, 2002

Author:			Vera W. Li

*******************************************************/

#ifndef BDAS_EXPORT_H

#define BDAS_EXPORT_H



#include "BDAS.h"



/*#ifdef BDADll_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif*/





 BDAS*  GetBDAS(char* str, SITES* s, int i, char*, LANDUNITS* plu, SPECIESATTRS* ps, PDP* ppdp, int ifBDAprepeat, int gDllMd );



 void GetBDAACTIVE(BDAS* pBDAS, int itr);





//#undef DLLCLASS



#endif 



