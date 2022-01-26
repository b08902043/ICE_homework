#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

struct cmp{
    bool operator() ( pair<pair<int,int>,long long> a, pair<pair<int,int>,long long> b ){
        return a.second > b.second;
        }
};
class Node{
public:
    int prev,next;    
};
int main(){
    int N,flag;
    cin >> N >> flag;
    //find the longest
    
    for(int k = 0;k < N;k ++){
        int n;
        long long count = 0,scount = 0;
        vector<int> longest;
        unordered_map<int,Node> list,slist;
        pair<pair<int,int>,long long> near;
        priority_queue<pair<pair<int,int>,long long>, vector<pair<pair<int,int>,long long>>, cmp> min,smin;
        int max,t;
        cin >> n;
        for(int j = 0;j < n;j ++){
            if(j == 0){
                cin >> max;
            }
            else{
                cin >> t;
                if((long long)t * max > 0){
                    max = (max > t)? max:t;
                }
                else{
                    longest.push_back(max);
                    count += max;
                    max = t;
                }
                
            }
            
        }
        longest.push_back(max);
        count += max;
        scount = count;
        //make list
        for(int i = 0;i < longest.size();i ++){
            list[i].next = i+1;
            list[i].prev = i-1;
        }
        list[0].prev = longest.size()-1;
        list[longest.size()-1].next = 0;
        //make slist
        if(longest.size() > 1){
            slist = list;
            if(longest[0] > longest[longest.size()-1]){
                slist.erase(longest.size()-1);
                slist[longest.size()-2].next = 0;
                slist[0].prev = longest.size()-2;
                scount -= longest[longest.size()-1];
            }
            else{
                slist.erase(0);
                slist[longest.size()-1].next = 1;
                slist[1].prev = longest.size()-1;
                scount -= longest[0];
            }
        }
        unordered_map<int,Node>:: iterator l;
        //make queue
        for(l = list.begin();l != list.end();l ++){
            near.first.first = (*l).first;
            near.first.second = (*l).second.next;
            near.second = longest[near.first.first]+longest[near.first.second];
            min.push(near);
        }
        
        for(l = slist.begin();l != slist.end();l ++){
            near.first.first = (*l).first;
            near.first.second = (*l).second.next;
            near.second = longest[near.first.first]+longest[near.first.second];
            smin.push(near);
        }
        long long ans[n];
        for(int i = 0;i < n;i ++){
            ans[i] = 0;
        }
        //calculate size > 2
        int currindex,nextindex;
        pair<pair<int,int>, long long> test;
        while(list.size() > 2){
            test = min.top();
            currindex = test.first.first;
            nextindex = test.first.second;
            ans[list.size()-1] = count;
            if(list.count(currindex) && list[currindex].next == nextindex){
                list[list[currindex].prev].next = list[nextindex].next;
                list[list[nextindex].next].prev = list[currindex].prev;
                near.first.first = list[list[nextindex].next].prev;
                near.first.second = list[list[currindex].prev].next;
                
                near.second = longest[near.first.first]+longest[near.first.second];
                count -= (longest[currindex]+longest[nextindex]);
                min.pop();
                min.push(near);
                list.erase(currindex);
                list.erase(nextindex);
            }
            else{
                
                min.pop();
                
            }
            
        }
        while(slist.size() > 2){
            currindex = smin.top().first.first;
            nextindex = smin.top().first.second;
            ans[slist.size()-1] = scount;
            if(slist.count(currindex) &&slist[currindex].next == nextindex){
                slist[slist[currindex].prev].next = slist[nextindex].next;
                slist[slist[nextindex].next].prev = slist[currindex].prev;
                near.first.first = slist[currindex].prev;
                near.first.second = slist[nextindex].next;
                near.second = longest[slist[currindex].prev]+longest[slist[nextindex].next];
                scount -= (longest[currindex]+longest[nextindex]);
                smin.push(near);
                slist.erase(currindex);
                slist.erase(nextindex);
            }
            else{
                smin.pop();
            }
        }
        if(list.size() == 2){
            for(l = list.begin();l != list.end();l ++){
                ans[1] += longest[(*l).first];
            }
        }
        if(list.size() == 1){
            ans[0] = count;
        }
        if(slist.size() == 2){
            for(l = slist.begin();l != slist.end();l ++){
                ans[1] += longest[(*l).first];
            }
        }
        if(slist.size() == 1){
            ans[0] = scount;
        }
        for(int i = 0;i < n;i++){
            cout << ans[i] << " ";
        }
        
        cout << endl;
    }
}