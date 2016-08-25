/////////////////////////////////////////

//last modified by Wei Li, august 27, 2004

////////////////////////////////////////



#include <assert.h>

#include <stdio.h>

#include "IntArray.h"

#include "GlobalVariables.h"

#include "CohortRemovalMask.h"

#include "SiteRemovalMask.h"

#include "system1.h"



//modified by Wei Li on planting code

SiteRemovalMask::SiteRemovalMask() : itsPlantingCode(numberOfSpecies) 

{

	assert(numberOfSpecies > 0);

    mask = new CohortRemovalMask[numberOfSpecies];

    numSpec = numberOfSpecies;

}



SiteRemovalMask::~SiteRemovalMask() {

    delete [] mask;

}



void SiteRemovalMask::read(FILE* infile) {

    for (int i=0;i<numSpec;i++) 

	{

		//by wei li

		fscanc(infile,"%d ",&itsPlantingCode[i+1]);

		//by wei li

         mask[i].read(infile);

    }

}



void SiteRemovalMask::dump() {

    for (int i=0;i<numSpec;i++) {

        mask[i].dump();

    }

}



/* inline */ CohortRemovalMask* SiteRemovalMask::operator()(int species) {

    return mask + (species-1);

}



//by wei li

int SiteRemovalMask::plantingCode(int species) {

    return itsPlantingCode[species];

}

//by wei li