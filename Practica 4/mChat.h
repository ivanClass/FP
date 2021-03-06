#ifndef CHAT_H
	#define CHAT_H

	#include <iostream>
	#include <fstream>
	#include <iomanip>

	#include "mListaMensajes.h"
	#include "mServidor.h"
	#include "mGraficos.h"

	using namespace std;

	typedef struct 
	{
		string nombreChat;
		string duenoChat;
		tListaMensajes listamensajes;
	} tChat;

	void inicializarChat(tChat &chat, string nombreChat, string duenoChat);
	bool cargarChat(tChat &chat,ifstream &archivo, string idUsuario);
	void guardarChat(ofstream &archivo,tChat chat);
	void mostrarCabecera(tChat chat);
	void mostrarInterfazChat(tChat chat);
	void gestionarChat(tChat &chat, tServidor &servidor);


#endif //CHAT_H