#include "mUsuario.h"

bool cargarUsuario(tUsuario &usuario, ifstream &archivo)
{
	string nombre_usuario;

	archivo >> nombre_usuario;
	inicializarUsuario(usuario,nombre_usuario);

	cargarColaMensajes(archivo,usuario.cola);

	return !archivo.fail();
}

void guardarUsuario(ofstream &archivo,const tUsuarioPtr &usuario)
{
	archivo << usuario->idusuario << endl;

	guardarColaMensajes(archivo,usuario->cola);
}

void inicializarUsuario(tUsuario &usuario,string nombre)
{
	usuario.idusuario = nombre;
	inicializarListaMensajes(usuario.cola);
}

string devolverNombreUsuario(const tUsuarioPtr &usuario){
	return usuario->idusuario;
}

void devolverColaUsuario(tUsuarioPtr &usuario,tListaMensajes &listamensajes){
	listamensajes = usuario->cola;
}

void anadirMensajes(tUsuarioPtr &usuario,const tListaMensajes &listamensajes){
	usuario->cola = listamensajes;
}

void inicializarColaUsuario(tUsuarioPtr &usuario){
	(usuario->cola).contador = 0;
}
