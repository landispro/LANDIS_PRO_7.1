#ifndef SYSTEM1_H

#define SYSTEM1_H



#include <stdio.h>



#undef min

#undef max



#ifdef LANDIS40CORE_EXPORTS

	#define DLLFUNC   __declspec( dllexport )

#else

	#define DLLFUNC   __declspec( dllimport )

#endif



#ifdef __cplusplus

extern "C" {  // only need to export C interface if

              // used by C++ source code

#endif





//DLLFUNC int fscanc(FILE *fp, char *fmt, ...);

// fscanc: fscanf function with one more feature: jump the comment delimited

// by # pairs. It'll return TRUE, if success, otherwise FALSE.

DLLFUNC	FILE* LDfopen(char * strFName, int);

DLLFUNC FILE* LDfopen_0(char * strFName,char * strType);

DLLFUNC void LDfclose(FILE*);

DLLFUNC void LDfprintf(FILE *stream, const char *format);

DLLFUNC void LDfprintf2i(FILE *stream, const char *format, int);

DLLFUNC void LDfprintf2c(FILE *stream, const char *format, char*);

DLLFUNC void LDfprintf4(FILE *stream, const char *format, int, int, int, int);



DLLFUNC void LDfprintf6(FILE *stream, const char *format, int i1, const char* str2, int i3, int i4, int i5, int i6);



DLLFUNC int LDfread(char*,int,int,FILE*);



DLLFUNC int fscanc(FILE *fp, char *fmt, ...);



// j.Yang added here

DLLFUNC int LDfprintf0(FILE * fp,const char * fmt, ...);

DLLFUNC int LDprintf(const char *fmt, ...);



DLLFUNC int LDfflush (FILE * fp);



DLLFUNC int LDfscanf(FILE *fp, const char *fmt, char* );

DLLFUNC int LDfscanf3(FILE *fp, const char *fmt, int* i1, int* i2, int* i3);



DLLFUNC int mfscanc(FILE *fp, char *fmt, ...);

DLLFUNC char*	LDfgets(char *str, int n, FILE* fstream );

DLLFUNC int	LDfgetc(FILE *stream);



DLLFUNC void LDrewind(FILE*);



DLLFUNC int min(int, int);       //Returns the minimum of two integers.

DLLFUNC int max(int, int);       //Returns the maximum of two integers.



DLLFUNC void skipblanks(FILE*);

//This will skip all white space in a file.



// all random number calls automaticaly call fseed



DLLFUNC void fseed(int);

//This will seed the random number generator.



//Nim: commented out the next line

//int intrand();

//returns an integer random number



DLLFUNC float frand();

//This returns a random number.

//<Add by Qia to test on Dec 11 2008>

DLLFUNC float frand1();//This is for change of Fuel

DLLFUNC int frandrand();//This is for change of BDA



//</Add By Qia to test on Dec 11 2008>

//<Add By Qia on Jan 14 2009>

DLLFUNC float frandrandSuccesstion(int timestep, char argu);//This is for Succession

//</Add By Qia on Jan 14 2009>

DLLFUNC double drand();

//This returns a random number.



DLLFUNC int irand(int a, int b);

//This will return a random integer between a and b inclusive.



DLLFUNC float frandNorm();

//This returns a random number normally distributed around 0.



DLLFUNC float franCos();



DLLFUNC int factorial(int k);

//J.Yang Facotrail function k!



//float franII();



DLLFUNC void swap(float&, float&);

//This will swap two floating point values.





/*#ifdef __HARVEST__

DLLFUNC float gasdev();

DLLFUNC float gasdev(float mean, float sd);

#endif*/







DLLFUNC int LDeof(FILE*);

//This will return TRUE if eof is encountered and FALSE otherwise.  It is

//different from the feof library function in that it skips all white space

//before detecting the end of file condition.

DLLFUNC float LDmin(float, float); //Returns the minimum of two floats.



DLLFUNC float LDmax(float, float); //Returns the maximum of two floats.



#ifdef __cplusplus

}

#endif



#ifdef LANDIS40CORE_EXPORTS



#endif



#undef DLLFUNC



#endif







