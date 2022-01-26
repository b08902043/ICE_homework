#include<iostream>
#include <vector>
#include<algorithm>
using namespace std;
bool cmp1(pair<long long,long long>a,pair<long long,long long>b)
{
    return a.second < b.second;
}
bool cmp2(pair<long long,long long>a,pair<long long,long long>b)
{
    return a.first < b.first;
}
vector<pair<long long,long long> > Merge(long long &count,int start,int end,vector<pair<long long,long long> > &v,long long a,long long b,long long c){
    vector<pair<long long,long long> > ans;
    if(start >= end){
        return ans;
    }
    if(end- start == 1){
        ans.push_back(v[start]);
        return ans;
    }
    int middle = (start+end)/2;
    while(middle < end){
        if(v[middle-1].second == v[middle].second) middle ++;
        else break;
    }
    if(middle == end){
        middle = (start+end)/2-1;
        while(middle > start){
            if(v[middle-1].second == v[middle].second) middle --;
            else break;
        }
    }
    if(middle == start){
        vector<pair<long long,long long> > sub = {&v[start],&v[end]};
        sort(sub.begin(),sub.end(),cmp2);
        return sub;
    }
    vector<pair<long long,long long> > right = Merge(count,middle,end,v,a,b,c);
    vector<pair<long long,long long> > left= Merge(count,start,middle,v,a,b,c);
    int leftIndex = 0,rightIndex = 0;
    while(leftIndex != left.size() && rightIndex != right.size()){
        if(right[rightIndex].first * a <= left[leftIndex].first*b+c || right[rightIndex].second == left[leftIndex].second){
            rightIndex ++;
            count += leftIndex;
        }
        else leftIndex ++;
    }
    while(rightIndex != right.size()){
        count += left.size();
        rightIndex ++;
    }
    leftIndex = 0,rightIndex = 0;
    while(leftIndex != left.size() && rightIndex != right.size()){
        if(left[leftIndex].first < right[rightIndex].first){
            ans.push_back(left[leftIndex]);
            leftIndex ++;
        }
        else{
            ans.push_back(right[rightIndex]);
            rightIndex ++;
        }
    }
    while(leftIndex != left.size()){
        ans.push_back(left[leftIndex]);
        leftIndex ++;
    }
    while(rightIndex != right.size()){
        ans.push_back(right[rightIndex]);
        rightIndex ++;
    }
    return ans;
}
int main(){
    int N;
    long long a,b,c;
    cin >> N >> a >> b >> c;
    vector<pair<long long,long long> > v;
    for(int i = 0;i < N;i ++){
        pair<long,long> temp;
        cin >> temp.first >> temp.second;
        v.push_back(temp);
    }
    sort(v.begin(),v.end(),cmp1);
    long long count = 0;
    vector<pair<long long,long long> > ans;
    ans = Merge(count,0,N,v,a,b,c);
    cout << count << endl;
    return 0;
}