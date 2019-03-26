#ifdef __UNIX__

#define REVERSEBYTES

#endif


#include <assert.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <limits.h>

#include "system1.h"

#include "error.h"

#ifdef REVERSEBYTES

#include "mbiconvt.h"

#endif

#include "map8.h"

#include <cstdio> //*

#include <stdio.h> //*

#include <stdlib.h>//*

#include "gdal_priv.h"//*

#include "cpl_conv.h" // for CPLMalloc() //*

#include "cpl_string.h"//*

#include "ogr_spatialref.h"//*




MAP8::MAP8()

//Constructor, No dimensions.



{

	int i; //Nim: added this line

	strcpy(title, "NO TITLE");

	for (i = 0; i < MapmaxValue; i++)           //Nim: changed int i to i and <= to <

	{

		sprintf(legend[i], "%d", i);

	}

	largeCell = 0;

	data = NULL;

	for (i = 0; i < 32; i++) header[i] = 0;  //Nim: changed int i to i

}





MAP8::MAP8(unsigned long* dest)

//Constructor, No dimensions but sets the coordinates.

{

	int i; //Nim: added this line

	strcpy(title, "NO TITLE");

	for (i = 0; i < MapmaxValue; i++)           //Nim: changed int i to i and <= to <

	{

		sprintf(legend[i], "%d", i);

	}

	largeCell = 0;

	data = NULL;

	for (i = 0; i < 32; i++) header[i] = dest[i]; //Nim: changed int i to i

}



MAP8::MAP8(int r, int c)

//Constructor, Dimensions given.



{

	int i; //Nim: added this line

	strcpy(title, "NO TITLE");

	for (i = 0; i < MapmaxValue; i++) //Nim: changed int i to i

	{

		sprintf(legend[i], "<%d>", i);

	}

	largeCell = 0;

	data = NULL;

	for (i = 0; i < 32; i++) header[i] = 0; //Nim: changed int i to i and 31 to 32

	dim(r, c);

}



MAP8::~MAP8()

//Destructor.



{

	if (data)

		delete[] data;

}



int MAP8::readLegend(char* fn)

//Read legend from a file.  First line of the file is a title.  All remaining

//lines are legends for up to fifteen classes.



{

	FILE *fp;



	if ((fp = fopen(fn, "r")) == NULL)

	{

		return 1;

	}

	fgets(title, 60, fp);

	*(title + strlen(title) - 1) = '\0';



	int i = 0;

	while (!feof(fp))

	{

		fgets(legend[i], 60, fp);

		*(legend[i] + strlen(legend[i]) - 1) = '\0';

		i++;

	}

	fclose(fp);

	return 0;

}



int MAP8::read(const char *fn)

//Read map from a file.   Input file is an ERDAS GIS File with no extension.



{

	char str[100];

	long dest[32];

	float temp;

	int i, j, numread, xDim, yDim;

	unsigned char c;//Add By Qia on Jan 27 2009

	FILE *fp, *fp2;



	sprintf(str, "%s", fn);

	if ((fp = fopen(str, "rb")) == NULL)

	{

		return 1;

	}



	fread((char*)header, 4, 32, fp);



#ifdef REVERSEBYTES

	float temp2=0;

	fread((char*)&temp,4,1,fp);

	ERDr4_f(&temp,cellSize);

	fread((char*)&temp,4,1,fp);

	ERDr4_f(&temp,temp2);

	printf("%f %f\n", temp2, cellSize);

	if (temp2!=cellSize)

		errorSys("Maps don't account for inequality in x and y.",CONTINUE);

	cellSize*=temp2;

#else

	fread((char*)&temp, 4, 1, fp);

	cellSize = temp;

	fread((char*)&temp, 4, 1, fp);

	//if (temp!=cellSize)

	// errorSys("Maps don't account for inequality in x and y.",CONTINUE);

	cellSize *= temp;

#endif



#ifdef REVERSEBYTES

	ERDi4_c(&header[4],xDim); //Nim: changed yDim to xDim

	ERDi4_c(&header[5],yDim); //Nim: changed xDim to yDim

#else

	xDim = header[4]; //Nim: changed yDim to xDim

	yDim = header[5]; //Nim: changed xDim to yDim

#endif



	dim(yDim, xDim);

	for (i = yDim; i > 0; i--)

	{

		for (j = 1; j <= xDim; j++)

		{

			//numread=fread((char*)(&((*this)(i,j))),1,1,fp);//Commented By Qia on Jan 27 2009

			//<Add By Qia on Jan 27 2009>

			numread = fread((char*)(&c), 1, 1, fp);

			(*this)(i, j) = (unsigned short)c;

			//</Add By Qia on Jan 27 2009>

			if (numread > 0)

			{

				if ((*this)(i, j) > largeCell)

					largeCell = (*this)(i, j);

			}

		}

	}

	fclose(fp);



	/*TRAILER FILE*/

	sprintf(str, "%s.trl", fn);

	if ((fp2 = fopen(str, "rb")) == NULL)

	{

		errorSys("TRAILER FILE NOT FOUND.\n", CONTINUE);

	}

	else

	{

		fread((char*)dest, 1, 128, fp2);        /*Header*/

		fread((char*)green, 1, 128, fp2);       /*Green*/

		fread((char*)&green[128], 1, 128, fp2); /*Green*/

		fread((char*)red, 1, 128, fp2);         /*Red*/

		fread((char*)&red[128], 1, 128, fp2);   /*Red*/

		fread((char*)blue, 1, 128, fp2);        /*Blue*/

		fread((char*)&blue, 1, 128, fp2);       /*Blue*/

		fread((char*)dest, 1, 128, fp2);        /*Empty Record*/

		for (i = 9; i <= 16; i++)                  /*Histogram*/

			fread((char*)dest, 1, 128, fp2);

		for (i = 0; i <= (int)largeCell; i++)

		{

			fread(legend[i], 1, 32, fp2);

			for (j = 0; j <= 31; j++)

				if (legend[i][j] == '~')

					break;

			legend[i][j] = '\0';

		}

		fclose(fp2);

	}



	return 0;

}



