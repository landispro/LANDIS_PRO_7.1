#include "error.h"

#include "point.h"

#include "List.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "HarvestPath.h"

#include "SiteHarvester.h"

#include "StandHarvester.h"

#include "HarvestRegime.h"

#include "HarvestPathIterator.h"

#include "TwoPassStandBasedRegime.h"



TwoPassStandBasedRegime::TwoPassStandBasedRegime() {

    itsState = START;

    itsEntryDecade = 0;

    itsReentryDecade = 0;

    itsReentryRemovalMask = 0;

    itsTargetCut = 0;

}



TwoPassStandBasedRegime::~TwoPassStandBasedRegime() {

    delete itsReentryRemovalMask;

}



int TwoPassStandBasedRegime::conditions() {

    int passed;

    

    switch (itsState) {



    case ENTRYPENDING :

        if (currentDecade == itsEntryDecade) {

            passed = 1;

            itsState = ENTRYREADY;

        } else

            passed = 0;

        break;



    case REENTRYPENDING :

        if (currentDecade == itsReentryDecade) {

            passed = 1;

            itsState = REENTRYREADY;

        } else

            passed = 0;

        break;



    case DONE :

        passed = 0;

        break;



    default :

        errorSys("Illegal call to GroupSelectionRegime::conditions.", STOP);

        break;

    }

    return passed;

}



void TwoPassStandBasedRegime::harvest() {



    switch (itsState) {

    

    case ENTRYREADY :

        HarvestRegime::harvest();

        itsState = REENTRYPENDING;

        break;



    case REENTRYREADY :

        reharvest();

        itsState = DONE;

        break;



     default :

        errorSys("Illegal call to TwoPassStandBasedRegime::conditions.", STOP);

        break;

    }

}



int TwoPassStandBasedRegime::isHarvestDone() {

    int result;

    result = getReport()->numberOfSitesCut() >= itsTargetCut;

    return result;

}



void TwoPassStandBasedRegime::reharvest() {

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



