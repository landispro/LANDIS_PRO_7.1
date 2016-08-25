#include <ctype.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "defines.h"

#include "error.h"

#include "system1.h"

#include "params.h"



#include "io.h"



extern int gDLLMode;



PARAMETERS::PARAMETERS()

//Constructor.

{

specAttrFile=NULL;

landUnitFile=NULL;

landImgMapFile=NULL; //*

//siteInFile=NULL;

siteImgFile = NULL;//*

reclassInFile=NULL;

//reclassOutFile=NULL;

//ageIndexFile=NULL;

OutputOption70=NULL;

outputDir=NULL;

disturbance=NULL;

//default_plt=NULL;

freq_out_put=NULL;



varianceSECFile=NULL;

SeedRainFile=NULL;

GrowthFlagFile=NULL;

MortalityFile=NULL;



numberOfIterations=0;

numberOfReplicates=0;

randSeed=0;

}





PARAMETERS::~PARAMETERS()

//Destructor.

{

delete [] specAttrFile;

delete [] landUnitFile;

//delete[] landUnitMapFile;

delete[] landImgMapFile; //*

//delete [] siteInFile;

delete[] siteImgFile;//*

delete [] reclassInFile;

//delete [] reclassOutFile;

//delete [] ageIndexFile;

delete [] OutputOption70;

delete [] outputDir;

delete [] disturbance;

//delete [] default_plt;

delete [] freq_out_put;

delete [] varianceSECFile;

delete [] SeedRainFile;

delete [] GrowthFlagFile;

delete [] MortalityFile;

delete [] Biomassfile;

delete [] VolumeFile;

}





int PARAMETERS::read(FILE* infile, int* BDANo)

//Read in all parameters from a file.



