#include <stdlib.h>

#include <stdio.h>

#include <iostream>

#include "system1.h"

#include "error.h"

#include "species.h"

#include "landus.h"

#include "site.h"

#include "sites.h"



//<Add By Qia on Oct 08 2008>

#include <vector>

#include <list>

//</Add By Qia on Oct 08 2008>

#define MaximumAvailableSeeds 100000000



#define TPA		0

#define BA		1

#define Bio		2

#define Car		3

#define IV		4

#define Seeds	5

#define RDensity	6

#define DBH 7



///////////////////////////////////////////////////////////////////////////////

//				SITES CLASS CODE			     //

///////////////////////////////////////////////////////////////////////////////



SITES::SITES(int species, int i, int j)

//Constructor.  This will dimension the size of the map to i rows and j

//columns.  The number of species is set to species.



{

SPECIES junk(species);

//map=new SITE[i*j];//commented by Qia on Oct 10 2008

Pro0or401=1;

map70=new SITE[i*j]; //Add by Qia Oct 10 2008

//map_landtype=new LANDUNIT*[i*j];//Add by Qia Oct 10 2008

//sitetouse=new SITE;//Add By Qia on Dec 19 2008



//<Add By Qia on June 29 2009>

//SeedRain=new float[i*j];

//GrowthRates=new float[i*j];

//MortalityRates=new float[i*j];

//</Add By Qia on June 29 2009>

rows=i;

columns=j;

}





SITES::SITES()

//Constructor.  The maximum number of species will be set to species.

//The map dimensions will can be set by a call to SITES::dim after

//construction.



{

//SPECIES();



map70=NULL;

map_landtype=NULL;

SeedRain=NULL;

GrowthRates=NULL;

MortalityRates=NULL;

Volume=NULL;

Pro0or401=1;

rows=0;

columns=0;



BiomassFireCost=NULL;

CarbonFireCost=NULL;



BiomassHarvestCost=NULL;

CarbonHarvestCost=NULL;



BiomassFuelCost=NULL;

CarbonFuelCost=NULL;



BiomassBDACost=NULL;

CarbonBDACost=NULL;



BiomassWindCost=NULL;

CarbonWindCost=NULL;





int Fireflag=0;



int Harvestflag=0;



int Fuelflag=0;



int BDAflag=0;



int Windflag=0;



int flagAgeRangeOutput=0;



//<Add By Qia on April 23 2010>

OutputGeneralFlagArray = NULL;

OutputAgerangeFlagArray = NULL;

SpeciesAgerangeArray = NULL;

AgeDistStat_Year = NULL;

AgeDistStat_AgeRange = NULL;

//</Add By Qia on April 23 2010>



}



SITES::~SITES()

//Destructor.



{

if(map70)

	delete [] map70; //Nim: added []

if(map_landtype)

	delete [] map_landtype; //Add By Qia Oct 13 2008

//<Add By Qia Oct 14 2008>

//<Add By Qia on June 29 2009>

if(SeedRain)

	delete [] SeedRain;

if(GrowthRates)

	delete [] GrowthRates;

if(MortalityRates)

	delete [] MortalityRates;
for(int i = 0;i<GrowthRates_file.size();i++){
	delete [] GrowthRates_file.at(i);
}
for(int i = 0;i<MortalityRates_file.size();i++){
	delete [] MortalityRates_file.at(i);
}
for(int i = 0;i<Volume_file.size();i++){
	delete [] Volume_file.at(i);
}
if(Volume)

	delete [] Volume;

//</Add By Qia on June 29 2009>



//<Add By Qia on April 23 2010>

if(OutputGeneralFlagArray)

	delete OutputGeneralFlagArray;

if(OutputAgerangeFlagArray)

	delete OutputAgerangeFlagArray;

if(SpeciesAgerangeArray)

	delete SpeciesAgerangeArray;

//</Add By Qia on April 23 2010>

//<Add By Qia on Dec 29 2010>

if(AgeDistStat_AgeRange)

	delete AgeDistStat_AgeRange;

if(AgeDistStat_Year)

	delete AgeDistStat_Year;

//</Add By Qia on Dec 29 2010>

if(BiomassFireCost)

	delete BiomassFireCost;

if(CarbonFireCost)

	delete CarbonFireCost;



if(BiomassHarvestCost)

	delete BiomassHarvestCost;

if(CarbonHarvestCost)

	delete CarbonHarvestCost;



if(BiomassFuelCost)

	delete BiomassFuelCost;

if(CarbonFuelCost)

	delete CarbonFuelCost;



if(BiomassBDACost)

	delete BiomassBDACost;

if(CarbonBDACost)

	delete CarbonBDACost;



if(BiomassWindCost)

	delete BiomassWindCost;

if(CarbonWindCost)

	delete CarbonWindCost;





if(sitetouse)

delete sitetouse;

if(biomassData)

delete biomassData;



int sum=0;

for(int i=0;i<SortedIndex.size();i++)

{

	SITE *temp;

	temp=SortedIndex.at(i);;

	delete temp;

	

}

//</Add By Qia Oct 14 2008>

}



//<Add By Qia on Feb 09 2010>

void SITES::Wind70outputdim()

{

	BiomassWindCost=new double[rows*columns];

	CarbonWindCost=new double[rows*columns];

	Windflag=1;

	memset(BiomassWindCost, 0, rows*columns);

	memset(CarbonWindCost, 0, rows*columns);

}

void SITES::Harvest70outputdim()

{

	BiomassHarvestCost=new double[rows*columns];

	CarbonHarvestCost=new double[rows*columns];

	Harvestflag=1;

	memset(BiomassHarvestCost, 0, rows*columns);

	memset(CarbonHarvestCost, 0, rows*columns);

}

void SITES::Fire70outputdim()

{

	BiomassFireCost=new double[rows*columns];

	CarbonFireCost=new double[rows*columns];

	Fireflag=1;

	memset(BiomassFireCost, 0, rows*columns);

	memset(CarbonFireCost, 0, rows*columns);

}

void SITES::Fuel70outputdim()

{

	BiomassFuelCost=new double[rows*columns];

	CarbonFuelCost=new double[rows*columns];

	Fuelflag=1;

	memset(BiomassFuelCost, 0, rows*columns);

	memset(CarbonFuelCost, 0, rows*columns);

}

void SITES::BDA70outputdim()

{

	BiomassBDACost=new double[rows*columns];

	CarbonBDACost=new double[rows*columns];

	BDAflag=1;

	memset(BiomassBDACost, 0, rows*columns);

	memset(CarbonBDACost, 0, rows*columns);

}



double SITES::Wind70outputGetBiomassvalue(int i, int j)

{

int x;

#ifdef BOUNDSCHECK

if (i<=0 || i>rows || j<=0 || j>columns)

    {

     char err[80];

     sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

                  coordinates",i,j);

     errorSys(err,STOP);

    }

#endif

x=(i-1)*columns;

x=x+j-1;

//return &map[x]; //landis 4.0



return BiomassWindCost[x]; // Add by Qia Oct 07 2008

}

double SITES::Harvest70outputGetBiomassvalue(int i, int j)

{

	int x;

#ifdef BOUNDSCHECK

	if (i<=0 || i>rows || j<=0 || j>columns)

		{

		 char err[80];

		 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

					  coordinates",i,j);

		 errorSys(err,STOP);

		}

#endif

	x=(i-1)*columns;

	x=x+j-1;

	//return &map[x]; //landis 4.0

	

	return BiomassHarvestCost[x]; // Add by Qia Oct 07 2008



}

double SITES::Fire70outputGetBiomassvalue(int i, int j)

{

	int x;

#ifdef BOUNDSCHECK

	if (i<=0 || i>rows || j<=0 || j>columns)

		{

		 char err[80];

		 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

					  coordinates",i,j);

		 errorSys(err,STOP);

		}

#endif

	x=(i-1)*columns;

	x=x+j-1;

	//return &map[x]; //landis 4.0

	

	return BiomassFireCost[x]; // Add by Qia Oct 07 2008



}

double SITES::Fuel70outputGetBiomassvalue(int i, int j)

{

		int x;

#ifdef BOUNDSCHECK

	if (i<=0 || i>rows || j<=0 || j>columns)

		{

		 char err[80];

		 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

					  coordinates",i,j);

		 errorSys(err,STOP);

		}

#endif

	x=(i-1)*columns;

	x=x+j-1;

	//return &map[x]; //landis 4.0

	

	return BiomassFuelCost[x]; // Add by Qia Oct 07 2008

}

double SITES::BDA70outputGetBiomassvalue(int i, int j)

{

		int x;

#ifdef BOUNDSCHECK

	if (i<=0 || i>rows || j<=0 || j>columns)

		{

		 char err[80];

		 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

					  coordinates",i,j);

		 errorSys(err,STOP);

		}

#endif

	x=(i-1)*columns;

	x=x+j-1;

	//return &map[x]; //landis 4.0

	

	return BiomassBDACost[x]; // Add by Qia Oct 07 2008

}



double SITES::Wind70outputGetCarbonvalue(int i, int j)

{

		int x;

#ifdef BOUNDSCHECK

		if (i<=0 || i>rows || j<=0 || j>columns)

			{

			 char err[80];

			 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

						  coordinates",i,j);

			 errorSys(err,STOP);

			}

#endif

		x=(i-1)*columns;

		x=x+j-1;

		//return &map[x]; //landis 4.0

		

		return CarbonWindCost[x]; // Add by Qia Oct 07 2008



}

double SITES::Harvest70outputGetCarbonvalue(int i, int j)

	{

		int x;

#ifdef BOUNDSCHECK

		if (i<=0 || i>rows || j<=0 || j>columns)

			{

			 char err[80];

			 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

						  coordinates",i,j);

			 errorSys(err,STOP);

			}

#endif

		x=(i-1)*columns;

		x=x+j-1;

		//return &map[x]; //landis 4.0

		

		return CarbonHarvestCost[x]; // Add by Qia Oct 07 2008



}

double SITES::Fire70outputGetCarbonvalue(int i, int j)

	{

			int x;

#ifdef BOUNDSCHECK

			if (i<=0 || i>rows || j<=0 || j>columns)

				{

				 char err[80];

				 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

							  coordinates",i,j);

				 errorSys(err,STOP);

				}

#endif

			x=(i-1)*columns;

			x=x+j-1;

			//return &map[x]; //landis 4.0

			

			return CarbonFireCost[x]; // Add by Qia Oct 07 2008

	

	}



double SITES::Fuel70outputGetCarbonvalue(int i, int j)

	{

		int x;

#ifdef BOUNDSCHECK

		if (i<=0 || i>rows || j<=0 || j>columns)

			{

			 char err[80];

			 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

						  coordinates",i,j);

			 errorSys(err,STOP);

			}

#endif

		x=(i-1)*columns;

		x=x+j-1;

		//return &map[x]; //landis 4.0

		

		return CarbonFuelCost[x]; // Add by Qia Oct 07 2008



}

double SITES::BDA70outputGetCarbonvalue(int i, int j)

	{

		int x;

#ifdef BOUNDSCHECK

		if (i<=0 || i>rows || j<=0 || j>columns)

			{

			 char err[80];

			 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

						  coordinates",i,j);

			 errorSys(err,STOP);

			}

#endif

		x=(i-1)*columns;

		x=x+j-1;

		//return &map[x]; //landis 4.0

		

		return CarbonBDACost[x]; // Add by Qia Oct 07 2008



}

/////////////////////////////////////////////////////



void SITES::Wind70outputIncreaseBiomassvalue(int i,int j,double value)

{

int x;

#ifdef BOUNDSCHECK

if (i<=0 || i>rows || j<=0 || j>columns)

    {

     char err[80];

     sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

                  coordinates",i,j);

     errorSys(err,STOP);

    }

#endif

x=(i-1)*columns;

x=x+j-1;

//return &map[x]; //landis 4.0



BiomassWindCost[x]+=value; // Add by Qia Oct 07 2008

}

void SITES::Harvest70outputIncreaseBiomassvalue(int i, int j, double value)

{

	int x;

#ifdef BOUNDSCHECK

	if (i<=0 || i>rows || j<=0 || j>columns)

		{

		 char err[80];

		 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

					  coordinates",i,j);

		 errorSys(err,STOP);

		}

#endif

	x=(i-1)*columns;

	x=x+j-1;

	//return &map[x]; //landis 4.0

	

	BiomassHarvestCost[x]+=value; // Add by Qia Oct 07 2008



}

void SITES::Fire70outputIncreaseBiomassvalue(int i, int j, double value)

{

	int x;

#ifdef BOUNDSCHECK

	if (i<=0 || i>rows || j<=0 || j>columns)

		{

		 char err[80];

		 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

					  coordinates",i,j);

		 errorSys(err,STOP);

		}

#endif

	x=(i-1)*columns;

	x=x+j-1;

	//return &map[x]; //landis 4.0

	

	BiomassFireCost[x]+=value; // Add by Qia Oct 07 2008



}

void SITES::Fuel70outputIncreaseBiomassvalue(int i, int j, double value)

{

		int x;

#ifdef BOUNDSCHECK

	if (i<=0 || i>rows || j<=0 || j>columns)

		{

		 char err[80];

		 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

					  coordinates",i,j);

		 errorSys(err,STOP);

		}

#endif

	x=(i-1)*columns;

	x=x+j-1;

	//return &map[x]; //landis 4.0

	

	BiomassFuelCost[x]+=value; // Add by Qia Oct 07 2008

}

void SITES::BDA70outputIncreaseBiomassvalue(int i, int j, double value)

{

		int x;

#ifdef BOUNDSCHECK

	if (i<=0 || i>rows || j<=0 || j>columns)

		{

		 char err[80];

		 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

					  coordinates",i,j);

		 errorSys(err,STOP);

		}

#endif

	x=(i-1)*columns;

	x=x+j-1;

	//return &map[x]; //landis 4.0

	

	BiomassBDACost[x]+=value; // Add by Qia Oct 07 2008

}



void SITES::Wind70outputIncreaseCarbonvalue(int i, int j, double value)

{

		int x;

#ifdef BOUNDSCHECK

		if (i<=0 || i>rows || j<=0 || j>columns)

			{

			 char err[80];

			 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

						  coordinates",i,j);

			 errorSys(err,STOP);

			}

#endif

		x=(i-1)*columns;

		x=x+j-1;

		//return &map[x]; //landis 4.0

		

		CarbonWindCost[x]+=value; // Add by Qia Oct 07 2008



}

