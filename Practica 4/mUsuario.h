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

	void inicializarUsuario(tUsuario &usuario,string nombre);
	bool cargarUsuario(tUsuario &usuario, ifstream &archivo);
	void guardarUsuario(ofstream &archivo,tUsuario usuario);

#endif //USUARIO_H