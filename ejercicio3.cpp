#include <cassert>
#include <iostream>

using namespace std;

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
        if (posHijoDer <= ultimoOcupado &&
            comparar(arr[posHijoDer], arr[posHijoIzq])) {
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
    int num;
    cin >> num;
    Heap<long long> heap(num, menor);
    for(int i=0; i<num;i++){
        long long n1;
        cin >> n1;
        heap.insertar(n1);
    }
    long long costoTotal = 0;

    while (heap.cantidad() > 1) {
        long long a = heap.tope();
        heap.eliminarTope();

        long long b = heap.tope();
        heap.eliminarTope();

        long long nuevo = a + b;
        costoTotal += nuevo;
        heap.insertar(nuevo);
    }

    cout << costoTotal << '\n';
    return 0;   
}