void SITES::Harvest70outputIncreaseCarbonvalue(int i, int j, double value)

	{

		int x;

#ifdef BOUNDSCHECK

		if (i<=0 || i>rows || j<=0 || j>columns)

			{

			 char err[80];

			 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

						  coordinates",i,j);

			 errorSys(err,STOP);

			}

#endif

		x=(i-1)*columns;

		x=x+j-1;

		//return &map[x]; //landis 4.0

		

		CarbonHarvestCost[x]+=value; // Add by Qia Oct 07 2008



}

void SITES::Fire70outputIncreaseCarbonvalue(int i, int j, double value)

	{

			int x;

#ifdef BOUNDSCHECK

			if (i<=0 || i>rows || j<=0 || j>columns)

				{

				 char err[80];

				 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

							  coordinates",i,j);

				 errorSys(err,STOP);

				}

#endif

			x=(i-1)*columns;

			x=x+j-1;

			//return &map[x]; //landis 4.0

			

			CarbonFireCost[x]+=value; // Add by Qia Oct 07 2008

	

	}



void SITES::Fuel70outputIncreaseCarbonvalue(int i, int j, double value)

	{

		int x;

#ifdef BOUNDSCHECK

		if (i<=0 || i>rows || j<=0 || j>columns)

			{

			 char err[80];

			 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

						  coordinates",i,j);

			 errorSys(err,STOP);

			}

#endif

		x=(i-1)*columns;

		x=x+j-1;

		//return &map[x]; //landis 4.0

		

		CarbonFuelCost[x]+=value; // Add by Qia Oct 07 2008



}

void SITES::BDA70outputIncreaseCarbonvalue(int i, int j, double value)

	{

		int x;

#ifdef BOUNDSCHECK

		if (i<=0 || i>rows || j<=0 || j>columns)

			{

			 char err[80];

			 sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

						  coordinates",i,j);

			 errorSys(err,STOP);

			}

#endif

		x=(i-1)*columns;

		x=x+j-1;

		//return &map[x]; //landis 4.0

		

		CarbonBDACost[x]; // Add by Qia Oct 07 2008



}



//</Add By Qia on Feb 09 2010>



void SITES::dim(int species, int i, int j)

//This will dimension the size of the map to i rows and j columns, and it

//will initialize the SPECIES class to species..



{

if (map70!=NULL)

   delete [] map70; //Nim: added []

if (map_landtype!=NULL)

   delete [] map_landtype; 

SITE temp;

temp.setNumber(species);

specNum=species;

//map=new SITE[i*j]; //landis 4.0

Pro0or401=1;

map70=new SITE[i*j]; //Add by Qia Oct 07 2008

//sitetouse=new SITE;//Add By Qia on Dec 19 2008



map_landtype=new LANDUNIT*[i*j];//Add by Qia Oct 07 2008

//<Add By Qia on June 29 2009>

SeedRain = new float[species*(MaxDistofAllSpec / CellSize * MaxDistofAllSpec / CellSize + 2)];

GrowthRates=new float[species*(320/TimeStep+1)];

MortalityRates=new float[species*(320/TimeStep+1)];

Volume=new float[species*(320/TimeStep+1)];

//</Add By Qia on June 29 2009>

rows=i;

columns=j;

//<Add By Qia on April 23 2010>

OutputGeneralFlagArray = new int[(species+1)*NumTypes70Output];

OutputAgerangeFlagArray = new int[(species+1)*NumTypes70Output];

SpeciesAgerangeArray = new int[species*500/TimeStep];
 
//</Add By Qia on April 23 2010>

//<Add By Qia on Dec 29 2010>

AgeDistStat_Year = new int[species*500/TimeStep];

AgeDistStat_AgeRange = new int[species*500/TimeStep];

//</Add By Qia on Dec 29 2010>



countWenjuanDebug = 0;



}



SITE* SITES::operator() (int i, int j) //need to change by Qia Oct 07 2008

//This will referrence a site map by row i and column j.



