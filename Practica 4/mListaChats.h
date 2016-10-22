#ifndef LISTACHATS_H
	#define LISTACHATS_H
	
	#include <iostream>
	#include <fstream>
	#include "mChat.h"

	using namespace std;

	const int MAXCHATS = 10;
	typedef tChat tChats[MAXCHATS];

	typedef struct
	{
		tChats chats;
		int contador;
	} tListaChats;

	//inicializar
	void inicializarListaChats(tListaChats &lista);
	bool cargarListaChats(tListaChats &lista,string idUsuario);
	void guardarListaChats(tListaChats listachats, string idusuario);
	int buscarChat(tListaChats listachats,string idchat); //busqueda lineal
	void eliminarChat(tListaChats &listachats,int poschat);
	void anadirChat(tListaChats &listachats, tChat chatinsertar);
	void moverAlFinal(tListaChats &listachats,int poschat);
	void ordenarPorNombre(tListaChats &listachats);
	void ordenarPorFecha(tListaChats &listachats);
#endif //LISTACHATS_H
