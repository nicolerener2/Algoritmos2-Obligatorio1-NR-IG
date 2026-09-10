#include <cassert>
#include <string>
#include <iostream>
#include <limits>
//#include <algorithm>  va o no va?

using namespace std;
template <typename T>
struct NodoAVL{
    T dato; 
    int altura;
    NodoAVL *izq;
    NodoAVL *der;

    NodoAVL (T elem){
        dato = elem;
        altura=1;
        izq = der = NULL;
    }
};

template <typename T>
class AVL{
private:
    NodoAVL<T>* raiz;

    int getAltura (NodoAVL<T>* nodo){
        if (!nodo){
            return 0;
        }
        return nodo->altura;
    }

    int getBalance (NodoAVL<T>* nodo){
        if (!nodo){
            return 0;
        }
        return getAltura (nodo->der) - getAltura(nodo->izq);
    }

    NodoAVL<T>* rotacionDerecha (NodoAVL<T>* nodo){
        NodoAVL<T>* A = nodo->izq;
        NodoAVL<T>* B = nodo;
        NodoAVL<T>* T2 = A->der;

        B->izq = T2;
        A->der = B;

        B->altura = 1 + max(getAltura(B->izq), getAltura(B->der));
        A->altura = 1 + max(getAltura(A->izq), getAltura(A->der));

        return A;
    }

    NodoAVL<T>* rotacionIzquierda (NodoAVL<T>* nodo){
        NodoAVL<T>* A = nodo;
        NodoAVL<T>* B = nodo->der;
        NodoAVL<T>* T2 = B->izq;

        A->der = T2;
        B->izq = A;
        
        A->altura = 1 + max(getAltura(A->izq), getAltura(A->der));
        B->altura = 1 + max(getAltura(B->izq), getAltura(B->der));
        
        return B;
    }

    NodoAVL<T>* insertarRec (NodoAVL<T>* nodo, T elem){
        if (!nodo){
            return new NodoAVL<T>(elem);
        }
        else if (elem < nodo->dato){
            nodo->izq = insertarRec(nodo->izq, elem);
        }
        else if (elem > nodo->dato){
            nodo->der = insertarRec(nodo->der, elem);
        }
        else{
            return nodo;
        }

        nodo->altura = 1 + max(getAltura(nodo->izq), getAltura(nodo->der));

        int balance = getBalance(nodo);

        if (balance < -1 && elem < nodo->izq->dato){
            return rotacionDerecha(nodo);
        }

        if (balance < -1 && elem > nodo->izq->dato){
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }

        if (balance > 1 && elem < nodo->der->dato){
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }

        if (balance >1 && elem > nodo->der->dato){
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    bool buscarRec (NodoAVL<T>* nodo, T elem){
        if(!nodo) return false;
        if(nodo->dato == elem) return true;
        if (nodo->dato<elem) return buscarRec(nodo->der, elem);
        return buscarRec(nodo->izq, elem);
    }

    void rangoRec(NodoAVL<T>* nodo, T desde, T hasta){
        if(!nodo) return;
        if (nodo->dato > desde) rangoRec(nodo->izq, desde, hasta);
        if (nodo->dato >= desde && nodo->dato <= hasta){
            cout << nodo->dato << endl;
        }
        if (nodo->dato < hasta){
            rangoRec(nodo->der, desde, hasta);
        }
    }

public:

    AVL(){
        raiz= NULL;
    }

    void alta(T elem){
        raiz=insertarRec(raiz,elem);
    }

    bool buscar(T elem){
        return buscarRec(raiz, elem);
    }

    void rango(T desde, T hasta){
        rangoRec(raiz, desde, hasta);
    }

};


int main(){
    AVL<long long> monedas;
    AVL<string> pinturas;

    int num;
    cin >> num;
    for(int i=0; i<num;i++){
        string op;
        cin >> op;
        string tipo;
        cin >> tipo;
        if(tipo=="P"){
            string n;
            cin>> n;
            if(op=="RANGO"){
                string hasta;
                cin >> hasta;
                pinturas.rango(n,hasta);
            }
            else if (op=="ALTA"){
                pinturas.alta(n);
            }
            else{
                if(pinturas.buscar(n)){
                    cout << "si" << endl;
                }
                else{
                    cout << "no" << endl;
                }
            }
        }
        else{
            long long n;
            cin>> n;
            if(op=="RANGO"){
                long long hasta;
                cin >> hasta;
                monedas.rango(n,hasta);
            }
            else if (op=="ALTA"){
                monedas.alta(n);
            }
            else{
                if(monedas.buscar(n)){
                    cout << "si" << endl;
                }
                else{
                    cout << "no" << endl;
                }
            }
        }
        
    }
    return 0;

}