{

int x;



#ifdef BOUNDSCHECK

if (i<=0 || i>rows || j<=0 || j>columns)

    {

     char err[80];

     sprintf(err,"SITES::operator() (int,int)-> (%d, %d) are illegal map\

                  coordinates",i,j);

     errorSys(err,STOP);

    }

#endif

x=(i-1)*columns;

x=x+j-1;

//return &map[x]; //landis 4.0



return &map70[x]; // Add by Qia Oct 07 2008



}



void SITES::read(FILE* infile)

//This will read in a set of sites from infile.



{

int i;

SITE *p;//Change by Qia on Oct 10 2008 Original4.0: SITE *p



p=map70;

for (i=1;i<=rows*columns;i++)

   {

    if (feof(infile))

       errorSys("SITES::read(FILE*)-> Premature end of file.",STOP);

    (p)->read(infile);//Change by Qia on Oct 10 2008 original 4.0: p->read

    p++;

   }

}



void SITES::write(FILE* outfile)

//This will write out a set of sites to outfile.



{

int i;

SITE *p;//Change by Qia on Oct 10 2008 Original4.0: SITE *p



p=map70;

for (i=1;i<=rows*columns;i++)

   {

    (p)->write(outfile);//Change by Qia on Oct 10 2008 original 4.0: p->write

    fprintf(outfile,"\n");

    p++;

   }

}





void SITES::dump()

//This will dump a set of sites to the CRT screen.



{

    int i,j;

    for (i=rows; i>=1; i--) {

        for (j=1; j<=columns; j++) {

            printf("site(%d,%d) =\n", i, j);

            (*this)(i,j)->dump();

        } 

    }

}



/* J.Yang side-effect of del the composite rel.

void SITES::attach(LANDUNITS *lu)

//This will attach a set of land units to all sites.



{

if (rows<=0 || columns<=0)

   errorSys("SITES::attach(LANDUNITS*)-> Can't attach to NULL map.",STOP);

map->attach(lu);

}

*/



int SITES::numRows()

//This will return the number of rows in the sites structure.



{

return rows;

}



int SITES::numColumns()

//This will return the number of columns in the sites structure.



{

return columns;

}



int SITES::number()

//This will return the total number of sites.



{

return numRows()*numColumns();

}



int SITES::numActive()

//This will return the number of sites with active land units on the map.



{

int count=0;

for (int i=0;i<=numRows()*numColumns()-1;i++)

    if (map_landtype[i]->active())

        count++;            

return count;

}



void SITES::setHeader(unsigned long dest[])

{

//sets the sites header info.

for (int i = 0; i<32; i++)

	header[i] = dest[i];

xLLCorner=*(((float*)header)+28);

yLLCorner=*(((float*)header)+29);



}



unsigned long* SITES::getHeader()

{

//copy the header info.

return &header[0];

}



//ifdef __HARVEST__

int SITES::inBounds(int r, int c) {

    if (r >= 1 && r <= rows && c >= 1 && c <= columns)

        return 1;

    else

        return 0;

}

//#endif

//<Add by Qia on Oct 08 2008>

int SITES::SITE_compare(int site1_x,int site1_y,int site2_x,int site2_y)

{

	int x,y;

	int result;

	SITE *site1, *site2;

	x=(site1_x-1)*columns;

	x=x+site1_y-1;



	y=(site2_x-1)*columns;

	y=y+site2_y-1;



	site1=map[x];

	site2=map[y];

	result=SITE_compare(site1,site2);

	return result;

}

int SITES::SITE_compare(SITE * site1,SITE * site2)

{

	SPECIE *specie1;

	SPECIE *specie2;

	specie1=site1->first();

	specie2=site2->first();

	int num=specie1->getAgeVectorNum();

	while(specie1!=NULL && specie2!=NULL)

		{

			if(specie1->vegPropagules>specie2->vegPropagules)

				return 1;

			if(specie1->vegPropagules<specie2->vegPropagules)

				return 2;

			if(specie1->disPropagules>specie2->disPropagules)

				return 1;

			if(specie1->disPropagules<specie2->disPropagules)

				return 2;

			for(int i=0;i<num;i++)

				{

					if(specie1->getAgeVector(i)>specie2->getAgeVector(i))

						return 1;

					if(specie1->getAgeVector(i)<specie2->getAgeVector(i))

						return 2;

				}

			

			specie1=site1->next();

			specie2=site2->next();

		}

	return 0;

}

//</Add by Qia on Oct 08 2008>



//<Add by Qia on Oct 08 2008>

void SITES::fillinSitePt(int i, int j, SITE *site)

//

{

	int x;

	x=(i-1)*columns;

	x=x+j-1;

	map[x]=site;

}

SITE * SITES::locateSitePt(int i, int j)

//

{

	int x;

	x=(i-1)*columns;

	x=x+j-1;

	return map[x];

}

void SITES::fillinLanduPt(int i, int j, LANDUNIT *landUnitPt)

//

{

	int x;

	x=(i-1)*columns;

	x=x+j-1;

	map_landtype[x]=landUnitPt;

}

LANDUNIT * SITES::locateLanduPt(int i, int j)

//find the landtype

{

	int x;

	x=(i-1)*columns;

	x=x+j-1;

	return map_landtype[x];

}



int SITES::SITE_delete(int pos_sortIndex, SITE *site, int i, int j)

//When a site disappears, delete it

{

	int x;

	std::vector<SITE *>::iterator temp_sitePtr;

	x=(i-1)*columns;

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



int SITES::SITE_insert(int pos_sortIndex, SITE *site, int i, int j)

//when there is a new site during succession or whatever, we need to 

//check if the new site already exists, if yes combine with existing one

//if not insert to the position according to sort

{

	

	int x;

	int ifexist=0, pos=0;

	SITE *temp;

	x=(i-1)*columns;

	x=x+j-1;  

	std::vector<SITE *>::iterator temp_sitePtr;

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

			temp= new SITE;

			*temp=*site;

			temp->numofsites=1;

			map[x]=temp;

			SortedIndex.insert(SortedIndex.begin()+pos, temp);

		}

	return 1;

}



int SITES::SITE_LocateinSortIndex(SITE *site, int *pos, int *ifexist)

//Find if a new site exists in sorted list

//If a new site exists, find its location and set *ifexist as 1

//if this no site matches this one, find location before which new site pointer should be inserted

//By Qia Oct 09 2008

{

	int begin, end, mid;

	SITE *temp;

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

int SITES::SITE_sort()

//use babble algorithm to sort the initial site list array

{

	int size,i,j;

	SITE *site1, *site2,*temp;

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

//</Add by Qia on Oct 08 2008>



//<Add by Qia on Oct 20 2008>

void SITES::BefStChg(int i, int j)

//Before Site Change

//This function back up a site and following changes are based on this seprated site

//sort vector is not touched here

{

	return ;

	SITE *temp;

	temp=locateSitePt(i,j);

	*sitetouse=*temp;

	if(temp->numofsites==1)

		{

			int pos,ifexist=0;

			SITE_LocateinSortIndex(sitetouse,&pos,&ifexist);

			if(ifexist)

				{

					std::vector<SITE *>::iterator temp_sitePtr;

					temp_sitePtr=SortedIndex.begin();

					SortedIndex.erase(temp_sitePtr+pos);

					delete temp;

				}

			else

				{

					printf("num of vectors %d\n",SortedIndex.size());

					printf("ERROR ERROR ERROR ERROR!!~~~%d\n",pos);

					temp->dump();

					SortedIndex.at(pos)->dump();

					SortedIndex.at(pos-1)->dump();

					SortedIndex.at(pos-2)->dump();

					SortedIndex.at(0)->dump();

					SortedIndex.at(1)->dump();

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

	//sitetouse->numofsites=1;

	fillinSitePt(i,j,sitetouse);

	return ;

}

void SITES::AftStChg(int i,int j)

//After Site Change

//This function does combination and delete of the seprated site made by BefStChg(int i, int j)

//insert this site to the sorted vector

{

	return ;

	SITE_insert(0,sitetouse,i,j);

	return ;

}

//</Add By Qia on Oct 20 2008>



//<Add By Qia on June 30 2009>

void SITES::SiteDynamics(int RDflag, int Row, int Col)

//According to shade-rule and RD-rule determine species succession on sites, No Return Value

{

	int i,j,tempnumtree;

	int numSpec;

	SITE * siteptr;

	LANDUNIT *l;

	siteptr=SITES::operator()(Row,Col);
	
	l=SITES::locateLanduPt(Row,Col);
	int wenjuan_debug = 0;
	if(Row == 10 && Col == 7 && wenjuan_debug){
		printf("here we go with debugging\n");
		printf("%s\n",l->name);
		for(i=1;i<=siteptr->number();i++)
               {
               if(siteptr->specAtt(i)->SpType>=0)
                {
                  for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)
                     {
						 printf("%d, %d, tree num: %d, \n", i, j, siteptr->SpecieIndex(i)->getTreeNum(j,i));
                      
				  }
			   }
		 }

	}

	if(RDflag==0)

		{

		//if(siteptr->specAtt(i)->shadeTolerance<GetMaxShadeTolerance())

		

			SITES::GetSeedNumberOnSite(Row,Col);

			SeedGermination(siteptr,l,RDflag);

			GetRDofSite(Row,Col);

			

			SITES::NaturalMortality(siteptr,Row,Col,1);//kill the youngest of trees

			GetRDofSite(Row,Col);

			//if(siteptr->RD>l->MaxRD){

			//	SITES::Selfthinning(siteptr,l);

			//	GetRDofSite(Row,Col);

			//	}

		}

	else if(RDflag==1)

		{

		//if(siteptr->specAtt(i)->shadeTolerance>=siteptr->HighestShadeTolerance)

		

			SITES::GetSeedNumberOnSite(Row,Col);

			SeedGermination(siteptr,l,RDflag);

			GetRDofSite(Row,Col);

			

			SITES::NaturalMortality(siteptr,Row,Col,1);//kill the youngest of trees

			GetRDofSite(Row,Col);

			//if(siteptr->RD>l->MaxRD){

			//	SITES::Selfthinning(siteptr,l);

			//	GetRDofSite(Row,Col);

			//	}

		}

	else if(RDflag==2)

		{

		//if(siteptr->specAtt(i)->shadeTolerance==GetMaxShadeTolerance()&&siteptr->MaxAge>=l->minShade)

			SITES::GetSeedNumberOnSite(Row,Col);

			SeedGermination(siteptr,l,RDflag);

			GetRDofSite(Row,Col);

			SITES::NaturalMortality(siteptr,Row,Col,1);//kill all ages of trees

			GetRDofSite(Row,Col);

			//if(siteptr->RD>l->MaxRD){

			//	SITES::Selfthinning(siteptr,l);

			//	GetRDofSite(Row,Col);

			//	}

		}

	else if(RDflag==3)

		{

			SITES::GetSeedNumberOnSite(Row,Col);

			SeedGermination(siteptr,l,RDflag);

			GetRDofSite(Row,Col);

			SITES::NaturalMortality(siteptr,Row,Col,0);//kill all ages of trees

			GetRDofSite(Row,Col);

		}

	else if(RDflag==4)

		{	

			double thres_RD4 = 1.0/100000.0*TimeStep;
			if(drand()>thres_RD4){
				SITES::NaturalMortality(siteptr,Row,Col,0);//kill all ages of trees
				GetRDofSite(Row,Col);
				if(siteptr->RD>l->MaxRD){		
					SITES::Selfthinning(siteptr,l, Row, Col);
					GetRDofSite(Row,Col);
					}
			}
			else{
				double targetRD = l->MaxRDArray[0];
				NaturalMortality_killbytargetRD(siteptr,Row,Col,targetRD);
				GetRDofSite(Row,Col);
			}

		}

	else{

			errorSys("Site Dynamics Parameter Error\n",STOP);

		}

	if(siteptr->RD<=0.0)

		{

			

			SeedGermination(siteptr,l,RDflag);

			GetRDofSite(Row,Col);

			

			SITES::NaturalMortality(siteptr,Row,Col,1);//kill the youngest of trees

			GetRDofSite(Row,Col);

		}

	return ;

}

/*void SITES::Selfthinning(SITE* siteptr, LANDUNIT *l) //replace Bu's design by Wenjuan on March 04 2011

{

	int m=1,i,j,speciesstandcount=0;

	float tempRD;

	float RDStep=0;

	long tempvalue;

	int numSpec;

	numSpec=siteptr->number();

	int *indexSpec=new int[320/TimeStep];

	int *indexShade=new int[320/TimeStep];

	float *indexRD=new float[320/TimeStep];

	float *indexRDSpec=new float[320/TimeStep*numSpec];

	for(i=1;i<=siteptr->number();i++)

		{

		if(siteptr->specAtt(i)->SpType>=0&&siteptr->SpecieIndex(i)->query(TimeStep,siteptr->specAtt(i)->longevity))//||siteptr->SpecieIndex(i)->AvailableSeed>0||siteptr->SpecieIndex(i)->TreesFromVeg>0)

			speciesstandcount++;

		}

	if(speciesstandcount>1)

		tempRD=siteptr->RD-l->MaxRD*(0.98+frand1()*0.02);

	else

		tempRD=siteptr->RD-0.55*(0.98+frand1()*0.02);

	if (tempRD<=0)

		return;

	for(j=1;j<=320/TimeStep;j++)

		{

		indexSpec[j-1]=0;

		indexShade[j-1]=0;

		indexRD[j-1]=0;

		for(i=1;i<=numSpec;i++)

			{

			indexRDSpec[(i-1)*320/TimeStep+(j-1)]=0;

			if(j<=siteptr->specAtt(i)->longevity/TimeStep&&siteptr->SpecieIndex(i)->getTreeNum(j,i)&&siteptr->specAtt(i)->SpType>=0)

				{

				indexSpec[j-1]+=1;

				indexShade[j-1]+=(6-siteptr->specAtt(i)->shadeTolerance);

				indexRDSpec[(i-1)*320/TimeStep+(j-1)]=(SITES::GetGrowthRates(i,j)/25.4)*(SITES::GetGrowthRates(i,j)/25.4)*siteptr->specAtt(i)->MaxAreaOfSTDTree*siteptr->SpecieIndex(i)->getTreeNum(j,i)/CellSize/CellSize;

				indexRD[j-1]+=indexRDSpec[(i-1)*320/TimeStep+(j-1)];

				}

			}

		}

	for(j=1;j<=320/TimeStep;j++)

		{

		if(indexRD[j-1]>tempRD)

			{

			for(i=1;i<=numSpec;i++)

				{

				if(j<=(siteptr->specAtt(i)->longevity/TimeStep)&&siteptr->SpecieIndex(i)->getTreeNum(j,i)>0)

					{

					tempvalue=(int)((indexRDSpec[(i-1)*320/TimeStep+(j-1)]-tempRD*indexRDSpec[(i-1)*320/TimeStep+(j-1)]/indexRD[j-1])/(indexRDSpec[(i-1)*320/TimeStep+(j-1)]/siteptr->SpecieIndex(i)->getTreeNum(j,i)));

					if(tempvalue>0)

						siteptr->SpecieIndex(i)->setTreeNum(j,i,tempvalue);

					else

						siteptr->SpecieIndex(i)->setTreeNum(j,i,0);					

					}

				}

			break;

			}

		else

			{

			for(i=1;i<=numSpec;i++)

				{

				if(j<=(siteptr->specAtt(i)->longevity/TimeStep))

				siteptr->SpecieIndex(i)->setTreeNum(j,i,0);

				}

			tempRD-=indexRD[j-1];

			indexRD[j-1]=0;

			}

		}	

	delete [] indexSpec;

	delete [] indexShade;

	delete [] indexRD;

	delete [] indexRDSpec;

}*/

void SITES::ListbubbleSort()//Bubble sort function 

{

	int i,j;

	for(i = (AreaList.size() - 1); i > 0; i--)

	{

		for(j = 1; j <= i; j++)

		{

			if(AreaList.at(j-1)>AreaList.at(j)) 

			{

				std::swap( AreaList[j-1], AreaList[j] );

				std::swap( SpecIndexArray[j-1], SpecIndexArray[j] );

				std::swap( AgeIndexArray[j-1], AgeIndexArray[j] );

			}



		}



	}



}



void SITES::Selfthinning(SITE* siteptr, LANDUNIT *l, int row, int col){

	int i=0,j=0, age_i, spec_i;

	int *quaterPercent = new int[specNum*5];

	float thinning_percentatge[5];

	double Area_tobeThin;

	float TargetRD = siteptr->RD-l->MaxRD;
	int wenjuan_debug = 0;
	if(TargetRD <=0) {

		delete quaterPercent;

		return;

		}

	else{

		Area_tobeThin = TargetRD*CellSize*CellSize;

		}

	thinning_percentatge[0]= 0.95;

	thinning_percentatge[1]= 0.9;

	thinning_percentatge[2]= 0.85;

	thinning_percentatge[3]= 0.80;

	thinning_percentatge[4]= 0.75;

	for(i=1;i<=siteptr->number();i++){

		quaterPercent[(i-1)*4+0] = 1;

		quaterPercent[(i-1)*4+1] = siteptr->specAtt(i)->longevity/TimeStep/4;

		quaterPercent[(i-1)*4+2] = siteptr->specAtt(i)->longevity/TimeStep/2;

		quaterPercent[(i-1)*4+3] = siteptr->specAtt(i)->longevity/TimeStep/4*3;

		quaterPercent[(i-1)*4+4] = siteptr->specAtt(i)->longevity/TimeStep;

		}

	for(j = 0 ; j<4 ;j++){

		AreaList.clear();

		SpecIndexArray.clear();

		AgeIndexArray.clear();

		if(j==0){

			float subArea_tobeThin = 0.0;

			for(spec_i=1;spec_i<=siteptr->number();spec_i++){

				for(age_i=quaterPercent[(spec_i-1)*4+j]; age_i<quaterPercent[(spec_i-1)*4+j+1] ; age_i++)

					{

						subArea_tobeThin += thinning_percentatge[siteptr->specAtt(spec_i)->shadeTolerance-1]*pow((SITES::GetGrowthRates(spec_i,age_i,l->ltID)/25.4), 1.605)*siteptr->SpecieIndex(spec_i)->getTreeNum(age_i,spec_i)*siteptr->specAtt(spec_i)->MaxAreaOfSTDTree;

					float temp = pow((SITES::GetGrowthRates(spec_i,age_i,l->ltID)/25.4), 1.605)*siteptr->specAtt(spec_i)->MaxAreaOfSTDTree;

					AreaList.push_back(temp);

					SpecIndexArray.push_back(spec_i);

					AgeIndexArray.push_back(age_i);

					}

				}

			ListbubbleSort();

			if(subArea_tobeThin >= Area_tobeThin){

					for(i=0 ; i<AreaList.size() ; i++){

						if(siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))>0){

							float tempAreaInvolveTreeNum ;

							tempAreaInvolveTreeNum = AreaList.at(i)*siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]; 

							if(tempAreaInvolveTreeNum > Area_tobeThin){

								int treesToremove, treesLeft;

								treesToremove = Area_tobeThin/(AreaList.at(i));

								

								treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))- treesToremove;

								//if(0)//
								if(col == 1 && row == 20 && wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								

								Area_tobeThin -= tempAreaInvolveTreeNum;

								delete quaterPercent;

								return ;

								}

							else{

								

								int treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*(1-thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]);

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								}

							}

						}

					}

			else{

					for(i=0 ; i<AreaList.size() ; i++){

							if(siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))>0){

							float tempAreaInvolveTreeNum ;

							tempAreaInvolveTreeNum = AreaList.at(i)*siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]; 

							

							{

								

								int treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*(1-thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]);

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								}

							}

						}

				}

				}

		AreaList.clear();

		SpecIndexArray.clear();

		AgeIndexArray.clear();

		if(j==1){

			float subArea_tobeThin = 0.0;

			for(spec_i=1;spec_i<=siteptr->number();spec_i++){

				for(age_i=quaterPercent[(spec_i-1)*4+j]; age_i<quaterPercent[(spec_i-1)*4+j+1] ; age_i++)

					{

					subArea_tobeThin += thinning_percentatge[siteptr->specAtt(spec_i)->shadeTolerance-1]*pow((SITES::GetGrowthRates(spec_i,age_i,l->ltID)/25.4), 1.605)*siteptr->SpecieIndex(spec_i)->getTreeNum(age_i,spec_i)*siteptr->specAtt(spec_i)->MaxAreaOfSTDTree;

					float temp = pow((SITES::GetGrowthRates(spec_i,age_i, l->ltID)/25.4), 1.605)*siteptr->specAtt(spec_i)->MaxAreaOfSTDTree;

					AreaList.push_back(temp);

					SpecIndexArray.push_back(spec_i);

					AgeIndexArray.push_back(age_i);

					}

				}

			ListbubbleSort();

			if(subArea_tobeThin >= Area_tobeThin){

					for(i=0 ; i<AreaList.size() ; i++){

						if(siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))>0){

							float tempAreaInvolveTreeNum ;

							tempAreaInvolveTreeNum = AreaList.at(i)*siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/2; 

							if(tempAreaInvolveTreeNum > Area_tobeThin){

								int treesToremove, treesLeft;

								treesToremove = Area_tobeThin/(AreaList.at(i));

								treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))- treesToremove;

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								delete quaterPercent;

								return ;

								}

							else{

								int treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*(1-thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/2);

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								}

							}

						}

					}

					else{

						for(i=0 ; i<AreaList.size() ; i++){

						if(siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))>0){

							float tempAreaInvolveTreeNum ;

							tempAreaInvolveTreeNum = AreaList.at(i)*siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/2; 

							{

								int treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*(1-thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/2);

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								}

							}

						}

						}

			}

		AreaList.clear();

		SpecIndexArray.clear();

		AgeIndexArray.clear();

		if(j==2){

			float subArea_tobeThin = 0.0;

			for(spec_i=1;spec_i<=siteptr->number();spec_i++){

				for(age_i=quaterPercent[(spec_i-1)*4+j]; age_i<quaterPercent[(spec_i-1)*4+j+1] ; age_i++)

					{

					subArea_tobeThin += thinning_percentatge[siteptr->specAtt(spec_i)->shadeTolerance-1]*pow((SITES::GetGrowthRates(spec_i,age_i, l->ltID)/25.4), 1.605)*siteptr->SpecieIndex(spec_i)->getTreeNum(age_i,spec_i)*siteptr->specAtt(spec_i)->MaxAreaOfSTDTree;

					float temp = pow((SITES::GetGrowthRates(spec_i,age_i,l->ltID)/25.4), 1.605)*siteptr->specAtt(spec_i)->MaxAreaOfSTDTree;

					AreaList.push_back(temp);

					SpecIndexArray.push_back(spec_i);

					AgeIndexArray.push_back(age_i);

					}

				}

			ListbubbleSort();

			if(subArea_tobeThin >= Area_tobeThin){

					for(i=0 ; i<AreaList.size() ; i++){

						if(siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))>0){

							float tempAreaInvolveTreeNum ;

							tempAreaInvolveTreeNum = AreaList.at(i)*siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/4; 

							if(tempAreaInvolveTreeNum > Area_tobeThin){

								int treesToremove, treesLeft;

								treesToremove = Area_tobeThin/(AreaList.at(i));

								treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))- treesToremove;

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								delete quaterPercent;

								return ;

								}

							else{

								int treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*(1-thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/4);

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								}

							}

						}

					}

			else{

					for(i=0 ; i<AreaList.size() ; i++){

						if(siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))>0){

							float tempAreaInvolveTreeNum ;

							tempAreaInvolveTreeNum = AreaList.at(i)*siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/4; 

							{

								int treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*(1-thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/4);

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								}

							}

						}

				}

			}

		AreaList.clear();

		SpecIndexArray.clear();

		AgeIndexArray.clear();

		if(j==3){

			float subArea_tobeThin = 0.0;

			for(spec_i=1;spec_i<=siteptr->number();spec_i++){

				for(age_i=quaterPercent[(spec_i-1)*4+j]; age_i<=quaterPercent[(spec_i-1)*4+j+1] ; age_i++)

					{

					subArea_tobeThin += thinning_percentatge[siteptr->specAtt(spec_i)->shadeTolerance-1]*pow((SITES::GetGrowthRates(spec_i,age_i,l->ltID)/25.4), 1.605)*siteptr->SpecieIndex(spec_i)->getTreeNum(age_i,spec_i)*siteptr->specAtt(spec_i)->MaxAreaOfSTDTree;

					float temp = pow((SITES::GetGrowthRates(spec_i,age_i,l->ltID)/25.4), 1.605)*siteptr->specAtt(spec_i)->MaxAreaOfSTDTree;

					AreaList.push_back(temp);

					SpecIndexArray.push_back(spec_i);

					AgeIndexArray.push_back(age_i);

					}

				}

			ListbubbleSort();

			if(subArea_tobeThin >= Area_tobeThin){

					for(i=0 ; i<AreaList.size() ; i++){

						if(siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))>0){

							float tempAreaInvolveTreeNum ;

							tempAreaInvolveTreeNum = AreaList.at(i)*siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/8; 

							if(tempAreaInvolveTreeNum > Area_tobeThin){

								int treesToremove, treesLeft;

								treesToremove = Area_tobeThin/(AreaList.at(i));

								treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))- treesToremove;

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								delete quaterPercent;

								return ;

								}

							else{

								int treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*(1-thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/8);

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								}

							}

						}

					}

			else{

					for(i=0 ; i<AreaList.size() ; i++){

						if(siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))>0){

							float tempAreaInvolveTreeNum ;

							tempAreaInvolveTreeNum = AreaList.at(i)*siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/8; 

							{

								int treesLeft = siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i))*(1-thinning_percentatge[siteptr->specAtt(SpecIndexArray.at(i))->shadeTolerance-1]/8);

								//if(0)//
								if(col == 1 && row == 20 &&wenjuan_debug)

									{

									printf("Col:%d, Row:%d:\n", col, row);

									printf("area: %f, Spec: %d, Age: %d, TreeInit: %d, TreeLeft: %d\n", AreaList.at(i), SpecIndexArray.at(i), AgeIndexArray.at(i),  siteptr->SpecieIndex(SpecIndexArray.at(i))->getTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i)), max(0,treesLeft));

									}

								siteptr->SpecieIndex(SpecIndexArray.at(i))->setTreeNum(AgeIndexArray.at(i),SpecIndexArray.at(i),max(0,treesLeft));

								Area_tobeThin -= tempAreaInvolveTreeNum;

								}

							}

						}

				}

			}

		}

	

	delete quaterPercent;

}

