#include "system1.h"

#include "point.h"

#include "site.h"

#include "SiteRemovalMask.h"

#include "HarvestReport.h"

#include "agelist.h"

#include "CohortRemovalMask.h"

//#include "landis.h"

//#include "GlobalFunctions.h"

//#include "GlobalVariables.h"

#include "SiteHarvester.h"

#include "FuelGlobalVariables.h"





SiteHarvester::SiteHarvester(int harvestType, SiteRemovalMask* someRemovalMask, HarvestReport* someReport, int someDuration) {

    itsHarvestType = harvestType;

    itsRemovalMask = someRemovalMask;

    itsReport = someReport;

    itsDuration = someDuration;

}



/* inline */ int SiteHarvester::getHarvestType() {

    return itsHarvestType;

}



/* inline */ SiteRemovalMask* SiteHarvester::getRemovalMask() {

    return itsRemovalMask;

}



/* inline */ HarvestReport* SiteHarvester::getReport() {

    return itsReport;

}



/* inline */ int SiteHarvester::getDuration() {

    return itsDuration;

}



int SiteHarvester::harvest(const LDPOINT& pt) {

  /*  SITE* site = (*pfuelcoresites)(pt.y,pt.x);

    AGELIST* a;

    CohortRemovalMask* m;

    int cohortCut;

    int siteCut = 0;



    for (int i = 1; i <= numberOfSpecies; i++) {

        a = (AGELIST*) (*site)(i);

        m = (*itsRemovalMask)(i);

        cohortCut = harvestCohorts(a, m);

        itsReport->addToSpeciesTotal(i, cohortCut);

        //if (cohortCut > 0) siteCut = 1;

		//??

		siteCut = 1;

    }

    if (siteCut == 1) {

        itsReport->incrementSiteCount();

        site->harvestType = (short) itsHarvestType;

        site->lastHarvest = (short) currentDecade;

        site->harvestExpirationDecade = (short) (currentDecade + itsDuration);

        setUpdateFlags(pt.y,pt.x);

    }

    return siteCut;*/

	return 0;

}



int SiteHarvester::harvestCohorts(AGELIST* cohorts, CohortRemovalMask* mask) 

{

	/*

    int sumCut = 0;

    for (int age=10; age<=640; age+=10) {

        if (mask->query(age) && cohorts->query(age)) {

            cohorts->reset(age);

            sumCut += age;

        }

    }

    return sumCut;

	*/

	return 0;

}





