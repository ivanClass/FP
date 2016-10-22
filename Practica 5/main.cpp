
/*******************************
	PRACTICA 5 - CHATSAPP 2.0
	Iv�n Aguilera Calle
	Noel �lgora Igual
	LAB01-P101
********************************/
/*
Hab�is puesto todos los include en el .h deber�ais de poner el .h �nicamente aquellos que se necesiten en el .h y en el .cpp el resto. Por ejemplo, en mensaje.h inclu�s <sstream> cuando esta librer�a no se usa para nada en el .h�
-ListaMensajes:	
cargarColaMensajes: No deber�ais de actualizar el contador hasta no saber realmente cuantos mensajes se han cargado, si vienen mas mensajes de los que caben o hay alg�n error el contador de la cola ser� incorrecto tal y como lo ten�is�	
-Chat:
cargarChat: Antes de inicializar el chat deber�ais de comprobar si se ha llegado al centinela.	
cargarColaMensajes deber�a de devolver un booleano para indicar si todo ha ido bien.	
mostrarInterfazChat: Os carg�is varias veces la encapsulaci�n, por ejemplo en: chat.listamensajes.mensajes[i].emisor
gestionarChat: Repet�s c�digo, deber�ais de haber hecho un do_while o inicializar mensaje a vacio.	<- chorrada
-ListaChats: 
cargarListaChats: Deber�a de llamar al subprograma anadirChat y no repetir c�digo.	
eliminarChat: No se deben usar return vacios para forzar la  salida, deber�a de devolver un booleano que indique si todo ha ido bien.
anadirChat: No se deben usar return vacios para forzar la  salida, deber�a de devolver un booleano que indique si todo ha ido bien.
ordenarPorNombre: Os carg�is la encapsulaci�n en listachats.chats[j].nombreChat. --> ARREGLADO
ordenarPorFecha: Os carg�is la encapsulaci�n en listachats.chats[j].listamensajes.-->ARREGLADO
-Usuario:
cargarUsuario: antes de crear el usuario deber�ais de comprobar que no es el centinela.
-Servidor:
enviarMensaje:
anadirMensaje deber�a de devolver un booleano que indicase si se ha a�adido el mensaje correctamente.	
Os carg�is la encapsulaci�n en: servidor.usuarios.usuarios[posUsuario].cola.	-->ARREGLADO
obtenerNuevosMensajes: Viol�is la encapsulaci�n varias veces. -->ARREGLADO
-Cliente:
menuAccionApp:
Viol�is la encapsulaci�n en muchas ocasiones.	 -->ARREGLADO
Subprograma demasiado largo, deber�ais de haberlo dividido en subprogramas.
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
