#include<iostream>
#include<limits>
#include<string>
#include<cmath>
#include<vector>
#include<math.h> 
#include<queue>
#define Min -9223372036854775807
using namespace std;
typedef long long int ll;
class Square{
public:
    int i,j;
    Square(){}
    Square(int _i,int _j):i(_i), j(_j){}
};
int base(double a,double b){
    return log(a)/log(b);
}
int main(){
    int N;
    cin >> N;
    for(int num = 0;num < N;num ++){
        ll n,m,k;
        cin >> n >> m >> k;
        vector<ll> **map;
        vector<Square> **preSquare;
        preSquare = new vector<Square> *[n];
        for(int i = 0;i < n;i ++){
            preSquare[i] = new vector<Square> [m]; 
        }
        map = new vector<ll> *[n];
        for(int i = 0;i < n;i ++){
            map[i] = new vector<ll> [m];
        }
        string tmp;
        Square curr;
        vector<Square> **prestep;
        prestep = new vector<Square> *[n];
        for(int i = 0;i < n;i ++){
            prestep[i] = new vector<Square> [m];
        }
        // dp map and previous step 
        for(int i = 0;i < n;i ++){
            for(int j = 0;j < m;j ++){
                cin >> tmp;
                if(tmp == "X"){
                    map[i][j].push_back(Min);
                }
                else{
                    map[i][j].push_back(stoll(tmp, nullptr, 10));
                }
                preSquare[i][j].push_back(Square(i,j));
            }
        }
        //find log_k
        for(int i = 0;i < n;i ++){
            for(int j = 0;j < m;j ++){
                //log_k : small triangle len
                double log_k = 1;
                //next_k : big triangle len
                double next_k = 2;
                //count : index in vector
                int count = 1;
                //flag : if big triangle is made
                bool flag = true;
                for(int l = 1;l < k+1;l ++){
                    if(i-1 < 0 && j-1 < 0){
                        map[i][j].push_back(Min);
                        preSquare[i][j].push_back(Square(i,j));
                    }
                    else if(i-1 < 0){
                        map[i][j].push_back(map[i][j-1][l-1]);
                        preSquare[i][j].push_back(Square(preSquare[i][j-1][l-1]));
                    }
                    else if(j-1 < 0){
                        map[i][j].push_back(map[i-1][j][l-1]);
                        preSquare[i][j].push_back(Square(preSquare[i-1][j][l-1]));
                    }
                    else{
                        if(map[i][j-1][l-1] > map[i-1][j][l-1]){
                            map[i][j].push_back(map[i][j-1][l-1]);
                            preSquare[i][j].push_back(Square(preSquare[i][j-1][l-1]));   
                        }
                        else{
                            map[i][j].push_back(map[i-1][j][l-1]);
                            preSquare[i][j].push_back(Square(preSquare[i-1][j][l-1]));
                        }
                    }
                }
                ll max = Min;
                for(int l = 1;l < k+1;l ++){
                    if(max < map[i][j][l]){
                        max = map[i][j][l];
                        if(prestep[i][j].empty()){
                            prestep[i][j].push_back(Square(preSquare[i][j][l].i,preSquare[i][j][l].j));
                        }
                        else{
                            prestep[i][j][0].i = preSquare[i][j][l].i;
                            prestep[i][j][0].j = preSquare[i][j][l].j;
                        }
                        
                    }
                    
                }
                if(max == Min || map[i][j][0] == Min){
                    if(max == Min){
                        if(prestep[i][j].empty()){
                            prestep[i][j].push_back(Square(i,j));
                        }
                        else{
                            prestep[i][j][0].i = i;
                            prestep[i][j][0].j = j;
                        }
                    }
                    if(i != 0 || j != 0){
                        map[i][j][0] = Min;

                    }
                }
                else{
                    map[i][j][0] += max;
                }
            }
            
        }
        
        Square ans;
        vector<pair<int,int> > a;
        if(map[n-1][m-1][0] == Min){
            cout << "Impassable" << endl;
        }
        else{
            cout << "Passable" << endl;
            cout << map[n-1][m-1][0] << endl;
            ans.i = n-1;
            ans.j = m-1;
            pair<int,int> pos;
            pos.first = ans.i+1;
            pos.second = ans.j+1;
            a.push_back(pos);
            while(ans.i != 0 || ans.j != 0){
                int tmpi = ans.i;
                int tmpj = ans.j;
                ans.i = prestep[tmpi][tmpj][0].i;
                ans.j = prestep[tmpi][tmpj][0].j;
                pos.first = ans.i+1;
                pos.second = ans.j+1;
                a.push_back(pos);
            }
            cout << a.size() << endl;
            while(!a.empty()){
                cout << a.back().first << " " << a.back().second << endl;
                a.pop_back();
            }
        }
    }
}