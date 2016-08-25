#include "HarvestPath.h"

#include "point.h"

#include "HarvestPathIterator.h"



HarvestPathIterator::HarvestPathIterator(const HarvestPath& somePath) : it(somePath.itsPath) {}



/* inline */ int HarvestPathIterator::more() {

    return it.more();

}



/* inline */ LDPOINT HarvestPathIterator::current() {

    return it.current();

}



/* inline */ void HarvestPathIterator::advance() {

    it.advance();

}



