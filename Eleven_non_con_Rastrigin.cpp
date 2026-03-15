# include "de.h"
#include "math.h"

float Eleven_non_con_Rastrigin(int D,float c[],long *nfeval){

	int k,p;
	double s,x1,x2,m,m1,y;

	(*nfeval)++;

        s=0.0;
        m=0.0;
        y=0.0;

        for(k=0;k<D;++k)
		{
            m= c[k];

			if(fabs(m)<0.5)
                y=m;
            else if(fabs(m)>=0.5)
                y=0.5*floor((2*m)+0.5);

			s= s + ( (y*y)  - 10 * cos(2*3.1416 *3.1416*  y /180) +10 ) ;
		}
		return s;
}