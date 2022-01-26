#include<iostream>
#include<vector>
#include<cstdlib>
#define MAX 9223372036854775807
using namespace std;
int main(){
    int N,M;
    cin >> N >> M;
    vector<long long> nums(N);
    for(int i = 0;i < N;i ++){
        cin >> nums[i];
    }
    long long cut[N][M];
    long long min = MAX;
    bool head[N];
    for(int i = 0;i < N;i ++){
        head[i] = 0;
    }
    int end = (4*N/M > N)? N: 4*N/M;
    for(int i = 0;i < end;i ++){
        while(1){
            int n = rand()%N;
            if(head[n] == 0){
                head[n] = 1;
                break;
            }
        }
    }
    //where to cut;
    for(int start = 0;start < N;start ++){
        if(head[start] == 1){
            for(int i = 0;i < N ;i ++){
                int curr = (start+i)%N;
                int prev = (start+i+N-1)%N;
                int prev2 = (start+i+N-2)%N;
                for(int j = 0;j <= i && j < M ;j ++){
                    if(j == 0){
                        //one segment
                        if(i == 0){
                            //N = 1
                            cut[i][j] = nums[curr];
                        }
                        else if(i == 1){
                            //N = 2
                            cut[i][j] = nums[curr]+nums[prev]-abs(nums[curr]-nums[prev]);
                        }
                        else{
                            cut[i][j] = cut[i-1][j]+nums[curr]-abs(nums[curr]-nums[prev])+nums[prev] * ((nums[prev2] & nums[prev]) ^ (nums[prev] | nums[curr]) ^ (nums[prev2] + nums[curr]));
                        }
                    }
                    else if(i == j){
                        cut[i][j] = cut[i-1][j-1] + nums[curr];
                    }
                    else{
                        long long m,m_1,n_2;
                        //m
                        m = cut[i-1][j]+nums[curr]-abs(nums[curr]-nums[prev])+nums[prev] * ((nums[prev2] & nums[prev]) ^ (nums[prev] | nums[curr]) ^ (nums[prev2] + nums[curr]));
                        //m-1
                        m_1 = cut[i-1][j-1]+nums[curr];
                        //n-2
                        
                        if(i-2 >= j-1){
                            n_2 = cut[i-2][j-1]+nums[curr]+nums[prev]-abs(nums[curr]-nums[prev]);
                            cut[i][j] = (m < m_1)? m:m_1;
                            cut[i][j] = (n_2 < cut[i][j])?n_2:cut[i][j];
                        }
                        else{
                            cut[i][j] = (m < m_1)? m:m_1;
                        }
                        

                    }
                }
            }
            min = (cut[N-1][M-1] < min)? cut[N-1][M-1]:min;
        }
    }
    cout << min << endl;
    return 0;
}