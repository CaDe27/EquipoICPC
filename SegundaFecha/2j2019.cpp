#include <iostream>
#include <algorithm>
#include <cstdint>
#define loop(i, a, b) for(int i =a; i < b; ++i)
using namespace std;

//la idea es representar al numero con una mascara de bits
//guardamos en una cubeta cuantas hay de cada mascara y
//usamos una dp de modo que el estado sea [numero acumulado][mascara actual]
// y lo que puedes hacer es tomar la cantidad maxima par o impar de esa mascara en la cubeta

const int maxMasc = 1023;
int cubeta[maxMasc+1];

int transformaABits(int64_t num){
    int p, bits = 0, nPrimos = 10;
    int primos[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    loop(i, 0, nPrimos){
        p = primos[i];
        while(num % (p*p) == 0)
            num/=(p*p);
        if( num%p == 0)
            bits += (1<<i);   
    }
    return bits;
}

int dp[maxMasc+1][maxMasc+1];
bool visitados[maxMasc+1][maxMasc+1];

int DP(int mascara, int actual){
    if(actual > maxMasc)
        return mascara == 0? 0: -1;

    if(!visitados[mascara][actual]){
        visitados[mascara][actual] = true;
        if(cubeta[actual] == 0)
            dp[mascara][actual] = DP(mascara,actual+1);
        else{
            int total1 = -1, total2 = -1;

            //si tomo la cantidad impar tope
            if(DP(mascara^actual,actual+1) >= 0)
                total1 = (cubeta[actual] - (cubeta[actual]&1? 0:1) ) + dp[mascara^actual][actual+1];

            //si tomo la cantidad par tope
            if(DP(mascara, actual+1) >= 0)
                total2 = (cubeta[actual]/2)*2 + dp[mascara][actual+1];

            dp[mascara][actual] = max(total1, total2);
        }
    }
    return dp[mascara][actual];
}


int main(){
    ios_base::sync_with_stdio(0);
    if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    int n;
    cin>>n;

    loop(i, 0, n){
        int64_t num;
        cin>>num;
        ++cubeta[transformaABits(num)];
    }
    cout<<DP(0, 0)<<'\n';   
}