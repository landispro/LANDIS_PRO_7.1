
#include <stdlib.h> 


#include <string.h>
#include <stdio.h>

#include <direct.h>
#include <errno.h>

#include "system1.h"
#include "BDAExport.h"


BDAS* GetBDAS(char* str, SITES* s, int i, char* outputdir, LANDUNITS* plu, SPECIESATTRS* ps, PDP* ppdp, int ifBDAprepeat, int gDllMd)
{
  return new BDAS(str, s, i, outputdir, plu, ps, ppdp, ifBDAprepeat, gDllMd);

}

void GetBDAACTIVE(BDAS* pBDAS, int itr)
{
  pBDAS->Active(itr);

}