void SITES::SeedGermination(SITE* siteptr, LANDUNIT *l, int RDFlag)

{
	int wenjuan_debug = 0;
	int i,j,agetemp,speciesstandcount=0;

	double TempRD=0, WholeRD=0,WholeRD1=0,TmpMaxRD=0;

	double *IndexRD;

	double RDTotal;

	double seedlingTemp;

	float *SppRD;

	int *SppShade;

	int *SppPresence;

	float IndexDBH=0;

	long *Seedling;

	float *TmpSppRD;

	long WholeSeedling=0;

	long temp;

	double temp1;

	IndexRD=new double[siteptr->number()];

	Seedling=new long[siteptr->number()];

	SppShade=new int[6];

	SppRD=new float[6];
	
	SppPresence=new int[siteptr->number()];
	for(i = 0; i<siteptr->number() ; i++){
		IndexRD[i] = 0;
		Seedling[i] = 0;
		SppPresence[i] = 0;
	}
	for(i=0; i<6;i++){
		SppShade[i] = 0;
		SppRD[i] = 0;
	}
	
	if(RDFlag==0 || RDFlag==1)

		{

		RDTotal = 0.0;

		for(i=1;i<=siteptr->number();i++){

			IndexRD[i-1] = (double)(pow((SITES::GetGrowthRates(i,1, l->ltID)/25.4),1.605)*siteptr->specAtt(i)->MaxAreaOfSTDTree*siteptr->SpecieIndex(i)->AvailableSeed/CellSize/CellSize);

			RDTotal += IndexRD[i-1];

			}

		if(RDTotal >= 0.0){

			if(RDTotal <= l->MaxRD - siteptr->RD ){

				for(i=1;i<=siteptr->number();i++){

					if(siteptr->specAtt(i)->shadeTolerance<=4 || (siteptr->specAtt(i)->shadeTolerance==5&&siteptr->MaxAge>=l->minShade))

						{

						temp=(long)(siteptr->SpecieIndex(i)->TreesFromVeg*siteptr->SpecieIndex(i)->vegPropagules);

						siteptr->SpecieIndex(i)->TreesFromVeg=0;

						Seedling[i - 1] = (siteptr->SpecieIndex(i)->AvailableSeed)*l->probRepro(i) + temp;

						
						if ((siteptr->SpecieIndex(i)->AvailableSeed)*l->probRepro(i) + temp > 0 && (siteptr->SpecieIndex(i)->AvailableSeed)*l->probRepro(i) + temp < 1){

							int ran = rand() % 10 + 1; // ran in the range 1 to 10

							if (ran < 2){

								Seedling[i - 1] = 1;

							}


						}

						//if (siteptr->SpecieIndex(i)->AvailableSeed !=0)
//std::cout << "seedling:" << siteptr->SpecieIndex(i)->AvailableSeed << "    " << Seedling[i - 1] << std::endl;

						if(wenjuan_debug){
							printf("spec: %d, landtype: %s, temp: %ld, avlbseed: %ld, probRepro: %f, seedling: %ld\n",
								i, l->name,temp,siteptr->SpecieIndex(i)->AvailableSeed,l->probRepro(i),Seedling[i-1]);
						}
						}

					}

				}

			else{

				for(i=1;i<=siteptr->number();i++){

					if(siteptr->specAtt(i)->shadeTolerance<=4 || (siteptr->specAtt(i)->shadeTolerance==5&&siteptr->MaxAge>=l->minShade))

						{

						temp=(long)(siteptr->SpecieIndex(i)->TreesFromVeg*siteptr->SpecieIndex(i)->vegPropagules);

						siteptr->SpecieIndex(i)->TreesFromVeg=0;

						seedlingTemp = IndexRD[i-1] *(l->MaxRD -siteptr->RD)/RDTotal*CellSize*CellSize/(pow((SITES::GetGrowthRates(i,1 ,l->ltID)/25.4),1.605)*siteptr->specAtt(i)->MaxAreaOfSTDTree);

						Seedling[i-1] = (seedlingTemp)*l->probRepro(i) + temp;
						if(wenjuan_debug){
							printf("spec: %d, landtype: %s, temp: %ld, avlbseed: %ld, probRepro: %f, seedling: %ld\n",
								i, l->name,temp,siteptr->SpecieIndex(i)->AvailableSeed,l->probRepro(i),Seedling[i-1]);
						}
						}

					}

				}

			}

		else{

			delete [] IndexRD;

			delete [] Seedling;

			delete [] SppRD;

			delete [] SppShade;

			delete [] SppPresence;

			return ;

			}

		}

	else if(RDFlag==2)

		{

		RDTotal = 0.0;

		for(i=1;i<=siteptr->number();i++)

			{

			if(siteptr->specAtt(i)->shadeTolerance>=siteptr->HighestShadeTolerance)//changed by wenjuan//if(siteptr->specAtt(i)->shadeTolerance==siteptr->HighestShadeTolerance&&siteptr->MaxAge>=l->minShade)

				{

					IndexRD[i-1] = (double)(pow((SITES::GetGrowthRates(i,1, l->ltID)/25.4),1.605)*siteptr->specAtt(i)->MaxAreaOfSTDTree*siteptr->SpecieIndex(i)->AvailableSeed/CellSize/CellSize);

					RDTotal += IndexRD[i-1];

				}

			else

				{

					Seedling[i-1]=0;

				}

			}

		if(RDTotal >= 0.0){

			if(RDTotal <= l->MaxRD - siteptr->RD){

				for(i=1;i<=siteptr->number();i++){

					if(siteptr->specAtt(i)->shadeTolerance>=siteptr->HighestShadeTolerance){

						temp=(long)(siteptr->SpecieIndex(i)->TreesFromVeg*siteptr->SpecieIndex(i)->vegPropagules);

						siteptr->SpecieIndex(i)->TreesFromVeg=0;

						Seedling[i-1] = (siteptr->SpecieIndex(i)->AvailableSeed)*l->probRepro(i) + temp;
						if(wenjuan_debug){
							printf("spec: %d, landtype: %s, temp: %ld, avlbseed: %ld, probRepro: %f, seedling: %ld\n",
								i, l->name,temp,siteptr->SpecieIndex(i)->AvailableSeed,l->probRepro(i),Seedling[i-1]);
						}
						}

					}

				}

			else{

				for(i=1;i<=siteptr->number();i++){

					if(siteptr->specAtt(i)->shadeTolerance>=siteptr->HighestShadeTolerance){

						temp=(long)(siteptr->SpecieIndex(i)->TreesFromVeg*siteptr->SpecieIndex(i)->vegPropagules);

						siteptr->SpecieIndex(i)->TreesFromVeg=0;

						seedlingTemp = IndexRD[i-1] * (l->MaxRD -siteptr->RD)/RDTotal*CellSize*CellSize/(pow((SITES::GetGrowthRates(i,1, l->ltID)/25.4),1.605)*siteptr->specAtt(i)->MaxAreaOfSTDTree);

						Seedling[i-1] = (seedlingTemp)*l->probRepro(i) + temp;
						if(wenjuan_debug){
							printf("spec: %d, landtype: %s, temp: %ld, avlbseed: %ld, probRepro: %f, seedling: %ld\n",
								i, l->name,temp,siteptr->SpecieIndex(i)->AvailableSeed,l->probRepro(i),Seedling[i-1]);
						}
					}

						}

				}

			}

		else{

			delete [] IndexRD;

			delete [] Seedling;

			delete [] SppRD;

			delete [] SppShade;

			delete [] SppPresence;

			return ;

			}

		}

	else if(RDFlag == 3){

		RDTotal = 0.0;

		for(i=1;i<=siteptr->number();i++)

			{

			if(siteptr->specAtt(i)->shadeTolerance==MaxShadeTolerance&&siteptr->MaxAge>=l->minShade)//changed by wenjuan//if(siteptr->specAtt(i)->shadeTolerance==siteptr->HighestShadeTolerance&&siteptr->MaxAge>=l->minShade)

				{

					IndexRD[i-1] = (double)(pow((SITES::GetGrowthRates(i,1, l->ltID)/25.4),1.605)*siteptr->specAtt(i)->MaxAreaOfSTDTree*siteptr->SpecieIndex(i)->AvailableSeed/CellSize/CellSize);

					RDTotal += IndexRD[i-1];

				}

			else

				{

					Seedling[i-1]=0;

				}

			}

		if(RDTotal >= 0.0){

			if(RDTotal <= l->MaxRD - siteptr->RD){

				for(i=1;i<=siteptr->number();i++){

					if(siteptr->specAtt(i)->shadeTolerance==MaxShadeTolerance&&siteptr->MaxAge>=l->minShade){

						temp=(long)(siteptr->SpecieIndex(i)->TreesFromVeg*siteptr->SpecieIndex(i)->vegPropagules);

						siteptr->SpecieIndex(i)->TreesFromVeg=0;

						Seedling[i-1] = (siteptr->SpecieIndex(i)->AvailableSeed)*l->probRepro(i) + temp;
						if(wenjuan_debug){
							printf("spec: %d, landtype: %s, temp: %ld, avlbseed: %ld, probRepro: %f, seedling: %ld\n",
								i, l->name,temp,siteptr->SpecieIndex(i)->AvailableSeed,l->probRepro(i),Seedling[i-1]);
						}
						}

					}

				}

			else{

				for(i=1;i<=siteptr->number();i++){

					if(siteptr->specAtt(i)->shadeTolerance==MaxShadeTolerance&&siteptr->MaxAge>=l->minShade){

						temp=(long)(siteptr->SpecieIndex(i)->TreesFromVeg*siteptr->SpecieIndex(i)->vegPropagules);

						siteptr->SpecieIndex(i)->TreesFromVeg=0;

						seedlingTemp = IndexRD[i-1] *(l->MaxRD -siteptr->RD)/RDTotal*CellSize*CellSize/(pow((SITES::GetGrowthRates(i,1, l->ltID)/25.4),1.605)*siteptr->specAtt(i)->MaxAreaOfSTDTree);

						Seedling[i-1] = (seedlingTemp)*l->probRepro(i) + temp;
						if(wenjuan_debug){
							printf("spec: %d, landtype: %s, temp: %ld, avlbseed: %ld, probRepro: %f, seedling: %ld\n",
								i, l->name,temp,siteptr->SpecieIndex(i)->AvailableSeed,l->probRepro(i),Seedling[i-1]);
						}
						}

					}

				}

			}

		else{

			delete [] IndexRD;

			delete [] Seedling;

			delete [] SppRD;

			delete [] SppShade;

			delete [] SppPresence;

			return ;

			}

		}

	else 

		{

			WholeSeedling=0;

			WholeRD=0;

			IndexDBH=0;

			for(i=1;i<=siteptr->number();i++){

				Seedling[i-1]=0;

				}

		}

	

	for(i=1;i<=siteptr->number();i++)

		{

		//agetemp=(int)(TempRD*Seedling[i-1]/WholeSeedling/((SITES::GetGrowthRates(i,1)/25.4)*(SITES::GetGrowthRates(i,1)/25.4))/siteptr->specAtt(i)->MaxAreaOfSTDTree*CellSize*CellSize);

		if(Seedling[i-1]>0)

			siteptr->SpecieIndex(i)->setTreeNum(1,i,Seedling[i-1]);

		else

			siteptr->SpecieIndex(i)->setTreeNum(1,i,0);

		}

	delete [] IndexRD;

	delete [] Seedling;

	delete [] SppRD;

	delete [] SppShade;

	delete [] SppPresence;

	return ;

}



void SITES::GetRDofSite(int Row, int Col)

//calculate the RD for a given site, No Return Value

