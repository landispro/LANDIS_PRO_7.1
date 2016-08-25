#ifndef OLDESTRANK_H

#define OLDESTRANK_H



#include <stdio.h>

#include "IntArray.h"

#include "List.h"

#include "SiteHarvester.h"

#include "ManagementArea.h"

#include "StandRankingAlgorithm.h"



class OldestRank : public StandRankingAlgorithm {

public :

    OldestRank(int someManagementAreaId, int someRotationAge) : StandRankingAlgorithm(someManagementAreaId, someRotationAge) {}

    virtual ~OldestRank() {}

    

    void read(FILE* infile) {}

    void rankStands(List<int>& theRankedList);

};



#endif

