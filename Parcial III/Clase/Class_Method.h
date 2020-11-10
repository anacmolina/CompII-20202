//================================================                                                                 
// Construccion de la clase. Diferencia finitas  |
// Prototipo                                     |
//                                               |                                                                 
// Ana Cristina Molina                           |                                                                 
// Andres Arteaga                                |                                                                 
//                                               |                                                                 
// Update: 10 de noviembre de 2020               |                                                                 
//================================================  

#ifndef Method_H
#define Method_H
#include <functional>
#include <cmath>
#include <vector>


using namespace std;

class DiferenciasFinitas
{
    public:
    DiferenciasFinitas (const double, const double, const double, const double, const int, function<double(double, double, double)>, function<double(double, double, double)>, function<double(double, double, double)>);

    void set_a ( const double );
    double get_a () const;

    void set_b ( const double );
    double get_b () const;

    void set_alpha ( const double );
    double get_alpha () const;

    void set_beta ( const double );
    double get_beta () const;

    void set_N ( const double );
    double get_N () const;

    void set_f (function<double(double, double, double)>& f);
    double call_f (double, double, double);

    void set_fy (function<double(double, double, double)>& fy);
    double call_fy (double, double, double);

    void set_fyp (function<double(double, double, double)>& fpy);
    double call_fyp (double, double, double);

    void set_W ( vector<double> W);
    vector<double> get_W (); 

    vector<double> initialize_W();

    double get_h();

    void do_while(string, double);


    private:

    double a;
    double b;
    double alpha;
    double beta;
    int N;
    
    function<double(double, double, double)> f;   
    function<double(double, double, double)> fy;   
    function<double(double, double, double)> fyp;   

    double h;

    vector<double> W;
    vector<double> X;
};

#endif
