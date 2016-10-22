#include "mChat.h"

void inicializarChat(tChat &chat, string nombreChat, string duenoChat)
{
	chat.nombreChat = nombreChat;
	chat.duenoChat = duenoChat;

	inicializarListaMensajes(chat.listamensajes);
}

bool cargarChat(tChat &chat,ifstream &archivo, string idUsuario){ //revisar
	
	string nombreChat;

	archivo >> nombreChat;
	inicializarChat(chat,nombreChat,idUsuario);

	cargarColaMensajes(archivo,chat.listamensajes);

	return !archivo.fail();
}

void guardarChat(ofstream &archivo,tChat chat){

	archivo << chat.nombreChat << endl;

	guardarColaMensajes(archivo,chat.listamensajes);
}

void mostrarCabecera(tChat chat){
	cout << chat.nombreChat << endl;;
	cout << setw(70) << right << mostrarMensaje(UltimoMensaje(chat.listamensajes));
	dibujarLineaHorizontal();
}

void mostrarInterfazChat(tChat chat){
	system("cls");

	dibujarLineaHorizontal();
	setColor(tColor::light_red);
	imprimirCentrado("CHAT CON " + chat.nombreChat);
	dibujarLineaHorizontal();
	for(int i = 0; i < chat.listamensajes.contador; i++){
		if(chat.listamensajes.mensajes[i].emisor == chat.nombreChat){
			setColor(light_yellow);
			cout  << setw(79) << right << mostrarMensaje(chat.listamensajes.mensajes[i]) << endl;
		}
		else{
			setColor(light_blue);
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
		mensajeNuevo = crearMensaje(chat.duenoChat,chat.nombreChat,mensaje);
		añadirMensaje(chat.listamensajes,mensajeNuevo);
		enviarMensaje(servidor,mensajeNuevo);

		mostrarInterfazChat(chat);

		cout << "Escribe aqui ($salir$ para salir): ";
		getline(cin,mensaje);
	}
}