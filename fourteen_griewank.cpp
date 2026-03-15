# include "de.h"

float fourteen_griewank(int D,float c[], long *nfeval)
{
	int k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

	s=0.0;
        m=0.0;

        for(k=0;k<D;++k){
			m= c[k];
			s=s+m*m;
		}
        s=s/4000.0;
        m=1.0;
        for(k=0;k<D;++k){
			int t=k+1;
			m=m* cos ( c[k] / pow(t,0.5) );
		}
		s=s-m+1;

		return s;

}