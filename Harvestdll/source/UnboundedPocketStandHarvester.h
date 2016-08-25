#ifndef UNBOUNDEDPOCKETSTANDHARVESTER_H

#define UNBOUNDEDPOCKETSTANDHARVESTER_H



#include "StandHarvester.h"

#include "point.h"

#include "SiteHarvester.h"

#include "HarvestPath.h"

#include "Stand.h"

#include "List.h"



class UnboundedPocketStandHarvester : public StandHarvester {

public :

    UnboundedPocketStandHarvester(int targetCut, LDPOINT startPoint, SiteHarvester* siteHarvester, HarvestPath* path = 0);

    virtual ~UnboundedPocketStandHarvester() {}

    virtual int harvest();



private :

    void rankNeighborSite(int r, int c, int& bestRank, LDPOINT& bestSite);



    int itsTargetCut;

    LDPOINT itsStartPoint;

    List<LDPOINT> itsNeighborList;

};



#endif

