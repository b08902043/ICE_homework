#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define LongMax 9223372036854775807
using namespace std;
class road{
public:
    int index,c,u;
};
class Node{
public:
    int pi,index;
    long long key;
};
class Compare{
public:
    bool operator() (Node a, Node b)
    {
        return a.key > b.key;
    }
};
class Compare2{
public:
    bool operator() (pair<int,int> a,pair<int,int> b){
        return a.second > b.second;
    }
};
void initVisited(vector<bool> &visited){
    for(int i = 0;i < visited.size();i ++){
        visited[i] = false;
    }
}
void initVertex(vector<Node> &vertex){
    for(int i = 0;i < vertex.size();i ++){
        vertex[i].index = i;
        vertex[i].key = LongMax;
        vertex[i].pi = -1;
    }
    return;
}
int main(){
    int N,M;
    cin >> N >> M;
    vector<vector<road> > Roadlist(N+1);
    vector<int> Road(M+1);
    for(int i = 1;i <= M;i ++){
        int u,v;
        road tmproad;
        cin >> u >> v >> tmproad.c;
        tmproad.index = i;
        tmproad.u = v;
        Roadlist[u].push_back(tmproad);
        tmproad.u = u;
        Roadlist[v].push_back(tmproad); 
        Road[i] = tmproad.c;       
    }
    
    vector<bool> visited(N+1);
    vector<int> ans;
    vector<Node> vertex(N+1);
    vector<long long> Lastadd(N+1);
    for(int i = 0;i < Lastadd.size();i ++){
        Lastadd[i] = LongMax;
    }
    //shortest path
    Lastadd[1] = 0;
    initVisited(visited);
    initVertex(vertex);
    vertex[1].pi = -1;
    vertex[1].key = 0;
    vertex[1].index = 1;
    priority_queue<Node,vector<Node>,Compare> Q;
    Q.push(vertex[1]);
    
    while(!Q.empty()){
        int u = Q.top().index;
        Q.pop();
        if(!visited[u]){
            visited[u] = true;
            for(int i = 0;i < Roadlist[u].size();i ++){
                if(!visited[Roadlist[u][i].u] && (vertex[u].key+Roadlist[u][i].c < vertex[Roadlist[u][i].u].key || (vertex[u].key+Roadlist[u][i].c == vertex[Roadlist[u][i].u].key && Roadlist[u][i].c < Lastadd[Roadlist[u][i].u]))){
                    vertex[Roadlist[u][i].u].key = vertex[u].key+Roadlist[u][i].c;
                    vertex[Roadlist[u][i].u].pi = u;
                    vertex[Roadlist[u][i].u].index = Roadlist[u][i].u;
                    Q.push(vertex[Roadlist[u][i].u]);
                    vertex[Roadlist[u][i].u].index = Roadlist[u][i].index;
                    Lastadd[Roadlist[u][i].u] = vertex[u].key+Roadlist[u][i].c;
                }
            }
        }
    }
    long long sum = 0;
    for(int i = 2;i < vertex.size();i ++){
        ans.push_back(vertex[i].index);
        sum += Road[vertex[i].index];
    }
    //minimum spanning tree
    initVisited(visited);
    priority_queue<pair<int,int> ,vector<pair<int,int> >,Compare2> Q_span;
    pair<int,int> span;
    long long sum_span = 0;
    span.first = 1;
    span.second = 0;
    
    Q_span.push(span);
    while(!Q_span.empty()){
        int u = Q_span.top().first;
        if(!visited[u]){
            visited[u] = true;
            sum_span += Q_span.top().second;
            Q_span.pop();
            for(int i = 0;i < Roadlist[u].size();i ++){
                if(!visited[Roadlist[u][i].u]){
                    span.first = Roadlist[u][i].u;
                    span.second = Roadlist[u][i].c;
                    Q_span.push(span);
                }
            }
        }
        else{
            Q_span.pop();
        }
        
    }
    if(sum != sum_span){
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    sort(ans.begin(),ans.end());
    for(int i = 0;i < ans.size();i ++){
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}