#ifndef ECONOMICIMPORTANCERANK_H

#define ECONOMICIMPORTANCERANK_H



#include <stdio.h>

#include "site.h"

#include "IntArray.h"

#include "List.h"

#include "SiteRemovalMask.h"

#include "SiteHarvester.h"

#include "Stand.h"

#include "ManagementArea.h"

#include "StandRankingAlgorithm.h"

#include "Stands.h"





class EconomicImportanceRank : public StandRankingAlgorithm {

public :

    EconomicImportanceRank(int someManagementAreaId, int someRotationAge, SiteRemovalMask* someSiteRemovalMask);

    virtual ~EconomicImportanceRank() {}



    void read(FILE* infile);

    void rankStands(List<int>& theRankedList);



private :

    int computeStandImportance(Stand* stand);

    int computeSiteImportance(SITE* site);



    SiteRemovalMask* itsRemovalMask;

    IntArray itsDollarValuePerTon;

    IntArray itsMaturity;



};



#endif