{

       int i,j;

       int numSpec;

       SITE * siteptr;

       siteptr=SITES::operator()(Row,Col);

       siteptr->HighestShadeTolerance=0;

       numSpec=siteptr->number();

       siteptr->RD=0;
	   LANDUNIT *l;

		l=SITES::locateLanduPt(Row,Col);

       for(i=1;i<=numSpec;i++)

               {

               if(siteptr->specAtt(i)->SpType>=0)

                       {

                               for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

                                       {

                                               float temp=pow((SITES::GetGrowthRates(i,j,l->ltID)/25.4),1.605)*siteptr->specAtt(i)->MaxAreaOfSTDTree*siteptr->SpecieIndex(i)->getTreeNum(j,i)/CellSize/CellSize;

                                               siteptr->RD=siteptr->RD+temp;

                                               if(siteptr->SpecieIndex(i)->getTreeNum(j,i)>0)

                                                       {

                                                               if(siteptr->HighestShadeTolerance<siteptr->specAtt(i)->shadeTolerance)

                                                                       {

                                                                               siteptr->HighestShadeTolerance=siteptr->specAtt(i)->shadeTolerance;

                                                                       }

                                                       }

                                       }

                       }

               }

       if(0){

               printf("after get RD of site\n");

               for(int i_spec = 1; i_spec <= siteptr->number();i_spec++){

                       for(int i_age=1;i_age<=siteptr->specAtt(i_spec)->longevity/TimeStep;i_age++){

                               if(siteptr->SpecieIndex(i_spec)->getTreeNum(i_age,i_spec)>0){

                                               printf("SPEC: %d Age: %d RD: %f TN: %d GR: %f \n",i_spec, i_age,

siteptr->RD, siteptr->SpecieIndex(i_spec)->getTreeNum(i_age,i_spec),GetGrowthRates(i_spec,i_age,l->ltID));

                                               }

                               }

               }

               }

}



/*void SITES::GetRDofSite(int Row, int Col)

//calculate the RD for a given site, No Return Value

{

	int i,j;

	int numSpec;

	SITE * siteptr;

	siteptr=SITES::operator()(Row,Col);

	siteptr->HighestShadeTolerance=0;

	double treenum_cell=0,MaxSDI_cell=0,Dq = 0, BA_spec =0; 

	numSpec=siteptr->number();

	siteptr->RD=0;

	for(i=1;i<=numSpec;i++)

		{

		treenum_cell=0,MaxSDI_cell=0,Dq = 0, BA_spec =0; 

		if(siteptr->specAtt(i)->SpType>=0)

			{

				for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

					{

						if(siteptr->SpecieIndex(i)->getTreeNum(j,i)>0)

							{

								treenum_cell += siteptr->SpecieIndex(i)->getTreeNum(j,i);

								BA_spec+=SITES::GetGrowthRates(i,j)*SITES::GetGrowthRates(i,j)/4*3.1415926*siteptr->SpecieIndex(i)->getTreeNum(j,i);

								

							}

					}

				if(treenum_cell == 0){

					

				}

				else{

					Dq = 2*sqrt(BA_spec/treenum_cell/3.1415926);

					siteptr->RD += treenum_cell*pow(Dq/25.4,1.605)*siteptr->specAtt(i)->MaxAreaOfSTDTree/CellSize/CellSize;

				}

			}

		}

	return ;

}*/



void SITES::MaxAgeofSite(SITE *siteptr)

//calculate the MaxAge for a given site

{

	int i,j;

	int numSpec;

	siteptr->MaxAge=0;

	numSpec=siteptr->number();

	for(i=1;i<=numSpec;i++)

		{

		for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

			{

				if(siteptr->SpecieIndex(i)->getTreeNum(j,i)>0)

					{

						if(siteptr->MaxAge<j)

							siteptr->MaxAge=j;

					}

			}

		}

}

void SITES::GetMatureTree()

{

	int i,j,m,k;

	SITE * siteptr;

	int tempvalue=0;

	for(i=1;i<=rows;i++)

		{

		for(j=1;j<=columns;j++)

			{

			siteptr=SITES::operator()(i,j);

			for(k=1;k<=siteptr->number();k++)

				{

				tempvalue=0;

				for(m=siteptr->specAtt(k)->maturity/TimeStep;m<=siteptr->specAtt(k)->longevity/TimeStep;m++)

					{

					tempvalue+=siteptr->SpecieIndex(k)->getTreeNum(m,k);

					}

				siteptr->SpecieIndex(k)->SetMatureTreeValue(tempvalue);

				}

			}

		}

}

void SITES::GetSeedNumberOnSite(int Row, int Col)

//According to total seed of each species, calculate the available seed number would disperse into other sites

{

	int i,j,k,m;
	SITE * siteptr;

	float TempDist;


	int rangXLeft, rangXRight, rangYDown, rangYUp;

	siteptr=SITES::operator()(Row,Col);
	LANDUNIT *l;

	l=SITES::locateLanduPt(Row,Col);

	int num_row = numRows();

	int num_col = numColumns();

for(k=1;k<=siteptr->number();k++)

{
	int local_maxD = siteptr->specAtt(k)->maxD;

	int local_maxD_d_cellsize = local_maxD / CellSize;

	siteptr->SpecieIndex(k)->AvailableSeed=0;

	if(siteptr->specAtt(k)->SpType<0)

		{

		siteptr->SpecieIndex(k)->AvailableSeed=siteptr->specAtt(k)->TotalSeed*TimeStep;

		}

	else{

		if(locateLanduPt(Row,Col)->probRepro(k)>0&&siteptr->specAtt(k)->maxD<0){

			

			for(int i_age=siteptr->specAtt(k)->maturity/TimeStep;i_age<=siteptr->specAtt(k)->longevity/TimeStep;i_age++){

				if(siteptr->SpecieIndex(k)->getTreeNum(i_age,k)>0){
						siteptr->SpecieIndex(k)->AvailableSeed+=pow(GetGrowthRates(k,i_age,l->ltID)/25.4, 1.605)*siteptr->SpecieIndex(k)->getTreeNum(i_age,k)*siteptr->specAtt(k)->TotalSeed*TimeStep; //wenjuan changed on mar 30 2011

						}	

				}

			}
		//// only consider here
		//if(locateLanduPt(Row,Col)->probRepro(k)>0&&siteptr->specAtt(k)->maxD>0)

		//	{
		//		
		//	
		//	
		//	// needed to be modified 
		//		for(i=Row-siteptr->specAtt(k)->maxD/CellSize;i<=Row+siteptr->specAtt(k)->maxD/CellSize;i++)

		//			{
		//			// needed to be modified
		//			for(j=Col-siteptr->specAtt(k)->maxD/CellSize;j<=Col+siteptr->specAtt(k)->maxD/CellSize;j++)

		//				{

		//				if(i>=1&&i<=numRows()&&j>=1&&j<=numColumns()&&locateLanduPt(i,j)!=NULL&&locateLanduPt(i,j)->active())

		//					{
		//					// needed to be modified 
		//					TempDist = max(abs(i-Row),abs(j-Col));

		//					unsigned long tempAvailableSeed =(GetSeedRain(k,TempDist)*SITES::operator()(i,j)->SpecieIndex(k)->GetMatureTreeValue()*SITES::operator()(i,j)->specAtt(k)->TotalSeed*TimeStep);

		//					siteptr->SpecieIndex(k)->AvailableSeed+=tempAvailableSeed;

		//					}

		//				}

		//			if(siteptr->SpecieIndex(k)->AvailableSeed>CellSize*CellSize*1000)

		//				{

		//					siteptr->SpecieIndex(k)->AvailableSeed=CellSize*CellSize*1000; // range 0 to 4,294,967,295

		//					break;

		//				}

		//			

		//			}

		//	//siteptr->SpecieIndex(k)->AvailableSeed*=TimeStep;

		//	siteptr->SpecieIndex(k)->AvailableSeed=(siteptr->SpecieIndex(k)->AvailableSeed*(0.95+frand1()*0.1));

		//	}

		

		if (locateLanduPt(Row, Col)->probRepro(k) > 0 && local_maxD > 0)

		{
			/*int radis = 100;*/
			//float X = Row - 0.5; float Y = Col - 0.5;
			//int minX = floor(X); //10
			//int maxX = ceil(X);  //11
			//int minY = floor(Y); //15
			//int maxY = ceil(Y);  //16
			/*rangXLeft = Col - local_maxD_d_cellsize;

			rangXRight = Col + local_maxD_d_cellsize;

			rangYDown = Row - local_maxD_d_cellsize;

			rangYUp = Row + local_maxD_d_cellsize;*/
			if (siteptr->specAtt(k)->maxD > CellSize){

				for (i = Row - siteptr->specAtt(k)->maxD / CellSize; i <= Row + siteptr->specAtt(k)->maxD / CellSize; i++)

				{
				// needed to be modified
				for (j = Col - siteptr->specAtt(k)->maxD / CellSize; j <= Col + siteptr->specAtt(k)->maxD / CellSize; j++)

				{

					if (i >= 1 && i <= num_row && j >= 1 && j <= num_col && locateLanduPt(i, j) != NULL&&locateLanduPt(i, j)->active()){

						//if ((i <= sqrt(local_maxD_d_cellsize * local_maxD_d_cellsize - (j - X)* (j - X)) + Y) && (i >= -sqrt(local_maxD_d_cellsize * local_maxD_d_cellsize - (j - X)* (j - X)) + Y)) {

						TempDist = (j - Col)*(j - Col) + (i - Row)*(i - Row);



						if (TempDist <= local_maxD_d_cellsize * local_maxD_d_cellsize){

							//std::cout << "distance" << sqrt(TempDist) << std::endl;

							unsigned long tempAvailableSeed = (GetSeedRain(k, TempDist)*SITES::operator()(i, j)->SpecieIndex(k)->GetMatureTreeValue()*SITES::operator()(i, j)->specAtt(k)->TotalSeed*TimeStep);

							siteptr->SpecieIndex(k)->AvailableSeed += tempAvailableSeed;

							///std::cout << "Probability: " << GetSeedRain(k, TempDist) << std::endl;
						}


					}
				}



				if (siteptr->SpecieIndex(k)->AvailableSeed > CellSize*CellSize * 1000)

				{

					siteptr->SpecieIndex(k)->AvailableSeed = CellSize*CellSize * 1000; // range 0 to 4,294,967,295

					break;

				}


				}
			}
			else {

					for (i = Row - 1; i <= Row + 1; i++)

				{
				// needed to be modified
				for (j = Col - 1; j <= Col + 1; j++)

				{

					if (i >= 1 && i <= num_row && j >= 1 && j <= num_col && locateLanduPt(i, j) != NULL&&locateLanduPt(i, j)->active()){

						//if ((i <= sqrt(local_maxD_d_cellsize * local_maxD_d_cellsize - (j - X)* (j - X)) + Y) && (i >= -sqrt(local_maxD_d_cellsize * local_maxD_d_cellsize - (j - X)* (j - X)) + Y)) {

						//TempDist = (j - Col)*(j - Col) + (i - Row)*(i - Row);

						TempDist = siteptr->specAtt(k)->maxD *siteptr->specAtt(k)->maxD ;



					//	if (TempDist <= local_maxD_d_cellsize * local_maxD_d_cellsize){

							//std::cout << "distance" << sqrt(TempDist) << std::endl;

							unsigned long tempAvailableSeed = (GetSeedRain(k, TempDist)*SITES::operator()(i, j)->SpecieIndex(k)->GetMatureTreeValue()*SITES::operator()(i, j)->specAtt(k)->TotalSeed*TimeStep);

							siteptr->SpecieIndex(k)->AvailableSeed += tempAvailableSeed;

							///std::cout << "Probability: " << GetSeedRain(k, TempDist) << std::endl;
					//	}


					}
				}



				if (siteptr->SpecieIndex(k)->AvailableSeed > CellSize*CellSize * 1000)

				{

					siteptr->SpecieIndex(k)->AvailableSeed = CellSize*CellSize * 1000; // range 0 to 4,294,967,295

					break;

				}


				}
			}

			//siteptr->SpecieIndex(k)->AvailableSeed = (siteptr->SpecieIndex(k)->AvailableSeed*(0.95 + frand1()*0.1));
			//if (siteptr->SpecieIndex(1)->AvailableSeed != 0){

			//	//std::cout << SITES::operator()(251, 251)->SpecieIndex(k)->GetMatureTreeValue() << std::endl;

			//	

			//	//unsigned long temp = GetSeedRain(1, sqrt((j - Col)*(j - Col) + (i - Row)*(i - Row)));

			//	

			//	//std::cout << "cell (" << Row << "," << Col << ")Availabel seed:" << siteptr->SpecieIndex(1)->AvailableSeed << std::endl;
			//}

		}

	} 

}



}

//</Add By Qia on June 30 2009>
//<Add By Qia on Aug 22 2013>
void SITES::NaturalMortality_killbytargetRD(SITE * siteptr,int Row,int Col,double targetRD){
	int i,j,k;
	for(i=1;i<=siteptr->number();i++){
		if(siteptr->specAtt(i)->SpType>=0){
			for(j=siteptr->specAtt(i)->longevity/TimeStep;j>=1;j--){
				if(siteptr->SpecieIndex(i)->getTreeNum(j,i)>0){
					siteptr->SpecieIndex(i)->setTreeNum(j,i,0);
					GetRDofSite(Row,Col);
					if(siteptr->RD<=targetRD){
						return ;
					}
				}
			}
		}
	}
}
//</Add By Qia on Aug 22 2013>
//<Add By Qia on July 1 2009>

void SITES::NaturalMortality(SITE * siteptr,int Row,int Col,int StartAge)

//According to MortalityRates, kill trees and calculate tree numbers

