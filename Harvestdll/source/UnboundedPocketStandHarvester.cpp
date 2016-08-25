#include <assert.h>

//#include "landis.h"

#include "point.h"

#include "List.h"

#include "SiteHarvester.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "HarvestPath.h"

#include "HarvestPathIterator.h"

#include "BoundedPocketStandHarvester.h"

#include "UnboundedPocketStandHarvester.h"



UnboundedPocketStandHarvester::UnboundedPocketStandHarvester(int targetCut, LDPOINT startPoint, SiteHarvester* siteHarvester, HarvestPath* path) {



    assert(targetCut >= 0);

//  assert(sites.inBounds(startPoint.y, startPoint.x));  //modified by Vera

	assert(inBounds(startPoint.y, startPoint.x));

    assert(siteHarvester);



    int standId = (int) standMap.getvalue32out(startPoint.y, startPoint.x);//change by Qia on Nov 4 2008

    assert(standId > 0);

//	setStand(stands(standId));			//modified by Vera

	setStand((*pstands)(standId));

    setSiteHarvester(siteHarvester);

    setPath(path);

    itsTargetCut = targetCut;

    itsStartPoint = startPoint;

}



int UnboundedPocketStandHarvester::harvest() {

    int r, c, bestRank;

    LDPOINT pt, startPoint, bestPoint;

    HarvestPath pocketPath;

    BoundedPocketStandHarvester* pocketHarvester;

    HarvestPathIterator* it;

    int pocketCut;

    int sumCut = 0;



    startPoint = itsStartPoint;



    do {

        pocketHarvester = new BoundedPocketStandHarvester(itsTargetCut - sumCut, startPoint, getSiteHarvester(), &pocketPath);

        pocketCut = pocketHarvester->harvest();

        sumCut += pocketCut;

        if (sumCut < itsTargetCut) {

            bestRank = 0;

            for (it = new HarvestPathIterator(pocketPath); it->more(); it->advance()) {

                pt = it->current();

                c = pt.x; r = pt.y;

                rankNeighborSite(r, c-1, bestRank, bestPoint);

                rankNeighborSite(r, c+1, bestRank, bestPoint);

                rankNeighborSite(r-1, c, bestRank, bestPoint);

                rankNeighborSite(r+1, c, bestRank, bestPoint);

            }

            delete it;

            if (bestRank > 0)

                startPoint = bestPoint;

        }

        delete pocketHarvester;

    } while (sumCut < itsTargetCut && bestRank > 0);



    if (getPath()) getPath()->addPath(pocketPath);

    return sumCut;

}



void UnboundedPocketStandHarvester::rankNeighborSite(int r, int c, int& bestRank, LDPOINT& bestSite) {

    int rank;

    LDPOINT pt(c,r);

    int id;

    

//  if (!sites.inBounds(r,c))

	if (!inBounds(r,c))

        return;

    else if ((id = standMap.getvalue32out(r,c)) <= 0)//change by Qia on Nov 4 2008

        return;

    //else if (visitationMap(r,c) == currentHarvestEventId)
	// %%# Changed 1
	else if (visitationMap.get_data(r, c) == currentHarvestEventId)

        return;

//  else if ((rank = stands(id)->getRank()) == 0 || (bestRank > 0 && rank >= bestRank))  Modified by Vera

	else if ((rank = (*pstands)(id)->getRank()) == 0 || (bestRank > 0 && rank >= bestRank))

        return;

    else if (!canBeHarvested(pt))

        return;

    else {

        bestRank = rank;

        bestSite.x = c;

        bestSite.y = r;

    }

}





