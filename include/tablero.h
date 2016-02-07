#ifndef _TABLERO_H_
#define _TABLERO_H_

#include <iostream>
using namespace std;

struct Casilla{
	bool bomba, abierta, marcada;
};

class Tablero{
	private:
		Casilla* datos;
		int filas, columnas;
	public:
		Tablero(int f, int c);
		Tablero(const Tablero& tab);
		~Tablero();
		Tablero& operator=(const Tablero &tab);
		Casilla operator()(int f, int c)const;
		Casilla& operator()(int f, int c);
		int Filas()const;
		int Columnas()const;
		Casilla Elemento(int f, int c)const;
		void ModificarCasilla(int f, int c, bool bomba, bool abierta, bool marcada);
};

istream& operator>>(istream& is, Casilla& casilla);
ostream& operator<<(ostream& os, const Casilla& casilla);
istream& operator>>(istream& is, Tablero& tab);
ostream& operator<<(ostream& os, const Tablero& tab);

#endif
