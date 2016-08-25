// 1. Spread to site neighbors only if something is cut.

// 2. Spread to N, S, E, W.



#include <assert.h>

#include "map8.h"

#include "point.h"

#include "SiteHarvester.h"

//#include "landis.h"

#include "system1.h"

#include "GlobalVariables.h"

#include "GlobalFunctions.h"

#include "HarvestPath.h"

#include "BoundedPocketStandHarvester.h"

#include "PDP.h"

//begin add by Vera Nov. 10

int currentDecade;

int numberOfSpecies;



MAP16 standMap;

MAP16 managementAreaMap;



MANAGEMENTAREAS managementAreas;

HarvestEventQueue harvestEvents;



FILE* harvestOutputFile1;

FILE* harvestOutputFile2;



unsigned short currentHarvestEventId;





STANDS*			pstands;

//STANDS			Harveststands;

//pstands = new STANDS();



SITES*			pCoresites;

HARVESTSites*	pHarvestsites;

int				giRow;

int				giCol;



int				iParamstandAdjacencyFlag;

int				iParamharvestDecadeSpan;

float			fParamharvestThreshold;



SPECIESATTRS*	pspeciesAttrs;

MAP16			visitationMap;

PDP*			m_pPDP; //added by Vera





/*end add by Vera*/





//--end add by Vera Nov. 10

BoundedPocketStandHarvester::BoundedPocketStandHarvester(int targetCut, LDPOINT startPoint, SiteHarvester* siteHarvester,

  HarvestPath* path) {

	
    assert(targetCut >= 0);



 /*   int SITES::inBounds(int r, int c) {

    if (r >= 1 && r <= rows && c >= 1 && c <= columns)

        return 1;

    else

        return 0;

*/


	assert(inBounds(startPoint.y, startPoint.x));

    assert(siteHarvester);



    int standId = (int) standMap.getvalue32out(startPoint.y, startPoint.x); //changed By Qia on Nov 4 2008
	
    assert(standId > 0);

 //   setStand(stands(standId));  Modified by Vera

    setStand((*pstands)(standId));



    setSiteHarvester(siteHarvester);

    setPath(path);

    itsTargetCut = targetCut;

    itsStartPoint = startPoint;

 }



int BoundedPocketStandHarvester::EVENT_GROUP_SELECTION_REGIME_70_clear_cut(int i, int j){
	static int count = 0;
	count++;

	//printf("BPSH EVENT, %d, %d\n", i, j);

	int k, m;

	int sitecut = 0;

	double TmpBasalAreaS=0;
	LANDUNIT *l;

	l = pCoresites->locateLanduPt(i,j);

	

	for(k=1;k<=pCoresites->specNum;k++){

		if(pCoresites->flag_cut_GROUP_CUT[k-1]){

			for(m=1;m<=(*pCoresites)(i,j)->specAtt(k)->longevity/pCoresites->TimeStep;m++){

				if((*pCoresites)(i,j)->SpecieIndex(k)->getTreeNum(m,k)>0){

					sitecut = 1;

					TmpBasalAreaS=pCoresites->GetGrowthRates(k,m,l->ltID)*pCoresites->GetGrowthRates(k,m,l->ltID)/4*3.1415926*(*pCoresites)(i,j)->SpecieIndex(k)->getTreeNum(m,k)/10000.00;
					
					if((*pCoresites)(i,j)->specAtt(k)->MinSproutAge<=m*pCoresites->TimeStep&&(*pCoresites)(i,j)->specAtt(k)->maxSproutAge>=m*pCoresites->TimeStep){

						(*pCoresites)(i,j)->SpecieIndex(k)->TreesFromVeg+=(*pCoresites)(i,j)->SpecieIndex(k)->getTreeNum(m,k);

					}
					(*pCoresites)(i,j)->SpecieIndex(k)->setTreeNum(m,k,0);

					pHarvestsites->AddMoreValueHarvestBA_spec(i,j,k-1,TmpBasalAreaS);

					pHarvestsites->AddMoreValueHarvestBA(i,j,TmpBasalAreaS);

				}

				

			}

		}

	}

	if (sitecut >= 1) {

		//harvestEvents.itsEvents.at(currentHarvestEventId);

		(*pHarvestsites)(i,j)->harvestType = getSiteHarvester()->getHarvestType();

		(*pHarvestsites)(i,j)->lastHarvest =  currentDecade;

		for(k=1;k<=pCoresites->specNum;k++){

			if(pCoresites->flag_plant_GROUP_CUT[k-1]){

				int tree_left = (*pCoresites)(i,j)->SpecieIndex(k)->getTreeNum(1,k);

				(*pCoresites)(i,j)->SpecieIndex(k)->setTreeNum(1,k,pCoresites->num_TreePlant_GROUP_CUT[k-1]+tree_left);

			}

		}

	}

	return sitecut;

}

