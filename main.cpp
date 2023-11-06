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
    int min_stock, cant_depositos, cant_columnas_csv, stock_articulo, deposito_min_stock, deposito_stock, max_stock;
    Lista<string> *datos_linea = new Lista<string>();       // Inicializo la lista que va a contener los datos de cada linea
    string linea, dato_auxiliar, stock_deposito_minimo, articulo_stock, articulo_deposito_stock;
    double elapsed_secs;
    char delimitador = ';';                                 // Va a ser el separador de los diferentes datos
    int total_art_dif = 0, total_art = 0;

    cout << "Comenzando a medir Tiempo\n"
         << endl;

    begin = clock();

    printf("Cual va a ser el stock minimo: ");
    cin >> min_stock;

    printf("Cual va a ser el deposito con stock minimo: ");
    cin >> deposito_min_stock;

    printf("Nombre del artículo a comprobar stock:");
    cin >> articulo_stock;

    printf("Nombre del artículo a comprobar stock en base a deposito:");
    cin >> articulo_deposito_stock;

    printf("Cual va a ser el deposito a revisar el stock del artículo:");
    cin >> deposito_stock;

    printf("Cual va a ser el stock maximo:");
    cin >> max_stock;

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
        {                                                   // Al corregir bug, cambiar < de linea 70 por <=
            getline(stream, dato_auxiliar, delimitador);    // Obtenemos el dato hasta el delimitador
            datos_linea->insertarUltimo(dato_auxiliar);     // Insertamos el dato en la lista
        }
        stock_articulo = datos_linea->get_total_art();
        total_art += stock_articulo;                        // Sumamos la cantidad de articulos de la linea

        cout << "El articulo " << datos_linea->getDato(2) << " tiene " << stock_articulo << " en total." << endl;

        if (stock_articulo < min_stock)
        {
          cout << "El articulo " << datos_linea->getDato(2) << " tiene minimo de stock. (" << stock_articulo << ")" << endl;
        }

        stock_deposito_minimo = datos_linea->getDato(deposito_min_stock+2); // Bug conocido: Si el deposito no tiene stock, hay error al convertir de string a int
        if ( stoi(stock_deposito_minimo) < min_stock)
        {
          cout << "El articulo " << datos_linea->getDato(2) << " tiene minimo de stock en el deposito " << deposito_min_stock << "(" << stock_articulo << ")" << endl;
        }
        
        if (articulo_stock == datos_linea->getDato(2)){
            cout << "El articulo " << datos_linea->getDato(2) << " tiene stock de " << stock_articulo << endl;
        }

        if (articulo_stock == datos_linea->getDato(2)){
            cout << "El articulo " << datos_linea->getDato(2) << " tiene stock de " << datos_linea->getDato(deposito_stock+2) << " en el depósito " << deposito_stock << endl;
        }

        if (stock_articulo > max_stock)
        {
          cout << "El articulo " << datos_linea->getDato(2) << " tiene maximo de stock. (" << stock_articulo << ")" << endl;
        }

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