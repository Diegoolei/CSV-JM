#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Lista/Lista.h" // Para la lista de articulos, incluye stdlib.h
// #include "Lista/CircList.h"
#include <algorithm> // Para contar la cantidad de delimitadores
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
    int cantArticulos, stockmin, cant_depositos;
    Lista<string> grupo, barras, articulo, Dep1, Dep2, Dep3, Dep4, Dep5, aux, artmins;
    string linea, Grupo, CodigoBarras, Articulo, Deposito1, Deposito2, Deposito3, Deposito4, Deposito5;
    stringstream stream(linea);
    double elapsed_secs;
    char delimitador = ';'; // Va a ser el separador de los diferentes datos
    int sumaProductos = 0, total_art_dif = 0;

    cout << "Comenzando a medir Tiempo\n"
         << endl;

    begin = clock();

    printf("Cual va a ser el stock minimo: ");
    cin >> stockmin;

    archivo.open("Inventariado Fisico.csv", ios::in); // Abrimos el archivo en modo lectura
    if (archivo.fail())                               // Notificamos en caso de error
        cout << "Error";

    getline(archivo, linea); // Usamos la primera fila del CSV para saber cuantos depósitos hay
    cant_depositos = count(linea.begin(), linea.end(), delimitador) - 3; // Se resta 3 porque son 3 columnas que no son depositos

    while (getline(archivo, linea))
    {
        total_art_dif++; // Cantidad de articulos diferentes (igual a cant lineas en CSV)
        
        getline(stream, Grupo, delimitador);
        getline(stream, CodigoBarras, delimitador);
        getline(stream, Articulo, delimitador);
        getline(stream, Deposito1, delimitador);
        getline(stream, Deposito2, delimitador);
        getline(stream, Deposito3, delimitador);
        getline(stream, Deposito4, delimitador);
        getline(stream, Deposito5, delimitador);

        // funcion para minimo de stock
        if (MinimoStock(Deposito1, Deposito2, Deposito3, Deposito4, Deposito5, stockmin))
            artmins.insertarUltimo(Articulo);

        grupo.insertarUltimo(Grupo);
        barras.insertarUltimo(CodigoBarras);
        articulo.insertarUltimo(Articulo);
        Dep1.insertarUltimo(Deposito1);
        Dep2.insertarUltimo(Deposito2);
        Dep3.insertarUltimo(Deposito3);
        Dep4.insertarUltimo(Deposito4);
        Dep5.insertarUltimo(Deposito5);
    }
    cout << "Hay " << total_art_dif << " articulos diferentes." << endl;

    // Cantidad total de art�culos
    sumaProductos += Dep1.sumarDeposito() + Dep2.sumarDeposito() + Dep3.sumarDeposito();
    sumaProductos += Dep4.sumarDeposito() + Dep5.sumarDeposito();
    cout << "Hay " << sumaProductos << " articulos en total." << endl;

    cout << "Los elementos con minimo de stock son : " << endl;
    artmins.print();

    end = clock();

    elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n"
         << endl;
    return 0;
}