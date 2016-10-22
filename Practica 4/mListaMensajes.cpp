#include "mListaMensajes.h"

void guardarColaMensajes(ofstream &archivo,tListaMensajes cola)
{
	archivo << cola.contador << endl;

	for(int i=0; i < cola.contador; i++){
		guardarMensaje(archivo,cola.mensajes[i]);
	}
}

bool cargarColaMensajes(ifstream &archivo,tListaMensajes &cola)
{
	int i = 0;
	bool no_error = true;

	archivo >> cola.contador;

	while(i < cola.contador && no_error)
	{
		no_error = cargarMensaje(archivo,cola.mensajes[i]);
		i++;
	}

	return no_error;
}

void inicializarListaMensajes(tListaMensajes &cola)
{
	cola.contador = 0;
}

tMensaje UltimoMensaje(tListaMensajes cola){
	return cola.mensajes[cola.contador - 1];
}

void añadirMensaje(tListaMensajes &cola,tMensaje mensaje)
{
	if (cola.contador < MAXMENSAJES)
	{
		cola.mensajes[cola.contador] = mensaje;
		cola.contador++;
	}
}
