//================================================
// Juego tetris.cpp                              |
//                                               |
// Ana Cristina Molina                           |
// Andres Arteaga                                |
//                                               |
// Update: 26 de noviembre de 2020               |
//================================================

//Librerias
#include <iostream>        
#include <SFML/Graphics.hpp> // Libreria para los graficos
#include <time.h>

// Constantes
#define size_sq 50   // Lado celda cuadricula
#define x_set 50     // Posx cuadricula
#define y_set 50     // Posx cuadricula
#define size_ver 650 // Lado ver cuadricula
#define size_hor 400 // Lado hor cuadricula

const int M = size_ver / size_sq; // Filas cuadricula
const int N = size_hor / size_sq; // Columnas Cuadricula

// Variables globales
bool start = 0; // Variable para empezar el juego

int value = 0;  // Contador de puntaje

int screen[M][N] = {0};  // Ocupacion de la cuadricula (Copia) 

// ID figuras  
int pieces[7][4] =
  {
    1, 3, 5, 7, //I n=0
    2, 4, 5, 7, //Z n=1
    3, 5, 4, 6, //S n=2
    3, 5, 4, 7, //T n=3
    2, 3, 5, 7, //L n=4
    3, 5, 7, 6, //J n=5
    2, 3, 4, 5, //O n=6
  };

// Crea objetos con dos atributos
struct vtr2
{
  int x, y;
} fig[4], fig_prev[4], pos[4]; // Arreglos para encontrar las posiciones de cada celda de las figuras

// Funcion para determinar game over
bool top()
{
  for (int i = 0; i < N; i++)
    {
      if (screen[1][i] != 0) // Se recorre la segunda fila para determina si alguna celda esta ocupada
	  return 0;      
    }
  
  return 1;
}

// Se crea el fondo del juego
void background(sf::RenderWindow *window)
{
  sf::Texture imlogo;   // Se carga el logo
  imlogo.loadFromFile("download_.png");

  sf::Sprite logo(imlogo); // Se convierte en un rectangulo manipulable

  logo.setPosition(1.5*x_set + size_hor, y_set); // Se fija la posicion
  window->draw(logo); // Se pone en la ventana

  sf::Font font;  // Se carga la fuente para escribir
  font.loadFromFile("COURIER.TTF");

  // Objetos de texto para Game Over y el puntaje
  sf::Text text3;     
  sf::Text score;
  sf::Text value_score;

  // Determinar si se agrega GAME OVER a la pantalla, top = false :: Game Over
  if (!top())
  { 
    text3.setFont(font); // Usar fuente
    text3.setString("GAME\nOVER"); // Palabra
    text3.setCharacterSize(80); // Tamaño
    text3.setFillColor(sf::Color::White); // Color
    text3.setStyle(sf::Text::Bold); // Estilo
    text3.setPosition(size_hor + 1.5 * x_set, size_ver /1.5); // Posicion
    window->draw(text3); // Escribir texto
  }

  // Escribir el texto SCORE
  score.setFont(font);
  score.setString("SCORE");
  score.setCharacterSize(38); 
  score.setFillColor(sf::Color::Green);
  score.setStyle(sf::Text::Bold | sf::Text::Underlined); // Subrayado

  score.setPosition(size_hor + size_hor / 3.5, 2 * size_ver / 4); 
  window->draw(score);

  // Escribir el puntaje
  value_score.setFont(font);
  value_score.setString(std::to_string(value));
  value_score.setCharacterSize(38); 
  value_score.setFillColor(sf::Color::White);
  value_score.setStyle(sf::Text::Bold);

  value_score.setPosition(size_hor + 3 * x_set, 2 * size_ver / 4 + y_set);
  window->draw(value_score);

  // Marco de la cuadricula
  sf::RectangleShape setUp(sf::Vector2f(size_hor, size_ver)); // Tamano
  setUp.setOutlineThickness(5); // Grosor
  setUp.setOutlineColor(sf::Color::White); // Color

  // Celdas de la cuadricula
  sf::RectangleShape square_set(sf::Vector2f(size_sq, size_sq));
  square_set.setFillColor(sf::Color::Black); // Color
  square_set.setOutlineThickness(2);
  square_set.setOutlineColor(sf::Color::White);

  setUp.setPosition(x_set, y_set); 
  window->draw(setUp); // Dibujar marco

  // Dibujar celdas
  for (int j = 0; j < M; j++)
  {
    for (int i = 0; i < N; i++)
    {
      square_set.setPosition(x_set + i * size_sq, y_set + j * size_sq);
      window->draw(square_set);
    }
  }
}

