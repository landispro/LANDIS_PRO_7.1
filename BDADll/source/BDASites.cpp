/*
Name:			BDASites.cpp 
Description:	BDASites
Input:			
Output:			
Date:			Oct. 16, 2002
Last Mod:		
*/
#include <stdlib.h>
#include <string.h>
#include "BDASites.h"

//##ModelId=3F01D0EA0099
BDASites::BDASites()
{
	m_iRows = 0;
	m_iCols = 0;
	//m_pBDAMap = NULL; //commented By Qia on Dec 03 2008
	map=NULL;//Add By Qia on Dec 03 2008
}

//##ModelId=3F01D0EA00A4
BDASites::BDASites(int i, int j)
{
	//m_pBDAMap = new BDASITE[i * j]; //commented By Qia on Dec 03 2008
	map=new BDASITE*[i*j]; //Add by Qia Dec 03 2008
	printf("LandisPro BDA map allocated\n");
	m_iRows = i;
	m_iCols = j; 
	//<Add By Qia on Dec 03 2008>
	int x;
	BDASITE *site;
	site=new BDASITE;
	sitetouse=new BDASITE;
	site->numofsites=i*j;
	SortedIndex.push_back(site);
	for (int r = 1; r <= i; r++)
		for (int c = 1; c <= j; c++)
		{
			x=(r - 1) * m_iCols;
			x=x + c - 1;
			map[x]=site;
		}
	//</Add By Qia on Dec 03 2008>
}

//##ModelId=3F01D0EA00A7
BDASites::~BDASites()
{
//	delete [] m_pBDAMap;//commented By Qia on Dec 03 2008
	
	//<Add By Qia on Dec 03 2008>
	if(map)
		delete [] map;
for(int i=0;i<SortedIndex.size();i++)
{
	BDASITE *temp;
	temp=SortedIndex.at(i);;
	delete temp;
}
delete sitetouse;
//</Add By Qia on Dec 03 2008>
}

//##ModelId=3F01D0EA00B3
BDASITE* BDASites::operator() (int i, int j)
{
	int x;

	#ifdef BOUNDSCHECK
	if (i<=0 || i> m_irows || j<=0 || j> m_iCols)
	{
		char err[80];
		sprintf(err,"BDASites::operator() (int,int)-> (%d, %d) are illegal map\
                  coordinates",i,j);
		errorSys(err,STOP);
    }
	#endif

	x=(i - 1) * m_iCols;
	x=x + j - 1;
//	return &m_pBDAMap[x]; //commented By Qia on Dec 03 2008
	return map[x];//Add By Qia on Dec 03 2008

}


//##ModelId=3F01D0EA00D4
int	BDASites::numRows()
{
	return m_iRows;
}

//##ModelId=3F01D0EA00E2
int	BDASites::numColums()
{
	return m_iCols;
}

//##ModelId=3F01D0EA00D2
void BDASites::dump()
{
	int	i, j;

	for (i = 1; i <= m_iRows; i ++)
	{
		for (j = 1; j <= m_iCols; j ++)
		{
			printf("%f ",  (*this)(i, j)->fSiteResourceDom);
		}
		printf("\n");
	}
}

//<Add By Qia on Nov 07 2008>
int BDASites::SITE_compare(int site1_x,int site1_y,int site2_x,int site2_y)
{
	int x,y;
	int result;
	BDASITE *site1, *site2;
	x=(site1_x-1)*m_iCols;
	x=x+site1_y-1;

	y=(site2_x-1)*m_iCols;
	y=y+site2_y-1;

	site1=map[x];
	site2=map[y];
	result=SITE_compare(site1,site2);
	return result;
}

void BDASites::dumpsite(BDASITE *site)
{
	printf("%d ",site->enumOutbreakZone);
	printf("%d ",site->bDeadArea);
	printf("%d ",site->bNewEpicenter);
	printf("%d ",site->cDispersal);
	printf("%d ",site->iLastBDADisturb);
	printf("%d",site->iDisturbSeverity);
	
	printf("%f ",site->fSiteResourceDom);
	printf("%f ",site->fSiteResDomMod);
	printf("%f ",site->fSV);
	printf("%f ",site->fNeighborResDom);
	
	printf("|%d \n",site->numofsites);
	printf("\n");
}

