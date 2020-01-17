//Print all strongly connected components

//Based on Kosaraju's algorithm.
//https://www.geeksforgeeks.org/strongly-connected-components/

/*
//why do es it work?
//  the main real question is "why does dfs[v] on transpose graph prints the scc of v?"
//  Prove by contradiction.
//      Suppose there's a vertex x in dfs[v] over transpose, 
//      (a ->b means there's a path from a to b) such thar v ->x, but ~(x->v).
//      Since we are computing dfs[v] first than dfs[x], it means we first visited all the x non yet visited branch 
//      before v's in original dfs. But, since there's a path from x to v, it means v was visited first
//      (if not, since v is a son of x, v's branch would have been visited first).
//      Since there's no path from v to x, v was visited first, and it's whole branch to. That means we first visited all
//      the v non yet visited branch, a contradiction. 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
void dfs(int v,vector<int> adj[], bool visited[], stack<int> &next){
    visited[v] = true;
    for(int son: adj[v])
        if(!visited[son])
            dfs(son, adj, visited, next);
    cout<<"meto a "<<v<<endl;
    next.push(v);
}

void dfs(int v,vector<int> transpose[], bool visited[]){
    visited[v] = true;
    cout<<v<<" ";
    for(int son: transpose[v])
        if(!visited[son])
            dfs(son, transpose, visited);
}

int main(){
    if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    //supose nodes are from 0 to v-1
    int v, e;
    cin>>v>>e;
    vector<int> adj[v], transpose[v];
    for(int i = 0; i < e; ++i){
        int a, b;
        cin>>a>>b;
        adj[a].push_back(b);
        transpose[b].push_back(a);
    }

    stack<int> next;
    bool visited[v];
    fill(visited, visited+v, false);
    for(int i = 0; i < v; ++i){
        if(!visited[i])
            dfs(i, adj, visited, next);
    }

    fill(visited, visited+v, false);
    cout<<"stringly connected components are:"<<endl;
    while(!next.empty()){
        int aux = next.top(); next.pop();
        if(!visited[aux]){
            dfs(aux, transpose, visited);
            cout<<endl;
        }
    }


}