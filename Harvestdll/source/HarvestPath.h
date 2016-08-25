#ifndef HARVESTPATH_H

#define HARVESTPATH_H



#include "point.h"

#include "List.h"



class HarvestPathIterator;



class HarvestPath {

public :

    HarvestPath();

    virtual ~HarvestPath() {}

    void reset();

    void append(const LDPOINT& pt);

    void addPath(HarvestPath& somePath);

    void dump();

    friend class HarvestPathIterator;

private :

    List<LDPOINT> itsPath;

};



#endif



