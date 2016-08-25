#ifndef ONEPASSSTANDBASEDREGIME

#define ONEPASSSTANDBASEDREGIME



#include <stdio.h>

#include "Stand.h"

#include "HarvestRegime.h"

#include "SiteRemovalMask.h"



class OnePassStandBasedRegime : public HarvestRegime {

public :

    OnePassStandBasedRegime();

    virtual ~OnePassStandBasedRegime();

    

    virtual int isA() = 0;

    int conditions();

    void harvest();



    virtual void read(FILE* infile) = 0;

    virtual void readCustomization1(FILE* infile) = 0;

    virtual void readCustomization2(FILE* infile) = 0;



protected :

    int isHarvestDone();

    virtual int harvestStand(Stand* stand) = 0;



    enum {START, ENTRYPENDING, ENTRYREADY, DONE} itsState;

    int itsEntryDecade;

    int itsTargetCut;



};



#endif

