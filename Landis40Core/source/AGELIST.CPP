#include <ctype.h>

#include <stdio.h>

#include "defines.h"

#include "system1.h"

#include "error.h"

#include "agelist.h"

//#include <vld.h>

//<Add By Qia on Jan 05 2009>

#include "GlobalVariables.h"

//</Add By Qia on Jan 05 2009>

#include <algorithm>//add by Qia on March 04 2009





//<Add By Qia on Jan 05 2009>

static unsigned int times=10;

//</Add By Qia on Jan 05 2009>





//<Add By Qia on Jan 06 2009>

static int *countofagevector;

//</Add By Qia on Jan 06 2009>







///////////////////////////////////////////////////////////////////////////////

//			CONSTANT DECLARATIONS				     //

///////////////////////////////////////////////////////////////////////////////



//The following masks are used by the AGELIST class to process bits.  lowMask

//is a mask with the low bit set.  highMask has the high bit set and fullMask

//has all bits sets.  Mask is an array with 32 elements, each having their

//respective bit set.



static const unsigned long lowMask=0x00000001;

static const unsigned long highMask=0x80000000;

static const unsigned long fullMask=0XFFFFFFFF;

static const unsigned long mask[32] =

{

0x00000001, 0x00000002, 0x00000004, 0x00000008,

0x00000010, 0x00000020, 0x00000040, 0x00000080,

0x00000100, 0x00000200, 0x00000400, 0x00000800,

0x00001000, 0x00002000, 0x00004000, 0x00008000,

0x00010000, 0x00020000, 0x00040000, 0x00080000,

0x00100000, 0x00200000, 0x00400000, 0x00800000,

0x01000000, 0x02000000, 0x04000000, 0x08000000,

0x10000000, 0x20000000, 0x40000000, 0x80000000

};



//////////////////////////////////////////////////////////////////////////////

//			    AGELIST CLASS CODE				    //

//////////////////////////////////////////////////////////////////////////////

void timestep::gettimestep(int temp)

{

  Time_step=temp;

  times=temp;

  int residue;

  //residue=320%temp;

  //if(residue==0)

  	//countofagevector=320/temp;

  //else

}

//<Add By Qia on June 30 2009>

//<Add By Qia on July 5 2009>

void timestep::getSpecNum(int num)

{

	SpecNum=num;

	countofagevector=new int[num];

}

void timestep::Setlongevity(int i,int num)

{

	if(i>SpecNum)

		errorSys("Illegal spec index in set longevity",STOP);

	countofagevector[i-1]=num/times;

}

timestep::~timestep()

{

	delete countofagevector;

}

//</Add By Qia on July 5 2009>

int AGELIST::getTreeNum(int n,int specIndex)

{

	if(n==0)

		return 0; //Add By Qia on March 23 2010 for 'n' index 0 bug

	if(n<0||n>countofagevector[specIndex-1]){

		printf("%d,%d,%d",n,countofagevector[specIndex-1],agevector[n]);

		errorSys("Index age error in agelist 70 Pro",STOP);

	}

	return agevector[n];

}

void AGELIST::setTreeNum(int n, int specIndex, int num)

{

	if(n<1||n>countofagevector[specIndex-1])

		errorSys("set age error in agelist 70 Pro",STOP);

	agevector[n]=num;

	if(num<0)

		agevector[n]=0;

	return ;

}

void AGELIST::GrowTree(int specIndex)

{

	int i=0;

	for(i=agevector[0];i>1;i--)

		{

			agevector[i]=agevector[i-1];

		}

	agevector[1]=0;

}

//</Add By Qia on June 30 2009>



//<Add By Qia on Jan 12 2009>

int AGELIST::getAgeVector(int i)

{

	if(i<0)//||i>=countofagevector)

		{

			errorSys("AGELIST::set()-> Illegal age.",STOP); 

		}

	return agevector[i];

}

//</Add By Qia on Jan 12 2009>



//<Add By Qia on Jan 12 2009>

int AGELIST::getAgeVectorNum()

{	

	return agevector[0];

}

int AGELIST::getTimeStep()

{

	return times;

}



//</Add By Qia on Jan 12 2009>



AGELIST::AGELIST()

{

	agevector=NULL;

}



void AGELIST::AGELISTAllocateVector(int index)

//Constructor.



{

	//<Add By Qia on Jan 07 2009>

	agevector=NULL;

	agevector=new int[countofagevector[index]+1];

	int i;

	agevector[0]=countofagevector[index];

	for(i=1;i<=countofagevector[index];i++)

		{

			agevector[i]=0;

		}

	//</Add By Qia on Jan 07 2009>

//original 4.0

//young=0;

//old=0;

}

