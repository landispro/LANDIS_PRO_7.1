#ifndef SITEHARVESTER_H

#define SITEHARVESTER_H



#include "point.h"

#include "site.h"

#include "SiteRemovalMask.h"

#include "HarvestReport.h"

#include "agelist.h"

#include "CohortRemovalMask.h"



#include "stands.h"



class SiteHarvester {

public :

    SiteHarvester(int harvestType, SiteRemovalMask* someRemovalMask, HarvestReport* someReport, int someDuration = 1);

    virtual ~SiteHarvester() {}



    int getHarvestType();

    SiteRemovalMask* getRemovalMask();

    HarvestReport* getReport();

    int getDuration();

    

    int harvest(const LDPOINT& pt);



	/* begin: added by Vera*/

	STANDS*					pstands;

	/* end:  added by Vera*/

protected :

    int harvestCohorts(AGELIST* cohorts, CohortRemovalMask* mask);



    int itsHarvestType;

    SiteRemovalMask* itsRemovalMask;

    HarvestReport* itsReport;

    int itsDuration;

};



#endif

