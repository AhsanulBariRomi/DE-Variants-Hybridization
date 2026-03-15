//       D I F F E R E N T I A L     E V O L U T I O N       
//                                                           
// Program: de.c                                              
// Version: 3.6                                               
//                                                           
// Authors: Dr. Rainer Storn                                  
//         c/o ICSI, 1947 Center Street, Suite 600           
//         Berkeley, CA 94707                                
//         Tel.:   510-642-4274 (extension 192)              
//         Fax.:   510-643-7684                              
//         E-mail: storn@icsi.berkeley.edu                   
//         WWW: http://http.icsi.berkeley.edu/~storn/        
//         on leave from                                     
//         Siemens AG, ZFE T SN 2, Otto-Hahn Ring 6          
//         D-81739 Muenchen, Germany                         
//         Tel:    636-40502                                 
//         Fax:    636-44577                                 
//         E-mail: rainer.storn@zfe.siemens.de               
//                                                           
//         Kenneth Price                                     
//         836 Owl Circle                                    
//         Vacaville, CA 95687                               
//         E-mail: kprice@solano.community.net
//
//  Changes for Visual Sutdio 2010, by Charles Brauer
//                                                           
// This program implements some variants of Differential      
// Evolution (DE) as described in part in the techreport      
// tr-95-012.ps of ICSI. You can get this report either via   
// ftp.icsi.berkeley.edu/pub/techreports/1995/tr-95-012.ps.Z  
// or via WWW: http://http.icsi.berkeley.edu/~storn/litera.html*
// A more extended version of tr-95-012.ps is submitted for   
// publication in the Journal Evolutionary Computation.
//                                                           
// ou may use this program for any purpose, give it to any   
// person or change it according to your needs as long as you 
// are referring to Rainer Storn and Ken Price as the origi-  
// nators of the the DE idea.                                 
// If you have questions concerning DE feel free to contact   
// us. We also will be happy to know about your experiences   
// with DE and your suggestions of improvement.               

#include <iostream>
#include "stdafx.h"
#include "de.h"

using namespace std;

long  rnd_uni_init;
float c[MAXPOP][MAXDIM], d[MAXPOP][MAXDIM];
float c1[MAXPOP][MAXDIM],c2[MAXPOP][MAXDIM], d1[MAXPOP][MAXDIM],d2[MAXPOP][MAXDIM];

float oldarray[MAXPOP][MAXDIM];
float newarray[MAXPOP][MAXDIM];

float oldarray2[MAXPOP][MAXDIM];
float newarray2[MAXPOP][MAXDIM];

float swaparray[MAXPOP][MAXDIM];

float rnd_uni(long *idum);
float extern evaluate(int D, float tmp[], long *nfeval);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float extern one_sphere(int D, float c[ ], long *nfeval);
float extern seven_rosenbrock(int D,float c[], long *nfeval);
float extern ten_rastrigin(int D,float c[], long *nfeval);
float extern fourteen_griewank(int D,float c[], long *nfeval);
float extern twoSchwefelsNonSep(int D, float c[], long *nfeval);
float extern twoSchwefelsSep(int D,float c[],long *nfeval);
float extern Eleven_non_con_Rastrigin(int D,float c[],long *nfeval);
float extern fifteen_Alpine(int D,float c[],long *nfeval);
float extern Kowalik(int D,float c[],long *nfeval);
float extern Michalewicz(int D,float c[],long *nfeval);

int CopyVector(float a[], float b[]) {
  for (int k=0; k<MAXDIM; k++) {
    a[k] = b[k];
  }
  return 0;
}

int CopyArray(float dest[MAXPOP][MAXDIM], float src[MAXPOP][MAXDIM]) {
  for (int j=0; j<MAXPOP; j++) {
    for (int k=0; k<MAXDIM; k++) {
      dest[j][k] = src[j][k];
    }
  }
  return 0;
}
                                                                                                                                
