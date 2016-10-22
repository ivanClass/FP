#include "mListaMensajes.h"

void guardarColaMensajes(ofstream &archivo,const tListaMensajes &cola)
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
		if(i == cola.tamano)
			redimensionarListaMensajes(cola,(((cola.tamano*3)/2) + 1));

		no_error = cargarMensaje(archivo,cola.mensajes[i]);
		i++;
	}

	return no_error;
}

void inicializarListaMensajes(tListaMensajes &cola)
{
	cola.contador = 0;
	cola.tamano = INIMAXMENSAJES;
	cola.mensajes = new tMensaje[INIMAXMENSAJES];
}

void ultimoMensaje(const tListaMensajes &cola, tMensaje &mensaje){
	mensaje = cola.mensajes[cola.contador - 1];
}

void anadirMensaje(tListaMensajes &cola,tMensaje mensaje)
{
		if(cola.contador == cola.tamano)
			redimensionarListaMensajes(cola,(((cola.tamano*3)/2) + 1));

		cola.mensajes[cola.contador] = mensaje;
		cola.contador++;
}

void redimensionarListaMensajes(tListaMensajes &cola,int nuevaDimension){
	tMensajesPtr mensajes = new tMensaje[nuevaDimension];
	
	for(int i = 0; i < cola.tamano;i++){
		mensajes[i] = cola.mensajes[i];
	}

	delete[] cola.mensajes;

	cola.mensajes = mensajes;
	cola.tamano = nuevaDimension;
}
void destruirListaMensajes(tListaMensajes &cola){

	delete [] cola.mensajes;
	cola.contador = 0;
	cola.tamano = 0;
}