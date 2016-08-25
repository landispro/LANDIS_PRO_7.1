#ifndef STANDRANKINGALGORITHM_H

#define STANDRANKINGALGORITHM_H



#include <stdio.h>

#include "site.h"

#include "List.h"

#include "Stand.h"

#include "SiteHarvester.h"

#include "ManagementArea.h"

//#include "GlobalVariables.h"



//#include "stands.h"



class StandRankingAlgorithm {

public :

    StandRankingAlgorithm(int someManagementAreaId, int someRotationAge);

    virtual ~StandRankingAlgorithm() {}



    virtual void read(FILE* infile) = 0;

    virtual void rankStands(List<int>& theRankedList) = 0;



	/* begin: added by Vera*/

//	extern STANDS*					pstands;

	/* end:  added by Vera*/



protected :

    void filter(IntArray& theStandArray, IntArray& theAgeArray, int& theLength);

    void ascendingSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength);

    void descendingSort(IntArray& theStandArray, IntArray& theSortKeyArray, int theLength);

	void descendingSort_doubleArray(IntArray& theStandArray, double* theSortKeyArray, int theLength);//Add by Qia

    void assign(IntArray& theStandArray, int theLength, List<int>& theRankedList);

	//<Add By Qia on Oct 03 2009>

	void filterByVolume(IntArray& theStandArray, IntArray& theAgeArray, int& theLength);

	//</Add By Qia on Oct 03 2009>



protected :

    ManagementArea* itsManagementArea;

    int itsRotationAge;



};



#endif



