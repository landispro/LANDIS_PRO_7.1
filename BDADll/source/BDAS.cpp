/********************************************************/
/*BDAS.cpp: implementation of the BDAS class.           */
/*Description: keep the list of BDAs					*/
/********************************************************/


#include <stdlib.h> 


#include <string.h>
#include <stdio.h>

#include <direct.h>
#include <errno.h>

#include "BDAS.h"
#include "error.h"
#include "system1.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//##ModelId=3F01D0EA0121
BDAS::BDAS()
{

}

/**************************************************************************
Name:		BDAS
Description:read in all the BDAs, and store them is m_pBDAList
Updated by Wei Li on April 26, 2004, to add a BDA directory to the output
***************************************************************************/
//##ModelId=3F01D0EA0122
BDAS::BDAS(char* strfn, SITES* s, int cellsize, char* OutputDir, LANDUNITS* lus, SPECIESATTRS*  sa, PDP* ppdp, int ifBDArepeat, int gDllMd)
{
	int		i;
	FILE*	pfBDAInit;
	char	strBDAName[20];
	char	str1[200];
	//char	string[30] = "\0";
	bool	bSpeedUp = false;
	int iSpeedUp;


	if ((pfBDAInit = LDfopen(strfn, 1)) == NULL)
		errorSys("BDAS: BDAInit file not found.",STOP);

	if (fscanc(pfBDAInit, "%d", &m_iBDANum) != 1) 
		errorSys("BDAS: Error in reading BDAInit number.", STOP);


	if (m_iBDANum <= 0)
		errorSys("BDAS: Invalid BDA numbers.", STOP);
	
	if (fscanc(pfBDAInit, "%d", &iSpeedUp) != 1) 
		errorSys("BDAS: Error in reading BDAInit SpeedUp parameters.", STOP);
	if (iSpeedUp >0) bSpeedUp = true;

	m_pBDAList = (BDA**)malloc(m_iBDANum * sizeof(BDA*));

	sprintf(str1, "%s/%s/", OutputDir, "BDA");

	if (_mkdir(str1) != 0)
	{
		if (errno != EEXIST)
			errorSys("BDAS: Can't create the direcory", STOP);
	}
	//printf("get here 1...\n");
	//fflush(stdin);


	for (i = 0; i < m_iBDANum; i ++)
	{
		//printf("get the loop 2 \n");
		//fflush(stdin);

		if (fscanc(pfBDAInit, "%s", strBDAName) != 1) 
			errorSys("Landis: Error in reading BDAInit number.", STOP);
	
		printf("get the %s\n",strBDAName);
		fflush(stdin);


		m_pBDAList[i] = new BDA(strBDAName, s, cellsize, lus, sa, ppdp, ifBDArepeat, gDllMd, i);


		if (m_pBDAList[i] == NULL)
			errorSys("BDAS: BDA read error.",STOP); 
		sprintf(m_pBDAList[i]->m_strBDAOutput, "%s/%s/", str1, m_pBDAList[i]->m_strName);

		if (_mkdir(m_pBDAList[i]->m_strBDAOutput) != 0)
		{
			if (errno != EEXIST)
				errorSys("BDAS: Can't create the direcory", STOP);
		}



		m_pBDAList[i]->m_bSpeedUp = bSpeedUp;
	}


}


//##ModelId=3F01D0EA0124
BDAS::~BDAS()
{
	int	i;

	for (i = 0; i < m_iBDANum; i ++)
		delete m_pBDAList[i];

	free(m_pBDAList);
}

/**************************************************************
Name:		Active
Description:perform biological Disturbance for BDAs stored in
			m_pBDAList 

***************************************************************/
//##ModelId=3F01D0EA0131
void BDAS::Active(int itr)
{
	int	i;

	for (i = 0; i < m_iBDANum; i++)
	{
		printf("\nBDA %s is being processed\n", m_pBDAList[i]->m_strName);
		m_pBDAList[i]->BDAActive();
		m_pBDAList[i]->BDAOutputMap(itr);
	}

}


/*BDAS*  GetBDAS(char* str, SITES* s, int i, LANDUNITS* plu, SPECIESATTRS* ps )
{
 
  return new BDAS(str, s, i, plu, ps);

};
*/