// Elegir colores al azar
sf::Color random_color(int n)
{
  // Objetos de la libreria SFML
  sf::Color red = sf::Color::Red;
  sf::Color green = sf::Color::Green;
  sf::Color blue = sf::Color::Blue;
  sf::Color yellow = sf::Color::Yellow;
  sf::Color magenta = sf::Color::Magenta;
  sf::Color cyan = sf::Color::Cyan;

  if (n == 0)
    return red;
  if (n == 1)
    return green;
  if (n == 2)
    return blue;
  if (n == 3)
    return yellow;
  if (n == 4)
    return magenta;
  if (n == 5)
    return cyan;
}

// Funcion para crear cuadrados como objetos de la libreria
sf::RectangleShape squares(int s, sf::Color color)
{
  sf::RectangleShape square(sf::Vector2f(s - 2, s - 2)); // s: Lado del cuadrado
  square.setFillColor(color); // Pinta el cuadrado
  square.setOutlineThickness(2); // Borde de cuadrado 
  square.setOutlineColor(sf::Color::Black); // Color borde

  return square;
}

// Generar figuras a partir de las celdas
void gen_figure(int n)
{
  for (int i = 0; i < 4; i++)
  {
    fig[i].x = pieces[n][i] % 2 + N / 2 - 1;  // Centra en la mitad de la cuadricula
    fig[i].y = pieces[n][i] / 2;
  }
}

// Dibujar las figuras
void draw_figure(sf::RenderWindow *window, sf::Color c) // Se pasa por referencia la ventana a dibujar
{
  sf::RectangleShape s = squares(size_sq, c); // Se crea un cuadrado

  // Se calculan, fijan y dibujan las posiciones 
  for (int i = 0; i < 4; i++)
    { 
      pos[i].x = x_set + fig[i].x * size_sq;      
      pos[i].y = y_set + (fig[i].y - 1) * size_sq;
      
      s.setPosition(pos[i].x, pos[i].y);
      window->draw(s);
    }
}

// Verificar que las figuras se queden en la cuadricula
bool check()
{
  for (int i = 0; i < 4; i++)
    if (fig[i].x < 0 || fig[i].x >= N || fig[i].y >= M)
      return 0;
    else if (screen[fig[i].y][fig[i].x]) // Verificar la ocupacion en la matriz copia
      return 0;

  return 1;
}

// Realizar traslacion en x y y usando las teclas Left, Right, Down
void traslation(int dx, int dy) // Recibe la variacion en x y y
{
  // Traslacion en x y aumento de dx
  for (int i = 0; i < 4; i++)
  {
    fig_prev[i] = fig[i];
    fig[i].x += dx;
  }
  if (!check()) // Si se sale de la cuadricula se deja como estaba
    for (int i = 0; i < 4; i++)
      fig[i] = fig_prev[i];

  // Mismo para y
  for (int i = 0; i < 4; i++)
  {
    fig_prev[i] = fig[i];
    fig[i].y += dy;
  }
  if (!check())
    for (int i = 0; i < 4; i++)
      fig[i] = fig_prev[i];
}

// Rotar la figura que deciende
void rotation(int rotate)
{
  if (rotate == 1)
  {
    vtr2 cr = fig[1];  // Define el centro de rotacion (cr)
    for (int i = 0; i < 4; i++)
    {
      int vx = fig[i].x - cr.x; // Diferencia con cr
      int vy = fig[i].y - cr.y;

      int vtx = -1 * vy; // Matriz de rotacion
      int vty = 1 * vx;

      fig[i].x = cr.x + vtx; // Vector final
      fig[i].y = cr.y + vty;
    }
    if (!check()) // Verificar que no se salga de la celda
      for (int i = 0; i < 4; i++)
        fig[i] = fig_prev[i];
  }
}

// Fijar la figura al caer
void fixed_figure(sf::RenderWindow *window, sf::Color color)
{
  sf::RectangleShape square = squares(size_sq, color); // Se crea el cuadrado

  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
    {
      if (screen[i][j] == 0) // Verifica ocupacion si esta ocupado dibuja la celda
        continue;
      square.setPosition(x_set + j * size_sq, y_set + i * size_sq);
      window->draw(square);
    }
}

