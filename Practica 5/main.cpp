
/*******************************
	PRACTICA 5 - CHATSAPP 2.0
	Iván Aguilera Calle
	Noel Álgora Igual
	LAB01-P101
********************************/
/*
Habéis puesto todos los include en el .h deberíais de poner el .h únicamente aquellos que se necesiten en el .h y en el .cpp el resto. Por ejemplo, en mensaje.h incluís <sstream> cuando esta librería no se usa para nada en el .h…
-ListaMensajes:	
cargarColaMensajes: No deberíais de actualizar el contador hasta no saber realmente cuantos mensajes se han cargado, si vienen mas mensajes de los que caben o hay algún error el contador de la cola será incorrecto tal y como lo tenéis…	
-Chat:
cargarChat: Antes de inicializar el chat deberíais de comprobar si se ha llegado al centinela.	
cargarColaMensajes debería de devolver un booleano para indicar si todo ha ido bien.	
mostrarInterfazChat: Os cargáis varias veces la encapsulación, por ejemplo en: chat.listamensajes.mensajes[i].emisor
gestionarChat: Repetís código, deberíais de haber hecho un do_while o inicializar mensaje a vacio.	<- chorrada
-ListaChats: 
cargarListaChats: Debería de llamar al subprograma anadirChat y no repetir código.	
eliminarChat: No se deben usar return vacios para forzar la  salida, debería de devolver un booleano que indique si todo ha ido bien.
anadirChat: No se deben usar return vacios para forzar la  salida, debería de devolver un booleano que indique si todo ha ido bien.
ordenarPorNombre: Os cargáis la encapsulación en listachats.chats[j].nombreChat. --> ARREGLADO
ordenarPorFecha: Os cargáis la encapsulación en listachats.chats[j].listamensajes.-->ARREGLADO
-Usuario:
cargarUsuario: antes de crear el usuario deberíais de comprobar que no es el centinela.
-Servidor:
enviarMensaje:
anadirMensaje debería de devolver un booleano que indicase si se ha añadido el mensaje correctamente.	
Os cargáis la encapsulación en: servidor.usuarios.usuarios[posUsuario].cola.	-->ARREGLADO
obtenerNuevosMensajes: Violáis la encapsulación varias veces. -->ARREGLADO
-Cliente:
menuAccionApp:
Violáis la encapsulación en muchas ocasiones.	 -->ARREGLADO
Subprograma demasiado largo, deberíais de haberlo dividido en subprogramas.
*/


#include "mServidor.h"
#include "mCliente.h"
#include "mGraficos.h"
#include <iostream>

int main()
{
	tServidor servidor;
	string idUsuario;
	bool salir = false;
	bool ok;

	if(cargarUsuarios(servidor.usuarios))
	{
		while(!salir)
		{
			setColor(tColor::white);
			system("cls");
			cout << "Introduzca el usuario (0 para salir): ";
			cin >> idUsuario;

			if(idUsuario != "0")
			{
				buscarUsuario(servidor.usuarios,idUsuario,ok);
				if(ok){
					ejecutarApp(servidor,idUsuario);
				}
				else{
					cout << "Usuario no existente..." << endl;
					Sleep(500);
				}
			}
			else
				salir = true;
		}

		guardarUsuarios(servidor.usuarios);
		destruirListaUsuarios(servidor.usuarios);
	}
	else
	{
		cout << "Error no se pudo cargar el archivo de usuarios...." << endl;
		system("pause");
	}
	return 0;
}
