#include<bits/stdc++.h>
using namespace std;

int func(){
    cout<<"Inside function\n";
    // exit(0);
}

//Called after exit is called
void func2(){
    cout<<"Main Ended\n";
}

int main(){
    if(atexit(func2) != 0){
        cout<<"can't register func2\n";
    }

    cout<<"Main begins\n";
    func();
    cout<<"Ending Main\n";
}