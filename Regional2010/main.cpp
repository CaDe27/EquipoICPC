#include <bits/stdc++.h>
#define MOD 100000000

using namespace std;
typedef int64_t ll;

ll m[102][102][102];
int M, n;
struct range{
    int ini, fin;
    const bool operator<(const range &otro)const{
        if(ini == otro.ini)
            return fin < otro.fin;
        return ini < otro.ini;
    }
};
vector<range> rango(101);
ll dp(int l, int mid, int r){
    if(r == n+1)
        return rango[mid].fin >= M?1:0;
    if(rango[r].ini >  rango[mid].fin)
        return m[l][mid][r] = 0;
    if(m[l][mid][r] == -1){
        if(rango[l].fin < rango[r].ini && rango[mid].fin < rango[r].fin)
            m[l][mid][r] = (dp(mid, r, r+1)%MOD + dp(l,mid,r+1)%MOD)%MOD;
        else
            m[l][mid][r] = (dp(l,mid,r+1)%MOD);
    }
    return m[l][mid][r];
}
void clean(){
    for(int i = 0; i <= 100; i++)
        for(int j = 0; j <= 100; j++)
            for(int k = 0; k <= 100; k++)
                m[i][j][k] = -1;
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    int in,f;
    cin >> M >> n;
    while(M != 0 && n != 0){
        clean();
        rango[0]={0,0};
        for(int i = 1; i <= n; i++){
            cin >> in >> f;
            rango[i]= {in,f};
        }
        sort(rango.begin(), rango.begin()+n+1);
        int i = 1;
        ll suma = 0;
        while(i <= n && rango[i].ini == 0){
            suma = (suma + dp(0,i,i+1))%MOD;
            i++;
        }
        cout << suma << "\n";
        cin >> M >> n;
    }
    return 0;
}
