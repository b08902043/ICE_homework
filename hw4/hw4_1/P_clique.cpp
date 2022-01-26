#include<iostream>
#include<vector>
#include<bitset>
#include<algorithm>
#include<glpk.h>
#include "ypglpk.hpp"
using namespace std;
using namespace ypglpk;
void BronKer(vector<bitset<80> > &ans,bitset<80> R, bitset<80> P, bitset<80> X, int N, bitset<80> edge[], vector<vector<double> > &A){
    if(P.none() && X.none()){
        //find the clique
        for(int i = 0;i < N;i++){
            A[i].push_back(-R[i]);
            
        }
        ans.push_back(R);
        return;
    }
    else if(P.none()){
        //the cliqe has been calculated
        return;
    }
    else{
        
        //1.arbitary choose one pivot
        int pivot;
        for(int i = 0;i < N;i ++){
            if(P[i] != 0){
                pivot = i;
                break;
            }
        }
        //find which is not pivot's neignbor
        bitset<80> tmp = P & (~edge[pivot]);
        for(int i = 0;i < N;i++){
            if(tmp[i]){
                R[i] = 1;
                BronKer(ans,R, P & edge[i], X & edge[i], N, edge, A);
                R[i] = 0;
                P[i] = 0;
                X[i] = 1;
            }
        }
    }
    return;
}
int main(){
    int T;
    cin >> T;
    int N,M;
    for(int t = 0;t < T;t ++){
        bitset<80> edge[80];
        cin >> N >> M;
        for(int i = 0;i < M;i ++){
            int a,b;
            cin >> a >> b;
            edge[a][b] = 1;
            edge[b][a] = 1;
        }
        
        bitset<80> R,P,X;
        R.reset();
        P.set();
        X.reset();
        vector<vector<double> > A(N);
        vector<bitset<80> > ans;
        BronKer(ans,R,P,X,N,edge,A);
        vector<double> B(N+2*A[0].size());
        vector<double> C(A[0].size());
        for(int i = 0;i < A[0].size();i ++){
            C[i] = -1;
        }
        for(int i = 0;i < N;i ++){
            B[i] = -1;
        }    
        int num = A[0].size();
        for(int i = N;i < N+num;i ++){
            vector<double> tmp;
            for(int j = 0;j < num;j ++){
                
                if(i-N == j){
                    tmp.push_back(-1);
                }
                else{
                    tmp.push_back(0);
                }
            }
            A.push_back(tmp);
            B[i] = 0;
        }     
        for(int i = N+num;i < N+2*num;i ++){
            vector<double> tmp;
            for(int j = 0;j < num;j ++){
                if(i-N-num == j){
                    tmp.push_back(1);
                }
                else{
                    tmp.push_back(0);
                }
                
            }
            A.push_back(tmp);
            B[i] = 1;
        }
        vector<bool> isint(num, true);
        pair<double,std::vector<double>> x = mixed_integer_linear_programming(A, B, C, isint);
        int count = 0;
        for(int i = 0;i < x.second.size();i ++){
            if(x.second[i] == 1){
                count ++;
            }
        }
        cout << count << endl;
        bool hasout[N];
        for(int i = 0;i < N;i ++){
            hasout[i] = 0;
        }
        for(int i = 0;i < x.second.size();i ++){
            count = 0;
            vector<int> out;
            if(x.second[i] != 0){
                for(int j = 0;j < ans[i].size();j ++){
                    if(!hasout[j] && ans[i][j] == 1){
                        hasout[j] = 1;
                        out.push_back(j);
                        count ++;
                    }
                }
                cout << count << " ";
                for(int j = 0;j < out.size();j ++){
                    cout << out[j] << " ";
                }
                cout << endl;
            }
        }
    }
    
    return 0;
}
/*
algorithm BronKerbosch2(R, P, X) is
    if P and X are both empty then
        report R as a maximal clique
    choose a pivot vertex u in P ⋃ X
    for each vertex v in P \ N(u) do
        BronKerbosch2(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
        P := P \ {v}
        X := X ⋃ {v}
*/