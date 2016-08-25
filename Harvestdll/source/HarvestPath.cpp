#include "point.h"

#include "HarvestPathIterator.h"

#include "HarvestPath.h"



HarvestPath::HarvestPath() {

    reset();

}



/* inline */ void HarvestPath::reset() {

    itsPath.reset();

}



/* inline */ void HarvestPath::append(const LDPOINT& pt) {

	printf("HarvestPath::append(const LDPOINT& pt),pt.x=%d, pt.y = %d",pt.x,pt.y);

    itsPath.append(pt);

}



void HarvestPath::addPath(HarvestPath& somePath) {

    LDPOINT pt;

    for (HarvestPathIterator it(somePath); it.more(); it.advance()) {

        pt = it.current();

        itsPath.append(pt);

    }

}



/* inline */ void HarvestPath::dump() {

    itsPath.dump();

}



