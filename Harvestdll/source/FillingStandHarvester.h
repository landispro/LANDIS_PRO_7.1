#ifndef FILLINGSTANDHARVESTER_H

#define FILLINGSTANDHARVESTER_H



#include "StandHarvester.h"

#include "Stand.h"

#include "SiteHarvester.h"

#include "HarvestPath.h"



class FillingStandHarvester : public StandHarvester {

public :

    FillingStandHarvester(Stand* stand, SiteHarvester* siteHarvester, HarvestPath* path = 0);

    virtual ~FillingStandHarvester() {}

    virtual int harvest();

};



#endif

