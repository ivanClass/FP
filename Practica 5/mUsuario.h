#ifndef USUARIO_H
	#define USUARIO_H

	#include <fstream>
	#include <iostream>

	#include "mListaMensajes.h"

	using namespace std;

	typedef struct 
	{
		string idusuario;
		tListaMensajes cola;
	} tUsuario;

	typedef tUsuario *tUsuarioPtr;

	void inicializarUsuario(tUsuario &usuario,string nombre);
	bool cargarUsuario(tUsuario &usuario, ifstream &archivo);
	void guardarUsuario(ofstream &archivo,const tUsuarioPtr &usuario);
	string devolverNombreUsuario(const tUsuarioPtr &usuario);
	void devolverColaUsuario(tUsuarioPtr &usuario,tListaMensajes &listamensajes);
	void anadirMensajes(tUsuarioPtr &usuario,const tListaMensajes &listamensajes);
	void inicializarColaUsuario(tUsuarioPtr &usuario);

#endif //USUARIO_H