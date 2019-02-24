#include<bits/stdc++.h>

using namespace std;

class ListNode{
public:
    int data;
    ListNode *next;

    ListNode(const int x = -1, ListNode *p = nullptr){
        data = x;
        next = p;
    }
};

int main(){
    int cnt = 100000;
    ListNode *tempNode[cnt];

    chrono::time_point<std::chrono::system_clock> my_startTime, my_endTime;
    my_startTime = chrono::system_clock::now();
    for(int i = 0; i < cnt; i++){
        tempNode[i] = new ListNode;
    }
    my_endTime = chrono::system_clock::now();
    chrono::duration<double> timeTaken = 
                            chrono::duration_cast<chrono::duration<double>>(my_endTime - my_startTime);

    cout<<"Allocation Time: "<<timeTaken.count()/cnt<<endl;

    my_startTime = chrono::system_clock::now();
    for(int i = 0; i < cnt; i++){
        delete tempNode[i];
    }
    my_endTime = chrono::system_clock::now();
    timeTaken =  chrono::duration_cast<chrono::duration<double>>(my_endTime - my_startTime);

    cout<<"Deallocation Time: "<<timeTaken.count()/cnt<<endl;
}