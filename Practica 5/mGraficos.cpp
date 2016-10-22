#include "mGraficos.h"

void setColor(tColor color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

void dibujarLineaHorizontal()
{
	setColor(white);
	for(int i = 0; i < 80; i++){
		cout << LINEAHORIZONTAL;
	}
	cout << endl;
}

void imprimirCentrado(string str)
{
	cout << setw(40 + (str.size()/2)) << right<< str << endl;
}