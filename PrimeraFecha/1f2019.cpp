#include <iostream>
#include <vector>
#include <algorithm>
#define loop(i, a, b) for(int i = a; i < b; ++i)
using namespace std;

const int maxN = 100000, logN = 18;
int n;

vector<int> adj[maxN+1];
int table[logN+1][maxN+1], maxi[logN+1][maxN+1]; 

int nextValue = -1;
int values[3*maxN+3];
struct nd{
    int level, value, rootFather;
}nds[maxN+1];

int findRoot(int a){
    if(nds[a].rootFather == a)
        return a;
    return nds[a].rootFather = findRoot(nds[a].rootFather);
}

void uniteTrees(int a, int b, int day){
    int fa = findRoot(a), fb = findRoot(b);
    if(fa != fb){
        if(nds[fa].level < nds[fb].level) swap(fa, fb);
        nds[fa].level = max(nds[fb].level +1, nds[fa].level);
        adj[fa].push_back(fb);
        nds[fb].rootFather = fa;
        table[0][fb] = fa;
        maxi[0][fb] = day;
    }
}

int findValue(int a){
    if(values[a] == a)
        return a;
    return values[a] = findValue(values[a]);
}

void uniteValues(int a, int b, int r){
    int gb, ga, pa, pb;
    pa = a + 1;
    if(pa/3 != a/3) pa -= 3;
    ga = pa + 1;
    if(ga/3 != a/3) ga -= 3;

    pb = b + 1;
    if(pb/3 != b/3) pb -= 3;
    gb = pb + 1;
    if(gb/3 != b/3) gb -= 3;

    if(r == 0){
        values[b] = a;
        values[gb] = ga;
        values[pb] = pa;
    }else if(r == 1){
        values[gb] = a;
        values[b] = pa;
        values[pb] = ga;
    }else{
        values[b] = ga;
        values[gb] = pa;
        values[pb] = a; 
    }
}

void update(int a, int b, int r, int day){
    uniteTrees(a, b, day);
    if(nds[a].value == -1) nds[a].value = 3*(++nextValue); 
    if(nds[b].value == -1) nds[b].value = 3*(++nextValue);
    uniteValues(nds[a].value = findValue(nds[a].value), 
    nds[b].value = findValue(nds[b].value), r);

}

void assignLevel(int f, int lvl){
    nds[f].level = lvl;
    for(int s: adj[f])
        assignLevel(s, 1+lvl);
}

//creates LCA Binary Lifting table
void createLCATable(){
    int mid;
	for(int k = 1; k<=logN; ++k){
		for(int nd = 1; nd <= n; ++nd){
           mid = table[k-1][nd];
           if(mid != 0){
               table[k][nd] = table[k-1][mid];
               maxi[k][nd]  = max(maxi[k-1][nd], maxi[k-1][mid]); 
           }
        }
    }
}

int actMaxi;
//to get the k-th father of node i
int jump(int i, int k){
    int x=0;
	while(k > 0){
		if(k&1){
            actMaxi = max(actMaxi, maxi[x][i]);
			i = table[x][i];
        }
		++x;
		k>>=1;
	}
	return i;
}

int maxUpToLca(int i, int j){
    actMaxi = -1;
	//to put i and j in the same level
    if(nds[i].level< nds[j].level)
        j = jump(j, nds[j].level-nds[i].level);
    else
        i = jump(i, nds[i].level-nds[j].level);
    
    //these happens if one of them was lca of them
    if(i==j)
        return actMaxi;
    
	//these is to put both just below the LCA
    for(int d = logN; d>=0; --d){
        if(table[d][i] != table[d][j]){
            actMaxi = max(actMaxi, max(maxi[d][i], maxi[d][j]));
            i = table[d][i];
            j = table[d][j];
        }
    }
    //as they were just below the LCA, the LCA is the parent of either of the nodes
    return max(actMaxi, max(maxi[0][i], maxi[0][j]));
}

void processQuery(int a, int b){
    if(findRoot(a) == findRoot(b)){
        cout<<maxUpToLca(a, b)<<" ";
        int v1 = nds[a].value = findValue(nds[a].value);
        int v2 = nds[b].value = findValue(nds[b].value);
        if(v1 == v2) cout<<0<<'\n';
        else if(v2 == v1+1 || v2 == v1-2)  cout<<1<<'\n';
        else cout<<-1<<'\n';
    }
    else
        cout<<-1<<'\n';

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    cin>>n;
    loop(i, 0, n+1){
        nds[i].rootFather = i;
        nds[i].level = 0;
        nds[i].value = -1;
        values[3*i] = 3*i;
        values[3*i+1] = 3*i+1;
        values[3*i+2] = 3*i+2;
    }

    int m;
    cin>>m;
    int a, b, r;
    loop(i, 1, m+1){
        cin>>a>>b>>r;
        update(a, b, r, i);
    }

    loop(i, 0, n)
        if(nds[i].rootFather == i)
            assignLevel(i, 0);

    createLCATable();

    int q;
    cin>>q;
    loop(i, 0, q){
        cin>>a>>b;
        processQuery(a, b);
    }

    return 0;
}