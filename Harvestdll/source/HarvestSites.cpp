/*

Name:			BDASites.cpp 

Description:	BDASites

Input:			

Output:			

Date:			Oct. 16, 2002

Last Mod:		

*/
#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>

#include <crtdbg.h>

#include <stdlib.h>

#include <string.h>



//add by Vera

#include "sites.h"

#include "HarvestSites.h"

#include "GlobalVariables.h"

#include "system1.h"

//


double HARVESTSites::GetValueHarvestBA(int i,int j)

{

	int x;

	x=(i - 1) * m_iCols;

	x=x + j - 1;

	return BA_harvest_output[x];

}

int		HARVESTSites::SetValueHarvestBA(int i,int j,double value){

	int x;

	x=(i - 1) * m_iCols;

	x=x + j - 1;

	BA_harvest_output[x] = value;

	return 0;

}



int		HARVESTSites::AddMoreValueHarvestBA(int i,int j,double value){

	int x;

	x=(i - 1) * m_iCols;

	x=x + j - 1;

	BA_harvest_output[x] += value;

	return 0;

}

double HARVESTSites::GetValueHarvestBA_spec(int i,int j,int spec)

{

	int x;

	x=(i - 1) * m_iCols;

	x=x + j - 1;

	return BA_harvest_output_spec[spec][x];

}

int		HARVESTSites::SetValueHarvestBA_spec(int i,int j,int spec,double value){

	int x;

	x=(i - 1) * m_iCols;

	x=x + j - 1;

	BA_harvest_output_spec[spec][x] = value;

	return 0;

}



int		HARVESTSites::AddMoreValueHarvestBA_spec(int i,int j,int spec,double value){

	int x;

	x=(i - 1) * m_iCols;

	x=x + j - 1;

	BA_harvest_output_spec[spec][x] += value;

	return 0;

}

int		HARVESTSites::clearValueHarvestBA(){

	int r =m_iRows ;

	int c =m_iCols;

	int i,j,x;

	for (i = 1; i <= r; i++)

		for (j = 1; j <= c; j++)

		{

			x=(i - 1) * m_iCols;

			x=x + j - 1;

			BA_harvest_output[x] =0.0;

		}

	for(int i_spec=0;i_spec< pCoresites->specNum ;i_spec++){

		for (i = 1; i <= r; i++)

			for (j = 1; j <= c; j++)

			{

				x=(i - 1) * m_iCols;

				x=x + j - 1;

				BA_harvest_output_spec[i_spec][x] =0.0;

			}

	}

	return 1;

}

HARVESTSites::HARVESTSites()

{

	m_iRows = 0;

	m_iCols = 0;

	//m_pHarvestMap = NULL; //commented By Qia on Nov 07 2008

}





HARVESTSites::HARVESTSites(int r, int c)
{
	int x;



	m_iRows = r;

	m_iCols = c;

	map = new HARVESTSite*[r*c];//Add by Qia Nov 07 2008

	/*for (int i = 0; i < r*c; i++)
	{
		map[i] = new HARVESTSite();
	}*/

	BA_harvest_output = new double[r*c];

	BA_harvest_output_spec = new double *[pCoresites->specNum];

	for (int i = 0; i < pCoresites->specNum; i++)
	{

		BA_harvest_output_spec[i] = new double[r*c];

	}

	//printf("LandisPro harvest map allocated\n");
	//fflush(stdout);

	if (map == NULL)
		cerr << "No Memory for harvestSite map" << endl;
	//fflush(stdout);

	HARVESTSite *site;

	sitetouse = new HARVESTSite;

	int classsize = sizeof(HARVESTSite);

	//SortedIndex.push_back(site);

	for (int i = 1; i <= r; i++)
	{

		for (int j = 1; j <= c; j++)
		{

			site = new HARVESTSite;

			site->lastHarvest = 0;

			site->harvestType = 0;

			site->harvestExpirationDecade = 0;

			site->itsMaxAge = 0;

			site->updateFlag = 1;

			site->numofsites = r*c;
			
			x = (i - 1) * m_iCols;

			x = x + j - 1;

		/*	map[x]->lastHarvest = 0;

			map[x]->harvestType = 0;

			map[x]->harvestExpirationDecade = 0;

			map[x]->itsMaxAge = 0;

			map[x]->updateFlag = 1;

			map[x]->numofsites = r*c;*/

			map[x] = site;

			BA_harvest_output[x] = 0.0;

		}

	}

	for (int i_spec = 0; i_spec < pCoresites->specNum; i_spec++)
	{
		for (int i = 1; i <= r; i++)
		{
			for (int j = 1; j <= c; j++)
			{
				x = (i - 1) * m_iCols;

				x = x + j - 1;

				BA_harvest_output_spec[i_spec][x] = 0.0;
			}
		}
	}//done for (int i_spec = 0; i_spec < pCoresites->specNum; i_spec++)

}





