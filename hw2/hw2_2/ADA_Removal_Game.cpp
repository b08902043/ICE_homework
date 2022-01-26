#include<iostream>
#include<unordered_map>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

int GCD(int a,int b){
    int gcd = 1;
    int reminder,min;
    while(1){
        if(a%2 == 0 && b% 2 == 0){
            gcd *= 2;
            a = a >> 1;
            b = b >> 1;
        }
        else if(a%2 == 0 && b %2 != 0){
            a = a >> 1;
        }
        else if(a%2 != 0 && b%2 == 0){
            b = b >> 1;
        }
        else{
            reminder = abs(a-b);
            min = (a < b)? a:b;
            a = (reminder > min)? reminder:min;
            b = (reminder <= min)? reminder:min;
        }
        if(b == 0) return (a*gcd);
    }
    return a;
}


int main(){
    int N;
    cin >> N;
    int arr[N];
    for(int i = 0;i < N;i ++){
        cin >> arr[i];        
    }
    long long ans;
    unordered_map<string ,int > gcd_map;
    string tmpstring;
    int gcd[N][N];
    for(int i = 0;i < N-1;i ++){
        for(int j = i;j < N;j ++){
            gcd[i][j] = GCD(arr[i],arr[j]);
            gcd[j][i] = gcd[i][j];
        }
    }
    long long dp[N][N];
    long long max;
    for(int i = 0;i < N;i ++){
        for(int j = 0;j < N;j ++){
            dp[i][j] = 1;
        }
    }
    for(int i = 1;i < N;i ++){
        for(int j = 0;j < N-i;j ++){
            if(i == 1){
                dp[j][j+i] = gcd[j][j+i];
            }
            else if(i == 2){
                if(gcd[j][j+1] != 1 && gcd[j+1][j+2] != 1 && gcd[j][j+2] != 1){
                    dp[j][j+i] = gcd[j][j+1]+gcd[j+1][j+2];
                }    
                else{
                    dp[j][j+i] = 1;
                }
            }
            else{
                
                dp[j][j+i] = 1;
                max = 1;
                //( )( )
                for(int k = j+1;k < i+j-1;k ++){
                    if(dp[j][k] != 1 && dp[k+1][i+j] != 1){
                        max = (max > dp[j][k]+dp[k+1][i+j])? max: dp[j][k]+dp[k+1][i+j];
                    }       
                }
                //a( )b
                if(dp[j+1][i+j-1] != 1){
                    if(gcd[j][j+i] != 1){
                        max = (max > dp[j+1][j+i-1]+gcd[j][j+i])? max: dp[j+1][j+i-1]+gcd[j][j+i];
                    }
                }
                //a( )b( )c
                for(int k = j+3;k < j+i-1;k ++){
                    if(dp[j+1][k-1] != 1 && dp[k+1][i+j-1] != 1){
                        if(gcd[j][k] != 1 && gcd[k][j+i] != 1 && gcd[j][j+i] != 1){
                            int tmp = gcd[j][k]+gcd[k][j+i];
                            max = (max > tmp+dp[j+1][k-1]+dp[k+1][i+j-1])? max:tmp+dp[j+1][k-1]+dp[k+1][i+j-1];
                        }  
                    }
                }
                //ab( )c
                if(dp[j+2][j+i-1] != 1){
                    if(gcd[j][j+1] != 1 && gcd[j+1][j+i] != 1 && gcd[j][j+i] != 1){
                        int tmp = gcd[j][j+1]+gcd[j+1][j+i];
                        if(tmp != 1){
                            max = (max > tmp+dp[j+2][j+i-1])? max:tmp+dp[j+2][j+i-1];
                        }
                    }  
                }
                //a( )bc
                if(dp[j+1][j+i-2] != 1){
                    if(gcd[j][j+i-1] != 1 && gcd[j+i-1][j+i] != 1 && gcd[j][j+i] != 1){
                        int tmp = gcd[j][j+i-1]+gcd[j+i-1][j+i];
                        if(tmp != 1){
                            max = (max > tmp+dp[j+1][j+i-2])? max:tmp+dp[j+1][j+i-2];
                        }
                    } 
                }
                dp[j][j+i] = max;
            }
        }
        
    }
    if(dp[0][N-1] == 1){
        cout << -1 << endl;
    }
    else{
        cout << dp[0][N-1] << endl;
    }
    
    return 0;
}