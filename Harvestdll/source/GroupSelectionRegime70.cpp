#include <assert.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include "system1.h"

#include "error.h"

#include "SiteRemovalMask.h"

#include "GlobalVariables.h"

#include "Stand.h"

#include "List.h"

#include "SiteHarvester.h"

#include "HarvestEvent.h"

#include "StandHarvester.h"

#include "HarvestReport.h"

#include "HarvestPath.h"

#include "MultiplePocketStandHarvester.h"

#include "GroupSelectionRegime70.h"



GroupSelectionRegime70::GroupSelectionRegime70()

{

    itsState = START;

    itsEntryDecade = 0;

    itsRepeatInterval = 0;

    itsTargetCut = 0;

    itsStandProportion = 0.0;

    itsMeanGroupSize = 0.0;

    itsStandardDeviation = 0.0;

    itsTotalNumberOfStands = 0;

}



GroupSelectionRegime70::~GroupSelectionRegime70() {

	if(total_reentry_event_instances > 0){

		delete GroupSelectionRegime70_reentry_event_instances;
	}

}



/* inline */ int GroupSelectionRegime70::isA() {

    return EVENT_GROUP_SELECTION_REGIME_70;

}



int GroupSelectionRegime70::conditions() {

    int passed;

    switch (itsState) {

	case PENDING :

        if (currentDecade == itsEntryDecade) {

            passed = 1;

			itsState = TOHARVEST;

			send_parameters_to_current(1,-1);

        } else if (currentDecade>itsEntryDecade&&(currentDecade-itsEntryDecade) % itsRepeatInterval == 0) {

            passed = 1;


            itsState = TOHARVEST;

			send_parameters_to_current(1,-1);
		}

		else{

			passed = 0;

		}
		if(currentDecade>itsEntryDecade){

			for(int i=0;i<total_reentry_event_instances;i++){

				int inteval_reentry = GroupSelectionRegime70_reentry_event_instances[i].itsReentryInteval;

				if((currentDecade-itsEntryDecade-inteval_reentry)%(itsRepeatInterval) == 0 ||(currentDecade-itsEntryDecade)-inteval_reentry == 0){

					passed = 1;

					itsState = TOREENTRY;

					send_parameters_to_current(0,i);
				}
			}
		}
        break;



    /*case REENTRYPENDING :

        if ((currentDecade-itsEntryDecade) % itsRepeatInterval != 0)

            passed = 0;

        else {

            passed = 1;

            itsState = REENTRYREADY;

        }

        break;*/



    default :

        errorSys("Illegal call to GroupSelectionRegime70::conditions.", STOP);

        break;

    }



    return passed;

}



void GroupSelectionRegime70::harvest() {


	switch (itsState) {



    case TOHARVEST :

		HarvestRegime::harvest();

        itsState = PENDING; 

		break;



    case TOREENTRY :

		reharvest();

		itsStands.clear();

        itsState = PENDING;

		break;



   default :

        errorSys("Illegal call to GroupSelection::harvest.", STOP);

    }

}



void GroupSelectionRegime70::read(FILE* infile) {

    if (itsState == START) {

        HarvestRegime::read(infile);

        itsState = PENDING;

    } else {

        errorSys("Illegal call to GroupSelectionRegime70::read.", STOP);

    }

}



