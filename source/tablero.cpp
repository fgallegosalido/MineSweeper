#include "tablero.h"

using namespace std;

Tablero::Tablero(int f, int c){

	datos = new Casilla[f*c];
	filas = f;
	columnas = c;

	for (int i=0; i<f*c; i++){
		datos [i].bomba = false;
		datos [i].abierta = false;
		datos [i].marcada = false;
	}
}

Tablero::~Tablero(){
	delete[] datos;
	datos = 0;
}

Tablero::Tablero(const Tablero& tab){
	int num_casillas = (tab.filas)*(tab.columnas);
	datos = new Casilla [num_casillas];
	filas = tab.filas;
	columnas = tab.columnas;

	for (int i=0; i<num_casillas; i++){
		datos[i] = tab.datos[i];
	}
}

Tablero& Tablero::operator=(const Tablero& tab){
	if (this!=&tab){

		int num_casillas = (tab.filas)*(tab.columnas);
		delete[] this->datos;
		datos = new Casilla [num_casillas];
		filas = tab.filas;
		columnas = tab.columnas;

		for (int i=0; i<num_casillas; i++){
			datos[i] = tab.datos[i];
		}
	}
	return *this;
}

Casilla Tablero::operator()(int f, int c)const{
	return datos[f*columnas + c];
}

Casilla& Tablero::operator()(int f, int c){
	return datos[f*columnas + c];
}

int Tablero::Filas()const{
	return filas;
}

int Tablero::Columnas()const{
	return columnas;
}

Casilla Tablero::Elemento(int f, int c)const{
	return datos [f*columnas + c];
}

void Tablero::ModificarCasilla(int f, int c, bool bomba, bool abierta, bool marcada){
	datos [f*columnas + c].bomba = bomba;
	datos [f*columnas + c].abierta = abierta;
	datos [f*columnas + c].marcada = marcada;
}

istream& operator>>(istream& is, Casilla& casilla){
	char bomba, abierta, marcada;
	is >> bomba;
	is >> abierta;
	is >> marcada;

	if (is){
		casilla.bomba = (bomba=='0');
		casilla.abierta = (abierta=='0');
		casilla.marcada = (marcada=='0');
	}

	return is;
}

ostream& operator<<(ostream& os, const Casilla& casilla){

	os << ((casilla.bomba) ? '0' : '1') << " ";
	os << ((casilla.abierta) ? '0' : '1') << " ";
	os << ((casilla.marcada) ? '0' : '1') << " ";
	return os;
}

istream& operator>>(istream& is, Tablero& tab){
	int filas, columnas;
	is >> filas >> columnas;

	if (filas>0 && columnas>0 && is){
		Tablero tablero(filas, columnas);
		for (int i=0; i<filas; i++){
			for (int j=0; j<columnas; j++){
				is >> tablero(i, j);
			}
		}
		if (is){
		tab = tablero;
		}
 	}
	return is;
}

ostream& operator<<(ostream& os, const Tablero& tab){
	os << tab.Filas() << " " << tab.Columnas() << "\n";
	for (int i=0; i<tab.Filas(); i++){
		for (int j=0; j<tab.Columnas(); j++){
			os << tab(i, j);
		}
	}
	os << endl;

	return os;
}