{

char dispType[40];

specAttrFile=new char[FNSIZE];

landUnitFile=new char[FNSIZE];

//landUnitMapFile=new char [FNSIZE]; // landtype.gis

landImgMapFile = new char[FNSIZE]; //* landtype.img 

//siteInFile=new char[FNSIZE]; // speciesmap.gis

siteImgFile = new char[FNSIZE];// *speciesmap3.img 

reclassInFile=new char[FNSIZE];

//reclassOutFile=new char[FNSIZE]; // mapindex.dat
//
//ageIndexFile=new char[FNSIZE]; // ageindex.dat

OutputOption70=new char[FNSIZE];

outputDir=new char[FNSIZE];

disturbance=new char[FNSIZE];

//default_plt=new char[FNSIZE]; //default

freq_out_put=new char[FNSIZE];

printf("Reading from parameter File\n\n");



//<Add By Qia on Jan 21 2009>

varianceSECFile= new char[FNSIZE];

//</Add By Qia on Jan 21 2009>

SeedRainFile=new char[FNSIZE];

GrowthFlagFile=new char[FNSIZE];

MortalityFile=new char[FNSIZE];

Biomassfile=new char[FNSIZE];

VolumeFile=new char[FNSIZE];



//Wind

strWindInitName = new char[FNSIZE];

//BDA entry point: BDA Init file

strBDAInitName = new char[FNSIZE];	//BDA entry point

//Fuel entry point: Fuel Init file

strFuelInitName = new char[FNSIZE];

//Haevset entry point: Harvest init file

strHarvestInitName = new char[FNSIZE];

//Fire entry point: Fire init file

strFireInitName = new char[FNSIZE];

//char temp[100];



char* str = new char [1000];



int dllmode = 0;



if (fscanc(infile,"%s",specAttrFile)!=1)

	 errorSys("Error reading in specAttrFile from parameter file.",STOP);

if (fscanc(infile,"%s",landUnitFile)!=1)

	 errorSys("Error reading in landUnitFile from parameter file.",STOP);

//if (fscanc(infile,"%s",landUnitMapFile)!=1)
//
//	 errorSys("Error reading in landUnitMapFile from parameter file.",STOP);

if (fscanc(infile, "%s", landImgMapFile) != 1) //* landtype.img

	errorSys("Error reading in  GIS File from parameter file.", STOP); //*

//if (fscanc(infile,"%s",siteInFile)!=1)
//
//	 errorSys("Error reading in  GIS File from parameter file.",STOP);

if (fscanc(infile, "%s", siteImgFile) != 1) //* speciesmap3.img 

	errorSys("Error reading in  GIS File from parameter file.", STOP);

if (fscanc(infile,"%s",reclassInFile)!=1)

	 errorSys("Error reading in reclassInFile from parameter file.",STOP);

//if (fscanc(infile,"%s",reclassOutFile)!=1)
//
//	 errorSys("Error reading in reclassOutFile from parameter file.",STOP);
//
//if (fscanc(infile,"%s",ageIndexFile)!=1)
//
//	 errorSys("Error reading in ageIndexFile from parameter file.",STOP);

if (fscanc(infile,"%s",OutputOption70)!=1)

	 errorSys("Error reading in OutputOption70 from parameter file.",STOP);



if (fscanc(infile,"%s",outputDir)!=1)

	 errorSys("Error reading in outputDir from parameter file.",STOP);

//if (fscanc(infile,"%s",default_plt)!=1)
//
//	 errorSys("Error reading in default.plt from parameter file.",STOP);

if (fscanc(infile,"%s",freq_out_put)!=1)

	 errorSys("Error reading in freq.out.put from parameter file.",STOP);

if (fscanc(infile,"%s",Biomassfile)!=1)

	 errorSys("Error reading in biomassfile from parameter file.",STOP);



if (fscanc(infile,"%d",&numberOfIterations)!=1)

	 errorSys("Error reading in numberOfIterations from parameter file.",STOP); 

if (fscanc(infile,"%d",&randSeed)!=1)

	 errorSys("Error reading in randSeed from parameter file.",STOP);

if (fscanc(infile,"%d",&cellSize)!=1)

	 errorSys("Error reading in cellSize from parameter file.",STOP);

if (fscanc(infile,"%s",dispType)!=1)

	 errorSys("Error reading in dispRegime from parameter file.",STOP);



if (fscanc(infile,"%d",&timestep)!=1)//Add By Qia

	 errorSys("Error reading in timestep from parameter file.",STOP);

if (fscanc(infile,"%d",&timestep_Wind)!=1)//Add By Qia

	 errorSys("Error reading in timestep from parameter file.",STOP);

if (fscanc(infile,"%d",&timestep_Fire)!=1)//Add By Qia

	 errorSys("Error reading in timestep from parameter file.",STOP);

if (fscanc(infile,"%d",&timestep_BDA)!=1)//Add By Qia

	 errorSys("Error reading in timestep from parameter file.",STOP);

if (fscanc(infile,"%d",&timestep_Fuel)!=1)//Add By Qia

	 errorSys("Error reading in timestep from parameter file.",STOP);

if (fscanc(infile,"%d",&timestep_Harvest)!=1)//Add By Qia

	 errorSys("Error reading in timestep from parameter file.",STOP);

//<Add By Qia on Jan 21 2009 changed on Feb 23 2009>

if (fscanc(infile,"%s",varianceSECFile)!=1)//Add By Qia

	 errorSys("Error reading in SEC parameter from parameter file.",STOP);

if (!strcmp (varianceSECFile, "N/A")){

	flagforSECFile=0;

}

else if(!strcmp (varianceSECFile, "0"))

	flagforSECFile=0;

else if(!strcmp (varianceSECFile, "1"))

	flagforSECFile=1;

else if(!strcmp (varianceSECFile, "2"))

	flagforSECFile=2;

else

	flagforSECFile=3;



//</Add By Qia on Jan 21 2009>

if (fscanc(infile,"%s",GrowthFlagFile)!=1)//Add By Qia

	 errorSys("Error reading in growthrate parameter from parameter file.",STOP);

if (!strcmp (GrowthFlagFile, "N/A")){

	GrowthFlag=0;

}

else if(!strcmp (GrowthFlagFile, "0"))

	GrowthFlag=0;

else

	GrowthFlag=1;





if (fscanc(infile,"%s",MortalityFile)!=1)//Add By Qia

	 errorSys("Error reading in mortality parameter from parameter file.",STOP);

if (!strcmp (MortalityFile, "N/A")){

	MortalityFlag=0;

}

else if(!strcmp (MortalityFile, "0"))

	MortalityFlag=0;

else

	MortalityFlag=1;



/*if (fscanc(infile,"%s",SeedRainFile)!=1)//Add By Qia

	 errorSys("Error reading in seedrain parameter from parameter file.",STOP);

if (!strcmp (SeedRainFile, "N/A")){

	SeedRainFlag=0;

}

else if(!strcmp (SeedRainFile, "0"))

	SeedRainFlag=0;

else

	SeedRainFlag=1;*/



SeedRainFlag=0;





if (fscanc(infile,"%s",VolumeFile)!=1)//Add By Qia

	 errorSys("Error reading in seedrain parameter from parameter file.",STOP);

if (!strcmp (VolumeFile, "N/A")){

	VolumeFlag=0;

}

else if(!strcmp (VolumeFile, "0"))

	VolumeFlag=0;

else

	VolumeFlag=1;



//<Add By Qia on Aug 01 2012>
 if (fscanc(infile, "%lf", &stocking_x_value)!=1)

    errorSys("Error reading TargetStocking from harvest section.",STOP);
 if (fscanc(infile, "%lf", &stocking_y_value)!=1)

    errorSys("Error reading TargetStocking from harvest section.",STOP);
 if (fscanc(infile, "%lf", &stocking_z_value)!=1)

    errorSys("Error reading TargetStocking from harvest section.",STOP);
//</Add By Qia on Aug 01 2012>

//disturbances

if (fscanc(infile,"%s",strWindInitName)!=1)	//wind entry point

	 errorSys("Error reading in windthrow flag from parameter file.",STOP);

if (strcmp (strWindInitName, "N/A"))

	dllmode = dllmode | G_WIND;



if (fscanc(infile,"%s",strFireInitName)!=1)	//fire entry point

	 errorSys("Error reading in fire flag from parameter file.",STOP);

if (strcmp (strFireInitName, "N/A"))

	dllmode = dllmode | G_FIRE;



if (fscanc(infile,"%s", strBDAInitName)!=1)		//BDA entry point

	errorSys("Error reading in BDAInit file info",STOP);

if (strcmp (strBDAInitName, "N/A"))

{

	dllmode = dllmode | G_BDA;

	FILE* tmp = LDfopen(strBDAInitName, 1);

	if (tmp == NULL)

		errorSys("Error Open BDA parameter file error.",STOP);

	fscanc(tmp, "%d", BDANo);

	LDfclose(tmp);

}



if (fscanc(infile,"%s", strFuelInitName)!=1)	//Fuel entry point

	errorSys("Error reading in FuelInit file info",STOP);

if (strcmp (strFuelInitName, "N/A"))

	dllmode = dllmode | G_FUEL;



if (fscanc(infile,"%s",strHarvestInitName)!=1)	//Harvest entry point

	 errorSys("Error reading in HarvestInit file info.",STOP);

if (strcmp (strHarvestInitName, "N/A"))

	dllmode = dllmode | G_HARVEST;





if (strcmp(dispType,"NO_DISPERSAL")==0)

	 dispRegime=NO_DISPERSAL;

else if (strcmp(dispType,"UNIFORM")==0)

	 dispRegime=UNIFORM;

else if (strcmp(dispType,"NEIGHBORS")==0)

	 dispRegime=NEIGHBORS;

else if (strcmp(dispType,"DISPERSAL")==0)

	 dispRegime=DISPERSAL;

else if (strcmp(dispType,"RAND_ASYM")==0)

	 dispRegime=RAND_ASYM;

else if (strcmp(dispType,"MAX_DIST")==0)

	 dispRegime=MAX_DIST;

else if (strcmp(dispType,"SIM_RAND_ASYM")==0)

	 dispRegime=SIM_RAND_ASYM;

else

	 errorSys("Input file error or illegal seed dispersal routine." ,STOP);



return dllmode;



}





