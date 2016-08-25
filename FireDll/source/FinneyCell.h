// FinneyCell.h: interface for the CFinneyCell class.

//

//////////////////////////////////////////////////////////////////////



#if !defined(AFX_FinneyCell_H__D61BD8F8_992C_4244_B10E_9C1A9EB5CDD4__INCLUDED_)

#define AFX_FinneyCell_H__D61BD8F8_992C_4244_B10E_9C1A9EB5CDD4__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



class CFinneyCell  

{

public:

	void setValue(int r, int c, float time);

	float minTime;

	int col;

	int row;

	CFinneyCell();

	virtual ~CFinneyCell();



	bool CFinneyCell::operator< (const CFinneyCell&  right) const;

	bool CFinneyCell::operator> (const CFinneyCell&  right) const;

	bool CFinneyCell::operator== (const CFinneyCell&  right) const;

	bool CFinneyCell::operator!= (const CFinneyCell&  right) const;



};



#endif // !defined(AFX_FinneyCell_H__D61BD8F8_992C_4244_B10E_9C1A9EB5CDD4__INCLUDED_)

