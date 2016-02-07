#include "campominas.h"
#include "tablero.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>
using namespace std;

const int TAMANIO = 100;
enum TipoAccion {abrir, marcar, salvar, error};

struct Accion{
  TipoAccion tipo_accion;
  char parametros[TAMANIO];
};


//Codifica la cadena introducida por el usuario en la acción a realizar.
Accion Lectura(char* cadena){
  Accion accion;
  char* cad_aux;
  cad_aux = new char[8];
  bool terminador = false;
  const char abrir[] = "abrir";
  const char marcar[] = "marcar";
  const char salvar[] = "salvar";

  for (int i=0; !terminador && i<7; i++){
    if (cadena[i] != 32 && strlen(cadena) != strlen(cad_aux)){
      cad_aux [i] = tolower(cadena[i]);
    }
    else{
      terminador = true;
      cad_aux[i] = '\0';
    }
  }

  if (strlen(cadena) != strlen(cad_aux)){
    if (strcmp(cad_aux, abrir) == 0 || (strlen(cad_aux) == 1 && cad_aux[0] == 'a')){
      accion.tipo_accion = TipoAccion::abrir;
    }
    else if (strcmp(cad_aux, marcar) == 0 || (strlen(cad_aux) == 1 && cad_aux[0] == 'm')){
      accion.tipo_accion = TipoAccion::marcar;
    }
    else if (strcmp(cad_aux, salvar) == 0 || (strlen(cad_aux) && cad_aux[0] == 's')){
      accion.tipo_accion = TipoAccion::salvar;
    }
    else{
      accion.tipo_accion = TipoAccion::error;
    }

    bool siguiente_caracter = false;
    int posicion = 0;

    for (unsigned int i=strlen(cad_aux)+1; i<strlen(cadena); i++){
      if (cadena[i] != 32){
        accion.parametros[posicion] = cadena[i];
        posicion++;
        siguiente_caracter = true;
      }
      else{
        if (siguiente_caracter){
          accion.parametros[posicion] = cadena[i];
          posicion++;
          siguiente_caracter = false;
        }
      }
    }
    accion.parametros[posicion] = '\0';
  }
  else{
    accion.tipo_accion = TipoAccion::error;
  }
  delete[] cad_aux;
  return accion;
}


//Codifica la acción a realizar, de manera que se ejecuten las instrucciones.
bool RealizarAccion (const Accion& accion, CampoMinas& campo){
  if (accion.tipo_accion != TipoAccion::error){
    int num_parametros = 1;

    for (unsigned int i=0; i<strlen(accion.parametros); i++){
      if (accion.parametros[i] == ' '){
        num_parametros++;
      }
    }

    if (num_parametros == 2){
      char cad_fila [10], cad_columna [10];
      int fila, columna, usados = 1;
      for (int i=0; accion.parametros[i] != ' '; i++){
        cad_fila[i] = accion.parametros[i];
        usados++;
      }
      for (unsigned int i=usados; i<strlen(accion.parametros); i++){
        cad_columna[i - usados] = accion.parametros[i];
      }
      fila = atoi(cad_fila);
      columna = atoi(cad_columna);

      if (fila<campo.Filas() && fila>=0 && columna<campo.Columnas() && columna>=0){
        if(accion.tipo_accion == TipoAccion::abrir){
          campo.Abrir(fila, columna);
        }
        else if (accion.tipo_accion == TipoAccion::marcar){
          campo.Marcar(fila, columna);
        }
        else{
          cerr << "Acción incorrecta.\n";
          return false;
        }
      }
      else{
        cerr << "Parámetros incorrectos.\n";
        return false;
      }
    }
    else if (num_parametros == 1){
      if (accion.tipo_accion == TipoAccion::salvar){
        campo.Escribir(accion.parametros);
      }
      else{
        cerr << "Acción incorrecta.\n";
        return false;
      }
    }
    else{
      cerr << "Número de parámetros incorrecto.\n";
      return false;
    }
    return true;
  }
  else{
    cerr << "Acción incorrecta.\n";
    return false;
  }
}

int main(int argc, char* argv[]){
  srand(time(0));
  CampoMinas campo_de_juego(1, 1, 1);

  //Comprobación de argumentos.
  if (argc == 4){
    int filas = atoi(argv[1]);
    int columnas = atoi(argv[2]);
    int minas = atoi(argv[3]);

    if (filas>4 && columnas>4 && minas<(filas*columnas)/2 && minas>=5){
      CampoMinas campo_aux(filas, columnas, minas);
      campo_de_juego = campo_aux;
    }
    else{
      cerr << "Error: Parámetros incorrectos. Uso: " << argv[0] << " filas(mayor que 4) columnas(mayor que 4) minas(mayor que 5 y menor que filas*columnas/2)\n";
      return 1;
    }
  }
  else if (argc == 2){
    bool existe;
    existe = campo_de_juego.Leer(argv[1]);

    if (existe){
      cout << "Archivo leído con éxito.\n";
    }
    else{
      cerr << "Error: No existe el archivo indicado.\n";
      return 1;
    }
  }
  else{
    cerr << "Error: Número de argumentos incorrecto. Uso:\n";
    cerr << " -Si se pasan tres argumentos, estos serán filas, columnas y minas (en ese orden).\n";
    cerr << " -Si se pasa un argumento, este será el nombre del archivo con la partida guardada.\n";
    cerr << " -En cualquier otro caso, se imprimirá este mensaje de ayuda y el programa terminará.\n";
    return 1;
  }
  char accion[TAMANIO];
  Accion accion_a_realizar;

  //Bucle principal para poder jugar.
  do{
    campo_de_juego.PrettyPrint();
    cout << "Dime acción (abrir(a), marcar(m) o salvar(s)) y posición (fila y columna): ";

    cin.getline(accion, TAMANIO, '\n');
    accion_a_realizar = Lectura(accion);

    if (RealizarAccion(accion_a_realizar, campo_de_juego)){
      cout << "Acción correcta.\n";
    }
    else{
      cerr << "Acción incorrecta, vuelva a introducirla.\n";
    }

  }while(!campo_de_juego.PartidaGanada() && !campo_de_juego.Explotado() && !campo_de_juego.Salvado());

  if (accion_a_realizar.tipo_accion == TipoAccion::salvar){
    cout << "Partida guardada con éxito.\n";
  }
  else{
    campo_de_juego.TableroResuelto();
    if (campo_de_juego.PartidaGanada()){
      cout << "¡Has ganado la partida!\n" << endl;
    }
    else{
      cout << "Lo siento, las minas te han podido.\n" << endl;
    }
  }
}
