#ifndef BOUNDEDPOCKETSTANDHARVESTER_H

#define BOUNDEDPOCKETSTANDHARVESTER_H



#include "StandHarvester.h"

#include "point.h"

#include "SiteHarvester.h"

#include "HarvestPath.h"

#include "Stand.h"

#include "List.h"

//#include <vld.h>

class BoundedPocketStandHarvester : public StandHarvester {

public :

    BoundedPocketStandHarvester(int targetCut, LDPOINT startPoint, SiteHarvester* siteHarvester, HarvestPath* path = 0);

    virtual ~BoundedPocketStandHarvester() {}

    virtual int harvest();

	int harvest_EVENT_GROUP_SELECTION_REGIME_70(LDPOINT pt);

	int EVENT_GROUP_SELECTION_REGIME_70_clear_cut(int, int);

private :

    void addSiteNeighbor(int r, int c);



    int itsTargetCut;

    LDPOINT itsStartPoint;

    List<LDPOINT> itsNeighborList;

};



#endif

