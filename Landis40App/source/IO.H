#ifndef IO_H

#define IO_H



#include "fire.h"

#include "wind.h"

#include "PDP.h"

//#include "timber.h"



void ioInit();

//Initialize io package.



void printMessage(const char*);

//Print message on CRT screen.



void putOutput(int, int, int freq[], double wAdfGeoTransform[]);

//This will write out a Landis description for the current replicate and

//iteration.

void putOutput_Landis70ProModules(int rep, int itr, int freq[]); //Add By Qia on Feb 19 2010





void ioTerm();

//Uninitialize io package.



void getInput(FILE*, int freq[], char reMethods[MAX_RECLASS][80], char ageMaps[MAX_SPECIES][80], PDP**, int, double  wAdfGeoTransform[]);

//This will read in all Landis variables.



void help();



void argHelp();



void  OutputScenario();  //added by Wei Li April 1, 2004

void putOutput_Landis70Pro(int rep, int itr, int freq[], double wAdfGeoTransform[]);

void initiateOutput_landis70Pro();

void AgeDistOutputFromBufferToFile();

void putOutput_AgeDistStat(int itr);

void AgeDistOutputBufferRelease();

void outputFileheader(FILE *fp);

#endif

