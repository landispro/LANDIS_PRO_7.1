#ifndef RANDOMRANK_H

#define RANDOMRANK_H



#include <stdio.h>

#include "IntArray.h"

#include "List.h"

#include "SiteHarvester.h"

#include "ManagementArea.h"

#include "StandRankingAlgorithm.h"

#include "BoundedPocketStandHarvester.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"



class RandomRank : public StandRankingAlgorithm {

public :

    RandomRank(int someManagementAreaId, int someRotationAge) : StandRankingAlgorithm(someManagementAreaId, someRotationAge) {}

    virtual ~RandomRank() {}

    

    void read(FILE* infile) {}

    void rankStands(List<int>& theRankedList);

};



#endif

