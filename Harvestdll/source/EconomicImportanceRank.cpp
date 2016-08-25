#include <stdio.h>

#include "system1.h"

//#include "landis.h"



#include "GlobalVariables.h"

#include "StandIterator.h"

#include "point.h"

#include "agelist.h"

#include "site.h"

#include "IntArray.h"

#include "ManagementArea.h"

#include "SiteHarvester.h"

#include "Stand.h"

#include "CohortRemovalMask.h"

#include "SiteRemovalmask.h"

#include "EconomicImportanceRank.h"





EconomicImportanceRank::EconomicImportanceRank(int someManagementAreaId, int someRotationAge, SiteRemovalMask* someSiteRemovalMask) :

      StandRankingAlgorithm(someManagementAreaId, someRotationAge), itsDollarValuePerTon(numberOfSpecies), itsMaturity(numberOfSpecies) {

    itsRemovalMask = someSiteRemovalMask;

    for (int i = 1; i <= numberOfSpecies; i++) {

        itsDollarValuePerTon[i] = 0;

        itsMaturity[i] = 1;

    }

}



void EconomicImportanceRank::read(FILE* infile) {

    int d,m;

    for (int i = 1; i <= numberOfSpecies; i++) {

        fscanc(infile, "%d", &d);

        fscanc(infile, "%d", &m);

        itsDollarValuePerTon[i] = d;

        itsMaturity[i] = m;

    }

}



void EconomicImportanceRank::rankStands(List<int>& theRankedList) {

    int i, id;

    Stand* stand;

    int theLength;

    IntArray theStandArray(itsManagementArea->numberOfStands());

    IntArray theAgeArray(itsManagementArea->numberOfStands());

    IntArray theSortKeyArray(itsManagementArea->numberOfStands());



    filter(theStandArray, theAgeArray, theLength);



    for (i = 1; i <= theLength; i++) {

        id = theStandArray[i];

//      stand = stands(id);  //Modified by Vera

        stand = (*pstands)(id);



        theSortKeyArray[i] = computeStandImportance(stand);

    }



    descendingSort(theStandArray, theSortKeyArray, theLength);

    assign(theStandArray, theLength, theRankedList);

}



int EconomicImportanceRank::computeStandImportance(Stand* stand) {

    LDPOINT p;

    SITE* site;

    int sum = 0;



    for (StandIterator it(*stand); it.moreSites(); it.gotoNextSite()) {

        p = it.getCurrentSite();

//        site = sites(p.y,p.x); changed by Wei Li

		site = (*pCoresites)(p.y,p.x);

        if (pCoresites->locateLanduPt(p.y,p.x)->active()) {//Original Landis4.0:site->landUnit->active()

        													//Change By Qia on Oct 13 2008

            sum += computeSiteImportance(site);

        }

    }

    return sum;

}



int EconomicImportanceRank::computeSiteImportance(SITE* site) {

    AGELIST* a;

    CohortRemovalMask* m;

    int econImportance = 0;

    int i, k;



    for (i = 1; i <= numberOfSpecies; i++) {

        m = (*itsRemovalMask)(i);

        if (m->query()) {

            a = (AGELIST*) (*site)(i);

            for (k = itsRotationAge; k <= 320; k+=pCoresites->TimeStep_Harvest) {

                if (a->query(k)) {

                    econImportance += (int) ((float) itsDollarValuePerTon[i] / itsMaturity[i] * k/pCoresites->TimeStep_Harvest);

                }

            }

        }

    }

    return econImportance;

}



