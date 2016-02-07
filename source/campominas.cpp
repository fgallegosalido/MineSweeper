#include <cstdlib>
#include <fstream>
#include <cstring>
#include "tablero.h"
#include "campominas.h"
using namespace std;

struct CeldaPosicion{
	int filas, columnas;
	CeldaPosicion* siguiente;
};

int Uniforme(int minimo, int maximo){
	double aleatorio = rand()/(RAND_MAX+1.0);
	return minimo+(maximo-minimo+1)*aleatorio;
}

bool CampoMinas::FueraTablero(int f, int c)const{
	if (f<0 || f+1>Filas() || c<0 || c+1>Columnas()){
		return true;
	}
	else{
		return false;
	}
}

int CampoMinas::MinasAlrededor(int f, int c)const{
	int num_minas = 0;

	for (int i=f-1; i<=f+1; i++){
		for (int j=c-1; j<=c+1; j++){
			if (!(FueraTablero(i, j) || (f==i && c==j))){
				if (tablero.Elemento(i, j).bomba){
					num_minas++;
				}
			}
		}
	}
	return num_minas;
}

CampoMinas::CampoMinas(int f, int c, int minas)
	:tablero(f, c)
{
	explotado = false;
	salvado = false;
	int fil, col;
	while (minas>0){
		fil = Uniforme(0, f-1);
		col = Uniforme(0, c-1);
		if (!tablero.Elemento(fil, col).bomba){
			tablero.ModificarCasilla(fil, col, true, false, false);
			minas--;
		}
	}
}

int CampoMinas::Filas()const{
	return tablero.Filas();
}

int CampoMinas::Columnas()const{
	return tablero.Columnas();
}

bool CampoMinas::Explotado()const{
	return explotado;
}

bool CampoMinas::Salvado()const{
	return salvado;
}

bool CampoMinas::PartidaGanada()const{
	if (!Explotado()){
		for (int i=0; i<Filas(); i++){
			for (int j=0; j<Columnas(); j++){
				if (!tablero.Elemento(i, j).abierta && !tablero.Elemento(i, j).bomba){
					return false;
				}
			}
		}
		return true;
	}
	else{
		return false;
	}
}

bool CampoMinas::Marcar(int f, int c){
	if (tablero(f, c).abierta){
		return false;
	}
	else{
		tablero.ModificarCasilla(f, c, tablero(f, c).bomba, false, !tablero(f, c).marcada);
		return true;
	}
}

bool CampoMinas::Abrir(int f, int c){
	if (FueraTablero(f, c) || tablero.Elemento(f, c).abierta || tablero.Elemento(f, c).marcada){
		return false;
	}
	else{
		CeldaPosicion* aux=0;
		CeldaPosicion* pend=0;
		int fil, col;

		pend = new CeldaPosicion;
		pend->filas = f;
		pend->columnas = c;
		pend->siguiente = 0;

		while (pend!=0){
			aux = pend->siguiente;
			fil = pend->filas;
			col = pend->columnas;
			delete pend;
			pend = aux;

			if (!tablero.Elemento(fil, col).abierta){

				tablero.ModificarCasilla(fil, col, tablero.Elemento(fil, col).bomba, true, false);
				if (tablero.Elemento(fil, col).bomba){
					explotado = true;
				}

				if (MinasAlrededor(fil, col) == 0){
					for (int i=fil-1; i<=fil+1; i++){
						for (int j=col-1; j<=col+1; j++){
							if (!FueraTablero(i, j) && !tablero.Elemento(i, j).abierta && !tablero.Elemento(i, j).marcada && (fil!=i || col!=j)){
								pend = new CeldaPosicion;
								pend->siguiente = aux;
								pend->filas = i;
								pend->columnas = j;
								aux = pend;
							}
						}
					}
				}
			}
		}
		return true;
	}
}

void CampoMinas::PrettyPrint(ostream &os)const{
	os << "\n   ";
	for (int i=0; i<Columnas(); i++){
		if (i<10){
			os << " " << i << " ";
		}
		else{
			os << i << " ";
		}
	}
	os << "\n";
	os << "  _";
	for (int i=0; i<Columnas(); i++){
		os << "___";
	}
	os << "\n";
	for (int i=0; i<Filas(); i++){
		if (i<10){
			os << i << " |";
		}
		else{
			os << i << "|";
		}
		for (int j=0; j<Columnas(); j++){
			if (tablero.Elemento(i, j).abierta){
				os << " ";
				if (MinasAlrededor(i, j) == 0){
					os << " ";
				}
				else{
					os << MinasAlrededor(i, j);
				}
				os << "|";
			}
			else if (tablero.Elemento(i, j).marcada){
				os << " ?|";
			}
			else{
				os << " *|";
			}
		}
		os << "\n";
	}
	os << "  -";
	for (int i=0; i<Columnas(); i++){
		os << "---";
	}
	os << "\n" << endl;
}

void CampoMinas::TableroResuelto()const{
	cout << "\n   ";
	for (int i=0; i<Columnas(); i++){
		if (i<10){
			cout << " " << i << " ";
		}
		else{
			cout << i << " ";
		}
	}
	cout << "\n";
	cout << "  _";
	for (int i=0; i<Columnas(); i++){
		cout << "___";
	}
	cout << "\n";
	for (int i=0; i<Filas(); i++){
		if (i<10){
			cout << i << " |";
		}
		else{
			cout << i << "|";
		}
		for (int j=0; j<Columnas(); j++){
			if (!tablero.Elemento(i, j).bomba){
				cout << " ";
				if (MinasAlrededor(i, j) == 0){
					cout << " ";
				}
				else{
					cout << MinasAlrededor(i, j);
				}
				cout << "|";
			}
			else{
				cout << " X|";
			}
		}
		cout << "\n";
	}
	cout << "  -";
	for (int i=0; i<Columnas(); i++){
		cout << "---";
	}
	cout << "\n" << endl;
}

bool CampoMinas::Leer(const char* name){
	ifstream ifs(name);

	if (ifs){
		char cad[25];
		const char magic_cad[] = "#MP−BUSCAMINAS−V1";

		ifs.getline(cad, 25);

		if(strcmp(cad, magic_cad) == 0){
			ifs >> tablero;
			return true;
		}
	}
	return false;
}

bool CampoMinas::Escribir(const char* name){
	ofstream ofs(name);

	if (ofs){
		ofs << "#MP−BUSCAMINAS−V1\n";
		ofs << tablero;
	}
	ofs.close();
	if (ofs){
		salvado = true;
		return true;
	}
	else{
		return false;
	}
}
