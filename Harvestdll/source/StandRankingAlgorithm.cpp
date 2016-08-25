#include <stdio.h>

#include "site.h"

#include <assert.h>

//#include "landis.h"

#include "GlobalVariables.h"

#include "IntArray.h"

#include "List.h"

#include "Stand.h"



//#include "Stands.h" //add by Vera



#include "StandIterator.h"

#include "ManagementArea.h"

#include "ManagementAreaIterator.h"

#include "SiteHarvester.h"

#include "StandRankingAlgorithm.h"



StandRankingAlgorithm::StandRankingAlgorithm(int someManagementAreaId, int someRotationAge) {

    itsManagementArea = managementAreas(someManagementAreaId);

    itsRotationAge = someRotationAge;

}



void StandRankingAlgorithm::filter(IntArray& theStandArray, IntArray& theAgeArray, int& theLength) {

	
    Stand* stand;

    int theNewLength = 0;
	int count = 0;


    for (ManagementAreaIterator it(*itsManagementArea); it.moreStands(); it.gotoNextStand()) {

	
        int id = it.getCurrentStand();

//      stand = stands(id);  Modified by Vera

		stand = (*pstands)(id);

        if (stand->canBeHarvested() && stand->getAge() >= itsRotationAge) {

            theNewLength++;

            theStandArray[theNewLength] = id;

            theAgeArray[theNewLength] = stand->getAge();

        }

    }

    theLength = theNewLength;

}

//<Add By Qia on Oct 3rd 2009>

void StandRankingAlgorithm::filterByVolume(IntArray& theStandArray, IntArray& theAgeArray, int& theLength) {

    int id;

    Stand* stand;

    int theNewLength = 0;



    for (ManagementAreaIterator it(*itsManagementArea); it.moreStands(); it.gotoNextStand()) {

        id = it.getCurrentStand();

//      stand = stands(id);  Modified by Vera

		stand = (*pstands)(id);

        if (stand->canBeHarvested() && stand->ComputeStandVolume()>= 0) {

            theNewLength++;

            theStandArray[theNewLength] = id;

            theAgeArray[theNewLength] = stand->ComputeStandVolume();

        }

    }

    theLength = theNewLength;

}



//</Add By Qia on Oct 3rd 2009>

void StandRankingAlgorithm::ascendingSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength) {

    int temp;

    for (int i = 1; i <= theLength-1; i++) {

        for (int j = i+1; j <= theLength; j++) {

            if (theSortKeyArray[j] < theSortKeyArray[i]) {

                temp = theStandArray[j]; theStandArray[j] = theStandArray[i]; theStandArray[i] = temp;

                temp = theSortKeyArray[j]; theSortKeyArray[j] = theSortKeyArray[i]; theSortKeyArray[i] = temp;

            }

        }

    }

}



void StandRankingAlgorithm::descendingSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength) {

    int temp;

    for (int i = 1; i <= theLength-1; i++) {

        for (int j = i+1; j <= theLength; j++) {

            if (theSortKeyArray[j] > theSortKeyArray[i]) {

                temp = theStandArray[j]; theStandArray[j] = theStandArray[i]; theStandArray[i] = temp;

                temp = theSortKeyArray[j]; theSortKeyArray[j] = theSortKeyArray[i]; theSortKeyArray[i] = temp;

            }

        }

    }

}



void StandRankingAlgorithm::descendingSort_doubleArray(IntArray& theStandArray, double* theSortKeyArray, int theLength){//Add by Qia 

    int temp;

	double temp_double;

    for (int i = 1; i <= theLength-1; i++) {

        for (int j = i+1; j <= theLength; j++) {

            if (theSortKeyArray[j] > theSortKeyArray[i]) {

                temp = theStandArray[j]; theStandArray[j] = theStandArray[i]; theStandArray[i] = temp;

                temp_double = theSortKeyArray[j]; theSortKeyArray[j] = theSortKeyArray[i]; theSortKeyArray[i] = temp_double;

            }

        }

    }

}

void StandRankingAlgorithm::assign(IntArray& theStandArray, int theLength, List<int>& theRankedList) {



/*  

	for (int i = 1; i <= stands.number(); i++)   Modified by Vera

	stands(i)->setRank(0);										

*/

	for (int i = 1; i <= pstands->number(); i++)

        (*pstands)(i)->setRank(0);



    int rank = 1;

    for (int i = 1; i <= theLength; i++) {

//      stands(theStandArray[i])->setRank(rank++);   Modified by Vera

		(*pstands)(theStandArray[i])->setRank(rank++);

        theRankedList.append(theStandArray[i]);

    }

}



