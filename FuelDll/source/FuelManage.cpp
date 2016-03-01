// FuelManEvent.cpp: implementation of the FuelManEvent class.

//

//////////////////////////////////////////////////////////////////////



#include "FuelManage.h"

#include "error.h"

#include "system1.h"

#include "FuelGlobalVariables.h"

#include "ManagementAreas.h"



FUELSTANDS*		fuelpstands;

FuelSites		fuelsites;

FuelRule		fuelrule;

MAP16			standMap;

MAP16			managementAreaMap;

MANAGEMENTAREAS managementAreas;

char*			fueloutputDir;

int				gDLLMode;

SITES*			pfuelcoresites;

float			harvestThreshold;

int				numberOfSpecies;

PDP*			pPDP;

FuelManage		fuelManager;

FuelTrack		fueltrack;



//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////



FuelManage::FuelManage()

{

	



}



void FuelManage::read (FILE *inFile) {

    FuelManEvent* theEvent;

	

	do {

		

		theEvent = new FuelManEvent();	// initialize the event



        theEvent->read(inFile);			// read in the fuel event



		addEvent(theEvent);				// add the fuel event into list



    } while (!LDeof(inFile));

	

	

}



FuelManage::~FuelManage()

{

	



}



/**

 * adds another harvest event to the list

 *

 * @param an individual FuelManage event 

 * @return void 

 */



void FuelManage::addEvent(FuelManEvent* someEvent) {

    itsEvents.append(someEvent);

}





FuelManEvent * FuelManage::getFuelManEvent() {

	

	// Return the current fuel management event

	ListIterator<FuelManEvent*> it(itsEvents);	

	return it.current();

}



/**

 *  This loops through the list of fuel management events and runs the fuel management.

 *  It creates a pointer to a fuel management event. Then through polymorphism the pointer

 *  will call each individual management event's conditons function and if it passes the 

 *  conditions set in the fuel management prescriptions then the fuel management occurs.

 *

 * @return void 

 */



void FuelManage::processEvents(int itr) {

    FuelManEvent* p;

//	printf("fuelmanage-> processEvents");

	// If the fuel management equal to NULL, then stop

	if(fuelManageFile ==NULL)

		errorSys("Error. Can't open fuelmanage file for write.\n",STOP);



	// Deal with fuel managements

    for (ListIterator<FuelManEvent*> it(itsEvents); it.more(); it.advance()) {

		//fprintf(fuelManageFile, "Iteration  %d  ", itr);

		// Get current fuel management event

        p = it.current();

		//<Add By Qia on May 19 2009>

		if (!strcmp (p->Label, "PRESCRIBEDBURNING")){

			p->Treatment(itr, fuelManageFile, fuelManOutStand,1); 

			}

		else if (!strcmp (p->Label, "CWDREDUCTION")){

			p->Treatment(itr, fuelManageFile, fuelManOutStand,0); 

			}

		else if (!strcmp (p->Label, "PRESCRIBEDFIRE+CWDREDUCTION")){

			p->Treatment(itr, fuelManageFile, fuelManOutStand,2); 

			}

		else{

			p->Treatment(itr, fuelManageFile, fuelManOutStand,0); 

			}

		//</Add By Qia on May 19 2009>

		// Do the treatment based on the prescription

       // p->Treatment(itr, fuelManageFile, fuelManOutStand); //comment By Qia



    }

}



