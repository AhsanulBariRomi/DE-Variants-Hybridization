# include "de.h"

float Michalewicz(int D,float c[],long *nfeval)
{
	int j,k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

	s=0.0;
	m=0.0;

    for (j=0;j<D; j++)
		{
			s += sin(c[j])*pow ( sin((j+1)*c[j]*c[j]/3.14159), 20);
		}
		s = -1 * s;

		return s;
}