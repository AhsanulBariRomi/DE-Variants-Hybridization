# include "de.h"

float fifteen_Alpine(int D,float c[],long *nfeval)
{
	int k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

	s=0.0;
	m=0.0;
	m1=0.0;
	
	for(k=0;k<D;++k)
	{
        m= c[k];
        m1= m*0.1;

        s = s + fabs( (m*sin(m))+ m1);
    }

	return s;
}