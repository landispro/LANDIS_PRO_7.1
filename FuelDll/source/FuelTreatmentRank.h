// FireRiskRank.h: interface for the FireRiskRank class.

//

//////////////////////////////////////////////////////////////////////

#ifndef _FUELTREAT_

#define _FUELTREAT_



#include <stdio.h>

#include "IntArray.h"

#include "List.h"

#include "SiteHarvester.h"

#include "ManagementArea.h"

//#include "StandRankingAlgorithm.h"





//class FireRiskRank : public StandRankingAlgorithm

//class FuelTreatmentRank : public StandRankingAlgorithm

class FuelTreatmentRank

{

public:

	FuelTreatmentRank (int, int, int);

    

	virtual ~FuelTreatmentRank();



    long rankStands(List<int>& theRankedList);		// rank the stands for fuel treatment

	//void filter(IntArray& theStandArray, IntArray& theAgeArray, int& theLength, int minFireRisk);

	long filter(IntArray& ,IntArray& , int& , int );	// filter the stands

    void ascendingSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength);		// ascending sorting

    void descendingSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength);		// descending sorting

	void randomSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength);		// random sorting

    void assign(IntArray& theStandArray, int theLength, List<int>& theRankedList);				// assign the sort



	int minClass;		// mimum potential fire risk for fuel treatment

	int flag;			// flag of ranking

    ManagementArea* itsManagementArea;		// array of management area



};



#endif

