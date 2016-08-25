#ifndef PILE_H

#define PILE_H



#include "point.h"



#define MAXPILE 25000   //changed from 25000 to 16000



class PILE

//Pile ADT.  Accepts POINT as input and output.



{

public:



PILE();             //Constructor.

int isEmpty();      //This returns true if the pile is empty.

int push(LDPOINT p);  //Pushes p onto the pile.  Returns true if unsucceful,

                    //false otherwise.

LDPOINT pull();       //Pulls p off of the pile.

void reset();       //This will reset the pile to an empty state.



private:



LDPOINT  items[MAXPILE];  //Array of pile items;

int numItems;         //Number of items on pile.

};



#endif

