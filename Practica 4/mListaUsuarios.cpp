#include "mListaUsuarios.h"

void ordenarPorNombre(tListaUsuarios &lista);

bool cargarUsuarios(tListaUsuarios &listausuarios){
	ifstream archivoCarga;
	tUsuario usuarioCarga;
	bool ok = true;

	listausuarios.contador = 0;

	archivoCarga.open("usuarios.txt");
	if(!archivoCarga.is_open())
		ok = false;
	else
	{
		ok = cargarUsuario(usuarioCarga,archivoCarga);
		while(usuarioCarga.idusuario != "XXX" && listausuarios.contador < MAXUSUARIOS && ok){
			listausuarios.usuarios[listausuarios.contador] = usuarioCarga;
			listausuarios.contador++;
			ok = cargarUsuario(usuarioCarga,archivoCarga);
		}
		if(usuarioCarga.idusuario == "XXX")
			ok = true;
		archivoCarga.close();
	}

	if(ok)
		ordenarPorNombre(listausuarios);
	return ok;
}

void guardarUsuarios(tListaUsuarios listausuarios){
	ofstream archivoguardado;
	tUsuario usuarioguardar;

	archivoguardado.open("usuarios.txt");
	if(archivoguardado.is_open())
	{
		for(int i = 0; i < listausuarios.contador; i++){
			usuarioguardar = listausuarios.usuarios[i];
			guardarUsuario(archivoguardado,usuarioguardar);
		}
		archivoguardado << "XXX" << endl;
		archivoguardado.close();
	}
}

int buscarUsuario(tListaUsuarios listausuarios,string idusuario){
	int ini=0,fin=listausuarios.contador-1,mitad;
	bool encontrado=false;

	while((ini <= fin) && !encontrado){
		mitad=(ini+fin)/2;
		if(idusuario == listausuarios.usuarios[mitad].idusuario)
			encontrado=true;
		else{
			if(idusuario < listausuarios.usuarios[mitad].idusuario)
				fin=mitad-1;
			else
				ini=mitad+1;
		}
	}
	if(encontrado==false)
		mitad=-1;
	
	return mitad;
}

void ordenarPorNombre(tListaUsuarios &lista){
	bool inter=true;
	int i=0;
	tUsuario usuarioTmp;

	while((i < lista.contador - 1) && inter){
		inter=false;
		for (int j = lista.contador - 1; j > i; j--)
		{
			if(lista.usuarios[j].idusuario < lista.usuarios[j-1].idusuario){
				usuarioTmp = lista.usuarios[j];
				lista.usuarios[j] = lista.usuarios[j-1];
				lista.usuarios[j-1] = usuarioTmp;
				inter=true;
			}
		}
		if(inter)
			i++;
	}
}