int BDASites::SITE_compare(BDASITE * site1,BDASITE * site2)
{
	
			if(site1->enumOutbreakZone>site2->enumOutbreakZone)
				return 1;
			if(site1->enumOutbreakZone<site2->enumOutbreakZone)
				return 2;
			
			if(site1->bDeadArea>site2->bDeadArea)
				return 1;
			if(site1->bDeadArea<site2->bDeadArea)
				return 2;
			
			if(site1->bNewEpicenter>site2->bNewEpicenter)
				return 1;
			if(site1->bNewEpicenter<site2->bNewEpicenter)
				return 2;

			if(site1->cDispersal>site2->cDispersal)
				return 1;
			if(site1->cDispersal<site2->cDispersal)
				return 2;

			if(site1->iLastBDADisturb>site2->iLastBDADisturb)
				return 1;
			if(site1->iLastBDADisturb<site2->iLastBDADisturb)
				return 2;

			if(site1->iDisturbSeverity>site2->iDisturbSeverity)
				return 1;
			if(site1->iDisturbSeverity<site2->iDisturbSeverity)
				return 2;
			if(site1->fSiteResourceDom>site2->fSiteResourceDom)
				return 1;
			if(site1->fSiteResourceDom<site2->fSiteResourceDom)
				return 2;

			if(site1->fSiteResDomMod>site2->fSiteResDomMod)
				return 1;
			if(site1->fSiteResDomMod<site2->fSiteResDomMod)
				return 2;

			if(site1->fSV>site2->fSV)
				return 1;
			if(site1->fSV<site2->fSV)
				return 2;

			if(site1->fNeighborResDom>site2->fNeighborResDom)
				return 1;
			if(site1->fNeighborResDom<site2->fNeighborResDom)
				return 2;
			
			
		
	return 0;
}

int BDASites::SITE_sort()
//use babble algorithm to sort the initial site list array
{
	int size,i,j;
	BDASITE *site1, *site2,*temp;
	size=SortedIndex.size();
	for(i=SortedIndex.size()-1;i>0;i--)
		{
			for(j=0;j<=i-1;j++)
				{
					site1=SortedIndex.at(j);
					site2=SortedIndex.at(j+1);
					if(SITE_compare(site1,site2)==1)
						{
							temp=SortedIndex.at(j);
							SortedIndex.at(j)=SortedIndex.at(j+1);
							SortedIndex.at(j+1)=temp;
						}
				}
		}
	return 1;
}

int BDASites::SITE_insert(int pos_sortIndex, BDASITE *site, int i, int j)
//when there is a new site during harvest, we need to 
//check if the new site already exists, if yes combine with existing one
//if not insert to the position according to sort
{
	
	int x;
	int ifexist=0, pos=0;
	BDASITE *temp;
	x=(i-1)*m_iCols;
	x=x+j-1;  
	std::vector<BDASITE *>::iterator temp_sitePtr;
	temp_sitePtr=SortedIndex.begin();
	
	SITE_LocateinSortIndex(site, &pos,&ifexist);
	if(ifexist)
		{
			map[x]=SortedIndex.at(pos);
			map[x]->numofsites++;
			//delete  site;
		}
	else
		{
			temp=new BDASITE;
			temp->bDeadArea=site->bDeadArea;
			temp->bNewEpicenter=site->bNewEpicenter;
			temp->cDispersal=site->cDispersal;
			temp->enumOutbreakZone=site->enumOutbreakZone;
			temp->fNeighborResDom=site->fNeighborResDom;
			temp->fSiteResDomMod=site->fSiteResDomMod;
			temp->fSiteResourceDom=site->fSiteResourceDom;
			temp->fSV=site->fSV;
			temp->iDisturbSeverity=site->iDisturbSeverity;
			temp->iLastBDADisturb=site->iLastBDADisturb;
			map[x]=temp;
			temp->numofsites=1;
			SortedIndex.insert(temp_sitePtr+pos, temp);
		}
	return 1;
}

int BDASites::SITE_delete(int pos_sortIndex, BDASITE *site, int i, int j)
//When a site disappears, delete it
{
	int x;
	std::vector<BDASITE *>::iterator temp_sitePtr;
	x=(i-1)*m_iCols;
	x=x+j-1;
	if(site!=SortedIndex.at(pos_sortIndex))
		return 0;
	if(site!=map[x])
		return 0;
	delete site;
	temp_sitePtr=SortedIndex.begin();
	SortedIndex.erase(temp_sitePtr+pos_sortIndex);
	return 1;	
}

