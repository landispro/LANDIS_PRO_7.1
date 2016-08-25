// FuelTrack.cpp: implementation of the FuelTrack class.

//

//////////////////////////////////////////////////////////////////////

#include "FuelGlobalVariables.h"

#include "FuelTrack.h"

#include "SITE.H"

#include "SITES.H"

#include "LANDU.H"

#include "SPECIE.H"

#include "SPECATT.H"

#include "ERROR.H"

#include "system1.h"

#include "agelist.h"

#include "fueldefines.h"

#include <math.h>





//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////



FuelTrack::FuelTrack()

{



}



FuelTrack::~FuelTrack()

{



}



void FuelTrack::FFTrack () {

	// this function will track the fine fuel load

	

    float FFLoad;

//	float totalWeight;

	int spID;

	int ltID;

	int spNum;

	

	int	snr, snc;

	

	int i;

	int j;



	LANDUNIT *l;

	SPECIE *s;

	SPECIESATTR *sa;

			

	snr=pfuelcoresites->numRows();

	snc=pfuelcoresites->numColumns();

	// for each row and column

	for (i=1;i<=snr;i++) { 

		for (j=1;j<=snc;j++) {

	//		printf("%i, %i\n", i, j);

			l=pfuelcoresites->locateLanduPt(i,j); //Original landis4.0: (*pfuelcoresites)(i,j)->landUnit

												//changed By Qia on Oct 13 2008

			// get the land type info

			FFLoad = 0;

			int FFLoadClass = 0;

			spNum = 0;



			//if (i==363 && j == 426) 

			//	printf("\n");



			//printf("\n i:  %d  j:   %d\n", i, j);



			if (l!=NULL && l->active()) {

				// if landtype is active

				ltID = l->ltID;

//				printf("ltID:%d\n", ltID);

				s=(*pfuelcoresites)(i,j)->first();        //Get the first specie.

				sa=(*pfuelcoresites)(i,j)->specAtt();     //Associated attributes.

				int oldage = 0;

				spID = 0;

	//			totalWeight = 0;

				while (s!=NULL && sa!=NULL) {

					oldage = s->oldest();									

					if(oldage >0) {

						

						FFLoad = FFLoad + fuelsites.CalculateFFLoad(spID,oldage,sa->longevity,ltID);

						//printf("Age :%d   Longevity   %d     Ff  %d  FFL  %1.0f\n", oldage, sa->longevity,fuelsites.CalculateFFLoad(spID,oldage,sa->longevity,ltID), FFLoad);

						// get the fine fuel load of each species, add them together

						///totalWeight += fuelsites.getSpWeight(spID, ltID);

						//printf("Weight %f   FFload %f \n",totalWeight, FFLoad);

						spNum++;						

					}

					spID ++;

					s = (*pfuelcoresites)(i,j)->next();

					// get the next species

					sa = (*pfuelcoresites)(i,j)->specAtt();				

					// get the associated attributes

				}

				

				if (spNum <1)	FFLoadClass = 0;

				// if species number <1, then fine fuel = 0

				else {					

					FFLoad = FFLoad / spNum;



					//printf("FFload %4.0f\n", FFLoad);

					// calculate the fine fuel load for the site

					if (FFLoad <0.5)		FFLoadClass = 0;					

					else {

						if (FFLoad >5.5)	FFLoadClass = 5;

						else FFLoadClass = int (FFLoad+ 0.5);

						// Landtype modifier Fine Fuel load

						FFLoadClass = fuelsites.landtypeInfo[ltID].fineFuelLoad[FFLoadClass-1];

						//printf("FFLoad  %d\n",FFLoadClass);

					}			

				}

			}



			//if (FFLoadClass > 4)

			//	printf("\n");



			// Mortality increase coarse fuels

			//int TimeSinceLastMortality = (pPDP->sTSLMortality)[i][j];

			//if (TimeSinceLastMortality==0)				

			//	FFLoadClass ++;





			//printf("FFLoad 1  %d\n",FFLoadClass);

			

			//fuelsites(i,j)->FFLoad = (char) FFLoadClass;

			// Shang 03/04

			// Windthrow disturb fine fuels

			if (gDLLMode & G_WIND)

				FFLoadClass = fuelsites.windDisFFLoad (FFLoadClass, i, j);

			//printf("FFLoad 2  %d\n",FFLoadClass);



			// BDA modify coarse fuel loads

			if (gDLLMode & G_BDA) {

				FFLoadClass = fuelsites.BDADisCFLoad (FFLoadClass, i, j);

			}

			//printf("FFLoad 3  %d\n",FFLoadClass);



			// Harvest disturb fine fuels

			if (gDLLMode & G_HARVEST) {

				FFLoadClass = fuelsites.HarvestDisFFLoad ((int)FFLoadClass, i, j);

			}

			//printf("FFLoad 4  %d\n",FFLoadClass);



			// Fire disturbance fine fuels

			if (gDLLMode & G_FIRE)

				FFLoadClass = fuelsites.fireDisFFLoad (FFLoadClass, i, j);

			//printf("FFLoad 5 %d\n",FFLoadClass);

			

			// save the fine fuel into PDP

			fuelsites.setFFLoad(FFLoadClass, i, j);



			//printf("FFLoad 6 %d\n",FFLoadClass);



		}

	}

}





