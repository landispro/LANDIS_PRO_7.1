////////////////////////////////////////

//Last modified by Wei Li to incorporate planning code

// August 27, 2004

//

//

///////////////////////////////////////



#include "system1.h"

#include "point.h"

#include "site.h"

#include "SiteRemovalMask.h"

#include "HarvestReport.h"

#include "agelist.h"

#include "CohortRemovalMask.h"

//#include "landis.h"

#include "GlobalFunctions.h"

#include "GlobalVariables.h"

#include "SiteHarvester.h"



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

//  SITE* site = sites(pt.y,pt.x);

	//<Add By Qia on Oct 23 2008>

	pCoresites->BefStChg(pt.y,pt.x);

	//</Add By Qia on Oct 23 2008>

	

	SITE* site = (*pCoresites)(pt.y,pt.x);
	LANDUNIT *l;
	l=pCoresites->locateLanduPt(pt.y,pt.x);
    AGELIST* a;

    CohortRemovalMask* m;

    int cohortCut;

    int siteCut = 0;

	

	//by wei li

	int sitePlanted = 0;

	//by wei li



    for (int i = 1; i <= numberOfSpecies; i++) 

	{

        a = (AGELIST*) (*site)(i);

        m = (*itsRemovalMask)(i);

        cohortCut = harvestCohorts(a, m);

		//<Add By Qia on Feb 16 2010>

		double tmpBiomass, tmpCarbon;

		for (int age=pCoresites->TimeStep_Harvest; age<=320; age+=pCoresites->TimeStep_Harvest) {

	        if (m->query(age) && a->query(age)) {

				tmpBiomass=exp(pCoresites->GetBiomassData(site->specAtt(i)->BioMassCoef,1)+pCoresites->GetBiomassData(site->specAtt(i)->BioMassCoef,2)*log(pCoresites->GetGrowthRates(i,age/pCoresites->TimeStep,l->ltID)))*((*pCoresites) (pt.y,pt.x)->SpecieIndex(i)->getTreeNum(age/pCoresites->TimeStep,i))/1000.00;

				pCoresites->Harvest70outputIncreaseBiomassvalue(pt.y,pt.x,tmpBiomass);

				tmpCarbon=exp(pCoresites->GetBiomassData(site->specAtt(i)->BioMassCoef,1)+pCoresites->GetBiomassData(site->specAtt(i)->BioMassCoef,2)*log(pCoresites->GetGrowthRates(i,age/pCoresites->TimeStep,l->ltID)))*(*pCoresites) (pt.y,pt.x)->SpecieIndex(i)->getTreeNum(age/pCoresites->TimeStep,i);

				pCoresites->Harvest70outputIncreaseCarbonvalue(pt.y,pt.x,tmpCarbon*site->specAtt(i)->CarbonCoEfficient);

	        }

    	}

		//</Add By Qia on Feb 16 2010>

        itsReport->addToSpeciesTotal(i, cohortCut);

        if (cohortCut > 0) siteCut = 1;

		

		//by wei li

		if (itsRemovalMask->plantingCode(i) && !a->query(pCoresites->TimeStep_Harvest)) 

		{

            a->set(pCoresites->TimeStep_Harvest);

            sitePlanted = 1;

			

        }

		//end by wei li

    }

    if (siteCut == 1) {

        itsReport->incrementSiteCount();

/*  Modified by Vera

        site->harvestType = (short) itsHarvestType;

        site->lastHarvest = (short) currentDecade;

        site->harvestExpirationDecade = (short) (currentDecade + itsDuration);

        setUpdateFlags(pt.y,pt.x);

*/

		pHarvestsites->BefStChg(pt.y,pt.x); //Add By Qia on Nov 07 2008

        //(*pHarvestsites)(pt.y, pt.x)->harvestType = (short) itsHarvestType;

        //(*pHarvestsites)(pt.y, pt.x)->lastHarvest = (short) currentDecade;



		//update PDP

		m_pPDP->sTSLHarvest[pt.y][pt.x] = 0;

		m_pPDP->cHarvestEvent[pt.y][pt.x] = (short) itsHarvestType;



        (*pHarvestsites)(pt.y, pt.x)->harvestExpirationDecade = (short) (currentDecade + itsDuration);

		pHarvestsites->AftStChg(pt.y,pt.x);

		setUpdateFlags(pt.y,pt.x);

    }



	//by wei li

	if (siteCut || sitePlanted)

        setUpdateFlags(pt.y,pt.x);

	//by wei li

	//<Add By Qia on Oct 23 2008>

	pCoresites->AftStChg(pt.y,pt.x);

	//</Add By Qia on Oct 23 2008>

    return siteCut;

}



int SiteHarvester::harvestCohorts(AGELIST* cohorts, CohortRemovalMask* mask) {

    int sumCut = 0;

    for (int age=pCoresites->TimeStep_Harvest; age<=320; age+=pCoresites->TimeStep_Harvest) {

        if (mask->query(age) && cohorts->query(age)) {

            cohorts->reset(age);

						

            sumCut += age;

        }

    }

    return sumCut;

}