int BDASites::SITE_LocateinSortIndex(BDASITE *site, int *pos, int *ifexist)
//Find if a new site exists in sorted list
//If a new site exists, find its location and set *ifexist as 1
//if this no site matches this one, find location before which new site pointer should be inserted
//By Qia Nov 07 2008
{
	int begin, end, mid;
	BDASITE *temp;
	int temp_flag;
	*ifexist=0;
	begin=0;
	end=SortedIndex.size();
	if(end==0){
		printf("No site at all wrong wrong wrong\n");
		return -1;
		}
	end--;
	mid=(begin+end)/2;
	temp=SortedIndex.at(mid);
	while(begin<end)
		{
			temp_flag=SITE_compare(site,temp);
			if(temp_flag==0)
				{
					*ifexist=1;
					*pos=mid;
					return 1;
				}
			else if(temp_flag==1)
				{
					begin=mid+1;
					mid=(begin+end)/2;
				}
			else if(temp_flag==2)
				{
					end=mid-1;
					mid=(begin+end)/2;
				}
			else
				{
					return -1;
				}
			temp=SortedIndex.at(mid);
		}
	temp_flag=SITE_compare(site,temp);
	if(temp_flag==0)
		{
			*ifexist=1;
			*pos=mid;
			return 1;
		}
	else if(temp_flag==2)
		{
			*ifexist=0;
			*pos=mid;
			return 0;
		}
	else if(temp_flag==1)
		{
			*ifexist=0;
			*pos=mid+1;
			return 0;
		}
	else
		{
			return -1;
		}
}

void BDASites::fillinSitePt(int i, int j, BDASITE *site)
//
{
	int x;
	x=(i-1)*m_iCols;
	x=x+j-1;
	map[x]=site;
}

BDASITE * BDASites::locateSitePt(int i, int j)
//
{
	int x;
	x=(i-1)*m_iCols;
	x=x+j-1;
	return map[x];
}


void BDASites::BefStChg(int i, int j)
//Before Site Change
//This function back up a site and following changes are based on this seprated site
//sort vector is not touched here
{
	BDASITE *temp;
	temp=locateSitePt(i,j);

	sitetouse->bDeadArea=temp->bDeadArea;
	sitetouse->bNewEpicenter=temp->bNewEpicenter;
	sitetouse->cDispersal=temp->cDispersal;
	sitetouse->enumOutbreakZone=temp->enumOutbreakZone;
	sitetouse->fNeighborResDom=temp->fNeighborResDom;
	sitetouse->fSiteResDomMod=temp->fSiteResDomMod;
	sitetouse->fSiteResourceDom=temp->fSiteResourceDom;
	sitetouse->fSV=temp->fSV;
	sitetouse->iDisturbSeverity=temp->iDisturbSeverity;
	sitetouse->iLastBDADisturb=temp->iLastBDADisturb;
	
	if(temp->numofsites==1)
		{
			int pos,ifexist=0;
			SITE_LocateinSortIndex(sitetouse,&pos,&ifexist);
			if(ifexist)
				{
					std::vector<BDASITE *>::iterator temp_sitePtr;
					temp_sitePtr=SortedIndex.begin();
					SortedIndex.erase(temp_sitePtr+pos);
					delete temp;
				}
			else
				{
					printf("num of vectors %d\n",SortedIndex.size());
					printf("ERROR ERROR ERROR ERROR!!~~~%d\n",pos);
					//
					dumpsite(sitetouse);
					dumpsite(temp);
					dumpsite(SortedIndex.at(0));
					dumpsite(SortedIndex.at(1));
					dumpsite(SortedIndex.at(pos-2));
					dumpsite(SortedIndex.at(pos-1));
					dumpsite(SortedIndex.at(pos));
					dumpsite(SortedIndex.at(pos+1));
					dumpsite(SortedIndex.at(pos+2));
				}
		}
	else if(temp->numofsites<=0)
		{
			printf("NO NO NO NO NO\n");
		}
	else
		{
			temp->numofsites--;
		}
	fillinSitePt(i,j,sitetouse);
	return ;
}
void BDASites::AftStChg(int i,int j)
//After Site Change
//This function does combination and delete of the seprated site made by BefStChg(int i, int j)
//insert this site to the sorted vector
{
	SITE_insert(0,sitetouse,i,j);
	return ;
}
//</Add By Qia on Nov 07 2008>


