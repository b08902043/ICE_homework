#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
using namespace std;
class Node{
public:
    int group,num;
};
class Group{
public:
    int cordin,parent,index;
};
void Findgroup(vector<Group> &group,int catmove,int &whichgroup){
    //find a root
    if(group[catmove].index == group[catmove].parent){
        whichgroup = group[catmove].index;
        return;
    }
    else{
        Findgroup(group,group[catmove].parent,whichgroup);
    }
    group[catmove].parent = whichgroup;
    return;
}
void init(vector<Group> &group,map<int,Node> &map,int pos){
    map[pos].num = 1;
    map[pos].group = group.size();
    Group newgroup;
    newgroup.cordin = pos;
    newgroup.index = group.size();
    newgroup.parent = group.size();
    group.push_back(newgroup);
    return;
}
int main(){
    int N,Q;
    cin >> N >> Q;
    long long crowdedness = 0;
    map<int,Node> map;
    vector<Group> group;
    vector<int> cat(N+1);
    //init
    for(int i = 1;i < N+1;i ++){
        int tmp;
        cin >> tmp;
        //if the position has been init
        if(map.count(tmp)){
            crowdedness += (long long)map[tmp].num;
            map[tmp].num ++;
            cat[i] = map[tmp].group;
            
        }
        else{
            cat[i] = group.size();
            init(group,map,tmp);
        }
    }

    for(int event = 0;event < Q;event ++){
        int flag;
        cin >> flag;
        if(flag == 1){
            int foodpos,radius;
            cin >> foodpos >> radius;
            int start = (foodpos-radius > 0)? foodpos-radius:0;
            long long end = foodpos+radius;
            end = (end < 1000000000)? end:1000000000;
            int whichgroup;
            //find food position is in which group
            if(!map.count(foodpos)){
                whichgroup = group.size();
                init(group,map,foodpos);
                map[foodpos].num --;
            }
            else{
                whichgroup = map[foodpos].group;
            }
            auto it = map.lower_bound(start);
            vector<int> remove;
            //merge group
            while(it != map.end() && (*it).first <= (int)end){
                auto next_it = it;
                next_it ++;
                if((*it).first != foodpos){
                    group[map[(*it).first].group].parent = whichgroup;
                    crowdedness += ((long long)map[(*it).first].num * (long long)map[foodpos].num);
                    map[foodpos].num += map[(*it).first].num;
                    (*it).second.num = 0;
                    map.erase((*it).first);
                } 
                it = next_it;
            }
            cout << crowdedness << "\n";
        }
        else{
            int catmove,newpos;
            cin >> catmove >> newpos;
            //find this cat is in which group
            int whichgroup;
            Findgroup(group,cat[catmove],whichgroup);
            //check whether the oldpos will be empty after moving
            int oldpos = group[whichgroup].cordin;
            if(map[oldpos].num > 1){
                crowdedness -= (map[oldpos].num-1);
                map[oldpos].num --;
            }
            else{
                map.erase(oldpos);
            }
            
            //check whether the newpos is empty
            if(!map.count(newpos)){
                cat[catmove] = group.size();
                init(group,map,newpos);                
            }
            else{
                cat[catmove] = map[newpos].group;
                crowdedness += map[newpos].num;
                map[newpos].num ++;
                
            }
            cout << crowdedness << "\n";
        }
    }
    return 0;
}