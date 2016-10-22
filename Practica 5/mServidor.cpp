#include "mServidor.h"

void enviarMensaje(tServidor &servidor, const tMensaje &mensaje)
{
	bool ok;
	int posUsuario = buscarUsuario(servidor.usuarios,devolverReceptorMensaje(mensaje),ok);
	tListaMensajes listamensajes;

	if (ok)
	{
		devolverColaUsuario((servidor.usuarios.usuarios[posUsuario]),listamensajes);
		anadirMensaje(listamensajes,mensaje);
		anadirMensajes(servidor.usuarios.usuarios[posUsuario],listamensajes);
	}
	else
		cout << "Error usuario " << mensaje.receptor << " no encontrado" << endl;

}

void obtenerNuevosMensajes(tServidor &servidor, string idUsuario,tListaMensajes &cola)
{
	bool ok;
	int posUsuario = buscarUsuario(servidor.usuarios,idUsuario,ok);

	if (ok)
	{
		devolverColaUsuario(servidor.usuarios.usuarios[posUsuario],cola);
		inicializarColaUsuario(servidor.usuarios.usuarios[posUsuario]);

	}
	else
		cout << "Error usuario " << idUsuario << " no encontrado" << endl;
}
