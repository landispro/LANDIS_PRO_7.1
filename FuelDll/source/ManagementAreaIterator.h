#ifndef MANAGEMENTAREAITERATOR_H

#define MANAGEMENTAREAITERATOR_H



#include "ManagementArea.h"

#include "List.h"



class ManagementAreaIterator {

public :

    ManagementAreaIterator(ManagementArea& m);

    virtual ~ManagementAreaIterator() {}

    int moreStands();

    int getCurrentStand();

    void gotoNextStand();

private :

    ListIterator<int> it;

};



#endif



