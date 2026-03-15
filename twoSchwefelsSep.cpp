# include "de.h"

float twoSchwefelsSep(int D,float c[],long *nfeval)
{
	int k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

	s=0.0;
	m=0.0;

	s=fabs(c[0]);

    for(k=0;k<D;++k)
	{
		if(fabs(c[k])>=s)
			s=fabs(c[k]);
    }
	return s;
}