int MAP8::write(const char *fn)

//This will write the map to a file.  It will use the default color scheme.



{
	double wAdfGeoTransform[6] = { 0.00, cellSize, 0.00, 600.00, 0.00, -cellSize };//
	return write(fn, red, green, blue,  wAdfGeoTransform);

}



int MAP8::write(const char *fn, int *red, int *green, int *blue, double wAdfGeoTransform[])

//Write map to a file.  There is no extension on the file name.  Three

//arrays of colors cooresponding to the palette (RGB) are also included.



{

	int i;

	unsigned char ured[maxLeg],

		ugreen[maxLeg],

		ublue[maxLeg];



	/// 27JUL94_CSH

	for (i = 0; i < maxLeg; i++)

	{

		ured[i] = (unsigned char)red[i];

		ugreen[i] = (unsigned char)green[i];

		ublue[i] = (unsigned char)blue[i];

	}

	return write(fn, (unsigned char*)&ured[0], (unsigned char*)&ugreen[0], (unsigned char*)&ublue[0],  wAdfGeoTransform);

}



int MAP8::write(const char *fn, unsigned char *red, unsigned char *green, unsigned char *blue, double wAdfGeoTransform[])

//Write map to a file.  There is no extension on the file name.  Three

//arrays of colors cooresponding to the palette (RGB) are also included.



{

	char str[100], str1[100];

	unsigned long dest[32];

	int i, j, numrow, numcol;

	FILE *fp;

	numrow = rows();

	numcol = cols();

	const char *pszFormat = "HFA";//*

	GDALDriver *poDriver;//*

	char **papszMetadata;//*

	poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);//*

	if (poDriver == NULL)//*
		exit(1);

	papszMetadata = poDriver->GetMetadata();//*

	GDALDataset *poDstDS;//*

	GDALRasterBand *outPoBand; //*

	char **papszOptions = NULL;//*

	float *pafScanline;//*

	unsigned int *pintScanline; //*

	char *pszSRS_WKT = NULL;//*

	OGRSpatialReference oSRS;//*

	oSRS.SetUTM(11, TRUE);//*

	oSRS.SetWellKnownGeogCS("HEAD74");//*NAD27

	oSRS.exportToWkt(&pszSRS_WKT);//*

	CPLFree(pszSRS_WKT);
	//sprintf(str, "%s.gis", fn);

	sprintf(str1, "%s.img", fn); //*

	pintScanline = (unsigned int *)CPLMalloc(sizeof(unsigned int)* (numcol*numrow));//*

	poDstDS = poDriver->Create(str1, numcol, numrow, 1, GDT_UInt32, papszOptions);//*

	if (poDstDS == NULL){

		printf("could not create file for img file output");//*

		return 1;
	}

	poDstDS->SetGeoTransform(wAdfGeoTransform);//*

	outPoBand = poDstDS->GetRasterBand(1);//*

	//for (i = 0; i < 32; i++) dest[i] = 0; //Nim: changed 31 to 32



	//for (i = numrow; i > 0; i--)

	//{

	//	for (j = 1; j <= numcol; j++)

	//	{

	//		if ((*this)(i, j) > largeCell)

	//			largeCell = (*this)(i, j);

	//	}

	//}



	/*strcpy((char*)header, "HEAD74");

	*(((char*)header) + 7) = (char)0;

	*(((char*)header) + 8) = (char)1;*/

#ifdef REVERSEBYTES

	int itemp;

	ERDc_i4(numCols,&header[4]);

	ERDc_i4(numRows,&header[5]);

	itemp=largeCell;

	ERDi_i2(itemp,(&header[22])+2);

