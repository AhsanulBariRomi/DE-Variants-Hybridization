# include "de.h"

float twoSchwefelsNonSep(int D,float c[],long *nfeval)
{
	int k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

	s=0.0;
	m=0.0;

	for(k=0;k<D;++k)
	{
		s= s + fabs(c[k]);
		m= m * fabs(c[k]);
	}
	s=s+m;

	return s;

}