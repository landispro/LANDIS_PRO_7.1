#include <assert.h>

#include "point.h"

//#include "landis.h"

#include "error.h"

//#include "GlobalVariables.h"

#include "ManagementArea.h"

#include "ManagementAreas.h"

#include "FuelGlobalVariables.h"





MANAGEMENTAREAS::MANAGEMENTAREAS() {

    numManagementAreas = 0;

    managementAreas = 0;

}



MANAGEMENTAREAS::~MANAGEMENTAREAS() {

    delete [] managementAreas;

}



/* inline */ int MANAGEMENTAREAS::number() {

    return numManagementAreas;

}



/* inline */ ManagementArea* MANAGEMENTAREAS::operator() (int n) {

     assert(n >= 1 || n <= numManagementAreas);

     return managementAreas + (n-1);

}



void MANAGEMENTAREAS::construct() {

    int i, r, c, id, snr, snc;

 

//    assert(sites.number() > 0);  modified by Vera

    assert(pfuelcoresites->number() > 0);



    assert(managementAreaMap.rows() > 0);

    

    numManagementAreas = managementAreaMap.high();

    

    if (managementAreas)

        delete [] managementAreas;

    managementAreas = new ManagementArea[numManagementAreas];



  	/* Modified by Vera

    snr=sites.numRows();

    snc=sites.numColumns();

	*/

	snr=pfuelcoresites->numRows();

    snc=pfuelcoresites->numColumns();



    for (i=0; i < numManagementAreas; i++) {

        managementAreas[i].itsId = i+1;

    }

    

    for (r=1; r <= snr; r++) {

        for (c=1; c <= snc; c++) {

           // id = managementAreaMap(r,c);
			// // %%# Changed 2
			id = managementAreaMap.get_data(r, c);

            if (id > 0 && standMap.getvalue32out(r,c) > 0) {//change by Qia on Nov 4 2008

                managementAreas[id-1].itsTotalSites++;

//                if (sites(r,c)->landUnit->active())   Modified by Vera

                if (pfuelcoresites->locateLanduPt(r,c)->active())

				//Original Landis4.0: (*pfuelcoresites)(r,c)->landUnit->active()

				//Changed By Qia on Oct 13 2008

                    managementAreas[id-1].itsActiveSites++;

                managementAreas[id-1].addStand(standMap.getvalue32out(r,c));//change by Qia on Nov 4 2008

	         }

        }

    }



//    for (i=0; i < numManagementAreas; i++) {

//        cout << (i+1) << endl;

//        managementAreas[i].itsStandList.dump();

//    }



}

