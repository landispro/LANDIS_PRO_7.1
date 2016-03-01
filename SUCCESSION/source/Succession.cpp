/************************************************

Name:					Succession.cpp

Originally created by:  Hong

Modularized by:			Wei Li Oct. 7, 2003



*************************************************/



#include <string.h>

#include <time.h>

//#include <vld.h>



#include "system1.h"

#include "Succession.h"

#include "error.h"

#include <math.h>;

using namespace std;



#define NO_DISPERSAL  0     //No seed dispersal.

#define UNIFORM       1     //Uniform seed dispersal.

#define NEIGHBORS     2     //Seed to immediate neighbors.

#define DISPERSAL     3     //Seed within effective distance.

#define RAND_ASYM     4     //Seed using interpolated chaotic distances.

#define MAX_DIST      5     //RAND_ASYM up to maximum distances.

#define SIM_RAND_ASYM 6     //RAND_ASYM up to maximum distances, Simulated



SUCCESSION::~SUCCESSION()

{

	

}



SUCCESSION::SUCCESSION(SITES* pS, LANDUNITS* plu, OPTIM* pp, int cS)

{

	cellSize = cS;

	psites = pS;

	plandUnits = plu;

	poptim = pp;	

	CurrentIteration=-1;//Add By Qia on Jan 14 2009

}



/*void SUCCESSION::initiateVariableVector(int NumofIter, int temp)

{

	VectorIteration=new char[NumofIter];

	timestep=temp;

	Totaliteration=NumofIter;

	int i;

	char Timestep1[8]={-1,-1,-1,0,1,1,1,0};

	char Timestep2[6]={-1,-1,0,1,1,0};

	char Timestep3[4]={-1,0,1,0};

	char Timestep46[2]={-1,1};

	switch (timestep){

		case 1:

			for(i=0;i<Totaliteration;i++)

				{

					VectorIteration[i]=Timestep1[i%8];

				}

			break;

		case 2:

			for(i=0;i<Totaliteration;i++)

				{

					VectorIteration[i]=Timestep2[i%6];

				}

			break;

		case 3:

			for(i=0;i<Totaliteration;i++)

				{

					VectorIteration[i]=Timestep3[i%4];

				}

			break;

		case 4:

			for(i=0;i<Totaliteration;i++)

				{

					VectorIteration[i]=Timestep46[i%2];

				}

			break;

		case 5:

			for(i=0;i<Totaliteration;i++)

				{

					VectorIteration[i]=Timestep46[i%2];

				}

			break;

		case 6:

			for(i=0;i<Totaliteration;i++)

				{

					VectorIteration[i]=Timestep46[i%2];

				}

			break;

		default:

			for(i=0;i<Totaliteration;i++)

				{

					VectorIteration[i]=0;

				}

			break;

		}

}*/



void SUCCESSION::seed(SPECIESATTR *sa, LANDUNIT *l, SPECIE *s, int shade, int sn,

			 int row, int col, int dispRegime )

//The following routine selects the appropriate seed dispersal

//routine and switches to it.  The parameters are passed on to the

//individual routines.  They are discussed below.



{

//switch (parameters.dispRegime)

  switch (dispRegime)

	  {

		case NO_DISPERSAL:  noDisp(sa, l, s, shade, sn);

			  break;

		case UNIFORM:       uniDisp(sa, l, s, shade, sn);

			  break;

		case NEIGHBORS:     neighDisp(sa, l, s, shade, sn, row, col);

			  break;

		case DISPERSAL:     seedDisp(sa, l, s, shade, sn, row, col);

			  break;

		case RAND_ASYM:     randDisp(sa, l, s, shade, sn, row, col);

			  break;

		case MAX_DIST:      maxDisp(sa, l, s, shade, sn, row, col);

			  break;

		case SIM_RAND_ASYM: maxDisp(sa, l, s, shade, sn, row, col);

			  break;

	  }  

}





////////////////////////////////////////////////////////////////////////////

//                      SEED DISPERSAL REGIME SUPPORT ROUTINES            //

////////////////////////////////////////////////////////////////////////////



//All dispersal routines receive the current species attribute (sa), land

//unit type (l), Specie (s), shade value (shade), and species index number

