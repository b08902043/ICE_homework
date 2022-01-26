#include<iostream>
#include<queue>
#include<vector>
#include<stdbool.h>
#include<algorithm>
typedef long long int ll;
using namespace std;
class Job{
public:
    ll start,end,num,price;
    Job(){}
    Job(ll _start,ll _end,ll _num, ll _price):start(_start), end(_end),num(_num),price(_price){}
}; 
bool cmp(Job a,Job b){
    return a.start < b.start;
}  
bool cmp2(Job a,Job b){
    return a.price < b.price;
}
struct cmp1{
    bool operator() ( Job a, Job b ){
        return a.end > b.end;
        }
};
int main(){
    int N;
    cin >> N;
    vector<Job> job,job_price;
    priority_queue<Job,vector<Job>,cmp1> sort_end;
    Job tmp;
    for(int i = 0;i < N;i ++){
        cin >> tmp.start >> tmp.end >> tmp.num >> tmp.price;
        job.push_back(tmp);
    }
    job_price = job;
    sort(job.begin(),job.end(),cmp);
    sort(job_price.begin(),job_price.end(),cmp2);
    
    ll bonus = 0;
    ll next_t,top_t,val;
    ll price = job_price[0].price;
    ll index = 0;
    ll prev_price = 0;
    
    while(index < job_price.size()){
        ll curr_time ;
        ll end_time;
        bool flag = true;
        for(int i = 0;i < job.size();i ++){
            if(job[i].price >= price){
                if(flag){
                    curr_time = job[i].start;
                    flag = false;
                }
                if(job[i].start == curr_time){ 
                    sort_end.push(job[i]);
                }
                else{
                    next_t = job[i].start; //right time bound
                    vector<Job> tmp_job;
                    while(curr_time < next_t && !sort_end.empty()){
                        top_t = sort_end.top().end; //when top task finish
                        val = sort_end.top().num; // xi of the job
                        // if task finish before next time bound
                        if(top_t < next_t){
                            //compare xi and maxmium unit can be finished in top_t
                            if(val <= top_t-curr_time+1){
                                bonus += val*(price-prev_price);
                                curr_time += val;
                                sort_end.pop();
                            }
                            else{
                                bonus += (top_t-curr_time+1)*(price-prev_price);
                                curr_time = top_t+1;
                                sort_end.pop();
                            }
                        }
                        else{
                            if(val <= next_t-curr_time){
                                bonus += val*(price-prev_price);
                                curr_time += val;
                                sort_end.pop();
                                
                            }
                            else{
                                bonus += (next_t-curr_time)*(price-prev_price);
                                tmp = sort_end.top();
                                tmp.num -= next_t-curr_time;
                                curr_time = next_t;
                                
                                sort_end.pop();
                                tmp_job.push_back(tmp);
                            }
                        }
                    }  
                    
                    while(!tmp_job.empty()){
                        sort_end.push(tmp_job.back());
                        tmp_job.pop_back();
                    }
                    sort_end.push(job[i]);
                    curr_time = job[i].start;       
                }
            }
            
        }
        while(!sort_end.empty()){
            if(sort_end.top().num <= sort_end.top().end-curr_time+1){
                bonus += (sort_end.top().num)*(price-prev_price);
                curr_time += sort_end.top().num;
                sort_end.pop();
            }
            else{
                bonus += (sort_end.top().end-curr_time+1)*(price-prev_price);
                curr_time = sort_end.top().end+1;
                sort_end.pop();
            }
        
        }
        while(index < job_price.size() && job_price[index].price == price){
            index ++;
        }
        if(index < job_price.size()){
            prev_price = price;
            price = job_price[index].price;
        }
        else{
            break;
        }
    }
    
    cout << bonus << endl;
    return 0;
}