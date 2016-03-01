#include <ctype.h>

#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <stdarg.h>

#include "error.h"

#include "system1.h"

#include "defines.h"

#define DELIMIT    '#'

#define PI         3.141592654



static int stringCommentFlag = 0;

static int charCommentFlag = 0;



//////////////////////////////////////////////////////////////////////////////

//                      GENERAL FUNCTIONS CODE                              //

//////////////////////////////////////////////////////////////////////////////



int isStringComment(char *s)

// Given a string, if it is part of comment return TRUE, otherwise FALSE



{

int count=0;



for (s; *s; s++)

	 if (*s==DELIMIT)

		 {

		 count+=1;

		 stringCommentFlag=(stringCommentFlag+1)%2;

		 }

if (stringCommentFlag==1 || count>0) return true;

else return false;

}



int isCharComment(char ch)

// Given a charactor, if it is part of comment retunn TRUE, otherwise FALSE



{

if (ch==DELIMIT)

	charCommentFlag=(charCommentFlag+1)%2;



if ( charCommentFlag==1 || ch==DELIMIT ) 

	return true;

else 

	return false;

 }



// fscanc: fscanf function with one more feature: jump the comment delimited

// by # pairs. It'll return TRUE, if success, otherwise FALSE.

int fscanc(FILE *fp, char *fmt, ...)

{



va_list ap;                 // points to each unnamed arg in turn 

char *p, *sval, temp[256];  //Nim: changed 80 to 255

int* ival;       //Nim: changed int to int*

long* lval;      //Nim: changed long to long*

float* fval;    //Nim: added this line

double* dval;    //Nim: changed double to double*





va_start(ap, fmt);          // make ap point to 1st unnamed arg 

for (p=fmt; *p; p++)

	 {

	 if (*p != '%') continue;



	 while (fscanf(fp, "%s", temp), isStringComment(temp))

			 ;

     //if (JIAN_DEBUG) printf("%s is not a comment\n",temp);



	 switch (*++p)

		 {

		 case 'd':

			  ival = va_arg(ap, int*);   //Nim: changed int to int*

			  sscanf(temp, "%d", ival);

			  break;

		 case 'f':

			  fval = va_arg(ap, float*); //Nim: changed dval to fval and double to float*

			  sscanf(temp, "%f", fval);  //Nim: changed dval to fval

			  break;

         case 's':

			  sval = va_arg(ap, char*);

			  strcpy(sval, temp);

	          break;

         case 'l':

	       switch (*++p)

	       {

	       case 'd':

		      lval = va_arg(ap, long*); //Nim: changed long to long*

		      sscanf(temp, "%ld", lval);

		      break;

		   case 'f':

		 	 dval = va_arg(ap, double*); //Nim: changed double to double*

			 sscanf(temp, "%lf", dval);   //Nim: changed %f to %lf

			 break;

		   default:

			 break;

		   }

		  break;

		default:

			  break;

		};

	 }

	 va_end(ap);             // clean up when done  



return true;



}



int mfscanc(FILE *fp, char *fmt, ...) 

//modified fscanc function, to read line by line and could contain space in the return string



{

va_list ap;                 /* points to each unnamed arg in turn  */

char *p, *sval, temp[256];  

int* ival;       

long* lval;      

float* fval;    

double* dval;   

char line[256];



va_start(ap, fmt);          /* make ap point to 1st unnamed arg */

for (p=fmt; *p; p++)

	 {

	 if (*p != '%') continue;



	 while(!feof(fp))

	 {

		strcpy(line,"");

		fgets(line,256,fp);

		if(!strcmp(line,"")) break;

	 }



	if(strcmp(line,""))

	{

		perror("Could not get string from infile");

		return false;

	}



	char seps[] = "#";

	char *token;

	token = strtok(line,seps);

	if (token !=NULL) 

		strcpy(temp,token);

	else

		strcpy(temp,line);





	 switch (*++p)

		 {

		 case 'd':

			  ival = va_arg(ap, int*);   //Nim: changed int to int*

			  sscanf(temp, "%d", ival);

			  break;

		 case 'f':

			  fval = va_arg(ap, float*); //Nim: changed dval to fval and double to float*

			  sscanf(temp, "%f", fval);  //Nim: changed dval to fval

			  break;

         case 's':

			  sval = va_arg(ap, char*);

			  strcpy(sval, temp);

	          break;

         case 'l':

	       switch (*++p)

	       {

		       case 'd':

			      lval = va_arg(ap, long*); //Nim: changed long to long*

				  sscanf(temp, "%ld", lval);

				  break;

			   case 'f':

		 		  dval = va_arg(ap, double*); //Nim: changed double to double*

				  sscanf(temp, "%lf", dval);   //Nim: changed %f to %lf

				  break;

			   default:

				  break;

		   }		  

		default:

			  break;

		}

	 }

	 va_end(ap);             /* clean up when done    */

return true;

}





