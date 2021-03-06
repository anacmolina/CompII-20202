//================================================
// Codigo de diferencias finitas no lineares     |
//                                               |    
// Oscilador forzado                             | 
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

// Funciones y derivadas
double f( double x, double y, double yp )
{
    double M=2, S=1, r=0.3;
    return -(S/M)*y - (r/M)*yp + 2*(1-sin(x));
}

double fy( double x, double y, double yp)
{
    double M=2, S=1, r=0.3;
    return -S/M;
}

double fyp( double x, double y, double yp)
{
    double M=2, S=1, r=0.3;
    return -r/M;
}

// Solucion original
double y( double x)
{
    double C1=-278./109., C2=-110425000./38319931.;
    return 32*exp(-0.075*x)*(C1*cos(0.703118*x) + C2*sin(0.703118*x)) + 2. + (200./109.)*sin(x) + (60./109.)*cos(x);
}


int main()
{
  // Calculo para distintos N
    for (int i=100;i<=1000;i+=100)
    {    
        
        string title1="F-D_n_"+to_string(i)+".txt", title2="F-D_a_"+to_string(i)+".txt";

        double a=1., b=31., alpha=y(a), beta=y(b); int N=i;
        double x=0.;
        DiferenciasFinitas ejercicio1 = DiferenciasFinitas(a, b, alpha, beta, N, f, fy, fyp);
    
        ofstream file;
        file.open(title2);
        for (int j=0;j<=N+1;j++)
        {
            x = a + j*ejercicio1.get_h();
            file << x << "\t" << y(x) << endl;
        }
        file.close();

        vector<double> W;
        W=ejercicio1.initialize_W();
        ejercicio1.do_while(title1, pow(10, -4));
    }    
    return 0;
   
}
