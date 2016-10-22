#ifndef LISTAMENSAJES_H
	#define LISTAMENSAJES_H
	#include <fstream>
	#include <iostream>
	#include <Windows.h>

	#include "mMensaje.h"

	const int INIMAXMENSAJES = 10;
	typedef tMensaje *tMensajesPtr;

	typedef struct 
	{
		tMensajesPtr mensajes;
		int contador;
		int tamano;
	} tListaMensajes;

	void inicializarListaMensajes(tListaMensajes &listamensajes);
	void guardarColaMensajes(ofstream &archivo,const tListaMensajes &cola);
	bool cargarColaMensajes(ifstream &archivo,tListaMensajes &cola);
	void ultimoMensaje(const tListaMensajes &cola, tMensaje &mensaje);
	void anadirMensaje(tListaMensajes &cola,tMensaje mensaje);
	void redimensionarListaMensajes(tListaMensajes &cola,int nuevaDimension);
	void destruirListaMensajes(tListaMensajes &cola);


#endif // LISTAMENSAJES_H
