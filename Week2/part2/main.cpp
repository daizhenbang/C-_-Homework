#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class CStudent{
    private:
        char* name;
        int age, id;
        unsigned int g1,g2,g3,g4,ave;
    public:
        CStudent(char* _name, int _age, int _id, unsigned int _g1, unsigned _g2, unsigned _g3, unsigned _g4, unsigned _ave=0):
            name(_name),age(_age),id(_id),g1(_g1),g2(_g2),g3(_g3),g4(_g4),ave(_ave){}//Constructor
        
        void AveCalculator(){
            ave = (g1+g2+g3+g4)/4;
        }//Calculate the average score

        void printInfo(){
            cout<<name<<","<<age<<","<<id<<","<<ave<<endl;
        }//Print the information

};


int main(){
    char* Name;
    int _age, _id;
    unsigned int _g1,_g2,_g3,_g4;
    
    string input;
    cin>>input;
    size_t pos = 0;
    vector<string> token;
    while ((pos=input.find(',')) != string::npos){
        token.push_back(input.substr(0,pos));
        input.erase(0,pos+1);
    }
    Name = &token[0][0u];
    _age = atoi( token[1].c_str() ); 
    _id = atoi( token[2].c_str());
    _g1 = (unsigned int)atoi( token[3].c_str());
    _g2 = (unsigned int)atoi( token[4].c_str());
    _g3 = (unsigned int)atoi( token[5].c_str());
    _g4 = (unsigned int)atoi( input.c_str());

    CStudent student(Name,_age,_id,_g1,_g2,_g3,_g4);
    student.AveCalculator();
    student.printInfo();
    
    return 0;
}

