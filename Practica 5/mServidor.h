#ifndef SERVIDOR_H
	#define SERVIDOR_H

	#include "mListaUsuarios.h"
	#include "mListaMensajes.h"
	#include "mMensaje.h"
	typedef struct
	{
		tListaUsuarios usuarios;
	} tServidor;

	void enviarMensaje(tServidor &servidor, const tMensaje &mensaje);
	void obtenerNuevosMensajes(tServidor &servidor, string idUsuario,tListaMensajes &cola);
#endif 