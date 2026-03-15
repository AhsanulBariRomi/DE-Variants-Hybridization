# include "de.h"

float ten_rastrigin(int D,float c[], long *nfeval)
{
	int k,p;
	double s,x1,x2,m,m1;

	(*nfeval)++;

	s=0.0;
	m=0.0;
	for(k=0;k<D;++k){
		m= c[k];
		s= s + ( (m*m)  - 10 * cos(2*3.1416 *3.1416*  m /180) +10 ) ;
	}
	return s;
}