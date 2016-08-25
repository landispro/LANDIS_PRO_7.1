#include <assert.h>

#include "point.h"

#include "system1.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "Stand.h"

#include "SiteHarvester.h"

#include "StandIterator.h"

#include "BoundedPocketStandHarvester.h"

#include "MultiplePocketStandHarvester.h"



MultiplePocketStandHarvester::MultiplePocketStandHarvester(Stand* stand, float proportion, float meanGroupSize,

  float standardDeviation, SiteHarvester* siteHarvester) {

    assert(stand);

    assert(proportion > 0.0);

    assert(meanGroupSize >= 1.0); //original assert(meanGroupSize > 1.0), Qia changed to >=

    assert(standardDeviation >= 0.0);

    assert(siteHarvester);

    itsProportion = proportion;

    itsMeanGroupSize = meanGroupSize;

    itsStandardDeviation = standardDeviation;

    itsTargetCut = 0;

    setStand(stand);

    setSiteHarvester(siteHarvester);

}



int MultiplePocketStandHarvester::getRandomStartPoint(LDPOINT& startPoint) {

	static int count = 0;
	count++;

    LDPOINT pt;

    int found;



    for (int i=0; i<100; i++) {

        pt = getStand()->getRandomPoint();

        found = isValidStartPoint(pt);

        if (found) break;

    }
	
    if (!found) 
	{
		
		assert(getStand() != NULL);		
        
		for (StandIterator it(*getStand()); it.moreSites(); it.gotoNextSite()) 
		{
			
            pt = it.getCurrentSite();

            found = isValidStartPoint(pt);

            if (found) break;

        }
		
    }



    startPoint = pt;

    return found;

}



/* inline */ int MultiplePocketStandHarvester::isValidStartPoint(LDPOINT pt) {

   // return canBeHarvested(pt) && (visitationMap(pt.y,pt.x) != currentHarvestEventId);
	// %%# Changed 7
	return canBeHarvested(pt) && (visitationMap.get_data(pt.y, pt.x) != currentHarvestEventId);

}



int MultiplePocketStandHarvester::harvest() {
	
    LDPOINT startPoint;

    int targetPocketCut=0;

    
	BoundedPocketStandHarvester* pocketHarvester;
	
	
    int pocketCut = 0;

    int sumCut = 0;

	
	itsTargetCut = (int) (getStand()->numberOfActiveSites() * itsProportion);

	while (sumCut < itsTargetCut) {

		if (!getRandomStartPoint(startPoint)) break;

		targetPocketCut = getRandomGroupSize();

		//BoundedPocketStandHarvester pocketHarvester(targetPocketCut, startPoint, getSiteHarvester());
		pocketHarvester = new BoundedPocketStandHarvester(targetPocketCut, startPoint, getSiteHarvester());

	
		pocketCut = pocketHarvester->harvest();

		//pocketCut = pocketHarvester.harvest();

		sumCut += pocketCut;

		delete pocketHarvester;
		pocketHarvester = NULL;

    }

	
    return sumCut;

}



int MultiplePocketStandHarvester::getRandomGroupSize() {

    int gsize;

    while ((gsize = (int) gasdev(itsMeanGroupSize, itsStandardDeviation)) < 1);

    return gsize;

}





