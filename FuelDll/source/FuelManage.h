// FuelManEvent.h: interface for the FuelManEvent class.

//

//////////////////////////////////////////////////////////////////////



#ifndef _FUELMANA_

#define _FUELMANA_



#include "DEFINES.H"

#include <stdio.h>

#include "FuelManEvent.h"

#include "List.h"





class FuelManage

{



public:

	

	FuelManage();

	~FuelManage();

	void read (FILE*);						// read in fuel management events

    void addEvent(FuelManEvent*);			// add fuel management event

	FuelManEvent* getFuelManEvent();		// get fuel management event

	void processEvents(int);	// process fuel management event



private :

	/**

	 * This is a linked list of all FuelManEvent for this run.

	 */

    List<FuelManEvent*> itsEvents;



};



#endif

