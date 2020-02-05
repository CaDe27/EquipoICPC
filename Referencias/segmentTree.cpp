#include <iostream>
#include <algorithm>
#include <climits>

#define loop(i, a, b) for(int i = a; i < b; ++i)

using namespace std;

const int maxN = 100000;
int n;

struct SegmentTree{
    int left[maxN+1], right[maxN+1], funct[maxN+1], delta[maxN+1]; 
    
    //if instead of incrementing, you need other aggregate update function, 
    // change propagate, update and incrementI and queryI
    void init(int i, int a, int b){
        left[i] = a;
        right[i] = b;
        if(a==b) return;
        int m = (a+b)/2;
        init(2*i, a, m);
        init(2*i+1, m+1,b);
    }
    
    SegmentTree(int n){
        init(1, 1, n);
    }

    void propagate(int i){
        delta[2*i] += delta[i];
        delta[2*i + 1] += delta[i];
        delta[i] = 0;
    }

    void update(int i){
        //its now implemented with min
        funct[i] =  min(funct[2*i] + delta[2*i], funct[2*i+1] + delta[2*i+1]);
    }

    void incrementI(int i, int a, int b, int val){
        if(b < left[i] || right[i] < a)
            return;
        
        if( a<=left[i] && right[i]<=b ){
            delta[i] += val;
            return;
        }
        
        propagate(i);
        incrementI(2*i, a, b, val);
        incrementI(2*i+1, a, b, val);
        update(i);
        
    }

    void increment(int a, int b, int val){
        incrementI(1, a, b, val);
    }

    int queryI(int i, int a, int b){
        if(b < left[i] || right[i] < a)
            return INT_MAX;
        
        if(a <= left[i] && right[i] <= b)
            return funct[i] + delta[i];
        
        propagate(i);
        int leftQ =  queryI(2*i, a, b);
        int rightQ = queryI(2*i+1, a, b);
        update(i);
        return min(leftQ, rightQ);
    }

    int query(int a, int b){
        return queryI(1, a, b);
    }

};

int main(){
    SegmentTree a(10);
}