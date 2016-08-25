#include "system1.h"

#include "ManagementArea.h"

#include "SiteHarvester.h"

#include "List.h"

#include "IntArray.h"

#include "OldestRank.h"

#include "RandomRank.h"



void RandomRank::rankStands(List<int>& theRankedList) {

	

    IntArray theStandArray(itsManagementArea->numberOfStands());	
    IntArray theAgeArray(itsManagementArea->numberOfStands());
	//cerr << "size of theStandArray = %d it should be 314067\n" << itsManagementArea->numberOfStands() << endl;
	//printf("size of theStandArray = %d it should be less than 314067\n", itsManagementArea->numberOfStands());

	int theLength = 0;
    filter(theStandArray, theAgeArray, theLength);
	
	// other value is euqal to zero.
	//printf("theLength = %d; it should be less than 314067; numberOfStands should be equal or larger than theLength\n", theLength);
	//assert(itsManagementArea->numberOfStands() >= theLength);

	//printf("getsize = %\n", theStandArray.getsize());
	/*cerr << "theStandArray[theLength-1] = " << theStandArray[theLength-1] << endl;
	cerr << "theStandArray[theLength] = " << theStandArray[theLength] << endl;
	cerr << "theStandArray[theLength + 1] = " << theStandArray[theLength+1] << endl;*/

    for (int i = 1; i <= theLength; i++) 
	{
         int k = (int) (theLength * frand()) + 1;

		 // Harvest Bug 04/15/2015
		if (k > theLength) {
			//cerr << "k = " << k << "  k should be equal to " << theLength + 1 << endl;
			
			k = theLength;
		}

		assert(k >= 1 && k <= theLength);

        const int temp = theStandArray[i];

        theStandArray[i] = theStandArray[k];

        theStandArray[k] = temp;

    }



    assign(theStandArray, theLength, theRankedList);

}





