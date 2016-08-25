#include <assert.h>

#include "point.h"

//#include "landis.h"

#include "error.h"

#include "GlobalVariables.h"

#include "Stand.h"

#include "Stands.h"

//#include <iostream.h>



STANDS::STANDS() { 

    numStands = 0;

    stands = 0;

}



STANDS::~STANDS() {

    delete [] stands;

}



/* inline */ int STANDS::number() {

    return numStands;

}



/* inline */ Stand* STANDS::operator() (int n) {

	/*if (n <1 || n > numStands){

		cerr << "n = " << n << endl;
	}*/

     assert(n >= 1 && n <= numStands);

     return stands + (n-1);

}



void STANDS::construct() {

    int i, r, c, id, nid, snr, snc, mid, currMid;

    LDPOINT pmin;

    LDPOINT pmax;

    char errorString[80];



/*  assert(sites.number() > 0);  modified by Vera

    assert(standMap.rows() > 0);*/

    

    assert(pCoresites->number() > 0);

    assert(standMap.rows() > 0);



    numStands = standMap.high();

	

    if (stands)

        delete [] stands;

    stands = new Stand[numStands];

 

/*	

    snr = sites.numRows();   Modified by Vera

    snc = sites.numColumns();

*/

    snr = pCoresites->numRows();

    snc = pCoresites->numColumns();



    for (i=0; i < numStands; i++) {

        stands[i].itsId = i+1;

        stands[i].itsMinPoint.x = snc;

        stands[i].itsMinPoint.y = snr;

        stands[i].itsMaxPoint.x = 1;

        stands[i].itsMaxPoint.y = 1;

		assert(stands[i].itsMinPoint.x >= 1 && stands[i].itsMinPoint.x <= snc);
		assert(stands[i].itsMinPoint.y >= 1 && stands[i].itsMinPoint.y <= snr);

    }

	

    for (r=1; r <= snr; r++) {



        for (c=1; c <= snc; c++) {



            id = standMap.getvalue32out(r,c);//change by Qia on Nov 4 2008



            if (id > 0) {

						// Determine lower left and upper right stand coordinates

						 pmin = stands[id-1].itsMinPoint;

						 pmax = stands[id-1].itsMaxPoint;

						 //cerr << "before"<< "id =" << id << " stands[id-1].itsMinPoint.x =" << pmin.x << "  stands[id-1].itsMinPoint.y =" << pmin.y << endl;

						// cerr << " stands[id-1].itsMaxPoint.x =" << pmax.x << " stands[id-1].itsMaxPoint.y =" << pmax.y << endl;

						// cerr << "r =" << r << " c =" << c << endl;

						if (r < pmin.y) pmin.y = r;

						 if (r > pmax.y) pmax.y = r;

						 if (c < pmin.x) pmin.x = c;

						 if (c > pmax.x) pmax.x = c;

						 assert(pmin.x);
 						 stands[id-1].itsMinPoint = pmin;

						stands[id-1].itsMaxPoint = pmax;

						//cerr <<"after"<< "id =" << id << " stands[id-1].itsMinPoint.x =" << pmin.x << "  stands[id-1].itsMinPoint.y =" << pmin.y << endl;
						//cerr << " stands[id-1].itsMaxPoint.x =" << pmax.x << " stands[id - 1].itsMaxPoint.y =" << pmax.y << endl;

						assert(stands[id - 1].itsMinPoint.x >= 1 && stands[id - 1].itsMinPoint.x <= snc);
						assert(stands[id - 1].itsMinPoint.y >= 1 && stands[id - 1].itsMinPoint.y <= snr);
						assert(stands[id - 1].itsMaxPoint.x >= 1 && stands[id - 1].itsMaxPoint.x <= snc);
						assert(stands[id - 1].itsMaxPoint.y >= 1 && stands[id - 1].itsMaxPoint.y <= snr);

						// Set management area identifier

					   // mid = managementAreaMap(r,c);
						mid = managementAreaMap.get_data(r, c);

						if (mid <= 0) {

							sprintf(errorString, "No management area defined at (x,y) = (%d,%d) StandID: %d", c, r,id);

							errorSys(errorString, STOP);

						}

						if ((currMid = stands[id-1].itsManagementAreaId) > 0 && currMid != mid) {

							sprintf(errorString, "Stand %d crosses management area boundary at (x,y):currMid:%d, mid: %d = (%d,%d)", id, c, r,currMid,mid);

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

						/*Modified by Vera

						stands[id-1].itsTotalSites++;

						if (sites(r,c)->landUnit->active())

							stands[id-1].itsActiveSites++;

								*/

						stands[id-1].itsTotalSites++;

						if (pCoresites->locateLanduPt(r,c)->active())//Original Landis4.0: (*pCoresites)(r,c)->landUnit->active()

																	//Changed By Qia Oct 13 2008
						{
							stands[id-1].itsActiveSites++;
						}


	         }

        }

    }

//    for (i=0; i < numStands; i++) {

//       cout << (i+1) << endl;

//       stands[i].itsNeighborList.dump();

//    }





}

