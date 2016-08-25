#include <stdio.h>

#include "CohortRemovalMask.h"



/* inline */ void CohortRemovalMask::read(FILE* infile) {

    mask.read(infile);

}



/* inline */ void CohortRemovalMask::dump() {

    mask.dump();

}



/* inline */ int CohortRemovalMask::query() {

    return mask.query();

}



/* inline */ int CohortRemovalMask::query(int n) {

    return mask.query(n);

}
