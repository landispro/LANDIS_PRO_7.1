// FireRegimeUnit.h: interface for the CFireRegimeUnit class.

//

//////////////////////////////////////////////////////////////////////



#if !defined(AFX_FIREREGIMEUNIT_H__B75FC4FA_AA05_4AB3_B4FA_1E0DFCD9F143__INCLUDED_)

#define AFX_FIREREGIMEUNIT_H__B75FC4FA_AA05_4AB3_B4FA_1E0DFCD9F143__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



#define PASSIVE 0

#define ACTIVE  1

#define WATER   2

#define WETLAND 3

#define BOG     4

#define LOWLAND 5

#define NONFOREST 6



#include "stdio.h"



class CFireRegimeUnit 

{

public:

	char*  name;               //Fire Regime Unit name.

	int index; //0, 1, 2, ...

	int    fireInterval,       //Mean interval between fires measured in years.         	   		       

           initialLastFire,	   //initial last fire disturbance 

		   windCurve[5],

		   windClass[5],

           fireCurve[5],       //Elements 0-4 correpsond to fire class 1-5.  Each

                               //element stores the number of years fuel must

                               //accumulate for the LANDUNIT to accomodate a fire

                               //of a given severity.

           fireClass[5];       //This holds fire classes in conjunction with fire

                               //curve.



           //windCurve[5],       //Same as fireCurve and fireClass but used for fire

		   //I should delete wind curve info. J.Yang 2004-2-17

           //windClass[5];       //fuel after windthrow.

			// I also should delete windClass info. J.Yang 2004-2-17



    float  m_fIgPoisson;			//Fire ignition Poisson parameter

	//average # of ignition per ha (10,000 m2) per decade

    float  m_fMFS; // mean fire size in this landtype (ha)

    float  m_fFireSTD; //fire size variance squar root in this landtype (ha)

       



	CFireRegimeUnit();

	virtual ~CFireRegimeUnit();



	void read(FILE*);          //Read a fire regime unit from a file.

	void write(FILE*);         //Write a fire regime unit to a file.

	void dump();               //Dump contents of fire regime unit to the CRT.	

	

	

	int active();              //A fire regime type is either active or inactive.

                           //Inactive fire regime units are not processed.

	int water();               //Returns true if a fire regime unit type is water, false

                           //otherwise.	



private:	

	int status;                //Either ACTIVE, PASSIVE, or WATER.



};



#endif // !defined(AFX_FIREREGIMEUNIT_H__B75FC4FA_AA05_4AB3_B4FA_1E0DFCD9F143__INCLUDED_)

