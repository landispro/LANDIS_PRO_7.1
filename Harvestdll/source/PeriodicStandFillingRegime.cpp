#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "SiteRemovalMask.h"

#include "GlobalVariables.h"

#include "Stand.h"

#include "HarvestEvent.h"

#include "StandHarvester.h"

#include "HarvestRegime.h"

#include "SiteHarvester.h"

#include "FillingStandHarvester.h"

#include "PeriodicStandFillingRegime.h"



PeriodicStandFillingRegime::PeriodicStandFillingRegime() {

    itsState = START;

    itsEntryDecade = 0;

    itsFinalDecade = 0;

    itsReentryInterval = 0;

    itsTargetCut = 0;

}



PeriodicStandFillingRegime::~PeriodicStandFillingRegime() {

}



/* inline */ int PeriodicStandFillingRegime::isA() {

    return EVENT_PERIODIC_STAND_FILLING_REGIME;

}



int PeriodicStandFillingRegime::conditions() {

    int passed;



    switch (itsState) {



    case ENTRYPENDING :

        if (currentDecade < itsEntryDecade) {

            passed = 0;

        } else if (currentDecade > itsFinalDecade) {

            passed = 0;

            itsState = DONE;

        } else if ((currentDecade-itsEntryDecade) % itsReentryInterval != 0) {

            passed = 0;

        } else {

            passed = 1;

            itsState = ENTRYREADY;

        }

        break;



    case DONE :

        passed = 0;

        break;



    default :

        errorSys("Illegal call to PeriodicStandFillingRegime::conditions.", STOP);

        break;

    }



    return passed;

}



void PeriodicStandFillingRegime::harvest() {

    switch (itsState) {

    case ENTRYREADY :

        HarvestRegime::harvest();

        itsState = ENTRYPENDING;

        break;

    default :

        errorSys("Illegal call to PeriodicStandFillingRegime::harvest.", STOP);

        break;

    }

}



void PeriodicStandFillingRegime::read(FILE* infile) {

    if (itsState == START) {

        HarvestRegime::read(infile);

        itsState = ENTRYPENDING;

    } else {

        errorSys("Illegal call to PeriodicStandFillingRegime::read.", STOP);

    }

}

void PeriodicStandFillingRegime::readCustomization1(FILE* infile) {

    float targetProportion;



    if (fscanc(infile, "%d", &itsEntryDecade)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsEntryDecade=itsEntryDecade/pCoresites->TimeStep_Harvest;

	if(itsEntryDecade<pCoresites->TimeStep_Harvest)

		itsEntryDecade=1;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%d", &itsFinalDecade)!=1)

        errorSys("Error reading final decade from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsFinalDecade=itsFinalDecade/pCoresites->TimeStep_Harvest;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%d", &itsReentryInterval)!=1)

        errorSys("Error reading reentry interval from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsReentryInterval=itsReentryInterval/pCoresites->TimeStep_Harvest;

	if(itsReentryInterval<pCoresites->TimeStep_Harvest)

		itsReentryInterval=1;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%f", &targetProportion)!=1)

        errorSys("Error reading target proportion from harvest section.",STOP);

    itsTargetCut = (int) (managementAreas(getManagementAreaId())->numberOfActiveSites() * targetProportion);

}



void PeriodicStandFillingRegime::readCustomization2(FILE* infile) {

    setDuration(1);

}



int PeriodicStandFillingRegime::isHarvestDone() {

    int result;

    result = getReport()->numberOfSitesCut() >= itsTargetCut;

    return result;

}



int PeriodicStandFillingRegime::harvestStand(Stand* stand) {

    SiteHarvester theSiteHarvester(getSequentialId(), getRemovalMask(), getReport(), getDuration());

    FillingStandHarvester theStandHarvester(stand, &theSiteHarvester);

    int standCut = theStandHarvester.harvest();

    return standCut;

}



