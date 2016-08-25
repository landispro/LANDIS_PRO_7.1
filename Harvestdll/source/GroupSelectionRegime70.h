#ifndef GROUPSELECTIONREGIME70_H

#define GROUPSELECTIONREGIME70_H



#include <stdio.h>

#include "HarvestRegime.h"

#include "SiteRemovalMask.h"

#include "Stand.h"

#include "List.h"

using namespace std;

class GroupSelectionRegime70_reentry_event{//add by Qia on May 29 2012

public: 

	int flag_cut_GROUP_CUT[200]; 

	int flag_plant_GROUP_CUT[200];

	int num_TreePlant_GROUP_CUT[200];

	int itsReentryInteval;

	int itsEntryDecade;

    int itsRepeatInterval;

    int itsTargetCut;

	int SitesCut;

    float itsStandProportion;

    float itsMeanGroupSize;

    float itsStandardDeviation;

    int itsTotalNumberOfStands;


	float targetProportion;

    int standProportionDenominator;

    int rotationLength;

	void GroupSelectionRegime70_load_reentry_parameters(FILE *fp);
};

class GroupSelectionRegime70 : public HarvestRegime {

public :

    GroupSelectionRegime70();

    virtual ~GroupSelectionRegime70();

	int isA();

    int conditions();

    void harvest();

    void read(FILE* infile);

	GroupSelectionRegime70_reentry_event* GroupSelectionRegime70_reentry_event_instances;

	int current_reentry_event_instances;

	int total_reentry_event_instances;

	void send_parameters_to_current(int flag, int);

	void copy_initial_parameters();

protected :

    void readCustomization1(FILE* infile);

    void readCustomization2(FILE* infile);

	int isHarvestDone();

    int harvestStand(Stand* stand);

    void reharvest();



private :

	enum { START, TOHARVEST, TOREENTRY, DONE, PENDING } itsState;

	float targetProportion;

    int standProportionDenominator;

    int rotationLength;

	int itsEntryDecade;

    int itsRepeatInterval;

    int itsTargetCut;

	int SitesCut;

    float itsStandProportion;

    float itsMeanGroupSize;

    float itsStandardDeviation;

    int itsTotalNumberOfStands;

    vector<int> itsStands;
	
	float targetProportion_copy; //<Add By Qia on June 02 2012>

    int standProportionDenominator_copy;

    int rotationLength_copy;
	
    int itsTargetCut_copy;

	int SitesCut_copy;

    float itsStandProportion_copy;

    float itsMeanGroupSize_copy;

    float itsStandardDeviation_copy;

    int itsTotalNumberOfStands_copy;  //</Add By Qia on June 02 2012>

};



#endif



