#ifndef HARVESTREGIME_H

#define HARVESTREGIME_H



#include <stdio.h>

#include "HarvestEvent.h"

#include "IntArray.h"

#include "Stand.h"

#include "SiteHarvester.h"

#include "HarvestReport.h"

#include "StandRankingAlgorithm.h"



class HarvestRegime : public HarvestEvent {

public :

    HarvestRegime();

    virtual ~HarvestRegime();



    virtual int isA() = 0;

    virtual int conditions() = 0;

    virtual void harvest() = 0;

    virtual void read(FILE* infile) = 0;



    int getManagementAreaId();

    int getRotationAge();

    SiteRemovalMask* getRemovalMask();

    StandRankingAlgorithm* getRankAlgorithm();

    int getDuration();

    HarvestReport* getReport();



	/* begin: added by Vera*/

//	STANDS*					pstands;

	/* end:  added by Vera*/



protected :

    void setDuration(int duration);



    virtual void readCustomization1(FILE* infile) = 0;

    virtual void readCustomization2(FILE* infile) = 0;

    

    virtual int isHarvestDone() = 0;

    virtual int harvestStand(Stand* stand) = 0;

    virtual void writeReport(FILE* outfile);



private :

    int itsManagementAreaId;

    int itsRotationAge;

    SiteRemovalMask* itsRemovalMask;

    StandRankingAlgorithm* itsRankAlgorithm;

    int itsDuration;

    HarvestReport* itsReport;

};



#endif