void PARAMETERS::dump()

//This shall dump the contents of parameters.



{

printf("specAttrFile:       %s\n",specAttrFile);

printf("landUnitFIle:       %s\n",landUnitFile);

//printf("landUnitMapFIle:    %s\n", landUnitMapFile);

printf("landImgFile:        %s\n", landImgMapFile);//*

//printf("siteInFile:         %s\n",siteInFile);

printf("siteImgFile:         %s\n", siteImgFile);//*

printf("reclassInFile:      %s\n",reclassInFile);

//printf("reclassOutFile:     %s\n",reclassOutFile);

//printf("ageIndexFile:       %s\n",ageIndexFile);

printf("outputDir:          %s\n",outputDir);

printf("disturbance:        %s\n",disturbance);

//printf("default_plt:        %s\n",default_plt);

printf("freq_out_put:		%s\n",freq_out_put);

printf("numberOfIterations: %d\n",numberOfIterations);

printf("randSeed:           %d\n",randSeed);

printf("cellSize:           %d\n",cellSize);

switch (dispRegime)

	{

	 case NO_DISPERSAL:  printf("dispRegime:         NO_DISPERSAL\n"); break;

	 case UNIFORM:       printf("dispRegime:         UNIFORM\n"); break;

	 case NEIGHBORS:     printf("dispRegime:         NEIGHBORS\n"); break;

	 case DISPERSAL:     printf("dispRegime:         DISPERSAL\n"); break;

	 case RAND_ASYM:     printf("dispRegime:         RAND_ASYM\n"); break;

	 case MAX_DIST:      printf("dispRegime:         MAX_DIST\n"); break;

	 case SIM_RAND_ASYM: printf("dispRegime:         SIM_RAND_ASYM\n"); break;

	 default: errorSys("PARAMETERS::dump()-> Illegal dispRegime",STOP);

	}

//printf("wind flag:          %d\n",wind);

printf("fire flag:          %d\n",fire);

//printf("timber flag:        %d\n",timber);



}





