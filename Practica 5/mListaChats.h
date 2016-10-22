#ifndef LISTACHATS_H
	#define LISTACHATS_H
	
	#include <iostream>
	#include <fstream>
	#include "mChat.h"

	using namespace std;

	const int INIMAXCHATS = 10;
	typedef tChat *tChatPtr;

	typedef struct
	{
		tChatPtr chats;
		int contador;
		int tamano;
	} tListaChats;

	void inicializarListaChats(tListaChats &lista);
	bool cargarListaChats(tListaChats &lista,string idUsuario);
	void guardarListaChats(const tListaChats &listachats, string idusuario);
	int buscarChat(const tListaChats &listachats,string idchat); //busqueda lineal
	void eliminarChat(tListaChats &listachats,int poschat);
	void anadirChat(tListaChats &listachats, tChat chatinsertar);
	void moverAlFinal(tListaChats &listachats,int poschat);
	void ordenarPorNombre(tListaChats &listachats);
	void ordenarPorFecha(tListaChats &listachats);
	int devolverContadorChats(const tListaChats &chats);
	string devolverNombreChat(const tChat &chat);
	void redimensionarListaChats(tListaChats &chats, int nuevaDim);
	void destruirListaChats(tListaChats &listachats);

#endif //LISTACHATS_H
