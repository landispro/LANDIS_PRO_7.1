#ifndef ONEPASSSTANDSPREADINGREGIME_H

#define ONEPASSSTANDSPREADINGREGIME_H



#include <stdio.h>

#include "Stand.h"

#include "OnePassStandBasedRegime.h"



class OnePassStandSpreadingRegime : public OnePassStandBasedRegime {

public :

    OnePassStandSpreadingRegime();

    virtual ~OnePassStandSpreadingRegime() {}

    

    int isA();

    void read(FILE* infile);



protected :

    void readCustomization1(FILE* infile);

    void readCustomization2(FILE* infile);

    int harvestStand(Stand* stand);



private :

    float itsMeanStandCutSize;

    float itsStandardDeviation;

};



#endif



