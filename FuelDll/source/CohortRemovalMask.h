#ifndef COHORTREMOVALMASK_H

#define COHORTREMOVALMASK_H



#include <stdio.h>

#include "agelist.h"



class CohortRemovalMask {

public :

    CohortRemovalMask() {}

    virtual ~CohortRemovalMask() {}

    void read(FILE* infile);

    void dump();

    int query();

    int query(int n);

private :

    AGELIST mask;

};



#endif

