/*
Practica 1 Version 4 - (12/12/2013)  *
                                     *
Fundamentos de la Programacion       *
Facultad de Informatica              *
Universidad Complutense de Madrid    *
                                     *
Autores:                             *
  Noel Algora Igual                  *
  Ivan Aguilera Calle                *
*/
#include <iostream> 
#include <fstream>
#include <string>
#include <cstdlib> 
#include <ctime>

using namespace std;

const int LONGITUD = 4;
const int INTENTOS = 3; 
const int INTERVALO = 3; 

int codeBreaker(int longitud,int intervalo,int intentos);
void codeBreakerAuto(int longitud,int intervalo,int intentos);
int claveAleatoria(int longitud,int intervalo);
int invertir(int n);
bool codigoValido(int codigo,int longitud,int intervalo);
int numeroBips(int codigo, int clave);
int pedirIntentos();
int pedirLongitud();
int pedirIntervalo();
int menu();
bool mostrar(string nombArch);
string bipsBops(int coincidencias,int longitud);
int claveAleatoriaAuto(int codigo,int longitud,int coincidencias,int intervalo);

int main(){
	ifstream ifile;
	ofstream ofile;
	bool salir = false;
	int maxIntentos = INTENTOS;
	int longitud = LONGITUD;
	int intervalo = INTERVALO;
	int intentos = 0;

	srand(time(NULL));

	//Carga configuracion de archivo
	ifile.open("configCB.txt");

	if(ifile.is_open())
		ifile >> maxIntentos >> longitud >> intervalo;
	else
		cout << "Error: Archivo de opciones no encontrado, cargando configuracion por defecto." << endl;

	ifile.close();

	while(!salir)
	{
		switch (menu()) // MENU
		{
			case 0: //salir
				salir = true;
				break;

			case 1: //jugar
				intentos = codeBreaker(longitud,intervalo,maxIntentos);
				if(intentos > maxIntentos)
					cout << "Has utilizado " << intentos -1 << " intentos" << endl;
				else if(intentos > 0)
					cout << "Has utilizado " << intentos << " intentos" << endl;
				else
					cout << "Partida abandonada" << endl;
				break;

			case 2: //intentos
				maxIntentos = pedirIntentos();
				cout << "Numero de intentos modificado." << endl;
				break;

			case 3: //longitud
				longitud = pedirLongitud();
				cout << "Longitud de los codigos modificada." << endl;
				break;

			case 4: //intervalo
				intervalo = pedirIntervalo();
				cout << "Intervalo de digitos modificado." << endl;
				break;
			
			case 5: //acerca de codebreaker
				mostrar("versionCB.txt");
				break;

			case 6: //rompedor automatico
				codeBreakerAuto(longitud,intervalo,maxIntentos);
				break;
		}
	}
	//Guarda configuracion en archivo
	ofile.open("configCB.txt");

	if(ofile.is_open())
		ofile << maxIntentos << endl << longitud << endl <<  intervalo << endl;
	else
		cout << "Error: no se pudo escribir en el archivo de opciones.";
	return 0;
}

/******************************************
-codeBreaker
Lleva a cabo el desarrollo del juego, se le introducen como argumentos la longitud,
intervalo e intentos que tendra el juego y devuelve el numero e intentos si acierta,
el numero de itnentos mas uno si se pasa de intentos y 0 si abandona el juego.
*******************************************/
int codeBreaker(int longitud,int intervalo,int intentos)
{
	int clave = claveAleatoria(longitud,intervalo);
	int k = 0;
	int coincidencias = 0;
	int codigo = 1;

	while(k < intentos && codigo != 0 && coincidencias != longitud)
	{
		cout << "Introduce un codigo (0 para abandonar): "; cin >> codigo;
		k++;

		if(codigoValido(codigo,longitud,intervalo))
		{
			coincidencias = numeroBips(codigo,clave);
			cout << bipsBops(coincidencias,longitud);
		}
		else if(codigo != 0)
			cout << "El codigo excede la longitud o contiene digitos no validos" << endl;
	}

	if(codigo == 0)
		return 0;
	else if(coincidencias == longitud)
		return k;
	else
		return k + 1;
}

/******************************************
-codeBreakerAuto
Lleva a cabo el rompedor automatico, se le introducen como parametros la longitud,
intervalo e intentos que tendra el juego y intenta descifrar el codigo, teniendo la salida
del juego en el archivo de texto.
*******************************************/
void codeBreakerAuto(int longitud,int intervalo,int intentos)
{
	int clave = claveAleatoria(longitud,intervalo);
	int codigo = claveAleatoria(longitud,intervalo);
	ofstream file;
	string fname;
	int k = 1;
	int coincidencias = 0;

	cout << "Introduzca el nombre de archivo: "; cin >> fname;
	file.open(fname);
	if(!file.is_open())
	{
		cout << "Error no se pudo abrir el archivo" << endl;
		cout << "Proceso finalizado" << endl;
		return;
	}

	while(k <= intentos && coincidencias != longitud)
	{
		file << "Introduce un codigo (0 para abandonar): " << codigo << endl;
		coincidencias = numeroBips(codigo,clave);

		file << bipsBops(coincidencias,longitud);

		if(coincidencias != longitud)
		{
			codigo = claveAleatoriaAuto(codigo,longitud,coincidencias,intervalo);
		}
		k++;
	}

	file << "Has utilizado " << k - 1 << " intentos.";
	file.close();
	cout << "Proceso finalizado" << endl;
	return;
}

