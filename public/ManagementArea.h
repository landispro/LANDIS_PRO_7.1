#ifndef MANAGEMENTAREA_H

#define MANAGEMENTAREA_H



#include "point.h"

#include "List.h"



class ManagementAreaIterator;

class MANAGEMENTAREAS;



class ManagementArea {

friend class ManagementAreaIterator;

friend class MANAGEMENTAREAS;

public :

    ManagementArea();

    virtual ~ManagementArea() {}

    void setUpdateFlag();

    int getId();

    int inManagementArea(int r, int c);

    int inManagementArea(LDPOINT p);

    int numberOfSites();

    int numberOfActiveSites();

    int numberOfStands();



private :

    void update();

    void addStand(int id);



    int itsId;

    int itsTotalSites;

    int itsActiveSites;

    unsigned char itsUpdateFlag;

    List<int> itsStandList;

};



#endif

