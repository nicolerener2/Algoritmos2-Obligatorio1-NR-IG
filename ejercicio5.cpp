#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

struct Sendero{
    int origen;
    int destino;
    int costo;
};

class MFset {
private:
    int* padre;
    int* altura;

public:
    MFset(int cant){
        padre = new int[cant + 1];
        altura = new int[cant + 1];
        for (int i = 1; i <= cant; i++) {
            padre[i] = i;
            altura[i] = 0;
        }
    }

    int find (int x){
        if(padre[x]!=x){
            padre[x]=find(padre[x]);
        }
        return padre[x];
    }

    bool merge (int a, int b){
        int x=find(a);
        int y= find(b);
        if(x==y) return false;
        if(altura[x]>altura[y]) padre[y]=x;
        else if (altura[x]<altura[y]) padre[x]=y;
        else{
            padre[y]=x;
            altura[x]++;
        }
        return true;
    }

    ~MFset() {
        delete[] padre;
        delete[] altura;
    }
};

bool menorCosto(Sendero a, Sendero b){
    return a.costo < b.costo; 
}


int main(){
    int ver;
    cin >> ver;
    int ar;
    cin >> ar;
    //no hay suficientes senderos para conectar los refugios.
    if (ar < ver - 1) {
        cout << "imposible" << '\n';
        return 0;
    }
    Sendero* senderos = new Sendero[ar];
    for(int i=0; i<ar;i++){
        cin >> senderos[i].origen;
        cin >> senderos[i].destino;
        cin >> senderos[i].costo;
    }
    sort(senderos, senderos + ar, menorCosto);
    MFset m(ver);

    long long costoTotal = 0;
    int elegidos=0;

    for(int i=0;i<ar && elegidos<ver-1; i++){
        int origen = senderos[i].origen;
        int destino= senderos[i].destino;
        int liderY=m.find(origen);
        int liderX=m.find(destino);
        if(liderY!=liderX){
            m.merge(liderY,liderX);
            costoTotal+= senderos[i].costo;
            elegidos++;
        }
    }
    delete[] senderos;
    if(elegidos==ver-1){
        cout<< costoTotal << '\n';
    }
    else{
        cout << "imposible" << '\n';
    }
    return 0;
}