{

	int i,j,k;

	float tmpDQ,TmpMortality,DeadTree;

	unsigned int DeadTreeInt;

	LANDUNIT *l;

	l=SITES::locateLanduPt(Row,Col);

	

if (StartAge==0)

	{//kill all tree, else kill youngest tree

	if(MortalityFlag==0)

		{

		tmpDQ=0;

		for(i=1;i<=siteptr->number();i++)

			{

			if(siteptr->specAtt(i)->SpType>=0)

			for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

				{

				//tmpDQ+=GetGrowthRates(i,j)/30.48*GetGrowthRates(i,j)/30.48/4*3.1415926/10000*CellSize*CellSize*siteptr->SpecieIndex(i)->getTreeNum(j,i);

				tmpDQ+=GetGrowthRates(i,j,l->ltID)/30.48*GetGrowthRates(i,j,l->ltID)/30.48/4*3.1415926/(0.0002471*CellSize*CellSize)*siteptr->SpecieIndex(i)->getTreeNum(j,i);//Wenjuan Suggested on Nov 16 2010

				}

			}

		for(i=1;i<=siteptr->number();i++)

			{

			if(siteptr->specAtt(i)->SpType>=0){

				for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

					{

					

					//for(k=1;k<=TimeStep;k++)

						{

						

						TmpMortality=(TimeStep/10)*1.0/(1.0+exp(3.25309-0.00072647*tmpDQ+0.01668809*GetGrowthRates(i,j,l->ltID)/2.54));//" /(1+l->probRepro(i))" remove by Wenjuan Feb 04 2011;
						TmpMortality = LDmin(1.0, TmpMortality);
						DeadTree=siteptr->SpecieIndex(i)->getTreeNum(j,i)*TmpMortality;//(siteptr->specAtt(i)->shadeTolerance);//considered shade tolerance

						int numnum=siteptr->SpecieIndex(i)->getTreeNum(j,i);

						DeadTreeInt = DeadTree;

						if((DeadTree-(float)DeadTreeInt)>=0.0001){

							if(frand1()<0.1){

								DeadTreeInt++;

								}

							}
						siteptr->SpecieIndex(i)->setTreeNum(j,i,max(0,numnum-DeadTreeInt));//max(0,numnum-DeadTreeInt)
						//printf("1Col: %d, row: %d, deadtree: %d, orig tree %d, value to set %d\n", Col, Row, DeadTreeInt, numnum,max(0,numnum-DeadTreeInt));
						tmpDQ-=GetGrowthRates(i,j,l->ltID)/30.48*GetGrowthRates(i,j,l->ltID)/30.48/4*3.1415926/(0.0002471*CellSize*CellSize)*DeadTree;//Wenjuan Suggested on Nov 16 2010

					}

					}

				}

			else{

				for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

					{

					siteptr->SpecieIndex(i)->setTreeNum(j,i,CellSize*CellSize);

					}

				}

			//GetSeedNumberOnSite(Row,Col);

			}

		}

	else

		{

		for(i=1;i<=siteptr->number();i++)

			{

			if(siteptr->specAtt(i)->SpType>=0)

				{

				for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

					{

						DeadTree=siteptr->SpecieIndex(i)->getTreeNum(j,i)*GetMortalityRates(i,j,l->ltID);//" /(1+l->probRepro(i))" remove by Wenjuan Feb 04 2011;

						DeadTreeInt = DeadTree;

						if((DeadTree-(float)DeadTreeInt)>=0.0001){

							if(frand1()<0.1){

								DeadTreeInt++;

								}

							}
						int numnum = siteptr->SpecieIndex(i)->getTreeNum(j,i);
						siteptr->SpecieIndex(i)->setTreeNum(j,i,max(0,numnum-DeadTreeInt));//max(0,siteptr->SpecieIndex(i)->getTreeNum(j,i)-DeadTreeInt)
						//printf("2Col: %d, row: %d, deadtree: %d, orig tree %d, value to set %d\n", Col, Row, DeadTreeInt, numnum,max(0,numnum-DeadTreeInt));
					}

				}

			else{

				for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

					{

					siteptr->SpecieIndex(i)->setTreeNum(j,i,CellSize*CellSize);

					}

				}

			}

		}

	}

else

	{//kill all tree

	if(MortalityFlag==0)

		{

		tmpDQ=0;

		for(i=1;i<=siteptr->number();i++)

			{

			if(siteptr->specAtt(i)->SpType>=0)

			for(j=1;j<=siteptr->specAtt(i)->longevity/TimeStep;j++)

				{

				tmpDQ+=GetGrowthRates(i,j,l->ltID)/30.48*GetGrowthRates(i,j,l->ltID)/30.48/4*3.1415926/(0.0002471*CellSize*CellSize)*siteptr->SpecieIndex(i)->getTreeNum(j,i);//Wenjuan Suggested on Nov 16 2010

				}

			}

		for(i=1;i<=siteptr->number();i++)

			{

			if(siteptr->specAtt(i)->SpType>=0){

				for(j=1;j<=StartAge;j++)

					{					

					//for(k=1;k<=TimeStep;k++)

						{

						TmpMortality=(TimeStep/10)*1.0/(1.0+exp(3.25309-0.00072647*tmpDQ+0.01668809*GetGrowthRates(i,j,l->ltID)/2.54));//" /(1+l->probRepro(i))" remove by Wenjuan Feb 04 2011;
						TmpMortality = LDmin(1.0, TmpMortality);
						DeadTree=siteptr->SpecieIndex(i)->getTreeNum(j,i)*TmpMortality;//(siteptr->specAtt(i)->shadeTolerance);//considered shade tolerance

						DeadTreeInt = DeadTree;

						if((DeadTree-(float)DeadTreeInt)>=0.0001){

							if(frand1()<0.1){

								DeadTreeInt++;

								}

							}

						int numnum=siteptr->SpecieIndex(i)->getTreeNum(j,i);

						siteptr->SpecieIndex(i)->setTreeNum(j,i,max(0,numnum-DeadTreeInt));//max(0,numnum-DeadTreeInt)
						//printf("3Col: %d, row: %d, deadtree: %d, orig tree %d, value to set %d\n", Col, Row, DeadTreeInt, numnum,max(0,numnum-DeadTreeInt));
						tmpDQ-=GetGrowthRates(i,j,l->ltID)/30.48*GetGrowthRates(i,j,l->ltID)/30.48/4*3.1415926/(0.0002471*CellSize*CellSize)*DeadTree;//Wenjuan Suggested on Nov 16 2010

					}

					}

				}

			else{

				for(j=1;j<=StartAge;j++)

					{

					siteptr->SpecieIndex(i)->setTreeNum(j,i,CellSize*CellSize);

					}

				}

			//GetSeedNumberOnSite(Row,Col);

			}

		}

	else

		{

		for(i=1;i<=siteptr->number();i++)

			{

			if(siteptr->specAtt(i)->SpType>=0)

				{

				for(j=1;j<=StartAge;j++)

					{
						
						DeadTree=siteptr->SpecieIndex(i)->getTreeNum(j,i)*GetMortalityRates(i,j,l->ltID);//" /(1+l->probRepro(i))" remove by Wenjuan Feb 04 2011;

					DeadTreeInt = DeadTree;

					if((DeadTree-(float)DeadTreeInt)>=0.0001){

							if(frand1()<0.1){

								DeadTreeInt++;

								}

							}
					int numnum = siteptr->SpecieIndex(i)->getTreeNum(j,i);
					siteptr->SpecieIndex(i)->setTreeNum(j,i,max(0,numnum-DeadTreeInt));//max(0,siteptr->SpecieIndex(i)->getTreeNum(j,i)-DeadTreeInt)
					//printf("4Col: %d, row: %d, deadtree: %d, orig tree %d, value to set %d\n", Col, Row, DeadTreeInt, numnum,max(0,numnum-DeadTreeInt));
					}

				}

			else{

				for(j=1;j<=StartAge;j++)

					{

					siteptr->SpecieIndex(i)->setTreeNum(j,i,CellSize*CellSize);

					}

				}

			}

		}

	}





}



//<Add By Qia on April 23 2010>

void SITES::SetOutputGeneralFlagArray(int i, int j, int value)

{

	if(i>(specNum+1)||j>NumTypes70Output)

		errorSys("Out bound in Flag Array\n",STOP);

	else

		OutputGeneralFlagArray[i*NumTypes70Output+j]= value;

}

int SITES::GetOutputGeneralFlagArray(int i, int j)

{

	if(i>(specNum+1)||j>NumTypes70Output)

		errorSys("Out bound in Flag Array\n",STOP);

	else

		return OutputGeneralFlagArray[i*NumTypes70Output+j];

}



void SITES::SetflagAgeOutput(int value)

{

	flagAgeRangeOutput = value;

}

int SITES::GetflagAgeOutput()

{

	return flagAgeRangeOutput;

}



void SITES::SetOutputAgerangeFlagArray(int i, int j, int value)

{

	if(i>(specNum+1)||j>NumTypes70Output)

		errorSys("Out bound in Flag Array\n",STOP);

	else

		OutputAgerangeFlagArray[i*NumTypes70Output+j]= value;

}

int SITES::GetOutputAgerangeFlagArray(int i, int j)

{

	if(i>(specNum+1)||j>NumTypes70Output)

		errorSys("Out bound in Flag Array\n",STOP);

	else

		return OutputAgerangeFlagArray[i*NumTypes70Output+j];

}





void SITES::SetSpeciesAgerangeArray(int specindex, int count, int value1, int value2)

{

	if(specindex>specNum)

		errorSys("Out bound in species age range\n",STOP);

	if (count>40)

		errorSys("Out bound in species age range\n",STOP);

	SpeciesAgerangeArray[specindex*500/TimeStep+count*2-1]=value1;

	SpeciesAgerangeArray[specindex*500/TimeStep+count*2]=value2;

}

int SITES::GetSpeciesAgerangeArray(int specindex, int count, int *value1, int *value2)

{

	if(specindex>specNum)

		errorSys("Out bound in species age range\n",STOP);

	if (count>40)

		errorSys("Out bound in species age range\n",STOP);

	*value1=SpeciesAgerangeArray[specindex*500/TimeStep+count*2-1];

	*value2=SpeciesAgerangeArray[specindex*500/TimeStep+count*2];

	return 1;

}



int SITES::GetAgerangeCount(int specindex)

{

	return SpeciesAgerangeArray[specindex*500/TimeStep];

}



int SITES::SetAgerangeCount(int specindex, int count)

{

	SpeciesAgerangeArray[specindex*500/TimeStep]=count;

	return 1;

}

//<Add By Qia on Dec 29 2010>

void SITES::SetAgeDistStat_YearVal(int specindex, int count, int value1)

{

	if(specindex>specNum)

		errorSys("Out bound in species age range\n",STOP);

	if (count>40)

		errorSys("Out bound in species age range\n",STOP);

	AgeDistStat_Year[specindex*500/TimeStep+count]=value1;

}

int SITES::GetAgeDistStat_YearVal(int specindex, int count, int *value1)

{

	if(specindex>specNum)

		errorSys("Out bound in species age range\n",STOP);

	if (count>40)

		errorSys("Out bound in species age range\n",STOP);

	*value1=AgeDistStat_Year[specindex*500/TimeStep+count];

	return 1;

}



int SITES::GetAgeDistStat_YearCount(int specindex)

{

	return AgeDistStat_Year[specindex*500/TimeStep];

}



int SITES::SetAgeDistStat_YearValCount(int specindex, int count)

{

	AgeDistStat_Year[specindex*500/TimeStep]=count;

	return 1;

}



/////////////////

void SITES::SetAgeDistStat_AgeRangeVal(int specindex, int count, int value1, int value2)

{

	if(specindex>specNum)

		errorSys("Out bound in species age range\n",STOP);

	if (count>40)

		errorSys("Out bound in species age range\n",STOP);

	AgeDistStat_AgeRange[specindex*500/TimeStep+count*2-1]=value1;

	AgeDistStat_AgeRange[specindex*500/TimeStep+count*2]=value2;

}

int SITES::GetAgeDistStat_AgeRangeVal(int specindex, int count, int *value1, int *value2)

{

	if(specindex>specNum)

		errorSys("Out bound in species age range\n",STOP);

	if (count>40)

		errorSys("Out bound in species age range\n",STOP);

	*value1=AgeDistStat_AgeRange[specindex*500/TimeStep+count*2-1];

	*value2=AgeDistStat_AgeRange[specindex*500/TimeStep+count*2];

	return 1;

}



int SITES::GetAgeDistStat_AgeRangeCount(int specindex)

{

	return AgeDistStat_AgeRange[specindex*500/TimeStep];

}



int SITES::SetAgeDistStat_AgeRangeCount(int specindex, int count)

{

	AgeDistStat_AgeRange[specindex*500/TimeStep]=count;

	return 1;

}





//</Add By Qia on Dec 29 2010>

void SITES::Read70OutputOption(char *FileName)

