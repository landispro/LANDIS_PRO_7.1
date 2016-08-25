#ifndef RANKBYSTOCKING_H

#define RANKBYSTOCKING_H

//add by Qia on Sep 01 2009

#include <stdio.h>

#include "IntArray.h"

#include "List.h"

#include "SiteHarvester.h"

#include "ManagementArea.h"

#include "StandRankingAlgorithm.h"



class RankbyStocking : public StandRankingAlgorithm {

public :

    RankbyStocking(int someManagementAreaId, int someRotationAge) : StandRankingAlgorithm(someManagementAreaId, someRotationAge) {}

    virtual ~RankbyStocking() {}

    double computeStandStocking(Stand* stand);

    void read(FILE* infile) {}

    void rankStands(List<int>& theRankedList);


};



#endif



