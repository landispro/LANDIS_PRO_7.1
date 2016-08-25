#include "SiteHarvester.h"

#include "StandHarvester.h"



StandHarvester::StandHarvester() {

    itsStand = 0;

    itsSiteHarvester = 0;

    itsPath = 0;

}



/* inline */ void StandHarvester::setStand(Stand* stand) {

    itsStand = stand;

}



/* inline */ void StandHarvester::setSiteHarvester(SiteHarvester* siteHarvester) {

    itsSiteHarvester = siteHarvester;

}



/* inline */ void StandHarvester::setPath(HarvestPath* path) {

    itsPath = path;

}



/* inline */ Stand* StandHarvester::getStand() {

    return itsStand;

}



/* inline */ SiteHarvester* StandHarvester::getSiteHarvester() {

    return itsSiteHarvester;

}



/* inline */ HarvestPath* StandHarvester::getPath() {

	//printf("StandHarvester::getPath(),itsPath = %d \n", itsPath);
	//fflush(stdout);
    
	return itsPath;

}



