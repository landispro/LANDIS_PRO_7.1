#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "point.h"

#include "SiteRemovalMask.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "Stand.h"

#include "SiteHarvester.h"

#include "StandHarvester.h"

#include "HarvestPath.h"

#include "HarvestEvent.h"

#include "UnboundedPocketStandHarvester.h"

#include "TwoPassStandSpreadingRegime.h"



TwoPassStandSpreadingRegime::TwoPassStandSpreadingRegime() {

    itsMeanStandCutSize = 0.0;

    itsStandardDeviation = 0.0;

}



/* inline */ int TwoPassStandSpreadingRegime::isA() {

    return EVENT_TWO_PASS_STAND_SPREADING_REGIME;

}



void TwoPassStandSpreadingRegime::read(FILE* infile) {

    if (itsState == START) {

        HarvestRegime::read(infile);

        itsState = ENTRYPENDING;

    } else {

        errorSys("Illegal call to TwoPassStandSpreadingRegime::read.", STOP);

    }



}



void TwoPassStandSpreadingRegime::readCustomization1(FILE* infile) {

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

    if (fscanc(infile, "%f", &itsMeanStandCutSize)!=1)

        errorSys("Error reading mean stand cut size from harvest section.",STOP);

    if (fscanc(infile, "%f", &itsStandardDeviation)!=1)

        errorSys("Error reading standard deviation from harvest section.",STOP);

}



void TwoPassStandSpreadingRegime::readCustomization2(FILE* infile) {

    itsReentryRemovalMask = new SiteRemovalMask;

    itsReentryRemovalMask->read(infile);

    setDuration(1);

}



int TwoPassStandSpreadingRegime::harvestStand(Stand* stand) {

    LDPOINT standStartPoint;

    int standCut = 0;



    if (getRandomHarvestablePoint(stand, standStartPoint)) {

        int standTargetCut = (int) gasdev(itsMeanStandCutSize, itsStandardDeviation);

        //RScheller 5/12/03:  fix problem of low mean StandCutSize and large StandardDeviation

		//that results in standTargetCut <= 0 which crashes the program.

        while(standTargetCut <= 0)

        {

			standTargetCut = (int) gasdev(itsMeanStandCutSize, itsStandardDeviation);

		}

        SiteHarvester theSiteHarvester(getSequentialId(), getRemovalMask(), getReport(), getDuration());

        UnboundedPocketStandHarvester theStandHarvester(standTargetCut, standStartPoint, &theSiteHarvester, &itsPath);

        standCut = theStandHarvester.harvest();

    }

    return standCut;

}





