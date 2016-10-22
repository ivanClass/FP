#ifndef MENSAJE_H
	#define MENSAJE_H
	#include <string>
	#include <fstream>
	using namespace std;

	typedef time_t tFecha;

	typedef struct 
	{
		string emisor;
		string receptor;
		tFecha fecha;
		string texto;
	} tMensaje;

	void crearMensaje(string emisor,string receptor, string texto,tMensaje &nuevoMensaje);
	string mostrarMensaje(tMensaje mensaje);
	bool cargarMensaje(ifstream &archivo,tMensaje &mensaje);
	void guardarMensaje(ofstream &archivo,tMensaje mensaje);
	string devolverEmisorMensaje(const tMensaje &mensaje);
	string devolverReceptorMensaje(const tMensaje &mensaje);

#endif //MENSAJE_H