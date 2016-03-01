/***********************************************
Name: FuelGlobalFuncs.cpp



************************************************/
#include
#include "FuelGlobalFuncs.h"


void getFuelInput(FuelSites &fuelsites) {

	int i=0;
	FILE *fuelFile;	
	if(parameters.fuel) {
		if ((fuelFile=fopen(parameters.fuelInputFile,"r"))==NULL)
			errorSys("Fuel input file not found.",STOP);

//		printf("Begin reading in fuel data\n");
		fuelsites.init(speciesAttrs.number(), landUnits.number());		
		fuelsites.read(fuelFile);
		fuelsites.initFuelSite(sites.numRows()+1,sites.numColumns()+1);
	}

}

void getFuelManage(FuelManage &fuelManager) {

	int i=0;
	FILE *fuelFile;	

	if(parameters.fuelManagement) {
		if ((fuelFile=fopen(parameters.fuelManFile,"r"))==NULL)
			errorSys("Fuel input file not found.",STOP);

//		printf("Begin reading in fuel management data\n");
		fuelManager.read(fuelFile);
		
	}
}



void getFuelRule() {
	FILE *fuelRuleFile;	
	if(parameters.fuel) {
		if ((fuelRuleFile=fopen(parameters.fuelRuleFile,"r"))==NULL)
			errorSys("Fuel Rule file not found.",STOP);		
		fuelrule.read(fuelRuleFile);
	}
}

#endif