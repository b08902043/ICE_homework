#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct cmp
{
    bool operator()(pair<int,int> &a, pair<int,int> &b) const
    {
        return a.second < b.second;
    }
};
void finishtime(int curr,vector<bool> &cango,vector<vector<int> > &road, priority_queue<pair<int,int>,vector<pair<int,int> >,cmp > &time,int &count){
    for(int i = 0;i < road[curr].size();i ++){
        if(cango[road[curr][i]]){
            cango[road[curr][i]] = false;
            
            finishtime(road[curr][i],cango,road,time,count);
        }
    }
    count ++;
    pair<int,int> tmp;
    tmp.first = curr;
    tmp.second = count;
    time.push(tmp);
    return;
}
void initcango(vector<bool> &cango){
    for(int i = 0;i <= cango.size();i ++){
        cango[i] = true;
    }
}
void Reverse(vector<vector<int> > &road,vector<vector<int> > &reverseroad){
    for(int i = 1;i < road.size();i ++){
        for(int j = 0;j < road[i].size();j ++){
            reverseroad[road[i][j]].push_back(i);
        }
    }
}
void FindoutZero(int curr,vector<vector<int> > &reverseroad,vector<bool> &cango,vector<int> &DAG,int count,vector<int> &tmp){
    DAG[curr] = count;
    tmp.push_back(curr);
    for(int i = 0;i < reverseroad[curr].size();i ++){
        if(cango[reverseroad[curr][i]]){  
            cango[reverseroad[curr][i]] = false;
            FindoutZero(reverseroad[curr][i],reverseroad,cango,DAG,count,tmp);
        }
    }
    return;
}
void Findpair(vector<vector<int> > &Daglist,int curr,vector<bool> &visited,vector<bool> &in,vector<bool> &out,int &child){
    if(child == -1){
        for(int i = 0;i < Daglist[curr].size();i ++){  
            if(!visited[Daglist[curr][i]]){
                visited[Daglist[curr][i]] = true;
                if(in[Daglist[curr][i]] == 1 && out[Daglist[curr][i]] == 0){
                    child = Daglist[curr][i];
                    return;
                }
                else{
                    Findpair(Daglist,Daglist[curr][i],visited,in,out,child);
                }
                if(child != -1){
                    break;
                }
            }
        }
    }
    
    return;
}
int main(){
    int T,flag;
    cin >> T >> flag;
    for(int w = 0;w < T;w ++){
        int N,M;
        cin >> N >> M;
        vector<vector<int> > road(N+1);
        for(int i = 0;i < M;i ++){
            int v1,v2;
            cin >> v1 >> v2;
            road[v1].push_back(v2);
        }
        //find the finish time
        priority_queue<pair<int,int>,vector<pair<int,int> >,cmp > time;
        int count = 0;
        vector<bool> cango(N+1);
        initcango(cango);
        for(int i = 1;i <= N;i ++){
            if(cango[i]){
                cango[i] = false;
                finishtime(i,cango,road,time,count);
            }
        }
        initcango(cango);
        vector<vector<int> > reverseroad(N+1);
        Reverse(road,reverseroad);
        //find DAG
        vector<int> DAG(N+1);
        vector<vector<int> > Dagtodot;
        vector<int> nu;
        Dagtodot.push_back(nu);
        count = 1;
        while(!time.empty()){
            int curr = time.top().first;
            if(cango[curr]){
                cango[curr] = false;
                vector<int> tmp;
                FindoutZero(curr,reverseroad,cango,DAG,count,tmp);
                Dagtodot.push_back(tmp);
                count ++;
                time.pop();
            }
            else{
                time.pop();
            }
        }
        //find indegree and outdegree of each SCC 
        vector<bool> in(Dagtodot.size());
        vector<bool> out(Dagtodot.size());
        vector<int> in_zero,out_zero;
        for(int i = 1;i < in.size();i ++){
            in[i] = false;
            out[i] = false;
        }
        vector<vector<int> > Daglist(Dagtodot.size());
        for(int i = 1;i < Dagtodot.size();i ++){
            for(int j = 0;j < Dagtodot[i].size();j ++){
                for(int k = 0;k < reverseroad[Dagtodot[i][j]].size();k ++){
                    if(DAG[reverseroad[Dagtodot[i][j]][k]] != i){
                        bool flag = true;
                        for(int l = 0;l < Daglist[i].size();l ++){
                            if(DAG[reverseroad[Dagtodot[i][j]][k]] == Daglist[i][l]){
                                flag = false;
                            }
                        }
                        if(flag){
                            in[DAG[reverseroad[Dagtodot[i][j]][k]]] = true;
                            out[i] = true;
                            Daglist[i].push_back(DAG[reverseroad[Dagtodot[i][j]][k]]);
                        }
                        
                    }
                }
            }
        }
        int indegree = 0,outdegree = 0;
        for(int i = 1;i < in.size();i ++){
            if(in[i] == 0){
                in_zero.push_back(i);
                indegree ++;
            } 
        }
        for(int i = 1;i < in.size();i ++){
            if(out[i] == 0){
                outdegree ++;
                out_zero.push_back(i);
            }
        }
        if(Dagtodot.size() == 2){
            cout << "0" << endl;
            continue;
        }
        else{
            int max;
            max = (indegree > outdegree)? indegree:outdegree;
            cout << max << endl;
        }
        if(flag == 0){
            continue;
        }
        //pair dots
        vector<pair<int,int> > haspair;
        vector<int> nopair_out,nopair_in;
        vector<int> single;
        vector<bool> visited(in.size());
        vector<bool> is_in(in.size());
        for(int i = 0;i < visited.size();i ++){
            visited[i] = false;
            is_in[i] = true;
        }
        for(int i = 1;i < in.size();i ++){
            if(in[i] == 0 && out[i] == 1){
                int child = -1;
                Findpair(Daglist,i,visited,in,out,child);
                if(child != -1){
                    pair<int,int> tmp;
                    tmp.first = i;
                    tmp.second = child;
                    is_in[child] = false;
                    haspair.push_back(tmp);
                }
                else{
                    nopair_out.push_back(i);
                }
            }
        }
        for(int i = 1;i < in.size();i ++){
            if(in[i] == 0 && out[i] == 0){
                single.push_back(i);
            }
            else if(in[i] == 1 && out[i] == 0 && is_in[i]){
                nopair_in.push_back(i);
            }
        }
        //combine pair dots
        for(int i = 0;i < (int)haspair.size()-1;i ++){
            cout << Dagtodot[haspair[i+1].first][0] << " " << Dagtodot[haspair[i].second][0] << endl;
        }
        for(int i = 0;i < single.size();i ++){
            if(i == 0){
                if(!haspair.empty()){
                    cout << Dagtodot[single[i]][0] << " " << Dagtodot[haspair.back().second][0] << endl;
                }
            }
            else{
                cout << Dagtodot[single[i]][0] << " " << Dagtodot[single[i-1]][0] << endl;
            }
        }
        //connect pair dots and single dots to a cycle
        int cycle;
        if(!haspair.empty() && !single.empty()){
            cout << Dagtodot[haspair[0].first][0] << " " << Dagtodot[single.back()][0] << endl;
            cycle = Dagtodot[haspair[0].first][0];
        }
        if(!haspair.empty() && single.empty()){
            cout << Dagtodot[haspair[0].first][0] << " " << Dagtodot[haspair.back().second][0] << endl;
            cycle = Dagtodot[haspair[0].first][0];
        }
        if(haspair.empty() && !single.empty()){
            cout << Dagtodot[single[0]][0] << " " << Dagtodot[single.back()][0] << endl;
            cycle = Dagtodot[single[0]][0];
        }
        // add nopair to the cycle
        while(!nopair_in.empty() && !nopair_out.empty()){
            cout << Dagtodot[nopair_out.back()][0] << " " << Dagtodot[nopair_in.back()][0] << endl; 
            nopair_out.pop_back();
            nopair_in.pop_back();
        }
        while(!nopair_out.empty()){
            cout << Dagtodot[nopair_out.back()][0] << " " << cycle << endl;
            nopair_out.pop_back();
        }
        while(!nopair_in.empty()){
            cout << cycle << " " << Dagtodot[nopair_in.back()][0] << endl;
            nopair_in.pop_back();
        }
    }
    
    return 0;
}