void skipblanks(FILE* infile)

//This will skip all white space and the comment delimited by # pairs in infile.



{

char ch;



//while (((ch=getc(infile))!=EOF)&&(isspace(ch))) {}     old code

while (((ch=(char)getc(infile))!=EOF) && ((isspace(ch)) || (isCharComment(ch)))) {}



if (!feof(infile))

	 ungetc(ch, infile);

}



int LDeof(FILE* infile)

//This will return TRUE if eof is encountered and FALSE otherwise.  It is

//different from the feof library function in that it skips all white space

//and the comment delimited by # pairs before detecting the end of file

//condition.



{

char ch;



// while (((ch=getc(infile))!=EOF)&&(isspace(ch))) {}     old code

while ( ( (ch=(char)getc(infile))!=EOF) && ( (isspace(ch)) || (isCharComment(ch)) ) ) {}



if (!feof(infile))

	{

	 ungetc(ch,infile);

	 return false;

	}

else

	 return true;

}



int min(int a, int b)

//Returns minimun of a and b.



{

if (a<b)

	return a;

else

	return b;

}



float LDmin(float a, float b)

//Returns minimum of a and b.



{

if (a<b)

	return a;

else

	return b;

}



int max(int a, int b)

//Returns maximum of a and b.



{

if (a>b)

	 return a;

else

	 return b;

}



float LDmax(float a, float b)

//Returns maximum of a and b.



{

if (a>b)

	 return a;

else

	 return b;

}



void fseed(int seed)

//This will seed the random number generator.



{

#ifdef __UNIX__

srand48(seed);

#else

srand(seed);

#endif

}



float frand()

//This will return a random number.



{

#ifdef __UNIX__

	{

	return (float)drand48();

	}

#else

	{

	return (float) rand() / (float) RAND_MAX;

	}

#endif

}



//<Add By Qia on Dec 11 2008>

float frand1()

//add to replace all (float)((double)rand()/(double)(RAND_MAX+1)) in fuelsites.cpp

{

	return (float)((double)rand()/(double)(RAND_MAX+1));

}

//</Add By Qia on Dec 11 2008>





//<Add By Qia on Dec 11 2008>

int frandrand() 

//Add to replace all rand() in BDA.cpp

{

	return rand();

}

//</Add By Qia on Dec 11 2008>



//<Add By Qia on Jan 14 2009>

float frandrandSuccesstion(int timestep, char argu) 

{

	float result,sign,variation;

	#ifdef __UNIX__

	{

	sign=(float) argu;

	result= (float) drand48();

	variation= drand48()/2;

	result = result/(1+sign*variation);

	result = result/10*timestep;

	return result;

	}

	#else

	{

	sign=(float) argu;

	result= (float) rand() / (float) RAND_MAX;

	variation= frand1()/2*sign;

	result = result/(1+variation);

	result=result*10/timestep;

	return result;

	}

	#endif

}

//</Add By Qia on Jan 14 2009>

double drand()

//This will return a random number.



{

#ifdef __UNIX__

	{

	return drand48();

	}

#else

	{

	return (double) rand() / (double) RAND_MAX;

	}

#endif

}



int irand(int a, int b)

//This will return a random integer between a and b inclusive.

{

 return (int) (rand() % (b-a+1) + a);

}



float frandNorm()

//This returns a random number normally distributed around 0.0.

{

 float a1=0, a2=0;

 while (a1==0)

 {

 	a1=frand();

 	a2=frand();

 }

 return (float)( sqrt((float)-0.75*log(a1))*sin(PI*PI*a2) )-(float)0.14;

}





float franCos()

{

 float a1=frand();

 return (float) cos(PI*PI*a1);

}





void swap(float &a, float &b)

//This will swap the values of a and b.



{

float t;

t=a;

a=b;

b=t;

}



#ifdef __HARVEST__

float gasdev()

{

	static int iset=0;

	static float gset;

	float fac,rsq,v1,v2;



	if  (iset == 0) {

		do {

			v1=(float)2.0*frand()-(float)1.0;

			v2=(float)2.0*frand()-(float)1.0;

			rsq=v1*v1+v2*v2;

		} while (rsq >= 1.0 || rsq == 0.0);

		fac=(float)sqrt((float)-2.0*log(rsq)/rsq);

		gset=v1*fac;

		iset=1;

		return v2*fac;

	} else {

		iset=0;

		return gset;

	}

}



float gasdev(float mean, float sd){

    float gset;

    gset = gasdev()*sd + mean;

    return gset;

}

#endif



int factorial(int k)

{

	if(k=0) return 1;

	int i,temp=1;

	for(i=k;i>=1;i--)

	{

		temp = temp*i;

	}

	return temp;

}



FILE* LDfopen(char * strFName, int type)

