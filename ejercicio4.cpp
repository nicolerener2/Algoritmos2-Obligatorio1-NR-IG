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
        //si la posicion del hIzq fuera mayor que el ultimoOcupado, no tiene hijos
        if (posHijoIzq > ultimoOcupado) return;
        //supone que el hijoIzq es el menor
        int posMenor = posHijoIzq;
        //si existe el hijo derecho Y el der es menor al izq, cambia el menor por el hijoDer
        if (posHijoDer <= ultimoOcupado && comparar(arr[posHijoDer], arr[posHijoIzq])) {
            posMenor = posHijoDer;
        }
        //si alguno de los hijos es menor que el padre, los cambio 
        if (comparar(arr[posMenor], arr[posActual])) {
            swap(posMenor, posActual);
            //Ahora el que era el padre paso a estar en la posicion posMenor
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

    //leo cant modulos y dependencias 
    int V, A;
    cin >> V >> A;

    //me guardo las prioridades de cada modulo en un array
    int* Listaprioridades = new int[V + 1];
    for (int i = 1; i <= V; i++){
        int P;
        cin >> P;
        Listaprioridades[i] = P;
    }

    //cant de dependencias pendientes de cada modulo
    int* pendientes = new int[V +1]();
    //para guardar que modulo depende de cual
    Lista* dependencias = new Lista[V +1];
    for (int i=1; i <= V; i++){
        dependencias[i].primero = NULL;
    }

    //leo las dependencias
    for (int i=0; i < A; i++){
        int u,v;
        cin >> u >> v;

        //creo un nodo para guardar que v depende de u
        Nodo* nuevo = new Nodo;
        nuevo->modulo = v;

        //inserto el nodo al principio de la lista de u
        nuevo->siguiente = dependencias[u].primero;
        dependencias[u].primero = nuevo;

        //el modulo v tiene una dependencia mas 
        pendientes[v]++;
    }

    //creo el heap para guardar los modulos que estan listos
    Heap<Modulo> heap (V, compararModulos);

    //recorro los modulos para ver cuales estan listos 
    for (int i=1; i <= V; i++){
        if (pendientes[i]==0){
            Modulo nuevo; 
            nuevo.numero = i;
            nuevo.prioridad = Listaprioridades[i];
            heap.insertar(nuevo);
        }
    }
    
    //guardo el orden en que se van compilando los modulos 
    int* orden = new int[V];
    int compilados = 0;

    //voy compilando los modulos del heap (pq en el heap estan solo los que estan listos para compilar)
    while (!heap.estaVacio()){
        //compilo el modulo de menor prioridad y lo guardo 
        Modulo actual = heap.tope();
        heap.eliminarTope();

        //guardo el modulo que acabo de compilar
        orden[compilados] = actual.numero;
        compilados++;

        //voy a la lista de modulos que dependian del actual y les resto una dependencia pendiente, y si queda en 0 los inserto en el heap
        Nodo* aux= dependencias[actual.numero].primero;
        while (aux !=NULL){
            pendientes[aux->modulo]--;

            //si el modulo no depende de ningun otro mas, lo inserto en el heap
            if (pendientes[aux->modulo] == 0){
                Modulo nuevo;
                nuevo.numero = aux->modulo;
                nuevo.prioridad = Listaprioridades[nuevo.numero];
                heap.insertar(nuevo);
            }

            aux = aux->siguiente;
        }
    }

    //si no se compilan todos los modulos, es pq hay un ciclo
    if (compilados != V){
        cout << "imposible" << endl;
    }
    //sino, imprimo los numeros en orden de compilacion
    else{
        for (int i=0; i<compilados; i++){
            cout << orden[i] << endl;
        }
    }

    //libero memoria de las listas 
    for (int i=1; i <= V; i++){
        Nodo* aux = dependencias[i].primero;
        while(aux!=NULL){
            Nodo* sig = aux->siguiente;
            delete aux;
            aux = sig;
        }
    }

    //libero la memoria de los arreglos
    delete[] Listaprioridades;
    delete[] pendientes;
    delete[] dependencias;
    delete[] orden;

    return 0;
}


