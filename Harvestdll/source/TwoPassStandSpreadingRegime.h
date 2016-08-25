#ifndef TWOPASSSTANDSPREADINGREGIME_H

#define TWOPASSSTANDSPREADINGREGIME_H



#include <stdio.h>

#include "Stand.h"

#include "TwoPassStandBasedRegime.h"



class TwoPassStandSpreadingRegime : public TwoPassStandBasedRegime {

public :

    TwoPassStandSpreadingRegime();

    virtual ~TwoPassStandSpreadingRegime() {}



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