//<Add By Qia on March 04 2009>

AGELIST::AGELIST(const AGELIST& agelist)

{

	agevector=new int[agelist.agevector[0]+1];printf("call copy constructor\n");

	for(int i=0;i<=agelist.agevector[0];i++)

		{

			agevector[i]=agelist.agevector[i];

		}

}

/*AGELIST& AGELIST::operator = ( const AGELIST& agelist )

{

	if(this!= &agelist)

		{

			agevector=new unsigned long[countofagevector];

			std::copy( agelist.agevector, agelist.agevector +countofagevector, countofagevector );

		}

	return *this;

}*/

//<Add By Qia on Jan 09 2009>

AGELIST& AGELIST::operator=(const AGELIST& s)

{

	if(agevector!=NULL)

		delete [] agevector;

	agevector=new int[s.agevector[0]+1];

	for(int i=0;i<=s.agevector[0];i++)

		{

			agevector[i]=s.agevector[i];

		}		

	return *this;

}



//</Add By Qia on Jan 09 2009>



AGELIST::~AGELIST()

{ 

	if(agevector){

	delete [] agevector;

	}

}

//<Add By Qia on March 04 2009>



void AGELIST::clear()

//Clear agelist.



{

	//<Add By Qia on Jan 07 2009>

	int i;

	if(agevector==NULL)

		{

		agevector=new int[320+1];

		agevector[0]=320;

		for(i=1;i<=agevector[0];i++)

			{

				agevector[i]=0;

			}

		}

	else{

		for(i=1;i<=agevector[0];i++)

				{

					agevector[i]=0;

				}

		}

	//</Add By Qia on Jan 07 2009>

	//original 4.0

	//young=0;

	//old=0;



}



void AGELIST::set(int age)

//Set an age to true.



{

if(age%times==0)

age=age/times;//Changed By Qia on Jan 05 2009

else

	age=age/times+1;

#ifdef BOUNDSCHECK

if (age<1 || age>320/times)//Changed By Qia on Jan 07 2009

   errorSys("AGELIST::set()-> Illegal age.",STOP);

#endif

//<Add By Qia on Jan 07 2009>

int temp1,temp2;

temp1=(age-1)/32;

temp2=(age-1)%32;

if(age==64)

	printf("something happend\nn");

agevector[temp1]|=mask[temp2];

//</Add By Qia on Jan 07 2009>

/*if (age<=31)

    {

     young |= mask[age];

    }

else

    {

     old |= mask[age-32];

    }*/

}



void AGELIST::reset(int age)

//Reset an age to false.



{

if(age%times==0)

age=age/times;//Changed By Qia on Jan 05 2009

else

	age=age/times+1;

#ifdef BOUNDSCHECK

if (age<1 || age>320/times)

   errorSys("AGELIST::reset()-> Illegal age.",STOP);

#endif

//<Add By Qia on Jan 07 2009>

if(age<1||age>agevector[0])

	errorSys("Agelist Reset Problem",STOP);

agevector[age]=0;

//</Add By Qia on Jan 07 2009>   

/*if (age<=31)

    {

     young &= ~mask[age];

    }

else

    {

     old &= ~mask[age-32];

    }*/

}  



void AGELIST::shiftOld()

//Shift all ages up one to the next age class.



{

//<Add By Qia on Jan 07 2009>

/*int i;

if(countofagevector==1)

{

	agevector[0]<<=1;

	return ;

}

for(i=countofagevector-1;i>=0;i--)

{

	agevector[i]<<=1;

	if(i>0){

		if((agevector[i-1]&highMask))

			{	

				agevector[i]|=lowMask;

			}

	}

}*/

//</Add By Qia on Jan 07 2009>

/*

old <<= 1;

if (young & highMask)

    old |= lowMask;

young <<= 1;*/

}



int AGELIST::query()

//Returns true if any age clases are present, false otherwise.



{

int i,result=0;

for(i=1;i<=agevector[0];i++)

{

	result=result||agevector[i];

}

return result;

}





int AGELIST::query(int age)

//Return true if an age exists in the list, false otherwise.



