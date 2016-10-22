#ifndef LISTAMENSAJES_H
	#define LISTAMENSAJES_H
	#include <fstream>
	#include <iostream>

	#include "mMensaje.h"

	const int MAXMENSAJES = 20;
	typedef tMensaje tMensajes[MAXMENSAJES];

	typedef struct 
	{
		tMensajes mensajes;
		int contador;
	} tListaMensajes;

	void inicializarListaMensajes(tListaMensajes &listamensajes);
	void guardarColaMensajes(ofstream &archivo,tListaMensajes cola);
	bool cargarColaMensajes(ifstream &archivo,tListaMensajes &cola);
	tMensaje UltimoMensaje(tListaMensajes cola);
	void añadirMensaje(tListaMensajes &cola,tMensaje mensaje);

#endif // LISTAMENSAJES_H
