#ifndef RELATIVEOLDESTRANK_H

#define RELATIVEOLDESTRANK_H



#include <stdio.h>

#include "site.h"

#include "IntArray.h"

#include "List.h"

#include "SiteRemovalMask.h"

#include "SiteHarvester.h"

#include "Stand.h"

#include "ManagementArea.h"

#include "StandRankingAlgorithm.h"



class RelativeOldestRank : public StandRankingAlgorithm {

public :

    RelativeOldestRank(int someManagementAreaId, int someRotationAge, SiteRemovalMask* someSiteRemovalMask);

    virtual ~RelativeOldestRank() {}



    void read(FILE* infile) {}

    void rankStands(List<int>& theRankedList);



private :

    int computeStandImportance(Stand* stand);

    float computeSiteImportance(SITE* site);



    SiteRemovalMask* itsRemovalMask;

};



#endif

