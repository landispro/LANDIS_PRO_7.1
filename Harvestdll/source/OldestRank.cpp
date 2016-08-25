#include "ManagementArea.h"

#include "SiteHarvester.h"

#include "List.h"

#include "IntArray.h"

#include "OldestRank.h"



void OldestRank::rankStands(List<int>& theRankedList) {

    int theLength;

    IntArray theStandArray(itsManagementArea->numberOfStands());

    IntArray theAgeArray(itsManagementArea->numberOfStands());



    filter(theStandArray, theAgeArray, theLength);

    descendingSort(theStandArray, theAgeArray, theLength);

    assign(theStandArray, theLength, theRankedList);

}



