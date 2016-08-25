#ifndef FUELSTAND_H

#define FUELSTAND_H



#include "point.h"

#include "List.h"

#include "IntArray.h"



class StandIterator;

class FUELSTANDS;



/**

 * This is the data structure that holds the information about a particular stand

 *

 * @author NIM

 */

class FUELStand 

{

friend class StandIterator;

friend class FUELSTANDS;

public :

    FUELStand();

    ~FUELStand();



    void setUpdateFlag();



    int getId();

    int FuelgetManagementAreaId();

    LDPOINT getMinPoint();

    LDPOINT getMaxPoint();



    void setRank(int rank);

    int getRank();



    void reserve();

    void unreserve();

    int isReserved();



    int getAge();

    

    int canBeHarvested();

    int wasRecentlyHarvested();

    int neighborsWereRecentlyHarvested();

    

    int inStand(int r, int c);

    int numberOfSites();

    int numberOfActiveSites();



    LDPOINT getRandomPoint();

    



//	#ifdef _FUELMAN_

	float	getMeanFireRisk ();

	int		itsUpdateFireRiskFlag;

	float itMeanFireRisk;

	float itMeanFireProbability;

	float itMeanFireProbabilityClass;

	float itMeanFireIntensity;

	float itMeanFineFuel;

	float itMeanCoarseFuel;

	int itsFuelTreatmentSites;	

//	#endif



    

private :

    void update();

    int isNeighbor(int r, int c);

    void addNeighbor(int id);



	void fireRisk ();



     /**

     * the id number of the stand from the stand input map

     */

    int itsId;





        /**

     * the management area the stand belongs to

     * gets assigned in the construct method of the Stands class

     */

    int itsManagementAreaId;





        /**

     * The point with the smallest value in the stand

     * The map values start in the lower left corner and increases to 

     * to the upper right corner.

     */

    LDPOINT itsMinPoint;





        /**

     * The point with the largest value in the stand

     * The map values start in the lower left corner and increases to 

     * to the upper right corner.

     */

    LDPOINT itsMaxPoint;





        /**

     * the total number of sites in the stand

     */

    int itsTotalSites;





        /**

     * the total number of sites that are active

     */

    int itsActiveSites;





        /**

     * the number of sites that are 'harvestable' 

     * according to conditions such as age or if neighbors have been harvested etc

     */

    int itsHarvestableSites;

    



    /**

     * not really the mean age

     * is actually the mean of the youngest cohorts ages

     */

    int itsMeanAge;





    /**

    * How to tell if the stand has had any disturbances

    */

    unsigned char itsUpdateFlag;





    /**

    * itsNeighborList:

    */

    List<int> itsNeighborList;





    /**

     * itsRecentHarvestFlag:

     */

    int itsRecentHarvestFlag;





        /**

     * Where it ranks according to the ranking algorithm

     */

    int itsRank;





    /**

     * if the stand is reserved from harvesting or not

     */

    int itsReserveFlag;



};



#endif