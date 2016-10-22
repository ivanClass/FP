#ifndef CLIENTE_H
	#define CLIENTE_H
	#include <string>

	#include "mListaChats.h"
	#include "mChat.h"
	#include "mGraficos.h"
	#include "mServidor.h"
	using namespace std;

	

	typedef struct
	{
		string idUsuario;
		tListaChats chats;
	} tDatosCliente;

	void inicializarApp(tDatosCliente &cliente, string idUsuario);
	void obtenerNuevosMensajes(tServidor &servidor,tDatosCliente &cliente);
	void mostrarInterfaz(const tDatosCliente &cliente);
	void crearNuevoChat(tServidor &servidor,tDatosCliente &cliente);
	void ejecutarApp(tServidor &servidor, string idUsuario);	
#endif