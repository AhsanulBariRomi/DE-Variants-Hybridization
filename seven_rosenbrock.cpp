# include "de.h"

float seven_rosenbrock(int D,float c[], long *nfeval)
{
	int k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

		s=0.0;
		m=0.0;
        double	ss=0.0;
        for(k=0;k<D-1;++k){
			m= c[k];
			s=s + 100* (c[k+1] - (m*m) )* (c[k+1] - ( m*m ))   + (m-1) *(m-1);
		}
		return s;
}
