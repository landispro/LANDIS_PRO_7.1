#include <assert.h>

#include "point.h"

#include "system1.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

//#include "landis.h"

#include "ManagementArea.h"



ManagementArea::ManagementArea() {

    itsId = 0;

    itsTotalSites = 0;

    itsActiveSites = 0;

    itsUpdateFlag = 1;

}



/* inline */ void ManagementArea::setUpdateFlag() {

    itsUpdateFlag = 1;

}



/* inline */ int ManagementArea::getId() {

    return itsId;

}



/* inline */ int ManagementArea::inManagementArea(int r, int c) {

	//<Add By Qia on Nov 3 2008>

	int tempMid=0,sid;

	

	sid = standMap.getvalue32out(r,c);//change by Qia on Nov 4 2008

	if(sid>0)

	tempMid=(*pstands)(sid)->getManagementAreaId();

	

	int result = (managementAreaMap.inMap(r,c) && tempMid == itsId);

	

	//</Add By Qia on Nov 3 2008>

	//<Landis 4.0 changed By Qia on Nov 3 2008>

    //int result = (managementAreaMap.inMap(r,c) && managementAreaMap(r,c) == itsId);

	//</Landis 4.0 Changed By Qia on Nov 3 2008>

	return result;

}



/* inline */ int ManagementArea::inManagementArea(LDPOINT p) {

    return inManagementArea(p.y, p.x);

}



/* inline */ int ManagementArea::numberOfSites() {

    return itsTotalSites;

}



/* inline */ int ManagementArea::numberOfActiveSites() {

    return itsActiveSites;

}



int ManagementArea::numberOfStands() {

    return itsStandList.length();

}



void ManagementArea::update() {

    if (itsUpdateFlag) {

        itsUpdateFlag = 0;

    }

}



void ManagementArea::addStand(int id) {

    if (!itsStandList.isMember(id))

        itsStandList.append(id);

}



