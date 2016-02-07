#ifndef _CAMPOMINAS_H_
#define _CAMPOMINAS_H_

#include "tablero.h"
#include <iostream>
using namespace std;

int Uniforme(int minimo, int maximo);

class CampoMinas{
	private:
		Tablero tablero;
		bool explotado;
		bool salvado;
		int MinasAlrededor(int f, int c)const;
		bool FueraTablero(int f, int c)const;
	public:
		CampoMinas(int f, int c, int minas);
		int Filas()const;
		int Columnas()const;
		bool Explotado()const;
		bool Salvado()const;
		bool PartidaGanada()const;
		bool Marcar(int f, int c);
		bool Abrir(int f, int c);
		void PrettyPrint(ostream& os=cout)const;
		void TableroResuelto()const;
		bool Leer(const char* name);
		bool Escribir(const char* name);
};

#endif
