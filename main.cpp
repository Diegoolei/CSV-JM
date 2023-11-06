#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Lista/Lista.h"                                    // Para la lista de articulos, incluye stdlib.h
// #include "Lista/CircList.h"
#include <algorithm>                                        // Para contar la cantidad de delimitadores
using namespace std;

bool MinimoStock(string dato1, string dato2, string dato3, string dato4, string dato5, int stockmin)
{
  int valor;
  bool bandera;

  if (dato1 == "")
    dato1 = "0";
  if (dato2 == "")
    dato2 = "0";
  if (dato3 == "")
    dato3 = "0";
  if (dato4 == "")
    dato4 = "0";
  if (dato5 == "")
    dato5 = "0";

  valor = stoi(dato1) + stoi(dato2) + stoi(dato3) + stoi(dato4) + stoi(dato5);
  bandera = valor <= stockmin;
  
  return bandera;
}


int main()
{
    clock_t begin, end;
    ifstream archivo;
    int stockmin, cant_depositos, cant_columnas_csv;
    Lista<string> *datos_linea = new Lista<string>();       // Inicializo la lista que va a contener los datos de cada linea
    string linea, dato_auxiliar;
    double elapsed_secs;
    char delimitador = ';';                                 // Va a ser el separador de los diferentes datos
    int total_art_dif = 0, total_art = 0;

    cout << "Comenzando a medir Tiempo\n"
         << endl;

    begin = clock();

    printf("Cual va a ser el stock minimo: ");
    cin >> stockmin;

    archivo.open("Inventariado Fisico.csv", ios::in);       // Abrimos el archivo en modo lectura
    if (archivo.fail())                                     // Notificamos en caso de error
        cout << "Error";

    getline(archivo, linea);                                // Usamos la primera fila del CSV para saber cuantos depósitos hay
    cant_columnas_csv = count(linea.begin(), linea.end(), delimitador);
    cant_depositos = cant_columnas_csv - 2;                 // Se resta 2 porque son 3 columnas que no son depositos
    cout << "Hay " << cant_depositos << " depositos." << endl;

    
    while (getline(archivo, linea))
    {
        total_art_dif++;                                    // Cantidad de articulos diferentes (igual a cant lineas en CSV)
        stringstream stream(linea);
        for (int i = 0; i < cant_columnas_csv; i++)         // Bug conocido: No lee el último depósito, getline tiene comp. inesperado
        {
            getline(stream, dato_auxiliar, delimitador);    // Obtenemos el dato hasta el delimitador
            datos_linea->insertarUltimo(dato_auxiliar);     // Insertamos el dato en la lista
        }   
        total_art += datos_linea->get_total_art();          // Sumamos la cantidad de articulos de la linea
        datos_linea->vaciar();                              // Vaciamos la lista para la proxima linea

    }

    archivo.close(); // Cerramos el archivo

    cout << "Hay " << total_art_dif << " articulos diferentes." << endl;
    cout << "Hay " << total_art << " articulos en total." << endl;

    cout << "Los elementos con minimo de stock son : " << endl;

    end = clock();

    elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n"
         << endl;
    return 0;
}