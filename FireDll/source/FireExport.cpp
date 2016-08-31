//added by Wei Li, April 19, 2004



#include "fire.h"

#include "FireExport.h"





CFIRE* GetFire(char* strfn, int mode, SITES* outsites, LANDUNITS* outlus, 

			   SPECIESATTRS*  outsa, PDP* ppdp, int nFNOI,

			   char * strOutput,int randSeed)

{

  	CFIRE * pFire;

	pFire = new CFIRE(strfn, mode, outsites, outlus, outsa, ppdp, nFNOI,strOutput,randSeed);

	return pFire;

	//return new CFIRE(strfn, mode, outsites, outlus, outsa, ppdp, nFNOI,strOutput);



}



void GetFireACTIVATE(CFIRE* pf, int itr, int freq[], double wAdfGeoTransform[])

{

  //  pw->activate(itr, freq, s, sp, cellSize, randSeed, numberOfIterations, gDLLMode);

	pf->Activate(itr, freq, wAdfGeoTransform);

}