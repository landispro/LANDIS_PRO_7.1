#ifndef HARVESTEVENT_H

#define HARVESTEVENT_H



#include <stdio.h>



//changed by Vera April 10, 2004 to enable bit operations

#define EVENT_ONE_PASS_STAND_FILLING_REGIME 9

#define EVENT_PERIODIC_STAND_FILLING_REGIME 10

#define EVENT_TWO_PASS_STAND_FILLING_REGIME 11

#define EVENT_ONE_PASS_STAND_SPREADING_REGIME 4

#define EVENT_TWO_PASS_STAND_SPREADING_REGIME 5

#define EVENT_GROUP_SELECTION_REGIME 6



/* 21-SEP-99 */

#define EVENT_PERIODIC_TWO_PASS_STAND_FILLING_REGIME 7

#define EVENT_REPEATING_TWO_PASS_STAND_FILLING_REGIME 8

#define EVENT_Volume_BA_THINING 1 //Add By Qia on Aug 03 2009

#define EVENT_GROUP_SELECTION_REGIME_70 2 //Add By Qia on Nov 10 2011

#define EVENT_STAND_STOCKING_HARVEST 3 //Add By Qia on July 26 2012
/* -- END -- */







#ifdef HARVESTDLL_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif





class DLLCLASS HarvestEvent {

public :

    HarvestEvent();

    virtual ~HarvestEvent();

    virtual int isA() = 0;

    virtual int conditions() = 0;

    virtual void harvest() = 0;

    virtual void read(FILE* infile) = 0;

/* 22-OCT-99 */

    void setSequentialId(int someId);

    int getSequentialId();



	void setUserInputId(int someId);

    int getUserInputId();

/* -- END -- */



//protected :

    void setLabel(const char* label);

    const char* getLabel();



private :

    char* itsLabel;

/* 22-OCT-99 */

    int itsSequentialId;

	int UserInputID_70;

/* -- END -- */

};



/* 22-OCT-99 */



/* Replaced all occurrences of "SiteHarvester theSiteHarvester(isA(),"

                          with "SiteHarvester theSiteHarvester(getSequentialId()," */



/* -- END -- */

#undef DLLCLASS



#endif



