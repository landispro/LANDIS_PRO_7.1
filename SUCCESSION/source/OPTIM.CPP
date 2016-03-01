#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "defines.h"

#include "error.h"

#include "landu.h"

#include "specatt.h"

#include "specie.h"

//#include "landis.h"

#include "optim.h"



OPTIM::OPTIM()

//Constructor.



{

specNum=0;

rows=0;

cols=0;

active=NULL;

mature=NULL;

}





OPTIM::~OPTIM()

//Destructor.



{

if(active!=NULL) 

	delete [] active; 

if(mature!=NULL)

	delete [] mature; 

}



void OPTIM::dim(int sn, int r, int c, SITES* pS, SPECIESATTRS*  psa)

//Constructor.  First Parameters are number of

//species, number of rows and columns.



{

specNum=sn;

rows=r;

cols=c;

active=NULL;

mature=NULL;

active=new unsigned char[specNum];

//<Changed By Qia on Oct 24 2008>

mature=new unsigned char[specNum*rows*cols/8+8]; //Original 4.0: mature=new unsigned char[specNum*rows*cols]; 

//</Changed By Qia on Oct 24 2008>

psites = pS;

pspeciesAttrs = psa;

}



void OPTIM::initialize()

//This will initialize or reinitialize the map.





{

int i, j, snr, snc, specAtNumb;

specAtNumb=pspeciesAttrs->number();



for (i=1;i<=specAtNumb;i++)

    if (strncmp((*pspeciesAttrs)(i)->name,"popu",4)==0)

        active[i-1]=true;     //Aspen are always active.

    else

        active[i-1]=false;

    

snr=psites->numRows();

snc=psites->numColumns();    

int tempOldest = 0;    

for (i=1;i<=snr;i++)

    for (j=1;j<=snc;j++)

        {

         //Define Land unit.

         LANDUNIT *l=psites->locateLanduPt(i,j);//Original Landis4.0: (*psites)(i,j)->landUnit, Changed By Qia on Oct 10 2008

         if (l!=NULL && l->active())

             {

              SPECIE *s=(*psites)(i,j)->first();

              SPECIESATTR *sa=(*psites)(i,j)->specAtt();

              int speciesNum=1;         

              

              //Inner loop; Loops through all species on a site.

              while (s!=NULL)

               {

                 if (s->query() || s->vegPropagules)

                   {

                    active[speciesNum-1]=true;

                   }

				 tempOldest=s->oldest();

                 if ( (tempOldest!=0)&&((tempOldest>=sa->maturity)||(tempOldest>=sa->maxSproutAge)) )

                  {//<commented By Qia to compress optim on Oct 24 2008>

				 	//mature[((speciesNum-1)*rows*cols)+((i-1)*cols)+(j-1)]=true; //Original Landis4.0

				 	//</commented By Qia to compress optim on Oct 24 2008>

				 	//<Add By Qia on Oct 24 2008>

					unsigned char bitBuffer=0;

					int Positiontemp;

					Positiontemp=((speciesNum-1)*rows*cols)+((i-1)*cols)+(j-1);

				    bitBuffer=mature[Positiontemp/8];

					bitBuffer=bitBuffer|(1<<(7-Positiontemp%8));

					mature[Positiontemp/8]=bitBuffer;

					//</Add By Qia on Oct 24 2008>

                 	}

                 else

                  {//<commented By Qia to compress optim on Oct 24 2008>

				 	//mature[((speciesNum-1)*rows*cols)+((i-1)*cols)+(j-1)]=false; //Original Landis4.0

				 	//</commented By Qia to compress optim on Oct 24 2008>

				 	//<Add By Qia on Oct 24 2008>

					unsigned char bitBuffer=0;

					int Positiontemp=((speciesNum-1)*rows*cols)+((i-1)*cols)+(j-1);

				    bitBuffer=mature[Positiontemp/8];

					bitBuffer=bitBuffer&~(1<<(7-Positiontemp%8));

					mature[Positiontemp/8]=bitBuffer;

                 	}

				 //</Add By Qia on Oct 24 2008>

                  //Loop to next species and species attribute.

                 s=(*psites)(i,j)->next();

                 sa=(*psites)(i,j)->specAtt();    

                 speciesNum++;

               }

            } 

          else

            {

             for (int speciesNum=1;speciesNum<=specAtNumb;speciesNum++)

                  { //<commented By Qia to compress optim on Oct 24 2008>

				 	//mature[((speciesNum-1)*rows*cols)+((i-1)*cols)+(j-1)]=false; //Original Landis4.0

				 	//</commented By Qia to compress optim on Oct 24 2008>

				 	//<Add By Qia on Oct 24 2008>

					unsigned char bitBuffer=0;

					int Positiontemp=((speciesNum-1)*rows*cols)+((i-1)*cols)+(j-1);

				    bitBuffer=mature[Positiontemp/8];

					bitBuffer=bitBuffer&~(1<<(7-Positiontemp%8));

					mature[Positiontemp/8]=bitBuffer;

			 //</Add By Qia on Oct 24 2008>

			 }

            }

       }

	

}



int OPTIM::speciesActive(int sn) 

//This will return true if a species referrenced

//by number is active.

   /// 28JUL94_CSH

{

if (sn>0 && sn<=pspeciesAttrs->number())

    return active[sn-1];

else

{

   errorSys("ERROR:  Illegal species number OPTIM::speciesActive",STOP);

   return -999;

}

}



//<changed By Qia on Oct 24 2008>

unsigned char OPTIM::operator()(int sn, int r,int c) //Original 4.0: unsigned char *OPTIM::operator()(int sn, int r,int c) 

//</changed By Qia on Oct 24 2008>

//This will return a referrence to the appropriate species, row, column

//cordinate in the maturity array.



{

int ref;

if (sn<1 || sn>pspeciesAttrs->number() ||

    r<1 || r>rows ||

    c<1 || c>cols)

    errorSys("OPTIM bounds error",STOP);



sn--;

r--;

c--;

ref=(sn*rows*cols)+(r*cols)+c;

//<commented By Qia on Oct 24 2008>

//return &mature[ref];

//</commented By Qia on Oct 24 2008>

//<Add By Qia on Oct 24 2008>

if (mature[ref/8]&(1<<(7-ref%8)))

{

	return 1;

}

else

{

	return 0;

}



//</Add By Qia on Oct 24 2008>

}





void OPTIM::dump()

//This dumps some simple statistics on seed availability.



{

int i,j,k;

int p=0;



for (i=0;i<18;i++)

  {

   int number=0;

   for (j=0;j<rows;j++)

       for (k=0;k<cols;k++)

	   	//if (mature[p++])

	      // number++;

           //<changed by Qia on Oct 24 2008>

           if (mature[p/8]&(1<<(7-p%8)))

		   	{number++;p++;}

		   //</changed By Qia on Oct 24 2008>

   printf("Species=%d, Number=%d\n",i+1,number);	

  }

}    

