#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
    Complex& operator=(string s){
        size_t pos1 = s.find("+");
        size_t pos2 = s.find("i");
        string sReal = s.substr(0,pos1);
        string sImagine = s.substr(pos1+1,pos2);
        r = atof(sReal.c_str());
        i = atof(sImagine.c_str());
        return *this;
    }

};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
