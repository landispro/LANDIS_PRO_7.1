#include "error.h"

#include "GlobalVariables.h"

#include "HarvestRegime.h"

#include "OnePassStandBasedRegime.h"



OnePassStandBasedRegime::OnePassStandBasedRegime() {

    itsState = START;

    itsEntryDecade = 0;

    itsTargetCut = 0;

}



OnePassStandBasedRegime::~OnePassStandBasedRegime() {

}



int OnePassStandBasedRegime::conditions() {

    int passed;



    switch (itsState) {

    

    case ENTRYPENDING :

        if (currentDecade < itsEntryDecade)

            passed = 0;

        else if (currentDecade == itsEntryDecade) {

            passed = 1;

            itsState = ENTRYREADY;

        }

        break;



    case DONE :

        passed = 0;

        break;

        

    default :

        errorSys("Illegal call to OnePassStandBasedRegime::conditions.", STOP);

        break;

    }



    return passed;

}



void OnePassStandBasedRegime::harvest() {

    switch (itsState) {

    case ENTRYREADY :

        HarvestRegime::harvest();

        itsState = DONE;

        break;

    default :

        errorSys("Illegal call to OnePassStandBasedRegime::harvest.", STOP);

    }

}



int OnePassStandBasedRegime::isHarvestDone() {

    int result;

    result = getReport()->numberOfSitesCut() >= itsTargetCut;

    return result;

}



