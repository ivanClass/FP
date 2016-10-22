#include "mListaChats.h"

void inicializarListaChats(tListaChats &lista)
{
	lista.contador = 0;
	lista.tamano = INIMAXCHATS;
	lista.chats = new tChat[lista.tamano];
}

bool cargarListaChats(tListaChats &lista,string idUsuario)
{
	ifstream archivo;
	tChat tmp;
	string nombreArchivo = idUsuario + "_chats.txt";
	bool ok = true;
	int taminicial;

	archivo.open(nombreArchivo);

	if(archivo.is_open())
	{
		archivo >> taminicial;
		if(taminicial >= INIMAXCHATS)
			redimensionarListaChats(lista,((taminicial/10)+1)*10); // redondeo a las decenas
		while(ok && (lista.contador < taminicial))
		{
			ok = cargarChat(tmp,archivo,idUsuario);
			lista.chats[lista.contador] = tmp;
			lista.contador++;
		}
		archivo.close();
	}

	return ok;
}

void guardarListaChats(const tListaChats &listachats, string idUsuario){
	ofstream archivo;
	string nombreArchivo = idUsuario + "_chats.txt";

	archivo.open(nombreArchivo);
	if(archivo.is_open())
	{
		archivo << listachats.contador << endl;
		for(int i = 0; i < listachats.contador; i++)
			guardarChat(archivo,listachats.chats[i]);

		archivo.close();
	}
}

int buscarChat(const tListaChats &listachats,string idchat){
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

	if((listachats.tamano-listachats.contador) > (listachats.tamano/2)) // redimensiona si queda mas de la mitad libre
		redimensionarListaChats(listachats,(listachats.tamano*2)/3);
}

void anadirChat(tListaChats &listachats, tChat chatinsertar)
{
	if(listachats.contador == listachats.tamano)
		redimensionarListaChats(listachats,(((listachats.tamano*3)/2) + 1));

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
			if(devolverNombreChat(listachats.chats[j]) < devolverNombreChat(listachats.chats[j-1])){
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
	tChat chattmp;
	tMensaje mens1,mens2;

	while((i < listachats.contador - 1) && inter){
		inter=false;
		for (int j = listachats.contador - 1; j > i; j--)
		{
			ultimoMensaje(listachats.chats[j].listamensajes, mens1);
			ultimoMensaje(listachats.chats[j - 1].listamensajes, mens2);

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

int devolverContadorChats(const tListaChats &chats){
	return chats.contador;
}

void redimensionarListaChats(tListaChats &chats, int nuevaDim){
	tChatPtr chattmp = new tChat[nuevaDim];

	for(int i = 0; i < chats.contador;i++){
		chattmp[i] = chats.chats[i];
	}

	delete[] chats.chats;

	chats.chats = chattmp;
	chats.tamano = nuevaDim;
}

void destruirListaChats(tListaChats &listachats){

	for(int i = 0; i < listachats.contador; i++){
		destruirListaMensajes(listachats.chats[i].listamensajes);
	}
	delete [] listachats.chats;
	listachats.contador = 0;
	listachats.tamano = 0;
}
