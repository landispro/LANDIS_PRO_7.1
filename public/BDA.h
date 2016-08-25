/********************************************************************

Name:			BDA.h 

Description:	Biological Disturbance Agent Module class definition

Input:			BDA.dat

Output:			updated species cohorts, LiveBiomass and DeadBiomass

Date:			Oct. 10, 2002

Last Modify:    Jan. 29, 2002

Author:			Wei Li

Notes:			also made small modification in defines.h and Specie.h

*********************************************************************/



#ifndef BDA_H

#define BDA_H





#include "MAP8.h"



#include "BDAdefines.h"

#include "BDASites.h"

#include "Sites.h"



#include "stocc.h"



#include "PDP.h"



#ifdef BDADll_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif





enum TempPattern		{random, cyclic};

enum TempType			{pulse,  continuous};

enum NeighborShape		{uniform, linear, gaussian};

enum InitialCondition	{map, none};

enum SRDMode			{SRDmax, SRDmean};

//for temporal 2

enum RandomFuncs		{RFuniform, RFnormal};

enum TempType2			{TTpulse, TTvariablepulse, TTcontinuous};



//for dispersal dilation

typedef struct Delta Delta;

struct Delta

{

    int			dx;

    int			dy;

};



typedef struct Dilation Dilation;

struct Dilation

{

    int			size;

    Delta*		elem;

};





//##ModelId=3F01D0EB0055

class  BDA

{

public: 

	PDP*	m_pPDP;

	int		m_iDllMode;

	int		m_iBDANo;				//ith BDA

	int		m_ifBDArepeat;

	char	m_strBDAOutput[FNSIZE];

	char	m_strName[FNSIZE];		//BDA name

	char	m_strICMap[FNSIZE];		//Initial Confitions map, optional

	int		m_iTimeStep;



	bool	m_bEpidemicYear;

	SRDMode	m_enumSRDMode;			//SiteResourceDominance mode, true="max" false= "mean"

	float	m_fSVCalibrator;		//siteVulnerability calibrator



	//Land type modifiers

	int		m_iLTModNum;						//the number of land type, derived from LandUnits

	char	m_strLTModName[BDA_MAX_LANDTYPEMOD][FNSIZE];//name of land type modifiers 

	float	m_fLTModVal[BDA_MAX_LANDTYPEMOD];	//the values of land type modifiers

	//add at Nov. 10, 2003, by Vera

	char	m_strLTModNameNodata[BDA_MAX_LANDTYPEMOD][FNSIZE];  //add at Nov. 10, 2003, to store landtype of type nodata

	int		m_iNodataIndex;



	//Disturbance modifiers

	int		m_iDMNo;								//number of Disturbance modifiers

	int		m_iDisturbType;							//disturbance type list, fire, wind, timber, harvest

	float	m_fDisturbMod[BDA_MAX_DISTURNMOD];		//disturbance modifiers list

	int		m_iDisturbModYear[BDA_MAX_DISTURNMOD];	//disturbance year list



	//Temporal Parameters

	int				m_iTimeSinceLastEpidemic;			

	TempPattern		m_enumTempPattern;			//random or cyclic

	TempType2		m_enumTempType;				//pulse or continuous

	int				m_iTemporalFreq;			

	int				m_iMinROS;					//min Regional Outbreak Status

	int				m_iMaxROS;					//max Regional Outbreak Status

	int				m_iROS;						//Regional Outbreak Status



	//Temporal Parameters 2

	int				m_iTimetoNextEpidemic;

	RandomFuncs		m_enumRandomFuncs;

	TempType2		m_enumTempType2;

	float			m_fRandomParam1;

	float			m_fRandomParam2;



	//Neighborhood Parameters

	bool			m_bNeighborFlag;		//for the calculation of site valnerabilty 

	float			m_fNeighborRadius;		//number of sites	 

	NeighborShape	m_enumNeighborShape;	//uniform, linear decrease, or gaussian

	float			m_fNeighborWeight;		//1=equal, 0.1=higher local, 10=higher landscape



	//Dispersal

	bool	m_bDispFlag;					//dispersal flag

	bool	m_bSpatialSyn;					//0=spatially synchronous, 1=spatially asynchronous#

	int		m_iDispersalRate;				//units: # of sites

	float	m_fEpidemicThresh;				//range [0-1]

	unsigned int		m_uiEpicenterNum;

	bool	m_bSeedEpicenter;

	float	m_fOutbreakCoeff;

	float	m_fNonOutbreakCoeff;

	InitialCondition	m_enumInitialCondition;	//map or none

	

	//Host Preference array

	int*	MinorHostAge;		

	int*	SecondaryHostAge;

	int*	PrimaryHostAge;



	//Host Tolerance array

	int*	ResistantHostAge;	

	int*	Toleranthostage;

	int*	VulnerableHostAge;



	//BDA Sites Map

	BDASites*	m_pBDA;			

	int			m_iCol;				 

	int			m_iRow;



	//speed up

	bool		m_bSpeedUp;



	//dispersal template

	int			m_iDispersalTemplate;

	Dilation*	m_pDilation;

	

	//constructors 

	BDA();

	BDA(FILE*);					//initialize BDAMap pointed to by BDASites*

	BDA(char*, SITES* outsites, int outcellsize, LANDUNITS* outlus, SPECIESATTRS*  outsa, PDP*, int, int, int);

	~BDA();



	//BDA input and output

	void	read			(FILE*);	//read in BAD.dat and more...

	void	write			(FILE*);

	void	dump			(int);

	void	BDAOutputMap	(int);	//BDA map output



	void	BDAActive			();				//main function of BDA module

	int		Temporal			();

	int		Temporal2			();

	void	SiteResDom			();	

	void	SiteResDomMod		();

	void	NeighborResDom		();

	void	NeighborResDomSample();



	void	SiteVulnerability	(bool);

	void	DisturbSite			();

	void	NewEpicenters		();

	void    DispersalRegion		(int, int, int, Dilation*, Zone);

	void	UpdatePDP();



private:



	StochasticLib * m_pStochastic;



	bool	IsNotNodata	(int, int);



	float	UniformRandomNum;

	int*	m_pEpiList;

	float**	m_pfSlidingWindow;	//sliding window template

	int		m_iSlidingWindowSize;



	float**	WindowFloatTemplate	();	

	

	float**	Window				(int);

	char**	WindowChar			(int, char);



	void	WindowFree			(float**, int);

	void	WindowCharFree		(char**, int);

	

	float** WindowBoundary		(float**, int, float, NeighborShape);

	char**	WindowCharBoundary	(char**, int, float, bool);



	void	WindowCoordinates	(int, int, int, int*, int*, int*, int*, int*, int*, int*, int*);



	float	Distance			(int, int, int, int);



	void	SitesClean			(bool);

	void	ParamAdjust			();

	void	SetOutbreakZone		(Zone);

	void	SingleNeighborResDom(int, int, int);	//calculate site (i, j)'s NeighborResDom



	float	RandomNumber		();



	//dilation

	Dilation*	DilationNew		(int size, Delta* elem);

	void		DilationFree	(Dilation* d);



	void	DataWrite			(char*);					//for debug

	void	DataWriteSingle		(char*, float);

	void	PSNR				(char*, char*, float*, float*);





public:

	SITES*			pBDAsites;

	int				cellSize;

	LANDUNITS*		pBDAlandUnits;

	SPECIESATTRS*	pBDAspeciesAttrs;



};



#undef DLLCLASS



#endif

