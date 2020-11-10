//================================================
// Codigo de diferencias finitas no lineares     |
//                                               |    
// Burden Sec 11.4 -- Fisica computacional II    | 
// Ejemplo 1                                     |
//                                               |   
// Andres Arteaga                                |  
// Ana Cristina Molina                           |
//                                               |   
// Update: 10 de noviembre de 2020                |
//================================================

#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

/* Solucion para ejemplo 1 - Sec. 11.4
   y'' = 1/8( 32 + 2x^3 - y*y' )
   a = 1 , b = 3 , y(1)=17 , y(3)=43/3
*/

// Definicion de la funcion y sus derivadas
double f( double x, double y, double yp )
{
  return (1.0/8.0)*( 32.0 + 2*pow(x,3) - y*yp);
}

double fy( double x, double y, double yp)
{
  return 1.0/8.0*( -yp );
}

double fyp( double x, double y, double yp)
{
  return 1.0/8.0*( -y );
}

// Codigo principal
int main()
{
  // Definicion de las constantes
  double TOL = pow(10, -4);
  double a = 1.0, b = 3.0;
  double alpha = 17.0, beta = 43.0/3;
  int N = 39;
  double h = ( b - a )/(N + 1) ;

  // Inicializacion vector W
  vector<double> w;
  double w0 = alpha, wNp1 = beta;

  w.push_back(w0);
  for (int i=1; i<=N; i++) w.push_back(alpha + i*h*(beta-alpha)/(b-a));
  w.push_back(wNp1);

  // Definicion de los ciclos
  int k=1, M=300;

  while(k<=M)
    {
      // Calculo de los coeficientes de la matriz jacobiana
      double x, t;

      x = a + h;
      t = (w[2] - alpha)/(2*h);
      
      vector<double> A, B, C, D;

      A.push_back( 2.0 + pow(h, 2.0)*fy(x, w[1], t) );
      B.push_back( -1.0 + (h/2.0)*fyp(x, w[1], t) );
      C.push_back( 0.0 );
      D.push_back( -(2.0*w[1] - w[2] - alpha + pow(h, 2.0)*f(x, w[1], t)) );

      for(int i=2; i<=N-1; i++)
	{
	  x = a + i*h;
	  t = (w[i+1] - w[i-1])/(2*h);

	  A.push_back( 2.0 + pow(h, 2.0)*fy(x, w[i], t) );
	  B.push_back( -1.0 + (h/2.0)*fyp(x, w[i], t) );
	  C.push_back( -1.0 - (h/2.0)*fyp(x, w[i], t) );
	  D.push_back( -(2.0*w[i] - w[i+1] - w[i-1] + pow(h, 2.0)*f(x, w[i], t)) );
	}

      x = b - h;
      t = (beta - w[N-1])/(2*h);
      
      A.push_back( 2.0 + pow(h, 2.0)*fy(x, w[N], t) );
      B.push_back( 0.0 );
      C.push_back( -1.0 + (h/2.0)*fyp(x, w[N], t) );    
      D.push_back( -(2.0*w[N] - w[N-1] - beta + pow(h, 2.0)*f(x, w[N], t)) );
      

      // Solucion al sistema de ecuaciones
      
      vector<double> L, U, Z;

      L.push_back(A[0]);
      U.push_back(B[0]/A[0]);
      Z.push_back(D[0]/L[0]);

      for(int i=1; i<=N-2; i++)
	{
	  L.push_back(A[i] - C[i]*U[i-1]);
	  U.push_back(B[i]/L[i]);
	  Z.push_back((D[i]-C[i]*Z[i-1])/L[i]);
	}

      L.push_back(A[N-1] - C[N-1]*U[N-2]);
      U.push_back(0.0);
      Z.push_back((D[N-1]-C[N-1]*Z[N-2])/L[N-1]);

      // Calculo del vector v y suma para converger w a y
      vector<double> v (N+1);

      v.at(N) = Z[N-1];

      w[N] = w[N] + v[N];

      for( int i=N-1; i>=1; i-- )
	{
	  v.at(i) = Z[i-1] - U[i-1]*v[i+1];
	  w[i] = w[i] + v[i];
	}

      A.clear(); B.clear(); C.clear(); D.clear();
      L.clear(); U.clear(); Z.clear();

      // Calculo de la tolerancia
      double s_v=0;
      
      for(int i=1; i<v.size(); i++)
	{
	  s_v = s_v + v[i]*v[i];
	}

      double norm_v = sqrt(s_v);      

      cout << "iter: "<< k << "\t \t" << norm_v << endl;
      
      if(norm_v<=TOL)
	{
	  cout << "x \t y" << endl;
	  
	  for(int i=0; i<=N+1; i++)
	    {
	      x = a + i*h;
	      cout << x << "\t" << w[i] << endl;
	    }
	  
	  cout << "Procedimiento exitoso." <<  endl;
	  
	  k = M+1;
	}
      else
	{
	  k++;
	  
	  if(k>M)
	    {
	      cout << "Iteraciones excedidas. Procedimiento fallido." <<  endl;
	    }
	}      
    }
  
  return 0;  
}


