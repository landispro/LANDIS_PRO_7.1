

#ifndef AGELIST_H

#define AGELIST_H



#include <stdio.h>







#ifdef LANDIS40CORE_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif



class DLLCLASS AGELIST



{



public:



void AGELISTAllocateVector(int index);              //Constructor.

AGELIST();



//<Add By Qia on March 04 2009>

AGELIST(const AGELIST& agelist);



//AGELIST& operator = ( const AGELIST& agelist );



~AGELIST();

//<Add By Qia on March 04 2009>

void clear();           //Clear age list.

void set(int);          //Set an age to true.

void reset(int);        //Reset an age to false.

void shiftOld();        //Shift all ages up one to the next age class.

int query();            //Returns true if any ages are present in age list,

                        //false otherwise.

int query(int);         //Return true if age is in list, false otherwise.

int query(int, int);    //Return true if an age exists in the given range

                        //bounded by two integers.

int youngest();         //Return the youngest age.

int oldest();           //Return the oldest age.

int number();           //Return the number of age clases present.

void read(FILE*);       //This shall read the age list from a file.

void readBinary(FILE*);//Add By Qia on Feb 26 2009

void readTreeNum(FILE*, int); //Add By Qia on July 6 2009

void write(FILE*);      //This shall write the age list to a file.

void dump();            //This shall dump the age list to the CRT.





//<Add By Qia on Oct 08 2008>

//unsigned long getYoung();

//unsigned long getOld();

//</Add By Qia on Oct 08 2008>



//<Add By Qia on Jan 12 2009>

int getAgeVector(int i);

int getAgeVectorNum();

int getTimeStep();

//</Add By Qia on Jan 12 2009>

//<Add By Qia on June 30 2009>

int getTreeNum(int n,int specIndex);

void setTreeNum(int n, int specIndex, int age);

void GrowTree(int specIndex);

//</Add By Qia on June 30 2009>





//<Add By Qia on Jan 09 2009>

AGELIST& operator=(const AGELIST&);



//</Add By Qia on Jan 09 2009>





protected:



//unsigned long young, old;  //commented By Qia on Jan 06 2009

//The data is held in two long 32 bit integers.  For

                          //transportability this relation must be held.  If

                          //32 bit integers are not available this class must

                          //be reprogrammed.

int *agevector;

};



//<Add By Qia on Jan 05 2009>

class DLLCLASS timestep{

public:

	void gettimestep(int temp);

	void getSpecNum(int num);

	void Setlongevity(int i,int num);

	~timestep();

	unsigned int Time_step;

	int SpecNum;

};



#undef DLLCLASS

//</Add By Qia on Jan 05 2009>



#endif