//(sn).  The more complex routines also recieve the row, column map

//coordinates.  Each routine determines if the recruitement of the species

//will occur this year based on seed availability, light and probability

//of birth based on species type and landunit type.  If recruitment

//occurs birth is called.



void SUCCESSION::noDisp(SPECIESATTR *sa, LANDUNIT *l, SPECIE *s, int shade, int sn)

//Seed search only occurs on same site.



{

//if ((s->vegPropagules>0 && sa->vegProb>frand()) || s->disPropagules>0)

//	 //if (frand()<probBirth(sa, l, sn))

//	 if (frand() < (l->probRepro(sn)) )

//	if (enoughLight(sa, shade))

//				 s->birth();

}



void SUCCESSION::uniDisp(SPECIESATTR *sa, LANDUNIT *l, SPECIE *s, int shade, int sn)

//No seed search.  Seed is always present.



{

//if (frand()<probBirth(sa, l, sn))

if (frand()< (l->probRepro(sn)) )

	 if (enoughLight(sa, shade))

	 s->birth();

}



void SUCCESSION::neighDisp(SPECIESATTR *sa, LANDUNIT *l, SPECIE *s, int shade, int sn,

			 int row, int col)

//Seed search occurs on same site and immediate neighbors (including

//diagonals).



{

int i, j, minrow, mincol;

//if (frand()<probBirth(sa, l, sn))

if (frand()< (l->probRepro(sn)) )



//	minrow=min(row+1,sites.numRows());

//	mincol=min(col+1,sites.numColumns());

	minrow=min(row+1,psites->numRows());

	mincol=min(col+1,psites->numColumns());

	for (i=max(row-1,1);i<=minrow;i++)

		for (j=max(col-1,1);j<=mincol;j++)

		{

			//RScheller 5/12/03:  Check shade at other site:

//			int shade=findShade(sites(i,j));  //Shade class for site.

			int shade=findShade((*psites)(i,j));  //Shade class for site.

//			if ((*sites(i,j))(sn)->disPropagules>0 && enoughLight(sa, shade))

			if ((*(*psites)(i,j))(sn)->disPropagules>0 && enoughLight(sa, shade))

			{

				s->birth();

				

				return;

			}

		}

}



void SUCCESSION::seedDisp(SPECIESATTR *sa, LANDUNIT *l, SPECIE *s, int shade, int sn,

			int row, int col)

//Seed search occurs on same site and all sites in an uniform ring of the

//immediate site with radius sa->effectD.



{

	int minrow, mincol;

	int pixRange=sa->effectiveD/cellSize + 1;

	

	if (frand() < (l->probRepro(sn)) ) {//can establish itself

	

		if (enoughLight(sa, shade)) 

		{

			

			

			if (sa->effectiveD==-1)

			{

				s->birth();

				

				return;

			}

			/* J.Yang when effectiveD eqauls zero, 

			the seed dispersal should not happen

			*/

			if (sa->effectiveD == 0)

			{

				return;

			}

			minrow=min(row+pixRange,psites->numRows());

			mincol=min(col+pixRange,psites->numColumns());

			for (int i=max(row-pixRange,1);i<=minrow;i++)

				for (int j=max(col-pixRange,1);j<=mincol;j++)

				{					

					/* J.Yang using frand() here because the location

					of the seeding spp. in the site is unknown

					change the if (condition) order 

					to improve the efficiency

					*/

					SPECIE * temp_s;

					temp_s = (*(*psites)(i,j))(sn);

					

					if (temp_s->disPropagules>0)

					{

						

						if ( cellSize * (sqrt( ((row-i)*(row-i)+(col-j)*(col-j)) - frand()) )

							< sa->effectiveD )

						{

							s->birth();

							

							return;

						}

					}

				}

	}	

		}



}



void SUCCESSION::randDisp(SPECIESATTR *sa, LANDUNIT *l, SPECIE *s, int shade, int sn,

		 int row, int col)

//Seed search occurs on all sites on the map so that seeding is chaoticly

//based on sa->effectD and sa->maxD.  Cells within the radius defined

//by sa->effectD have a 95% chance of seeding to the current cell.  Cells

//within the radius defined by sa->maxD have a 5% chance of seeding to the

