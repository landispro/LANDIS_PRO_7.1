#ifndef PERIODICTWOPASSSTANDFILLINGREGIME_H

#define PERIODICTWOPASSSTANDFILLINGREGIME_H



#include <stdio.h>

#include "List.h"

#include "HarvestRegime.h"

#include "SiteRemovalMask.h"

#include "Stand.h"

#include "HarvestPath.h"

#include "StandHarvester.h"

#include "PeriodicTwoPassStandFillingRegime.h"



class PeriodicTwoPassStandFillingRegime : public HarvestRegime {

public :

    PeriodicTwoPassStandFillingRegime();

    virtual ~PeriodicTwoPassStandFillingRegime();

    

    int isA();

    int conditions();

    void harvest();

    void read(FILE* infile);

    

protected :

    void readCustomization1(FILE* infile);

    void readCustomization2(FILE* infile);

    

    int isHarvestDone();

    int harvestStand(Stand* stand);

    

    void reharvestUsingRemovalMask1();

    void reharvestUsingRemovalMask2();



private :    

    enum {START, INITIALENTRYPENDING, INITIALENTRYREADY, ENTRYPENDING, ENTRYREADY, 

          REENTRYPENDING, REENTRYREADY, DONE} itsState;

    int itsEntryDecade;

    int itsReentryDecade;

    int itsReturnInterval;

    SiteRemovalMask* itsReentryRemovalMask;

    int itsTargetCut;

    HarvestPath itsPath;

};



#endif



