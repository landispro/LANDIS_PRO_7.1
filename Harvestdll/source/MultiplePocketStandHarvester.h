#ifndef MULTIPLEPOCKETSTANDHARVESTER_H

#define MULTIPLEPOCKETSTANDHARVESTER_H



#include "point.h"

#include "SiteHarvester.h"

#include "StandHarvester.h"

#include "Stand.h"



class MultiplePocketStandHarvester : public StandHarvester {

public :

    MultiplePocketStandHarvester(Stand* stand, float proportion, float meanGroupSize, float standardDeviation,

      SiteHarvester* siteHarvester);

    virtual ~MultiplePocketStandHarvester() {}

    virtual int harvest();



private :

    int getRandomStartPoint(LDPOINT& startPoint);

    int isValidStartPoint(LDPOINT pt);

    int getRandomGroupSize();



    float itsProportion;

    float itsMeanGroupSize;

    float itsStandardDeviation;

    int itsTargetCut;

};



#endif

