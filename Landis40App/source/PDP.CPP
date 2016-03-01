/*****************************

PDP.cpp

Created by Vera

Last modified: Jan 3, 2004



******************************/



#include <string.h>

#include <stdlib.h>



#include "sites.h"

#include "PDP.H"





//constructer

PDP::PDP(int mode, int col, int row, int BDANo)

{

	int	i;



	iCols = col;

	iRows= row;

	iBDANum = BDANo;



	sTSLFire = NULL;

	cFireSeverity = NULL;

	

	//Fuel

	cFineFuel = NULL;

	cCoarseFuel = NULL;



	// shang add

	cFireIntensityClass = NULL;				// 13.	PotentialFireIntensity

	cFireRiskClass = NULL;					// 14.	Potential FireRisk



	//BGrowth

	//can changed to short???

	iTotalLiveBiomass = NULL;

	iLiveBiomassBySpecies = NULL;

	iCoarseWoodyDebris = NULL;

	iDeadFineBiomass = NULL;



	//Harvest

	sTSLHarvest = NULL;

//	strHarvestEvent = NULL;  //1D

	cHarvestEvent = NULL;



	//wind

	sTSLWind = NULL;

	cWindSeverity = NULL;



	//Succession

	sTSLMortality = NULL;



	sTSLMortality = Array2D(sTSLMortality, iRows, iCols);

	//if BDA is loaded, intilize according to whether Fire, Harvetst, and Wind are loaded or not

	if (mode & G_BDA)              

	{

		if(mode & G_WIND)

			sTSLWind = Array2D(sTSLWind, iRows, iCols);

	}

	//Fire

	if (mode & G_FIRE)

	{

		sTSLFire = Array2D(sTSLFire, iRows, iCols);

		cFireSeverity = Array2D(cFireSeverity, iRows, iCols);

	}

	if (mode & G_FUEL)

	{

		cFineFuel = Array2D(cFineFuel, iRows, iCols);

		cCoarseFuel = Array2D(cCoarseFuel, iRows, iCols);

		// Shang add

		cFireIntensityClass = Array2D(cFireIntensityClass, iRows, iCols);		// 13.	PotentialFireIntensity

		cFireRiskClass = Array2D(cFireRiskClass, iRows, iCols);					// 14.	Potential FireRisk



	}



	//Fuel

	if (mode & G_FUEL)

	{

		if (mode & G_BDA)

		{

			//allocate BDA

			pBDAPDP = new BDAPDP[iBDANum];

			for (i = 0; i < iBDANum; i++)

			{

				pBDAPDP[i].BDAType = new char [50];

				pBDAPDP[i].cBDASeverity = Array2D(pBDAPDP[i].cBDASeverity, iRows, iCols);

				pBDAPDP[i].sTSLBDA = Array2D(pBDAPDP[i].sTSLBDA, iRows, iCols);

			}

		}

	}  //end of if (mode & G_FUEL)

	if(mode & G_WIND)

	{

		if (sTSLWind == NULL)

			sTSLWind = Array2D(sTSLWind, iRows, iCols); 

		if (cWindSeverity == NULL)

			cWindSeverity = Array2D(cWindSeverity, iRows, iCols);

		sTSLWind[1][1] = 0;

	}

	if (mode & G_HARVEST)

	{

			if (sTSLHarvest == NULL)

				sTSLHarvest = Array2D(sTSLHarvest, iRows, iCols);

			if (cHarvestEvent == NULL)

//				strHarvestEvent = new char[G_HARVEST_EVENTLENGTH];

				cHarvestEvent = Array2D(cHarvestEvent, iRows, iCols);

	}



}









PDP::~PDP()

{

	//Delete BDA

//	DeleteArray2D(



	//Delete fire

	DeleteArray2D(sTSLFire, iRows);

	DeleteArray2D(cFireSeverity, iRows);





	//Delete Fuel

	DeleteArray2D(cFineFuel, iRows);

	DeleteArray2D(cCoarseFuel, iRows);



	//Delete BGrowth

	DeleteArray2D(iTotalLiveBiomass, iRows);

	DeleteArray2D(iLiveBiomassBySpecies, iRows);

	DeleteArray2D(iCoarseWoodyDebris, iRows);

	DeleteArray2D(iDeadFineBiomass, iRows);



	//Delete Harvest

	DeleteArray2D(sTSLHarvest, iRows);

//	delete [] strHarvestEvent;

	DeleteArray2D(cHarvestEvent, iRows);



	//Delete wind

	DeleteArray2D(sTSLWind, iRows);

	DeleteArray2D(cWindSeverity, iRows);



	//Delete Succession

	DeleteArray2D(sTSLMortality, iRows);

}



template <class ArrayType>

ArrayType** PDP::Array2D(ArrayType** A, int row, int col)

{

	int	j;



	A =	new ArrayType* [row+1];

	if (A == NULL){

		printf("memory not enough new ArrayType* [row+1] %d %d\n", row,col);

		exit(1);

		}

	for (j = 0; j < row+1; j++)

	{

		A[j] = new ArrayType [col+1];

		if (A[j] == NULL){

			printf("memory not enough A[j] = new ArrayType [col+1]; %d %d\n", row,col);

			exit(1);

			}

		memset(A[j], 0, sizeof (ArrayType) * (col+1));

	}



	return A;

}



template <class ArrayType>

void PDP::DeleteArray2D(ArrayType** A, int row)

{

	int	j;



	if (A != NULL)

	{

		for (j = 0; j < row+1; j)

			delete [] A[j];



		delete [] A;

	}

}



//template <class ArrayType>

void PDP::pdpdump()

{

/*	int	i, j;



	FILE* m_pW = fopen("c:\PDPdump.txt", "w" );



	for (i = 1; i <= iRows; i++)

	{

		for (j = 1; j <= iCols; j++)

			fprintf(m_pW, "%i ", sTSLWind[i][j]);

		fprintf(m_pW, "%s", "\n");

	}



	fclose(m_pW);

*/

}



