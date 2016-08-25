#include <assert.h>

#include "point.h"

#include "site.h"

#include "system1.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "StandIterator.h"

//#include "landis.h"

#include "Stand.h"

#include "error.h"

Stand::Stand() {

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

}



/* inline */ void Stand::setUpdateFlag() {

    itsUpdateFlag = 1;

}



/* inline */ int Stand::getId() {

    return itsId;

}



/* inline */ int Stand::getManagementAreaId() {

    return itsManagementAreaId;

}



/* inline */ LDPOINT Stand::getMinPoint() {

    return itsMinPoint;

}



/* inline */ LDPOINT Stand::getMaxPoint() {

    return itsMaxPoint;

}



/* inline */ void Stand::setRank(int rank) {

    itsRank = rank;

}



/* inline */ int Stand::getRank() {

    return itsRank;

}



/* inline */ void Stand::reserve() {

    itsReserveFlag = 1;

}



/* inline */ void Stand::unreserve() {

    itsReserveFlag = 0;

}



/* inline */ int Stand::isReserved() {

    return itsReserveFlag;

}



/* inline */ int Stand::getAge() {
	//cerr << "int Stand::getAge() " << endl;

    update();

    return itsMeanAge;

}



/* inline */ int Stand::canBeHarvested() {

	//cerr << "int Stand::canBeHarvested() " << endl;
    update();

    return itsHarvestableSites > 0;
	// Jacob return !isReserved() && (itsHarvestableSites > 0);
}



/* inline */ int Stand::wasRecentlyHarvested() {

    update();

    return itsRecentHarvestFlag;

}



int Stand::neighborsWereRecentlyHarvested() {

	//cerr << "Stand::neighborsWereRecentlyHarvested()" << endl;

    int id;

    for (ListIterator<int> it(itsNeighborList); it.more(); it.advance()) {

        id = it.current();

//      if (stands(id)->wasRecentlyHarvested())  Modified by Vera

		if ((*pstands)(id)->wasRecentlyHarvested())

            return 1;

    }

    return 0;

}

//<Add By Qia on August 03 2009>

long Stand::ComputeStandVolume()

{

	int id,i,j;

	LDPOINT pt;

    SITE* sitetmp;

	long StandVolume=0;
	LANDUNIT *l;
    for (StandIterator it(*this); it.moreSites(); it.gotoNextSite()) {

        pt = it.getCurrentSite();

		sitetmp = (*pCoresites)(pt.y,pt.x);
		l=pCoresites->locateLanduPt(pt.y,pt.x);
		for(i=1;i<=pCoresites->specNum;i++)

			{

			for(j=1;j<=sitetmp->specAtt(i)->longevity/pCoresites->TimeStep;j++)

				{

					if(pCoresites->GetGrowthRates(i,j,l->ltID)>18.6)

					{

						StandVolume+=sitetmp->SpecieIndex(i)->getTreeNum(j,i)*pCoresites->GetVolume(i,j, l->ltID);

					}

				}

			}

    	}

	return StandVolume;

}

long Stand::ComputeStandVolume(int low,int high)

{

	int id,i,j;

	LDPOINT pt;

    SITE* sitetmp;

	HarvestStandVolume=0;
	LANDUNIT *l;
	 for (StandIterator it(*this); it.moreSites(); it.gotoNextSite()) {

        pt = it.getCurrentSite();

		sitetmp = (*pCoresites)(pt.y,pt.x);
		l=pCoresites->locateLanduPt(pt.y,pt.x);
		for(i=1;i<=pCoresites->specNum;i++)

			{

			for(j=low/pCoresites->TimeStep;j<=high/pCoresites->TimeStep;j++)

				{

				if(j<1||j>sitetmp->specAtt(i)->longevity/pCoresites->TimeStep)

					errorSys("Error at ComputeHavestStandVolume",STOP);

				if(pCoresites->GetGrowthRates(i,j,l->ltID)>18.6)

					{

						HarvestStandVolume+=sitetmp->SpecieIndex(i)->getTreeNum(j,i)*pCoresites->GetVolume(i,j, l->ltID);

					}

				}

			}

    	}

	return HarvestStandVolume;

}



 //</Add By Qia on August 03 2009>



/* inline */ int Stand::inStand(int r, int c) {

	//<Add By Qia on Nov 3 2008>
	static int inStandcount = 0;
	inStandcount++;

	int sid =0,tempMid=0;

	if(standMap.inMap(r,c)==0){

		//if (inStandcount > 1636000)
			//cerr << "standMap.inMap == 0" << endl;
		return 0;

	}

	sid=standMap.getvalue32out(r,c);//change by Qia on Nov 4 2008

	/*if (inStandcount > 163600)
		cerr << " standID =" << sid << endl;*/

	if(sid>0)
		tempMid=(*pstands)(sid)->getManagementAreaId();

	int result = (standMap.inMap(r,c) && standMap.getvalue32out(r,c) == itsId && tempMid == itsManagementAreaId);//change by Qia on Nov 4 2008

	//</Add By Qia on Nov 3 2008>

	//<Changed By Qia on Nov 3 2008>

    //int result = (standMap.inMap(r,c) && standMap(r,c) == itsId && managementAreaMap(r,c) == itsManagementAreaId);

	//</Changed By Qia on Nov 3 2008>

	return result;

}



