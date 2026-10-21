#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Modulo{
    int numero;
    int prioridad; 
};

struct Nodo {
    int modulo;
    Nodo* siguiente;
};

struct Lista {
    Nodo* primero;
};

bool compararModulos (Modulo a, Modulo b){
    if (a.prioridad == b.prioridad){
        return a.numero < b.numero;
    }
    else{
        return a.prioridad < b.prioridad;
    }
}

template<typename T>
class Heap {
private:
    T* arr;
    int capacidad;
    int ultimoOcupado;

    //POS:Devuelve true si el primer elemento debe estar antes que el segundo en el heap.
    bool (*comparar)(T, T);

    int padre(int pos) {
        return pos / 2;
    }

    int izq(int pos) {
        return pos * 2;
    }

    int der(int pos) {
        return pos * 2 + 1;
    }

    void swap(int posA, int posB) {
        T aux = arr[posA];
        arr[posA] = arr[posB];
        arr[posB] = aux;
    }

    void flotar(int posActual) {
        if (posActual == 1) return;
        int posPadre = padre(posActual);
        if (comparar(arr[posActual], arr[posPadre])) {
            swap(posActual, posPadre);
            flotar(posPadre);
        }
    }

    void hundir(int posActual) {
        int posHijoIzq = izq(posActual);
        int posHijoDer = der(posActual);
        if (posHijoIzq > ultimoOcupado) return;
        int posMenor = posHijoIzq;
        if (posHijoDer <= ultimoOcupado && comparar(arr[posHijoDer], arr[posHijoIzq])) {
            posMenor = posHijoDer;
        }
        if (comparar(arr[posMenor], arr[posActual])) {
            swap(posMenor, posActual);
            hundir(posMenor);
        }
    }

public:
    Heap(int unaCapacidad, bool (*comparar)(T, T)) {
        this->arr = new T[unaCapacidad + 1];
        this->capacidad = unaCapacidad;
        this->comparar = comparar;
        this->ultimoOcupado = 0;
    }

    T tope() {
        assert(!estaVacio());
        return arr[1];
    }

    void eliminarTope() {
        assert(!estaVacio());
        arr[1] = arr[ultimoOcupado];
        ultimoOcupado--;
        hundir(1);
    }

    int cantidad(){
        return ultimoOcupado;
    }

    ~Heap() {
        delete[] arr;
    }

    void insertar(T elem) {
        assert(!estaLleno());
        arr[++ultimoOcupado] = elem; 
        flotar(ultimoOcupado);
    }

    bool estaLleno() {
        return ultimoOcupado == capacidad;
    }

    bool estaVacio() {
        return ultimoOcupado == 0;
    }
};

bool menor(long long a, long long b) {
    return a < b;
}   

int main(){
    int V, A;
    cin >> V >> A;

    int* Listaprioridades = new int[V + 1];
    for (int i = 1; i <= V; i++){
        int P;
        cin >> P;
        Listaprioridades[i] = P;
    }

    int* pendientes = new int[V +1]();
    Lista* dependencias = new Lista[V +1];
    for (int i=1; i <= V; i++){
        dependencias[i].primero = NULL;
    }
    for (int i=0; i < A; i++){
        int u,v;
        cin >> u >> v;
        Nodo* nuevo = new Nodo;
        nuevo->modulo = v;
        nuevo->siguiente = dependencias[u].primero;
        dependencias[u].primero = nuevo;
        pendientes[v]++;
    }

    Heap<Modulo> heap (V, compararModulos);
    for (int i=1; i <= V; i++){
        if (pendientes[i]==0){
            Modulo nuevo; 
            nuevo.numero = i;
            nuevo.prioridad = Listaprioridades[i];
            heap.insertar(nuevo);
        }
    }
    int* orden = new int[V];
    int compilados = 0;

   
    while (!heap.estaVacio()){
        Modulo actual = heap.tope();
        heap.eliminarTope();
        orden[compilados] = actual.numero;
        compilados++;

        Nodo* aux= dependencias[actual.numero].primero;
        while (aux !=NULL){
            pendientes[aux->modulo]--;
            if (pendientes[aux->modulo] == 0){
                Modulo nuevo;
                nuevo.numero = aux->modulo;
                nuevo.prioridad = Listaprioridades[nuevo.numero];
                heap.insertar(nuevo);
            }

            aux = aux->siguiente;
        }
    }
    if (compilados != V){
        cout << "imposible" << endl;
    }
    else{
        for (int i=0; i<compilados; i++){
            cout << orden[i] << endl;
        }
    }

    for (int i=1; i <= V; i++){
        Nodo* aux = dependencias[i].primero;
        while(aux!=NULL){
            Nodo* sig = aux->siguiente;
            delete aux;
            aux = sig;
        }
    }
    delete[] Listaprioridades;
    delete[] pendientes;
    delete[] dependencias;
    delete[] orden;

    return 0;
}


