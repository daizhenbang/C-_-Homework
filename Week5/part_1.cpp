#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;
// 在此处补充你的代码
#include <string>
#define qsort(a,b,c,d) myqsort(a,b,c,d)

class MyString:public string{
public:
        MyString(){}
        MyString(const string& str);
        MyString(const MyString& str);
        MyString(const string& str, size_t pos, size_t len = npos);
        MyString (const char* s);
        MyString (const char* s, size_t n);
        MyString (size_t n, char c);
        MyString operator()(int pos, int len);
        friend bool operator<(const MyString& a, const MyString& b);
        friend bool operator>(const MyString& a, const MyString& b);
        friend bool operator==(const MyString& a, const MyString& b);
};

MyString::MyString(const string& str):string(str){}
MyString::MyString(const MyString& str):string(str){}
MyString::MyString(const string& str, size_t pos, size_t len):string(str,pos,len){}
MyString::MyString (const char* s):string(s){}
MyString::MyString (const char* s, size_t n):string(s,n){}
MyString::MyString (size_t n, char c):string(n,c){}

//Operator overloading
MyString MyString::operator()(int pos, int len){
    return MyString((string::substr(pos,len)).string::c_str());
}

bool operator<(const MyString& a, const MyString& b){
    // return int(a.substr(0,1).c_str()) < int(b.substr(0,1).c_str());
    return int(a.at(0)) < int(b.at(0));
}

bool operator>(const MyString& a, const MyString& b){
    // return int(a.substr(0,1).c_str()) > int(b.substr(0,1).c_str());
    return int(a.at(0)) > int(b.at(0));
}

bool operator==(const MyString& a, const MyString& b){
    // return int(a.substr(0,1).c_str()) == int(b.substr(0,1).c_str());
    return int(a.at(0)) == int(b.at(0));
}


void myqsort(MyString* base, int nelem, int width, int ( *pfCompare)(const void *, const void *)){
    MyString* tmpString = new MyString[nelem];
    for(int i=0; i<nelem; i++){
        tmpString[i] = *(base+i);
    }
    for(int i=0; i<nelem; i++){
        for(int j=i+1;j<nelem;j++){
            if(pfCompare(&tmpString[j],&tmpString[i]) <= 0){
                MyString temp = tmpString[i];
                tmpString[i] = tmpString[j];
                tmpString[j] = temp;
            }
        }
    }
    for(int i=0; i<nelem; i++){
        *(base+i) = tmpString[i];
    }
}
//End of operator overloading

int CompareString( const void * e1, const void * e2) {
    MyString * s1 = (MyString * ) e1;
    MyString * s2 = (MyString * ) e2;
    if( *s1 < *s2 )     return -1;
    else if( *s1 == *s2 ) return 0;
    else if( *s1 > *s2 ) return 1;
}
int main() {
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;

    qsort(SArray,4,sizeof(MyString), CompareString);
    for( int i = 0;i < 4;++i )
        cout << SArray[i] << endl;
    //输出s1从下标0开始长度为4的子串
    cout << s1(0,4) << endl;
    //输出s1从下标为5开始长度为10的子串
    cout << s1(5,10) << endl;
    return 0;
}
