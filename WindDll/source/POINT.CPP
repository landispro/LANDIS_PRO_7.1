#include "point.h"



// Also change "struct POINT" to "POINT"



LDPOINT::LDPOINT() {

    x = y = 0;

}



LDPOINT::LDPOINT(int tx, int ty) : x(tx), y(ty) {}



int LDPOINT::operator==(const LDPOINT& right) {

    return (x == right.x) && (y == right.y);

}



#ifdef __HARVEST__

void LDPOINT::print(ostream* os) {

    *os << "{" << x << "," << y << "}";

}



ostream& operator<<(ostream& os, LDPOINT& p) {

    p.print(&os);

    return os;

}

#endif

