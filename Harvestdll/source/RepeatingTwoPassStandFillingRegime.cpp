#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "point.h"

#include "SiteRemovalMask.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "SiteHarvester.h"

#include "Stand.h"

#include "StandHarvester.h"

#include "HarvestRegime.h"

#include "HarvestPath.h"

#include "HarvestPathIterator.h"

#include "HarvestEvent.h"

#include "FillingStandHarvester.h"

#include "RepeatingTwoPassStandFillingRegime.h"



RepeatingTwoPassStandFillingRegime::RepeatingTwoPassStandFillingRegime() {

    itsState = START;

    itsEntryDecade = 0;

    itsReentryDecade = 0;

    itsReturnInterval = 0;

    itsReentryRemovalMask = 0;

    itsTargetCut = 0;

}



RepeatingTwoPassStandFillingRegime::~RepeatingTwoPassStandFillingRegime() {

    delete itsReentryRemovalMask;

}



/* inline */ int RepeatingTwoPassStandFillingRegime::isA() {

    return EVENT_REPEATING_TWO_PASS_STAND_FILLING_REGIME;

}



int RepeatingTwoPassStandFillingRegime::conditions() {

    int passed;

    

    switch (itsState) {



    case ENTRYPENDING :

        if (currentDecade < itsEntryDecade) {

        	   passed = 0;

        } else if ((currentDecade-itsEntryDecade) % itsReturnInterval != 0) {

            passed = 0;

        } else {

            passed = 1;

            itsState = ENTRYREADY;

        }

        break;



    case REENTRYPENDING :

        if ((currentDecade-itsReentryDecade) % itsReturnInterval != 0) {

            passed = 0;

        } else {

            passed = 1;

            itsState = REENTRYREADY;

        }

        break;



    case DONE :

        passed = 0;

        break;



    default :

        errorSys("Illegal call to RepeatingTwoPassStandFillingRegime::conditions.", STOP);

        break;

    }

    return passed;

}



void RepeatingTwoPassStandFillingRegime::harvest() {



    switch (itsState) {

    

    case ENTRYREADY :

        HarvestRegime::harvest();

        itsState = REENTRYPENDING;

        break;



    case REENTRYREADY :

        reharvest();

        itsState = ENTRYPENDING;

        break;



     default :

        errorSys("Illegal call to RepeatingTwoPassStandFillingRegime::harvest.", STOP);

        break;

    }

}



void RepeatingTwoPassStandFillingRegime::read(FILE* infile) {

    if (itsState == START) {

        HarvestRegime::read(infile);

        itsState = ENTRYPENDING;

    } else {

        errorSys("Illegal call to RepeatingTwoPassStandFillingRegime::read.", STOP);

    }

}



void RepeatingTwoPassStandFillingRegime::readCustomization1(FILE* infile) {

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

    if (fscanc(infile, "%d", &itsReturnInterval)!=1)

        errorSys("Error reading return interval from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsReturnInterval=itsReturnInterval/pCoresites->TimeStep_Harvest;

	if(itsReturnInterval<pCoresites->TimeStep_Harvest)

		itsReturnInterval=1;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%d", &itsTargetCut)!=1)

    errorSys("Error reading target cut from harvest section.",STOP);

}



void RepeatingTwoPassStandFillingRegime::readCustomization2(FILE* infile) {

    itsReentryRemovalMask = new SiteRemovalMask;

    itsReentryRemovalMask->read(infile);

    setDuration(1);

}



int RepeatingTwoPassStandFillingRegime::isHarvestDone() {

    int result;

    result = getReport()->numberOfSitesCut() >= itsTargetCut;

    return result;

}



int RepeatingTwoPassStandFillingRegime::harvestStand(Stand* stand) {

    SiteHarvester theSiteHarvester(getSequentialId(), getRemovalMask(), getReport(), getDuration());

    FillingStandHarvester theStandHarvester(stand, &theSiteHarvester, &itsPath);

    int standCut = theStandHarvester.harvest();

    return standCut;

}



void RepeatingTwoPassStandFillingRegime::reharvest() {

    LDPOINT pt;

    int sumCut = 0;



    getReport()->reset();

    SiteHarvester theSiteHarvester(getSequentialId(), itsReentryRemovalMask, getReport(), getDuration());



    for (HarvestPathIterator it(itsPath); it.more(); it.advance()) {

        pt = it.current();

        if (canBeHarvested(pt))

            sumCut += theSiteHarvester.harvest(pt);

    }

    itsPath.reset();

    

    writeReport(harvestOutputFile2);

}

