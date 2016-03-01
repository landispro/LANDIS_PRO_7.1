/********************************************

Name:			FireSites.h 

Description:	FireSites

Input:			

Output:			

Date:			Feb. 18, 2004

Last Mod:		Feb. 18

*******************************************/



#ifndef FIRESITES_H

#define FIRESITES_H



#include <stdio.h>

#include "FireRegimeUnit.h"

//#include "FireRegimeUnits.h"



//<Add By Qia on Nov 24 2008>

#include <vector>

#include <list>
#include "point.h"
//</Add By Qia on Nov 24 2008>







typedef struct

{

	int FRUIndex;	

	int DEM;  //elevation, data type should be discussed, J.Yang 

	int numofsites;//Add By Qia on Nov 24 2008

}FIRESITE;



//<Add By Qia on Nov 24 2008>

typedef std::vector<FIRESITE *>  SortedFIRESITE;

//</Add By Qia on Nov 24 2008>



class CFireSites

{

public:

	

	int			m_iRows;	

	int			m_iCols;

	//<Add By Qia on Nov 24 2008>

	SortedFIRESITE SortedIndex;

	//</Add By Qia on Nov 24 2008>

	//FIRESITE*	m_pFireLAND; //commented by Qia on Nov 24 2008

	

	CFireSites();			//default constructor	

	CFireSites(int, int);	//constructor, sets m_pFireLAND to be given rows and columns	

	~CFireSites();		//destructor	

	FIRESITE* operator()	(int, int);  //return a pointer to a singular FIRESITE

	

	//void	readFireRegime(FILE*,CFireRegimeUnits*);	

	//void	write		(FILE*);	

	//void	dump		();	



	int		number		();			//return total number of FIRESITEs	

	int		numRows		();	

	int		numColumns	();

	//<Add by Qia on Nov 24 2008>
    //<Add By Qia on Dec 26 2013>
	std::vector<LDPOINT> FireRegimeUnitsList[70000];
	int FireRegimeCurrentIndex[70000];
	void create_FireRegimeUnitsListByIndex();
	LDPOINT return_a_point_from_index(int index, int cellNo);
	//</Add By Qia on Dec 26 2013>
int SITE_compare(FIRESITE *site1, FIRESITE *site2);

int SITE_compare(int site1_x, int site1_y, int site2_x, int site2_y);

                                   // Compare two sites to see the relation between them

                                   // return 0:equal; return 1: site1 is bigger; return 2: site2 is bigger; -1: error

                               

int SITE_sort();				  // sort the pointers to sites



int SITE_insert(int pos_sortIndex, FIRESITE *site, int i, int j);					// insert a site in to list



int SITE_delete(int pos_sortIndex, FIRESITE *site, int i, int j);				// remove a site from list





int SITE_LocateinSortIndex(FIRESITE *site, int *pos, int *ifexist);









void fillinSitePt(int i, int j, FIRESITE *site);

FIRESITE * locateSitePt(int i, int j);









void BefStChg(int i, int j);

void AftStChg(int i,int j);

//</Add By Qia on Nov 24 2008>



//<Add By Qia on Nov 24 2008>

private: 



FIRESITE** map;

FIRESITE *sitetouse;//Add By Qia on Dec 19 2008



//</Add By Qia on Nov 24 2008>





};





#endif

