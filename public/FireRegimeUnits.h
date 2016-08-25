// FireRegimeUnits.h: interface for the CFireRegimeUnits class.

//

//////////////////////////////////////////////////////////////////////



#if !defined(AFX_FIREREGIMEUNITS_H__78E1DC0A_F222_4334_B3DF_F0E134755AB5__INCLUDED_)

#define AFX_FIREREGIMEUNITS_H__78E1DC0A_F222_4334_B3DF_F0E134755AB5__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



#include "FireRegimeUnit.h"

#include "defines.h"



#include "List.h"

#include "point.h"

#include "stocc.h"

#include "FireSites.h"

#include <iostream>

#include <cstdio>

#include <stdio.h>

#include "gdal_priv.h"

#include "cpl_conv.h" // for CPLMalloc()

#include "cpl_string.h"

#include "ogr_spatialref.h"



typedef List<LDPOINT> sitesWRTFRUList;



class CFireRegimeUnits 

{

public:

	void updateIGDensity(int cellSize);

	long NumOfSites[256];



	//CFireRegimeUnits(int n=MAX_LANDUNITS,StochasticLib * pStochastic=NULL);	

	CFireRegimeUnits(int, StochasticLib * );	

	virtual ~CFireRegimeUnits();

	

	//sitesWRTFRUList * sitesWRTFRUListArray; // sites with respect to fire regime unit



	void read(FILE*);             //Read set of land unit attributes from a file.

	void write(FILE*);            //Write set of land unit attributes to a file.

	void dump();                  //Dump set of land unit attributes to the CRT.	

	void dispatch();              //dispatch all sites into respecting/all

							  //sitesWRTlandunitListPtr[i]

	

	CFireRegimeUnit* operator() (char*); //Referrence an attribute by species name.

	CFireRegimeUnit* operator() (int);   //Referrence an attribute by species number.

	CFireRegimeUnit* first();            //Referrence first land unit attribute.

	CFireRegimeUnit* next();             //Referrence next land unit attribute.

		                             //NOTE: All four referrence functions return 

                              //NULL if attribute referrenced is illeagal or

                              //unavailable.

	int number();                 //Returns number of land units.

	void attach(CFireSites *);

	void readFireRegimeGIS(FILE*);	
	
	void readFireRegimeIMG(GDALDataset*);

private:



	CFireRegimeUnit * pFireRegimeUnit;          //Array holding all fire regime units.

	CFireSites * m_pFireSites;

	StochasticLib * m_pStochastic;

	int numLU;                    //Number of fire regime units.

	int currentLU;                //Current fire regime unit being pointed to by first

                                  //and next access functions.

	int maxLU;                    //Maximum number of fire regime units.  Defined upon 

                                  //class construction.

	


};



#endif // !defined(AFX_FIREREGIMEUNITS_H__78E1DC0A_F222_4334_B3DF_F0E134755AB5__INCLUDED_)

