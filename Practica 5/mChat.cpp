#include "mChat.h"

void inicializarChat(tChat &chat, string nombreChat, string duenoChat)
{
	chat.nombreChat = nombreChat;
	chat.duenoChat = duenoChat;

	inicializarListaMensajes(chat.listamensajes);
}

bool cargarChat(tChat &chat,ifstream &archivo, string idUsuario){
	
	string nombreChat;

	archivo >> nombreChat;
	inicializarChat(chat,nombreChat,idUsuario);

	cargarColaMensajes(archivo,chat.listamensajes);

	return !archivo.fail();
}

void guardarChat(ofstream &archivo,tChat &chat){

	archivo << chat.nombreChat << endl;

	guardarColaMensajes(archivo,chat.listamensajes);
}

void mostrarCabecera(const tChat &chat){
	tMensaje mensaje;
	ultimoMensaje(chat.listamensajes, mensaje);
	cout << chat.nombreChat << endl;;
	cout << setw(70) << right << mostrarMensaje(mensaje);
	dibujarLineaHorizontal();
}

void mostrarInterfazChat(const tChat &chat){
	system("cls");

	dibujarLineaHorizontal();
	setColor(tColor::light_red);
	imprimirCentrado("CHAT CON " + chat.nombreChat);
	dibujarLineaHorizontal();
	for(int i = 0; i < chat.listamensajes.contador; i++){
		if(devolverEmisorMensaje(chat.listamensajes.mensajes[i]) == chat.nombreChat){
			setColor(light_yellow);
			cout  << setw(79) << right << mostrarMensaje(chat.listamensajes.mensajes[i]) << endl;
		}
		else{
			setColor(light_cyan);
			cout << setw(79) << left << mostrarMensaje(chat.listamensajes.mensajes[i]) << endl;
		}
		dibujarLineaHorizontal();
	}
}



void gestionarChat(tChat &chat, tServidor &servidor){
	string mensaje;
	tMensaje mensajeNuevo;

	cin.sync();

	mostrarInterfazChat(chat);
	cout << "Escribe aqui ($salir$ para salir): ";
	getline(cin,mensaje);

	while(mensaje != "$salir$")
	{
		crearMensaje(chat.duenoChat,chat.nombreChat,mensaje,mensajeNuevo);
		anadirMensaje(chat.listamensajes,mensajeNuevo);
		enviarMensaje(servidor,mensajeNuevo);

		mostrarInterfazChat(chat);

		cout << "Escribe aqui ($salir$ para salir): ";
		getline(cin,mensaje);
	}
	
}

string devolverNombreChat(const tChat &chat){
	return chat.nombreChat;
}

void devolverColaChat(const tChat &chat, tListaMensajes &cola){
	cola = chat.listamensajes;
}