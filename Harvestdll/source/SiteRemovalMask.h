//last modified by We Li august 27, 2004



#ifndef SITEREMOVALMASK_H

#define SITEREMOVALMASK_H



#include <stdio.h>

#include "IntArray.h"

#include "CohortRemovalMask.h"

//by wei li



//by wei li



class SiteRemovalMask {

public :

    SiteRemovalMask();

    virtual ~SiteRemovalMask();

    void read(FILE* infile);

    void dump();

    CohortRemovalMask* operator()(int species);

	//by wei li

	int plantingCode(int species);

	//by wei li

private :

    SiteRemovalMask(const SiteRemovalMask&);

    SiteRemovalMask& SiteRemovalMask::operator=(const SiteRemovalMask&);

    CohortRemovalMask* mask;

	IntArray itsPlantingCode;

    int numSpec;

};



#endif

