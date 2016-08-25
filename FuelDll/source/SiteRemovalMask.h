#ifndef SITEREMOVALMASK_H

#define SITEREMOVALMASK_H



#include <stdio.h>

#include "CohortRemovalMask.h"



class SiteRemovalMask {

public :

    SiteRemovalMask();

    virtual ~SiteRemovalMask();

    void read(FILE* infile);

    void dump();

    CohortRemovalMask* operator()(int species);

private :

    SiteRemovalMask(const SiteRemovalMask&);

    SiteRemovalMask& SiteRemovalMask::operator=(const SiteRemovalMask&);

    CohortRemovalMask* mask;

    int numSpec;

};



#endif


