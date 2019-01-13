#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct warrior{ 
    std::string name;
    int life;
    int strength;
};

class headquarter{
    private: 
        std::vector<warrior> sequence;
        std::string name; //red or blue
        int totLife;
        int selfIndex; //The index of all warriors in each headquarter
        int controlIndex;
        int MinLife;
        int vigor;//It's unable to generate more warriors if the vigor is zero.
        std::vector<warrior> dragon;
        std::vector<warrior> ninja;
        std::vector<warrior> iceman;
        std::vector<warrior> lion;
        std::vector<warrior> wolf;
    public:
        headquarter(std::string _name, int _totLife, std::vector<warrior> _sequence):name(_name),totLife(_totLife),sequence(_sequence){
            controlIndex = -1;
            selfIndex = -1;
            vigor = 1;
        }
        void minLife();
        bool generate();
};


void headquarter::minLife(){
    MinLife = 100000000;
    for(size_t i=0; i<sequence.size();i++){
        if(MinLife > sequence[i].life){
            MinLife = sequence[i].life;
        }
    }
}
bool headquarter::generate(){ 
    if(vigor == 0){ 
        return false; 
    } 
    selfIndex += 1;
    controlIndex += 1;
    int seqIndex = controlIndex%5;
    int actualIndex = -1;
    std::string warriorName;
    if (sequence[seqIndex].life <= totLife){
        warriorName = sequence[seqIndex].name;
        actualIndex = seqIndex;
        controlIndex = seqIndex;
    }
    else{
        for(size_t i=seqIndex+1; i<sequence.size();i++){
            if(sequence[i].life <= totLife){
                warriorName = sequence[i].name;
                actualIndex = i;
                controlIndex = i;
                break;
            }
        }
        if(actualIndex == -1){
            for(size_t i=0;i<seqIndex;i++){
                if(sequence[i].life <= totLife){
                    actualIndex = i;
                    controlIndex = i;
                    warriorName = sequence[i].name;
                    break;
                }
            }
        }
    }
    //make sure that there is at least one warrior that is added
    if(actualIndex != -1){
        totLife -= sequence[actualIndex].life;
        int certainWarrior = 0;
        int warriorIndex = 0;
        
        if(warriorName == "dragon"){ 
            dragon.push_back(sequence[actualIndex]);
            warriorIndex = dragon.size();
        }
        else if(warriorName == "ninja"){
            ninja.push_back(sequence[actualIndex]);
            warriorIndex = ninja.size();  
        }
        else if(warriorName == "iceman"){
            iceman.push_back(sequence[actualIndex]);
            warriorIndex = iceman.size(); 
        }
        else if(warriorName == "lion"){ 
            lion.push_back(sequence[actualIndex]);
            warriorIndex = lion.size(); 
        }
        else if(warriorName == "wolf"){ 
            wolf.push_back(sequence[actualIndex]);
            warriorIndex = wolf.size(); 
        }
        
        cout<<setfill('0')<<setw(3)<<selfIndex<<" "<<name<<" "<<warriorName<<" "<<selfIndex+1<<" born with strength "<<sequence[actualIndex].life;
        cout<<","<<warriorIndex<<" "<<warriorName<<" "<<"in "<<name<<" headquarter"<<endl; 
        return true;
    }
    else{
        cout<<setfill('0')<<setw(3)<<selfIndex<<" "<<name<<" headquarter stops making warriors"<<endl;
        vigor = 0;        
        return false;
    }
}

int main(){ 
    
    int caseNum;
    cin>>caseNum; 
    int* TotalLife = new int[caseNum];
    int* l1 = new int[caseNum];  
    int* l2 = new int[caseNum]; 
    int* l3 = new int[caseNum]; 
    int* l4 = new int[caseNum]; 
    int* l5 = new int[caseNum]; 
    for (size_t i=0;i<caseNum;i++){
        cin>>TotalLife[i]; 
        cin>>l1[i]>>l2[i]>>l3[i]>>l4[i]>>l5[i]; 
    }

    for (size_t i=0;i<caseNum; i++){
        std::vector<warrior> seqRed,seqBlue;
        warrior w1,w2,w3,w4,w5;
        w1.name = "iceman"; w1.life = l3[i];
        w2.name = "lion"; w2.life = l4[i];
        w3.name = "wolf"; w3.life = l5[i];
        w4.name = "ninja"; w4.life = l2[i];
        w5.name = "dragon"; w5.life = l1[i];
        
        seqRed.push_back(w1);
        seqRed.push_back(w2);
        seqRed.push_back(w3);
        seqRed.push_back(w4);
        seqRed.push_back(w5);

        seqBlue.push_back(w2);
        seqBlue.push_back(w5);
        seqBlue.push_back(w4);
        seqBlue.push_back(w1);
        seqBlue.push_back(w3);
        
        headquarter red("red",TotalLife[i],seqRed);
        headquarter blue("blue",TotalLife[i],seqBlue);
        red.minLife(); blue.minLife();
        
        cout<<"Case:"<<i+1<<endl;
        
        
        bool indi1, indi2;
        indi1 = red.generate();
        indi2 = blue.generate();
        while(indi1 || indi2){ 
            indi1 = red.generate();
            indi2 = blue.generate(); 
        }
    }
    return 0;
}   