/* inline */ int Stand::numberOfSites() {

    return itsTotalSites;

}



/* inline */ int Stand::numberOfActiveSites() {

    return itsActiveSites;

}



LDPOINT Stand::getRandomPoint() {

    LDPOINT pt;

    do {

        pt.x = irand(itsMinPoint.x, itsMaxPoint.x);

        pt.y = irand(itsMinPoint.y, itsMaxPoint.y);

    } while (!inStand(pt.y,pt.x));

    return pt;

}



void Stand::update() {

	static int count_update = 0;
	count_update++;

	//cerr << " start stand  update" << endl;
    LDPOINT pt;

    SITE* site;



    if (itsUpdateFlag) 

	{
		//cerr << "stand  update 1" << endl;
        if (itsActiveSites == 0) {
			//cerr << "stand  update 2" << endl;
            itsMeanAge = 0;

            itsHarvestableSites = 0;

            itsRecentHarvestFlag = 0;

        } else 

		{

			static int get_updatecount = 0;
			get_updatecount++;

			//if (get_updatecount > 48920){
				//cerr << "stand  update 3" << endl;
			//}

			

            int sum = 0;

            int rcount = 0;

            itsHarvestableSites = 0;

			
			LDPOINT tmp_pt = (*this).getMinPoint();

			LDPOINT tmp_ptmax = (*this).getMaxPoint();



			//if (get_updatecount > 48920)
			//{
			//	cerr << "min y = " << tmp_pt.y << "  min x =" << tmp_pt.x << endl;
			//	cerr << "max y = " << tmp_ptmax.y << "  max x =" << tmp_ptmax.x << endl;
			//}

			int temp_id = (*this).getId();		
			/*if (get_updatecount > 48920)
			{
				cerr << "stand_get_ID =" << temp_id << endl;
			}*/
			//int tmp_sid = standMap.getvalue32out(tmp_pt.y, tmp_pt.x);//change by Qia on Nov 4 2008

			
			/*if (get_updatecount > 48920)
			{
				
				
				cerr << " standID =" << tmp_sid << endl;
			}*/


            for (StandIterator it(*this); it.moreSites(); it.gotoNextSite()) {

				/*if (count_update > 10000)
				cerr << "stand  update 4" << endl;*/

                pt = it.getCurrentSite();


//              site = sites(pt.y,pt.x);   Modified by Vera

				site = (*pCoresites)(pt.y,pt.x);

                if (pCoresites->locateLanduPt(pt.y,pt.x)->active()) //original landis4.0: site->landUnit->active()

																	//Changed By Qia Oct 13 2008

				{

                //    sum += site->getMaxAge();   modified by Vera Nov.10, 2003

                	pHarvestsites->BefStChg(pt.y,pt.x); //Add By Qia on Nov 10 2008

					sum += (*pHarvestsites)(pt.y, pt.x)->getMaxAge(pt.y, pt.x);

					pHarvestsites->AftStChg(pt.y,pt.x); //Add By Qia on Nov 10 2008

                 //   if (standMap(pt.y,pt.x) > 0 && site->canBeHarvested())      modified by Vera Nov.10, 2003

					if (standMap.getvalue32out(pt.y,pt.x) > 0 && (*pHarvestsites)(pt.y, pt.x)->canBeHarvested(pt.y, pt.x))//change by Qia on Nov 4 2008

                        itsHarvestableSites++;

                //    if (site->wasRecentlyHarvested())		modified by Vera Nov.10, 2003

					if ((*pHarvestsites)(pt.y, pt.x)->wasRecentlyHarvested())

                        rcount++;

                }

            }

            itsMeanAge = sum / numberOfActiveSites();

//          if ((float) rcount / itsActiveSites < parameters.harvestThreshold)  modified by Vera

			if ((float) rcount / numberOfActiveSites() < fParamharvestThreshold)

                itsRecentHarvestFlag = 0;

            else

                itsRecentHarvestFlag = 1;

			//printf("stand %d: rcount: %d, itsarea: %d, total site: %d flag: %d\n", itsId, rcount,itsActiveSites, itsTotalSites,itsRecentHarvestFlag);

        }

        itsUpdateFlag = 0;

    }

	//cerr << " end stand  update" << endl;

}



int Stand::isNeighbor(int r, int c) {

    int nid;

//    if (!sites.inBounds(r,c))   modified by Vera

	if (!inBounds(r,c))

        return 0;

    if ((nid = standMap.getvalue32out(r,c)) <= 0 || nid == itsId)//change by Qia on Nov 4 2008

        return 0;

    else

        return nid;

}



/* inline */ void Stand::addNeighbor(int id) {

    if (!itsNeighborList.isMember(id))

        itsNeighborList.append(id);

}





