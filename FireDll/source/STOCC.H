/***************************** STOCC.H ************************* 2001-10-24 AF *

*

* This file contains class declarations for the C++ library of non-uniform

* random number generators. Most functions are fast and accurate, even for

* extreme values of the parameters.

*

* class StochasticLib:

* ====================

* This class can be derived from any of the uniform random number generators

* defined in randomc.h. StochasticLib provides the following non-uniform random 

* variate generators:

*

* int Bernoulli(double p);

* Bernoulli distribution. Gives 0 or 1 with probability 1-p and p.

*

* double Normal(double m, double s);

* Normal distribution with mean m and standard deviation s.

*

* long int Poisson (double L);

* Poisson distribution with mean L.

*

* long int Binomial (long int n, double p);

* Binomial distribution. n trials with probability p.

*

* long int Hypergeometric (long int n, long int m, long int t);

* Hypergeometric distribution. Taking n items out t, m of which are colored.

*

* long int NonCentralHypergeometric (long int n, long int m, long int t, double bias);

* Non-central hypergeometric distribution. Taking n items out t, m of which are colored, with bias

*

* long int ExtendedHypergeometric (long int n, long int m, long int t, double bias);

* Extended hypergeometric distribution.

*

* void Multinomial (long int * destination, double * source, long int n, int colors);

* void Multinomial (long int * destination, long int * source, long int n, int colors);

* Multivariate binomial distribution.

*

* void MultiHypergeo (long int * destination, long int * source, long int n, int colors);

* Multivariate hypergeometric distribution.

*

* void MultiNonCentralHypergeo (long int * destination, long int * source, double * weights, long int n, int colors);

* Multivariate extended hypergeometric distribution.

*

* void MultiExtendedHypergeo (long int * destination, long int * source, double * weights, long int n, int colors);

* Multivariate extended hypergeometric distribution.

*

* void Shuffle(int * list, int min, int n);

* Shuffle a list of integers.

*

* static double LnFac(int n);

* Log factorial. Mainly used internally.

*

* class StochasticLib2:

* =====================

* This class is derived from class StochasticLib. It redefines the functions

* Poisson, Binomial and HyperGeometric.

* In StochasticLib, these functions are optimized for being called with 

* parameters that vary. In StochasticLib2, the same functions are optimized

* for being called repeatedly with the same parameters. If your parameters

* seldom vary, then StochasticLib2 is faster. The two classes use different

* calculation methods, both of which are accurate.

*

* function code:

* ==============

* The code for the functions in StochasticLib are found in the file stoc1.cpp.

* The code for the functions in StochasticLib2 are found in the file stoc2.cpp.

*

* Unifrom random number generators (integer or float) are also available, as

* these are inherited from the random number generator class that is the base

* class of StochasticLib.

*

*

* Examples:

* =========

* The file ex-stoc.cpp contains an example of how to use this class library.

* The file ex-cards.cpp contains an example of how to shuffle a list of items.

* The file ex-lotto.cpp contains an example of how to generate a sequence of

* random integers where no number can occur more than once.

* The file evolc.zip contains examples of how to simulate biological evolution

* using this class library.

*

*

* Documentation:

* ==============

* The file stocc.htm contains further instructions.

* The file distrib.doc contains definitions of the statistic distributions.

* The file sampmet.doc contains theoretical descriptions of the methods used

* for sampling from these distributions.

*

*******************************************************************************/



#ifndef STOCC_H

#define STOCC_H



#include "randomc.h"



#ifndef RANDOM_GENERATOR

// define which random number generator to base stochastic library on:

#define RANDOM_GENERATOR TRandomMersenne

//#define RANDOM_GENERATOR TRanrotWGenerator

//#define RANDOM_GENERATOR TRandomMotherOfAll

#endif



void FatalError(char * ErrorText); // error exit



class StochasticLib : public RANDOM_GENERATOR {

  // This class encapsulates the random variate generating functions.

  // May be derived from any of the random number generators.



  // define constants

  enum constants {

    FAK_LEN = 1024,      // length of factorial table

    MAXCOLORS = 100      // maximum value of 'colors' in multivariate distributions

    };

  public:

  StochasticLib (int seed); // constructor

  int Bernoulli(double p);  // bernoulli distribution

  double Normal(double m, double s); // normal distribution

  long int Poisson (double L); // poisson distribution

  long int Binomial (long int n, double p); // binomial distribution

  long int Hypergeometric (long int n, long int m, long int t); // hypergeometric distribution

  long int NonCentralHypergeometric (long int n, long int m, long int t, double bias); // non-central hypergeometric distribution

  long int ExtendedHypergeometric (long int n, long int m, long int t, double bias); // extended hypergeometric distribution

  void Multinomial (long int * destination, double * source, long int n, int colors); // multinomial distribution

  void Multinomial (long int * destination, long int * source, long int n, int colors); // multinomial distribution

  void MultiHypergeo (long int * destination, long int * source, long int n, int colors); // multivariate hypergeometric distribution

  void MultiNonCentralHypergeo (long int * destination, long int * source, double * weights, long int n, int colors); // multivariate noncentral hypergeometric distribution

  void MultiExtendedHypergeo (long int * destination, long int * source, double * weights, long int n, int colors); // multivariate extended hypergeometric distribution

  void Shuffle(int * list, int min, int n); // shuffle integers

  long Uniform(long min,long max);

  double Exponential(double beta);

  

  // functions used internally

  static double LnFac(int n); // ln(n!)

  protected:

  static double fc_lnpk(long int k, long int N_Mn, long int M, long int n); // used by Hypergeometric



  // subfunctions for each approximation method

  long int PoissonInver(double L);                 // poisson by inversion

  long int PoissonRatioUniforms(double L);         // poisson by ratio of uniforms

  long int PoissonLow(double L);                   // poisson for extremely low L

  long int BinomialInver (long int n, double p);   // binomial by inversion

  long int BinomialRatioOfUniforms (long int n, double p); // binomial by ratio of uniforms

  long int HypInversionMod (long int n, long int M, long int N); // hypergeometric by inversion searching from mode

  long int HypRatioOfUnifoms (long int n, long int M, long int N); // hypergeometric by ratio of uniforms method

  long int ExtendedHypergeometricInversion (long int n, long int m, long int t, double b); // extended hypergeometric by inversion

  long int ExtendedHypergeometricRatioOfUnifoms (long int n, long int m, long int t, double b); // extended hypergeometric by ratio-of-uniforms

  

  // table of log factorial, used internally

  static double fac_table[FAK_LEN]; // table of ln(n!):

  };





class StochasticLib2 : public StochasticLib {

  // derived class, redefining some functions



  public:

  long int Poisson (double L); // poisson distribution

  long int Binomial (long int n, double p); // binomial distribution

  long int Hypergeometric (long int n, long int M, long int N); // hypergeometric distribution

  StochasticLib2(int seed):StochasticLib(seed){}; // constructor

  

  protected:

  long int PoissonModeSearch(double L); // poisson by search from mode

  long int PoissonPatchwork(double L);  // poisson by patchwork rejection

  static double PoissonF(long int k, double l_nu, double c_pm); // used by PoissonPatchwork

  long int BinomialModeSearch(long int n, double p); // binomial by search from mode

  long int BinomialPatchwork(long int n, double p); // binomial by patchwork rejection

  double BinomialF(long int k, long int n, double l_pq, double c_pm); // used by BinomialPatchwork

  long int HypPatchwork (long int n, long int M, long int N); // hypergeometric by patchwork rejection

};



#endif

