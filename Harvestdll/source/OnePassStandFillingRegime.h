#ifndef ONEPASSSTANDFILLINGREGIME_H

#define ONEPASSSTANDFILLINGREGIME_H



#include <stdio.h>

#include "Stand.h"

#include "OnePassStandBasedRegime.h"



class OnePassStandFillingRegime : public OnePassStandBasedRegime {

public :

    OnePassStandFillingRegime() {}

    virtual ~OnePassStandFillingRegime() {}



    int isA();

    void read(FILE* infile);



protected :

    void readCustomization1(FILE* infile);

    void readCustomization2(FILE* infile);

    int harvestStand(Stand* stand);

};



#endif



