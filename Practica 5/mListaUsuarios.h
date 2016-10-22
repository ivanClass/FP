#ifndef LISTAUSUARIOS_H
	#define LISTAUSUARIOS_H
	
	#include <iostream>
	#include <fstream>
	#include "mUsuario.h"

	const int MAXUSUARIOS = 50;
	typedef tUsuarioPtr tUsuarios[MAXUSUARIOS];

	typedef struct
	{
		tUsuarios usuarios;
		int contador;
	} tListaUsuarios;

	bool cargarUsuarios(tListaUsuarios &listausuarios);
	void guardarUsuarios(const tListaUsuarios &listausuarios);
	int buscarUsuario(const tListaUsuarios &listausuarios,string idusuario, bool &encontrado);
	void destruirListaUsuarios(tListaUsuarios &lista);

#endif //LISTAUSUARIOS_H