void GroupSelectionRegime70::readCustomization1(FILE* infile) {

     if (fscanc(infile, "%d", &itsEntryDecade)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	 if (fscanc(infile, "%d", &itsRepeatInterval)!=1)

        errorSys("Error reading reentry interval from harvest section.",STOP);

	if (fscanc(infile, "%f", &targetProportion)!=1)

        errorSys("Error reading management area target proportion from harvest section.",STOP);

    if (fscanc(infile, "%d", &standProportionDenominator)!=1)

        errorSys("Error reading stand proportion denominator from harvest section.",STOP);

    if (fscanc(infile, "%f", &itsMeanGroupSize)!=1)

        errorSys("Error reading mean group size from harvest section.",STOP);

    if (fscanc(infile, "%f", &itsStandardDeviation)!=1)

        errorSys("Error reading standard deviation from harvest section.",STOP);

    itsStandProportion = (float) 1.0 / standProportionDenominator;

	itsTargetCut = (int) ((float)(managementAreas(getManagementAreaId())->numberOfActiveSites()) * targetProportion);

    rotationLength = (int) (itsRepeatInterval * standProportionDenominator);

	SitesCut = 0;

    setDuration(rotationLength);



	if(pCoresites->specNum>200){

		  errorSys("Two many species for harvest.",STOP);

	 }

	 for(int i=0; i<pCoresites->specNum;i++){

		 if (fscanc(infile, "%d", &(pCoresites->flag_cut_GROUP_CUT[i]))!=1)

			errorSys("Error reading  from harvest section.",STOP);

		 if (fscanc(infile, "%d", &(pCoresites->flag_plant_GROUP_CUT[i]))!=1)

			errorSys("Error reading from harvest section.",STOP);

		 if (fscanc(infile, "%d", &(pCoresites->num_TreePlant_GROUP_CUT[i]))!=1)

			errorSys("Error reading from harvest section.",STOP);

	}
	 copy_initial_parameters(); //<Add By Qia on May 29 2012>

	if (fscanc(infile, "%d", &total_reentry_event_instances)!=1)

        errorSys("Error reading standard deviation from harvest section.",STOP);

	if(total_reentry_event_instances > 0){

		GroupSelectionRegime70_reentry_event_instances = new GroupSelectionRegime70_reentry_event[total_reentry_event_instances];
	}
	for(int ii=0;ii<total_reentry_event_instances;ii++){

		GroupSelectionRegime70_reentry_event_instances[ii].GroupSelectionRegime70_load_reentry_parameters(infile);
	}
	//</Add By Qia on May 29 2012>
}

void GroupSelectionRegime70_reentry_event::GroupSelectionRegime70_load_reentry_parameters(FILE *infile){

	int temp_load_format;

	if (fscanc(infile, "%d", &temp_load_format)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	if (fscanc(infile, "%d", &temp_load_format)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	if (fscanc(infile, "%d", &temp_load_format)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	if (fscanc(infile, "%d", &temp_load_format)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	if (fscanc(infile, "%d", &temp_load_format)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);



	

    if (fscanc(infile, "%d", &itsReentryInteval)!=1)

        errorSys("Error reading entry decade from harvest section.",STOP);

	 if (fscanc(infile, "%d", &itsRepeatInterval)!=1)

        errorSys("Error reading reentry interval from harvest section.",STOP);

	if (fscanc(infile, "%f", &targetProportion)!=1)

        errorSys("Error reading management area target proportion from harvest section.",STOP);

    if (fscanc(infile, "%d", &standProportionDenominator)!=1)

        errorSys("Error reading stand proportion denominator from harvest section.",STOP);

    if (fscanc(infile, "%f", &itsMeanGroupSize)!=1)

        errorSys("Error reading mean group size from harvest section.",STOP);

    if (fscanc(infile, "%f", &itsStandardDeviation)!=1)

        errorSys("Error reading standard deviation from harvest section.",STOP);

    


	if(pCoresites->specNum>200){

		  errorSys("Two many species for harvest.",STOP);

	 }

	 for(int i=0; i<pCoresites->specNum;i++){

		 if (fscanc(infile, "%d", &(flag_cut_GROUP_CUT[i]))!=1)

			errorSys("Error reading  from harvest section.",STOP);

		 if (fscanc(infile, "%d", &(flag_plant_GROUP_CUT[i]))!=1)

			errorSys("Error reading from harvest section.",STOP);

		 if (fscanc(infile, "%d", &(num_TreePlant_GROUP_CUT[i]))!=1)

			errorSys("Error reading from harvest section.",STOP);

	}
}
void GroupSelectionRegime70::send_parameters_to_current(int flag, int index){

	if(flag == 1){//initial or repeat

		targetProportion = targetProportion_copy;

		standProportionDenominator = standProportionDenominator_copy;

		rotationLength = rotationLength_copy;

		itsTargetCut = itsTargetCut_copy;

		SitesCut = SitesCut_copy;

		itsStandProportion = itsStandProportion_copy;

		itsMeanGroupSize = itsMeanGroupSize_copy;

		itsStandardDeviation = itsStandardDeviation_copy;

		itsTotalNumberOfStands = itsTotalNumberOfStands_copy;

		for(int i = 0;i<200;i++){

			pCoresites->flag_cut_GROUP_CUT[i] = pCoresites->flag_cut_GROUP_CUT_copy[i];

			pCoresites->flag_plant_GROUP_CUT[i] = pCoresites->flag_plant_GROUP_CUT_copy[i];

			pCoresites->num_TreePlant_GROUP_CUT[i] = pCoresites->num_TreePlant_GROUP_CUT_copy[i];
		}
		itsStandProportion = (float) 1.0 / standProportionDenominator;

		itsTargetCut = (int) ((float)(managementAreas(getManagementAreaId())->numberOfActiveSites()) * targetProportion);

		rotationLength = (int) (itsRepeatInterval * standProportionDenominator);

		SitesCut = 0;

		setDuration(rotationLength);
	}
	else if(flag == 0&& index<total_reentry_event_instances){//re-entry

		targetProportion = GroupSelectionRegime70_reentry_event_instances[index].targetProportion;

		standProportionDenominator = GroupSelectionRegime70_reentry_event_instances[index].standProportionDenominator;

		rotationLength = GroupSelectionRegime70_reentry_event_instances[index].rotationLength;

		itsTargetCut = GroupSelectionRegime70_reentry_event_instances[index].itsTargetCut;

		SitesCut = GroupSelectionRegime70_reentry_event_instances[index].SitesCut;

		itsStandProportion = GroupSelectionRegime70_reentry_event_instances[index].itsStandProportion;

		itsMeanGroupSize = GroupSelectionRegime70_reentry_event_instances[index].itsMeanGroupSize;

		itsStandardDeviation = GroupSelectionRegime70_reentry_event_instances[index].itsStandardDeviation;

		itsTotalNumberOfStands = GroupSelectionRegime70_reentry_event_instances[index].itsTotalNumberOfStands;
		for(int i = 0;i<200;i++){

			pCoresites->flag_cut_GROUP_CUT[i] = GroupSelectionRegime70_reentry_event_instances[index].flag_cut_GROUP_CUT[i];

			pCoresites->flag_plant_GROUP_CUT[i] = GroupSelectionRegime70_reentry_event_instances[index].flag_plant_GROUP_CUT[i];

			pCoresites->num_TreePlant_GROUP_CUT[i] = GroupSelectionRegime70_reentry_event_instances[index].num_TreePlant_GROUP_CUT[i];
		}
		itsStandProportion = (float) 1.0 / standProportionDenominator;

		itsTargetCut = (int) ((float)(managementAreas(getManagementAreaId())->numberOfActiveSites()) * targetProportion);

		rotationLength = (int) (itsRepeatInterval * standProportionDenominator);

		SitesCut = 0;

		setDuration(rotationLength);
	}
}

void GroupSelectionRegime70::copy_initial_parameters(){

	itsTargetCut_copy = itsTargetCut;

	SitesCut_copy = SitesCut;

	itsStandProportion_copy = itsStandProportion;

	itsMeanGroupSize_copy = itsMeanGroupSize;

	itsStandardDeviation_copy = itsStandardDeviation;

	itsTotalNumberOfStands_copy = itsTotalNumberOfStands;

	targetProportion_copy = targetProportion;

    standProportionDenominator_copy = standProportionDenominator;

    rotationLength_copy = standProportionDenominator;

	for(int i = 0;i<200;i++){

		pCoresites->flag_cut_GROUP_CUT_copy[i] = pCoresites->flag_cut_GROUP_CUT[i];

		pCoresites->flag_plant_GROUP_CUT_copy[i] = pCoresites->flag_plant_GROUP_CUT[i];

		pCoresites->num_TreePlant_GROUP_CUT_copy[i] = pCoresites->num_TreePlant_GROUP_CUT[i];
	}
}


void GroupSelectionRegime70::readCustomization2(FILE* infile) {

}



int GroupSelectionRegime70::isHarvestDone() {

    int result;

	if(SitesCut >= itsTargetCut){

		SitesCut = 0;

		return 1;

	}

	else{

		return 0;

	}

    result = SitesCut >= itsTargetCut;

	SitesCut = 0;

    return result;

}



int GroupSelectionRegime70::harvestStand(Stand* stand) {


	SitesCut+=stand->numberOfActiveSites();

	//printf("sitesinstand:%d SitesCut:%d Target:%d\n",stand->numberOfActiveSites(),SitesCut,itsTargetCut);

    SiteHarvester theSiteHarvester(getUserInputId(), getRemovalMask(), getReport(), getDuration());

	MultiplePocketStandHarvester theStandHarvester(stand, itsStandProportion, itsMeanGroupSize, itsStandardDeviation, &theSiteHarvester);

	
    int standCut = theStandHarvester.harvest();
	
    if (standCut > 0) {

        stand->reserve();

        itsStands.push_back(stand->getId());

        itsTotalNumberOfStands++;

    }


    return 1;

}



void GroupSelectionRegime70::reharvest() {

	

    Stand* stand;

    MultiplePocketStandHarvester* theStandHarvester;

    int standCut;

    SiteHarvester theSiteHarvester(getUserInputId(), getRemovalMask(), getReport(), getDuration());



    getReport()->reset();



	for (int i=0; i<itsStands.size(); i++) {

//        stand = stands(it.current());  Modified by Vera

		stand = (*pstands)(itsStands.at(i));



        theStandHarvester = new MultiplePocketStandHarvester(stand, itsStandProportion, itsMeanGroupSize,

          itsStandardDeviation, &theSiteHarvester);

        standCut = theStandHarvester->harvest();

        delete theStandHarvester;

    }



    writeReport(harvestOutputFile2);

}





