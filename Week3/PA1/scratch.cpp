#include <iostream>
using namespace std;

int main(){
    char** name;
    for(int i=0;i<5;i++){
        name[i] = (char)"ha";
    }
    for (int i=0;i<5;i++){
        cout<<name[i]<<endl;
    }
    return 0;
}
