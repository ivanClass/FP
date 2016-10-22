/***********
************/

#include "mServidor.h"
#include "mCliente.h"
#include "mGraficos.h"
#include <iostream>

int main()
{
	tServidor servidor;
	string idUsuario;
	bool salir = false;
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
				if(buscarUsuario(servidor.usuarios,idUsuario) != -1)
					ejecutarApp(servidor,idUsuario);
			}
			else
				salir = true;
		}

		guardarUsuarios(servidor.usuarios);
	}
	else
	{
		cout << "Error no se pudo cargar el archivo de usuarios...." << endl;
		system("pause");
	}
	return 0;
}
