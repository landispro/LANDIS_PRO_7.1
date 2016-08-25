#ifndef RANKBYVOLUME_H

#define RANKBYVOLUME_H

//add by Qia on Sep 01 2009

#include <stdio.h>

#include "IntArray.h"

#include "List.h"

#include "SiteHarvester.h"

#include "ManagementArea.h"

#include "StandRankingAlgorithm.h"



class RankbyVolume : public StandRankingAlgorithm {

public :

    RankbyVolume(int someManagementAreaId, int someRotationAge) : StandRankingAlgorithm(someManagementAreaId, someRotationAge) {}

    virtual ~RankbyVolume() {}

    double computeStandBA(Stand* stand);

    void read(FILE* infile) {}

    void rankStands(List<int>& theRankedList);

};



#endif



