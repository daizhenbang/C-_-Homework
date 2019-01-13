#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;
class hugeInt{
    private:
        string number;
        int sign;//0: positive; 1: negative
    public:
        hugeInt(){}
        hugeInt(string b);
        hugeInt(const hugeInt& b);

        hugeInt& operator=(const hugeInt& b);
        void printNum(){
            if(sign == 0) cout<<number<<endl;
            else cout<<"-"<<number<<endl;
        }
        friend istream& operator>>(istream& is, hugeInt& b);
        friend hugeInt operator+(const hugeInt& a, const hugeInt& b);
        friend hugeInt operator-(const hugeInt& a, const hugeInt& b);
        friend hugeInt operator*(const hugeInt& a, const hugeInt& b);
        friend hugeInt operator/(const hugeInt& a, const hugeInt& b);
};

hugeInt::hugeInt(string b){
    int signPos = b.find("-");
    if (signPos != string::npos){
        sign = 1;
        number = b.substr(signPos+1);
    }
    else{
        sign = 0;
        number = b;
    }
}

hugeInt::hugeInt(const hugeInt& b){
    sign = b.sign;
    number = b.number;
}

hugeInt& hugeInt::operator=(const hugeInt& b){
    sign = b.sign;
    number = b.number;
    return *this;
}

istream& operator>>(istream& is, hugeInt& b){
    string s;
    is>>s;
    int signPos = s.find("-");
    if (signPos != string::npos){
        b.sign = 1;
        b.number = s.substr(signPos+1);
    }
    else{
        b.sign = 0;
        b.number = s;
    }
    return is;
}

hugeInt operator+(const hugeInt& a, const hugeInt& b){
    string tmpString;

    if((a.sign == 0 && b.sign == 0) || (a.sign == 1 && b.sign ==1)){
        int idA = 0;
        int idB = 0;
        int digitA = 0;
        int digitB = 0;
        int higherD = 0;
        int lowerD = 0;
        int digitSum = 0;
        int sizeA = a.number.size();
        int sizeB = b.number.size();
        int minSize = sizeA;
        int maxSize = sizeB;
        string longer = b.number;
        if(sizeB < sizeA){
            minSize = sizeB;
            maxSize = sizeA;
            longer = a.number;
        }

        
        for(int i=1;i<=minSize; i++){
            idA = sizeA - i;
            idB = sizeB - i;
            digitA = atof(a.number.substr(idA,1).c_str());
            digitB = atof(b.number.substr(idB,1).c_str());
            digitSum = digitA + digitB + higherD;
            higherD = digitSum/10;
            lowerD = digitSum%10;

            ostringstream converter;
            converter<<lowerD;
            tmpString.insert(0,converter.str());
        }
        
        int id = 0;
        int digit = 0;
        for(int i=minSize+1; i<=maxSize; i++){
            id = maxSize - i;
            digit = atof(longer.substr(id,1).c_str());
            digitSum = digit + higherD;
            higherD = digitSum/10;
            lowerD = digitSum%10;
            ostringstream converter;
            converter<<lowerD;
            tmpString.insert(0,converter.str());
        }
        if(higherD != 0){
            ostringstream converter;
            converter<<higherD;
            tmpString.insert(0,converter.str());
        }
        if(a.sign == 1){
            tmpString.insert(0,"-");
        }
    }
    else{
        int id = 0;
        int digitS = 0;
        int digitL = 0;
        int higherD = 0;
        int lowerD = 0;
        int digitSum = 0;
        string longer = a.number;
        string shorter = b.number;
        int signIndicator = a.sign; 
        if(a.number.size() < b.number.size()){
            longer = b.number;
            shorter = a.number;
            signIndicator = b.sign;
        }
        else if(a.number.size() == b.number.size()){
            for(int i=0; i<a.number.size();i++){
                digitL = atoi(a.number.substr(i,1).c_str());
                digitS = atoi(b.number.substr(i,1).c_str());
                if(digitL < digitS){
                    longer = b.number;
                    shorter = a.number;
                    signIndicator = b.sign;  
                    break;
                }
                else if(digitL > digitS){
                    signIndicator = a.sign;
                    break;
                }
                else{
                    continue;
                }
            }
        } 
        int offset = longer.size()-shorter.size();
        for(int i=0;i<offset;i++){
            shorter.insert(0,"0");
            //cout<<shorter<<endl;
        }
        for(int i=1;i<=longer.size();i++){
            id = longer.size() - i;
            digitL = atoi(longer.substr(id,1).c_str());
            digitS = atoi(shorter.substr(id,1).c_str());
            lowerD = digitL-digitS+higherD; 
            higherD = 0;
            if(lowerD < 0){
                lowerD = lowerD + 10;
                higherD = -1;
            }
            ostringstream converter;
            converter<<lowerD;
            tmpString.insert(0,converter.str()); 
        }
        int currentSize = tmpString.size();
        for(int i=0; i<currentSize-1;i++){
            if(tmpString.substr(0,1) == "0"){
                tmpString.erase(0,1);
            }
            else{
                break;
            }
        }
        if (tmpString == "0") signIndicator = 0;
        //Determine the final sign
        string finalSign;
        if(a.number.size() > b.number.size()){
            if(a.sign == 1) finalSign = "-";
            else finalSign = "";
        }
        else if (a.number.size() < b.number.size()){
            if(a.sign == 1) finalSign = "";
            else finalSign = "-";
        }
        else{
            if(signIndicator == 1) finalSign = "-";
            else finalSign = "";
        }
        if (finalSign == "-") tmpString.insert(0,"-");
    }
    return hugeInt(tmpString);
}

