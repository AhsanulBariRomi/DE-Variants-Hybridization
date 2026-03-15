# include "de.h"

float Kowalik(int D,float c[],long *nfeval)
{
	int k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

	s=0.0;
	m=0.0;
	
	double a[]= {0.1957 , 0.1947 , 0.1735 , 0.1600 , 0.0844 , 0.0627 , 0.0456 , 0.0342 , 0.0323, 0.0235 , 0.0246};
    double b[]= {0.25 , 0.5 , 1 , 2 , 4 , 6 , 8 , 10 , 12  , 14 , 16};

	for(k=0;k<11;++k)
        {
            m= (a[k]  -  (c[0]*(b[k]*b[k] + b[k] * c[1] ) ) / ( b[k]*b[k]+ b[k]* c[2]  + c[3] ) );
            s=s+ m*m;
        }
	return s;
} 