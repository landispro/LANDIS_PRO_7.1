#ifndef REPEATINGTWOPASSSTANDFILLINGREGIME_H

#define REPEATINGTWOPASSSTANDFILLINGREGIME_H



#include <stdio.h>

#include "List.h"

#include "HarvestRegime.h"

#include "SiteRemovalMask.h"

#include "Stand.h"

#include "HarvestPath.h"

#include "StandHarvester.h"

#include "RepeatingTwoPassStandFillingRegime.h"



class RepeatingTwoPassStandFillingRegime : public HarvestRegime {

public :

    RepeatingTwoPassStandFillingRegime();

    virtual ~RepeatingTwoPassStandFillingRegime();

    

    int isA();

    int conditions();

    void harvest();

    void read(FILE* infile);

    

protected :

    void readCustomization1(FILE* infile);

    void readCustomization2(FILE* infile);

    

    int isHarvestDone();

    int harvestStand(Stand* stand);

    

    void reharvest();



private :    

    enum {START, ENTRYPENDING, ENTRYREADY, 

          REENTRYPENDING, REENTRYREADY, DONE} itsState;

    int itsEntryDecade;

    int itsReentryDecade;

    int itsReturnInterval;

    SiteRemovalMask* itsReentryRemovalMask;

    int itsTargetCut;

    HarvestPath itsPath;

};



#endif