HARVESTSites::~HARVESTSites()

{ 
	if(map){

			int x;

			int r = m_iRows;

			int c = m_iCols;

			HARVESTSite *site;

			for (int i = 1; i <= r; i++)
			{

				for (int j = 1; j <= c; j++)

				{
					x=(i - 1) * m_iCols;

					x=x + j - 1;

					site = map[x];

					if (site)

						delete site;

				/*	if (map[x])

						delete [] map[x];
*/
				}

			}

	delete [] map; //changed By Qia on Nov 07 2008

}

 //<Add By Qia on Dec 03 2008>

for(int i=0;i<SortedIndex.size();i++)

{

	HARVESTSite *temp;

	temp=SortedIndex.at(i);;

	delete temp;

}

if(sitetouse)

	delete sitetouse;

//</Add By Qia on Dec 03 2008>

if(BA_harvest_output)

delete BA_harvest_output;

if(BA_harvest_output_spec){

	for(int i = 0;i<pCoresites->specNum;i++){

		if(BA_harvest_output_spec[i])

		delete BA_harvest_output_spec[i];

	}

	delete BA_harvest_output_spec;

}

}





HARVESTSite* HARVESTSites::operator() (int i, int j)

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

	assert(i >= 1 && i <= m_iRows && j >= 1 && j <= m_iCols);

	//return &m_pHarvestMap[x]; //landis 4.0

	return map[x]; // Add by Qia Oct 07 2008



}







int	HARVESTSites::numRows()

{

	return m_iRows;

}





int	HARVESTSites::numColums()

{

	return m_iCols;

}



void HARVESTSites::dump()

{

	int	i, j;



	for (i = 1; i <= m_iRows; i ++)

	{

		for (j = 1; j <= m_iCols; j ++)

		{

//			printf("%f ",  (*this)(i, j)->fSiteResourceDom);

		}

		printf("\n");
		fflush(stdout);

	}

}



//<Add By Qia on Nov 07 2008>

int HARVESTSites::SITE_compare(int site1_x,int site1_y,int site2_x,int site2_y)

{

	int x,y;

	int result;

	HARVESTSite *site1, *site2;

	x=(site1_x-1)*m_iCols;

	x=x+site1_y-1;



	y=(site2_x-1)*m_iCols;

	y=y+site2_y-1;



	site1=map[x];

	site2=map[y];

	result=SITE_compare(site1,site2);

	return result;

}

int HARVESTSites::SITE_compare(HARVESTSite * site1,HARVESTSite * site2)

{

	

	

			if(site1->itsMaxAge>site2->itsMaxAge)

				return 1;

			if(site1->itsMaxAge<site2->itsMaxAge)

				return 2;



			if(site1->updateFlag>site2->updateFlag)

				return 1;

			if(site1->updateFlag<site2->updateFlag)

				return 2;



			if(site1->harvestType>site2->harvestType)

				return 1;

			if(site1->harvestType<site2->harvestType)

				return 2;



			if(site1->lastHarvest>site2->lastHarvest)

				return 1;

			if(site1->lastHarvest<site2->lastHarvest)

				return 2;



			if(site1->harvestExpirationDecade>site2->harvestExpirationDecade)

				return 1;

			if(site1->harvestExpirationDecade<site2->harvestExpirationDecade)

				return 2;

		

	return 0;

}



int HARVESTSites::SITE_sort()

//use babble algorithm to sort the initial site list array

{

	int size,i,j;

	HARVESTSite *site1, *site2,*temp;

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



int HARVESTSites::SITE_insert(int pos_sortIndex, HARVESTSite *site, int i, int j)

//when there is a new site during harvest, we need to 

//check if the new site already exists, if yes combine with existing one

//if not insert to the position according to sort

{

	

	int x;

	int ifexist=0, pos=0;

	HARVESTSite *temp;

	x=(i-1)*m_iCols;

	x=x+j-1;  

	std::vector<HARVESTSite *>::iterator temp_sitePtr;

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

			temp= new HARVESTSite;

			*temp=*site;

			temp->numofsites=1;

			map[x]=temp;

			SortedIndex.insert(temp_sitePtr+pos, temp);

		}

	return 1;

}



int HARVESTSites::SITE_delete(int pos_sortIndex, HARVESTSite *site, int i, int j)

//When a site disappears, delete it

