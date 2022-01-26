#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool cmp1(pair<int,int>a,pair<int,int>b)
{
	return a.first < b.first;
}
void FindUpBond(int val,int &upbond,int left,int right,vector<pair<int,int> > &l_up){

	if(right-left < 1){
		return;
	}
	if(right-left == 1){
		if(l_up[left].first > val){
			upbond = l_up[left].second;
		}
		return;
	}
	int middle = (left+right)/2;
	if(l_up[middle].first < val && l_up[middle-1].first > val){
		upbond = l_up[middle-1].second;
		return;
	}
	if(l_up[middle].first > val){
		FindUpBond(val,upbond,middle,right,l_up);
		return;
	}
	if(l_up[middle-1].first < val){
		FindUpBond(val,upbond,left,middle,l_up);
		return;
	}
	return;				
	
}
void FindDownBond(int val,int &downbond,int left,int right,vector<pair<int,int> > &l_down){	
	if(right-left < 1){
		return;
	}
	if(right-left == 1){ 
		if(l_down[left].first > val){
			downbond = l_down[left].second;
		}
		return;
	}
	int middle = (left+right)/2;
	if(l_down[middle].first < val && l_down[middle-1].first > val){
		downbond = l_down[middle-1].second;
		return;
	}
	if(l_down[middle].first > val){
		FindDownBond(val,downbond,middle,right,l_down);
		return;
	}
	if(l_down[middle-1].first < val){
		FindDownBond(val,downbond,left,middle,l_down);
		return;
	}
	return;
}
void FindUpNum(int upbond,int &rup,int left,int right,vector<pair<int,int> > &r_up){
	if(right-left < 1) return;
	if(right-left == 1){
		if(left == 0 && r_up[left].second < upbond){
			rup = 0;
		}
		return;
	}
	int middle = (left+right)/2;
	if(r_up[middle].second < upbond && r_up[middle-1].second > upbond){
		rup = middle;
		return;
	}
	if(r_up[middle].second > upbond){
		FindUpNum(upbond,rup,middle,right,r_up);
		return;
	}
	if(r_up[middle-1].second < upbond){
		FindUpNum(upbond,rup,left,middle,r_up);
		return;
	}
	return;
}
void FindDownNum(int downbond,int &rdown,int left,int right,vector<pair<int,int> > &r_down){
	if(right-left < 1)return;
	if(right-left == 1){
		if(left == 0 && r_down[left].second > downbond){
			rdown = 0;
		}
		return;
	}
	int middle = (left+right)/2;
	if(r_down[middle].second > downbond && r_down[middle-1].second < downbond){
		rdown = middle;
		return;
	}	
	if(r_down[middle].second < downbond){
		FindDownNum(downbond,rdown,middle,right,r_down);
		return;
	}
	if(r_down[middle-1].second > downbond){
		FindDownNum(downbond,rdown,left,middle,r_down);
		return;
	}
	return;
}
vector<pair<int,int> > SearchDot(long long &count,vector<pair<int,int> > &v,int left,int right){
	vector<pair<int,int> > ans;
	if(right-left == 0){
		return ans;
	}
	if(right-left == 1){
		ans.push_back(v[left]);
		return ans;
	}
    int middle = (right+left)/2;
	vector<pair<int,int> > l = SearchDot(count,v,left,middle);
	vector<pair<int,int> > r = SearchDot(count,v,middle,right);
    vector<pair<int,int> > l_up,l_down,r_up,r_down;
    /*
	cout << endl;
    for(int i = 0;i < l.size();i ++){
		cout << l[i].first << " " << l[i].second << endl;
	}
	for(int i = 0;i < r.size();i ++){
		cout << r[i].first << " " << r[i].second << endl;
	}
	*/
    //down_to_up
	int rdownindex = 0;
    for(int i = 0;i < l.size();i ++){
		int downbond = -1,rdown = r_down.size();
        while(rdownindex < r.size() && r[rdownindex].second < l[i].second){
            if(!r_down.empty()){
                while(!r_down.empty() && r_down.back().first > r[rdownindex].first){
                    r_down.pop_back();
                }
            }
            r_down.push_back(r[rdownindex]);
            rdownindex ++;
        }
        FindDownBond(l[i].first,downbond,0,l_down.size(),l_down);
		FindDownNum(downbond,rdown,0,r_down.size(),r_down);
		count += (r_down.size()-rdown);
		if(l_down.empty()){
			l_down.push_back(l[i]);
		}
		else{
			while(!l_down.empty() &&l[i].first > l_down.back().first){
				l_down.pop_back();
			}	
			l_down.push_back(l[i]);
		}
    }
	//up_to_down
	int rupindex = r.size()-1;
	for(int i = l.size()-1;i >= 0;i --){
		int upbond = v.size()+1,rup = r_up.size();
		while(rupindex >= 0  && r[rupindex].second > l[i].second){
            if(!r_up.empty()){
                while(!r_up.empty() && r_up.back().first > r[rupindex].first){
                    r_up.pop_back();
                }
            }
            r_up.push_back(r[rupindex]);
            rupindex --;
        }
		FindUpBond(l[i].first,upbond,0,l_up.size(),l_up);
		FindUpNum(upbond,rup,0,r_up.size(),r_up);
		count += (r_up.size()-rup);
		if(l_up.empty()){
			l_up.push_back(l[i]);
		}
		else{
			while(!l_up.empty() && l[i].first > l_up.back().first){
				l_up.pop_back();
			}
			l_up.push_back(l[i]);
		}
	}
    int lcount = 0,rcount = 0;
	while(lcount != l.size() && rcount != r.size()){
		if(l[lcount].second < r[rcount].second){
			ans.push_back(l[lcount]);
			lcount ++;
		}
		else{
			ans.push_back(r[rcount]);
			rcount ++;
		}
	}
	while(lcount != l.size()){
		ans.push_back(l[lcount]);
		lcount ++;
	}
	while(rcount != r.size()){
		ans.push_back(r[rcount]);
		rcount ++;
	}
	return ans;
}
int main(){ 
    int N;
	cin >> N;
	vector<pair<int,int> > v;
	for(int i = 0;i < N;i ++){
		pair<int,int> temp;
		cin >> temp.first >> temp.second;
		v.push_back(temp);
	}
	sort(v.begin(),v.end(),cmp1);
	long long count = 0;
	SearchDot(count,v,0,v.size());
	cout << count << endl;
	return 0;
}