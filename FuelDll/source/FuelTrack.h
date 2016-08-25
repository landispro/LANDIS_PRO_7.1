// FuelTrack.h: interface for the FuelTrack class.

//

//////////////////////////////////////////////////////////////////////

#ifndef _FUELMAN_

#define _FUELMAN_





class FuelTrack  

{

public:

	FuelTrack();

	~FuelTrack();

	void FFTrack();			// track fine fuel

	void CFTrack();			// track coarse fuel

	void CFInit();			// track coarse fuel at yr 0

	void FireRiskTrack();	// track fire probability, intensity and risk



};



#endif

