#include "system1.h"

#include "ManagementArea.h"

#include "SiteHarvester.h"

#include "List.h"

#include "IntArray.h"

#include "OldestRank.h"

#include "RankbyStocking.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "StandIterator.h"

//add by Qia on Sep 01 2009



/*RankbyVolume::RankbyVolume(int someManagementAreaId, int someRotationAge): StandRankingAlgorithm(someManagementAreaId, someRotationAge) {

    

}*/

void RankbyStocking::rankStands(List<int>& theRankedList) {

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

        SortKeyArrayDouble[i] = computeStandStocking(stand);

    }



    descendingSort_doubleArray(theStandArray, SortKeyArrayDouble, theLength);

    assign(theStandArray, theLength, theRankedList);

	delete SortKeyArrayDouble;

}


double RankbyStocking::computeStandStocking(Stand* stand) {

    LDPOINT p;

    SITE* site;

    double count = 0;

	int m,k;

    double num_trees=0; //N
	double Diameters = 0; //D
	double Diameters_square = 0; //D^2
	double x = pCoresites->stocking_x_value;
	double y = pCoresites->stocking_y_value;
	double z = pCoresites->stocking_z_value;
	LANDUNIT *l;
    for (StandIterator it(*stand); it.moreSites(); it.gotoNextSite()) {

        p = it.getCurrentSite();

//        site = sites(p.y,p.x);   modified by Vera
		l=pCoresites->locateLanduPt(p.y,p.x);
        site = (*pCoresites)(p.y,p.x);

		count+=1;

        for(k=1;k<=pCoresites->specNum;k++){

			for(m=1;m<=site->specAtt(k)->longevity/pCoresites->TimeStep;m++)

				{
					num_trees += site->SpecieIndex(k)->getTreeNum(m,k);
					Diameters += pCoresites->GetGrowthRates(k,m,l->ltID)*site->SpecieIndex(k)->getTreeNum(m,k)/2.54;
					Diameters_square += pCoresites->GetGrowthRates(k,m,l->ltID)*pCoresites->GetGrowthRates(k,m,l->ltID)*site->SpecieIndex(k)->getTreeNum(m,k)/2.54/2.54;
				}

		}
		
    }

	return (x*num_trees+y*Diameters+z*Diameters_square)/(pCoresites->CellSize*pCoresites->CellSize/4046.86)/stand->numberOfActiveSites();

}

