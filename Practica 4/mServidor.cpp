#include "mServidor.h"

void enviarMensaje(tServidor &servidor, tMensaje mensaje)
{
	int posUsuario = buscarUsuario(servidor.usuarios,mensaje.receptor);

	if (posUsuario != -1)
	{
		añadirMensaje(servidor.usuarios.usuarios[posUsuario].cola,mensaje);
	}
	else
		cout << "Error usuario " << mensaje.receptor << " no encontrado" << endl;
}

void obtenerNuevosMensajes(tServidor &servidor, string idUsuario,tListaMensajes &cola)
{
	int posUsuario = buscarUsuario(servidor.usuarios,idUsuario);

	if (posUsuario != -1)
	{
		cola = servidor.usuarios.usuarios[posUsuario].cola;
		servidor.usuarios.usuarios[posUsuario].cola.contador = 0;
	}
	else
		cout << "Error usuario " << idUsuario << " no encontrado" << endl;
}