{

	FILE *fp,*fpAgeDist;

	int i,j=0,count=0,value1,value2;

	char temp[100],ch;

	printf("reading Landis 70 output customization file...\n");

	if ((fp = LDfopen(FileName, 1)) == NULL)

		{

			errorSys("Can not open Read70OutputOption file",STOP);

		}

	////general every species////

	for(i=0;i<specNum;i++)

		{

		fscanc(fp,"%s",temp);

		///////////////////

		//TPA

		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputGeneralFlagArray(i,TPA,1);

			}

		else{

			SetOutputGeneralFlagArray(i,TPA,0);

			}


		// BA
		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputGeneralFlagArray(i,BA,1);

			}

		else{

			SetOutputGeneralFlagArray(i,BA,0);

			}

		//BIO

		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputGeneralFlagArray(i,Bio,1);

			}

		else{

			SetOutputGeneralFlagArray(i,Bio,0);

			}
		//IV
		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputGeneralFlagArray(i,IV,1);

			}

		else{

			SetOutputGeneralFlagArray(i,IV,0);

			}
		//SEEDS
		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputGeneralFlagArray(i,Seeds,1);

			}

		else{

			SetOutputGeneralFlagArray(i,Seeds,0);

			}
		//RD
		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputGeneralFlagArray(i,RDensity,1);

			}

		else{

			SetOutputGeneralFlagArray(i,RDensity,0);

			}

		}

	///////below is for general total//////////

	fscanc(fp,"%s",temp);

	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

		{

		SetOutputGeneralFlagArray(specNum,TPA,1);

		}

	else{

		SetOutputGeneralFlagArray(specNum,TPA,0);

		}



	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

		{

		SetOutputGeneralFlagArray(specNum,BA,1);

		}

	else{

		SetOutputGeneralFlagArray(specNum,BA,0);

		}



	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

		{

		SetOutputGeneralFlagArray(specNum,Bio,1);

		}

	else{

		SetOutputGeneralFlagArray(specNum,Bio,0);

		}



	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

		{

		SetOutputGeneralFlagArray(specNum,Car,1);

		}

	else{

		SetOutputGeneralFlagArray(specNum,Car,0);

		}

	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

		{

		SetOutputGeneralFlagArray(specNum,RDensity,1);

		}

	else{

		SetOutputGeneralFlagArray(specNum,RDensity,0);

		}

	/////////////////////

	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

		{

		SetflagAgeOutput(1);

		}

	else{

		SetflagAgeOutput(0);

		}

	/////below is age range for every species///////

	for(i=0;i<specNum;i++)

		{

		fscanc(fp,"%s",temp);

		//////////////////////

		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(i,TPA,1);

			}

		else{

			SetOutputAgerangeFlagArray(i,TPA,0);

			}

		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(i,BA,1);

			}

		else{

			SetOutputAgerangeFlagArray(i,BA,0);

			}

		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(i,Bio,1);

			}

		else{

			SetOutputAgerangeFlagArray(i,Bio,0);

			}

		fscanc(fp,"%s",temp);

		if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(i,IV,1);

			}

		else{

			SetOutputAgerangeFlagArray(i,IV,0);

			}

		}

	///////below is for age range total//////////

	fscanc(fp,"%s",temp);

	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(specNum,TPA,1);

			}

		else{

			SetOutputAgerangeFlagArray(specNum,TPA,0);

			}

	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(specNum,BA,1);

			}

		else{

			SetOutputAgerangeFlagArray(specNum,BA,0);

			}

	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(specNum,Bio,1);

			}

		else{

			SetOutputAgerangeFlagArray(specNum,Bio,0);

			}

	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(specNum,Car,1);

			}

		else{

			SetOutputAgerangeFlagArray(specNum,Car,0);

			}

	fscanc(fp,"%s",temp);

	if(!strcmp(temp,"Y"))

			{

			SetOutputAgerangeFlagArray(specNum,RDensity,1);

			}

		else{

			SetOutputAgerangeFlagArray(specNum,RDensity,0);

			}

	////////////////////////

	for(i=0;i<specNum;i++)

		{

		fscanc(fp,"%s",temp);

		fscanf(fp,"%d",&count);

		SetAgerangeCount(i,count);

		for(j=1;j<=count;j++)

			{

			fscanf(fp,"%d",&value1);

			fscanf(fp,"%c",&ch);

			fscanf(fp,"%d",&value2);

			SetSpeciesAgerangeArray(i,j, value1, value2);

			}

		}



	///////////////////////

	fscanc(fp,"%s",temp);

	if(strcmp(temp,"N/A")!=0){

		Flag_AgeDistStat = 1;

		if ((fpAgeDist= LDfopen(temp, 1)) == NULL)

			{

				errorSys("Can not open Read70OutputOption file",STOP);

			}

		for(i=0;i<specNum;i++)

			{

			fscanc(fpAgeDist,"%s",temp);

			fscanf(fpAgeDist,"%d",&count);

			SetAgeDistStat_YearValCount(i,count);

			for(j=1;j<=count;j++)

				{

				fscanf(fpAgeDist,"%d",&value1);

				SetAgeDistStat_YearVal(i,j, value1);

				}

			}

		for(i=0;i<specNum;i++)

			{

			fscanc(fpAgeDist,"%s",temp);

			fscanf(fpAgeDist,"%d",&count);

			SetAgeDistStat_AgeRangeCount(i,count);

			for(j=1;j<=count;j++)

				{

				fscanf(fpAgeDist,"%d",&value1);

				fscanf(fpAgeDist,"%c",&ch);

				fscanf(fpAgeDist,"%d",&value2);

				SetAgeDistStat_AgeRangeVal(i,j, value1, value2);

				}

			}

		fclose(fpAgeDist);

		}

	else{

		Flag_AgeDistStat = 0;

		}

	///////////////////////

	fclose(fp);

}



//</Add By Qia on April 23 2010>

float SITES::GetSeedRain(int spec,int Distance)

{
	if (MaxDistofAllSpec / CellSize > 1){

		if ((spec - 1)*(MaxDistofAllSpec / CellSize + 2) + Distance >= specNum*(MaxDistofAllSpec / CellSize*MaxDistofAllSpec / CellSize + 2)){

			std::cout << "probability is zero" << std::endl;

			return 0;

		}

		else

			return SeedRain[(spec - 1)*(MaxDistofAllSpec / CellSize + 2) + Distance];
	}
	else {

		if ((spec - 1)*(2 + 2) + Distance >= specNum*(4 + 2)){

			std::cout << "probability is our of bound" << std::endl;

			return 0;

		}

		else

			return SeedRain[(spec - 1)*(MaxDistofAllSpec / CellSize + 2) + Distance];
	}



}

float SITES::GetGrowthRates(int spec,int year, int landtype_index)

{

if(spec<1&&spec>specNum&&spec*year>=specNum*(320/TimeStep+1))

	errorSys("Out bound in GetGrowthRates\n",STOP);

else{
	if(GrowthRates_file.size()==0){
		return GrowthRates[(spec-1)*(320/TimeStep+1)+year-1];
	}
	else{
		if(landtype_index<GrowthRates_file.size()){
			return GrowthRates_file.at(landtype_index)[(spec-1)*(320/TimeStep+1)+year-1];
		}
		else{
			errorSys("Out bound in GetGrowthRates\n",STOP);
		}
		
	}
}

	

}

float SITES::GetMortalityRates(int spec,int year, int landtype_index)

{

if(spec<1&&spec>specNum&&spec*year>=specNum*(320/TimeStep+1))

	errorSys("Out bound in GetMortalityRates\n",STOP);

else{
	if(MortalityRates_file.size()==0){
		return MortalityRates[(spec-1)*(320/TimeStep+1)+year-1];
	}
	else{
		if(landtype_index<MortalityRates_file.size()){
			return MortalityRates_file.at(landtype_index)[(spec-1)*(320/TimeStep+1)+year-1];
		}
		else{
			errorSys("Out bound in MortalityRates\n",STOP);
		}
		
	}
}

	

}



float SITES::GetVolume(int spec,int year, int landtype_index)

{

if(spec<1&&spec>specNum&&spec*year>=specNum*(320/TimeStep+1))

	errorSys("Out bound in GetVolume\n",STOP);

else{
	if(Volume_file.size()==0){
		return Volume[(spec-1)*(320/TimeStep+1)+year-1];
	}
	else{
		if(landtype_index<Volume_file.size()){
			return Volume_file.at(landtype_index)[(spec-1)*(320/TimeStep+1)+year-1];
		}
		else{
			errorSys("Out bound in Volume\n",STOP);
		}
		
	}
}

	//return Volume[(spec-1)*(320/TimeStep+1)+year-1];

}



void SITES::SetSeedRain(int spec,int Distance,float value)

{

	if (MaxDistofAllSpec / CellSize > 1){

		if ((spec - 1)*(MaxDistofAllSpec / CellSize + 2) + Distance >= specNum*(MaxDistofAllSpec / CellSize*MaxDistofAllSpec / CellSize + 2))

			errorSys("Out bound in SetSeedRain\n", STOP);

		else

			SeedRain[(spec - 1)*(MaxDistofAllSpec / CellSize + 2) + Distance] = value;
	}
	else{
		if ((spec - 1)*(2 + 2) + Distance >= specNum*(4 + 2))

			errorSys("Out bound in SetSeedRain\n", STOP);

		else

			SeedRain[(spec - 1)*(MaxDistofAllSpec / CellSize + 2) + Distance] = value;
	}
	



}

void SITES::SetGrowthRates(int flag, int spec,int year,float value,int index_landtype)
{
	if(spec<1&&spec>specNum&&spec*year>=specNum*(320/TimeStep+1))
		errorSys("Out bound in SetGrowthRates\n",STOP);
	else{
		if(flag == 0){
			GrowthRates[(spec-1)*(320/TimeStep+1)+year-1]=value;
		}
		else{
			if(index_landtype == GrowthRates_file.size()){
				float *temp = new float[specNum*(320/TimeStep+1)];
				GrowthRates_file.push_back(temp);
			}
			GrowthRates_file.at(index_landtype)[(spec-1)*(320/TimeStep+1)+year-1] = value;
		}
	}
}

void SITES::SetMortalityRates(int flag, int spec,int year,float value, int index_landtype)

{

if(spec<1&&spec>specNum&&spec*year>=specNum*(320/TimeStep+1))

	errorSys("Out bound in SetMortalityRates\n",STOP);

else{
	if(flag == 0){
		MortalityRates[(spec-1)*(320/TimeStep+1)+year-1]=value;
	}
	else{
		if(index_landtype == MortalityRates_file.size()){
			float *temp = new float[specNum*(320/TimeStep+1)];
			MortalityRates_file.push_back(temp);
		}
		MortalityRates_file.at(index_landtype)[(spec-1)*(320/TimeStep+1)+year-1] = value;
	}
}

	

}

void SITES::SetVolume(int growthrate_flag, int spec,int year,float value, int index_landtype)

{

if(spec<1&&spec>specNum&&spec*year>=specNum*(320/TimeStep+1))

	errorSys("Out bound in Volume\n",STOP);

else{
	if(growthrate_flag == 0){
		Volume[(spec-1)*(320/TimeStep+1)+year-1]=value;
	}
	else{
		if(index_landtype == Volume_file.size()){
			float *temp = new float[specNum*(320/TimeStep+1)];
			Volume_file.push_back(temp);
		}
		Volume_file.at(index_landtype)[(spec-1)*(320/TimeStep+1)+year-1] = value;
	}
}

	

}



void SITES::GetSeedDispersalProbability(char* fileSeedDispersal, int seedflag)

//Get seed dispersal probability on a site and save in a matrix consists of distance and probability

{

int i,j;

float temp;

int index;

SITE *sitetmp=SITES::operator()(1,1);

float **Probability;

int *number;

float probSum;

int count;



SeedRainFlag=seedflag;

//if (SeedRainFlag == 0)
//
//{
//
//	/*for(i=1;i<=specNum;i++)
//
//	   {
//
//	   for(j=1;j<=MaxDistofAllSpec/CellSize;j++)
//
//	   {
//
//	   temp=(2*sitetmp->specAtt(i)->TotalSeed/(3.1415926*(sitetmp->specAtt(i)->effectiveD)*(sitetmp->specAtt(i)->effectiveD))*exp((float)(-2.0*j*CellSize/sitetmp->specAtt(i)->effectiveD)));
//
//	   SetSeedRain(i,j,temp);
//
//	   }
//
//	   temp=(2*sitetmp->specAtt(i)->TotalSeed/(3.1415926*(sitetmp->specAtt(i)->effectiveD)*(sitetmp->specAtt(i)->effectiveD))*exp((float)(-2.0*CellSize/4/sitetmp->specAtt(i)->effectiveD)));
//
//	   SetSeedRain(i,0,temp);
//
//	   }*/ // Bu's code
//
//
//
//	for (i = 1; i <= specNum; i++)  //Wen's code
//
//	{
//
//
//		Probability = new float[sitetmp->specAtt(i)->maxD / CellSize + 1];
//
//		probSum = 0.0;
//
//		for (j = 0; j <= sitetmp->specAtt(i)->maxD / CellSize; j++)
//
//		{
//
//			Probability[j] = exp(-1.0*j / (sitetmp->specAtt(i)->maxD / CellSize));//changed by wenjuan on Mar 29 2011//Probability[j]= exp(-1.0*j/(MaxDistofAllSpec/CellSize));
//
//			probSum += Probability[j];
//
//		}
//
//		for (j = 0; j <= sitetmp->specAtt(i)->maxD / CellSize; j++)
//
//		{
//			if (j == 0){
//				temp = Probability[j] / probSum;
//			}
//			else{
//				temp = Probability[j] / probSum / (8 * j);
//			}
//			SetSeedRain(i, j, temp);
//
//		}
//
//		delete Probability;
//
//	}
//}



 if (SeedRainFlag == 0)

 {

	 for (i = 1; i <= specNum; i++)  //Wen's code

	 {
		 if (sitetmp->specAtt(i)->maxD / CellSize > 1){
			 // allocate memory for Probablility, it is a 2D array
			 Probability = new float*[(sitetmp->specAtt(i)->maxD / CellSize * 2) + 1];

			 for (int l = 0; l < (sitetmp->specAtt(i)->maxD / CellSize * 2) + 1; l++){
				 Probability[l] = new float[(sitetmp->specAtt(i)->maxD / CellSize * 2) + 1];
			 }

			 for (int m = 0; m < (sitetmp->specAtt(i)->maxD / CellSize * 2) + 1; m++){

				 for (int n = 0; n < (sitetmp->specAtt(i)->maxD / CellSize * 2) + 1; n++){

					 Probability[m][n] = 0;
				 }
			 }
			 // allocate memory for number
			 number = new int[((sitetmp->specAtt(i)->maxD / CellSize) *(sitetmp->specAtt(i)->maxD / CellSize) * 2) + 1];

			 for (int l = 0; l < ((sitetmp->specAtt(i)->maxD / CellSize) *(sitetmp->specAtt(i)->maxD / CellSize) * 2) + 1; l++){

				 number[l] = 0;
			 }
		 }
		 else{
			 Probability = new float*[3];

			 for (int l = 0; l < 3; l++){
				 Probability[l] = new float[3];
			 }

			 for (int m = 0; m < 3; m++){

				 for (int n = 0; n < 3; n++){

					 Probability[m][n] = 0;
				 }
			 }
			 // allocate memory for number
			 number = new int[3];

			 for (int l = 0; l < 3; l++){

				 number[l] = 0;
			 }
		 }

		 probSum = 0.0;

		 count = 0;

		 // Calculate distance

		 if (sitetmp->specAtt(i)->maxD / CellSize > 1){

			 for (int m = -sitetmp->specAtt(i)->maxD / CellSize; m <= sitetmp->specAtt(i)->maxD / CellSize; m++){

				 for (int n = -sitetmp->specAtt(i)->maxD / CellSize; n <= sitetmp->specAtt(i)->maxD / CellSize; n++){

					 index = m* m + n *n;

					 if (sqrt(index) <= sitetmp->specAtt(i)->maxD / CellSize){

						 //distancetemp = sqrt(index);

						 //number[index] = number[index] + 1;

						 temp = 0.52383 * 1 / sitetmp->specAtt(i)->alpha* exp(-sqrt(sqrt(index)*CellSize / sitetmp->specAtt(i)->alpha));

						 Probability[m + sitetmp->specAtt(i)->maxD / CellSize][n + sitetmp->specAtt(i)->maxD / CellSize] = temp;

						 SetSeedRain(i, index, temp);

						 /*if (number[index] == 1){

							  probSum += Probability[m + sitetmp->specAtt(i)->maxD / CellSize][n + sitetmp->specAtt(i)->maxD / CellSize];

							  }*/

						 //count++;

					 }

				 }
			 }

		 }
		 else{

			 for (int m = -1; m <= 1; m++){

				 for (int n = -1; n <= 1; n++){

					 //index = m* m + n *n;
					 index = sitetmp->specAtt(i)->maxD* sitetmp->specAtt(i)->maxD;
					

					// if (sqrt(index) <= sitetmp->specAtt(i)->maxD / CellSize){

						 //distancetemp = sqrt(index);

						 //number[index] = number[index] + 1;

					 temp = 0.52383 * 1 / sitetmp->specAtt(i)->alpha* exp(-sqrt(sqrt(index)*CellSize / sitetmp->specAtt(i)->alpha));

						 Probability[m +1][n+1] = temp;

						 SetSeedRain(i, index, temp);

						 /*if (number[index] == 1){

						 probSum += Probability[m + sitetmp->specAtt(i)->maxD / CellSize][n + sitetmp->specAtt(i)->maxD / CellSize];

						 }*/

						 //count++;

					// }

				 }
			 }

		 }
	/*	 for (int l = 0; l < ((sitetmp->specAtt(i)->maxD / CellSize) *(sitetmp->specAtt(i)->maxD / CellSize) * 2) + 1; l++){

			 std::cout << " distance: " << sqrt(l)* CellSize<<" number :"<< number[l] << std::endl;
		 }
		 std::cout << std::endl;*/
		/* std::cout << "probability before normalization" << std::endl;

		 for (int m = 0; m < (sitetmp->specAtt(i)->maxD / CellSize * 2) + 1; m++){

			 for (int n = 0; n < (sitetmp->specAtt(i)->maxD / CellSize * 2) + 1; n++){

				 std:: cout<< Probability[m][n] << " ";
			 }

			 std::cout << std::endl;
		 }*/
		 //for (int m = -sitetmp->specAtt(i)->maxD / CellSize; m <= sitetmp->specAtt(i)->maxD / CellSize; m++){

			// for (int n = -sitetmp->specAtt(i)->maxD / CellSize; n <= sitetmp->specAtt(i)->maxD / CellSize; n++){

			//	 index = m* m + n *n;

			//	 if (sqrt(index) <= sitetmp->specAtt(i)->maxD / CellSize){

			//		 //temp = Probability[m + sitetmp->specAtt(i)->maxD / CellSize][n + sitetmp->specAtt(i)->maxD / CellSize] / probSum / number[index];

			//		 temp = Probability[m + sitetmp->specAtt(i)->maxD / CellSize][n + sitetmp->specAtt(i)->maxD / CellSize] ;

			//		// Probability[m + sitetmp->specAtt(i)->maxD / CellSize][n + sitetmp->specAtt(i)->maxD / CellSize] = temp;

			//		 SetSeedRain(i, index, temp);

			//		 //std::cout << "distance:" << sqrt(index) << "    Probability:" << temp << std::endl;
			//	 }
			// }
		 //}
		// std::cout << std::endl;
		/* std::cout << "probability after normalization" << std::endl;

		 for (int m = 0; m < (sitetmp->specAtt(i)->maxD / CellSize * 2) + 1; m++){

			 for (int n = 0; n < (sitetmp->specAtt(i)->maxD / CellSize * 2) + 1; n++){

				 std::cout << Probability[m][n] << " ";
			 }

			 std::cout << std::endl;
		 }
*/
		
		 if (sitetmp->specAtt(i)->maxD / CellSize > 1){

			 for (int l = 0; l < (sitetmp->specAtt(i)->maxD / CellSize) + 1; l++){

				 delete[] Probability[l];
			 }

			 delete[] Probability;

			 delete[]  number;
		 }
		 else {
			 for (int l = 0; l < 3; l++){

				 delete[] Probability[l];
			 }

			 delete[] Probability;

			 delete[]  number;
		 }

	 }



}

else

{//Read From File

	FILE *fp;

	if ((fp = LDfopen(fileSeedDispersal, 1)) == NULL)

		errorSys("Seed Dispersal Probability file not found.",STOP);

	for(i=1;i<=specNum;i++)

	{

		if(sitetmp->specAtt(i)->maxD<0)

			{

				if (fscanc(fp,"%f",&temp)!=1)

		   			errorSys("Error reading in Seed Prob from seed disp file.",STOP);

				temp=abs(temp);//*sitetmp->specAtt(i)->TotalSeed);

				SetSeedRain(i,0,temp);

			}

		else

			{

			if (sitetmp->specAtt(i)->maxD<CellSize)

				{

				for(j=0;j<=1;j++)

					{

					if (fscanc(fp,"%f",&temp)!=1)

			   			errorSys("Error reading in Seed Prob from seed disp file.",STOP);

					temp=temp*sitetmp->specAtt(i)->TotalSeed;

					SetSeedRain(i,j,temp);

					}

				}

			else

				{

				for(j=0;j<=sitetmp->specAtt(i)->maxD/CellSize;j++)

					{

					if (fscanc(fp,"%f",&temp)!=1)

			   			errorSys("Error reading in Seed Prob from seed disp file.",STOP);

					temp=temp*sitetmp->specAtt(i)->TotalSeed;

					SetSeedRain(i,j,temp);

					}

				}

			}	

	}

	LDfclose(fp);

}

}

