#ifndef GRAFICOS_H
	#define GRAFICOS_H

	#include <iostream>
	#include <iomanip>
	#include <string>
	#include <Windows.h>

	using namespace std;

	const char LINEAHORIZONTAL = char(196);

	typedef enum tColor 
	{ // Screen colors
		black, // 0
		dark_blue, // 1
		dark_green, // 2
		dark_cyan, // 3
		dark_red, // 4
		dark_magenta, // 5
		dark_yellow, // 6
		light_gray, // 7
		dark_gray, // 8
		light_blue, // 9
		light_green, // 10
		light_cyan, // 11
		light_red, // 12
		light_magenta, // 13
		light_yellow, // 14
		white // 15
	};

	void setColor(tColor color);
	void dibujarLineaHorizontal();
	void imprimirCentrado(string str);

#endif // !mColor_h
