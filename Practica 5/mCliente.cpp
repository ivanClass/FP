#include "mCliente.h"

const int CENTRAR_MENU = 35;

void menuAccionApp(tServidor &servidor,tDatosCliente &cliente,char accion,string idUsuario,bool &salir);

void inicializarApp(tDatosCliente &cliente, string idUsuario)
{
	cliente.idUsuario = idUsuario;
	inicializarListaChats(cliente.chats);
}

void obtenerNuevosMensajes(tServidor &servidor,tDatosCliente &cliente)
{
	tListaMensajes nuevosMensajes;
	int posChat;
	inicializarListaMensajes(nuevosMensajes);
	obtenerNuevosMensajes(servidor,cliente.idUsuario,nuevosMensajes);

	for(int i = 0; i < nuevosMensajes.contador; i++)
	{
		posChat = buscarChat(cliente.chats, devolverEmisorMensaje(nuevosMensajes.mensajes[i]));

		if(posChat != -1)
		{
			anadirMensaje(cliente.chats.chats[posChat].listamensajes,nuevosMensajes.mensajes[i]);
			moverAlFinal(cliente.chats,posChat);
		}
		else
		{
			tChat nuevoChat;
			inicializarChat(nuevoChat,devolverEmisorMensaje(nuevosMensajes.mensajes[i]),cliente.idUsuario);
			
			anadirMensaje(nuevoChat.listamensajes,nuevosMensajes.mensajes[i]);
			anadirChat(cliente.chats,nuevoChat);
		}
	}
}

void mostrarInterfaz(const tDatosCliente &cliente)
{
	system("cls");
	dibujarLineaHorizontal();

	setColor(tColor::light_red);
	imprimirCentrado("CHATSAPP 2.0: Chats de " + cliente.idUsuario);

	for(int i = 0; i < cliente.chats.contador; i++)
	{
		dibujarLineaHorizontal();
		setColor(tColor::light_yellow);
		cout << i << ": ";
		setColor(tColor::light_cyan);
		mostrarCabecera(cliente.chats.chats[i]);
	}

	dibujarLineaHorizontal();

	setColor(tColor::light_green);

	cout << setw(CENTRAR_MENU) << left << "Entrar al chat N: c N <intro>" << setw(CENTRAR_MENU) << right << "Crear nuevo chat: n <intro>" << endl
		 << setw(CENTRAR_MENU) << left << "Eliminar el chat N: e N <intro>" << setw(CENTRAR_MENU) << right << "Ordenar chats por nombre: o n <intro>" << endl
		 << setw(CENTRAR_MENU) << left << "Ordenar chats por fechas: o f <intro>" << setw(CENTRAR_MENU) << right << "Salir: s <intro>" << endl;

	dibujarLineaHorizontal();
}

void crearNuevoChat(tServidor &servidor,tDatosCliente &cliente)
{
	string nombreUsuario;
	int posUsuario;
	bool ok;
	cout << "Introduzca el id de usuario con el que desea empezar el chat: ";
	cin >> nombreUsuario;

	posUsuario = buscarUsuario(servidor.usuarios,nombreUsuario,ok);

	if(ok)
	{
		if(buscarChat(cliente.chats,nombreUsuario) != -1){
			cout << "El chat ya existe..." << endl;
			Sleep(500);
		}
		else{
			tChat nuevoChat;
			inicializarChat(nuevoChat,nombreUsuario,cliente.idUsuario);

			tMensaje nuevoMensaje;
			crearMensaje(cliente.idUsuario,nombreUsuario,"Nuevo chat iniciado por " + cliente.idUsuario,nuevoMensaje);
			anadirMensaje(nuevoChat.listamensajes,nuevoMensaje);
			anadirChat(cliente.chats,nuevoChat);
			enviarMensaje(servidor,nuevoMensaje);
		}
	}
	else{
		cout << "Error usuario no encontrado...." << endl;
		Sleep(500);
	}
}

void ejecutarApp(tServidor &servidor, string idUsuario)
{
	tDatosCliente cliente;
	char accion;
	bool salir = false;

	inicializarApp(cliente,idUsuario);
	if(cargarListaChats(cliente.chats,cliente.idUsuario))
	{
		obtenerNuevosMensajes(servidor,cliente);

		while(!salir)
		{
			mostrarInterfaz(cliente);
			cin >> accion;
			menuAccionApp(servidor,cliente,accion,idUsuario,salir);
		}

	}
}

void menuAccionApp(tServidor &servidor,tDatosCliente &cliente,char accion,string idUsuario,bool &salir){
	int numChat;
	tListaMensajes cola;
	switch (accion)
	{
		case 'c':
			cin >> numChat;
			if(numChat >= 0 && numChat < devolverContadorChats(cliente.chats)){
				devolverColaChat(cliente.chats.chats[numChat],cola);
				int contanterior = cola.contador;

				gestionarChat(cliente.chats.chats[numChat],servidor);

				devolverColaChat(cliente.chats.chats[numChat],cola);
				int contnuevo = cola.contador;

				if(contanterior != contnuevo)  //si no ha enviado mensajes el chat se queda en la misma posicion
					moverAlFinal(cliente.chats,numChat);
			}
			else
			{
				cout << "Error chat no existente..." << endl;
				Sleep(500);
			}
			break;
		case 'e':
			cin >> numChat;
			if(numChat >= 0 && numChat < devolverContadorChats(cliente.chats))
				eliminarChat(cliente.chats,numChat);
			else
			{
				cout << "Error chat no existente..." << endl;
				Sleep(500);
			}

			break;
		case 'n':
			crearNuevoChat(servidor,cliente);
			break;
		case 'o':
			cin >> accion;
			if(accion == 'f')
				ordenarPorFecha(cliente.chats);
			else if (accion == 'n')
				ordenarPorNombre(cliente.chats);
			else
			{
				cout << "Error opcion no valida (debe ser 'o f' o 'o n')." << endl;
				Sleep(1000);
			}

			break;
		case 's':
			guardarListaChats(cliente.chats,idUsuario);
			destruirListaChats(cliente.chats);
			salir = true;
			break;
		default:
			cout << "Error opcion no valida." << endl;
			Sleep(500);
			break;
	}
}
