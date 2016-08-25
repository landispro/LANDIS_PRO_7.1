#ifndef HARVESTREPORT_H

#define HARVESTREPORT_H



#include "IntArray.h"



class HarvestReport {

public :

    HarvestReport();

    virtual ~HarvestReport() {}

    void reset();

    void incrementSiteCount();

    void addToSpeciesTotal(int speciesIndex, int value);

    int numberOfSitesCut();

    int sumOfCohortsCut();

    int sumOfCohortsCut(int speciesIndex);

    void addReport(HarvestReport& someReport);

private :

    int count;

    IntArray sumBySpecies;

};



#endif