{

	if (type == 1)

		return fopen(strFName, "r");

	else if (type == 2)

		return fopen(strFName, "rb");

	else if (type ==3)

		return fopen(strFName, "w");

	else if (type == 4)

		return fopen(strFName, "a");	

	else return NULL;

}



FILE * LDfopen_0(char * strFName, char * strType)

{

	return fopen(strFName,strType);

}



int LDfread(char* dest,int i, int j,FILE* f)

{

	int num;

	num = fread(dest,i,j,f);

	return num;



}



void LDfclose(FILE* f)

{ 

	fclose(f);

}



void LDfprintf(FILE *stream, const char *format)

{

	fprintf(stream, format);

}



void LDfprintf2i(FILE *stream, const char *format, int i)

{

	fprintf(stream, format, i);

}



void LDfprintf2c(FILE *stream, const char *format, char* str)

{

	fprintf(stream, format, str);

}



void LDfprintf4(FILE *stream, const char *format, int i1, int i2, int i3, int i4)

{

	fprintf(stream, format, i1, i2, i3, i4);

}



void LDfprintf6(FILE *stream, const char *format, int i1, const char* str2, int i3, int i4, int i5, int i6)

{

	fprintf(stream, format, i1, str2, i3, i4, i5, i6);

}





int LDfscanf(FILE *fp, const char *fmt, char* str)

{

	return fscanf(fp, fmt, str);

}



int LDfscanf3(FILE *fp, const char *fmt, int* i1, int* i2, int* i3)

{

	return fscanf(fp, fmt, i1, i2,i3);

}



char*	LDfgets( char *str, int n, FILE* fstream )

{

	return fgets(str, n, fstream );

}



int	LDfgetc( FILE *stream)

{

	return fgetc(stream);

}



void LDrewind(FILE* infile)

{

	rewind(infile);

}



int LDfflush (FILE * fp)

{

	return fflush(fp);

}



int LDfprintf0(FILE * fp,const char * fmt, ...)

{

	va_list ap;	

		

	char *p, * ep, *sval, cval;  



	int ival;       

	long lval;      

	float fval;    

	double dval;    





	va_start(ap, fmt);          // make ap point to 1st unnamed arg 

	

	

	int n = 0;

	p = strdup(fmt);	

	while ( *p != '\0')

	{

		if ( *p != '%')

		{

			//Not special, just write out the char

			(void) putc(*p,fp);

			++n;

			++p;

		}

		else

		{

			ep = p + 1;

			switch (*ep)

			{

			case 'c':

				cval = va_arg(ap,char);

				n += fprintf(fp,"%c",cval);

				break;

			case 'd':

				ival = va_arg(ap, int);

				n += fprintf(fp,"%d",ival);

				break;

			case 'f':

				fval = va_arg(ap,float);

				n += fprintf(fp,"%f",fval);

				break;

			case 's':

				sval = va_arg(ap,char *);

				n += fprintf(fp,"%s",sval);

				break;

			case 'l':

				ep ++;

				switch (*ep)

				{

				case 'd':

					lval = va_arg(ap,long);

					n += fprintf(fp,"%ld",lval);

					break;

				case 'f':

					dval = va_arg(ap,double);

					n += fprintf(fp,"%lf",dval);

					break;

				default:

					return -1;

				}

				break;

			default:

				return -1;

			}

			p = ep+1;

		}	

	} //end of while

	va_end(ap);  // clean up when done  

	return n;



}



int LDprintf(const char * fmt, ...)

{

	va_list ap;	

		

	char *p, * ep, *sval, cval;  



	int ival;       

	long lval;      

	float fval;    

	double dval;    





	va_start(ap, fmt);          // make ap point to 1st unnamed arg 

	

	

	int n = 0;

	p = strdup(fmt);	

	while ( *p != '\0')

	{

		if ( *p != '%')

		{

			//Not special, just write out the char

			(void) putchar(*p);

			++n;

			++p;

		}

		else

		{

			ep = p + 1;

			switch (*ep)

			{

			case 'c':

				cval = va_arg(ap,char);

				n += printf("%c",cval);

				break;

			case 'd':

				ival = va_arg(ap, int);

				n += printf("%d",ival);

				break;

			case 'f':

				fval = va_arg(ap,float);

				n += printf("%f",fval);

				break;

			case 's':

				sval = va_arg(ap,char *);

				n += printf("%s",sval);

				break;

			case 'l':

				ep ++;

				switch (*ep)

				{

				case 'd':

					lval = va_arg(ap,long);

					n += printf("%ld",lval);

					break;

				case 'f':

					dval = va_arg(ap,double);

					n += printf("%lf",dval);

					break;

				default:

					return -1;

				}

				break;

			default:

				return -1;

			}

			p = ep+1;

		}	

	} //end of while

	va_end(ap);  // clean up when done  

	return n;

}