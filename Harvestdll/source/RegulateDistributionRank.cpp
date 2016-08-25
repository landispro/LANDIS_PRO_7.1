#include <assert.h>

#include <stdio.h>

#include <math.h>

#include "system1.h"

//#include "landis.h"

#include "point.h"

#include "agelist.h"

#include "site.h"

#include "IntArray.h"

#include "ManagementArea.h"

#include "ManagementAreaIterator.h"

#include "SiteHarvester.h"

#include "Stand.h"

#include "StandIterator.h"

#include "GlobalVariables.h"

#include "CohortRemovalMask.h"

#include "SiteRemovalMask.h"

#include "RegulateDistributionRank.h"



void RegulateDistributionRank::read(FILE* infile) {

    fscanc(infile, "%d", &itsScaleFactor);

}



void RegulateDistributionRank::rankStands(List<int>& theRankedList) {

    int id;

    int standAge;

    int maxStandAge = 0;

    IntArray freq(65);

    int theLength;

    IntArray theStandArray(itsManagementArea->numberOfStands());

    IntArray theAgeArray(itsManagementArea->numberOfStands());

    IntArray theSortKeyArray(itsManagementArea->numberOfStands());



    for (ManagementAreaIterator it(*itsManagementArea); it.moreStands(); it.gotoNextStand()) {

        id = it.getCurrentStand();

//        standAge = stands(id)->getAge();   Modified by Vera

        standAge = (*pstands)(id)->getAge();



        freq[standAge/pCoresites->TimeStep_Harvest+1]++;

        if (standAge > maxStandAge) maxStandAge = standAge;

    }



    float cumulativeFreq = 0.;

    for (int age = itsRotationAge; age <= 320; age+=pCoresites->TimeStep_Harvest) {

        cumulativeFreq += (float)exp((float)(age/maxStandAge)*(float)abs(itsScaleFactor)) * freq[age/pCoresites->TimeStep_Harvest+1];

    }



    filter(theStandArray, theAgeArray, theLength);



    float p;

    for (int i = 1; i <= theLength; i++) {

        standAge = theAgeArray[i];

        p = (float)(exp((float)(standAge/maxStandAge)*(float)abs(itsScaleFactor)) * freq[standAge/pCoresites->TimeStep_Harvest+1]) / cumulativeFreq;

        assert(p>=0.);

        if (itsScaleFactor < 0) {

           printf("\n");

           printf("standAge = %d\n", standAge);

           printf("maxStandAge = %d\n", maxStandAge);

           printf("itsScaleFactor = %d\n", itsScaleFactor);

           printf("freq[standAge/%d+1] = %d\n", pCoresites->TimeStep_Harvest,freq[standAge/pCoresites->TimeStep_Harvest+1]);

           printf("cumulativeFreq = %lf\n", cumulativeFreq);

           printf("(float)sortKey = %lf, (int)sortKey = %d\n", p, (int) p);

        }

        theSortKeyArray[i] = (int) p;

    }



    descendingSort(theStandArray, theSortKeyArray, theLength);

    assign(theStandArray, theLength, theRankedList);

}



