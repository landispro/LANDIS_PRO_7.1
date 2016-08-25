// FireCell.cpp: implementation of the CFinneyCell class.

//

//////////////////////////////////////////////////////////////////////





#include "FinneyCell.h"



#ifdef _DEBUG

#undef THIS_FILE

static char THIS_FILE[]=__FILE__;

#define new DEBUG_NEW

#endif



//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////



CFinneyCell::CFinneyCell()

{



}



CFinneyCell::~CFinneyCell()

{



}



bool CFinneyCell::operator< (const CFinneyCell&  right) const

{

	

	return (minTime < right.minTime);

}



bool CFinneyCell::operator> (const CFinneyCell&  right) const

{

	

	return (minTime > right.minTime);

}



bool CFinneyCell::operator== (const CFinneyCell&  right) const

{

	

	return (minTime == right.minTime);

}



bool CFinneyCell::operator!= (const CFinneyCell&  right) const

{

	

	return (minTime != right.minTime);

}



void CFinneyCell::setValue(int r, int c, float time)

{

	row = r;

	col = c;

	minTime = time;

}

