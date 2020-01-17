// { Driver Code Starts
#include<iostream>
#include <cmath>
using namespace std;

int *constructST(int arr[],int n);


int RMQ(int st[] , int n, int a, int b);
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int N;
        cin>>N;
        int A[N];
        for(int i=0;i<N;i++)
            cin>>A[i];
        int Q;
        cin>>Q;



        int *segTree = constructST(A,N);

        for(int i=0;i<Q;i++)
        {
            int start,e;
            
            cin>>start>>e;
            if(start>e)
            {
                swap(start,e);
            }
            cout<<RMQ(segTree,N,start,e)<<" ";
        }
        cout<<endl;
    }
}
// } Driver Code Ends
/*This is a function problem.You only need to complete the function given below*/
/* The functions which 
builds the segment tree */
int getMid(int a, int b){return a+(b-a)/2;}
int constructSTSub(int arr[],int *st,int si,int ss,int se){
    if(se == ss)
        st[si] = arr[ss];
    else{
        int mid = getMid(ss, se);
        st[si] = min(constructSTSub(arr, st, 2*si+1, ss, mid),
                     constructSTSub(arr, st, 2*si+2, mid+1, se));            
    }
	return st[si]; 
}

int *constructST(int arr[],int n)
{
  int x = (int)ceil(log2(n));
  int maxSize = (int)pow(2, x+1) - 1;
  int *st = new int[maxSize]; 
  constructSTSub(arr, st, 0, 0, n-1);
  return st;
}
/* The functions returns the
 min element in the range
 from a and b */
int RMQSub(int *st, int si, int ss, int se, int qs, int qe){
    if(qs<=ss && se<=qe)
        return st[si];
    else if(se<qs || qe<ss)
        return INT_MAX;
    else{
        int mid = getMid(ss, se);
        return min(RMQSub(st, 2*si+1, ss, mid, qs, qe),
                    RMQSub(st, 2*si+2, mid+1, se, qs, qe));
    }
}
/* The functions returns the
 min element in the range
 from a and b */
int RMQ(int *st , int n, int a, int b)
{
	if(a > b)
        swap(a,b);
        
    if(a > n-1 || b < 0)
        return -1;
    return RMQSub(st, 0, 0, n-1,a, b);
}