void FuelTrack::CFTrack () {

	// this function will track the coarse fuel load

	int CFLoad;

	int	snr, snc;

	int ltID;	

	int i;

	int j;



	LANDUNIT *l;

	snr=pfuelcoresites->numRows();

	snc=pfuelcoresites->numColumns();



	// add the time since last fuel management by 10 yrs

	if (gDLLMode & G_FUELMANAGEMENT)

		fuelsites.updateFuelManSite();



	

	// for each row and column

	for (i=1;i<=snr;i++) { 

		for (j=1;j<=snc;j++) {

			int TimeSinceLastDisturbance = 9999;

			int TimeSinceLastMortality = 9999;

			int TimeSinceLastWind = 9999;

			int TimeSinceLastBDA = 9999;

			int TimeSinceLastHarvest = 9999;

			int TimeSinceLastFuelManagement = 9999;

			int TimeSinceLastFire = 9999;



			l=pfuelcoresites->locateLanduPt(i,j);//Original landis4.0: (*pfuelcoresites)(i,j)->landUnit

												//Changed By Qia on Oct 13 2008

			// get the land type

			CFLoad = 0;			

			if (l!=NULL && l->active()) {

				// if landtype is active

				ltID = l->ltID;

				// Shang 03/04

				CFLoad = fuelsites.getCFLoad(i, j);

				// get the previous coarse fuel load

				//<Add By Qia on Nov 19 2008>

				fuelsites.BefStChg(i,j);

				//</Add By Qia on Nov 19 2008>

				fuelsites(i,j)->timeOfCFAccumulation += pfuelcoresites->TimeStep_Fuel;

				//<Add By Qia on Nov 19 2008>

				fuelsites.AftStChg(i,j);

				//</Add By Qia on Nov 19 2008>

				// Shang 03/04

				// Mortality increase coarse fuels

				TimeSinceLastMortality = (pPDP->sTSLMortality)[i][j];

				if (TimeSinceLastMortality>0)

					TimeSinceLastDisturbance = min (TimeSinceLastDisturbance, TimeSinceLastMortality);



				// Windthrow increase coarse fuels

				if (gDLLMode & G_WIND) {

					TimeSinceLastWind = (pPDP->sTSLWind)[i][j];

					if (TimeSinceLastWind>0)

						TimeSinceLastDisturbance = min (TimeSinceLastDisturbance, TimeSinceLastWind);

				}

				// BDA increase coarse fuels

				if (gDLLMode & G_BDA) {

					for(int t = 0; t<pPDP->iBDANum; t++)

						TimeSinceLastBDA = min (TimeSinceLastBDA, (pPDP->pBDAPDP[t]).sTSLBDA[i][j]);

					if(TimeSinceLastBDA>0)

						TimeSinceLastDisturbance = min (TimeSinceLastDisturbance, TimeSinceLastBDA);

				}



				if (gDLLMode & G_HARVEST) {

					TimeSinceLastHarvest = (pPDP->sTSLHarvest)[i][j];

					if (TimeSinceLastHarvest>0)

						TimeSinceLastDisturbance = min (TimeSinceLastDisturbance, TimeSinceLastHarvest);

				}



				if (gDLLMode & G_FUELMANAGEMENT) {

					TimeSinceLastFuelManagement = fuelsites.fuelManSite[(i-1)*fuelsites.cols + j-1].sTSLFUELMAN;

					if (TimeSinceLastFuelManagement>0)

						TimeSinceLastDisturbance = min (TimeSinceLastDisturbance, TimeSinceLastFuelManagement);

				}



				if (gDLLMode & G_FIRE) {

					TimeSinceLastFire = (pPDP->sTSLFire)[i][j];

					if (TimeSinceLastFire>0)

						TimeSinceLastDisturbance = min (TimeSinceLastDisturbance, TimeSinceLastFire);

				}



				CFLoad = fuelsites.CalculateCFLoad(ltID, CFLoad, fuelsites(i,j)->timeOfCFAccumulation, TimeSinceLastDisturbance, fuelsites(i,j)->beginCFDecompClass);

				// get the coarse fuel load

			}

			

			if (TimeSinceLastMortality==0) {

				//printf("Mortality -> CF from %d  to %d\n", CFLoad, CFLoad+1);

				CFLoad ++;

				

			}

						

			// Windthrow increase coarse fuels

			if (gDLLMode & G_WIND && TimeSinceLastWind==0) {

				CFLoad = fuelsites.windDisCFLoad (CFLoad, i, j);

			}



			// BDA modify coarse fuel loads

			if (gDLLMode & G_BDA && TimeSinceLastBDA==0) {

				CFLoad = fuelsites.BDADisCFLoad (CFLoad, i, j);

			}



			// Harvest change coarse fuels

			if (gDLLMode & G_HARVEST && TimeSinceLastHarvest==0) {

				CFLoad = fuelsites.HarvestDisCFLoad (CFLoad, i, j);

			}

			// Shang 03/04

			// Fire disturbe fuels

			if (gDLLMode & G_FIRE && TimeSinceLastFire == 0) 

				CFLoad = fuelsites.fireDisCFLoad (CFLoad, i, j);



			if (CFLoad <0)	CFLoad = 0;

			if (CFLoad >5)	CFLoad = 5;



			// save coarse fuels into PDP

			fuelsites.setCFLoad(CFLoad, i, j);



//			if (fuelsites(i,j)->beginCFDecompClass < CFLoad)

//				fuelsites(i,j)->beginCFDecompClass = CFLoad;	

		}

	}

}



