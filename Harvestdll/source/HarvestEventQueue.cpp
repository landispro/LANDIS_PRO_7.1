#include <stdio.h>

#include <string.h>

#include <math.h>

#include "system1.h"

#include "error.h"

#include "GlobalVariables.h"

#include "HarvestEvent.h"

#include "List.h"

#include "OnePassStandFillingRegime.h"

#include "TwoPassStandFillingRegime.h"

#include "PeriodicStandFillingRegime.h"

#include "OnePassStandSpreadingRegime.h"

#include "TwoPassStandSpreadingRegime.h"

#include "GroupSelectionRegime.h"

#include "HarvestVolumeFittingRegime.h"

#include "GroupSelectionRegime70.h"

#include "StockingCuttingRegime.h"

#include <stdlib.h>



/* 21-SEP-99 */

#include "PeriodicTwoPassStandFillingRegime.h"

#include "RepeatingTwoPassStandFillingRegime.h"

/* -- END -- */



#include "HarvestEventQueue.h"





HarvestEventQueue::HarvestEventQueue() 

{

	LegendLabeNo = 0;

}



HarvestEventQueue::~HarvestEventQueue() {

    HarvestEvent* p;

    for (ListIterator<HarvestEvent*> it(itsEvents); it.more(); it.advance()) {

        p = it.current();

        delete p;

    }

}



void HarvestEventQueue::addEvent(HarvestEvent* someEvent) {

    itsEvents.append(someEvent);

}



void HarvestEventQueue::processEvents(int itr) 

{
	//printf("harvestEventQueue::processEvents");
    HarvestEvent* p;

	LegendLabeNo = 0;

	//HarvestVolumeFittingRegime* p2;

    for (ListIterator<HarvestEvent*> it(itsEvents); it.more(); it.advance()) {

        p = it.current();

		strcpy((char*)LegendLabe[p->getSequentialId()], p->getLabel());

		LegendLabeNo++;

		if (p->conditions()) {

			currentHarvestEventId++;

			if(p->isA() == EVENT_Volume_BA_THINING){

				 //p2 = (HarvestVolumeFittingRegime*)p;

				// p->=0;
				
				// printf("Volume Cutting\n");

				 p->harvest();

			 }

			else if(p->isA() == EVENT_GROUP_SELECTION_REGIME_70){

				//printf("group selection cutting\n");

				p->harvest();

			}
			else if(p->isA() == EVENT_STAND_STOCKING_HARVEST){

				//printf("stocking cutting\n");

				p->harvest();

			}
		 }

    }

}



//modified by Vera, April 12, 2004 to pass out harvest events list

int HarvestEventQueue::read(FILE* infile) 

{

    int id;

	int Harvesteventmode = 0;

    HarvestEvent* theEvent;

/* 22-OCT-99 */

    int seqId = 0;

/* -- END -- */    



    do {

        if (fscanc(infile, "%d", &id)!=1)

            errorSys("Error reading harvest event identifier from harvest section.",STOP);



        switch (id) 

		{

        case EVENT_ONE_PASS_STAND_FILLING_REGIME :

            theEvent = new OnePassStandFillingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_ONE_PASS_STAND_FILLING_REGIME);

            break;



        case EVENT_PERIODIC_STAND_FILLING_REGIME :

            theEvent = new PeriodicStandFillingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_PERIODIC_STAND_FILLING_REGIME);

            break;

            

        case EVENT_TWO_PASS_STAND_FILLING_REGIME :

            theEvent = new TwoPassStandFillingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_TWO_PASS_STAND_FILLING_REGIME);

            break;



        case EVENT_ONE_PASS_STAND_SPREADING_REGIME :

            theEvent = new OnePassStandSpreadingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_ONE_PASS_STAND_SPREADING_REGIME);

            break;



        case EVENT_TWO_PASS_STAND_SPREADING_REGIME :

            theEvent = new TwoPassStandSpreadingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_TWO_PASS_STAND_SPREADING_REGIME);

            break;



        case EVENT_GROUP_SELECTION_REGIME :

            theEvent = new GroupSelectionRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_GROUP_SELECTION_REGIME);

            break;



/* 21-SEP-99 */

        case EVENT_PERIODIC_TWO_PASS_STAND_FILLING_REGIME :

            theEvent = new PeriodicTwoPassStandFillingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_PERIODIC_TWO_PASS_STAND_FILLING_REGIME);

            break;



        case EVENT_REPEATING_TWO_PASS_STAND_FILLING_REGIME :

            theEvent = new RepeatingTwoPassStandFillingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_REPEATING_TWO_PASS_STAND_FILLING_REGIME);

            break;

/* -- END -- */

		//<Aug 03 2009>

		case EVENT_Volume_BA_THINING:

            theEvent = new HarvestVolumeFittingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_Volume_BA_THINING);

            break;

		//</Aug 03 2009>

		//<Nov 10 2011>

		case EVENT_GROUP_SELECTION_REGIME_70:

            theEvent = new GroupSelectionRegime70();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_GROUP_SELECTION_REGIME_70);

            break;

		//</Nov 10 2011>
		//<July 29 2012>

		case EVENT_STAND_STOCKING_HARVEST:

            theEvent = new StockingCuttingRegime();

			Harvesteventmode = Harvesteventmode | (int)(float)pow(2.0f, (float)EVENT_STAND_STOCKING_HARVEST);

            break;

		//</July 29 2012>

        default :

            errorSys("Error reading harvest event number.",STOP);

            break;

        }



/* 22-OCT-99 */

       seqId = seqId + 1;

       theEvent->setSequentialId(seqId);

/* -- END -- */

        theEvent->read(infile);

        addEvent(theEvent);

 //   } while (!eof(infile));  //modiled by Vera

		} while (!LDeof(infile));





	//init LegendLabel Jan. 28, 2005

	int	j;



	LegendLabe = new char* [seqId+1];

	if (LegendLabe == NULL){

		printf("memory for LegendLabe not enough [seqId+1]\n");
		fflush(stdout);

		exit(1);

		}

	for (j = 0; j < seqId+1; j++)

	{

		LegendLabe[j] = new char [101];

		if (LegendLabe[j] == NULL){

			printf("memory for LegendLabe not enough char [101]\n");
			fflush(stdout);

			exit(1);

			}

		memset(LegendLabe[j], 0, sizeof (char) * (101));

	}



	return Harvesteventmode;

}



