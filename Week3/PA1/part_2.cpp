#include <iostream>
using namespace std;
class Sample{
public:
    int v;
    Sample(int n):v(n) { }
    Sample(const Sample& old){
        v = 2*old.v;
    }
};
int main() {
    Sample a(5);
    Sample b = a;
    cout << b.v;
    return 0;
}
