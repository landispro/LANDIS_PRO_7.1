#include <stdio.h>

#include "system1.h"

//#include "landis.h"

#include "point.h"

#include "agelist.h"

#include "site.h"

#include "IntArray.h"

#include "ManagementArea.h"

#include "SiteHarvester.h"

#include "Stand.h"

#include "StandIterator.h"

#include "GlobalVariables.h"

#include "CohortRemovalMask.h"

#include "SiteRemovalmask.h"

#include "RelativeOldestRank.h"



RelativeOldestRank::RelativeOldestRank(int someManagementAreaId, int someRotationAge, SiteRemovalMask* someSiteRemovalMask) :

      StandRankingAlgorithm(someManagementAreaId, someRotationAge) {

    itsRemovalMask = someSiteRemovalMask;

}



void RelativeOldestRank::rankStands(List<int>& theRankedList) {

    int i, id;

    Stand* stand;

    int theLength;

    IntArray theStandArray(itsManagementArea->numberOfStands());

    IntArray theAgeArray(itsManagementArea->numberOfStands());

    IntArray theSortKeyArray(itsManagementArea->numberOfStands());



    filter(theStandArray, theAgeArray, theLength);



    for (i = 1; i <= theLength; i++) {

        id = theStandArray[i];

//      stand = stands(id);  Modified by Vera

		stand = (*pstands)(id);

        theSortKeyArray[i] = computeStandImportance(stand);

    }



    descendingSort(theStandArray, theSortKeyArray, theLength);

    assign(theStandArray, theLength, theRankedList);

}



int RelativeOldestRank::computeStandImportance(Stand* stand) {

    LDPOINT p;

    SITE* site;

    int count = 0;

    float sum = 0.0;

    float relativeAge;



    for (StandIterator it(*stand); it.moreSites(); it.gotoNextSite()) {

        p = it.getCurrentSite();

//        site = sites(p.y,p.x);   modified by Vera

        site = (*pCoresites)(p.y,p.x);



        if (pCoresites->locateLanduPt(p.y,p.x)->active()) {//Original landis4.0: site->landUnit->active()

															//Changed By Qia on Oct 13 2008

        	relativeAge = computeSiteImportance(site);

            sum += relativeAge;

            count++;

        }

    }

    if (count == 0)

        return 0;

    else

        return (int) ((sum/count)*1000);

}



float RelativeOldestRank::computeSiteImportance(SITE* site) {

    AGELIST* a;

    CohortRemovalMask* m;

    int longevity;

    float maxAge = 0.0;

    int i;

   

    for (i = 1; i <= numberOfSpecies; i++) {

        m = (*itsRemovalMask)(i);

        if (m->query()) {

            a = (AGELIST*) (*site)(i);

            longevity=(*pspeciesAttrs)(i)->longevity;

            maxAge = max(maxAge, (float)(a->oldest()/(float)longevity));

        }

    }

    return maxAge;

}



