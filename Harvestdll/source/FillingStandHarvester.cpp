#include <assert.h>

#include "GlobalFunctions.h"

#include "Stand.h"

#include "SiteHarvester.h"

#include "point.h"

#include "StandIterator.h"

#include "HarvestPath.h"

#include "FillingStandHarvester.h"



FillingStandHarvester::FillingStandHarvester(Stand* stand, SiteHarvester* siteHarvester, HarvestPath* path) {

    assert(stand);

    assert(siteHarvester);

    setStand(stand);

    setSiteHarvester(siteHarvester);

    setPath(path);

}



int FillingStandHarvester::harvest() {



    LDPOINT pt;

    int sumCut = 0;



    for (StandIterator it(*getStand()); it.moreSites(); it.gotoNextSite()) {

        pt = it.getCurrentSite();

        if (canBeHarvested(pt)) {

            sumCut += getSiteHarvester()->harvest(pt);

            if (getPath()) getPath()->append(pt);

        }

    }

    return sumCut;

}



