#ifndef HARVESTEVENTQUEUE_H

#define HARVESTEVENTQUEUE_H



#include <stdio.h>

#include "HarvestEvent.h"

#include "List.h"

//#include "sites.h"

//#include "stands.h"



#ifdef HARVESTDLL_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



class  HarvestEventQueue {

public :

    HarvestEventQueue();

    virtual ~HarvestEventQueue();

    void addEvent(HarvestEvent* someEvent);

    DLLCLASS void processEvents(int itr);

    int read(FILE* infile);

//private :

     List<HarvestEvent*> itsEvents;

//	 char LegendLabe[251][100];

	 char** LegendLabe;

	 int LegendLabeNo;



 //    List<int> itsNeighborList;



};



#undef DLLCLASS



#endif

