# include "de.h"
float one_sphere(int D,float c[],long *nfeval)
{
	int k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

        s=0.0;
		for(k=0;k<D;++k){
			s= s + c[k]*c[k];
		}
		return s;
}