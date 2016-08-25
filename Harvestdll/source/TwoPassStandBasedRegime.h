#ifndef TWOPASSSTANDBASEDREGIME_H

#define TWOPASSSTANDBASEDREGIME_H



#include <stdio.h>

#include "List.h"

#include "HarvestRegime.h"

#include "SiteRemovalMask.h"

#include "Stand.h"

#include "HarvestPath.h"

#include "StandHarvester.h"



class TwoPassStandBasedRegime : public HarvestRegime {

public :

    TwoPassStandBasedRegime();

    virtual ~TwoPassStandBasedRegime();

    

    virtual int isA() = 0;

    int conditions();

    void harvest();



    virtual void read(FILE* infile) = 0;

    virtual void readCustomization1(FILE* infile) = 0;

    virtual void readCustomization2(FILE* infile) = 0;



protected :

    int isHarvestDone();

    virtual int harvestStand(Stand* stand) = 0;

    void reharvest();

    

    enum {START, ENTRYPENDING, ENTRYREADY, REENTRYPENDING, REENTRYREADY, DONE} itsState;

    int itsEntryDecade;

    int itsReentryDecade;

    SiteRemovalMask* itsReentryRemovalMask;

    int itsTargetCut;

    HarvestPath itsPath;

};



#endif

