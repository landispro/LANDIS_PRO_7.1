#ifndef PERIODICSTANDFILLINGREGIME_H

#define PERIODICSTANDFILLINGREGIME_H



#include <stdio.h>

#include "HarvestRegime.h"

#include "SiteRemovalMask.h"

#include "Stand.h"



class PeriodicStandFillingRegime : public HarvestRegime {

public :

    PeriodicStandFillingRegime();

    virtual ~PeriodicStandFillingRegime();



    virtual int isA();

    virtual int conditions();

    virtual void harvest();

    virtual void read(FILE* infile);



protected :

    void readCustomization1(FILE* infile);

    void readCustomization2(FILE* infile);



    int isHarvestDone();

    int harvestStand(Stand* stand);



private:

    enum {START, ENTRYPENDING, ENTRYREADY, DONE} itsState;

    int itsEntryDecade;

    int itsFinalDecade;

    int itsReentryInterval;

    int itsTargetCut;

};



#endif



