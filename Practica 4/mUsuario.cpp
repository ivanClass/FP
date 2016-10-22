#include "mUsuario.h"

bool cargarUsuario(tUsuario &usuario, ifstream &archivo)
{
	string nombre_usuario;

	archivo >> nombre_usuario;
	inicializarUsuario(usuario,nombre_usuario);

	cargarColaMensajes(archivo,usuario.cola);

	return !archivo.fail();
}

void guardarUsuario(ofstream &archivo, tUsuario usuario)
{
	archivo << usuario.idusuario << endl;

	guardarColaMensajes(archivo,usuario.cola);
}

void inicializarUsuario(tUsuario &usuario,string nombre)
{
	usuario.idusuario = nombre;
	inicializarListaMensajes(usuario.cola);
}
