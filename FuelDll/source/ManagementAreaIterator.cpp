#include "ManagementArea.h"

#include "ManagementAreaIterator.h"



ManagementAreaIterator::ManagementAreaIterator(ManagementArea& m) : it(m.itsStandList) {}



/* inline */ int ManagementAreaIterator::moreStands() {

    return it.more();

}



/* inline */ int ManagementAreaIterator::getCurrentStand() {

    return it.current();

}



/* inline */ void ManagementAreaIterator::gotoNextStand() {

    it.advance();

}