void SITES::GetSpeciesGrowthRates(char* fileGrowthRates, int growthrateflag)

//Reads or calculates species' growth rates at corresponding ages,  no return value

//Save the DBH and Age in a two dimension matrix, GrowthRates



{

int i,j,k;

float temp;

SITE *sitetmp=SITES::operator()(1,1);

GrowthFlag=growthrateflag;

if(GrowthFlag==0)

{

 for(i=1;i<=specNum;i++)

 	{

 	if(sitetmp->specAtt(i)->SpType==0)

 		{

 		for(j=1;j<=sitetmp->specAtt(i)->longevity/TimeStep+1;j++)

 			{

 			temp=exp(-11.37*exp(-0.088*j*TimeStep/sitetmp->specAtt(i)->longevity*100))*sitetmp->specAtt(i)->MaxDQ;

			SetGrowthRates(GrowthFlag,i,j,temp,0);

 			}

 		}

	else if(sitetmp->specAtt(i)->SpType==1)

		{

		for(j=1;j<=sitetmp->specAtt(i)->longevity/TimeStep+1;j++)

 			{

 			temp=exp(-11.7*exp(-0.12*j*TimeStep/sitetmp->specAtt(i)->longevity*100))*sitetmp->specAtt(i)->MaxDQ;

			SetGrowthRates(GrowthFlag,i,j,temp,0);

 			}

		}

	else

		{

		for(j=1;j<=sitetmp->specAtt(i)->longevity/TimeStep+1;j++)

 			{

 			SetGrowthRates(GrowthFlag,i,j,sitetmp->specAtt(i)->MaxDQ,0);

 			}

		}

 	}

}

else

{//Read data from file

	FILE *fp;

	if ((fp = LDfopen(fileGrowthRates, 1)) == NULL)

		errorSys("Specie Growth Rates file not found.",STOP);
	int numLU = 0;

	while (!LDeof(fp)){
		for(i=1;i<=specNum;i++)
		{
			for(j=1;j<=sitetmp->specAtt(i)->longevity/TimeStep;j++)
			{
				if (fscanc(fp,"%f",&temp)!=1)
   					errorSys("Error reading in growth rates from file.",STOP);
				SetGrowthRates(GrowthFlag, i,j,temp, numLU);
			}
		}
		numLU++;
	}

	LDfclose(fp);

}



}



void SITES::GetSpeciesMortalityRates(char* fileMortalityRates, int mortalityrateflag)

//Reads or calculates species' mortality rates at corresponding ages, No Return Value

//Save the DBH and Age in a two dimension matrix, MortalityRates

{

int i,j,k;

float temp;

SITE *sitetmp=SITES::operator()(1,1);

MortalityFlag=mortalityrateflag;

if(MortalityFlag==0)

{

}

else

{//read data from file

	FILE *fp;

	if ((fp = LDfopen(fileMortalityRates, 1)) == NULL)

		errorSys("Specie Mortality Rates file not found.",STOP);
//<Add By Qia on July 17 2013>
	//specific MortalityRates for different landtypes go here
//</Add By Qia on July 17 2013>
	int numLU = 0;

	while (!LDeof(fp)){
		for(i=1;i<=specNum;i++){
			for(j=1;j<=sitetmp->specAtt(i)->longevity/TimeStep;j++){
				if (fscanc(fp,"%f",&temp)!=1)
   					errorSys("Error reading in mortality rates from file.",STOP);
				SetMortalityRates(MortalityFlag,i,j,temp,numLU);
			}
		}
		numLU++;
	}
	LDfclose(fp);

}



}



void SITES::GetVolumeRead(char* fileVolumeFlag, int VolumeFlag_Flag)

{

	int i,j,k;

	float temp;

	SITE *sitetmp=SITES::operator()(1,1);

	float *VolumeTemp,TreeHeight;

	char FilenameHeights[FNSIZE];

	VolumeTemp=new float[specNum*6];

	VolumeFlag=VolumeFlag_Flag;

	if(VolumeFlag==0)

	{

		for(i=1;i<=specNum;i++)

			{

			for(j=1;j<=sitetmp->specAtt(i)->longevity/TimeStep;j++)

				{
				
				
				if(GrowthFlag == 0){
					temp=(-61.9+6.83*GetGrowthRates(i,j,0)/2.54)*pow(0.3048,3.0);
					SetVolume(GrowthFlag, i,j,temp,0);
				}
				else{
					for(int i_growth = 0;i_growth<GrowthRates_file.size();i_growth++){
						temp=(-61.9+6.83*GetGrowthRates(i,j,i_growth)/2.54)*pow(0.3048,3.0);
						SetVolume(GrowthFlag,i,j,temp,i_growth);
					}
				}
				

				}

			}

	}

	else

	{//read data from file

		FILE *fp,*fpTreeheight;

		if ((fp = LDfopen(fileVolumeFlag, 1)) == NULL)

			errorSys("fileVolumeFlag file not found.",STOP);

		fscanc(fp,"%d",&temp);

		VolumeFlag=temp;

		fscanc(fp,"%s",FilenameHeights);

		if ((fpTreeheight = LDfopen(FilenameHeights, 1)) == NULL)

			errorSys("FilenameHeights file not found.",STOP);

		

		if(VolumeFlag==1){

			for(i=1;i<=specNum;i++)

				{

				for(j=1;j<=6;j++)

					{

					fscanc(fp,"%f",&VolumeTemp[(i-1)*6+j-1]);

					}

				}

			for(i=1;i<=specNum;i++)

				{

				for(j=1;j<=sitetmp->specAtt(i)->longevity/TimeStep;j++)

					{

					fscanc(fpTreeheight,"%f",&TreeHeight);

					if(GrowthFlag == 0){
						temp=VolumeTemp[(i-1)*6]+VolumeTemp[(i-1)*6+1]*pow(GetGrowthRates(i,j,0),VolumeTemp[(i-1)*6+2])+VolumeTemp[(i-1)*6+3]*pow(GetGrowthRates(i,j,0),VolumeTemp[(i-1)*6+4])*pow(TreeHeight,VolumeTemp[(i-1)*6+5]);
						SetVolume(GrowthFlag, i,j,temp,0);
					}
					else{
						for(int i_growth = 0;i_growth<GrowthRates_file.size();i_growth++){
							temp=VolumeTemp[(i-1)*6]+VolumeTemp[(i-1)*6+1]*pow(GetGrowthRates(i,j,i_growth),VolumeTemp[(i-1)*6+2])+VolumeTemp[(i-1)*6+3]*pow(GetGrowthRates(i,j,i_growth),VolumeTemp[(i-1)*6+4])*pow(TreeHeight,VolumeTemp[(i-1)*6+5]);
							SetVolume(GrowthFlag,i,j,temp,i_growth);
						}
					}
					}

				}

			}

		else{

			errorSys("compute volume wrong",STOP);

			for(i=1;i<=specNum;i++)

			{

			for(j=1;j<=sitetmp->specAtt(i)->longevity/TimeStep;j++)

				{

				if (fscanc(fp,"%d",&temp)!=1)

					errorSys("Error reading in height rates from file.",STOP);

				
				if(GrowthFlag == 0){
					SetVolume(GrowthFlag, i,j,temp,0);
				}
				else{
					for(int i_growth = 0;i_growth<GrowthRates_file.size();i_growth++){
						SetVolume(GrowthFlag,i,j,temp,i_growth);
					}
				}
				}

			}

			}

		LDfclose(fpTreeheight);

		LDfclose(fp);

	}

	delete [] VolumeTemp;



}





//</Add By Qia on July 1 2009>

//<Add By Qia on July 7 2009>

float SITES::GetBiomassData(int i, int j)

{

	int temp;

	if(i>biomassNum||j<1||j>2)

		errorSys("index error at GetBiomass",STOP);

	temp=(i-1)*2+j-1;

	return biomassData[temp];

}

void SITES::SetBiomassData(int i, int j, float value)

{

	int temp;

	if(i>biomassNum||j<1||j>2)

		errorSys("index error at SetBiomass",STOP);

	temp=(i-1)*2+j-1;

	biomassData[temp]=value;

}

void SITES::SetBiomassNum(int num)

{

	biomassNum=num;

	biomassData=NULL;

	biomassData=new float[num*2];

}

void SITES::BiomassRead(FILE *fp)

//read biomass coefficients from a file into matrix, (float) BioMassData(int ID,2). No Return Value

//Read a ID first from the file, and ID is the size of BioMassData;

//Read the two variable in to BioMassData(v1,v2)

{

	int temp, i,j;

	float value;

	fscanc(fp,"%d",&temp);

	SetBiomassNum(temp);

	fscanc(fp,"%f",&value);

	SetBiomassThreshold(value);

	for(i=1;i<=temp;i++)

		{

		for(j=1;j<=2;j++)

			{

			if(fscanc(fp,"%f",&value)==EOF)

				errorSys("Error reading Biomassfile content",STOP);

			SetBiomassData(i,j,value);

			}	

			

		}

}



int SITES::GetMaxShadeTolerance()

{

	return MaxShadeTolerance;

}

//</Add By Qia on July 7 2009>



void SITES::SetBiomassThreshold(float num)

{

	BiomassThreshold=num;

}

float SITES::GetBiomassThreshold()

{

	return BiomassThreshold;

}