//current cells.  All other cells %chance may be calculated by fitting

//them on a asymptopic decay graph that runs through both points.



{

int i,j; //Nim: added this line

int minrow, mincol;

float tempnumb;





if (frand() < l->probRepro(sn) && enoughLight(sa, shade) && sa->effectiveD==-1)

{

	s->birth();

	return;

}

//int nr=sites.numRows();

//int nc=sites.numColumns();

int nr=psites->numRows();

int nc=psites->numColumns();



//int sd=parameters.cellSize+1;

int sd=cellSize+1;

int pixRange=sa->effectiveD/sd;

minrow=min(row+pixRange,nr);

mincol=min(col+pixRange,nc);

for (i=max(row-pixRange,1);i<=minrow;i++)

{

	for (j=max(col-pixRange,1);j<=mincol;j++)

	{

		//RScheller 5/12/03:  Check shade and reproductive ability at other site:

//		shade=findShade(sites(i,j));

		shade=findShade((*psites)(i,j));

//		l = sites(i,j)->landUnit;  //Land unit of other site.  Added RScheller

		

		l = psites->locateLanduPt(i,j);//Original landis4.0:l = (*psites)(i,j)->landUnit; change by Qia on Oct 13 2008

		if (frand() < l->probRepro(sn) && enoughLight(sa, shade) && (*(*psites)(i,j))(sn)->disPropagules>0)

		{

			tempnumb=(float)((row-i)*(row-i)+(col-j)*(col-j))*sd;

			tempnumb=(float)sqrt(tempnumb);

			if (sa->prob(tempnumb)>frand())

			{

				s->birth();

				return;

			}

		}

	}

}

// for all sites in the map check to see if seeding can take place from

// site(row, col)

for (i=1;i<=nr;i++) //Nim: changed int i to i

{

	for (j=1;j<=nc;j++) //Nim: changed int j to j

	{

		//RScheller 5/12/03:  Check shade and reproductive ability at other site:

		shade=findShade((*psites)(i,j));

		//l = (*psites)(i,j)->landUnit;  //Land unit of other site.  Added RScheller //Commented By Qia on Oct 13 2008

		l = psites->locateLanduPt(i,j);//Original landis4.0:l = (*psites)(i,j)->landUnit; change by Qia on Oct 13 2008

		if (frand() < l->probRepro(sn) && enoughLight(sa, shade) && (*(*psites)(i,j))(sn)->disPropagules>0)

		{

			tempnumb=(float)((row-i)*(row-i)+(col-j)*(col-j))*sd;

			tempnumb=(float)sqrt(tempnumb);

			if (sa->prob(tempnumb)>frand())

			{

				s->birth();

				return;

			}

		}

	}

}

}



void SUCCESSION::maxDisp(SPECIESATTR *sa, LANDUNIT *l, SPECIE *s, int shade, int sn,

			int row, int col)

//Seed search occurs on same site and all sites in an uniform ring of the

//immediate site within radius sa->maxD.  It will apply the random asymptopic

//dispersal seeding effect to all sites within this ring.



{

	int minrow, mincol;

	int pixRange=sa->maxD/cellSize + 1;

	if (sa->effectiveD == 0)

	{

		return;

	}

	

	if (frand() < (l->probRepro(sn)) ) //can establish itself

	{

		if (enoughLight(sa, shade)) 

		{



			if (sa->effectiveD==-1)

			{

				s->birth();

				return;

			}

			minrow=min(row+pixRange,psites->numRows());

			mincol=min(col+pixRange,psites->numColumns());

			for (int i=max(row-pixRange,1);i<=minrow;i++)

			{

				for (int j=max(col-pixRange,1);j<=mincol;j++)

				{					

					/* J.Yang using frand() here because the location

					of the seeding spp. in the site is unknown

					change the if (condition) order 

					to improve the efficiency

					*/

					SPECIE * temp_s;

					temp_s = (*(*psites)(i,j))(sn);

					if (temp_s->disPropagules>0 )

					{

						float tempD = cellSize * sqrt(float((row-i)*(row-i)+(col-j)*(col-j)));						

						if (sa->prob(tempD)> frand() )

						{

							s->birth();

							return;

						}

					}

				}

			}

		}

	}



	

}



