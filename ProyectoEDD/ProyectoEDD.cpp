#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
//La libreria de abajo nos sirve para poder crear los arreglos din�micos (tiene new y delete)
#include<stdlib.h>

using namespace std;

class Nodo {
private:
    string dato;
    Nodo* siguiente;

public:
    string getDato() {
        return dato;
    }

    void setDato(string d) {
        dato = d;
    }

    Nodo* getSiguiente() {
        return siguiente;
    }

    void setSiguiente(Nodo* siguiente) {
        this->siguiente = siguiente;
    }
};

class Lista {
private:
    Nodo* inicio;

public:
    Lista();

    Lista(const Lista& li);

    ~Lista();

    bool esVacia();

    int getTamanio();

    void insertar(int pos, string dato);

    void insertarPrimero(string dato);

    void insertarUltimo(string dato);

    void remover(int pos);

    string getDato(int pos);

    void reemplazar(int pos, string dato);

    void vaciar();

    int sumarDeposito();

    bool MinimoStock(string dato1,string dato2,string dato3, string dato4, string dato5, int stockmin);

    void print();
};

//Constructor
Lista::Lista() { inicio = nullptr; }

//Constructor por copia de la clase Lista
Lista::Lista(const Lista& li) { inicio = li.inicio; }

//Destructor de la clase Lista, se encarga de liberar la memoria de todos los nodos utilizados en la lista
Lista::~Lista() { vaciar(); }

//Metodo para saber si la lista esta vacia 
bool Lista::esVacia() { return inicio == nullptr; }

//Metodo para obtener la cantidad de nodos de la lista 
int Lista::getTamanio() {
    Nodo* aux = inicio;
    int size = 0;

    while (aux != nullptr) {
        aux = aux->getSiguiente();
        size++;
    }

    return size;
}

