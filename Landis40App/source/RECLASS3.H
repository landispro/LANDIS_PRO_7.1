#ifndef RECLASS3_H

#define RECLASS3_H



void reclassify(int timeStep, char ageMap[MAX_SPECIES][80]);

//updates m with the information read from species age maps.

//pre: age maps gis files for all species must be created

//pos: create new reclassification maps based on the instruction readed in

//     map index files and the associated RCS files.



void classify();

//classifies m with the methods defined in CLS files for the given year.

//pre: m must be updated (reclassify must be called), CLS files must exist.

//pos: create new classified map based on the instruction readed from CLS files.



#endif



