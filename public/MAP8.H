#ifndef MAP8_H

#define MAP8_H



#include <stdio.h>

#include "point.h"






#ifdef LANDIS40CORE_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllimport )

#endif





#define maxLeg  700 //256 changed By Qia on Jan 26 2009 

#define MapmaxValue  700 //Added By Qia on Feb 02 2009

#define MaxValueforLegend 700 //Added By Qia on March 20 2009

class DLLCLASS MAP8

{

public:



MAP8();                     //Constructor.  No dimensions.

MAP8(unsigned long*);		 //Constructor.  Initializes map coordinates

MAP8(int, int);             //Constructor.  Dimensions given.

~MAP8();                    //Destructor.



int read(const char*);      //Read map from a file.

                            //Input file is an ERDAS GIS File with noP

                            //extension.



int write(const char*, unsigned char*, unsigned char*, unsigned char*, double wAdfGeoTransform[]);

									//Write map to file.  There is

                           //no extension on the file name.  Three arrays

                           //of colors cooresponding to the palette (RGB)

                           //are also included.



int write(const char*, int*, int*, int*, double wAdfGeoTransform[]);  //Write map to file.  There is no

									//extension on the file name.  Three arrays

                           //of colors cooresponding to the palette (RGB)

                           //are also included.



int write(const char*);    //Write map to a file.  The color array is left

                           //unchanged from input.



int readLegend(char*);     //Read legend from a file.  First line of the

                           //file is a title.  All remaining lines are

                           //legends for up to fifteen classes.



void copy(const MAP8&);    //This will copy the contents of another map into

                           //the current map.  This includes legends, titles,

                           //and current display dimensions.



MAP8& MAP8::operator=(const MAP8&);    //Copy operator.



unsigned short& operator()(int, int); //Returns a single map element.



void dim(int, int);         //This will dimension or redimension the map size.

int cols();                 //Returns number of columns in map.

int rows();                 //Returns number of rows in map.

void rename(char*);         //This will rename the map.

void setHeader(unsigned long[]);  //This will set map coordinates

void assignLeg(int,char*);  //This will assign a new name to a legend element.

void fill(const unsigned short);    //This will fill a map with a single value.

void setCellSize(int);      //This will set the cell size of a pixel.

int high();                 //This will return the highest cell value in map.

float sizeOfCells();        //This will return the cell size of a map.

char* legendItem(int);      //This will return the contents of a legend item.



//#ifdef __HARVEST__

//void fillRegion(POINT pmin, POINT pmax, const unsigned char ch);

//int inMap(int r, int c);

//void dump();

//#endif



//<Add By Qia on Jan 26 2009>

int flag8or16;

      //Pointer to data array.

//</Add By Qia on Jan 26 2009>

private:



int numCols, numRows;      //Map dimensions.

unsigned short *data;       //Pointer to data array.

char title[80];            //Title.

char legend[MapmaxValue][64];   //Legend nodes.

unsigned short largeCell;   //Largest cell value.

float cellSize;            //Cell size in meters.

unsigned char 	red[maxLeg],	//Default red, white and blue color values.

      			green[maxLeg],

      			blue[maxLeg];

unsigned long header[32];  //Default file header.

};



//#ifdef __HARVEST__		commented by Vera Nov. 10,

class DLLCLASS MAP16 {

public:

    MAP16();                     //Constructor.  No dimensions.

    MAP16(int, int);             //Constructor.  Dimensions given.

    ~MAP16();                    //Destructor.

    int read(const char*);       //Read map from a file.
	int read(const char *fn, const int giRow, const int giCol);
   // unsigned short& operator()(int, int); //Returns a single map element.

	int readImg(const char *fn, const int giRow, const int giCol);

	// %%# Changed 5
	unsigned short get_data(int r, int c);
	// %%# Changed 6
	void set_data(int r, int c, unsigned short val);

    void dim(int, int);          //This will dimension or redimension the map size.

    int cols();                  //Returns number of columns in map.

    int rows();                  //Returns number of rows in map.

    void fill(const unsigned short);      //This will fill a map with a single value.

    int high();                  //This will return the highest cell value in map.

    int inMap(int r, int c);

    void dump();

	//<Add By Qia on Oct 31 2008>

	void freeMAPdata();

	//</Add By Qia on Oct 31 2008>

	//<Add By Qia on Nov 4 2008>

	void readtxt(char*);
	void readtxt(char *fn, const int giRow, const int giCol);

	void dim32(int, int);

	void putvalue32in(int r,int c, int value);

	int getvalue32out(int r,int c);

	//</Add By Qia on Nov 4 2008>

	

private:

    int numCols, numRows;       //Map dimensions.

    unsigned short *data;        //Pointer to data array.

    unsigned char flag16or32; //Add By Qia on Nov 4 2008

    unsigned int *data32;  //Add By Qia on Nov 4 2008

    unsigned int largeCell;    //Largest cell value. //original 4.0: unsigned short largeCell; 

    							//Changed By Qia on Nov 4 2008

    float cellSize;             //Cell size in meters.

    long header[32];            //Default file header.

};

//#endif		commented by Vera Nov. 10,







//<Add By Qia on Oct 31 2008>

/*class DLLCLASS MAP16virtual {

public:

    MAP16virtual();                     //Constructor.  No dimensions.

    MAP16virtual(int, int);             //Constructor.  Dimensions given.

    ~MAP16virtual();                    //Destructor.

    int read(const char*);       //Read map from a file.

    unsigned short& operator()(int, int); //Returns a single map element.

    void dim(int, int);          //This will dimension or redimension the map size.

    int cols();                  //Returns number of columns in map.

    int rows();                  //Returns number of rows in map.

    void fill(const unsigned short);      //This will fill a map with a single value.

    int high();                  //This will return the highest cell value in map.

    int inMap(int r, int c);

    void dump();



private:

    int numCols, numRows;       //Map dimensions.

    //unsigned short *data;        //Pointer to data array.

    MAP16 *mappointer;

    unsigned short largeCell;    //Largest cell value.

    float cellSize;             //Cell size in meters.

    long header[32];            //Default file header.

};

//#endif		commented by Vera Nov. 10,*/



#undef DLLCLASS

//</Add By Qia on Oct 31 2008>

#endif

