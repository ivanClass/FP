#ifndef MENSAJE_H
	#define MENSAJE_H

	#include <string>
	#include <iostream>
	#include <ctime>
	#include <sstream>
	#include <fstream>

	using namespace std;

	typedef time_t tFecha;

	typedef struct 
	{
		string emisor;
		string receptor;
		tFecha fecha;
		string texto;
	} tMensaje;

	tMensaje crearMensaje(string emisor,string receptor,string texto);
	string mostrarMensaje(tMensaje mensaje);
	string mostrarFecha(tFecha fecha);
	bool cargarMensaje(ifstream &archivo,tMensaje &mensaje);
	void guardarMensaje(ofstream &archivo,tMensaje &mensaje);

#endif //MENSAJE_H