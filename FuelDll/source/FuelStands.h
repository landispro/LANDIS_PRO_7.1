#ifndef FUELSTANDS_H

#define FUELSTANDS_H



#include "FUELStand.h"



class FUELSTANDS 

{

public :

    FUELSTANDS();

    virtual ~FUELSTANDS();

    int number();

    FUELStand* FUELSTANDS::operator() (int n);

    void construct();

private :

    int numStands;

    FUELStand* stands;

};



#endif



