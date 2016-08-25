#ifndef REGULATEDISTRIBUTIONRANK_H

#define REGULATEDISTRIBUTIONRANK_H



#include <stdio.h>

#include "IntArray.h"

#include "List.h"

#include "SiteHarvester.h"

#include "ManagementArea.h"

#include "StandRankingAlgorithm.h"



class RegulateDistributionRank : public StandRankingAlgorithm {

public :

    RegulateDistributionRank(int someManagementAreaId, int someRotationAge) : StandRankingAlgorithm(someManagementAreaId, someRotationAge) {}

    virtual ~RegulateDistributionRank() {}

    

    void read(FILE* infile);

    void rankStands(List<int>& theRankedList);

    

private :

    int itsScaleFactor;

};



#endif