void FuelTrack::CFInit () {

	// this function will calculate the coarse fuel load at yr 0

	int CFLoad;

	int	snr, snc;

	int ltID;	

	int i;

	int j;



	LANDUNIT *l;

	SPECIE *s;

	SPECIESATTR *sa;



	snr=pfuelcoresites->numRows();

	snc=pfuelcoresites->numColumns();

	

	// for each row and column

	for (i=1;i<=snr;i++) { 

		for (j=1;j<=snc;j++) {

			l=pfuelcoresites->locateLanduPt(i,j);//Original landis4.0: (*pfuelcoresites)(i,j)->landUnit

												//changed By Qia on Oct 13 2008

			// get land type

			CFLoad = 0;	

			if (l!=NULL && l->active()) {

				// if land type is active

				ltID = l->ltID;

				//<Add By Qia on Nov 19 2008>

				fuelsites.BefStChg(i,j);

				//</Add By Qia on Nov 19 2008>

				fuelsites(i,j)->timeOfCFAccumulation = (*pfuelcoresites)(i,j)->oldest();

				//<Add By Qia on Nov 19 2008>

				fuelsites.AftStChg(i,j);

				//</Add By Qia on Nov 19 2008>

				// time of coarse fuel load = the oldest age cohort in the site

				CFLoad = fuelsites.CFAccumulation (ltID,fuelsites(i,j)->timeOfCFAccumulation);

				// get the coarse fuel load





				// Calculate the stand age

								

				s=(*pfuelcoresites)(i,j)->first();        //Get the first specie.

				sa=(*pfuelcoresites)(i,j)->specAtt();     //Associated attributes.

				int oldage = 0, standAge = 0;

				while (s!=NULL && sa!=NULL) {

					oldage = s->oldest();									

					if(oldage >0) 

					   standAge = max(oldage, standAge);					

					s = (*pfuelcoresites)(i,j)->next();

					// get the next species

					sa = (*pfuelcoresites)(i,j)->specAtt();				

					// get the associated attributes

				}

				

				// set the stand age to timeSinceLastMortality

				pPDP->sTSLMortality[i][j] = (short)standAge;

				if ((gDLLMode & G_HARVEST) != 0)

					pPDP->sTSLHarvest[i][j] = (short) standAge;





			}

			if (CFLoad <0)	CFLoad = 0;

			if (CFLoad >5)	CFLoad = 5;

			//fuelsites(i,j)->CFLoad = (char) CFLoad;		

			// Shang 03/04

			fuelsites.setCFLoad(CFLoad, i, j);

			// save the coarse fuel load into fuelsites

			//<Add By Qia on Nov 19 2008>

				fuelsites.BefStChg(i,j);

				//</Add By Qia on Nov 19 2008>

			fuelsites(i,j)->beginCFDecompClass = CFLoad;	

				//<Add By Qia on Nov 19 2008>

				fuelsites.AftStChg(i,j);

				//</Add By Qia on Nov 19 2008>

			// save begin coarse fuel decomposition class into fuelsites

		}

	}

}



