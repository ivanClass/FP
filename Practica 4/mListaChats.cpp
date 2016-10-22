#include "mListaChats.h"

void inicializarListaChats(tListaChats &lista)
{
	lista.contador = 0;
}

bool cargarListaChats(tListaChats &lista,string idUsuario)
{
	ifstream archivo;
	tChat tmp;
	string nombreArchivo = idUsuario + "_chats.txt";
	bool ok = true;

	archivo.open(nombreArchivo);

	if(archivo.is_open())
	{
		ok = cargarChat(tmp,archivo,idUsuario);

		while(tmp.nombreChat != "XXX" && lista.contador < MAXCHATS && ok)
		{
			lista.chats[lista.contador] = tmp;
			lista.contador++;
			ok = cargarChat(tmp,archivo,idUsuario);
		}
		if(tmp.nombreChat == "XXX")
			ok = true;
		archivo.close();
	}

	return ok;
}

void guardarListaChats(tListaChats listachats, string idUsuario){
	ofstream archivo;
	string nombreArchivo = idUsuario + "_chats.txt";

	archivo.open(nombreArchivo);
	if(archivo.is_open())
	{
		for(int i = 0; i < listachats.contador; i++)
			guardarChat(archivo,listachats.chats[i]);

		archivo << "XXX" << endl;
		archivo.close();
	}
}

int buscarChat(tListaChats listachats,string idchat){
	bool encontrado = false;
	int i = 0;
	
	while(!encontrado && i < listachats.contador){
		if(listachats.chats[i].nombreChat == idchat)
			encontrado = true;
		else
			i++;
	}

	if(!encontrado)
		i = -1;

	return i;
}

void eliminarChat(tListaChats &listachats,int poschat){

	if(poschat < 0 || poschat >= listachats.contador)
		return;

	for(int i = poschat; i < listachats.contador - 1; i++)
		listachats.chats[i] = listachats.chats[i+1];
	
	listachats.contador--;
}

void anadirChat(tListaChats &listachats, tChat chatinsertar)
{
	if (listachats.contador == MAXCHATS)
		return;

	listachats.chats[listachats.contador] = chatinsertar;
	listachats.contador++;
}

void moverAlFinal(tListaChats &listachats,int poschat)
{
	tChat tmp_chat;
	tmp_chat = listachats.chats[poschat];

	eliminarChat(listachats,poschat);
	anadirChat(listachats,tmp_chat);
}

void ordenarPorNombre(tListaChats &listachats){
	bool inter=true;
	int i=0;
	tChat chattmp;

	while((i < listachats.contador - 1) && inter){
		inter=false;
		for (int j = listachats.contador - 1; j > i; j--)
		{
			if(listachats.chats[j].nombreChat < listachats.chats[j-1].nombreChat){
				chattmp = listachats.chats[j];
				listachats.chats[j] = listachats.chats[j-1];
				listachats.chats[j-1] = chattmp;
				inter=true;
			}
		}
		if(inter)
			i++;
	}
}

void ordenarPorFecha(tListaChats &listachats){
	bool inter=true;
	int i=0;
	tListaMensajes listamensajestmp;
	tChat chattmp;
	tMensaje mens1,mens2;

	while((i < listachats.contador - 1) && inter){
		inter=false;
		for (int j = listachats.contador - 1; j > i; j--)
		{
			mens1 = UltimoMensaje(listachats.chats[j].listamensajes);
			mens2 = UltimoMensaje(listachats.chats[j - 1].listamensajes);

			if(mens1.fecha > mens2.fecha){
				chattmp = listachats.chats[j];
				listachats.chats[j] = listachats.chats[j-1];
				listachats.chats[j-1] = chattmp;
				inter=true;
			}
		}
		if(inter)
			i++;
	}
}