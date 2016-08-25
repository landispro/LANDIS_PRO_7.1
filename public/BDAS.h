/*******************************************************

BDAS.h: interface for the BDAS class.

Last Modify:    Nov. 20, 2002

Author:			Vera W. Li

*******************************************************/

#ifndef BDAS_H

#define BDAS_H



#include "BDA.h"

#include "BDAdefines.h"

#include "sites.h"

#include "PDP.h"



//##ModelId=3F01D0EA00F2

class  BDAS  

{

public:

	//##ModelId=3F01D0EA0102

	BDA**	m_pBDAList;

	//##ModelId=3F01D0EA0106

	int		m_iBDANum;

	//##ModelId=3F01D0EA0111

	char	m_strBDAOutput[FNSIZE];



	BDAS();

	BDAS(char*, SITES*, int, char*, LANDUNITS*, SPECIESATTRS*, PDP*, int, int);

	~BDAS();



	void Active(int);







};



#endif 

