//No harvest flag for stand.  Only stand age is used in rank #2



#include <stdio.h>

#include "error.h"

#include "point.h"

#include "site.h"

//#include "landis.h"

#include "system1.h"

#include "GlobalVariables.h"

#include "HarvestReport.h"

#include "List.h"

#include "IntArray.h"

#include "Stand.h"

#include "StandIterator.h"

#include "SiteHarvester.h"

#include "StandRankingAlgorithm.h"

#include "RandomRank.h"

#include "OldestRank.h"

#include "EconomicImportanceRank.h"

#include "RegulateDistributionRank.h"

#include "RankbyVolume.h" //Add By Qia on Oct 03 2009
#include "RankbyStocking.h" //Add By Qia on July 27 2012

/* 29-SEP-99 */

#include "RelativeOldestRank.h"

/* -- END -- */

#include "HarvestRegime.h"

// Memory Leak Detection

#define CRTDBG_MAP_ALLOC

#include <stdlib.h>

#include <crtdbg.h>

HarvestRegime::HarvestRegime() {

    itsManagementAreaId = 0;

    itsRotationAge = 0;

    itsRemovalMask = 0;

    itsRankAlgorithm = 0;

    itsDuration = 0;

    itsReport = new HarvestReport;

}



HarvestRegime::~HarvestRegime() {

    delete itsRemovalMask;

    delete itsRankAlgorithm;

    delete itsReport;

}



/* inline */ int HarvestRegime::getManagementAreaId() {

    return itsManagementAreaId;

}



/* inline */ int HarvestRegime::getRotationAge() {

    return itsRotationAge;

}



/* inline */ SiteRemovalMask* HarvestRegime::getRemovalMask() {

    return itsRemovalMask;

}



/* inline */ StandRankingAlgorithm* HarvestRegime::getRankAlgorithm() {

    return itsRankAlgorithm;

}



/* inline */ int HarvestRegime::getDuration() {

    return itsDuration;

}



/* inline */ HarvestReport* HarvestRegime::getReport() {

    return itsReport;

}



/* inline */ void HarvestRegime::setDuration(int duration) {

    itsDuration = duration;

}



void HarvestRegime::harvest() {

	

    int id;

    List<int> rankedList;

    Stand* stand;

    int standCut;

	
    itsRankAlgorithm->rankStands(rankedList);
	
	getReport()->reset();
	

	// length of rankedList should be equal to length of  theLength;
	

	for (ListIterator<int> it(rankedList); !isHarvestDone() && it.more(); it.advance()) 
	{	
		
		
		
/*    

	  stand = stands(it.current());

      if (stand->canBeHarvested() && (parameters.standAdjacencyFlag == 0 || !stand->neighborsWereRecentlyHarvested())) modified by Vera  

*/		stand = (*pstands)(it.current());

	/*	cerr << "it.current() = " << it.current()<< endl;

	cerr << " HarvestRegime::harvest():standID = " << stand->getId() << endl;

	cerr << "HarvestRegime::harvest():Minpoint.x = " << stand->getMinPoint().x << " Minpoint.y  = " << stand->getMinPoint().y << endl;

	cerr << "HarvestRegime::harvest():Maxpoint.x = " << stand->getMaxPoint().x << " Maxpoint.y  = " << stand->getMaxPoint().y << endl;*/


		if (stand->canBeHarvested() && (iParamstandAdjacencyFlag == 0 || !stand->neighborsWereRecentlyHarvested())) 

		{
			
			standCut = harvestStand(stand);
		
        }



    }
	
	writeReport(harvestOutputFile2);
	



}



void HarvestRegime::writeReport(FILE* outfile) {

	//cerr << "HarvestRegime::writeReport" << endl;

    static int firstTime = 1;

    if (firstTime) 

	{

        LDfprintf(outfile, "eventType\tdescription\tdecade\tmanagementArea\tsitesCut\tsumAgesCut"); 



        for (int spp = 1; spp <= pspeciesAttrs->number(); spp++)

		    LDfprintf2c(outfile, "\t%s", (*pspeciesAttrs)(spp)->name);

        LDfprintf(outfile, "\n");



        firstTime = 0;

    }

/* 22-OCT-99 */ 

/* Changed isA() to getSequentialId() */

    LDfprintf6(outfile, "%d\t%s\t%d\t%d\t%d\t%d", getSequentialId(), getLabel(), currentDecade, getManagementAreaId(),

      itsReport->numberOfSitesCut(), itsReport->sumOfCohortsCut());

/* -- END -- */

/*  for (int spp = 1; spp <= speciesAttrs.number(); spp++)           Modified by Vera*/

    for (int spp = 1; spp <= pspeciesAttrs->number(); spp++)

        LDfprintf2i(outfile, "\t%d", itsReport->sumOfCohortsCut(spp));

    LDfprintf(outfile, "\n");

	//cerr << "end HarvestRegime::writeReport" << endl;

}



void HarvestRegime::read(FILE* infile) {

    int rankAlgorithmId;

    char label[255] = "Harvest Module\0";

	int id;

    /*if (fscanc(infile,"%s", label)!=1)

        errorSys("Error reading label from harvest section.",STOP);*/

	if (fscanc(infile,"%d", &id)!=1)

        errorSys("Error reading label from harvest section.",STOP);

    setLabel(label);

	setUserInputId(id);

    if (fscanc(infile, "%d", &itsManagementAreaId)!=1)

        errorSys("Error reading management area id from harvest section.",STOP);



    if (fscanc(infile, "%d", &itsRotationAge)!=1)

        errorSys("Error reading rotation age from harvest section.",STOP);



    if (fscanc(infile, "%d", &rankAlgorithmId)!=1)

        errorSys("Error reading rank algorithm from harvest section.",STOP);



    readCustomization1(infile);



    itsRemovalMask = new SiteRemovalMask;

	if(strcmp(label,"Basal_Area_Thinning")){

	   //itsRemovalMask->read(infile);

		readCustomization2(infile);

	}





    switch (rankAlgorithmId) {

    case 1 :

        itsRankAlgorithm = new RandomRank(itsManagementAreaId, itsRotationAge);

        break;

    case 6 :

        itsRankAlgorithm = new OldestRank(itsManagementAreaId, itsRotationAge);

        break;

    case 7 :

        itsRankAlgorithm = new EconomicImportanceRank(itsManagementAreaId, itsRotationAge, itsRemovalMask);

        break;

    case 4 :

        itsRankAlgorithm = new RegulateDistributionRank(itsManagementAreaId, itsRotationAge);

        break;

/* 29-SEP-99 */

    case 5 :

        itsRankAlgorithm = new RelativeOldestRank(itsManagementAreaId, itsRotationAge, itsRemovalMask);

        break;

	case 2 :

        itsRankAlgorithm = new RankbyVolume(itsManagementAreaId, itsRotationAge);

        break;
	case 3 : 
		itsRankAlgorithm = new RankbyStocking(itsManagementAreaId, itsRotationAge); //Add By Qia on July 26 2012
		break;

/* -- END -- */

    default :

        errorSys("Illegal rankAlgorithmId in HarvestRegime::read().", STOP);

        break;

    }

    itsRankAlgorithm->read(infile);



}



