#include <assert.h>

#include "point.h"

#include "site.h"

#include "system1.h"

//#include "GlobalVariables.h"

//#include "GlobalFunctions.h"

#include "StandIterator.h"

#include "FuelStand.h"

#include "error.h"

#include "FuelGlobalVariables.h"





FUELStand::FUELStand() 

{

    itsId = 0;

    itsManagementAreaId = 0;

    itsTotalSites = 0;

    itsActiveSites = 0;

    itsHarvestableSites = 0;

    itsMeanAge = 0;

    itsUpdateFlag = 1;

    itsRecentHarvestFlag = 0;

    itsRank = 0;

    itsReserveFlag = 0;

//	#ifdef _FUELMAN_

	itMeanFireRisk = 0;

	itMeanFireProbability = 0;

	itMeanFireProbabilityClass = 0;

	itMeanFireIntensity = 0;

	itMeanFineFuel = 0;

	itMeanCoarseFuel = 0;



	itsUpdateFireRiskFlag = 1;

	itsFuelTreatmentSites = 0;

//	#endif

}



FUELStand::~FUELStand()

{



}



/**

  * sets the variable itsUpdateFlag = 1

  *

  * @return void 

  */

/* inline */ void FUELStand::setUpdateFlag() {

    itsUpdateFlag = 1;

}



//#ifdef _FUELMAN_

float FUELStand::getMeanFireRisk () {

//	if(parameters.fuel && parameters.fuelManagement && itsUpdateFireRiskFlag)	

	if (gDLLMode & G_FUEL && itsUpdateFireRiskFlag)  //need to further change 

		fireRisk ();

	return itMeanFireRisk;

}

//#endif





 /**

  * returns the variable itsId

  *

  * @return int 

  */



/* inline */ int FUELStand::getId() {

    return itsId;

}





 /**

  * returns the variable itsManagementAreaId

  *

  * @return int 

  */



/* inline */ int FUELStand::FuelgetManagementAreaId() {

    return itsManagementAreaId;

}





 /**

  * returns the variable itsMinPoint

  *

  * @return POINT 

  */



/* inline */ LDPOINT FUELStand::getMinPoint() {

    return itsMinPoint;

}



/**

  * returns the variable itsMaxPoint

  *

  * @return POINT 

  */



/* inline */ LDPOINT FUELStand::getMaxPoint() {

    return itsMaxPoint;

}



/**

  * sets the variable itsRank = rank

  *

  * @param rank 

  * @return void 

  */



/* inline */ void FUELStand::setRank(int rank) {

    itsRank = rank;

}





 /**

  * returns the variable itsRank

  *

  * @return int 

  */



/* inline */ int FUELStand::getRank() {

    return itsRank;

}





 /**

  *  sets the variable itsReserveFlag = 1

  *

  * @return void 

  */



/* inline */ void FUELStand::reserve() {

    itsReserveFlag = 1;

}





 /**

  *  sets the variable itsReserveFlag = 0

  *

  * @return void 

  */



/* inline */ void FUELStand::unreserve() {

    itsReserveFlag = 0;

}





 /**

  * returns the variable itsReserveFlag

  *

  * @return int 

  */



/* inline */ int FUELStand::isReserved() {

    return itsReserveFlag;

}



/**

  * returns the variable itsMeanAge

  * calls the update() method first

  * see definition of itsMeanAge

  *

  * @return int 

  */



/* inline */ int FUELStand::getAge() {

    update();

    return itsMeanAge;

}



/**

  * returns whether or not the stand can be havested

  * calls the update() function before making the decision

  *

  * @return int // 1 if true and 0 if false

  */



/* inline */ int FUELStand::canBeHarvested() {

    update();

    return !isReserved() && (itsHarvestableSites > 0);

	// for poster

	//	return 1;

}





 /**

  * lets know if the stand has been harvested in the last 10 years

  * calls the update() function before making the decision

  * based on a calculation involving the number of active sites, the number of sites

  * harvested on the stand already and the harvest threshold set in the harvest prescription

  *

  * @return int // 1 if true and 0 if false

  */



/* inline */ int FUELStand::wasRecentlyHarvested() {

    update();

    return itsRecentHarvestFlag;

}



/**

 * checks out itsNeighborList to see if any have been harvested or not

 *

 * @return int // 1 if true and 0 if false

 */