{

	int x;

	std::vector<HARVESTSite *>::iterator temp_sitePtr;

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



int HARVESTSites::SITE_LocateinSortIndex(HARVESTSite *site, int *pos, int *ifexist)

//Find if a new site exists in sorted list

//If a new site exists, find its location and set *ifexist as 1

//if this no site matches this one, find location before which new site pointer should be inserted

//By Qia Nov 07 2008

{

	int begin, end, mid;

	HARVESTSite *temp;

	int temp_flag;

	*ifexist=0;

	begin=0;

	end=SortedIndex.size();

	if(end==0){

		printf("No site at all wrong wrong wrong\n");
		fflush(stdout);

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



void HARVESTSites::fillinSitePt(int i, int j, HARVESTSite *site)

//

{

	int x;

	x=(i-1)*m_iCols;

	x=x+j-1;

	map[x]=site;

}



HARVESTSite * HARVESTSites::locateSitePt(int i, int j)

//

{

	int x;

	x=(i-1)*m_iCols;

	x=x+j-1;

	return map[x];

}



void HARVESTSites::BefStChg(int i, int j)

//Before Site Change

//This function back up a site and following changes are based on this seprated site

//sort vector is not touched here

{

	return ;

	HARVESTSite *temp;

	temp=locateSitePt(i,j);

	*sitetouse=*temp;

	

	if(temp->numofsites==1)

		{

			int pos,ifexist=0;

			SITE_LocateinSortIndex(sitetouse,&pos,&ifexist);

			if(ifexist)

				{

					std::vector<HARVESTSite *>::iterator temp_sitePtr;

					temp_sitePtr=SortedIndex.begin();

					SortedIndex.erase(temp_sitePtr+pos);

					delete temp;

				}

			else

				{

					printf("num of vectors %d\n",SortedIndex.size());
					fflush(stdout);

					printf("ERROR ERROR ERROR ERROR!!~~~%d\n",pos);		
					fflush(stdout);

				}

		}

	else if(temp->numofsites<=0)

		{

			printf("NO NO NO NO NO\n");
			fflush(stdout);

		}

	else

		{

			temp->numofsites--;

		}

	//sitetouse->numofsites=1;

	fillinSitePt(i,j,sitetouse);

	return ;

}

void HARVESTSites::AftStChg(int i,int j)

//After Site Change

//This function does combination and delete of the seprated site made by BefStChg(int i, int j)

//insert this site to the sorted vector

{	

	return ;

	SITE_insert(0,sitetouse,i,j);

	return ;

}

//</Add By Qia on Nov 07 2008>



////////////////////////////////////////////HarvestSite//////////////////////////////////////////////



void HARVESTSite::setUpdateFlag() {

    updateFlag = 1;

}



/*

void HarvestSite::update() {

    if (updateFlag) {

        AGELIST* a;

        itsMaxAge = 0;

        for (int i = 1; i <= number(); i++) {

            a = (AGELIST*) (*this)(i);

            itsMaxAge = max(itsMaxAge, a->oldest());

        }

        updateFlag = 0;

    }

}

*/



HARVESTSite& HARVESTSite::operator=(const HARVESTSite& site)

{

	itsMaxAge=site.itsMaxAge;

	updateFlag=site.updateFlag;

	harvestType=site.harvestType;

	lastHarvest=site.lastHarvest;

	harvestExpirationDecade=site.harvestExpirationDecade;

	numofsites=1;

	return *this;

}

void HARVESTSite::update(int iRol, int iCol) 

{

    if (updateFlag) 

	{

        AGELIST* a;

        itsMaxAge = 0;

        for (int i = 1; i <= (*pCoresites)(iRol, iCol)->number(); i++) 

		{

            a = (AGELIST*) (*(*pCoresites)(iRol, iCol))(i);

            itsMaxAge = max(itsMaxAge, a->oldest());

        }

        updateFlag = 0;

    }

}



int HARVESTSite::getHarvestType() {

    return (int) harvestType;

}



int HARVESTSite::getHarvestDecade() {

    return (int) lastHarvest;

}



int HARVESTSite::getMaxAge(int iRol, int iCol) {

    update(iRol, iCol); 

    return itsMaxAge;

}



int HARVESTSite::canBeHarvested(int iRol, int iCol) {

    int result;

    result = pCoresites->locateLanduPt(iRol,iCol)->active();
	//Jacob result = pCoresites->locateLanduPt(iRol,iCol)->active() && (currentDecade >= harvestExpirationDecade);

	//Original landis4.0: (*pCoresites)(iRol, iCol)->landUnit->active()

	//Changed By Qia Oct 13 2008

    return result;

}



int HARVESTSite::wasRecentlyHarvested() {

    int result;

//  result = lastHarvest > 0 && (currentDecade - lastHarvest <= parameters->harvestDecadeSpan); Modified by Vera

    result = lastHarvest > 0 && (currentDecade - lastHarvest <= iParamharvestDecadeSpan);

	//printf("lastha: %d, currentDcd: %d, DecadeSpan: %d\n",lastHarvest,currentDecade,iParamharvestDecadeSpan);

    return result;

}