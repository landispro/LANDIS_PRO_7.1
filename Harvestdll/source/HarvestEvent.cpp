#include <string.h>

#include "HarvestEvent.h"



HarvestEvent::HarvestEvent() {

    itsLabel = 0;

    setLabel("none");

/* 22-OCT-99 */

    itsSequentialId = 0;

/* -- END -- */

}



HarvestEvent::~HarvestEvent() {

    delete [] itsLabel;

}



/* 22-OCT-99 */

void HarvestEvent::setSequentialId(int someId) {

	itsSequentialId = someId;

}



int HarvestEvent::getSequentialId() {

	return itsSequentialId;

}

void HarvestEvent::setUserInputId(int someId) {

	UserInputID_70 = someId;

}



int HarvestEvent::getUserInputId() {

	return UserInputID_70;

}

/* -- END -- */



void HarvestEvent::setLabel(const char* label) {

    delete [] itsLabel;

    itsLabel = new char[strlen(label)+1];

    strcpy(itsLabel, label);

}



/* inline */ const char* HarvestEvent::getLabel() {

    return itsLabel;

}