// add site nighbor
int BoundedPocketStandHarvester::harvest_EVENT_GROUP_SELECTION_REGIME_70(LDPOINT pt){
	
    //int i, k;
	int k = 0;

    int r[4];


    int siteCut = 0;

    int sumCut = 0;

	int c = 0;

	visitationMap.set_data(itsStartPoint.y, itsStartPoint.x, currentHarvestEventId);

    itsNeighborList.append(itsStartPoint);



    while (sumCut < itsTargetCut && itsNeighborList.length() > 0) {
		
		c = itsNeighborList.length();
	
        pt = itsNeighborList.remove();

        if (canBeHarvested(pt)) {
			
			siteCut = EVENT_GROUP_SELECTION_REGIME_70_clear_cut(pt.y,pt.x);

            sumCut += siteCut;


            if (siteCut > 0) {

				for (int i = 0; i < 4; i++){

					r[i] = i;
					
				}

                for (int i = 4; i > 0; i--) {

                    k = (int) (i * frand());

					//orignal no control over k, potential out of bound err 
					//<Add By Qia on Nov 1 2012>
					if(k<0){
						k = 0;
					}
					if(k>3){
						k = 3;
					}
					//</Add By Qia on Nov 1 2012>
					assert(k >= 0);
					assert(k < 4);
					
                    switch (r[k]) {
					
						

                    case 0: addSiteNeighbor(pt.y, pt.x-1);
                            break;

                    case 1: addSiteNeighbor(pt.y, pt.x+1);
                            break;

                    case 2: addSiteNeighbor(pt.y-1, pt.x);
                            break;

                    case 3: addSiteNeighbor(pt.y+1, pt.x);
                            break;

                    }
				

                    r[k] = r[i-1];
					
					if(k<0||k>3||(i-1)<0||(i-1)>3){

						printf("group selection index error\n");
					}
                }
				
            }
			
        }

    }
	
    return sumCut;

}





int BoundedPocketStandHarvester::harvest() {

	LDPOINT pt;

	int i = 0, k = 0;


	int r[4];

	int siteCut = 0;
	int sumCut = 0;


	int c = 0;

	visitationMap.set_data(itsStartPoint.y, itsStartPoint.x, currentHarvestEventId);


	itsNeighborList.append(itsStartPoint);



	while (sumCut < itsTargetCut && itsNeighborList.length() > 0) {
		c = itsNeighborList.length();

		pt = itsNeighborList.remove();

		if (canBeHarvested(pt)) {

			siteCut = harvest_EVENT_GROUP_SELECTION_REGIME_70(pt);

			sumCut += siteCut;

			if (siteCut > 0) {

				for (i = 0; i < 4; i++)

					r[i] = i;

				for (i = 4; i > 0; i--) {

					k = (int)(i * frand());
					//orignal no control over k, potential out of bound err 
					//<Add By Qia on Nov 1 2012>
					if (k < 0){
						k = 0;
					}
					if (k > 3){
						k = 3;
					}
					assert(k >= 0);
					assert(k < 4);

					switch (r[k]) {


					case 0: addSiteNeighbor(pt.y, pt.x - 1);
						break;

					case 1: addSiteNeighbor(pt.y, pt.x + 1);
						break;

					case 2: addSiteNeighbor(pt.y - 1, pt.x);
						break;

					case 3: addSiteNeighbor(pt.y + 1, pt.x);
						break;

					}

					r[k] = r[i - 1];

					if (k < 0 || k>3 || (i - 1) < 0 || (i - 1) > 3){

						printf("group selection index error\n");
					}

				}

			}


		}


		return sumCut;



	}

}


void BoundedPocketStandHarvester::addSiteNeighbor(int r, int c) {
	
	assert(currentHarvestEventId > 0);
	assert(currentHarvestEventId < 65535);

	
	const int first_val = getStand()->inStand(r, c);
	
	if (first_val && visitationMap.get_data(r, c) != currentHarvestEventId)
	{
		
		LDPOINT p(c,r);
		
        itsNeighborList.append(p);

		visitationMap.set_data(r, c, currentHarvestEventId);
		
	}
	
}



