// FireRiskRank.cpp: implementation of the FireRiskRank class.

//

//////////////////////////////////////////////////////////////////////

#include "FuelTreatmentRank.h"

#include "ManagementArea.h"

#include "SiteHarvester.h"

#include "List.h"

#include "IntArray.h"

#include "FUELStand.h"

#include "StandIterator.h"

//#include "GlobalVariables.h"

#include "ManagementAreaIterator.h"

#include "ManagementAreas.h"



#include "System1.h"

#include "error.h"



#include "FuelGlobalVariables.h"





//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////



FuelTreatmentRank::FuelTreatmentRank(int manageArea,int itflag, int itMinClass) {

	

    itsManagementArea = managementAreas(manageArea);

	flag = itflag;

	minClass = itMinClass;



};



FuelTreatmentRank::~FuelTreatmentRank(){}





    /**

    * This is the algorithm that will rank the stands potentual fire risk

    * 

    * @param theRankedList    the linked list of the stands in order

    * @return            the list was sent in empty by reference and now is full

    */

   long FuelTreatmentRank::rankStands(List<int>& theRankedList) {

       int i, id;

       FUELStand* stand;

       int theLength;

 	   long totalCell = 0;

		
	theLength = itsManagementArea->numberOfStands();
       IntArray theStandArray(itsManagementArea->numberOfStands());

       IntArray theAgeArray(itsManagementArea->numberOfStands());

       IntArray theSortKeyArray(itsManagementArea->numberOfStands());

		

       totalCell = filter(theStandArray, theAgeArray, theLength, minClass);

	   for (i = 1; i <= theLength; i++) {

           id = theStandArray[i];

           stand = (*fuelpstands)(id);
		   totalCell+=stand->numberOfActiveSites();

		   // get potential fire risk for each stand

		   int firerisk = (int) (stand->getMeanFireRisk()*100 + 0.5);

		   //int firerisk = (int) (stand->itMeanFireRisk * 100 + 0.5);

		   // if potential fire risk biger than minFireRisk, then add this stand into list

		   //if (firerisk >= minFireRisk)

			theSortKeyArray[i] = firerisk;

       }


	   if(flag == 0){
			descendingSort(theStandArray, theSortKeyArray, theLength);
	   }
	   else if(flag == 1){
		   ascendingSort(theStandArray, theSortKeyArray, theLength);
	   }
	   else{
		   randomSort(theStandArray, theSortKeyArray, theLength);
	   }
       assign(theStandArray, theLength, theRankedList);

	   return	totalCell;



   }



	long FuelTreatmentRank::filter(IntArray& theStandArray, IntArray& theAgeArray, int& theLength, int minFireRisk) {

	    int id;                 // used to keep track of which stand we are looking at

		FUELStand* stand;           // generic pointer to any stand

		int theNewLength = 0;   // a counter to move through the arrays and set the value of theLength at the end

		float fireRisk = 0;

		long totalCell = 0;

		for (ManagementAreaIterator it(*itsManagementArea); it.moreStands(); it.gotoNextStand()) {

			id = it.getCurrentStand();

			stand = (*fuelpstands)(id);

			stand->itsUpdateFireRiskFlag = 1;

			fireRisk = stand->getMeanFireRisk();

			

			if (fireRisk >= minFireRisk) {

			    theNewLength++;

		        theStandArray[theNewLength] = id;

			    theAgeArray[theNewLength] = stand->getAge();

				//printf("%d  meanfirerisk  %f \n", id, stand->itMeanFireRisk);				

			}

			totalCell += stand->itsFuelTreatmentSites;

		}

		theLength = theNewLength;

		return totalCell;

	}

	

// ascending sorting

void FuelTreatmentRank::ascendingSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength) {

    int temp;

    for (int i = 1; i <= theLength-1; i++) {

        for (int j = i+1; j <= theLength; j++) {

            if (theSortKeyArray[j] < theSortKeyArray[i]) {

                temp = theStandArray[j]; 

                theStandArray[j] = theStandArray[i]; 

                theStandArray[i] = temp;

                temp = theSortKeyArray[j]; 

                theSortKeyArray[j] = theSortKeyArray[i]; 

                theSortKeyArray[i] = temp;

            }

        }

    }

}


// random sorting

void FuelTreatmentRank::randomSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength) {

    int temp, k;

   for (int i = 1; i <= theLength; i++) {

        k = (int) (theLength * frand()) + 1;

        temp = theStandArray[i];

        theStandArray[i] = theStandArray[k];

        theStandArray[k] = temp;

    }

}

/**

 * Sorts the stands according to their key with largest being first

 *

 * @param theStandArray         IntArray of the stands in the management area

 * @param theSortKeyArray       IntArray of the keys to sort the arrays by

 * @param theLength             the length of the two arrays

 * @return void                 everything is passed by reference 

 */



void FuelTreatmentRank::descendingSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength) {

    int temp;

    for (int i = 1; i <= theLength-1; i++) {

        for (int j = i+1; j <= theLength; j++) {

            if (theSortKeyArray[j] > theSortKeyArray[i]) {

                temp = theStandArray[j];

				theStandArray[j] = theStandArray[i];

				theStandArray[i] = temp;

                temp = theSortKeyArray[j];

				theSortKeyArray[j] = theSortKeyArray[i];

				theSortKeyArray[i] = temp;

            }

        }

    }

	

}





/**

 * This takes the stands from the sorted stand array and put them into a linked list named theRankedList

 *

 * @param theStandArray         IntArray of the stands in the management area after been sorted 

 * @param theLength             the length of the arrays

 * @param theRankedList         A linked list of the sorted stands

 * @return void                 everything is passed by reference 

 */



void FuelTreatmentRank::assign(IntArray& theStandArray, int theLength, List<int>& theRankedList) {



    // Local Variables

    int rank = 1;  // used to set the rank



    // loop through all the stands and resest their rank to zero so they can be re-ranked next time

    for (int i = 1; i <= fuelpstands->number(); i++)

        (*fuelpstands)(i)->setRank(0);



    // make the ranked list from the sorted stand array

    for (int j = 1; j <= theLength; j++) {

        (*fuelpstands)(theStandArray[j])->setRank(rank++);

        theRankedList.append(theStandArray[j]);

    }

}







