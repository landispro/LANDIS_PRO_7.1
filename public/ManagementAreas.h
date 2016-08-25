#ifndef MANAGEMENTAREAS_H

#define MANAGEMENTAREAS_H



#include "ManagementArea.h"



#ifdef HARVESTDLL_EXPORTS

	#define DLLCLASS   __declspec( dllexport )

#else

 

	#ifdef FUELDLL_EXPORTS

		#define DLLCLASS   __declspec( dllexport )

	#else

		#define DLLCLASS   __declspec( dllimport )

	#endif



#endif



class DLLCLASS MANAGEMENTAREAS {

public :

    MANAGEMENTAREAS();

    virtual ~MANAGEMENTAREAS();

    int number();

    ManagementArea* MANAGEMENTAREAS::operator() (int n);

    void construct();

private :

    int numManagementAreas;

    ManagementArea* managementAreas;

};



#undef DLLCLASS



#endif



