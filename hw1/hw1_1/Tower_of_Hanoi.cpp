#include<iostream>
#include<string>
#include<queue>
using namespace std;
string Process(int N,queue<int> *polls,int position,int &plus){
    string ans;
    bool move = false;
    int move_to;
    for(int i = N;i > 0;i --){
        for(int j = 0;j < 3;j ++){
            if(polls[j].front() == i){
                if(move){
                    if(j != move_to && j != position){
                        move = false;
                        position = j;
                        move_to = j;
                        ans.push_back('0');
                    }
                    else{
                        move_to = 3-move_to-position;
                        position = j;
                        ans.push_back('1');
                    }
                }
                else{
                    if(j != position){
                        ans.push_back('1');
                        move = true;
                    }
                    else{
                        ans.push_back('0');
                    }
                    move_to = position;
                    position = j;
                }
                polls[j].pop();
            }
        }
    }
    return ans;
}
int main(){
    int N;
    cin >> N;
    queue<int> polls[3];
    queue<int> tempq[3];
    int nums;
    for(int i = 0;i < 3;i ++){
        int temp;
        cin >> nums;
        for(int j = 0;j < nums;j ++){
            cin >> temp;
            polls[i].push(temp);
            tempq[i].push(temp);
        }
    }
    int plus1 = 0,plus2 = 0;
    string back = Process(N,polls,0,plus1);
    string front = Process(N,tempq,2,plus2);
    //cout << back << "\n" << front << endl;
    bool correct = true;
    int length = back.length();
    for(int i = 0;i < length;i ++){
        if(back[length-1-i]-'0' + front[length-1-i] -'0' != 1){
            cout << -1 << endl;
            correct = false;
            break;
        }
    }
    long long count = 0;
    if(correct){
        for(int i = 0;i < length;i ++){
            count = count << 1;
            count += front[i]-'0';
            count %= 998244353;
        }
        cout << count << endl;
    }
    return 0;
}