{

if(age%times==0)

age=age/times;//Changed By Qia on Jan 05 2009

else

	age=age/times+1;

#ifdef BOUNDSCHECK

if (age<1 || age>320/times)

   errorSys("AGELIST::query(int)-> Illegal age.",STOP);

#endif

//<Add By Qia on Jan 07 2009>

if(age<1||age>agevector[0])

	errorSys("Agelist query Problem",STOP);



return agevector[age];

//</Add By Qia on Jan 07 2009>

/*

if (age<=31)

    {

     return young&mask[age];

    }

else

    {

     return old&mask[age-32];

    }*/

}  

 

int AGELIST::query(int low, int high)

//Return true if an age exists in the range bounded by low and high,

//false otherwise.



{

int i;

if(low%times==0)

low=low/times;//Changed By Qia on Jan 05 2009

else

	low=low/times+1;

#ifdef BOUNDSCHECK

if (low<1 || low>320/times)

   errorSys("AGELIST::query(int,int)-> Illegal lower bound.",STOP);

#endif

if(high%times==0)

high=high/times;//Changed By Qia on Jan 05 2009

else

	high=high/times+1;

#ifdef BOUNDSCHECK

if (high<1 || high>320/times)

   errorSys("AGELIST::query(int,int)-> Illegal upper bound.",STOP);

if (low>high)

   errorSys("AGELIST::query(int,int)-> Lower bound is greater than\

             upper bound.",STOP);

#endif

//<Add By Qia on Jan 08 2009>

for(i=low;i<=high;i++){

	if(i<1||i>agevector[0])

		errorSys("Agelist Reset Problem",STOP);

	if(agevector[i])

		return true;

}

//</Add By Qia on Jan 08 2009>

/*

for (i=low;i<=min(high,31);i++)

   if (young & mask[i])

      return true;



for (i=max(low-32,0);i<=high-32;i++)

   if (old & mask[i])

       return true;

*/



return false;       

}  



int AGELIST::youngest()

//Returns the youngest age present.



{

int i,j;

unsigned long y;

//<Add By Qia on Jan 07 2009>

for(j=1;j<=agevector[0];j++)

{

	if(agevector[j]>0)

		return (j)*times;

}

//<Add By Qia on Jan 07 2009>

/*

y=young;

o=old;



for (i=0;i<32;i++)

   {

    if (y&lowMask)

       return (i+1)*times;

    y>>=1;

   }   



for (i=0;i<32;i++)

   {

    if (o&lowMask)

       return (i+1)*times+320;

    o>>=1;

   }*/



return 0;   

}   



int AGELIST::oldest()

//Returns the oldest age present.



{

int i,j;

unsigned long o;





//<Add By Qia on Jan 07 2009>

for(j=agevector[0];j>=1;j--)

{

	if(agevector[j]>0)

		return (j)*times;

}

//<Add By Qia on Jan 07 2009>





/*

y=young;

o=old;



for (i=0;i<32;i++)

   {

    if (o&highMask)

       return (64-i)*times;

    o<<=1;

   }   



for (i=0;i<32;i++)

   {

    if (y&highMask)

       return (32-i)*times;

    y<<=1;

   }*/

return 0;   

} 



int AGELIST::number()

//Returns the number of age classes present.



{

int j,i,c=0;

//<Add By Qia on Jan 07 2009>

for(j=1;j<=agevector[0];j++)

{

	if(agevector[j]>0)

		c++;

}

//</Add By Qia on Jan 07 2009>

/*unsigned long y, o;



y=young;

o=old;



for (i=0;i<32;i++)

   {

    if (y&lowMask)

       c++;

    y>>=1;

   }   



for (i=0;i<32;i++)

   {

    if (o&lowMask)

        c++;

    o>>=1;

   }*/

return c;

}    

//<Add By Qia on Feb 26 2009>

void AGELIST::readBinary(FILE *infile)

{

	char ch;

	int j,numRead=0,temp1,temp2;

	//clear(specIndex);

	skipblanks(infile);

	for (j=0;j<320/times && ((ch=(char)LDfgetc(infile))!=EOF) && isdigit(ch);j++)

		{

			if(ch=='1')

				{

					temp1=j/32;

					temp2=j%32;

					agevector[temp1]=agevector[temp1]|mask[temp2];

				}

			else if(ch=='0')

				{

				}

			else

				{

					printf("read map attribute age error\n");

					errorSys("read map attribute age error\n",STOP);

				}

		}

}

//</Add By Qia on Feb 26 2009>

void AGELIST::read(FILE* infile)

//This shall read an age list from a file.



{

	

char ch;

int j,numSet=0,buffer1=0,buffer2=0,temp1,temp2,temp,barflag=0;

clear();



skipblanks(infile);

for (j=0;numSet<=320 && ((ch=(char)LDfgetc(infile))!=EOF);j++)

   {

    if(isdigit(ch))

		{

			if(barflag==0)

				buffer1=buffer1*10+ch-48;

			else

				buffer2=buffer2*10+ch-48;

    	}

	else{

			if(ch=='-')

				{

					barflag=1;

				}

			else if(ch==' ')

				{

					if(barflag==1)

						{

							barflag=0;

							for(temp=buffer1;temp<=buffer2;temp=temp+times)

								{

									if(temp>=times){

										agevector[temp/times]=1;

										numSet++;

										}									

								}

							buffer1=0;

							buffer2=0;

						}

					else{

							temp=buffer1;

							if(temp>=times){

										agevector[temp/times]=1;

										numSet++;

										buffer1=0;

										buffer2=0;

										}

							

						}

				}

			else

				{

					if(barflag==1)

						{

							barflag=0;

							for(temp=buffer1;temp<=buffer2;temp=temp+times)

								{

									if(temp>=times){

										agevector[temp/times]=1;

										numSet++;

										}

									

								}

							buffer1=0;

							buffer2=0;

						}

					else{

							

							temp=buffer1;

							if(temp>=times){

								agevector[temp/times]=1;

								numSet++;

								buffer1=0;

								buffer2=0;

								}

						}

					break;

				}

		}

	}

    /*young>>=1;

    if (old & lowMask)

         young=young | highMask;

    old>>=1;

    if (ch=='1')

         old=old | highMask;*/



   /*

for (j=1;j<=(64-numRead);j++)

   {

    young>>=1;

    if (old & lowMask)

       young=young|highMask;

    old>>=1;

   }   */

}

void AGELIST::readTreeNum(FILE* infile, int specIndex)

{

	char ch;

	int j,numSet=0,buffer1=0,buffer2=0,spaceflag=0;

	clear();



	skipblanks(infile);

	for (j=0;numSet<countofagevector[specIndex] && ((ch=(char)LDfgetc(infile))!=EOF);j++)

		{

		if(ch=='\n')

			break;

		if(isdigit(ch))

			{

				buffer1=buffer1*10+ch-48;

				spaceflag=0;

			}

		else

			{

				if(spaceflag==0){

				agevector[numSet+1]=buffer1;

				numSet++;

				buffer1=0;

				spaceflag=1;

				}

			}

		}

	if(numSet<1||numSet>countofagevector[specIndex])

		errorSys("specie composition error",STOP);

	return ;

}



void AGELIST::write(FILE* outfile)

//This will write an age list to a file.



{

int j,temp1,temp2;

long y, o;

//<Add By Qia on Jan 08 2009>

printf("%s,outfile %d",j);

for(j=0;j<320/times;j++)

{

	temp1=j/32;

	temp2=j%32;

	if(agevector[temp1]&mask[temp2])

		{

		fprintf(outfile,"1");

		}

	else

		fprintf(outfile,"0");

}

//</Add By Qia on Jan 08 2009>

/*

y=young;

o=old;



for (j=0;j<=31;j++)

   {

    if (y&lowMask)

        fprintf(outfile,"1");

    else

        fprintf(outfile,"0");

    y>>=1;

   }

   

for (j=0;j<=31;j++)

   {

    if (o&lowMask)

        fprintf(outfile,"1");

    else

        fprintf(outfile,"0");

    o>>=1;

   }	  */

}





void AGELIST::dump()

//This will dump an age list to the CRT.



{

int j,temp1,temp2;

//long y, o;

//<Add By Qia on Jan 08 2009>

//printf("\\\\\%d,%d\\\\\n",agevector[0],agevector[1]);



for(j=0;j<320/times;j++)

{

	temp1=j/32;

	temp2=j%32;

	if(agevector[temp1]&mask[temp2])

		printf("%d:a",temp2);

	else

		printf("%d:b",temp2);

}

//</Add By Qia on Jan 08 2009>

/*

for (j=0;j<=31;j++)

   {

    if (y&lowMask)

        printf("1");

    else

        printf("0");

    y>>=1;

   }

   

for (j=0;j<=31;j++)

   {

    if (o&lowMask)

        printf("1");

    else

        printf("0");

    o>>=1;

   }	  

   */

printf("\n");

}



//<Add By Qia on Oct 08 2008>



/*unsigned long AGELIST::getYoung(){

 return agevector[0];

}



unsigned long AGELIST::getOld(){

 return agevector[1];

}*/

//</Add By Qia on Oct 08 2008>





