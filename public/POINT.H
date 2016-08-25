#ifndef POINT_H

#define POINT_H



//#ifdef __HARVEST__

#include <iostream>

using namespace std;

//#endif

//



class  LDPOINT {

public :

    LDPOINT();

    LDPOINT(int tx, int ty);

    ~LDPOINT() {}

    int operator==(const LDPOINT& right);

//#ifdef __HARVEST__

    void print(ostream* os);

//#endif

    int x, y;

};



//#ifdef __HARVEST__

ostream& operator<<(ostream& os, LDPOINT& p);

//#endif



#endif

