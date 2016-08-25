#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "system1.h"

#include "error.h"

#include "landu.h"

#include "specatts.h"

#include "landus.h"



LANDUNITS::LANDUNITS(int n)

//Constructor.  N is equal to maximum array size for number of species.



{

numLU=0;

landUnits=new LANDUNIT[n];

currentLU=0;

maxLU=n;

}



LANDUNITS::~LANDUNITS()

//Destructor.

{

if (landUnits)     

   delete [] landUnits;

if(VectorIteration)

	delete [] VectorIteration;



}



void LANDUNITS::read(FILE* infile)

//Read set of land units from a file.

{

		numLU = 0;

		while (!LDeof(infile))

		{

			if (numLU<maxLU) //J.Yang 04/16/2002

			{

				 landUnits[numLU++].read(infile);

				 landUnits[numLU].ltID = numLU;		//add by Vera

			}

			else

				errorSys("LANDUNITS::read(FILE*)-> Array bounds error.",STOP);

		}

		

		printf("Number of landUnits: %d\n",numLU);

}



void LANDUNITS::write(FILE* outfile)

//Write set of land units to a file.



{

for (int i=0;i<numLU;i++)

{

    landUnits[i].write(outfile);

}

}



void LANDUNITS::dump()

//Dump set of land units to the CRT.



{

for (int i=0;i<numLU;i++)

{

    landUnits[i].dump();

    printf("===================================\n");

}

}



void LANDUNITS::attach(SPECIESATTRS *s)

//Attaches a set of species attributes to every land unit.  This must be

//performed following construction.



{

for (int i=0;i<maxLU;i++)

{

    landUnits[i].attach(s);

}

}



LANDUNIT* LANDUNITS::operator () (char *name)

//Referrence a land unit by land unit name.



{

for (int i=0;i<numLU;i++)

    if (strcmp(name,landUnits[i].name)==0)

       return &landUnits[i];



return NULL;

}



LANDUNIT* LANDUNITS::operator () (int n)

//Referrence a land unit by land unit number.



{

if (n>numLU || n<0)

	return NULL;

else

	return &landUnits[n];    

}



LANDUNIT* LANDUNITS::first()

//Referrence first land unit attribute.



{

currentLU=0;

if (numLU==0)

	 return NULL;

else

	 return &landUnits[0];

}



LANDUNIT* LANDUNITS::next()

//Referrence next land unit attribute.



{

currentLU++;

if (currentLU>=numLU)

	 return NULL;

else

	 return &landUnits[currentLU];

}



int LANDUNITS::number()

//Returns number of land units.



{

return numLU;

}

//<Original variance for SEC setup>

/*if(flag==1){

			char Timestep1[8]={-1,-1,-1,0,1,1,1,0};

			char Timestep2[6]={-1,-1,0,1,1,0};

			char Timestep3[4]={-1,0,1,0};

			char Timestep46[2]={-1,1};

			VectorIteration=new char[NumofIter];

			

			switch (timestep){

				case 1:

					for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=Timestep1[i%8]*(-1);

						}

					break;

				case 2:

					for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=Timestep2[i%6]*(-1);

						}

					break;

				case 3:

					for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=Timestep3[i%4]*(-1);

						}

					break;

				case 4:

					for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=Timestep46[i%2]*(-1);

						}

					break;

				case 5:

					for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=Timestep46[i%2]*(-1);

						}

					break;

				case 6:

					for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=Timestep46[i%2]*(-1);

						}

					break;

				default:

					for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=0;

						}

					break;

				}

			}

		if(flag==0){

			VectorIteration=new char[NumofIter];

				for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=0;

						}

			}

		if(flag==2){

				VectorIteration=new char[NumofIter];

				for(i=0;i<Totaliteration;i++)

						{

							VectorIteration[i]=0;

						}

		}

	if(flag==-1){//Varianes are decided by system

		char Timestep1[8]={-1,-1,-1,0,1,1,1,0};

		char Timestep2[6]={-1,-1,0,1,1,0};

		char Timestep3[4]={-1,0,1,0};

		char Timestep46[2]={-1,1};

		VectorIteration=new char[NumofIter];

		

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



//</Original Variance for SEC setup>

//<Add By Qia on Jan 20 2009>

void LANDUNITS::initiateVariableVector(int NumofIter, int temp, int num, int flag, char *fileSEC)

{

	

		timestep=temp;

		Totaliteration=NumofIter;

		numSpecies=num;

		flagforSECFile=flag;

		ReprodBackup();

		int i;

		int flagForVariance=0;

		int randnumber=0;

		int onceVarianceLast=0;

		VectorIteration=new char[NumofIter];

		if(frand1()>0.5)

			{

				flagForVariance=-1;

			}

		else{

				flagForVariance=1;

			}

		if(flag==0){

			for(i=0;i<Totaliteration;i++)

				{

					VectorIteration[i]=0;

				}

			}

		else if(flag==1){

			if(timestep>=5)

				{

				for(i=0;i<Totaliteration;i++)

					{

						VectorIteration[i]=0;

					}

				}

			else{

					for(i=0;i<Totaliteration;)

						{

							if(onceVarianceLast==0){

								randnumber=frandrand()%2+3;

								onceVarianceLast=randnumber/timestep;

								if(onceVarianceLast==0)

									onceVarianceLast=1;

								flagForVariance=flagForVariance*(-1);

								}

							else{

								VectorIteration[i]=flagForVariance;

								i++;

								onceVarianceLast--;

								}

						}

				}

			}

		else if(flag==2){

			for(i=0;i<Totaliteration;i++)

				{

					if(frand1()>0.5)

						{

							VectorIteration[i]=1;

						}

					else

						{

							VectorIteration[i]=-1;

						}

				}

			}

		else{

			}

				

		

}



void LANDUNITS::ReprodBackup()

{

	int i,j;

	for (i=0;i<numLU;i++)

		{

			for(j=0;j<numSpecies;j++)

			landUnits[i].probReproductionOriginalBackup[j]=landUnits[i].probReproduction[j];

		}

}



void LANDUNITS::ReprodUpdate(int year)

{

	int i,j;

	if(flagforSECFile==3||flagforSECFile==0)

		return ;

	for (i=0;i<numLU;i++)

		{

			for(j=0;j<numSpecies;j++){

			landUnits[i].probReproduction[j]=(landUnits[i].probReproductionOriginalBackup[j]/10*timestep)*(1+VectorIteration[year-1]);

			}

		}

	

}



//</Add By Qia on Jan 20 2009>