void PARAMETERS::write(FILE* outfile)

//This shall write the contents of parameters to outfile



{

fprintf(outfile,"%s\n",specAttrFile);

fprintf(outfile,"%s\n",landUnitFile);

//fprintf(outfile, "%s\n", landUnitMapFile);

fprintf(outfile, "%s\n", landImgMapFile);//*

//fprintf(outfile,"%s\n",siteInFile);

fprintf(outfile, "%s\n", siteImgFile);//*

fprintf(outfile,"%s\n",reclassInFile);

//fprintf(outfile,"%s\n",reclassOutFile);

//fprintf(outfile,"%s\n",ageIndexFile);

fprintf(outfile,"%s\n",outputDir);

fprintf(outfile,"%s\n",disturbance);

//fprintf(outfile,"%s\n",default_plt);

fprintf(outfile,"%s\n",freq_out_put);

fprintf(outfile,"%d\n",numberOfIterations);

fprintf(outfile,"%d\n",randSeed);

fprintf(outfile,"%d\n",cellSize);

switch (dispRegime)

	{

	 case NO_DISPERSAL:  fprintf(outfile,"NO_DISPERSAL\n"); break;

	 case UNIFORM:       fprintf(outfile,"UNIFORM\n"); break;

	 case NEIGHBORS:     fprintf(outfile,"NEIGHBORS\n"); break;

	 case DISPERSAL:     fprintf(outfile,"DISPERSAL\n"); break;

	 case RAND_ASYM:     fprintf(outfile,"RAND_ASYM\n"); break;

	 case MAX_DIST:      fprintf(outfile,"MAX_DIST\n"); break;

	 case SIM_RAND_ASYM: fprintf(outfile,"SIM_RAND_ASYM\n"); break;

	 default: errorSys("PARAMETERS::write()-> Illegal dispRegime.",STOP);

	}

//fprintf(outfile,"%d\n",wind);

fprintf(outfile,"%d\n",fire);

//fprintf(outfile,"%d\n",timber);



}



