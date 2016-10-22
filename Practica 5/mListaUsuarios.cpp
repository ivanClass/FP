#include "mListaUsuarios.h"

void insertarOrdenado(tListaUsuarios &lista, const tUsuario &usuario);

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
			insertarOrdenado(listausuarios,usuarioCarga);
			ok = cargarUsuario(usuarioCarga,archivoCarga);
		}
		if(usuarioCarga.idusuario == "XXX")
			ok = true;
		archivoCarga.close();
	}

	return ok;
}

void guardarUsuarios(const tListaUsuarios &listausuarios){
	ofstream archivoguardado;
	tUsuarioPtr usuarioguardar;

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


int buscarUsuario(const tListaUsuarios &listausuarios,string idusuario, bool &encontrado){
	int ini=0,fin=listausuarios.contador-1,mitad=0;
	encontrado=false;

	while((ini <= fin) && !encontrado){
		mitad=(ini+fin)/2;
		if(idusuario == devolverNombreUsuario(listausuarios.usuarios[mitad]))
			encontrado=true;
		else{
			if(idusuario < devolverNombreUsuario(listausuarios.usuarios[mitad]))
				fin=mitad-1;
			else
				ini=mitad+1;
		}
	}
	if(!encontrado)
		return ini;
	else
		return mitad;
}

void insertarOrdenado(tListaUsuarios &lista, const tUsuario &usuario){
	bool encontrado = false;
	if(lista.contador != MAXUSUARIOS){
		int i = buscarUsuario(lista,usuario.idusuario,encontrado);

		for(int j = lista.contador; j > i; j--){
			lista.usuarios[j] = lista.usuarios[j - 1];
		}

		lista.usuarios[i] = new tUsuario(usuario);
		lista.contador++;
	}
}

void destruirListaUsuarios(tListaUsuarios &lista){

	for(int i = 0; i < lista.contador;i++){
		destruirListaMensajes(lista.usuarios[i]->cola);
		delete lista.usuarios[i];
	}
	lista.contador = 0;
}


