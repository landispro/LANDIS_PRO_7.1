#ifndef TWOPASSSTANDFILLINGREGIME_H

#define TWOPASSSTANDFILLINGREGIME_H



#include <stdio.h>

#include "Stand.h"

#include "TwoPassStandBasedRegime.h"



class TwoPassStandFillingRegime : public TwoPassStandBasedRegime {

public :

    TwoPassStandFillingRegime() {}

    virtual ~TwoPassStandFillingRegime() {}

    

    int isA();

    void read(FILE* infile);

    

protected :

    void readCustomization1(FILE* infile);

    void readCustomization2(FILE* infile);

    int harvestStand(Stand* stand);

};



#endif



