#include <assert.h>

#include "FuelStand.h"

#include "point.h"

#include "StandIterator.h"



void StandIterator::advance() {  

    if (++p.x > stand.itsMaxPoint.x) {

	     p.y++;

	     p.x = stand.itsMinPoint.x;

    }

}



StandIterator::StandIterator(FUELStand& s) : stand(s), p(s.itsMinPoint) {

    assert(s.itsMinPoint.x > 0 && s.itsMinPoint.y > 0);

    while (moreSites() && !stand.inStand(p.y,p.x)) advance();

}



StandIterator::StandIterator(StandIterator& it) : stand(it.stand), p(it.p) {}



StandIterator::StandIterator(FUELStand& s, LDPOINT pt) : stand(s), p(pt) {

    assert(s.inStand(p.y,p.x));

}



/* inline */ int StandIterator::moreSites() {

    return (p.y <= stand.itsMaxPoint.y);

}



/* inline */ LDPOINT StandIterator::getCurrentSite() {

    assert(moreSites());

    return p;

}



/* inline */ void StandIterator::gotoNextSite() {

    advance();

    while (moreSites() && !stand.inStand(p.y,p.x)) advance();

}





