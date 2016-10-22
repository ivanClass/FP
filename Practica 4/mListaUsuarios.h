#ifndef LISTAUSUARIOS_H
	#define LISTAUSUARIOS_H
	
	#include <iostream>
	#include <fstream>
	#include "mUsuario.h"

	const int MAXUSUARIOS = 10;
	typedef tUsuario tUsuarios[MAXUSUARIOS];

	typedef struct
	{
		tUsuarios usuarios;
		int contador;
	} tListaUsuarios;

	bool cargarUsuarios(tListaUsuarios &listausuarios);
	void guardarUsuarios(tListaUsuarios listausuarios);
	int buscarUsuario(tListaUsuarios listausuarios,string idusuario);
#endif //LISTAUSUARIOS_H