#ifndef OPTIM_H

#define OPTIM_H



#include "sites.h"



#ifdef SUCCESSION_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif





class DLLCLASS OPTIM



{

public:



OPTIM();                   //Constructor. 

~OPTIM();                  //Destructor.



void dim(int, int, int, SITES*, SPECIESATTRS*);   //Dimension map size.  Parameters are number of

                           //species, number of rows and columns.



void initialize();         //This will initialize or reinitialize the map.



int speciesActive(int);    //This will return true if a species referrenced

                           //by number is active.



//<changed By Qia on Oct 24 2008>

unsigned char OPTIM::operator()(int, int, int);  //Orignal 4.0:unsigned char *OPTIM::operator()(int, int, int); 

//</changed By Qia on Oct 24 2008>

                           //This will return a referrence to the appropriate

                           //species, row, column, coordinate in the maturity

                           //array. 

void dump();		   //This dumps some simple statistics on seed 

                           //availability.



private:



unsigned char *active;     //List of active species.

unsigned char *mature;     //Three dimensional array referrenced by SPECIES,

                           //Row, and column.

int specNum,               //Number of species.

    rows, cols;            //number of rows and columns.



SITES*			psites;

SPECIESATTRS*	pspeciesAttrs;



};



#endif