int FUELStand::neighborsWereRecentlyHarvested() {

    int id;

    for (ListIterator<int> it(itsNeighborList); it.more(); it.advance()) {

        id = it.current();

        if ((*fuelpstands)(id)->wasRecentlyHarvested())

            return 1;

    }

    return 0;

}





 /**

  * checks to see if the site is in the stand or not

  *

  * @param r    // row coordinate in the map

  * @param c    // column coordinate in the map

  * @return int // 1 if true and 0 if false

  */



/* inline */ int FUELStand::inStand(int r, int c) {

	//<Add By Qia on Nov 20 2008>

	int sid,tempMid=0;

	

	sid=standMap.getvalue32out(r,c);//change by Qia on Nov 4 2008

	if(sid>0)

	tempMid=(*fuelpstands)(sid)->FuelgetManagementAreaId();

	int result = (standMap.inMap(r,c) && standMap.getvalue32out(r,c) == itsId && tempMid == itsManagementAreaId);//change by Qia on Nov 4 2008

	//</Add By Qia on Nov 20 2008>

	//<Changed By Qia on Nov 20 2008>

    //int result = (standMap.inMap(r,c) && standMap.getvalue32out(r,c) == itsId && managementAreaMap(r,c) == itsManagementAreaId);//changed BY Qia on Nov 4 2008

    //</Changed By Qia on Nov 20 2008>

    return result;

}



/**

  * returns the value in the variable itsTotalSites

  *

  * @return int 

  */

/* inline */ int FUELStand::numberOfSites() {

    return itsTotalSites;

}





 /**

  * returns the value in the variable itsActiveSites

  *

  * @return int 

  */



/* inline */ int FUELStand::numberOfActiveSites() {

    return itsActiveSites;

}





/**

 * will pick out a random POINT in that stand

 * the point is an x,y location on the stand map 

 * I beleive the use of points is reduce the overhead of passing around the whole site object

 * but you could have use a pointer.

 *

 * @return POINT 

 */



LDPOINT FUELStand::getRandomPoint() {

    LDPOINT pt;

    do {

        pt.x = irand(itsMinPoint.x, itsMaxPoint.x);

        pt.y = irand(itsMinPoint.y, itsMaxPoint.y);

    } while (!inStand(pt.y,pt.x));

    return pt;

}



/**

 * This will update the information about a stand

 * It will update the mean age of the site.

 * It will also make the decision if the stand has had

 * enough sites harvested to consider the the site 

 * harvested or not

 *

 * @return void 

 */



void FUELStand::update() {

/*    LDPOINT pt;

    SITE* site;



    if (itsUpdateFlag) {

        if (itsActiveSites == 0) {

            itsMeanAge = 0;

            itsHarvestableSites = 0;

            itsRecentHarvestFlag = 0;

        } else {

            int sum = 0;

            int rcount = 0;

            itsHarvestableSites = 0;

            for (StandIterator it(*this); it.moreSites(); it.gotoNextSite()) {

                pt = it.getCurrentSite();

                site = (*pfuelcoresites)(pt.y,pt.x);

                if (site->landUnit->active()) {

                    sum += site->getMaxAge();

                    if (standMap(pt.y,pt.x) > 0 && site->canBeHarvested())

                        itsHarvestableSites++;

                    if (site->wasRecentlyHarvested())

                        rcount++;

                }

            }

            itsMeanAge = sum / itsActiveSites;

			//printf("itsMeanAge %f \n", itsMeanAge);

            if ((float) rcount / itsActiveSites < harvestThreshold)

                itsRecentHarvestFlag = 0;

            else

                itsRecentHarvestFlag = 1;

			//printf("itsRecentHarvestFlag %d \n", itsRecentHarvestFlag);

        }

        itsUpdateFlag = 0;

    }*/

}



//#ifdef _FUELMAN_

// Calculate stand mean fire risk

