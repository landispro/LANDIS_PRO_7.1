#include <stdio.h>

#include "error.h"

#include "system1.h"

#include "GlobalVariables.h"

#include "Stand.h"

#include "HarvestEvent.h"

#include "SiteRemovalMask.h"

#include "SiteHarvester.h"

#include "FillingStandHarvester.h"

#include "OnePassStandFillingRegime.h"



/* inline */ int OnePassStandFillingRegime::isA() {

    return EVENT_ONE_PASS_STAND_FILLING_REGIME;

}



void OnePassStandFillingRegime::read(FILE* infile) {

    if (itsState == START) {

        HarvestRegime::read(infile);

        itsState = ENTRYPENDING;

    } else {

        errorSys("Illegal call to OnePassStandFillingRegime::read.", STOP);

    }

}



void OnePassStandFillingRegime::readCustomization1(FILE* infile) {

    if (fscanc(infile, "%d", &itsEntryDecade)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsEntryDecade=itsEntryDecade/pCoresites->TimeStep_Harvest;

	if(itsEntryDecade<pCoresites->TimeStep_Harvest)

		itsEntryDecade=1;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%d", &itsTargetCut)!=1)

        errorSys("Error reading target cut from harvest section.",STOP);

}



void OnePassStandFillingRegime::readCustomization2(FILE* infile) {

    setDuration(1);

}



int OnePassStandFillingRegime::harvestStand(Stand* stand) {

    SiteHarvester theSiteHarvester(getSequentialId(), getRemovalMask(), getReport(), getDuration());

    FillingStandHarvester theStandHarvester(stand, &theSiteHarvester);

    int standCut = theStandHarvester.harvest();

    return standCut;

}