// Determinar cuando se ocupa una fila completa
void remove_line()
{
  int k = M - 1;
  for (int i = M - 1; i > 0; i--)
  {
    int count = 0;
    for (int j = 0; j < N; j++)
    {
      if (screen[i][j])
        count++;
      screen[k][j] = screen[i][j];

      if (count >= N)
        value += 100;
    }
    if (count < N)
      k--;
  }
}

// Pone en pantalla tecla para empezar a jugar
void no_play(sf::RenderWindow* window)
{
  sf::Text text1, text2;
  
  sf::Font font;
  font.loadFromFile("COURIER.TTF");
  
  text1.setFont(font);
  text1.setString("To start press");
  text1.setCharacterSize(24); 
  text1.setFillColor(sf::Color::Red);
  text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
  
  text1.setPosition(size_hor + 1.5 * x_set, size_ver / 3);
  window->draw(text1);
  
  text2.setFont(font);
  text2.setString("SPACE");
  text2.setCharacterSize(48); 
  text2.setFillColor(sf::Color::Red);
  text2.setStyle(sf::Text::Bold);
  
  text2.setPosition(size_hor + size_hor / 4, size_ver / 2.6 );
  window->draw(text2);	
}

int main()
{
  srand(time(NULL)); // Semilla
    
  int dx = 0, dy = 0, rotate = 0;  // Inicializar traslacion y rotacion
  float timer = 0, delay = 0.5;    // Contador y tiempo de caida entre fila y fila

  // Generar primera figura
  int l = rand() % 7;
  gen_figure(l);
  
  sf::Clock clock; // Crear reloj

  sf::RenderWindow window(sf::VideoMode(700, 750), "Tetris"); // Crear ventana

  while (window.isOpen())  // Ventana abierta
  {
    float time = clock.getElapsedTime().asSeconds(); // Inicializar tiempo

    clock.restart(); // Empezar reloj
    timer += time;   // Contar tiempo transcurrido

    sf::Event e;     // Eventos detectados (Usar teclas)

    while (window.pollEvent(e))
    {
      if (e.type == sf::Event::Closed)
      {
        window.close();
      }

      if (e.type == sf::Event::KeyPressed)  // Uso de teclas
      {
	if (e.key.code == sf::Keyboard::Space) // Teclas para empezar el juego
          {
	    start = 1;
	    
	    value = 0; // Iniciar score y matriz copia
	    for(int i=0; i<N; i++)
	      for(int j=0; j<M; j++)
		screen[j][i] = 0;	      
	  }

	// Teclas para la rotacion, derecha, izquierda y abajo 
	else if (e.key.code == sf::Keyboard::Up)  
	  rotate = 1;
	
	else if (e.key.code == sf::Keyboard::Down)
	  dy = 1;
	
	else if (e.key.code == sf::Keyboard::Right)
	  dx = 1;
	
	else if (e.key.code == sf::Keyboard::Left)
	  dx = -1;
      }
    }

    window.clear(sf::Color::Black); // Refresca la pantalla

    background(&window); // Se dibuja el fondo
    
    if(!start) // Solo empieza en start true
      {
	no_play(&window); // Mensaje para empezar a jugar
      }    
    else      
      {
	int m;
	if (!top()) // Se termina el juego
	  {
	    start = 0; // Se pone en false el empezar a jugar
	  }
	else if (timer > delay) // 
	  {
	    for (int i = 0; i < 4; i++)
	      {
		fig_prev[i] = fig[i]; // Guarda posicion actual 
		fig[i].y += 1; // Se baja la figura en cada ciclo
	      }
	    
	    if (!check()) // Llegar al final 
	      {
		for (int i = 0; i < 4; i++)
		  screen[fig_prev[i].y][fig_prev[i].x] = 1; // Se actualiza la ocupacion
		
		int n = rand() % 7; 
		gen_figure(n); // Genera figura aleatoriamente

	      }
	    
	    m = rand() % 6; 
	    
	    timer = 0; // Reinicia el tiempo
	  }
	
	sf::Color color = random_color(m); // General color

	draw_figure(&window, color); // Dibuja la figura
	
	traslation(dx, dy); // Traslacion
	
	rotation(rotate); // Rotacion
	
	remove_line(); // Mover linea
	
	fixed_figure(&window, color); // Fijar las figuras
	
	dx = 0, dy = 0, rotate = 0; // Reinicia los movimientos	
      }

    window.display(); // Mostrar en pantalla
  }

  return 0;
}