void FUELStand::fireRisk() {

    LDPOINT pt;

    //SITE* site; //commented By Qia on Nov 17 2008



	int sum = 0;

	itMeanFireProbability = 0;

	itMeanFireProbabilityClass = 0;

	itMeanFireIntensity = 0;

	itMeanFineFuel = 0;

	itMeanCoarseFuel = 0;

	//itsActiveSites = 0;

	int fRisk = 0, fProb = 0, fInten = 0, ffload = 0, cfload = 0;

	float fProbability = 0;

	itsFuelTreatmentSites = 0;

		

	for (StandIterator it(*this); it.moreSites(); it.gotoNextSite()) {

		pt = it.getCurrentSite();

		//site = (*pfuelcoresites)(pt.y,pt.x); //commented By Qia on Nov 17 2008

		if (pfuelcoresites->locateLanduPt(pt.y,pt.x)->active()) { //Original landis4.0: site->landUnit->active()

																//changed By Qia Oct 13 2008

			/*

			printf("FF: %d  CF %d  FP: %d  FI: %d FR %d  FP %f \n", fuelsites(pt.y, pt.x)->FFLoad,

				fuelsites(pt.y, pt.x)->CFLoad, fuelsites(pt.y, pt.x)->fireProbility,

				fuelsites(pt.y, pt.x)->fireSeverity, fuelsites(pt.y, pt.x)->fireRisk,

				fuelsites(pt.y, pt.x)->potentialFireProbility);

			*/

			// Shang 03/04

			//fRisk = (int) fuelsites(pt.y, pt.x)->fireRisk;

			fRisk = (int) fuelsites.getFireRiskClass (pt.y, pt.x);

			//printf("%d \n", fRisk);

			if (fRisk>=0)       sum += fRisk;



			// Shang 03/04

			//fProb = (int) fuelsites(pt.y, pt.x)->fireProbility;

			fProb = (int) fuelsites.getFireProbabiltyClass (pt.y, pt.x);

			if (fProb>=0)	itMeanFireProbabilityClass += fProb;



			//fInten = (int) fuelsites(pt.y, pt.x)->fireSeverity;

			// Shang 03/04

			//fInten = (int) fuelsites(pt.y, pt.x)->fireIntensity;

			fInten = (int) fuelsites.getFireIntensityClass (pt.y, pt.x);

			if(fInten>=0)	itMeanFireIntensity+= fInten;



			// Shang 03/04

			//ffload = (int) fuelsites(pt.y, pt.x)->FFLoad;

			ffload = fuelsites.getFFLoad(pt.y, pt.x);

			if(ffload>=0)	itMeanFineFuel+=ffload;

			

			//cfload = (int) fuelsites(pt.y, pt.x)->CFLoad;

			cfload = fuelsites.getCFLoad(pt.y, pt.x);

			if(cfload>=0)	itMeanCoarseFuel+=cfload;



			// Shang 03/04

			//fProbability = fuelsites(pt.y, pt.x)->potentialFireProbility;

			fProbability = fuelsites.getFireProbabiltyClass (pt.y, pt.x);

			if(fProbability>=0)	itMeanFireProbability+=fProbability;

			

            itsFuelTreatmentSites ++;

        }

	}

    if(itsFuelTreatmentSites>0) {

		itMeanFireRisk = (float) sum / (float) itsFuelTreatmentSites;

		itMeanFireProbability = itMeanFireProbability / (float) itsFuelTreatmentSites;

		itMeanFireProbabilityClass = itMeanFireProbabilityClass / (float) itsFuelTreatmentSites;

		itMeanFireIntensity = itMeanFireIntensity / (float) itsFuelTreatmentSites;

		itMeanFineFuel = itMeanFineFuel / (float) itsFuelTreatmentSites;

		itMeanCoarseFuel = itMeanCoarseFuel / (float) itsFuelTreatmentSites;

	}

	else {

		itMeanFireRisk = 0;

		itMeanFireProbability = 0;

		itMeanFireProbabilityClass = 0;

		itMeanFireIntensity = 0;

		itMeanFineFuel = 0;

		itMeanCoarseFuel = 0;

	}

	

	// Finish update fire risk

	itsUpdateFireRiskFlag = 0;

}



//#endif



/**

 * Checks to see if the site is a neighbor or not.

 * a neighbor is a site in a different stand.

 *

 * @param r     // the row coordiante on the stand map

 * @param c     // the column coordiante on the stand map

 * @return int  // 0 if not a neighbor and the stand number if different then the current stand

 */



int FUELStand::isNeighbor(int r, int c) {

    int nid;

    if (!pfuelcoresites->inBounds(r,c))

        return 0;

    if ((nid = standMap.getvalue32out(r,c)) <= 0 || nid == itsId) //changed By Qia on Nov 4 2008

        return 0;

    else

        return nid;

}





 /**

  * add the stand id to the list of neighbors

  *

  * @param id       // the stand id of the neighbor

  * @return void 

  */



/* inline */ void FUELStand::addNeighbor(int id) {

    if (!itsNeighborList.isMember(id))

        itsNeighborList.append(id);

}



