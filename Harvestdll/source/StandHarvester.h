#ifndef STANDHARVESTER_H

#define STANDHARVESTER_H



#include "Stand.h"

#include "SiteHarvester.h"

#include "HarvestPath.h"



class StandHarvester {

public :

    StandHarvester();

    virtual ~StandHarvester() {}

    virtual int harvest() = 0;



    Stand* getStand();

    SiteHarvester* getSiteHarvester();

    HarvestPath* getPath();



protected :

    void setStand(Stand* stand);

    void setSiteHarvester(SiteHarvester* siteHarvester);

    void setPath(HarvestPath* path);



private :

    Stand* itsStand;

    SiteHarvester* itsSiteHarvester;

    HarvestPath* itsPath;

};



#endif

