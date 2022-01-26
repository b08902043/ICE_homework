#include<iostream>
#include<vector>
using namespace std;
class Max{
public:
    int start,end;
    long long max;
};
int main(){
    int N;
    bool flag;
    cin >> N >> flag;
    for(int i = 0;i < N;i ++){
        int num;
        cin >> num;
        vector<int> index(num,-1);
        long long maxpos = -1000000001,maxneg = -1000000001;
        int indexp,indexn;
        for(int j = 0;j < num;j ++){
            long long candy;
            cin >> candy;
            if(candy > 0){
                if(maxneg+candy > candy){
                    if(maxneg+candy > maxpos){
                        maxpos = maxneg+candy;
                        index[j] = indexn;
                        indexp = j;
                    }
                }
                else{
                    if(candy > maxpos){
                        maxpos = candy;
                        indexp = j;
                    }
                }
            }
            else if(candy < 0){
                if(maxpos+candy > candy){
                    if(maxpos+candy > maxneg){
                        maxneg = maxpos+candy;
                        indexn = j;
                        index[j] = indexp;
                    }
                }
                else{
                    if(candy > maxneg){
                        maxneg = candy;
                        indexn = j;
                    }
                }
            }
            else{
                if(maxpos > maxneg){
                    if(maxpos > 0){
                        maxneg = maxpos;
                        indexn = j;
                        index[j] = indexp; 
                    }
                    else{
                        maxneg = 0;
                        maxneg = 0;
                        indexn = j;
                        indexp = j;
                    }
                }
                else{
                    if(maxneg > 0){
                        maxpos = maxneg;
                        indexp = j;
                        index[j] = indexn;
                    }
                    else{
                        maxneg = 0;
                        maxneg = 0;
                        indexn = j;
                        indexp = j;
                    }
                }
            }
        }      
        if(maxneg > maxpos){
            cout << maxneg << endl;
            if(flag){
                vector<int> ans;
                while(indexn != -1){
                    ans.push_back(indexn);
                    indexn = index[indexn];
                }
                cout << ans.size() << " ";
                for(int k = ans.size()-1;k >= 0;k --){
                    cout << ans[k]+1 << " ";
                }
                cout << endl;
            }
        }  
        else{
            cout << maxpos << endl;
            if(flag){
                vector<int> ans;
                while(indexp != -1){
                    ans.push_back(indexp);
                    indexp = index[indexp];
                }
                cout << ans.size() << " ";
                for(int k = ans.size()-1;k >= 0;k --){
                    cout << ans[k]+1 << " ";
                }
                cout << endl;
            }
        }
    }
}