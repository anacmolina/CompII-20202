//================================================
// Codigo de diferencias finitas no lineares     |
//                                               |    
// Burden Sec 11.4 - Ejercicio 1                 | 
//                                               |  
// Andres Arteaga                                |  
// Ana Cristina Molina                           |
//                                               |   
// Update: 10 de noviembre de 2020               |
//================================================

#include "../Class_Method.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <string>

// Funciones asociadas

double f( double x, double y, double yp )
{
    return -pow(yp,2)-y+log(x);
}

double fy( double x, double y, double yp)
{
    return -1.;
}

double fyp( double x, double y, double yp)
{
  return -2*yp;
}

double y( double x)
{
    return log(x);
}

// Codigo principal
int main()
{
    for (int i=1;i<=20;i++)
    {
        string title1="ejercicio1_n_"+to_string(i)+".txt", title2="ejercicio1_a_"+to_string(i)+".txt";

	// Constantes
        double a=1, b=2, alpha=0, beta=log(2); int N=i;
        double x=0;
        DiferenciasFinitas ejercicio1 = DiferenciasFinitas(a, b, alpha, beta, N, f, fy, fyp);
    
	// Soluciones analiticas
        ofstream file;
        file.open(title2);
        for (int j=0;j<=N+1;j++)
        {
            x = a + j*ejercicio1.get_h();
            file << x << "\t" << y(x) << endl;
        }

	// Soluciones numericas
        vector<double> W;
        W=ejercicio1.initialize_W();
        ejercicio1.do_while(title1, pow(10, -4));    

    }
    
    return 0;
   
}