void SUCCESSION::extraSeed(int numSitesActive, int snr, int snc, int specAtNum)

//Under the MAX_DIST seeding regime every site has a 1/1000th chance of

//receiving random seeds.  This implements this chance.



{

// int numSites=numSitesActive/1000;

int row, col, sn, shade;

SPECIE *s;

SPECIESATTR *sa;

for (int i=1;i<=numSitesActive;i++)

	 {

	  row=irand(1,snr); //Nim: was (rand()%snr)+1

	  col=irand(1,snc); //Nim: was (rand()%snc)+1

	  sn=irand(1,specAtNum); //Nim: was (rand()%specAtNum)+1

	  shade=findShade((*psites)(row,col));      //Shade class for site.

	  s=(*(*psites)(row,col))(sn);            //Specie being processed.

	  sa=(*psites)(row,col)->specAtt();         //Associated attributes.

	  if (poptim->speciesActive(sn) && enoughLight(sa, shade))

	  s->birth();

	  //birth(s);

	 }

}



////////////////////////////////////////////////////////////////////////////

//                      FIRST ORDER ITERATION SUPPORT ROUTINES            //

////////////////////////////////////////////////////////////////////////////



void SUCCESSION::grow(SPECIE *s, SPECIESATTR *sa)

//This will grow all trees and update propagules as necessary.

//Currently disPropagules are either set at 0 or 10 dependent on mature

//tree presence.  Vegetative propagules raise in number for every 10 years

//of mature tree presence.  They fall in number for every 10 years of

//mature tree absence.



{

	s->grow();	

	

	if (s->oldest()>=sa->maturity)

	{

		s->disPropagules = true; 

	}  

	else

	{

		s->disPropagules = false;

	}	

	

}



void SUCCESSION::vegProp(SPECIE *s, SPECIESATTR *sa, int shade)

{

	

if ( enoughLight(sa, shade) )

	if (sa->vegProb > frand() )

	{

		s->birth();

		

	}

	//return;

//vegPropagules is set when read in mapattribute file, should not be changed

//here

//if (s->oldest()>=sa->maturity && s->youngest()<=sa->maxSproutAge)

//	 s->vegPropagules=true;

//else

//	 s->vegPropagules=false;

}



void SUCCESSION::kill(SPECIE *s, SPECIESATTR *sa)

//This will kill any trees that have reached maximum age.



{





	float *e0; e0=new float; *e0=(float) 0.00000001;             //for 32 bit system

	int longev=sa->longevity;



	s->kill(longev);

	for(int j=longev+1; j<=320;j+=psites->TimeStep) 

		s->kill(j); 

	//mod R.Scheller... kill all older, in case user inputs cohorts present at

	//ages older than longevity.



	if (s->query())

	{

		int numYears=(int)(longev/5);

		float chanceDeath= (float) 0.20;

		float chanceMod=(float) 0.8/((float)numYears+*e0);   	

		for (int i=longev-numYears;i<longev;i+=psites->TimeStep)

		{

			if (frand()<(chanceDeath/10*psites->TimeStep))

				s->kill(i);

			chanceDeath+=chanceMod;

		}

	}

   delete e0;

}



void SUCCESSION::birth(SPECIE *s)

//This will give birth to new trees in the 10 year old age class.

// to avoid needless function calls this routine is not used CSH

{

  s->birth();

}



float SUCCESSION::probBirth(LANDUNIT *l, int speciesNum)

//This will return the probability of birth for a particular species on a

//particular land unit given ideal conditions.



{

  return l->probRepro(speciesNum);

}



int SUCCESSION::enoughLight(SPECIESATTR *sa, int shade)

//This wil return true if their is enough light at the forest floor for

//species birth and false otherwise.  Sa is a species attribute and shade is

//a shade class.



{

 int tempshade=sa->shadeTolerance;

 if (tempshade==5)  //Shade class 5 species may grow under a canopy

	return true;

 else if (tempshade==-1)//pseudo-shrub species is able to grow under any canopy

 	return true;

 else

	return tempshade>shade;

}



int SUCCESSION::findShade(SITE* site)

//This will return the amount of shade for this site.



