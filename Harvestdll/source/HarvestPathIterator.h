#ifndef HARVESTPATHITERATOR_H

#define HARVESTPATHITERATOR_H



#include "HarvestPath.h"

#include "point.h"

#include "List.h"



class HarvestPathIterator {

public :

    HarvestPathIterator(const HarvestPath& somePath);

    virtual ~HarvestPathIterator() {}

    int more();

    LDPOINT current();

    void advance();

private :

    ListIterator<LDPOINT> it;

};



#endif

