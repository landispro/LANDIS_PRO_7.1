#include <assert.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include "system1.h"

#include "error.h"

#include "SiteRemovalMask.h"

#include "GlobalVariables.h"

#include "Stand.h"

#include "List.h"

#include "SiteHarvester.h"

#include "HarvestEvent.h"

#include "StandHarvester.h"

#include "HarvestReport.h"

#include "HarvestPath.h"

#include "MultiplePocketStandHarvester.h"

#include "GroupSelectionRegime.h"



GroupSelectionRegime::GroupSelectionRegime()

{

    itsState = START;

    itsEntryDecade = 0;

    itsReentryInterval = 0;

    itsTargetCut = 0;

    itsStandProportion = 0.0;

    itsMeanGroupSize = 0.0;

    itsStandardDeviation = 0.0;

    itsTotalNumberOfStands = 0;

}



GroupSelectionRegime::~GroupSelectionRegime() {

}



/* inline */ int GroupSelectionRegime::isA() {

    return EVENT_GROUP_SELECTION_REGIME;

}



int GroupSelectionRegime::conditions() {

    int passed;



    switch (itsState) {



    case ENTRYPENDING :

        if (currentDecade < itsEntryDecade)

            passed = 0;

        else if (currentDecade == itsEntryDecade) {

            passed = 1;

            itsState = ENTRYREADY;

        }

        break;



    case REENTRYPENDING :

        if ((currentDecade-itsEntryDecade) % itsReentryInterval != 0)

            passed = 0;

        else {

            passed = 1;

            itsState = REENTRYREADY;

        }

        break;



    default :

        errorSys("Illegal call to GroupSelectionRegime::conditions.", STOP);

        break;

    }



    return passed;

}



void GroupSelectionRegime::harvest() {

	switch (itsState) {



    case ENTRYREADY :
		cerr << " before HarvestRegime::harvest() " << endl;
		 HarvestRegime::harvest();
		 cerr << " after HarvestRegime::harvest() " << endl;
        itsState = REENTRYPENDING;

		break;



    case REENTRYREADY :

		reharvest();

        itsState = REENTRYPENDING;

		break;



   default :

        errorSys("Illegal call to GroupSelection::harvest.", STOP);

    }

}



void GroupSelectionRegime::read(FILE* infile) {

    if (itsState == START) {

        HarvestRegime::read(infile);

        itsState = ENTRYPENDING;

    } else {

        errorSys("Illegal call to GroupSelectionRegime::read.", STOP);

    }

}



void GroupSelectionRegime::readCustomization1(FILE* infile) {

    float targetProportion;

    int standProportionDenominator;

    int rotationLength;



    if (fscanc(infile, "%d", &itsEntryDecade)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsEntryDecade=itsEntryDecade/pCoresites->TimeStep_Harvest;

	if(itsEntryDecade<pCoresites->TimeStep_Harvest)

		itsEntryDecade=1;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%d", &itsReentryInterval)!=1)

        errorSys("Error reading reentry interval from harvest section.",STOP);

	//<Add By Qia on April 08 2009>

	itsReentryInterval=itsReentryInterval/pCoresites->TimeStep_Harvest;

	if(itsReentryInterval<pCoresites->TimeStep_Harvest)

		itsReentryInterval=1;

	//</Add By Qia on April 08 2009>

    if (fscanc(infile, "%f", &targetProportion)!=1)

        errorSys("Error reading management area target proportion from harvest section.",STOP);

    if (fscanc(infile, "%d", &standProportionDenominator)!=1)

        errorSys("Error reading stand proportion denominator from harvest section.",STOP);

    if (fscanc(infile, "%f", &itsMeanGroupSize)!=1)

        errorSys("Error reading mean group size from harvest section.",STOP);

    if (fscanc(infile, "%f", &itsStandardDeviation)!=1)

        errorSys("Error reading standard deviation from harvest section.",STOP);

    itsStandProportion = (float) 1.0 / standProportionDenominator;

    itsTargetCut = (int) (managementAreas(getManagementAreaId())->numberOfStands() * targetProportion);

    rotationLength = (int) (itsReentryInterval * standProportionDenominator);

    setDuration(rotationLength);

}



void GroupSelectionRegime::readCustomization2(FILE* infile) {

}



int GroupSelectionRegime::isHarvestDone() {

    int result;

    result = itsTotalNumberOfStands >= itsTargetCut;

    return result;

}



int GroupSelectionRegime::harvestStand(Stand* stand) {

    SiteHarvester theSiteHarvester(getSequentialId(), getRemovalMask(), getReport(), getDuration());

	MultiplePocketStandHarvester theStandHarvester(stand, itsStandProportion, itsMeanGroupSize, itsStandardDeviation, &theSiteHarvester);

    int standCut = theStandHarvester.harvest();

    if (standCut > 0) {

        stand->reserve();

        itsStands.append(stand->getId());

        itsTotalNumberOfStands++;

    }

    return standCut;

}



void GroupSelectionRegime::reharvest() {

    Stand* stand;

    MultiplePocketStandHarvester* theStandHarvester;

    int standCut;

    SiteHarvester theSiteHarvester(getSequentialId(), getRemovalMask(), getReport(), getDuration());



    getReport()->reset();



    for (ListIterator<int> it(itsStands); it.more(); it.advance()) {

//        stand = stands(it.current());  Modified by Vera

        stand = (*pstands)(it.current());



        theStandHarvester = new MultiplePocketStandHarvester(stand, itsStandProportion, itsMeanGroupSize,

          itsStandardDeviation, &theSiteHarvester);

        standCut = theStandHarvester->harvest();

        delete theStandHarvester;

    }



    writeReport(harvestOutputFile2);

}





