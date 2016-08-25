#ifndef GROUPSELECTIONREGIME_H

#define GROUPSELECTIONREGIME_H



#include <stdio.h>

#include "HarvestRegime.h"

#include "SiteRemovalMask.h"

#include "Stand.h"

#include "List.h"



class GroupSelectionRegime : public HarvestRegime {

public :

    GroupSelectionRegime();

    virtual ~GroupSelectionRegime();



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

    enum {START, ENTRYPENDING, ENTRYREADY, REENTRYPENDING, REENTRYREADY} itsState;

    int itsEntryDecade;

    int itsReentryInterval;

    int itsTargetCut;

    float itsStandProportion;

    float itsMeanGroupSize;

    float itsStandardDeviation;

    int itsTotalNumberOfStands;

    List<int> itsStands;

};



#endif



