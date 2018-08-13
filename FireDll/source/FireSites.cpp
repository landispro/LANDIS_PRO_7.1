/********************************************

Name:			FireSites.cpp 

Description:	FireSites

Input:			

Output:			

Date:			Feb. 18, 2004

Last Mod:		Feb. 18

*******************************************/



#include <stdlib.h>

#include <string.h>

#include "system1.h"

#include "error.h"

#include "FireSites.h"



//<Add By Qia on Nov 24 2008>

#include <vector>

#include <list>

//</Add By Qia on Nov 24 2008>





CFireSites::CFireSites()

{

	m_iRows = 0;

	m_iCols = 0;

	//m_pFireLAND = NULL;//commented By Qia on Nov 24 2008

}



CFireSites::CFireSites(int i, int j)

{

	m_iRows = i;

	m_iCols = j;

	//m_pFireLAND = new FIRESITE[i*j]; //commented By Qia on Nov 24 2008

	map=new FIRESITE*[i*j];//Add By Qia on Nov 24 2008

	printf("LandisPro fire map allocated\n");

	FIRESITE *temp;

	int x;

	sitetouse = new FIRESITE;

	temp=new FIRESITE;

	temp->FRUIndex=0;

	temp->DEM=0;

	temp->numofsites=i*j;

	SortedIndex.push_back(temp);

	for (i = 1; i <= m_iRows; i++)

		for (j = 1; j <= m_iCols; j++){

			//this->operator ()(i,j)->DEM = 0;

			x=(i - 1) * m_iCols;

			x=x + j - 1;

			map[x]=temp;

			}

			

}



CFireSites::~CFireSites()

{

	//if (m_pFireLAND)

		//delete [] m_pFireLAND;  //commented By Qia on Nov 24 2008

	if(map) delete [] map; //Add By Qia on Nov 24 2008

	//<Add By Qia on Nov 24 2008>

	for(int i=0;i<SortedIndex.size();i++)

	{

		FIRESITE *temp;

		temp=SortedIndex.at(i);

		delete temp;

	}

	//</Add By Qia on Nov 24 2008>

	delete sitetouse;

}



FIRESITE* CFireSites::operator() (int i, int j)

{

	int x;

	

	if (i<=0 || i> m_iRows || j<=0 || j> m_iCols)

	{

		char err[80];

		sprintf(err,"CFireSites::operator() (int,int)-> (%d, %d) are illegal map\
                  coordinates",i,j);

		errorSys(err,STOP);

    }	



	x=(i - 1) * m_iCols;

	x=x + j - 1;

	return map[x];

}



int	CFireSites::numRows()

{

	return m_iRows;

}

void CFireSites::create_FireRegimeUnitsListByIndex()
{
	int i = 0, j = 0;
	int x;
	int max_FRUIndex = 0;
	for (i=1;i<=m_iRows;i++)
	{
		for (j=1;j<=m_iCols;j++)
		{	
			x=(i - 1) * m_iCols;
			x=x + j - 1;
			LDPOINT p(j,i);
			FireRegimeUnitsList[map[x]->FRUIndex].push_back(p);
		}
	}
	for(i=0;i<70000;i++){
		FireRegimeCurrentIndex[i] = 0;
	}
}


LDPOINT CFireSites::return_a_point_from_index(int index, int cellNo){
	if(cellNo>FireRegimeUnitsList[index].size()){
		cout << "Fire index error -" << index << "\n";
		errorSys("Fire index error, contact development team\n",STOP);
	}
	cellNo--;
	LDPOINT p = FireRegimeUnitsList[index].at(cellNo);
	std::vector<LDPOINT>::iterator sitePtr;
	sitePtr=FireRegimeUnitsList[index].begin();
	FireRegimeUnitsList[index].erase(sitePtr+cellNo);
	
	FireRegimeCurrentIndex[index] = (FireRegimeCurrentIndex[index]+1)%70000;
	return p;
}


int	CFireSites::numColumns()

{

	return m_iCols;

}



int CFireSites::number()

//This will return the total number of sites.



{

	return numRows()*numColumns();

}



//<Add by Qia on Nov 24 2008>

int CFireSites::SITE_compare(int site1_x,int site1_y,int site2_x,int site2_y)

