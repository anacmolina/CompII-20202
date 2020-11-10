//================================================                                                                 
// Construccion de la clase. Diferencia finitas  |
// Main                                          |
//                                               |                                                                 
// Ana Cristina Molina                           |                                                                 
// Andres Arteaga                                |                                                                 
//                                               |                                                                 
// Update: 10 de noviembre de 2020               |                                                                 
//================================================ 

#include "Class_Method.h"
#include <iostream>

using namespace std;

// Solucion para ejemplo 1 - Sec. 11.4

// Definicion de la funcion y sus derivadas
double f( double x, double y, double yp )
{
  return (1.0/8.0)*( 32.0 + 2*pow(x,3) - y*yp);
}

double fy( double x, double y, double yp)
{  
  return 0;
}

double fyp( double x, double y, double yp)
{
  return 1.0/8.0*( -y );
}

// Codigo principal
int main()
{
  // Definicion constantes
  double a=1., b=3., alpha=17., beta=43./3; int N=39;

  // Objeto
  DiferenciasFinitas intento1 = DiferenciasFinitas(a, b, alpha, beta, N, f, fy, fyp);

  // Vector inicial
  vector<double> W;

  // Ejecucion del metodo
  W=intento1.initialize_W();
  intento1.do_while("dat.txt", pow(10, -4));

  return 0;    
}
