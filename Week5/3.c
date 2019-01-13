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