/******************************************
-claveAleatoria
Devuelve una clave aleatoria de longitud digitos y con digitos dentro del
intervalo 1 - intervalo
*******************************************/
int claveAleatoria(int longitud,int intervalo)
{
	int clave = 0;
	for (int i = 0; i < longitud; i++)
	{
		clave = clave * 10 + (rand() % intervalo + 1);
	}
	return clave;
}

/******************************************
-invertir
Devuelve el codigo n introduce invertido 123 -> 321
*******************************************/
int invertir(int n)
{
	int invertido = 0;
	while(n > 0)
	{
		invertido = invertido * 10 + n % 10;
		n /= 10;
	}
	return invertido;
}

/******************************************
-codigoValido
Comprueba si codigo tiene la longitud y sus digitos estan
el el intervalo. Devuelve true si se cumple y false si no.
*******************************************/
bool codigoValido(int codigo,int longitud,int intervalo)
{
	int digitos = 0;

	while(codigo > 0 && codigo%10 <= intervalo)
	{
		codigo /= 10;
		digitos++;
	}

	return (digitos == longitud);
}

/******************************************
-numeroBips
Devuelve el numero de coincidencias que hay seguidas entre los
dos codigos codigo y clave 
numeroBips(124,123) = 2
*******************************************/
int numeroBips(int codigo, int clave)
{
	int coincidencias = 0;
	codigo = invertir(codigo); 
	clave = invertir(clave);
	while((codigo % 10 == clave % 10) && (codigo > 0) && (clave > 0))
	{
		coincidencias++;
		codigo /= 10;
		clave /= 10;
	}

	return coincidencias;
}

/******************************************
-pedirIntentos
Pide al usuario que introduzca los intentos deseados,
comprueba que estan en el rango correcto y devuelve el numero introducido.
*******************************************/
int pedirIntentos()
{
	int intentos;
	cout << "Introduzca el numero de intentos: "; cin >> intentos;
	while(intentos < 1)
	{
		cout << "Error numero de intentos no valido\nIntroduzca el numero de intentos: "; cin >> intentos;
	}
	return intentos;
}

/******************************************
-pedirLongitud
Pide al usuario que introduzca la longitud deseada,
comprueba que esta en el rango correcto y devuelve el numero introducido.
*******************************************/
int pedirLongitud()
{
	int longitud;
	cout << "Introduzca la longitud del codigo: "; cin >> longitud;
	while(longitud < 1)
	{
		cout << "Error longitud no valida\nIntroduzca la longitud del codigo: "; cin >> longitud;
	}
	return longitud;
}

/******************************************
-pedirIntervalo
Pide al usuario que introduzca el intervalo deseado,
comprueba que esta en el rango correcto y devuelve el numero introducido.
*******************************************/
int pedirIntervalo()
{
	int intervalo;
	cout << "Introduzca el intervalo de digitos(2-9): "; cin >> intervalo;

	while(intervalo < 2 || intervalo > 9)
	{
		cout << "Error intervalo no valido\nIntroduzca el intervalo de digitos(2-9): "; cin >> intervalo;
	}

	return intervalo;
}

/******************************************
-menu
Muestra el menu y devuelve la opcion introducida por el usuario
*******************************************/
int menu()
{
	int opcion = 0;
	cout << "--------------------------------------" << endl
		 << "1 - Jugar" << endl
		 << "2 - Cambiar el maximo de intentos" << endl
		 << "3 - Cambiar la longitud de los codigos" << endl
		 << "4 - Cambiar el intervalo de digitos" << endl
		 << "5 - Acerca de CodeBreaker" << endl
		 << "6 - Rompedor automatico" << endl
		 << "0 - Salir" << endl
		 << "--------------------------------------" << endl
		 << "Opcion: ";	cin >> opcion;
	while(opcion < 0 || opcion > 6)
	{
		cout << "Error, opcion no valida." << endl << "Opcion: ";	cin >> opcion;
	}
	cout << "--------------------------------------" << endl;
	return opcion;
}

/******************************************
-mostrar
Muestra por pantalla el archivo con nombre nombArch, devuelve true si
consigue completar la operacion y false si falla.
*******************************************/
bool mostrar(string nombArch)
{
	ifstream file;
	char c = 0;

	file.open(nombArch.c_str());

	if(file.is_open())
	{
		file.get(c);

		while(!file.eof())
		{
			cout << c;
			file.get(c);
		}

		file.close();
		return true;
	}
	else
	{
		cout << "Error: Archivo no encontrado." << endl;
		return false;
	}
}

/******************************************
-bipsBops
Devuelve una cadena con los bips y bops resultantes de las coincidencias y
la longitud del codigo
*******************************************/
string bipsBops(int coincidencias,int longitud)
{
	string tmp;
	for(int i = 0; i < coincidencias;i++)
		tmp += " bip";
	if(coincidencias == longitud)
		tmp += " -- OK!\n";
	else
		tmp += " bop -- Acceso denegado!\n";
	return tmp;
}

/******************************************
-claveAleatoriaAuto
Devuelve una clave con el digito que no coincide cambiado y manteniendo el resto
*******************************************/
int claveAleatoriaAuto(int codigo,int longitud,int coincidencias,int intervalo)
{
	int codigo_temp = 0;
	codigo = invertir(codigo);

	for(int i = 0; i < longitud;i++)
	{
		codigo_temp = codigo_temp * 10;
		if (i == coincidencias)
		{
			int tmp = (codigo % 10) + 1;
			
			if(tmp > intervalo) tmp -= intervalo;

			codigo_temp += tmp;
			codigo /=10;
		}
		else
		{
			codigo_temp += codigo%10;
			codigo /= 10;
		}
	}
	return codigo_temp;
}