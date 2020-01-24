#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdint>
#define inf 20000000001
#define loop(i, a, b) for(int i = a; i < b; ++i)
#define backLoop(i, a, b) for(int i = a; i > b; --i)
using namespace std;

//la idea es usar Floyd Warshall
//comenzando del e-esimo empleado, podemos empezar a considerar 
//cada vez a mas ciudades como camino
const int maxN = 200;
long roads[maxN+1][maxN+1];
int n;

void floyd(int k){
    loop(i, 1, n+1)
    loop(j, 1, n+1)
        if(roads[i][j] > roads[i][k]+roads[k][j])
            roads[i][j] = roads[i][k]+roads[k][j];
}

int main(){
    if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    
    scanf("%d", &n);

    //inicializamos la matriz de caminos
    loop(i, 1, n+1){
        fill(roads[i], roads[i] + n+1, inf);
        roads[i][i] = 0;
    }

    //leemos el grafo
    int m; scanf("%d", &m);
    loop(i, 0, m){
        int a, b;
        long t;
        scanf("%d %d %ld", &a, &b, &t);
        roads[a][b] = roads[b][a] = t;
    }

    //leemos el orden en que permitiremos a nuevas ciudades
    //visited lo usamos para identificar a las ciudades que inicialmente pueden ser camino
    int e; scanf("%d", &e);
    bool avoided[n+1]; fill(avoided, avoided +n+1, 0);
    vector<int> avoid[e];
    loop(i, 0, e){
        int t, city;
        scanf("%d", &t);
        loop(j, 0, t){
            scanf("%d", &city);
            avoid[i].push_back(city);
            avoided[city] = true;
        }     
    }

    vector<int> schedule[e];
    loop(i, 0, e){
        int a;
        char c;
        do{
            scanf("%d%c", &a, &c);
            schedule[i].push_back(a);
        }while(c != '\n');
    }

    int g; scanf("%d", &g);
    //consideramos a las ciudades por las que todos que siempre pueden ser camino
    loop(i, 1, n+1)
        if(!avoided[i])
            floyd(i);

    long time[e];
    backLoop(i, e-1, -1){
        long total = 0;
        int last = g;
        schedule[i].push_back(g); //para el regreso a g
        
        //asigno el tiempo entre viajes
        for(int next : schedule[i]){
            if(roads[last][next] == inf){
                total = -1;
                break;
            }
            else{
                total += roads[last][next];
                last = next;
            }
        }
        time[i] = total;

        //agrego como camino a las que de este en adelante
        //no querian
        for(int k: avoid[i])
            floyd(k);
    }

    loop(i, 0, e){
        if(time[i] == -1)
            cout<<"Assign a better schedule\n";
        else
            cout<<time[i]<<'\n';
    }
    return 0;
}
