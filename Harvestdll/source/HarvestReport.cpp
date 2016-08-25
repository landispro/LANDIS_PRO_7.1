#include <assert.h>

#include "GlobalVariables.h"

#include "HarvestReport.h"



HarvestReport::HarvestReport() : sumBySpecies(numberOfSpecies) {

    reset();

}



void HarvestReport::reset() {

    count = 0;

    sumBySpecies.reset();

}



/* inline */ void HarvestReport::incrementSiteCount() {

    count++;

}



/* inline */ void HarvestReport::addToSpeciesTotal(int speciesIndex, int value) {

    sumBySpecies[speciesIndex] += value;

}



/* inline */ int HarvestReport::numberOfSitesCut() {

    return count;

}



/* inline */ int HarvestReport::sumOfCohortsCut() {

    return sumBySpecies.sum();

}



/* inline */ int HarvestReport::sumOfCohortsCut(int speciesIndex) {

    return sumBySpecies[speciesIndex];

}



void HarvestReport::addReport(HarvestReport& someReport) {

    count += someReport.count;

    for (int i=1; i <= sumBySpecies.number(); i++) {

        sumBySpecies[i] += someReport.sumBySpecies[i];

    }

}



