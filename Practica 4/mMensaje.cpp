#include "mMensaje.h"

tMensaje crearMensaje(string emisor,string receptor, string texto){
	tMensaje nuevoMensaje;

	nuevoMensaje.emisor = emisor;
	nuevoMensaje.receptor = receptor;
	nuevoMensaje.texto = texto;
	nuevoMensaje.fecha = time(0);

	return nuevoMensaje;
}

string mostrarMensaje(tMensaje mensaje){
	stringstream resultado;
	
	resultado << mensaje.emisor << " (";
	resultado << mostrarFecha(mensaje.fecha) << "): ";
	resultado << mensaje.texto;
	resultado << endl;

	return resultado.str();
}

string mostrarFecha(tFecha fecha)
{ 
	stringstream resultado; 
	tm ltt;

	localtime_s(&ltt,&fecha); 

	resultado<<1900 + ltt.tm_year<<"/"<<1 + ltt.tm_mon<<"/"<<ltt.tm_mday; 
	resultado<<", "<<ltt.tm_hour<<":"<<ltt.tm_min<<":"<<ltt.tm_sec; 
	return resultado.str(); 
}

bool cargarMensaje(ifstream &archivo,tMensaje &mensaje){
	archivo >> mensaje.emisor;
	archivo >> mensaje.fecha;
	getline(archivo,mensaje.texto);

	return !archivo.fail();
}

void guardarMensaje(ofstream &archivo,tMensaje &mensaje){

	archivo << mensaje.emisor << " ";
	archivo << mensaje.fecha << " ";
	archivo << mensaje.texto << endl;
}
