/********************************************

Name:			BDASites.h 

Description:	BDASites

Input:			

Output:			

Date:			Oct. 10, 2002

Last Mod:		Oct. 15

*******************************************/



#ifndef BDASITES_H

#define BDASITES_H



#include <stdio.h>

//<Add By Qia on Dec 03 2008>

#include <vector>

#include <list>

//</Add By Qia on Dec 03 2008>









enum Zone		{Nozone, Lastzone, Newzone};





//##ModelId=3F01D0EA0047

typedef struct

{

	float	fSiteResourceDom;	//SiteResourceDominance

	float	fSiteResDomMod;

	float	fSV;				//SiteVulnerability

	Zone	enumOutbreakZone;	// 0: inactive, 1: active, 2: outbrakzone

	float	fNeighborResDom;	

	bool	bNewEpicenter;

	int		iLastBDADisturb;	//last BDA disturbance time

	int		iDisturbSeverity;

	char	cDispersal;

	bool	bDeadArea;			//true dead area; false live area

	//<Add By Qia on Dec 03 2008>

	int numofsites;

	//</Add By Qia on Dec 03 2008>

}BDASITE;

//<Add By Qia on Dec 03 2008>

typedef std::vector<BDASITE *>  SortedBDASITE;

//</Add By Qia on Dec 03 2008>



//##ModelId=3F01D0EA0065

class BDASites

{

public:

	//##ModelId=3F01D0EA0075

	int			m_iRows;

	//##ModelId=3F01D0EA0084

	int			m_iCols;

	//##ModelId=3F01D0EA0095

	//BDASITE*	m_pBDAMap; //Commented By Qia on Dec 03 2008

	

 	//<Add By Qia on Dec 03 2008>

	SortedBDASITE SortedIndex;

	//</Add By Qia on Dec 03 2008>

	

	//##ModelId=3F01D0EA0099

	BDASites();			//default constructor

	//##ModelId=3F01D0EA00A4

	BDASites(int, int);	//constructor, sets m_pBDAMap to be given rows and columns

	//##ModelId=3F01D0EA00A7

	~BDASites();		//destructor



	//##ModelId=3F01D0EA00B3

	BDASITE* operator()	(int, int);  //return a pointer to a singular BDASITE



	//##ModelId=3F01D0EA00C3

	void	read		(FILE*);

	//##ModelId=3F01D0EA00C5

	void	write		(FILE*);

	//##ModelId=3F01D0EA00D2

	void	dump		();



	//##ModelId=3F01D0EA00D3

	int		number		();			//return total number of BDASites

	//##ModelId=3F01D0EA00D4

	int		numRows		();

	//##ModelId=3F01D0EA00E2

	int		numColums	();



	//<Add by Qia on Dec 03 2008>

	void dumpsite(BDASITE *site);

	int SITE_compare(BDASITE *site1, BDASITE *site2);

	int SITE_compare(int site1_x, int site1_y, int site2_x, int site2_y);

	                                   // Compare two sites to see the relation between them

	                                   // return 0:equal; return 1: site1 is bigger; return 2: site2 is bigger; -1: error

	                               

	int SITE_sort();				  // sort the pointers to sites



	int SITE_insert(int pos_sortIndex, BDASITE *site, int i, int j);					// insert a site in to list



	int SITE_delete(int pos_sortIndex, BDASITE *site, int i, int j);				// remove a site from list



	

	int SITE_LocateinSortIndex(BDASITE *site, int *pos, int *ifexist);

	

	void fillinSitePt(int i, int j, BDASITE *site);

	BDASITE * locateSitePt(int i, int j);

	

	void BefStChg(int i, int j);

	void AftStChg(int i,int j);

	//</Add By Qia on Dec 03 2008>

	private:

	//<Add by Qia Dec 03 2008>

	BDASITE **map;

	//</Add by Qia on Dec 03 2008>

	BDASITE *sitetouse;//Add By Qia on Dec 19 2008

};





#endif