#endif

	//<Add By Qia on Jan 27 2009>

	//strcpy((char*)header, "HEAD74");

	//*(((char*)header) + 7 - 1) = (char)2;

	//*(((char*)header) + 8 - 1) = (char)0;

	//*(((char*)header) + 9 - 1) = (char)1;



	//header[4] = numCols;

	//header[5] = numRows;

	//*(((float*)header) + 30) = cellSize;



	////</Add By Qia on Jan 27 2009>

	//fwrite((char*)header, 4, 32, fp);

	for (i = numrow; i > 0; i--)

	{

		for (j = 1; j <= numcol; j++)

		{

			/*fwrite((char*)(&((*this)(i, j))), 2, 1, fp);*/

			*(pintScanline + (numrow - i)*numcol + j - 1) = (*this)(i, j);//*

		}

	}

	outPoBand->RasterIO(GF_Write, 0, 0, numcol, numrow, pintScanline, numcol, numrow, GDT_UInt32, 0, 0);//*

	

	if (poDstDS != NULL)
		GDALClose((GDALDatasetH)poDstDS);//*

	CPLFree(pintScanline);
	CSLDestroy(papszOptions); //*

	//fclose(fp);



	//sprintf(str, "%s.trl", fn);

	//if ((fp = fopen(str, "wb")) == NULL)

	//{

	//	return 1;

	//}



	////Trailer files.

	////Record 1:

	//for (i = 0; i < 32; i++)

	//	dest[i] = 0;

	//strcpy((char*)dest, "TRAIL74");

	//strcpy(str, title);

	//strcat(str, "~");

	//strcpy(((char*)&dest[18]), str);

	//fwrite((char*)dest, 4, 32, fp);

	////Record 2-7:

	//static char nullchars[maxLeg] = { 0 };//Changed By Qia on Jan 28 2009 original 256

	//fwrite((char*)green, 1, maxLeg, fp);

	////fwrite(nullchars,1,256-maxLeg,fp); //Changed By Qia on Jan 28 2009 original 256-maxLeg

	//fwrite((char*)red, 1, maxLeg, fp);

	////fwrite(nullchars,1,256-maxLeg,fp);

	//fwrite((char*)blue, 1, maxLeg, fp);

	////fwrite(nullchars,1,256-maxLeg,fp);

	////Record 8:

	//for (i = 0; i < 32; i++)

	//	dest[i] = 0;

	//strcpy((char*)dest, "TRAIL74");

	//fwrite((char*)dest, 4, 32, fp);

	////Record 9-16:

	//for (i = 0; i < 32; i++)

	//	dest[i] = 0;

	//for (i = 9; i <= 16; i++)

	//	fwrite((char*)dest, 4, 32, fp);

	////Record 17-56: maximum map legend 50

	///* J.Yang I del. these to make sure the legend starts from 0 with real value

	//sprintf((char*)dest,"NA~");

	//fwrite((char*)dest,1,32,fp);

	//*/

	//for (i = 0; i < MapmaxValue; i++)

	//{

	//	for (j = 0; j < 32; j++)

	//		dest[j] = 0;

	//	sprintf((char*)dest, "%s~", legend[i]);

	//	fwrite((char*)dest, 1, 32, fp);

	//}

	//fclose(fp);

	return 0;

}



void MAP8::copy(const MAP8 &n)

//This will copy the contents of one map into another.  This

//includes legends, titles, and map dimensions.



{

	int i;

	largeCell = n.largeCell;

	dim(n.numRows, n.numCols);

	strcpy(title, n.title);

	for (i = 0; i < 22; i++)

		strcpy(legend[i], n.legend[i]);

	for (i = 0; i < numRows*numCols; i++)

		data[i] = n.data[i];

}





MAP8& MAP8::operator=(const MAP8 &n)



{

	int i;

	largeCell = n.largeCell;

	dim(n.numRows, n.numCols);

	strcpy(title, n.title);

	for (i = 0; i < maxLeg; i++)

		strcpy(legend[i], n.legend[i]);

	for (i = 0; i < numRows*numCols; i++)

		data[i] = n.data[i];

	return *this;

}



void MAP8::dim(int r, int c)

//This will dimension or redimension the map size.



{

	if (data != NULL)

		delete[] data; //Nim: added []



	numCols = c;

	numRows = r;

	data = new unsigned short[numCols*numRows];

	if (data == NULL){

		errorSys("Memory is not enough", STOP);

	}

}



int MAP8::cols()

//This will return the number of columns in the map.



{

	return numCols;

}



int MAP8::rows()

//This will return the number of rows in the map.



{

	return numRows;

}



unsigned short& MAP8::operator()(int r, int c)

//This will return a single map element.



