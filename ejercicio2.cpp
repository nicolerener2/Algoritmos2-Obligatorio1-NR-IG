#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
class HashAbierto {

private:

    struct Nodo {
        int* clave;
        int cant;
        Nodo* sig;
    };

    Nodo** tabla;
    int cantBuckets;
    int max;
    int cantCajones;

    int funcionDeHash(int* key){
        int h = 0;
        for(int i = 0; i < 26; i++){
            h = (31 * h + key[i]) % cantBuckets;
        }
        return h;
    }

    void insAux(Nodo*& n, int* clave){
        Nodo* nuevo= new Nodo;
        nuevo->clave=clave;
        nuevo->cant=1;
        nuevo->sig=n;
        n=nuevo;
        cantCajones++;
    }

    int* convArray(string clave){
        int* arr=new int[26];
        for(int i=0;i<26;i++){
            arr[i]=0;
        }
        for(int i=0;i<(int)clave.length();i++){
            char letra=clave[i];
            arr[letra - 'a']+=1;
        }
        return arr;
    }

    bool iguales(int* a1, int*a2){
        bool ig=true;
        for(int i=0; i<26 && ig; i++){
            if(a1[i]!=a2[i]){
                ig=false;
            }
        }
        return ig;
    }


public:

    HashAbierto(int nuevaCantBuckets) {
        cantBuckets = nuevaCantBuckets;
        tabla = new Nodo*[cantBuckets]();
        max=0;
        cantCajones=0;
    }


    void insertar(string clave) {
        int* arr=convArray(clave);
        int hash= funcionDeHash(arr);
        if(!tabla[hash]){
            insAux(tabla[hash],arr);
            if(max<1) max=1;
        }
        else{
            Nodo* aux=tabla[hash];
            bool noEsta=true;
            while(aux && noEsta){
                if(iguales(aux->clave,arr)){
                    aux->cant++;
                    noEsta=false;
                    if(max<aux->cant) max=aux->cant;
                    delete[] arr;
                }
                else{
                    aux=aux->sig;
                }
            }
            if(noEsta){
                insAux(tabla[hash], arr);
            } 
        }
    }

    int buscar(string clave){
        int* arr=convArray(clave);
        int hash= funcionDeHash(arr);

        Nodo* t=tabla[hash];
        while(t){
            if(iguales(t->clave,arr)){
                delete[] arr;
                return t->cant;
            }
            else{
                t=t->sig;
            }
        }
        delete[] arr;
        return 0;
    }

    int maximo(){
        return max;
    }

    int cantidad(){
        return cantCajones;
    }
};

int main(){
    int num;
    cin >> num;
    HashAbierto tabla(num);
    for(int i=0; i<num;i++){
        string clave;
        cin >> clave;
        tabla.insertar(clave); 
    }
    int num2;
    cin >> num2;
    for(int i=0; i<num2; i++){
        string clave;
        cin >> clave;
        int res=tabla.buscar(clave);
        cout<< res << endl;
    }
    int m= tabla.maximo();
    int c= tabla.cantidad();
    cout << c << " " << m << endl;
}