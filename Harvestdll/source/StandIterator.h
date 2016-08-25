#ifndef STANDITERATOR_H

#define STANDITERATOR_H



#include "Stand.h"

#include "point.h"



class StandIterator {

public :

    StandIterator(Stand& s);

    StandIterator(StandIterator& it);

    StandIterator(Stand& s, LDPOINT pt);

    virtual ~StandIterator() {}

    int moreSites();

    LDPOINT getCurrentSite();

    void gotoNextSite();

private :

    void advance();

    Stand& stand;

    LDPOINT p;

};



#endif