// SRC-FUNCTION   :main()                                           
// LONG_NAME      :main program                                     
// AUTHOR         :Rainer Storn, Kenneth Price                      
//                                                                 
// DESCRIPTION    :driver program for differential evolution.       
//                                                                 
// FUNCTIONS      :rnd_uni(), evaluate(), printf(), fprintf(),      
//                fopen(), fclose(), fscanf().                     
//                                                                 
// GLOBALS        :rnd_uni_init    input variable for rnd_uni()     
//                                                                 
// PARAMETERS     :argc            #arguments = 3                   
//                argv            pointer to argument strings      
//                                                                 
// PRECONDITIONS  :main must be called with three parameters        
//                e.g. like de1 <input-file> <output-file>, if     
//                the executable file is called de1.               
//                The input file must contain valid inputs accor-  
//                ding to the fscanf() section of main().          
//                                                                 
// POSTCONDITIONS :main() produces consecutive console outputs and  
//                writes the final results in an output file if    
//                the program terminates without an error.                                                                       

int _tmain(int argc, _TCHAR* argv[]) {
  int   i, j, L, n;      // counting variables                 
  int   r1, r2, r3, r4;  // placeholders for random indexes    
  int   r5,r6,r7;              // placeholders for random indexes    
  int   r10,r11,r20,r21;  
  int   D;               // Dimension of parameter vector      
  int   NP;              // number of population members       
  int   imin,imin2;            // index to member with lowest energy 
  int   refresh;         // refresh rate of screen output      
  int   strategy;
  int   strategy2;// choice parameter for screen output 
  int   gen, genmax, seed;   
  long  nfeval;          // number of function evaluations     
  
  float trial_energy;    // buffer variable                    
  float trial_energy2;
  
  float inibound_h;      // upper parameter bound              
  float inibound_l;      // lower parameter bound 

  float tmp[MAXDIM], best[MAXDIM], bestit[MAXDIM]; // members  
  float tmp2[MAXDIM], best2[MAXDIM], bestit2[MAXDIM];
  
  float energy[MAXPOP];  // obj. funct. values
  float energy2[MAXPOP];

  float F, CR;           // control variables of DE            
  float emin,emin2;            // help variables                     
  char ch;
  FILE  *stream;

  stream = fopen("demo.dat", "r");
  if (stream == NULL) {
    printf( "The file demo.dat was not opened\n" );
    cin.get(ch);
    exit(0);
  }

  fscanf(stream, "%d", &strategy);       // choice of strategy
  fscanf(stream, "%d", &genmax);         // maximum number of generations
  fscanf(stream, "%d", &refresh);        // output refresh cycle
  fscanf(stream, "%d", &D);              // number of parameters
  fscanf(stream, "%d", &NP);             // population size.
  fscanf(stream, "%f", &inibound_h);     // upper parameter bound for init
  fscanf(stream, "%f", &inibound_l);     // lower parameter bound for init
  fscanf(stream, "%f", &F);              // weight factor
  fscanf(stream, "%f", &CR);             // crossing over factor
  fscanf(stream, "%d", &seed);           // random seed 
  fclose(stream);

  strategy2 = 2;
  
  
  rnd_uni_init = -(long)seed;  // initialization of rnd_uni() 
  nfeval       =  0;           // reset number of function evaluations 
  float r;

  // Initialization
  // Right now this part is kept fairly simple and just generates
  // random numbers in the range [-initfac, +initfac]. You might
  // want to extend the init part such that you can initialize
  // each parameter separately.

  // spread initial population members
  for (i=0; i<NP; i++) {
    for (j=0; j<D; j++) {
      r = rnd_uni(&rnd_uni_init);
      c[i][j] = inibound_l + r*(inibound_h - inibound_l);
    }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //energy[i] = evaluate(D, c[i], &nfeval);
	//energy[i] = one_sphere(D, c[i], &nfeval);
	//energy[i] = seven_rosenbrock(D, c[i], &nfeval);
	//energy[i] = ten_rastrigin(D, c[i], &nfeval);
	//energy[i] = fourteen_griewank(D, c[i], &nfeval);
	//energy[i] = twoSchwefelsNonSep(D, c[i], &nfeval);
	//energy[i] = twoSchwefelsSep(D, c[i], &nfeval);
	//energy[i] = Eleven_non_con_Rastrigin(D, c[i], &nfeval);
	//energy[i] = fifteen_Alpine(D, c[i], &nfeval); 
	//energy[i] = Kowalik(D, c[i], &nfeval);
	if(i<NP/2)
		energy[i] = fourteen_griewank(D, c[i], &nfeval);
	else if(i>=NP/2)
		energy2[i-NP/2] = fourteen_griewank(D, c[i], &nfeval);

    // printf("%2d %20.8f %3d\n", i, energy[i], nfeval);
    // cin.get(ch);
  }

  for (i=0; i<NP; i++) {
		if (i<NP/2)
			CopyArray(c1, c);
		else
			CopyArray(c2, c);
  }

  emin = energy[0];
  imin = 0;
  for (i=1; i<NP/2; i++) {
    if (energy[i] < emin) {
      emin = energy[i];
      imin = i;
    }
  }

  CopyVector(best, c[imin]);
  CopyVector(bestit, c[imin]);

  ///////////////////////////////

  emin2 = energy2[0];
  imin2 = 0;
  for (i=1; i<NP/2; i++) {
    if (energy2[i] < emin2) {
      emin2 = energy2[i];
      imin2 = i;
    }
  }

  CopyVector(best2, c[imin2]);
  CopyVector(bestit2, c[imin2]);



  // old population (generation G)
  // new population (generation G+1)
  CopyArray(oldarray, c1);
  CopyArray(oldarray2, c2);
  // new population (generation G+1)
  CopyArray(newarray, d1);
  CopyArray(newarray2, d2);

  // Iteration loop
  gen = 0; // generation counter reset
  while ((gen < genmax)) {
    gen++;
    imin = 0;

    for (i=0; i<NP/2; i++) {
      // Pick a random population member 
      do {
        // Endless loop for NP < 2 !!!
        r = rnd_uni(&rnd_uni_init); 
        r1 = (int)(r*NP/2);
      } while(r1 == i);            
      
      do {
        // Endless loop for NP < 3 !!!
        r = rnd_uni(&rnd_uni_init);                         
        r2 = (int)(r*NP/2);
      } while((r2 == i) || (r2 == r1));

      do {
        // Endless loop for NP < 4 !!!     
        r3 = (int)(rnd_uni(&rnd_uni_init)*NP/2);
      } while((r3 == i) || (r3 == r1) || (r3 == r2));

	  ////////////////////////////////////////////////////////
      // Pick a random population member 
      do {
        // Endless loop for NP < 2 !!!
        r = rnd_uni(&rnd_uni_init); 
        r5 = (int)(r*NP/2);
      } while(r5 == i);            
      
      do {
        // Endless loop for NP < 3 !!!
        r = rnd_uni(&rnd_uni_init);                         
        r6 = (int)(r*NP/2);
      } while((r6 == i) || (r6 == r5));

      do {
        // Endless loop for NP < 4 !!!     
        r7 = (int)(rnd_uni(&rnd_uni_init)*NP/2);
      } while((r3 == i) || (r6 == r5) || (r7 == r6));



      // EXPONENTIAL CROSSOVER
      // DE/best/1/exp
      /*if (strategy == 1) {
        for (int k=0; k<MAXDIM; k++) {
          tmp[k] = oldarray[i][k];
        }
        n = (int)(rnd_uni(&rnd_uni_init)*D);
        L = 0;
        do {                       
          tmp[n] = bestit[n] + F*(oldarray[r2][n] - oldarray[r3][n]);
          n = (n+1)%D;
          L++;
        } while((rnd_uni(&rnd_uni_init) < CR) && (L < D));
      }*/

	  ///////////// DE/best/1/bin
	  if (strategy == 1) {
        for (int k=0; k<MAXDIM; k++) {
          tmp[k] = oldarray[i][k];
        }
        n = (int)(rnd_uni(&rnd_uni_init)*D);
        // perform D binomial trials
        for (L=0; L<D; L++) {
          // change at least one parameter
          if ((rnd_uni(&rnd_uni_init) < CR) || L == (D-1)) {                       
            tmp[n] = bestit[n] + F*(oldarray[r2][n] - oldarray[r3][n]);
          }
          n = (n+1)%D;
        }
      }

      // DE/rand/1/exp
      /*if (strategy2 == 2) {
        for (int k=0; k<MAXDIM; k++) {
          tmp2[k] = oldarray2[i][k];
        }
        n = (int)(rnd_uni(&rnd_uni_init)*D);
        L = 0;
        do {                       
          tmp2[n] = oldarray2[r5][n] + F*(oldarray2[r6][n] - oldarray2[r7][n]);
          n = (n+1)%D;
          L++;
        } while((rnd_uni(&rnd_uni_init) < CR) && (L < D));
      }*/

	  /////// DE/rand/1/bin
	  if (strategy2 == 2) {
        for (int k=0; k<MAXDIM; k++) {
          tmp2[k] = oldarray2[i][k];
        }
        n = (int)(rnd_uni(&rnd_uni_init)*D);
        // perform D binomial trials 
        for (L=0; L<D; L++) {
          // change at least one parameter
          if ((rnd_uni(&rnd_uni_init) < CR) || L == (D-1)) {                       
            tmp2[n] = oldarray2[r5][n] + F*(oldarray2[r6][n] - oldarray2[r7][n]);
          }
          n = (n+1)%D;
        }
      }
	   
      
	 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Trial mutation now in tmp[]. Test how good this choice really was.
	  //trial_energy = evaluate(D, tmp, &nfeval);  // Evaluate new vector in tmp[]
	  
	  //trial_energy = one_sphere(D, tmp, &nfeval);
	  //trial_energy2 = one_sphere(D, tmp2, &nfeval);

	  //trial_energy = seven_rosenbrock(D, tmp, &nfeval);

	  //trial_energy = ten_rastrigin(D, tmp, &nfeval);
	  //trial_energy2 = ten_rastrigin(D, tmp2, &nfeval);

	  trial_energy = fourteen_griewank(D, tmp, &nfeval);
	  trial_energy2 = fourteen_griewank(D, tmp2, &nfeval);

	  //trial_energy  = twoSchwefelsNonSep(D, tmp, &nfeval);
	  //trial_energy2 = twoSchwefelsNonSep(D, tmp2, &nfeval);

	  //trial_energy = twoSchwefelsSep(D, tmp, &nfeval);
	  //trial_energy = Eleven_non_con_Rastrigin(D, tmp, &nfeval);
	  //trial_energy = fifteen_Alpine(D, tmp, &nfeval);
	  //trial_energy = Kowalik(D, tmp, &nfeval);
	  
	  //trial_energy = Michalewicz(D, tmp, &nfeval);
	  //trial_energy2 = Michalewicz(D, tmp2, &nfeval);

      // improved objective function value?
      if (trial_energy <= energy[i]) {                                  
        energy[i] = trial_energy;         
        for (int k=0; k<MAXDIM; k++) {
          newarray[i][k] = tmp[k];
        }
        // Was this a new minimum?
        if (trial_energy<emin) {
          // reset emin to new low...
          emin = trial_energy;           
          imin = i;
          for (int k=0; k<MAXDIM; k++) {
            best[k] = tmp[k];
          }         
        }                           
      } 
	  else {
        // replace target with old value
        for (int k=0; k<MAXDIM; k++) {
          newarray[i][k] = oldarray[i][k];
        }
      }

	  CopyVector(bestit, best);  // Save best population member of current iteration

	  //////////////////////////////////////////////////////////////////////////////////
	  if (trial_energy2 <= energy2[i]) {                                  
        energy2[i] = trial_energy2;         
        for (int k=0; k<MAXDIM; k++) {
          newarray2[i][k] = tmp2[k];
        }
        // Was this a new minimum?
        if (trial_energy2<emin) {
          // reset emin to new low...
          emin2 = trial_energy2;           
          imin2 = i;
          for (int k=0; k<MAXDIM; k++) {
            best2[k] = tmp2[k];
          }         
        }                           
      } 
	  else {
        // replace target with old value
        for (int k=0; k<MAXDIM; k++) {
          newarray2[i][k] = oldarray2[i][k];
        }
      }
    }

    CopyVector(bestit2, best2);  // Save best population member of current iteration

	////////////////////////////////////////////// 1ST RANDOM GENERATE FOR STRETAGY 1 & 2
	for (i=0; i<NP/2; i++) { 
		do {
			r = rnd_uni(&rnd_uni_init); 
			r10 = (int)(r*NP/2);
		}while(r10 == i);

		do {
			r = rnd_uni(&rnd_uni_init); 
			r11 = (int)(r*NP/2);
		}while(r11 == i);
		////////////////////////////////////////////// 2ND RANDOM GENERATE FOR STRETAGY 1 & 2
		do {
			r = rnd_uni(&rnd_uni_init);                         
			r20 = (int)(r*NP/2);
        } while((r20 == i) || (r20 == 10));

		do {
			r = rnd_uni(&rnd_uni_init);                         
			r21 = (int)(r*NP/2);
        } while((r21 == i) || (r21 == r11));
	} 

	/*n = (int)(rnd_uni(&rnd_uni_init)*D);
	newarray[r10][n] = newarray2[r11][n];
	newarray2[r11][n] = newarray[r10][n];

	n = (int)(rnd_uni(&rnd_uni_init)*D);
	newarray[r20][n] = newarray2[r21][n];
	newarray2[r21][n] = newarray[r20][n];*/

	for(int i=0;i<MAXDIM;i++){
		newarray[r10][i]=bestit2[i];
		newarray2[r11][i]=bestit[i];
	}

    // swap population arrays. New generation becomes old one
    CopyArray(swaparray, oldarray);
    CopyArray(oldarray, newarray);
    CopyArray(newarray, swaparray);

	CopyArray(swaparray, oldarray2);
    CopyArray(oldarray2, newarray2);
    CopyArray(newarray2, swaparray);

    // display after every refresh generations

    // if (gen%refresh == 1) {
    if (false) {
      printf("\n\n Best-so-far obj. funct. value: %15.10f",emin);
      for (j=0; j<D; j++) {
        printf("\n best[%d]: %14.7f", j, best[j]);
      }
      printf("\n Generation: %d  NFEs: %d", gen, nfeval);
      printf("\n Strategy: %d  NP: %d  F: %f  CR: %f", strategy, NP, F, CR);

	  ////////////////////////////////

	  printf("\n\n Best-so-far obj. funct. value: %15.10f",emin2);
      for (j=0; j<D; j++) {
        printf("\n best[%d]: %14.7f", j, best2[j]);
      }
      printf("\n Generation: %d  NFEs: %d", gen, nfeval);
      printf("\n Strategy: %d  NP: %d  F: %f  CR: %f", strategy2, NP, F, CR);
    }
  }

  printf( "\n\n Best-so-far objective funct. value: %-15.10g", emin);
  for (j=0; j<D; j++) {
    printf("\n best[%d]: %18.10f", j, best[j]);
  }
  printf("\n No. of Generations: %d", gen);
  printf("\n Numner of Function Evaluations: %ld", nfeval);
  printf("\n Strategy: %d, NP: %d, F: %f, CR: %f", strategy, NP, F, CR); 

  //////////////////////////////////

  printf( "\n\n Best-so-far objective funct. value: %-15.10g", emin2);
  for (j=0; j<D; j++) {
    printf("\n best[%d]: %18.10f", j, best2[j]);
  }
  printf("\n No. of Generations: %d", gen);
  printf("\n Numner of Function Evaluations: %ld", nfeval);
  printf("\n Strategy: %d, NP: %d, F: %f, CR: %f", strategy2, NP, F, CR); 


  cin.get(ch);
  exit(0);

  return(0);
}