void FuelTrack::FireRiskTrack() {

	// this function will track the fire probability, intensity and risk

	int CFLoad, FFLoad, FireRisk, FireIntensity, FireProbability;

	float fireProbability;

	int	snr, snc;	

	int i;

	int j;



	LANDUNIT *l;

	snr=pfuelcoresites->numRows();

	snc=pfuelcoresites->numColumns();

	// for each row and column

	for (i=1;i<=snr;i++) { 

		for (j=1;j<=snc;j++) {

			l=pfuelcoresites->locateLanduPt(i,j); //Original landis4.0: l=(*pfuelcoresites)(i,j)->landUnit

												//Changed By Qia on Oct 13 2008

			// get the land type

			CFLoad = 0;

			FFLoad = 0;

			if (l!=NULL && l->active()) {

				// Shang 03/04

				FFLoad = fuelsites.getFFLoad(i,j);

				//FFLoad = (int) fuelsites(i,j)->FFLoad;

				// get the fine fuel load

				CFLoad = fuelsites.getCFLoad(i,j);

				//CFLoad = (int) fuelsites(i,j)->CFLoad;

				// get the coarse fuel load				

				

				// Tracking potential fire intensity

				if (FFLoad>0 && FFLoad<=5 && CFLoad>0 && CFLoad<=5)

					FireIntensity = fuelrule.getFireIntensity(FFLoad,CFLoad);

				else FireIntensity = 0;



				//if(FFLoad>=1 && CFLoad>=1)

				//	printf("FF:  %d  CF:  %d  FI:   %d\n", FFLoad, CFLoad, FireIntensity);

				

				// shang 06/04

				// use live fuel info to modify the potential fire intensity

				int tem1 = FireIntensity;

				//printf("FF:  %d  CF:  %d  FI:   %d\n", FFLoad, CFLoad, FireIntensity);

				

				FireIntensity = fuelsites.CrownFire (tem1, i, j);

				

				//printf("   FI:   %d\n", FireIntensity);



				//if(FFLoad>=1 && CFLoad>=1)

				//	printf("FF:  %d  CF:  %d  FI:   %d\n", FFLoad, CFLoad, FireIntensity);



				//if(FireIntensity < 0)		FireIntensity =0;

				//else if (FireIntensity > 5) FireIntensity = 5;				



				// Tracking potential fire probability class

				// Shang 04/04

				//fireProbability = fuelsites(i,j)->potentialFireProbility;

				if (pfuelcoresites->locateLanduPt(i,j)->active()) {

				//Original landis4.0: (*pfuelcoresites)(i,j)->landUnit->active()

				//changed By Qia on Oct 13 2008

					int fireInterval = fuelsites.fireRegime[fuelsites(i,j)->fireRegime].fireInterval;

					int timeSinceLastFire = 0;

					if (gDLLMode & G_FIRE)

						timeSinceLastFire = (pPDP->sTSLFire)[i][j];

					//timeSinceLastFire = (*pfuelcoresites)(i,j)->lastFire;

					else 

						timeSinceLastFire = fuelsites.fireRegime[fuelsites(i,j)->fireRegime].initialLastFire;					

					fireProbability = (1 - exp((float)-1*timeSinceLastFire/fireInterval));//10*pfuelcoresites->TimeStep_Fuel; Bu,Rencang April, 28 2009



					/*

					// classify the fire probility

					int fireINTERV=(*pfuelcoresites)(i,j)->landUnit->fireInterval;

					//if(fireINTERV>20)	printf("FRI %d\n", fireINTERV);



   					float siteProb=(*pfuelcoresites)(i,j)->landUnit->probCoef*(1.0/(double)fireINTERV)*

   						(exp(1.0/(double)fireINTERV));

					fireProbability = siteProb*(double)(*pfuelcoresites)(i,j)->lastFire/(double)fireINTERV;

					*/

					if (fireProbability>1)	fireProbability = 1;

				}		 

				else  fireProbability = 0;



				if(fireProbability>0) {

					FireProbability = 0;

					for(int t=4;t>=0;t--){

						if(fireProbability>=fuelrule.fireProbilityClass[t]) {

							FireProbability = t+1;

							break;

						}

					}

				}

				else	FireProbability = 0;

				if(FireProbability < 0)			FireProbability =0;

				else if (FireProbability > 5)	FireProbability = 5;

				//printf("Probility: %f      Class: %d \n",fireProbility,probility);



				// Tracking potential fire risk				

				if (FireProbability<=0 || FireIntensity<=0)

					FireRisk = 0;

				else 

					FireRisk = fuelrule.fireRisk[FireProbability-1][FireIntensity-1];

				if(FireRisk < 0)		FireRisk =0;

				else if (FireRisk > 5)	FireRisk = 5;

			}			

			else {

				FireRisk = 0;

				FireIntensity = 0;

				FireProbability = 0;

			}

			//fuelsites(i,j)->fireSeverity = (char)FireIntensity;

			// Shang 03/04

			//fuelsites(i,j)->fireIntensity = (char)FireIntensity;

			fuelsites.setFireIntensityClass (FireIntensity, i,j);

			

			//fuelsites(i,j)->fireProbility = (char)FireProbability;

			fuelsites.setFireProbabiltyClass (FireProbability, i,j);

			//fuelsites(i,j)->fireRisk = (char)FireRisk;

			fuelsites.setFireRiskClass (FireRisk, i,j);

		}

	}

}