hugeInt operator-(const hugeInt& a, const hugeInt& b){
    hugeInt temp(b);
    if(temp.sign == 1) temp.sign = 0;
    else temp.sign = 1;
    return a+temp;
};


hugeInt operator*(const hugeInt& a, const hugeInt& b){
    hugeInt longer = a;
    hugeInt shorter = b;
    if(a.number.size()<b.number.size()){
        longer = b;
        shorter = a;
    }
    int sizeShort = shorter.number.size();
    hugeInt result("0"); 
    hugeInt increment("1");
    
    int digit;
    int id = 0;
    int npos = 0;
    for(size_t i=1; i<=sizeShort;i++){
        hugeInt tmpResult("0");
        id = sizeShort - i;
        digit = atoi(shorter.number.substr(id,1).c_str()); 
        for(size_t j=0;j<digit;j++){
            tmpResult = tmpResult + longer;
        }
        for(int j=0; j<i-1; j++){
            tmpResult.number.push_back(0);
        }
        result = result + tmpResult;
    }
    if((a.sign == 0 && b.sign == 0 ) || (a.sign == 1 && b.sign == 1)){
        return result;
    }
    else{
        result.sign = 1;
        return result;
    }
}

hugeInt operator/(const hugeInt& a, const hugeInt& b){
    hugeInt longer = a;
    hugeInt shorter = b;
    int sizeShort = shorter.number.size();
    int sizeLong = longer.number.size();
    if (sizeShort > sizeLong){
        return hugeInt("0");
    }
    if(sizeShort <= 8){
        int shou, quotient[sizeLong-sizeShort+1]={0}, remainder[sizeLong-sizeShort+1]={0};
        int gong = atoi(shorter.number.c_str());
        shou = atoi(longer.number.substr(0,sizeShort).c_str());
        quotient[0] = shou/gong;
        remainder[0] = shou%gong;
        int count = 1;
        for(int i=sizeShort;i<sizeLong;i++){
            shou = atoi(longer.number.substr(i,1).c_str()) + remainder[count-1]*10;
            quotient[count] = shou/gong;
            remainder[count] = shou%gong;
            count += 1;
        }
        
        //Transform to hugeInt
        ostringstream converter;
        for(size_t i=0;i<sizeLong-sizeShort+1;i++){
            converter<<quotient[i]; 
        }
        string tmpString = converter.str();
        for(size_t i=0;i<sizeLong-sizeShort;i++){
            if(tmpString.substr(0,1) == "0"){
                tmpString.erase(0,1);
            }
            else{
                break;
            }
        }
        return hugeInt(tmpString);
    }
    else{
        int quotient[sizeLong-sizeShort+1]={0};
        hugeInt remainder[sizeLong-sizeShort+1];
        hugeInt gong = shorter.number;
        hugeInt shou = longer.number.substr(0,sizeShort);
        hugeInt tmpDiff;
        int count = 0;
        tmpDiff = shou - gong;
        while(tmpDiff.sign == 0){
            count += 1;
            tmpDiff = tmpDiff - gong;
        }
        quotient[0] = count;
        remainder[0] = tmpDiff+gong;
       
        count = 1;
        for(int i=sizeShort;i<sizeLong;i++){
            //cout<<remainder[count].number<<endl;
            shou = hugeInt(longer.number.substr(i,1))+ remainder[count-1]*hugeInt("10");
            tmpDiff = shou-gong;
            int count2 = 0;
            while(tmpDiff.sign == 0){
                count2 += 1;
                tmpDiff = tmpDiff - gong;
            }
            quotient[count] = count2;
            remainder[count] = tmpDiff + gong;
            count += 1;
        }

        //Transform to hugeInt
        ostringstream converter;
        for(size_t i=0;i<sizeLong-sizeShort+1;i++){
            converter<<quotient[i]; 
        }
        string tmpString = converter.str();
        for(size_t i=0;i<sizeLong-sizeShort;i++){
            if(tmpString.substr(0,1) == "0"){
                tmpString.erase(0,1);
            }
            else{
                break;
            }
        }

        return hugeInt(tmpString); 
    }
}

int main(){
    hugeInt a,b,c;
    string op;
    cin>>a>>op>>b;
    if(op == "+") c=a+b;
    else if(op == "-") c=a-b;
    else if(op == "*") c=a*b;
    else if(op == "/") c=a/b;
    else cout<<"Wrong Operator"<<endl;
    c.printNum();
    return 0;
}
