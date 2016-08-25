#include "wind.h"

#include "WindExport.h"





WIND* GetWind(char* strWindFileName, char* output, int dllmode)

{

  return new WIND(strWindFileName, output, dllmode);



}



void GetWindACTIVATE(WIND* pw, int itr, int freq[], SITES* s, SPECIESATTRS* sp, int cellSize, int randSeed, int numberOfIterations, int gDLLMode) //Nim: added int freq[]



{

    pw->activate(itr, freq, s, sp, cellSize, randSeed, numberOfIterations, gDLLMode);

}