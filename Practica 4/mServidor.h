#ifndef SERVIDOR_H
	#define SERVIDOR_H

	#include "mListaUsuarios.h"

	typedef struct
	{
		tListaUsuarios usuarios;
	} tServidor;

	void enviarMensaje(tServidor &servidor, tMensaje mensaje);
	void obtenerNuevosMensajes(tServidor &servidor, string idUsuario,tListaMensajes &cola);
#endif 