{

	long int x;

#ifdef BOUNDSCHECK

	if (r<=0 || r>numRows || c<=0 || c>numCols)

	{

		char err[80];

		sprintf(err,"MAP8::operator() (int,int)-> (%d, %d) are illegal map\

			coordinates",r,c);

			errorSys(err,STOP);

	}

#endif

	/// 20JUN94_CSH

	//x=(r-1)*numCols;

	//x=x+c-1;

	x = ((r - 1)*numCols) + c - 1;

	assert(x <= 2147483647 && x >= -2147483647);

	return data[x];

}



void MAP8::rename(char *c)

//This will rename a map.



{

	strncpy(title, c, 45);

}



void MAP8::assignLeg(int pos, char *c)

//This will assign a legend element to a map.



{

	strncpy(legend[pos], c, 50);

	if ((int)largeCell < pos)

		largeCell = (unsigned char)(pos + 1);

}



void MAP8::fill(const unsigned short c)

//This will fill a map with a single value.



{

	int i;

	for (i = 0; i < numCols*numRows; i++)

		data[i] = c;

}



void MAP8::setCellSize(int size)

//This will set the size of a single cell.



{

	cellSize = (float)size;

}



int MAP8::high()

//This will return the highest value present in the map.



{

	return largeCell;

}



float MAP8::sizeOfCells()

//This will return the cell size of a map.



{

	return cellSize;

}



char* MAP8::legendItem(int pos)

//This will return the contents of a legend item.



{

	//Note: strdup uses malloc.

	return strdup(legend[pos]);

}



void MAP8::setHeader(unsigned long* dest)

//sets the map coordinates.

{

	int i; //Nim: added this line

	for (i = 0; i < 32; i++) header[i] = dest[i]; //Nim: changed int i to i

}



/*__0909__

#ifdef __HARVEST__

void MAP8::fillRegion(POINT pmin, POINT pmax, const unsigned char ch) {

int r, c, p;

for (r=pmin.y;r<=pmax.y;r++) {

for (c=pmin.x;c<=pmax.x;c++) {

p=((r-1)*numCols)+c-1;

data[p]=ch;

}

}

}



int MAP8::inMap(int r, int c) {

int result = (r >= 1 && r <= numRows && c >= 1 && c <= numCols);

return result;

}



void MAP8::dump() {

int i, j, numrow, numcol, cellValue;

numrow=rows();

numcol=cols();

for (i=numrow;i>0;i--) {

for (j=1;j<=numcol;j++) {

cellValue = (int) (*this)(i,j);

printf(" %2d", cellValue);

}

printf("\n");

}

}

#endif*/



// #ifdef __HARVEST__       commented by Vera Nov. 10,



MAP16::MAP16()

//Constructor, No dimensions.

{

	int i;

	largeCell = 0;

	data = NULL;

	for (i = 0; i < 32; i++) header[i] = 0;

}



MAP16::MAP16(int r, int c)

//Constructor, Dimensions given.



{

	int i;

	largeCell = 0;

	data = NULL;

	for (i = 0; i < 32; i++) header[i] = 0;

	dim(r, c);

}



MAP16::~MAP16()

//Destructor.



{

	if (data)

		delete[] data;

	//<Add By Qia on Nov 4 2008>

	if (data32)

		delete[] data32;

	//</Add By Qia on Nov 4 2008>

}



int MAP16::read(const char *fn)

//Read map from a file.   Input file is an 16-bit ERDAS GIS File with no extension.



{

	char str[100];

	long dest[32];

	float temp;

	int i, j, numread, xDim, yDim, mapValue;

	unsigned short c16bit;

	unsigned char c8bit;

	flag16or32 = 16;  //Add  By Qia on Nov 4 2008

	FILE *fp;

	sprintf(str, "%s", fn); //Nim: changed %s.gis to %s

	if ((fp = fopen(str, "rb")) == NULL)

	{

		return 1;

	}



	fread((char*)header, 4, 30, fp);

	//added by Wei Li 

	char	b16or8;   //true: 16, false 8 bit



	if ((header[1] & 0xff0000) == 0x020000)

		b16or8 = 16;

	else if ((header[1] & 0xff0000) == 0)

		b16or8 = 8;

	else

	{

		b16or8 = -1;

		errorSys("Error: IO: Landtype map is niether 16 bit or 8 bit.", STOP);

	}

#ifdef REVERSEBYTES

	float temp2=0;

	fread((char*)&temp,4,1,fp);

	ERDr4_f(&temp,cellSize);

	fread((char*)&temp,4,1,fp);

	ERDr4_f(&temp,temp2);

	if (temp2!=cellSize)

		errorSys("Maps don't account for inequality in x and y.",CONTINUE);

	cellSize*=temp2;

#else

	fread((char*)&temp, 4, 1, fp);

	cellSize = temp;

	fread((char*)&temp, 4, 1, fp);

	//if (temp!=cellSize)

	// errorSys("Maps don't account for inequality in x and y.",CONTINUE);

	cellSize *= temp;

#endif



#ifdef REVERSEBYTES

	ERDi4_c(&header[4],xDim); //Nim: changed yDim to xDim

	ERDi4_c(&header[5],yDim); //Nim: changed xDim to yDim

#else

	xDim = header[4]; //Nim: changed yDim to xDim

	yDim = header[5]; //Nim: changed xDim to yDim

#endif



	dim(yDim, xDim);

	for (i = yDim; i > 0; i--)

	{

		for (j = 1; j <= xDim; j++)

		{

			if (b16or8 == 8){

				numread = fread((char*)(&c8bit), 1, 1, fp);

#ifdef __UNIX__

				ERDi2_i(&c8bit, mapValue);

#else

				mapValue = (int)c8bit;

#endif

			}

			else if (b16or8 == 16){

				numread = fread((char*)(&c16bit), 2, 1, fp);

#ifdef __UNIX__

				ERDi2_i(&c16bit, mapValue);

#else

				mapValue = (int)c16bit;

#endif

			}



			// (*this)(i,j)=(unsigned short)mapValue;

			// %%# Changed 13
			(*this).set_data(i, j, (unsigned short)mapValue);

			if (numread > 0)

			{

				if ((unsigned short)mapValue > largeCell)

					largeCell = (unsigned short)mapValue;

			}

		}

	}

	fclose(fp);



	return 0;

}



int MAP16::read(const char *fn, const int giRow, const int giCol)

//Read map from a file.   Input file is an 16-bit ERDAS GIS File with no extension.



{

	char str[100];

	long dest[32];

	float temp;

	int i, j, numread, xDim, yDim, mapValue;

	unsigned short c16bit;

	unsigned char c8bit;

	flag16or32 = 16;  //Add  By Qia on Nov 4 2008

	FILE *fp;

	sprintf(str, "%s", fn); //Nim: changed %s.gis to %s

	if ((fp = fopen(str, "rb")) == NULL)

	{

		return 1;

	}



	fread((char*)header, 4, 30, fp);

	//added by Wei Li 

	char	b16or8;   //true: 16, false 8 bit



	if ((header[1] & 0xff0000) == 0x020000)

		b16or8 = 16;

	else if ((header[1] & 0xff0000) == 0)

		b16or8 = 8;

	else

	{

		b16or8 = -1;

		errorSys("Error: IO: Landtype map is niether 16 bit or 8 bit.", STOP);

	}

#ifdef REVERSEBYTES

	float temp2 = 0;

	fread((char*)&temp, 4, 1, fp);

	ERDr4_f(&temp, cellSize);

	fread((char*)&temp, 4, 1, fp);

	ERDr4_f(&temp, temp2);

	if (temp2 != cellSize)

		errorSys("Maps don't account for inequality in x and y.", CONTINUE);

	cellSize *= temp2;

#else

	fread((char*)&temp, 4, 1, fp);

	cellSize = temp;

	fread((char*)&temp, 4, 1, fp);

	//if (temp!=cellSize)

	// errorSys("Maps don't account for inequality in x and y.",CONTINUE);

	cellSize *= temp;

#endif



#ifdef REVERSEBYTES

	ERDi4_c(&header[4], xDim); //Nim: changed yDim to xDim

	ERDi4_c(&header[5], yDim); //Nim: changed xDim to yDim

#else

	xDim = header[4]; //Nim: changed yDim to xDim

	yDim = header[5]; //Nim: changed xDim to yDim

#endif


	if (giRow != yDim){
		errorSys("stand/managearea map's row and visitation map's row does not match", STOP);
	}
	assert(giRow == yDim);
	if (giCol != xDim){
		errorSys("stand/managearea map's column and visitation map's column does not match", STOP);
	}
	assert(giCol == xDim);

	dim(yDim, xDim);

	for (i = yDim; i > 0; i--)

	{

		for (j = 1; j <= xDim; j++)

		{

			if (b16or8 == 8){

				numread = fread((char*)(&c8bit), 1, 1, fp); 
				

#ifdef __UNIX__

				ERDi2_i(&c8bit, mapValue);

#else

				mapValue = (int)c8bit;
				cout << mapValue << " ";
#endif

			}

			else if (b16or8 == 16){

				numread = fread((char*)(&c16bit), 2, 1, fp);

#ifdef __UNIX__

				ERDi2_i(&c16bit, mapValue);

#else

				mapValue = (int)c16bit;
				cout << mapValue << " ";

#endif

			}



			// (*this)(i,j)=(unsigned short)mapValue;

			// %%# Changed 13
			(*this).set_data(i, j, (unsigned short)mapValue);

			if (numread > 0)

			{

				if ((unsigned short)mapValue > largeCell)

					largeCell = (unsigned short)mapValue;

			}

		}

		cout << endl;

	}

	fclose(fp);



	return 0;

}


int MAP16::readImg(const char *fn, const int giRow, const int giCol)

//Use GDAL to read .IMG map file



{

	int i, j, numread = 1, xDim, yDim, mapValue, noDataValue;

	unsigned char c8bit;

	GDALRasterBand  *poBand;//*

	float *pafScanline;//*

	GDALDataset  *simgFile; //*

	GDALAllRegister(); //*

	if ((simgFile = (GDALDataset *)GDALOpen(fn, GA_ReadOnly)) == NULL) //*

		errorSys(" img map input file not found.", STOP);  //*

	


#ifdef REVERSEBYTES

	ERDi4_c(&header[4], xDim); //Nim: changed yDim to xDim

	ERDi4_c(&header[5], yDim); //Nim: changed xDim to yDim

#else

	//xDim = header[4]; //Nim: changed yDim to xDim

	//yDim = header[5]; //Nim: changed xDim to yDim

	xDim = simgFile->GetRasterXSize(); //*

	yDim = simgFile->GetRasterYSize(); //*

	
#endif


	if (giRow != yDim){
		errorSys("stand/managearea map's row and visitation map's row does not match", STOP);
	}

	assert(giRow == yDim);

	if (giCol != xDim){
		errorSys("stand/managearea map's column and visitation map's column does not match", STOP);
	}
	assert(giCol == xDim);

	dim(yDim, xDim);

	pafScanline = (float *)CPLMalloc(sizeof(float)* (xDim * yDim));//*

	poBand = simgFile->GetRasterBand(1);//*

	poBand->RasterIO(GF_Read, 0, 0, xDim, yDim, pafScanline, xDim, yDim, GDT_Float32, 0, 0);//*

	noDataValue = GDALGetRasterNoDataValue(poBand, NULL);

	for (i = yDim; i > 0; i--)
	{
		for (j = 1; j <= xDim; j++)
		{

#ifdef __UNIX__
			ERDi2_i(&c8bit, mapValue);
#else
			mapValue = (int)*(pafScanline + (yDim - i)*xDim + j - 1);//*

			//cout << mapValue << " ";
#endif

			if (mapValue == noDataValue) mapValue = 0;

			(*this).set_data(i, j, mapValue);

			if (numread > 0)

			{

				if (mapValue > largeCell)

					largeCell = mapValue;

			}

		}

		//cout << endl;

		}

	return 0;

}

void MAP16::dim(int r, int c)

//This will dimension or redimension the map size.



{

	if (data != NULL)

		delete[] data;



	numCols = c;

	numRows = r;

	flag16or32 = 16;

	data = new unsigned int[numCols*numRows];

}



int MAP16::cols()

//This will return the number of columns in the map.



{

	return numCols;

}



int MAP16::rows()

//This will return the number of rows in the map.



{

	return numRows;

}



//unsigned short& MAP16::operator()(int r, int c)

//This will return a single map element.



//{
//
//int x;
//
//
//
//#ifdef BOUNDSCHECK
//
//if (r<=0 || r>numRows || c<=0 || c>numCols)
//
//    {
//
//     char err[80];
//
//     sprintf(err,"MAP16::operator() (int,int)-> (%d, %d) are illegal map\
//
//						coordinates",r,c);
//
//     errorSys(err,STOP);
//
//	 }
//
//#endif 
//
///// 20JUN94_CSH
//
////x=(r-1)*numCols;
//
////x=x+c-1;
//
////<Add By Qia on Oct 31 2008>
//
//
//
//	x=((r-1)*numCols)+c-1;
//
//	static int operatorcount = 0; operatorcount++;
//	if (operatorcount > 10000 * 10000)
//		printf("r = %d c = %d  %d\n", r, c, data[x]);
//
//	assert(r >= 1 && r <= numRows && c >= 1 && c <= numCols);
//	assert(flag16or32 == 16);
//
////<changed By Qia on Nov 4 2008>
//	assert(data != NULL);
//	if(flag16or32==16){
//
//
//
//	return data[x];
//
//	}

//</changed By Qia on Nov 4 2008>



//</Add By Qia on Oct 31 2008>

//}


// %%# Changed 14
unsigned int MAP16::get_data(int r, int c)
{

	static int get_datacount = 0;
	get_datacount++;

	assert(flag16or32 == 16);

	//if (get_datacount >89364000)
		//cerr<<" get_data_1"<< endl;

	long int x = ((r - 1)*numCols) + c - 1;


	assert(x <= 2147483647 && x >= -2147483647);

	if (get_datacount > 8936400000000){
		cerr << "get_data c =" << c << endl;
		cerr << "get_data r =" << r << endl;
		//cerr << "x =" << x << endl;
	}


	assert(r >= 1 && r <= numRows && c >= 1 && c <= numCols);
	assert(data != NULL);
	
	//if (get_operatorcount > 10000 * 10000)
		//cerr << " c =" << c << " r =" << r << endl;
		//printf("get r= %d c = %d %d\n", r, c, data[x]);

	

	//#ifdef BOUNDSCHECK
	//
	//	if (r <= 0 || r>numRows || c <= 0 || c>numCols)
	//	{
	//		char err[80];
	//
	//		sprintf(err, "MAP16::operator() (int,int)-> (%d, %d) are illegal map coordinates", r, c);
	//
	//		errorSys(err, STOP);
	//	}
	//
	//#endif 


	//assert(r >= 1 && r <= numRows && c >= 1 && c <= numCols);
	//assert(data != NULL);

	if (flag16or32 == 16)
	{
		return data[x];
	
	}
}


// %%# Changed 15
void MAP16::set_data(int r, int c, unsigned int val)
{
	assert(flag16or32 == 16);

	long int x = ((r - 1)*numCols) + c - 1;

	static int set_operatorcount = 0;
	set_operatorcount++;

	//if (set_operatorcount > 10000 * 10000){
		//cerr << " c =" << c << endl;
		//cerr << "r =" << r << endl;
		//cerr << "x =" << x << endl;
	//}

	assert(x <= 2147483647 && x >= -2147483647);

	//#ifdef BOUNDSCHECK
	//
	//	if (r <= 0 || r>numRows || c <= 0 || c>numCols)
	//	{
	//		char err[80];
	//
	//		sprintf(err, "MAP16::operator() (int,int)-> (%d, %d) are illegal map coordinates", r, c);
	//
	//		errorSys(err, STOP);
	//	}
	//
	//#endif 


	assert(r >= 1 && r <= numRows && c >= 1 && c <= numCols);
	assert(data != NULL);


	data[x] = val;


}


void MAP16::putvalue32in(int r, int c, int value)

{

	long int x;

	x = ((r - 1)*numCols) + c - 1;

	assert(x <= 2147483647 && x >= -2147483647);

	data32[x] = value;

}



int MAP16::getvalue32out(int r, int c)

{

	long int x;

	
	assert(c >= 1 && c <= numCols && r >= 1 && r <= numRows);

	x = ((r - 1)*numCols) + c - 1;

	//assert(x <= 2147483647 && x >= -2147483647);
	
	if (flag16or32 == 16)

	{
		
		return (*this).get_data(r, c);

	}

	if (flag16or32 == 32){

		return data32[x];
	}

}



void MAP16::fill(const unsigned short c)

//This will fill a map with a single value.



{

	int i;

	for (i = 0; i < numCols*numRows; i++)

		data[i] = c;

}

//<Add By Qia on Oct 31 2008>

void MAP16::freeMAPdata()

//By Qia aim to compress management area data

{

	if (flag16or32 == 16){

		if (data)

			delete[] data;

		data = NULL;

		return;

	}

	if (flag16or32 == 32){

		if (data32)

			delete[] data32;

		data32 = NULL;

		return;

	}

}

//</Add By Qia on Oct 31 2008>



int MAP16::high()

//This will return the highest value present in the map.



{

	return (int)largeCell;

}



int MAP16::inMap(int r, int c) {

	//int result = (r >= 1 && r <= numRows && c >= 1 && c <= numCols);
	int result = 0;

	if (r >= 1 && r <= numRows && c >= 1 && c <= numCols){

		result = 1;
	}

	return result;

}



void MAP16::dump() {

	int i, j, numrow, numcol, cellValue;

	numrow = rows();

	numcol = cols();

	for (i = numrow; i > 0; i--) {

		for (j = 1; j <= numcol; j++) {

			// cellValue = (int) (*this)(i,j);
			// %%# Changed 17
			int cellValue = (*this).get_data(i, j);

			printf(" %2d", cellValue);

		}

		printf("\n");

	}

}



//<Add By Qia on Nov 4 2008>

void MAP16::readtxt(char *fn){

	char str[100];

	long dest[32];

	float temp;

	int i, j, numread, xDim, yDim, mapValue;

	unsigned short c;

	flag16or32 = 32;	//Add  By Qia on Nov 4 2008

	FILE *fp;

	sprintf(str, "%s", fn); //Nim: changed %s.gis to %s



	if ((fp = fopen(str, "r")) == NULL)

	{

		return;

	}





	//<Add By Qia on Nov 4 2008>

	fscanf(fp, "%s", str);

	fscanf(fp, "%d", &xDim);



	fscanf(fp, "%s", str);

	fscanf(fp, "%d", &yDim);



	fscanf(fp, "%s", str);

	fscanf(fp, "%s", str);



	fscanf(fp, "%s", str);

	fscanf(fp, "%s", str);



	fscanf(fp, "%s", str);

	fscanf(fp, "%f", &cellSize);



	fscanf(fp, "%s", str);

	fscanf(fp, "%s", str);



	//</Add By Qia on Nov 4 2008>

	/*#ifdef REVERSEBYTES

		float temp2=0;

		fread((char*)&temp,4,1,fp);

		ERDr4_f(&temp,cellSize);

		fread((char*)&temp,4,1,fp);

		ERDr4_f(&temp,temp2);

		if (temp2!=cellSize)

		errorSys("Maps don't account for inequality in x and y.",CONTINUE);

		cellSize*=temp2;

		#else

		fread((char*)&temp,4,1,fp);

		cellSize=temp;

		fread((char*)&temp,4,1,fp);

		//if (temp!=cellSize)

		// errorSys("Maps don't account for inequality in x and y.",CONTINUE);

		cellSize*=temp;

		#endif



		#ifdef REVERSEBYTES

		ERDi4_c(&header[4],xDim); //Nim: changed yDim to xDim

		ERDi4_c(&header[5],yDim); //Nim: changed xDim to yDim

		#else

		xDim=header[4]; //Nim: changed yDim to xDim

		yDim=header[5]; //Nim: changed xDim to yDim

		#endif*/



	dim32(yDim, xDim);

	for (i = yDim; i > 0; i--)

	{

		for (j = 1; j <= xDim; j++)

		{

			numread = fscanf(fp, "%d", &mapValue);

			putvalue32in(i, j, mapValue);

			if (numread > 0)

			{

				if (mapValue > largeCell)

					largeCell = mapValue;

			}

		}

	}

	fclose(fp);



	return;



}










void MAP16::readtxt(char *fn, const int giRow, const int giCol)
{

	char str[100];

	long dest[32];

	float temp;

	int i, j, numread, xDim, yDim, mapValue;

	unsigned short c;

	flag16or32 = 32;	//Add  By Qia on Nov 4 2008

	FILE *fp;

	sprintf(str, "%s", fn); //Nim: changed %s.gis to %s



	if ((fp = fopen(str, "r")) == NULL)
		return;


	//<Add By Qia on Nov 4 2008>

	fscanf(fp, "%s", str);

	fscanf(fp, "%d", &xDim);



	fscanf(fp, "%s", str);

	fscanf(fp, "%d", &yDim);

	
	if (giRow != yDim){
		errorSys("stand map's row and visitation map's row does not match", STOP);
	}
	assert(giRow == yDim);
	if (giCol != xDim){
		errorSys("stand map's column and visitation map's column does not match", STOP);
	}
	assert(giCol == xDim);

	fscanf(fp, "%s", str);

	fscanf(fp, "%s", str);



	fscanf(fp, "%s", str);

	fscanf(fp, "%s", str);



	fscanf(fp, "%s", str);

	fscanf(fp, "%f", &cellSize);



	fscanf(fp, "%s", str);

	fscanf(fp, "%s", str);



	dim32(yDim, xDim);

	for (i = yDim; i > 0; i--)

	{

		for (j = 1; j <= xDim; j++)

		{

			numread = fscanf(fp, "%d", &mapValue);

			putvalue32in(i, j, mapValue);

			if (numread > 0)

			{

				if (mapValue > largeCell)

					largeCell = mapValue;

			}

		}

	}

	fclose(fp);


}



















void MAP16::dim32(int r, int c){

	if (data32 != NULL)

		delete[] data32;



	numCols = c;

	numRows = r;

	data32 = new unsigned int[numCols*numRows];

}

//</Add By Qia on Nov 4 2008>







//<Add By Qia on Oct 31 2008>

/*MAP16virtual::MAP16virtual()

//Constructor, No dimensions.

{

int i;

largeCell=0;



for (i=0;i<32;i++) header[i]=0;

}



MAP16virtual::MAP16virtual(int r, int c)

//Constructor, Dimensions given.



{

int i;

largeCell=0;



for (i=0;i<32;i++) header[i]=0;

dim(r, c);

}



MAP16virtual::~MAP16virtual()

//Destructor.



{



}



int MAP16virtual::read(const char *fn)

//Read map from a file.   Input file is an 16-bit ERDAS GIS File with no extension.



{

char str[100];

long dest[32];

float temp;

int i, j, numread, xDim, yDim, mapValue;

unsigned short c;

FILE *fp;



sprintf(str,"%s",fn); //Nim: changed %s.gis to %s

if ((fp=fopen(str,"rb"))==NULL)

{

return 1;

}



fread((char*)header,4,30,fp);



#ifdef REVERSEBYTES

float temp2=0;

fread((char*)&temp,4,1,fp);

ERDr4_f(&temp,cellSize);

fread((char*)&temp,4,1,fp);

ERDr4_f(&temp,temp2);

if (temp2!=cellSize)

errorSys("Maps don't account for inequality in x and y.",CONTINUE);

cellSize*=temp2;

#else

fread((char*)&temp,4,1,fp);

cellSize=temp;

fread((char*)&temp,4,1,fp);

//if (temp!=cellSize)

// errorSys("Maps don't account for inequality in x and y.",CONTINUE);

cellSize*=temp;

#endif



#ifdef REVERSEBYTES

ERDi4_c(&header[4],xDim); //Nim: changed yDim to xDim

ERDi4_c(&header[5],yDim); //Nim: changed xDim to yDim

#else

xDim=header[4]; //Nim: changed yDim to xDim

yDim=header[5]; //Nim: changed xDim to yDim

#endif



dim(yDim,xDim);

for (i=yDim;i>0;i--)

{

for (j=1;j<=xDim;j++)

{

numread=fread((char*)(&c),2,1,fp);

#ifdef __UNIX__

ERDi2_i(&c, mapValue);

#else

mapValue=(int)c;

#endif

(*this)(i,j)=(unsigned short)mapValue;

if (numread>0)

{

if ((unsigned short)mapValue>largeCell)

largeCell=(unsigned short)mapValue;

}

}

}

fclose(fp);



return 0;

}



void MAP16virtual::dim(int r, int c)

//This will dimension or redimension the map size.



{





numCols=c;

numRows=r;



}



int MAP16virtual::cols()

//This will return the number of columns in the map.



{

return numCols;

}



int MAP16virtual::rows()

//This will return the number of rows in the map.



{

return numRows;

}



/*unsigned short& MAP16virtual::operator()(int r, int c)

//This will return a single map element.



{

int x;

#ifdef BOUNDSCHECK

if (r<=0 || r>numRows || c<=0 || c>numCols)

{

char err[80];

sprintf(err,"MAP16virtual::operator() (int,int)-> (%d, %d) are illegal map\

coordinates",r,c);

errorSys(err,STOP);

}

#endif

/// 20JUN94_CSH

//x=(r-1)*numCols;

//x=x+c-1;

x=((r-1)*numCols)+c-1;

return (*mappointer)(r,c);

}



void MAP16virtual::fill(const unsigned short c)

//This will fill a map with a single value.



{

int i;

for (i=0;i<numCols*numRows;i++)

;

}



int MAP16virtual::high()

//This will return the highest value present in the map.



{

return (int) largeCell;

}



int MAP16virtual::inMap(int r, int c) {

int result = (r >= 1 && r <= numRows && c >= 1 && c <= numCols);

return result;

}



void MAP16virtual::dump() {

int i, j, numrow, numcol, cellValue;

numrow=rows();

numcol=cols();

for (i=numrow;i>0;i--) {

for (j=1;j<=numcol;j++) {

cellValue = (int) (*this)(i,j);

printf(" %2d", cellValue);

}

printf("\n");

}

}

*/

//</Add By Qia on Oct 31 2008>

//#endif		commented by Vera Nov. 10





