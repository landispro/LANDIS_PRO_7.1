/*Class: Public Data Pool	*/

/*Name:  PDP.h				*/





/*defined in file: DEFINES.H*/

#ifndef PDP_H

#define PDP_H



#include "defines.h"

/*

#define G_SUCCESSION	1	//0x0000001 

#define G_BDA			2   //0x0000010

#define G_WIND			4   //0x0000100 

#define G_HARVEST		8	//0x0001000

#define G_FUEL			16  //0x0010000

#define G_FIRE			32  //0x0100000

#define	G_BGROWTH		64  //0x1000000*/



#define G_HARVEST_EVENTLENGTH	10





typedef struct

{

	short**	sTSLBDA;		//tinesince last BDA

	char**	cBDASeverity;

	char*	BDAType;



}BDAPDP;





class PDP

{

public:

	int			iCols;

	int			iRows;



	//BDA

	int			iBDANum;

	BDAPDP*		pBDAPDP;	



	//Fire

	short**		sTSLFire;

	char**		cFireSeverity;

	

	//Fuel

	char**		cFineFuel;

	char**		cCoarseFuel;

	char**		cFireIntensityClass;			// 13.	PotentialFireIntensity 

	char**		cFireRiskClass;					// 14.	Potential FireRisk





	//BGrowth

	//can changed to short???

	int**		iTotalLiveBiomass;

	int**		iLiveBiomassBySpecies;

	int**		iCoarseWoodyDebris;

	int**		iDeadFineBiomass;



	//Harvest

	short**		sTSLHarvest;

//	char*		strHarvestEvent;  //1D

	char**     cHarvestEvent;



	//wind

	short**		sTSLWind;

	char**		cWindSeverity;



	//Succession

	short**		sTSLMortality;





	PDP();

	PDP(int, int, int, int);

	~PDP();

	

	template <class ArrayType> 

	ArrayType** Array2D(ArrayType** A, int row, int col);

	

	template <class ArrayType> 

	void DeleteArray2D(ArrayType** A, int row);



//	template <class ArrayType> 

	void		pdpdump	();

};



#endif





