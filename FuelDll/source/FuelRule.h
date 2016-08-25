// FuelRule.h: interface for the FuelRule class.

//

//////////////////////////////////////////////////////////////////////



#ifndef _FUELRULE_

#define _FUELRULE_





#include <stdio.h>



#include "Defines.h"



class FuelRule  

{

public:



	int  

		fireIntensity[5][5],		//This describe fire intensity classes

		fireRisk[5][5];			//This describe fire risk classes

	float fireProbilityClass[5];	//This will hold the final potential fire probility class

	int fireProbReclass;



	float 

		fireProbility[5];		//This describe fire probility criteria



	FuelRule();

	~FuelRule();

	void read(FILE*);          //Read a fuel ruel from a file.

	int getFireIntensity (int, int);	// function to get the fire severity

	float getFireProbility (int, int);	// function to get the fire probability

};



#endif

