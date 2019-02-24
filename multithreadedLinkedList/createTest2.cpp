//99.9% member, 0.05%insert, 0.05% delete
#include<bits/stdc++.h>
using namespace std;

string opIns = "insert", opDel = "delete", opMember = "member";

string getOp(){
    int x = rand() % 10000;
    if(x <=9989){
        return opMember;
    }
    else if(x > 9989 && x < 9995){
        return opIns;
    }
    else{
        return opDel;
    }
}

int getVal(){
    return int(rand() % 100000000);
}

int main(){
    srand(time(0));
    int initialInsert = 1000;
    cout<<initialInsert<<endl;
    for(int i = 0; i < initialInsert; i++){
        cout<<getVal()<<endl; 
    }

    int operations = 100000;
    cout<<operations<<endl;
    for(int i = 0; i < operations; i++){
        cout<<getOp()<<" "<<getVal()<<endl;
    }
}