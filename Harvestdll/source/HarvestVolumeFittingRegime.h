#ifndef HARVESTVOLUMEFITTINGREGIME_H

#define HARVESTVOLUMEFITTINGREGIME_H





#include "HarvestVolumeFittingRegime.h"



#include <stdio.h>

#include "HarvestRegime.h"

#include "SiteRemovalMask.h"

#include "Stand.h"
using namespace std;
class HarvestVolumeFittingRegime_reentry_event{//add by Qia on May 29 2012
public: 


int itsReentryInteval;

int itsEntryDecade;

    int itsFinalDecade;


    int itsTargetCut;

	float targetProportion;

	float TargetVolume;//Aug 03 2009

	float Mininum_BA; //May 26 2011

	int Small0_Large1;//May 26 2011

	int speciesOrder[200]; //May 26 2011

	int flag_plant[200];

	int flag_cut[200];

	int num_TreePlant[200];

void HarvestVolumeFittingRegime_load_reentry_parameters(FILE *fp);
};

class HarvestVolumeFittingRegime : public HarvestRegime {

public :

	int StandsCut;

	int SitesCut;

	double GetBAinACell(int i, int j);

    HarvestVolumeFittingRegime();

	double CutShareBAinACell(int i, int j,double target);

	double CutShareBAinACell_LifeSpanPercent(int i, int j,double target);

    virtual ~HarvestVolumeFittingRegime();

	

    virtual int isA();

    virtual int conditions();

    virtual void harvest();

    virtual void read(FILE* infile);

	HarvestVolumeFittingRegime_reentry_event* HarvestVolumeFittingRegime_reentry_event_instances;
	int current_reentry_event_instances;
	int total_reentry_event_instances;

	void reharvest();
	void send_parameters_to_current(int flag, int);
	void copy_initial_parameters();
protected :

    void readCustomization1(FILE* infile);

    void readCustomization2(FILE* infile);



    int isHarvestDone();

    int harvestStand(Stand* stand);



private:

    enum {START, TOHARVEST, TOREENTRY, DONE, PENDING} itsState;

    int itsEntryDecade;

    int itsFinalDecade;

    int itsRepeatInterval;

    int itsTargetCut;

	float targetProportion;

	float TargetVolume;//Aug 03 2009

	float Mininum_BA; //May 26 2011

	int Small0_Large1;//May 26 2011

	int speciesOrder[200]; //May 26 2011

	int flag_plant[200];

	int flag_cut[200];

	int num_TreePlant[200];

	vector<int> itsStands;

	//<Add By Qia on June 02 2012>
	
	int itsTargetCut_copy;

	float targetProportion_copy;

	float TargetVolume_copy;//Aug 03 2009

	float Mininum_BA_copy; //May 26 2011

	int Small0_Large1_copy;//May 26 2011

	int speciesOrder_copy[200]; //May 26 2011

	int flag_plant_copy[200];

	int flag_cut_copy[200];

	int num_TreePlant_copy[200];
	//</Add By Qia on June 02 2012>

};







#endif





