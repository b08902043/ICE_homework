#include "ada-hw4-p3.h"
#include<utility>
#include<iostream>
#define CONCEAL 1
#define KNOWN 2
using namespace std;
// feel free to use global variables
std::vector<int> contest;
std::vector<std::pair<int,int> > known,conceal;
void MakeAns(vector<int> &ans){
    for(int i = 0;i < conceal.size();i ++){
        ans.push_back(conceal[i].first);
    }
    return;
}
std::vector<int> init(int N) {
    contest.resize(N);
    for (int i = 0; i < N; ++i)
        contest[i] = i;
    int start = 0,end = 1;
    while(end < N){
        if(compare(contest[start],contest[end])){
            known.push_back(std::make_pair(contest[start],start));
            start = end;
            end ++;
        } 
        else{
            conceal.push_back(std::make_pair(contest[start],start));
            conceal.push_back(std::make_pair(contest[end],end));
            if(known.empty()){
                start = end+1;
                end = end +2;
            }
            else{
                start = known.back().second;
                known.pop_back();
                end ++;
            }
        }
    }
    if(start < N) known.push_back(std::make_pair(contest[start],start));
    std::vector<int> ans;
    MakeAns(ans);
    return ans;
}
void Update(int inknown,int p){
    //if position in known >= p, pos ++
    for (int i = inknown; i < known.size(); i++){
        known[i].second ++;
    }
    //if position in conceal >= p, pos ++
    for (int i = 0; i < conceal.size(); i++){
        if (conceal[i].second >= p){
            conceal[i].second ++;
        }
    }
    return ;
}
void MakeConceal(int id,int p,int inknown,vector<int> &ans){
    conceal.push_back(std::make_pair(id, p));
    conceal.push_back(known[inknown]);
    MakeAns(ans);
    return;
}
std::vector<int> insert(int p, int id) {
    vector<int> ans;
    contest.insert(contest.begin() + p, id);
    int inknown = 0;
    //find the pos in known
    while (inknown < known.size() && known[inknown].second < p){
        inknown ++;
    }
    Update(inknown,p);
    
    if(known.size() == 0){
        /* insert known */
        known.push_back(make_pair(id,p));
        MakeAns(ans);
        return ans;
    }
    
    if (inknown == 0){
        
        //do not have something on the left
        if (!compare(id, known[inknown].first)){
            //compare with right and need to be concealed
            MakeConceal(id,p,inknown,ans);
            known.erase(known.begin() + inknown);
            return ans;
        }
    }
    else if (inknown == known.size()){
        //do not have something on the right
        if (!compare(known[inknown-1].first, id)){
            MakeConceal(id,p,inknown-1,ans);
            known.erase(known.begin() + inknown-1);
            return ans;
        }
    }
    else{
        //consider both side
        
        if (!compare(known[inknown-1].first, id)){
            MakeConceal(id,p,inknown-1,ans);
            known.erase(known.begin() + inknown-1);
            return ans;
        }
        else if (!compare(id, known[inknown].first)){
            MakeConceal(id,p,inknown,ans);
            known.erase(known.begin() + inknown);
            return ans;
        }
    }
        

    //if don't have to conceal
    known.insert(known.begin() + inknown, std::make_pair(id,p));
    MakeAns(ans);
    return ans;
}
void UpdateConceal(int Pair,int inconceal){
    if(Pair > inconceal){
        conceal.erase(conceal.begin()+Pair);
        conceal.erase(conceal.begin()+inconceal);
    }
    else{
        conceal.erase(conceal.begin()+inconceal);
        conceal.erase(conceal.begin()+Pair);
    }
    return;
}
void addConceal(int inconceal,int PosinKnown){
    conceal[inconceal].first = known[PosinKnown].first;
    conceal[inconceal].second = known[PosinKnown].second;
    known.erase(known.begin() + PosinKnown);
}
std::vector<int> remove(int p) {
    contest.erase(contest.begin() + p);
    vector<int> ans;
    int inknown = 0;
    bool in = false;
    for(inknown = 0;inknown < known.size();inknown ++){
        if (known[inknown].second == p){
            known.erase(known.begin() + inknown);
            in = true;
            break;
        }
    }
    if (in){
        for (int i = inknown; i < known.size(); i++){
            known[i].second --;
        }
        for (int i = 0; i < conceal.size(); i++){
            if (conceal[i].second > p){
                conceal[i].second --;
            }
        }
        MakeAns(ans);
        return ans;
    }
    //find contest in conceal
    int inconceal = 0;
    for(int i = 0;i < conceal.size();i ++){
        if(conceal[i].second == p){
            inconceal = i;
            break;
        }
    }
    int Pair;
    if(inconceal % 2 == 0){
        Pair = inconceal+1;
    }
    else{
        Pair = inconceal-1;
    }
    //find the insert position
    int PosinKnown;
    for(PosinKnown = 0;PosinKnown < known.size();PosinKnown ++){
        if(known[PosinKnown].second > conceal[Pair].second){
            break;
        }
    }
    if(known.empty()){
        known.push_back(conceal[Pair]);
        UpdateConceal(Pair,inconceal);
    }
    else if(PosinKnown == 0){
        //nothing on the left
        if(compare(conceal[Pair].first,known[PosinKnown].first)){
            known.insert(known.begin()+PosinKnown,conceal[Pair]);
            UpdateConceal(Pair,inconceal);
        }
        else{
            addConceal(inconceal,PosinKnown);
        }
    }
    else if(PosinKnown == known.size()){
        //nothing on the right
        if(compare(known[PosinKnown-1].first,conceal[Pair].first)){
            known.push_back(conceal[Pair]);
            UpdateConceal(Pair,inconceal);
        }
        else{
            addConceal(inconceal,PosinKnown-1);
        }
    }
    else{
        if(!compare(conceal[Pair].first,known[PosinKnown].first)){
            addConceal(inconceal,PosinKnown);
        }
        else{
            if(!compare(known[PosinKnown-1].first,conceal[Pair].first)){
                addConceal(inconceal,PosinKnown-1);
            }
            else{
                known.insert(known.begin()+PosinKnown,conceal[Pair]);
                UpdateConceal(Pair,inconceal);
            }
        }
    }
    for(int i = 0;i < known.size();i ++){
        if(known[i].second > p){
            known[i].second --;
        }
    }
    for(int i = 0;i < conceal.size();i ++){
        if(conceal[i].second > p){
            conceal[i].second --;
        }
    }
    MakeAns(ans);
    return ans;
}
