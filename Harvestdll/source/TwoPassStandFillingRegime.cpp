#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "SiteRemovalMask.h"

#include "GlobalVariables.h"

#include "SiteHarvester.h"

#include "Stand.h"

#include "StandHarvester.h"

#include "HarvestPath.h"

#include "HarvestEvent.h"

#include "FillingStandHarvester.h"

#include "TwoPassStandFillingRegime.h"



/* inline */ int TwoPassStandFillingRegime::isA() {

    return EVENT_TWO_PASS_STAND_FILLING_REGIME;

}



void TwoPassStandFillingRegime::read(FILE* infile) {

    if (itsState == START) {

        HarvestRegime::read(infile);

        itsState = ENTRYPENDING;

    } else {

        errorSys("Illegal call to TwoPassStandFillingRegime::read.", STOP);

    }

}



void TwoPassStandFillingRegime::readCustomization1(FILE* infile) {

    if (fscanc(infile, "%d", &itsEntryDecade)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsEntryDecade=itsEntryDecade/pCoresites->TimeStep_Harvest;

	if(itsEntryDecade<pCoresites->TimeStep_Harvest)

		itsEntryDecade=1;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%d", &itsReentryDecade)!=1)

        errorSys("Error reading reentry decade from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsReentryDecade=itsReentryDecade/pCoresites->TimeStep_Harvest;

	if(itsReentryDecade<pCoresites->TimeStep_Harvest)

		itsReentryDecade=1;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%d", &itsTargetCut)!=1)

    errorSys("Error reading target cut from harvest section.",STOP);

}



void TwoPassStandFillingRegime::readCustomization2(FILE* infile) {

    itsReentryRemovalMask = new SiteRemovalMask;

    itsReentryRemovalMask->read(infile);

    setDuration(1);

}



int TwoPassStandFillingRegime::harvestStand(Stand* stand) {

    SiteHarvester theSiteHarvester(getSequentialId(), getRemovalMask(), getReport(), getDuration());

    FillingStandHarvester theStandHarvester(stand, &theSiteHarvester, &itsPath);

    int standCut = theStandHarvester.harvest();

    return standCut;

}