{

 int shade=-1;        //pseudo-grass species

 SPECIE *specie=site->first();

 while (specie!=NULL)

	{

	 if (specie->oldest() >= site->specAtt()->maturity)

		  shade=max(site->specAtt()->shadeTolerance, shade);

	 specie=site->next();

	}

 return shade;

}





void SUCCESSION::findX1X2(int &x1, int &x2, int x, int y, int y1, int r)

//This will find the scan line (x1,x2) of a circle or radius r given that the

//center of the circle is at (x,y) and the scan line runs from (x1,y1) to

//(x2,y1).  It will also make sure that the entire scan line lies within the

//map boundaries.



{

int u, v;

int snc=psites->numColumns();



u=abs(y1-y);

v=r*r-u*u;

v=(int)(sqrt((float)v)+.999);

if ( (x - v) > 1 ) x1=(x-v);

else x1=1;

if ((x+v)<snc) x2=(x+v);

 else x2=snc;

}



void SUCCESSION::envChange(int i,int specAtNum, char* landUnitFile)

{

char str[50], iterString[5];

FILE *landTypeFile;

strcpy(str,landUnitFile);

itoa(i*psites->TimeStep,iterString,psites->TimeStep);

strcat(str,iterString);

if ((landTypeFile=fopen(str,"r"))==NULL)

	errorSys("Landtype input file not found.",STOP);

updateLandtype(landTypeFile,specAtNum); //J.Yang 04/16/2002

fclose(landTypeFile);

}



void SUCCESSION::updateLandtype(FILE* infile,int specAtNum)

//Read a land unit from a file.



{

int i; //Nim: added this line

LANDUNIT *l=plandUnits->first();

char instring[25];

int tempInt,tempClass[5];

int numberOfLandtype=0;

float tempFloat;

float *probReproduction=new float[specAtNum];



while(l)

{

	float *sppRep=l->probReproduction;

	if (fscanc(infile,"%s", instring)!=1)

   		errorSys("Error reading name from landtype file.",STOP);

	if (fscanc(infile,"%d", &tempInt)!=1)

   		errorSys("Error reading minShade from landtpye file.",STOP);

	if (fscanc(infile,"%d", &tempInt)!=1)

   		errorSys("Error reading fireInterval from landtype file.",STOP);

	if (fscanc(infile,"%f", &tempFloat)!=1)

   		errorSys("Error reading ignitionCoef from landtype file.",STOP);

	if (fscanc(infile,"%d", &tempInt)!=1)

   		errorSys("Error reading probCoef from landtype file.",STOP);

	if (fscanc(infile,"%d", &tempInt)!=1)

   		errorSys("Error reading lastWind from landtype file.",STOP);

	if (fscanc(infile,"%d", &tempInt)!=1)

   		errorSys("Error reading lastFire from landtype file.",STOP);



 	for (i=0;i<specAtNum;i++) //Nim: changed int i to i

	{

   	if (fscanc(infile,"%f",&probReproduction[i])!=1)

      	errorSys("Error reading in probReproduction from landtype file.",STOP);

      sppRep[i]=probReproduction[i];



	}

	for (i=0;i<5;i++)  //Nim: changed int i to i

	    if (fscanc(infile,"%d",&tempClass[i])!=1)

	       errorSys("Error reading in fireCurve from landtype file.",STOP);

	for (i=0;i<5;i++)  //Nim: changed int i to i

   	 if (fscanc(infile,"%d",&tempClass[i])!=1)

      	 errorSys("Error reading in fireClass from landtype file.",STOP);//J.Yang 04/17/2002

	for (i=0;i<5;i++)  //Nim: changed int i to i

	    if (fscanc(infile,"%d",&tempClass[i])!=1)

   	    errorSys("Error reading in windCurve from landtype file.",STOP);

	for (i=0;i<5;i++)  //Nim: changed int i to i

    	if (fscanc(infile,"%d",&tempClass[i])!=1)

      	 errorSys("Error reading in windClass from landtype file.",STOP);//J.Yang 04/17/2002

	numberOfLandtype++;

	l=plandUnits->next();

}

if(probReproduction)

delete [] probReproduction;

if (numberOfLandtype!=plandUnits->number())

	errorSys("The updating landtype files do not match.",STOP);

}

