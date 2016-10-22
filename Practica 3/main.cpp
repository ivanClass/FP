/*************************************************************************
				PRACTICA 3 - COLOR CRUSH
Noel Jose Algora Igual
Ivan Aguilera Calle
L01-G101

Partes Opcionales:
 -Permitir salvar partidas y recuperarlas(0.5):
	void guardarPartida(tJuego juego,bool &ok);
	void cargarPartida(tJuego &juego,bool &ok);

 -Cargar y guardar tableros de archivos(0.25):
	void cargarTablero(tTablero &tablero, bool &ok);		//carga un tablero de un fichero de texto
	void guardarTablero(const tTablero tableroguardar);		// guarda un tablero en un fichero de texto

 -Mantener en un archivo las puntuaciones de los usuarios(0.25):
	void guardarPuntuaciones(string nombre,int puntos);		//guarda nombre jugador y sus puntuaciones en un archivo de texto
	void mostrarPuntuaciones();	

*****************************************************************************/

/*
	-he cambiado un poco los graficos, las puntuaciones y los intentos para que salgan centrados
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const string archivoPuntuaciones = "puntuaciones.txt";
const bool DEBUG = false;
const int MLS_PAUSA = 300;
const int FILAS = 8;
const int COLUMNAS = 8;
const int INTENTOS = 15;

const char ESQUINASUPERIORIZQDA=char(218);
const char LINEAHORIZONTAL=char(196);
const char TABAJO=char(194);
const char ESQUINASUPERIORDCHA=char(191);
const char LINEAVERTICAL=char(179);
const char TDERECHA=char(195);
const char TCENTRAL=char(197);
const char TIZQUIERDA=char(180);
const char ESQUINAINFERIORIZQDA=char(192);
const char TARRIBA=char(193);
const char ESQUINAINFERIORDCHA=char(217);
const char FICHA=char(219);

typedef enum tFicha
{
	vacio,
	magenta,
	amarillo,
	azul,
	verde
};

typedef enum tDireccion
{
	arriba,
	abajo,
	izquierda,
	derecha,
	error
};

typedef enum { // Screen colors
	black, // 0
	dark_blue, // 1
	dark_green, // 2
	dark_cyan, // 3
	dark_red, // 4
	dark_magenta, // 5
	dark_yellow, // 6
	light_gray, // 7
	dark_gray, // 8
	light_blue, // 9
	light_green, // 10
	light_cyan, // 11
	light_red, // 12
	light_magenta, // 13
	light_yellow, // 14
	white // 15
} tColor;

typedef tFicha tTablero[FILAS][COLUMNAS];
typedef bool tBoolTablero[FILAS][COLUMNAS];

typedef struct 
{
	tTablero tablero;
	int intentos;
	int puntos;
} tJuego;

typedef struct
{
	int fila;
	int columna;
	tDireccion direccion;
} tMovimiento;

void jugar(tJuego &juego,bool &partida_no_acabada,bool nueva_partida);  //lleva a cabo toda la dinamica del juego junto con nuevaPartida y procesoJuego
void nuevaPartida(tJuego &juego,bool nueva_partida,bool &ok);
void procesoJuego(tJuego &juego, bool &ok);

void setColor(tColor color);
void generarTablero(tTablero tablero);									//genera un tTablero aleatoriamente
tFicha generarFicha();													//genera un tFicha aleatorio
void dibujarTablero(tJuego juego);										//muestra el tJuego(tablero,intentos y puntos) por pantalla
tColor fichaAColor(tFicha ficha);										//recibe un tFicha y devuelve un tColor
void dibujarLinea(char izq,char centro,char drcha);	

void process(tJuego &juego,bool &changed);									//elimina las fichas que hayan formado grupo
void processLoop(tJuego &juego);											//elimina los grupos de fichas hasta que no haya ninguno
void processFilas(tJuego &juego, bool &changed, tBoolTablero eliminar);		// busca grupos de fichas por filas y marca tBoolTablero con true,si hay grupo de																					   fichas,en las casillas en las que hay grupo
void processColumnas(tJuego &juego,bool &changed, tBoolTablero eliminar);	// busca grupos de fichas por columnas y marca tBoolTablero con true,si hay grupo de																				   fichas,en las casillas en las que hay grupo
void sumarPuntos(int cont,int &puntos);										//suma los puntos correspondientes

void drop(tTablero tablero,bool &changed);		//se encarga de la caida de fichas
void dropLoop(tJuego &juego);					//hace que las fichas sigan cayendo hasta que no haya ningun grupo ni huecos

tMovimiento nuevoMovimiento(int fila,int columna,char direccion);			//recibe fila,columna y una direccion del usuario y devuelve un tMovimiento(con la fila-1																			  y columna-1 introducida por el usuario)
void mover(tTablero tablero, tMovimiento move, bool &ok);					
bool movimientoValido(tMovimiento move);									//comprueba que el movimiento sea valido
void intercambiarFichas(tTablero tablero, tMovimiento move);				 //intercambia dos fichas del tablero
bool probarGrupos(const tTablero tablero,tMovimiento move);					//si se han formado grupos por filas o columnas devuelve true, si no false;
bool probarGruposFilas(const tTablero tablero, int fila,int columna);		//si se han formado grupo de fichas por filas devuelve true, si no false;
bool probarGruposColumnas(const tTablero tablero, int fila,int columna);	//si se han formado grupo de fichas por columnas devuelve true, si no false;
void posicionDestino(tDireccion direccion, int &incrFila,int &incrCol);		//dependiendo de la direccion introducida por el usuario, devuelve incrFila e incrCol

void guardarPartida(tJuego juego,bool &ok);		//guarda una partida(intentos,puntos y tablero) en un archivo de texto
void cargarPartida(tJuego &juego,bool &ok);		// carga una partida(intentos,puntos y tablero) de un archivo de texto

int opcionMenu();				//muestra un menu por pantalla para que el usuario elija una opcion

void mostrarPuntuaciones();		//lee y muestra por pantalla un archivo de puntuaciones con los nombres de los jugadores y sus puntuaciones y nº de partidas
void guardarPuntuaciones(string nombre,int puntos);		//guarda nombre jugador y sus puntuaciones en un archivo de texto

void cargarTablero(tTablero &tablero, bool &ok);		//carga un tablero de un fichero de texto
void guardarTablero(const tTablero tableroguardar);		// guarda un tablero en un fichero de texto


int main()
{
	int opcion;
	bool partida_acabada,ok;
	string nombreArchivo,nombre_usuario;
	tJuego juego;
	srand(time(NULL));

	setColor(white);
	cout << "Introduzca su nombre: "; cin >> nombre_usuario;

	do
	{
		opcion = opcionMenu();

		switch(opcion)
		{
			case 1:	//Nueva partida
				jugar(juego,partida_acabada,true);
				if(partida_acabada)
					guardarPuntuaciones(nombre_usuario,juego.puntos);
				break;
			case 2: //Cargar partida de archivo
				cargarPartida(juego,ok);
				if(ok)
				{
					jugar(juego,partida_acabada,false);
					if(partida_acabada)
						guardarPuntuaciones(nombre_usuario,juego.puntos);
				}
				break;
			case 3: //Generar tablero en archivo
				generarTablero(juego.tablero);
				guardarTablero(juego.tablero);
				break;
			case 4: //Mostrar puntuaciones
				mostrarPuntuaciones();
				break;
		}
	} 
	while (opcion != 0);
	
	return 0;
}

void jugar(tJuego &juego,bool &partida_acabada,bool nueva_partida)
{
	bool ok;

	nuevaPartida(juego,nueva_partida,ok);

	dibujarTablero(juego);

	processLoop(juego);

	procesoJuego(juego,ok);

	if(juego.intentos == 0)
	{
		partida_acabada = true;
		cout << "Enhorabuena partida completada con " << juego.puntos <<  " puntos" << endl;
		system("pause");
		system("cls");
	}
	else
		partida_acabada = false;
}

void nuevaPartida(tJuego &juego, bool nueva_partida, bool &ok){
	int opcion;

	if(nueva_partida)
	{
		juego.intentos = INTENTOS;
		juego.puntos = 0;

		do{
			cout << "Introduzca 0 para tablero aleatorio o 1 para cargarlo de archivo: "; cin >> opcion;
		}while(opcion != 0 && opcion != 1);

		if(opcion == 0)
			generarTablero(juego.tablero);
		else
		{
			cargarTablero(juego.tablero,ok);
			if(!ok){
				cout << "Tablero generado aleatoriamente" << endl;
				system("pause");
				generarTablero(juego.tablero);
			}
		}
		juego.intentos = INTENTOS;
		juego.puntos = 0;
	}
}

void procesoJuego(tJuego &juego, bool &ok){
	bool salir = false,	movimiento_correcto = true;
	tMovimiento move;	
	int fila,columna;
	char direccion;

	while (!salir) 
	{
		if(juego.intentos == 0)
			salir = true;
		else
		{
			cout << "Fila, columna y letra de direccion (A, B, I o D; 0 salir;-1 guardar): ";
			cin >> fila;
			if(fila == 0)
				salir = true;
			else if(fila == -1)
			{
				string nombreArchivo;
				guardarPartida(juego,ok);
				if(ok)
					salir = true;
			}
			else
			{
				cin >> columna >> direccion;

				move = nuevoMovimiento(fila,columna,direccion);
				mover(juego.tablero,move,movimiento_correcto);

				if(!movimiento_correcto)
					cout << "Movimiento incorrecto...." << endl;
				else
				{
					juego.intentos--;
					dibujarTablero(juego);
					processLoop(juego);
				}
			}
		}
	}
}
void setColor(tColor color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

void generarTablero(tTablero tablero)	//genera un tablero aleatoriamente
{
	for (int i = 0; i < FILAS; i++)
		for (int j = 0; j < COLUMNAS; j++)
			tablero[i][j] = generarFicha();
}

tFicha generarFicha()	//genera una ficha de color aleatorio
{
	return tFicha(rand()%4 +1);
}

void dibujarTablero(tJuego juego)	//muestra el tJuego(tablero,intentos y puntos) por pantalla
{
	if(!DEBUG) system("cls");
	setColor(white);
	cout << setw(15) << right << "Intentos: " << juego.intentos << "    Puntos: " << juego.puntos << endl;

	dibujarLinea(ESQUINASUPERIORIZQDA,TABAJO,ESQUINASUPERIORDCHA);

	for (int i = FILAS-1; i > -1; i--)
	{
		cout << setw(2) << i + 1  << setw(2) << LINEAVERTICAL;
		for (int j = 0; j  < COLUMNAS; j ++)
		{
			setColor(fichaAColor(juego.tablero[i][j]));
			for (int k = 0; k < 3; k++)
				cout << FICHA;

			setColor(white);
			cout << LINEAVERTICAL;
		}

		cout << endl;
		if(i != 0)
			dibujarLinea(TDERECHA,TCENTRAL,TIZQUIERDA);
	}

	dibujarLinea(ESQUINAINFERIORIZQDA,TARRIBA,ESQUINAINFERIORDCHA);
	
	cout << setw(2) << " ";
	for (int i = 0; i < COLUMNAS; i++)
		cout << setw(4) << i + 1;
	cout << endl;

	if(DEBUG)
	{
		system("pause");
		cout << endl;
	}
	else
		Sleep(MLS_PAUSA);
}

void dibujarLinea(char izq,char centro,char drcha)
{
	cout << setw(4) << izq;
	for (int i = 0; i < COLUMNAS; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << LINEAHORIZONTAL;
	
		if(i < COLUMNAS -1)
			cout << centro;
	}
	cout << drcha;
	cout << endl;
}

tColor fichaAColor(tFicha ficha)	//recibe un tFicha y devuelve un tColor
{
	tColor color;
	switch (ficha)
	{
		case vacio:
			color = black;
			break;
		case magenta:
			color = light_magenta;
			break;
		case amarillo:
			color = light_yellow;
			break;
		case azul:
			color = light_blue;
			break;
		case verde:
			color = light_green;
			break;
	}
	return color;
}

void processLoop(tJuego &juego)		//elimina los grupos de fichas hasta que no haya ninguno
{
	bool changed = true;

	while (changed) 
	{
		process(juego,changed);

		if (changed) 
		{
			dibujarTablero(juego);
			
			dropLoop(juego);
		}
	}
}

void process(tJuego &juego,bool &changed)		//elimina las fichas que hayan formado grupo
{
	tBoolTablero eliminar = {0};

	changed = false;

	processFilas(juego,changed,eliminar);
	processColumnas(juego,changed,eliminar);

	for (int i = 0; i < FILAS; i++)
		for (int j = 0; j < COLUMNAS; j++)
			if(eliminar[i][j] == true)
				juego.tablero[i][j] = vacio;
}

void processFilas(tJuego &juego, bool &changed,tBoolTablero eliminar)	//busca grupo de fichas por filas y marca tBoolTablero con true, si hay grupo de fichas, en las casillas en los que hay grupo
{
	tFicha ultima;
	int cont;

	for (int i = 0; i < FILAS; i++)
	{
		ultima = vacio;
		cont = 1;

		for (int j = 0; j < COLUMNAS; j++)
		{
			if(juego.tablero[i][j] != ultima)
			{
				if(cont > 2)
				{
					changed = true;
					sumarPuntos(cont,juego.puntos);

					for (int k = j - cont; k < j; k++)
						eliminar[i][k] = true;
				}
				ultima = juego.tablero[i][j];
				cont = 1;
			}
			else
				cont++;
		}

		if(cont > 2)
		{
			changed = true;
			sumarPuntos(cont,juego.puntos);

			for (int k = COLUMNAS - cont; k < COLUMNAS; k++)
				eliminar[i][k] = true;
		}
	}
}

void processColumnas(tJuego &juego,bool &changed,tBoolTablero eliminar) // busca grupos de fichas por columnas y marca tBoolTablero con true,si hay grupo de fichas,en																		   las casillas en las que hay grupo
{
	tFicha ultima;
	int cont;

	for (int i = 0; i < COLUMNAS; i++)
	{
		ultima = vacio;
		cont = 1;

		for (int j = 0; j < FILAS; j++)
		{
			if(juego.tablero[j][i] != ultima)
			{
				if(cont > 2)
				{
					changed = true;
					sumarPuntos(cont,juego.puntos);

					for (int k = j - cont; k < j; k++)
						eliminar[k][i] = true;
				}
				ultima = juego.tablero[j][i];
				cont = 1;
			}
			else
				cont++;
		}

		if(cont > 2)
		{
			changed = true;
			sumarPuntos(cont,juego.puntos);
		
			for (int k = FILAS - cont; k < COLUMNAS; k++)
				eliminar[k][i] = true;
		}
	}
}

void sumarPuntos(int cont,int &puntos)		//suma los puntos correspondientes
{
	switch (cont)
	{
		case 3:
			puntos += 3;
			break;
		case 4:
			puntos += 8;
			break;
		case 5:
		default:
			puntos += 15;
			break;
	}
}

void drop(tTablero tablero,bool &changed)  //se encarga de la caida de fichas
{
	changed = false;
	for (int col = 0; col < COLUMNAS; col++)
	{
		for (int fila = 0; fila < FILAS - 1; fila++)
			if(tablero[fila][col] == vacio)
			{
				changed = true;
				tablero[fila][col] = tablero[fila + 1][col];
				tablero[fila + 1][col] = vacio;
			}

		if(tablero[FILAS - 1][col] == vacio)
		{
			changed = true;
			tablero[FILAS - 1][col] = generarFicha();
		}
	}
}

void dropLoop(tJuego &juego) //hace que las fichas sigan cayendo hasta que no haya ningun grupo ni huecos
{
	bool changed = true;

	while(changed)
	{
		drop(juego.tablero,changed);

		if(changed)
			dibujarTablero(juego);
	}
}

tMovimiento nuevoMovimiento(int fila,int columna,char direccion) //recibe fila,columna y una direccion del usuario y devuelve un tMovimiento(con la fila-1 y columna-1																	 introducida por el usuario)
{
	tMovimiento move;
	
	move.fila = fila - 1;
	move.columna = columna - 1;
	direccion = toupper(direccion);

	switch(direccion)
	{
		case 'A':
			move.direccion = arriba;
			break;
		case 'B':
			move.direccion = abajo;
			break;
		case 'I':
			move.direccion = izquierda;
			break;
		case 'D':
			move.direccion = derecha;
			break;
		default:
			move.direccion = error;
			break;
	}

	return move;
}

bool movimientoValido(tMovimiento move)		 //comprueba que el movimiento sea valido
{
	bool ok = true;

	if(move.direccion != error)
	{
		if(move.fila >= 0 && move.fila <= FILAS - 1 && move.columna >= 0 && move.columna <= COLUMNAS - 1)
		{
			switch (move.direccion)
			{
				case arriba:
					if(move.fila == FILAS)
						ok = false;
					break;
				case abajo:
					if(move.fila == 0)
						ok = false;
					break;
				case izquierda:
					if(move.columna == 0)
						ok = false;
					break;
				case derecha:
					if(move.columna == COLUMNAS)
						ok = false;
					break;
			}
		}
		else
			ok = false;
	}
	else
		ok = false;

	return ok;
}

void mover(tTablero tablero, tMovimiento move, bool &ok)
{
	if(movimientoValido(move))
	{
		intercambiarFichas(tablero,move);

		if(probarGrupos(tablero,move))
		{
			ok = true;
		}
		else
		{
			intercambiarFichas(tablero,move);
			ok = false;
		}
	}
	else
		ok = false;
}

void intercambiarFichas(tTablero tablero, tMovimiento move)  //intercambia dos fichas
{
	int incrFila, incrCol;
	tFicha temp;

	posicionDestino(move.direccion,incrFila,incrCol);

	temp = tablero[move.fila + incrFila][move.columna + incrCol];
	tablero[move.fila + incrFila][move.columna + incrCol] = tablero[move.fila][move.columna];
	tablero[move.fila][move.columna] = temp;
}

bool probarGrupos(const tTablero tablero,tMovimiento move)  //si se han formado grupos por filas o columnas devuelve true, si no false;
{
	int incrFila, incrCol;
	bool ok = false;

	posicionDestino(move.direccion,incrFila,incrCol);

	switch (move.direccion)
	{
		case arriba:
		case abajo:
			if(probarGruposColumnas(tablero,move.fila,move.columna))
				ok = true;
			else if(probarGruposColumnas(tablero,move.fila + incrFila,move.columna + incrCol))
				ok = true;
			else if (probarGruposFilas(tablero,move.fila + incrFila,move.columna + incrCol))
				ok = true;
			else if (probarGruposFilas(tablero,move.fila,move.columna))
				ok = true;
			else
				ok = false;
			break;
		case izquierda:
		case derecha:

			if(probarGruposFilas(tablero,move.fila,move.columna))
				ok = true;
			else if(probarGruposFilas(tablero,move.fila + incrFila,move.columna + incrCol))
				ok = true;
			else if (probarGruposColumnas(tablero,move.fila + incrFila,move.columna + incrCol))
				ok = true;
			else if (probarGruposColumnas(tablero,move.fila,move.columna))
				ok = true;
			else
				ok = false;
			break;
	}

	return ok;
}

bool probarGruposFilas(const tTablero tablero, int fila,int columna) //si se han formado grupo de fichas por filas devuelve true, si no false;
{
	bool ok = false;
	int cont = 1;
	int columna_probar = columna - 1;
	bool ficha_diferente = false;

	while(columna_probar >= 0 && !ficha_diferente)
	{
		if(tablero[fila][columna] != tablero[fila][columna_probar])
			ficha_diferente = true;
		else
		{
			columna_probar--;
			cont++;
		}
	}

	ficha_diferente = false;
	columna_probar = columna + 1;

	while(columna_probar < COLUMNAS && !ficha_diferente)
	{
		if(tablero[fila][columna] != tablero[fila][columna_probar])
			ficha_diferente = true;
		else
			cont++;
			columna_probar++;
	}

	if(cont > 2)
		ok = true;

	return ok;
}

bool probarGruposColumnas(const tTablero tablero, int fila,int columna) //si se han formado grupo de fichas por columnas devuelve true, si no false;
{
	bool ok = false;
	int cont = 1;
	int fila_probar = fila - 1;
	bool ficha_diferente = false;

	while(fila_probar >= 0 && !ficha_diferente)
	{
		if(tablero[fila][columna] != tablero[fila_probar][columna])
			ficha_diferente = true;
		else
		{
			fila_probar--;
			cont++;
		}
	}

	ficha_diferente = false;
	fila_probar = fila + 1;

	while(fila_probar < FILAS && !ficha_diferente)
	{
		if(tablero[fila][columna] != tablero[fila_probar][columna])
			ficha_diferente = true;
		else
			cont++;
			fila_probar++;
	}

	if(cont > 2)
		ok = true;

	return ok;
}

void posicionDestino(tDireccion direccion, int &incrFila,int &incrCol)		// recibe un tMovimiento y  devuelve la fila y columna a la que se quiere mover la																					   ficha segun la direccion introducida
{		
	incrFila = 0;
	incrCol = 0;
	
	switch (direccion)
	{
		case arriba:
			incrFila = 1;
			incrCol = 0;
			break;
		case abajo:
			incrFila = -1;
			incrCol = 0;
			break;
		case derecha:
			incrCol = 1;
			incrFila = 0;
			break;
		case izquierda:
			incrCol =  -1;
			incrFila = 0;
			break;
	}
}

void guardarPartida(tJuego juego,bool &ok)		//guarda una partida(intentos,puntos y tablero) en un archivo de texto
{
	ofstream file;
	string nombreArchivo;

	cin.sync();
	cout << "Introduzca el nombre de archivo: "; 
	getline(cin,nombreArchivo);

	file.open(nombreArchivo.c_str());
	if(file.is_open())
	{
		file << juego.intentos << " " << juego.puntos << endl;

		for (int i = 0; i < FILAS; i++)
		{
			for (int j = 0; j < COLUMNAS; j++)
				file << juego.tablero[i][j] << " ";

			file << endl;
		}
		ok = true;
	}
	else
	{
		cout << "Error guardando partida en archivo..." << endl;
		ok = false;
	}
}

void cargarPartida(tJuego &juego,bool &ok)		// carga una partida(intentos,puntos y tablero) de un archivo de texto
{
	ifstream file;
	int x;
	string nombreArchivo;

	cin.sync();
	cout << "Introduzca el nombre de archivo: "; 
	getline(cin,nombreArchivo);

	file.open(nombreArchivo.c_str());
	if(file.is_open())
	{
		file >> juego.intentos >> juego.puntos;

		for (int i = 0; i < FILAS; i++)
		{
			for (int j = 0; j < COLUMNAS; j++)
			{
				file >> x;
				juego.tablero[i][j] = (tFicha)x;
			}
		}
		ok = true;
	}
	else
	{
		cout << "Error al cargar el archivo...." << endl;
		ok = false;
	}
}

int opcionMenu()		//muestra un menu por pantalla para que el usuario elija una opcion
{
	setColor(light_cyan);
	int opcion;

	cout << "--------------------Menu--------------------" << endl;
		 setColor(light_yellow);
	cout << "1 - Nueva partida" << endl
		 << "2 - Cargar partida de archivo" << endl
		 << "3 - Generar tablero en archivo" << endl
		 << "4 - Mostrar puntuaciones" << endl
		 << "0 - Salir" << endl;
		setColor(light_cyan);

	cout << "--------------------------------------------" << endl;
	do
	{
		setColor(white);
		cout << "Opcion: "; cin >> opcion;
	}
	while(opcion < 0 || opcion > 4);

	return opcion;
}

void guardarPuntuaciones(string nombre,int puntos)		//guarda nombre jugador y sus puntuaciones en un archivo de texto
{
	string tmpBuffer,bufferArchivo;
	fstream file;
	int posNombre,numJuegos,numPuntos;

	file.open(archivoPuntuaciones.c_str(), ios::in | ios::out);
	if(!file.is_open())
	{
		file.open(archivoPuntuaciones.c_str(),ios::out);

		if(file.is_open())
		{
			file << nombre << " 1 " << puntos;
			file.close();
		}
	}
	else
	{
		while(file >> tmpBuffer && tmpBuffer != nombre)
		{}
		
		if(tmpBuffer == nombre)
		{
			posNombre = (int)file.tellg();
			file >> numJuegos >> numPuntos;
			numJuegos++;
			numPuntos += puntos;
			
			tmpBuffer.erase();

			getline(file,tmpBuffer);
			while(!file.eof())
			{
				bufferArchivo += tmpBuffer + "\n";
				getline(file,tmpBuffer);
			}
			bufferArchivo += tmpBuffer;

			file.clear();
			file.seekp(posNombre);
			file << " " << numJuegos << " " << numPuntos << bufferArchivo;

			file.close();
		}
		else
		{
			file.clear();
			file.seekp(0,file.end);
			file << endl << nombre << " 1 " << puntos;
			file.close();
		}
	}
}

void mostrarPuntuaciones()		//lee y muestra por pantalla un archivo de puntuaciones
{
   ifstream inputFile;
   string nombre,juegos,puntos;
   inputFile.open(archivoPuntuaciones.c_str());
   if (!inputFile.is_open())
      cout << "Error! Archivo de puntuaciones no encontrado..." << endl;
   else 
   {
		cout << "Usuario          Juegos  Puntos" << endl;

		while(inputFile >> nombre >> juegos >> puntos)
			cout << nombre << setw(20 - nombre.size()) << juegos << setw(9) << puntos << endl;

		inputFile.close();
   }
}

void guardarTablero(const tTablero tableroguardar)		// guarda un tablero en un fichero de texto
{
	ofstream archivo;
	string nombrearchivo;

	cin.sync();
	cout << "Introduce nombre de archivo para guardar tablero: ";
	getline(cin, nombrearchivo);

	archivo.open(nombrearchivo.c_str());

	if(!archivo.is_open())
		cout << "Error guardando tablero...." << endl;
	else
	{
		for(int fila=FILAS-1; fila >= 0; fila--)
		{
			for(int columna=0; columna < COLUMNAS; columna++)
				archivo << tableroguardar[fila][columna] << " ";

			archivo << endl;
		}

		archivo.close();
	}
}

void cargarTablero(tTablero &tablero, bool &ok){	//carga un tablero de un fichero de texto
	ifstream archivodecarga;
	string nombrearchivo;
	int fichaarchivo;

	cin.sync();
	cout << "Introduce nombre de archivo a cargar:";
	getline(cin, nombrearchivo);

	archivodecarga.open(nombrearchivo.c_str());

	if(!archivodecarga.is_open())
	{
		cout << "Error no se ha podido cargar el archivo" << endl;
		ok = false;
	}
	else
	{
		for(int fila=FILAS-1; fila >= 0; fila--)
		{
			for(int columna=0; columna < COLUMNAS; columna++)
			{
			archivodecarga >> fichaarchivo;
			tablero[fila][columna] = tFicha(fichaarchivo);
			}
		}

		archivodecarga.close();
		ok = true;
	}
}