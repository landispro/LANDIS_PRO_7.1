#include <assert.h>

#include <stdio.h>

#include "GlobalVariables.h"

#include "CohortRemovalMask.h"

#include "SiteRemovalMask.h"



SiteRemovalMask::SiteRemovalMask() {

    assert(numberOfSpecies > 0);

    mask = new CohortRemovalMask[numberOfSpecies];

    numSpec = numberOfSpecies;

}



SiteRemovalMask::~SiteRemovalMask() {

    delete [] mask;

}



void SiteRemovalMask::read(FILE* infile) {

    for (int i=0;i<numSpec;i++) {

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

