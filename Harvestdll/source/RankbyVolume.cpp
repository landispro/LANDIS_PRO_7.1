#include "system1.h"

#include "ManagementArea.h"

#include "SiteHarvester.h"

#include "List.h"

#include "IntArray.h"

#include "OldestRank.h"

#include "RankbyVolume.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "StandIterator.h"

//add by Qia on Sep 01 2009



/*RankbyVolume::RankbyVolume(int someManagementAreaId, int someRotationAge): StandRankingAlgorithm(someManagementAreaId, someRotationAge) {

    

}*/

void RankbyVolume::rankStands(List<int>& theRankedList) {

    int i, id;

    Stand* stand;

    int theLength;

	double *SortKeyArrayDouble;

    IntArray theStandArray(itsManagementArea->numberOfStands());

    IntArray theAgeArray(itsManagementArea->numberOfStands());

    IntArray theSortKeyArray(itsManagementArea->numberOfStands());



    filter(theStandArray, theAgeArray, theLength);

	SortKeyArrayDouble = new double[theLength+1];

    for (i = 1; i <= theLength; i++) {

        id = theStandArray[i];

//      stand = stands(id);  Modified by Vera

		stand = (*pstands)(id);

        SortKeyArrayDouble[i] = computeStandBA(stand);

    }



    descendingSort_doubleArray(theStandArray, SortKeyArrayDouble, theLength);

    assign(theStandArray, theLength, theRankedList);

	delete SortKeyArrayDouble;

}





double RankbyVolume::computeStandBA(Stand* stand) {

    LDPOINT p;

    SITE* site;

    double count = 0;

	int m,k;

    double TmpBasalAreaS=0;
	LANDUNIT *l;
    for (StandIterator it(*stand); it.moreSites(); it.gotoNextSite()) {

        p = it.getCurrentSite();

//        site = sites(p.y,p.x);   modified by Vera

        site = (*pCoresites)(p.y,p.x);
		
		l=pCoresites->locateLanduPt(p.y,p.x);
		count+=1;

        for(k=1;k<=pCoresites->specNum;k++){

			for(m=1;m<=site->specAtt(k)->longevity/pCoresites->TimeStep;m++)

				{

					TmpBasalAreaS+=pCoresites->GetGrowthRates(k,m,l->ltID)*pCoresites->GetGrowthRates(k,m,l->ltID)/4*3.1415926*site->SpecieIndex(k)->getTreeNum(m,k)/10000.00;

				}

		}

    }

	if(count>0){

		TmpBasalAreaS=TmpBasalAreaS/count;

	}

    return TmpBasalAreaS;

}

