#include "mCliente.h"

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
		posChat = buscarChat(cliente.chats,nuevosMensajes.mensajes[i].emisor);

		if(posChat != -1)
		{
			añadirMensaje(cliente.chats.chats[posChat].listamensajes,nuevosMensajes.mensajes[i]);
			moverAlFinal(cliente.chats,posChat);
		}
		else
		{
			tChat nuevoChat;
			inicializarChat(nuevoChat,nuevosMensajes.mensajes[i].emisor,cliente.idUsuario);
			añadirMensaje(nuevoChat.listamensajes,nuevosMensajes.mensajes[i]);
			anadirChat(cliente.chats,nuevoChat);
		}
	}
}

void mostrarInterfaz(tDatosCliente cliente)
{
	system("cls");
	dibujarLineaHorizontal();

	setColor(tColor::light_red);
	imprimirCentrado("CHATSAPP 1.0: Chats de " + cliente.idUsuario);

	for(int i = 0; i < cliente.chats.contador; i++)
	{
		dibujarLineaHorizontal();
		setColor(tColor::light_magenta);
		cout << i << ": ";
		setColor(tColor::light_blue);
		mostrarCabecera(cliente.chats.chats[i]);
	}

	dibujarLineaHorizontal();

	setColor(tColor::light_red);

	cout << setw(35) << left << "Entrar al chat N: c N <intro>" << setw(35) << right << "Crear nuevo chat: n <intro>" << endl
		 << setw(35) << left << "Eliminar el chat N: e N <intro>" << setw(35) << right << "Ordenar chats por nombre: o n <intro>" << endl
		 << setw(35) << left << "Ordenar chats por fechas: o f <intro>" << setw(35) << right << "Salir: s <intro>" << endl;

	dibujarLineaHorizontal();
}

void crearNuevoChat(tServidor &servidor,tDatosCliente &cliente)
{
	string nombreUsuario;
	int posUsuario;
	cout << "Introduzca el id de usuario con el que desea empezar el chat: ";
	cin >> nombreUsuario;

	posUsuario = buscarUsuario(servidor.usuarios,nombreUsuario);

	if(posUsuario != -1)
	{
		tChat nuevoChat;
		inicializarChat(nuevoChat,nombreUsuario,cliente.idUsuario);
		tMensaje nuevoMensaje = crearMensaje(cliente.idUsuario,nombreUsuario,"Nuevo chat iniciado por " + cliente.idUsuario);
		añadirMensaje(nuevoChat.listamensajes,nuevoMensaje);
		anadirChat(cliente.chats,nuevoChat);
		enviarMensaje(servidor,nuevoMensaje);
	}
	else
		cout << "Error usuario no encontrado...." << endl;
}

void ejecutarApp(tServidor &servidor, string idUsuario)
{
	tDatosCliente cliente;
	char accion;
	bool salir = false;
	int numChat;

	inicializarApp(cliente,idUsuario);
	if(cargarListaChats(cliente.chats,cliente.idUsuario))
	{
		obtenerNuevosMensajes(servidor,cliente);

		while(!salir)
		{
			mostrarInterfaz(cliente);
			cin >> accion;

			switch (accion)
			{
			case 'c':
				cin >> numChat;
				if(numChat >= 0 && numChat < cliente.chats.contador)
					gestionarChat(cliente.chats.chats[numChat],servidor);
				else
				{
					cout << "Error numero de chat no valido." << endl;
					system("pause");
				}
				break;
			case 'e':
				cin >> numChat;
				if(numChat >= 0 && numChat < cliente.chats.contador)
					eliminarChat(cliente.chats,numChat);
				else
				{
					cout << "Error numero de chat no valido." << endl;
					system("pause");
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
					system("pause");
				}

				break;
			case 's':
				guardarListaChats(cliente.chats,idUsuario);
				salir = true;
				break;
			default:
				cout << "Error opcion no valida." << endl;
				system("pause");
				break;
			}
		}
	}
}