//Inserta un nodo con el dato en la posicion pos 
void Lista::insertar(int pos, string dato) {
    int posActual = 0;
    Nodo* aux = inicio, * nuevo;
    nuevo = new Nodo;
    nuevo->setDato(dato);

    if (pos == 0) {
        nuevo->setSiguiente(inicio);
        inicio = nuevo;
        return;
    }

    while (aux != nullptr && posActual < pos - 1) {
        aux = aux->getSiguiente();
        posActual++;
    }

    if (aux == nullptr) {
        throw 404;
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
}

//Inserta un nodo con el dato en la primera posicion 
void Lista::insertarPrimero(string dato) { insertar(0, dato); }

//Inserta un nodo con el dato en la ultima posicion
void Lista::insertarUltimo(string dato) {
    Nodo* aux = inicio, * nuevo;
    nuevo = new Nodo;
    nuevo->setDato(dato);

    if (aux == nullptr) {
        nuevo->setSiguiente(inicio);
        inicio = nuevo;
        return;
    }

    while (aux->getSiguiente() != nullptr) {
        aux = aux->getSiguiente();
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
}

//Elimina el nodo en la posicion 'pos' de la lista enlazada 
void Lista::remover(int pos) {
    Nodo* aux = inicio, * aBorrar;
    int posActual = 0;

    if (pos == 0) {
        inicio = inicio->getSiguiente();
        delete aux;
        return;
    }

    while (aux != nullptr && posActual < pos - 1) {
        aux = aux->getSiguiente();
        posActual++;
    }

    if (aux == nullptr) {
        throw 404;
    }

    aBorrar = aux->getSiguiente();
    aux->setSiguiente(aBorrar->getSiguiente());

    delete aBorrar;
}

//Obtener el dato del nodo en la posicion pos 
string Lista::getDato(int pos) {
    Nodo* aux = inicio;
    int posActual = 0;

    while (aux != nullptr && posActual < pos) {
        aux = aux->getSiguiente();
        posActual++;
    }

    if (aux == nullptr) {
        throw 404;
    }

    return aux->getDato();
}

//Reemplaza el dato almacenado en un nodo por este otro 
void Lista::reemplazar(int pos, string dato) {
    Nodo* aux = inicio;
    int posActual = 0;

    while (aux != nullptr && posActual < pos) {
        aux = aux->getSiguiente();
        posActual++;
    }

    if (aux == nullptr) {
        throw 404;
    }

    aux->setDato(dato);
}

//Funci�n que vacia la lista enlazada 
void Lista::vaciar() {
    Nodo* aux = inicio, * aBorrar;

    while (aux != nullptr) {
        aBorrar = aux;
        aux = aux->getSiguiente();
        delete aBorrar;
    }

    inicio = nullptr;

}
int Lista::sumarDeposito() {
    Nodo* aux = inicio;
    int cont = 0, suma = 0, valor;
    while (aux != nullptr) {
        if (aux->getDato() == "")
            aux = aux->getSiguiente();
        else {
            valor = stoi(aux->getDato());
            suma += valor;
            aux = aux->getSiguiente();
        }
        cont++;
    }
    return suma;
}
bool Lista::MinimoStock( string dato1, string dato2, string dato3, string dato4, string dato5, int stockmin) {
    
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

    int valor = 0;
    bool bandera = false;
    valor += stoi(dato1);
    valor += stoi(dato2);
    valor += stoi(dato3);
    valor += stoi(dato4);
    valor += stoi(dato5);



    if (valor <= stockmin)
        bandera = true;
    
    return bandera;


        
}
void Lista::print() {
    Nodo* aux = inicio;
    int cont = 1;
    while (aux != nullptr) {
        cout << cont << ". "<< aux->getDato() << endl;
        aux = aux->getSiguiente();
        cont++;
    }
    
}

int main() {
    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();
    
    
    ifstream archivo;
    int cantArticulos, sumaProductos = 0,stockmin;

    Lista grupo;
    Lista barras;
    Lista articulo;
    Lista Dep1;
    Lista Dep2;
    Lista Dep3;
    Lista Dep4;
    Lista Dep5;
    Lista aux;

    Lista artmins;


    printf("Cual va a ser el stock minimo: ");
    std::cin >> stockmin;

    archivo.open("Inventariado Fisico.csv", ios::in);       //Abrimos el archivo en modo lectura
    if (archivo.fail())         //Notificamos en caso de error
        cout << "Error";

    string linea;

    char delimitador = ';';     //Va a ser el separador de los diferentes datos

    getline(archivo, linea);    //Nos saltamos la primera fila que son solo los nombres de la tabla



    while (getline(archivo, linea)) {
        stringstream stream(linea);
        string Grupo, CodigoBarras, Articulo, Deposito1, Deposito2, Deposito3, Deposito4, Deposito5;
        getline(stream, Grupo, delimitador);
        getline(stream, CodigoBarras, delimitador);
        getline(stream, Articulo, delimitador);
        getline(stream, Deposito1, delimitador);
        getline(stream, Deposito2, delimitador);
        getline(stream, Deposito3, delimitador);
        getline(stream, Deposito4, delimitador);
        getline(stream, Deposito5, delimitador);

        // funcion para minimo de stock
        if (aux.MinimoStock(Deposito1, Deposito2, Deposito3, Deposito4, Deposito5, stockmin))
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
    //Cantidad total de art�culos diferentes
    cantArticulos = articulo.getTamanio();
    cout << "Hay " << cantArticulos << " articulos diferentes." << endl;

    //Cantidad total de art�culos
    sumaProductos += Dep1.sumarDeposito();
    sumaProductos += Dep2.sumarDeposito();
    sumaProductos += Dep3.sumarDeposito();
    sumaProductos += Dep4.sumarDeposito();
    sumaProductos += Dep5.sumarDeposito();
    cout << "Hay " << sumaProductos << " articulos en total." << endl;

    cout << "Los elementos con minimo de stock son : " << endl;
    artmins.print();

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;
    return 0;
}