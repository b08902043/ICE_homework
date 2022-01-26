#include<iostream>
#include<vector>
using namespace std;
void DFS(vector<vector<int> > &road,int &start,int curr,int layer,int &max,vector<int> &cango,vector<int> &parent,vector<int> &tmp){ 
    if(layer > max){
        max = layer;
        start = curr;
    }
    for(int i = 0;i < road[curr].size();i ++){
        if(cango[road[curr][i]]){
            cango[road[curr][i]] = false;
            tmp.push_back(road[curr][i]);
            parent[road[curr][i]] = curr;
            DFS(road,start,road[curr][i],layer+1,max,cango,parent,tmp);
            tmp.pop_back();
        }
    }
    return;
}
void DFS2(vector<vector<int> > &road,int curr,int layer,int &max,vector<int> &cango){
    if(layer > max){
        max = layer;
    }
    for(int i = 0;i < road[curr].size();i ++){
        if(cango[road[curr][i]]){
            cango[road[curr][i]] = false;
            DFS2(road,road[curr][i],layer+1,max,cango);
        }
    }
    return;
}
void BFS(int curr,vector<vector<int> > &road,vector<int> &cango,vector<int> &maxlength){
    int count = 0;
    bool flag = true;
    vector<int> next;
    next.push_back(curr);
    while(flag){
        vector<int> now;
        flag = false;
        for(int i = 0;i < next.size();i ++){
            for(int j = 0;j < road[next[i]].size();j ++){
                if(cango[road[next[i]][j]]){
                    cango[road[next[i]][j]] = false;
                    now.push_back(road[next[i]][j]);
                    flag = true;
                }
            }  
        }
        if(flag){
            count ++;
        }
        next = now;
    }
    maxlength.push_back(count);
}
void resetCango(vector<int> &cango){
    for(int i = 0;i < cango.size();i ++){
        cango[i] = true;
    }
    return;
}
int main(){
    int N;
    cin >> N;
    vector<vector<int> > road(N+1);
    for(int i = 0;i < N-1;i ++){
        int v1,v2;
        cin >> v1 >> v2;
        road[v1].push_back(v2);
        road[v2].push_back(v1);
    }
    //find the longest path
    //find the first dot
    vector<int> parent(N+1);
    int start;
    int max = 0;
    vector<int> cango(N+1);
    resetCango(cango);
    cango[1] = false;
    vector<int> discard;
    DFS(road,start,1,0,max,cango,parent,discard);
    //find the second dot
    int end;
    resetCango(cango);
    max = 0;
    cango[start] = false;
    vector<int> OnLongest,tmp;
    tmp.push_back(start);
    DFS(road,end,start,0,max,cango,parent,tmp);
    int curr = end;
    OnLongest.push_back(end);
    while(curr != start){
        curr = parent[curr];
        OnLongest.push_back(curr);
    }
    //for all dots on longest length, find the max distance
    resetCango(cango);
    for(int i = 0;i < OnLongest.size();i ++){
        cango[OnLongest[i]] = false;
    }
    vector<int> maxlength;
    
    maxlength.push_back(0);
    for(int i = 1;i < OnLongest.size()-1;i ++){
        //BFS(OnLongest[i],road,cango,maxlength);
        int nearmax = 0;
        DFS2(road,OnLongest[i],0,nearmax,cango);
        maxlength.push_back(nearmax);
    }
    //split the tree to two subtree
    int min = max;
    vector<int> leftmax(maxlength.size()),rightmax(maxlength.size());
    leftmax[0] = 0;
    rightmax[0] = 0;
    for(int i = 1;i < maxlength.size();i ++){
        leftmax[i] = (leftmax[i-1] > i+maxlength[i])? leftmax[i-1]:i+maxlength[i];
        rightmax[i] = (rightmax[i-1] > i+maxlength[max-i])?rightmax[i-1]:i+maxlength[max-i];
    }
   for(int i = 0;i < leftmax.size();i ++){
       int chose = (leftmax[i] > rightmax[max-i-1])? leftmax[i]:rightmax[max-i-1];
       int combine = (leftmax[i]+1)/2+(rightmax[max-1-i]+1)/2+1;
       chose = (chose > combine)? chose:combine;
       min = (min < chose)? min:chose;
   }
    cout << min << endl;
    return 0;
}