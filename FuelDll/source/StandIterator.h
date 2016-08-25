#ifndef STANDITERATOR_H

#define STANDITERATOR_H



#include "FUELStand.h"

#include "point.h"



class StandIterator {

public :

    StandIterator(FUELStand& s);

    StandIterator(StandIterator& it);

    StandIterator(FUELStand& s, LDPOINT pt);

    virtual ~StandIterator() {}

    int moreSites();

    LDPOINT getCurrentSite();

    void gotoNextSite();

private :

    void advance();

    FUELStand& stand;

    LDPOINT p;

};



#endif



