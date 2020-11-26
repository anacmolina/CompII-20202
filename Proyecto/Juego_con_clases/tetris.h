//================================================                                                                 
// Clase tetris.h                                |
// Prototipo                                     |
//                                               |                                                                 
// Ana Cristina Molina                           |                                                                 
// Andres Arteaga                                |                                                                 
//                                               |                                                                 
// Update: 26 de noviembre de 2020               |                                                                 
//================================================

#ifndef Tetris_H
#define Tetris_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include<time.h>

// Constantes                                                                                                                               
#define size_sq 50   // Lado celda cuadricula
#define x_set 50     // Posx cuadricula
#define y_set 50     // Posx cuadricula
#define size_ver 650 // Lado ver cuadricula
#define size_hor 400 // Lado hor cuadricula                                                                                                
const int M = size_ver / size_sq; // Filas cuadricula
const int N = size_hor / size_sq; // Columnas Cuadricula  

// ID figuras                                                                                            
const int pieces[7][4] =
  {
    1, 3, 5, 7, //I n=0                                                                                  
    2, 4, 5, 7, //Z n=1                                                                                  
    3, 5, 4, 6, //S n=2                                                                                  
    3, 5, 4, 7, //T n=3                                                                                  
    2, 3, 5, 7, //L n=4                                                                                  
    3, 5, 7, 6, //J n=5                                                                                  
    2, 3, 4, 5, //O n=6                                                                                  
  };

class Tetris
{
 public:
  Tetris();
  sf::RenderWindow window{sf::VideoMode(700, 750), "Tetris"}; // Crear ventana   
  void create_window();
  void background();
  // Crea objetos con dos atributos                                                                        
  struct vtr2
  {
    int x, y;
  };
  
  sf::Color random_color(int );
  sf::RectangleShape squares(int , sf::Color );
  /*void traslation(int , int ); // Realizar traslacion en x y y usando las teclas Left, Right, Down
  void gen_figure(int );   // Generar figuras a partir de las celdas                                                                
  void draw_figure(sf::Color c); // Dibujar las figuras 
  bool check(); // Verificar que las figuras se queden en la cuadricula                                                   
  void rotation(int );
  bool top();   // Funcion para determinar game over                                                                                       
  void fixed_figure(sf::Color color);  // Fijar la figura al caer
  void remove_line(); // Determinar cuando se ocupa una fila completa
  void no_play();   // Pone en pantalla tecla para empezar a jugar                                                    */                                          

 private:
  bool start; // Variable para empezar el juego                                                        
  int value;  // Contador de puntaje                                                                   
  int screen[M][N] = {0};  // Ocupacion de la cuadricula (Copia)
  // ID figuras                                                                                            
  vtr2 fig[4], fig_prev[4], pos[4]; // Arreglos para encontrar las posiciones de cada celda de las figuras
  int dx, dy, rotate;
  void traslation(int , int ); // Realizar traslacion en x y y usando las teclas Left, Right, Down
  void gen_figure(int );   // Generar figuras a partir de las celdas                                                                
  void draw_figure(sf::Color c); // Dibujar las figuras 
  bool check(); // Verificar que las figuras se queden en la cuadricula                                                   
  void rotation(int );
  bool top();   // Funcion para determinar game over                                                                                       
  void fixed_figure(sf::Color color);  // Fijar la figura al caer
  void remove_line(); // Determinar cuando se ocupa una fila completa
  void no_play();   // Pone en pantalla tecla para empezar a jugar                                                    
};

#endif
