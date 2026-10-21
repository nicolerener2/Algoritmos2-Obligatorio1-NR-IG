#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

struct Sendero{
    int origen;
    int destino;
    int costo;
};

class MFset {
private:
    vector<int> padre;
    vector<int> altura;

public:
    MFset(int cant){
        padre.resize(cant+1);
        altura.resize(cant+1,0);
        for(int i=1;i<=cant;i++){
            padre[i]=i;
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
    vector<Sendero> senderos(ar);
    for(int i=0; i<ar;i++){
        cin >> senderos[i].origen;
        cin >> senderos[i].destino;
        cin >> senderos[i].costo;
    }
    sort(senderos.begin(), senderos.end(),menorCosto);
    MFset m(ver);

    long long costoTotal = 0;
    int elegidos=0;

    for(int i=0;i<ar && elegidos<ver-1; i++){
        int origen = senderos[i].origen;
        int destino= senderos[i].destino;
        if(m.merge(origen,destino)){
            costoTotal+= senderos[i].costo;
            elegidos++;
        }
    }
    if(elegidos==ver-1){
        cout<< costoTotal << '\n';
    }
    else{
        cout << "imposible" << '\n';
    }
    return 0;
}