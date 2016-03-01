#include <assert.h>

#include "point.h"

//#include "landis.h"

#include "error.h"

#include "FuelGlobalVariables.h"

#include "FuelStand.h"

#include "FuelStands.h"

//#include <iostream.h>



FUELSTANDS::FUELSTANDS() {

    numStands = 0;

    stands = 0;

}



FUELSTANDS::~FUELSTANDS() {

    delete [] stands;

}



/* inline */ int FUELSTANDS::number() {

    return numStands;

}



/* inline */ FUELStand* FUELSTANDS::operator() (int n) {

     assert(n >= 1 || n <= numStands);

     return stands + (n-1);

}



void FUELSTANDS::construct() {

    int i, r, c, id, nid, snr, snc, mid, currMid;

    LDPOINT pmin;

    LDPOINT pmax;

    char errorString[80];



    assert(pfuelcoresites->number() > 0);

    assert(standMap.rows() > 0);

    

    numStands = standMap.high();

    

    if (stands)

        delete [] stands;

    stands = new FUELStand[numStands];

    

    snr = pfuelcoresites->numRows();

    snc = pfuelcoresites->numColumns();

    for (i=0; i < numStands; i++) {

        stands[i].itsId = i+1;

        stands[i].itsMinPoint.x = snc;

        stands[i].itsMinPoint.y = snr;

        stands[i].itsMaxPoint.x = 1;

        stands[i].itsMaxPoint.y = 1;

    }

    

    for (r=1; r <= snr; r++) {



        for (c=1; c <= snc; c++) {



            id = standMap.getvalue32out(r,c); //changed By Qia on Nov 4 2008



            if (id > 0) {

                // Determine lower left and upper right stand coordinates

	             pmin = stands[id-1].itsMinPoint;

	             pmax = stands[id-1].itsMaxPoint;

                if (r < pmin.y) pmin.y = r;

	             if (r > pmax.y) pmax.y = r;

	             if (c < pmin.x) pmin.x = c;

	             if (c > pmax.x) pmax.x = c;

 	             stands[id-1].itsMinPoint = pmin;

                stands[id-1].itsMaxPoint = pmax;

				assert(stands[id - 1].itsMinPoint.x >= 1 && stands[id - 1].itsMinPoint.x <= snc);
				assert(stands[id - 1].itsMinPoint.y >= 1 && stands[id - 1].itsMinPoint.x <= snr);



                // Set management area identifier

               // mid = managementAreaMap(r,c);
				// %%# Changed 4
				mid = managementAreaMap.get_data(r, c);

                if (mid <= 0) {

                    sprintf(errorString, "No management area defined at (x,y) = (%d,%d)", c, r);

                    errorSys(errorString, STOP);

                }

                if ((currMid = stands[id-1].itsManagementAreaId) > 0 && currMid != mid) {

                    sprintf(errorString, "Stand %d crosses management area boundary at (x,y) = (%d,%d)", id, c, r);

                    errorSys(errorString, STOP);

                }

                stands[id-1].itsManagementAreaId = mid;



                // Determine stand neighbors

                if ((nid = stands[id-1].isNeighbor(r,c+1)) > 0) {

                    stands[id-1].addNeighbor(nid);

                    stands[nid-1].addNeighbor(id);

                }

                if ((nid = stands[id-1].isNeighbor(r-1,c)) > 0) {

                    stands[id-1].addNeighbor(nid);

                    stands[nid-1].addNeighbor(id);

                }



                // Count total and active sites

                stands[id-1].itsTotalSites++;

                if (pfuelcoresites->locateLanduPt(r,c)->active())//Original landis4.0: (*pfuelcoresites)(r,c)->landUnit->active()

																//Changed By Qia on Oct 13 2008

                    stands[id-1].itsActiveSites++;



	         }

        }

    }

//    for (i=0; i < numStands; i++) {

//       cout << (i+1) << endl;

//       stands[i].itsNeighborList.dump();

//    }





}