{

	int x,y;

	int result;

	FIRESITE *site1, *site2;

	x=(site1_x-1)*m_iCols;

	x=x+site1_y-1;



	y=(site2_x-1)*m_iCols;

	y=y+site2_y-1;



	site1=map[x];

	site2=map[y];

	result=SITE_compare(site1,site2);

	return result;

}

int CFireSites::SITE_compare(FIRESITE * site1,FIRESITE * site2)

{

	if(site1->FRUIndex>site2->FRUIndex)

		return 1;

	if(site1->FRUIndex<site2->FRUIndex)

		return 2;

	if(site1->DEM>site2->DEM)

		return 1;

	if(site1->DEM<site2->DEM)

		return 2;

	return 0;

}

//</Add by Qia on Oct 08 2008>



//<Add by Qia on Oct 08 2008>

void CFireSites::fillinSitePt(int i, int j, FIRESITE *site)

//

{

	int x;

	x=(i-1)*m_iCols;

	x=x+j-1;

	map[x]=site;

}

FIRESITE * CFireSites::locateSitePt(int i, int j)

//

{

	int x;

	x=(i-1)*m_iCols;

	x=x+j-1;

	return map[x];

}





int CFireSites::SITE_delete(int pos_sortIndex, FIRESITE *site, int i, int j)

//When a site disappears, delete it

{

	int x;

	std::vector<FIRESITE *>::iterator temp_sitePtr;

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



int CFireSites::SITE_insert(int pos_sortIndex, FIRESITE *site, int i, int j)

//when there is a new site during succession or whatever, we need to 

//check if the new site already exists, if yes combine with existing one

//if not insert to the position according to sort

{

	

	int x;

	int ifexist=0, pos=0;

	FIRESITE *temp;

	x=(i-1)*m_iCols;

	x=x+j-1;  

	std::vector<FIRESITE *>::iterator temp_sitePtr;

	temp_sitePtr=SortedIndex.begin();

	

	SITE_LocateinSortIndex(site, &pos,&ifexist);

	if(ifexist)

		{

			map[x]=SortedIndex.at(pos);

			map[x]->numofsites++;

			//delete  site;

		}

	else

		{	temp=new FIRESITE;

			temp->FRUIndex=site->FRUIndex;

	temp->DEM=site->DEM;

			temp->numofsites=1;

			map[x]=temp;

			SortedIndex.insert(temp_sitePtr+pos, temp);

		}

	return 1;

}



int CFireSites::SITE_LocateinSortIndex(FIRESITE *site, int *pos, int *ifexist)

//Find if a new site exists in sorted list

//If a new site exists, find its location and set *ifexist as 1

//if this no site matches this one, find location before which new site pointer should be inserted

//By Qia Oct 09 2008

{

	int begin, end, mid;

	FIRESITE *temp;

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

int CFireSites::SITE_sort()

//use babble algorithm to sort the initial site list array

{

	int size,i,j;

	FIRESITE *site1, *site2,*temp;

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



void CFireSites::BefStChg(int i, int j)

//Before Site Change

//This function back up a site and following changes are based on this seprated site

//sort vector is not touched here

{

	FIRESITE *temp;

	temp=locateSitePt(i,j);

	sitetouse->FRUIndex=temp->FRUIndex;

	sitetouse->DEM=temp->DEM;

	

	if(temp->numofsites==1)

		{

			int pos,ifexist=0;

			SITE_LocateinSortIndex(sitetouse,&pos,&ifexist);

			if(ifexist)

				{

					std::vector<FIRESITE *>::iterator temp_sitePtr;

					temp_sitePtr=SortedIndex.begin();

					SortedIndex.erase(temp_sitePtr+pos);

					delete temp;

				}

			else

				{

					printf("num of vectors %d\n",SortedIndex.size());

					printf("ERROR ERROR ERROR ERROR!!~~~%d\n",pos);

					

				}

		}

	else if(temp->numofsites<=0)

		{

			printf("FIRESITE NO NO NO NO NO\n");

		}

	else

		{

			temp->numofsites--;

		}

	fillinSitePt(i,j,sitetouse);

	return ;

}

void CFireSites::AftStChg(int i,int j)

//After Site Change

//This function does combination and delete of the seprated site made by BefStChg(int i, int j)

//insert this site to the sorted vector

{

	SITE_insert(0,sitetouse,i,j);

	return ;

}

//</Add By Qia on Nov 24 2008>





