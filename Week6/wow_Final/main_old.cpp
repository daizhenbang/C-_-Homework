#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <stdio.h>
using namespace std;

class warrior{
public:
    std::string name;
    int life;
    warrior(){}
    warrior(std::string _name, int _life):name(_name),life(_life){}
    warrior(const warrior& w){name = w.name;life = w.life;}
    void printBasic(int selfIndex,std::string name,std::string warriorName, int Life, int warriorIndex){
        cout<<setfill('0')<<setw(3)<<selfIndex<<" "<<name<<" "<<warriorName<<" "<<selfIndex+1<<" born with strength "<<Life;
        cout<<","<<warriorIndex<<" "<<warriorName<<" "<<"in "<<name<<" headquarter"<<endl;
    }
};

class dragon:public warrior{
public:
    int weapon;
    double morale;
    dragon(){}
    dragon(std::string _name, int _life, int _weapon, double _morale):warrior(_name,_life),weapon(_weapon),morale(_morale){}
    dragon(const warrior& w, int _weapon, double _morale):warrior(w),weapon(_weapon),morale(_morale){}
    dragon(const dragon& d){
        warrior::name = d.name;
        warrior::life = d.life;
        weapon = d.weapon;
        morale = d.morale;
    }
    void printExra(std::string weaponName){
        double remorale = morale*100;
        if( (remorale-floor(remorale)) > (ceil(remorale)- remorale)) remorale = ceil(remorale);
        else remorale = floor(remorale);
        cout<<"It has a "<<weaponName;
        printf(",and it's morale is %.2f\n", remorale/100);
    }
};

class ninjia:public warrior{
public:
    int weapon1;
    int weapon2;
    ninjia(){}
    ninjia(std::string _name, int _life, int _weapon1, int _weapon2):warrior(_name,_life),weapon1(_weapon1),weapon2(_weapon2){}
    ninjia(const warrior& w, int _weapon1, int _weapon2):warrior(w),weapon1(_weapon1),weapon2(_weapon2){}
    ninjia(const ninjia& d){
        warrior::name = d.name;
        warrior::life = d.life;
        weapon1 = d.weapon1;
        weapon2 = d.weapon2;
    }
    void printExra(std::string weaponName1, std::string weaponName2){
        cout<<"It has a "<<weaponName1<<" and a "<<weaponName2<<endl;
    }
};

class iceman:public warrior{
public:
    int weapon;
    iceman(){}
    iceman(std::string _name, int _life, int _weapon):warrior(_name,_life),weapon(_weapon){}
    iceman(const warrior& w, int _weapon):warrior(w),weapon(_weapon){}
    iceman(const iceman& d){
    warrior::name = d.name;
    warrior::life = d.life;
    weapon = d.weapon;
    }
    void printExra(std::string weaponName){
        cout<<"It has a "<<weaponName<<endl;
    }
};

class lion:public warrior{
public:
    int loyalty;
    lion(){}
    lion(std::string _name, int _life, int _loyalty):warrior(_name,_life),loyalty(_loyalty){}
    lion(const warrior& w, int _loyalty):warrior(w),loyalty(_loyalty){}
    lion(const lion& d){
        warrior::name = d.name;
        warrior::life = d.life;
        loyalty = d.loyalty;
    }
    void printExra(){
        cout<<"It's loyalty is "<<loyalty<<endl;
    }

};

class wolf:public warrior{
public:
    wolf(){}
    wolf(std::string _name, int _life):warrior(_name,_life){}
    wolf(const warrior& w){name = w.name; life = w.life;}
    wolf(const wolf& d){
        warrior::name = d.name;
        warrior::life = d.life;
    }
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
        std::vector<std::string> allWeapon;
        std::vector<dragon> teamDragon;
        std::vector<ninjia> teamNinja;
        std::vector<iceman> teamIceman;
        std::vector<lion> teamLion;
        std::vector<wolf> teamWolf;
    public:
        headquarter(std::string _name, int _totLife, std::vector<warrior> _sequence):name(_name),totLife(_totLife),sequence(_sequence){
            controlIndex = -1;
            selfIndex = -1;
            vigor = 1;
            allWeapon.push_back("sword");
            allWeapon.push_back("bomb");
            allWeapon.push_back("arrow");
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
            dragon tmpWarrior(sequence[actualIndex],(selfIndex+1)%3,((double)totLife)/sequence[actualIndex].life);
            teamDragon.push_back(tmpWarrior);
            warriorIndex = teamDragon.size();
            tmpWarrior.printBasic(selfIndex, name, warriorName, sequence[actualIndex].life, warriorIndex);
            tmpWarrior.printExra(allWeapon[tmpWarrior.weapon]);

        }
        else if(warriorName == "ninja"){
            ninjia tmpWarrior(sequence[actualIndex],(selfIndex+1)%3,(selfIndex+2)%3);
            teamNinja.push_back(tmpWarrior);
            warriorIndex = teamNinja.size();
            tmpWarrior.printBasic(selfIndex, name, warriorName, sequence[actualIndex].life, warriorIndex);
            tmpWarrior.printExra(allWeapon[tmpWarrior.weapon1],allWeapon[tmpWarrior.weapon2]);
        }
        else if(warriorName == "iceman"){
            iceman tmpWarrior(sequence[actualIndex],(selfIndex+1)%3);
            teamIceman.push_back(tmpWarrior);
            warriorIndex = teamIceman.size();
            tmpWarrior.printBasic(selfIndex, name, warriorName, sequence[actualIndex].life, warriorIndex);
            tmpWarrior.printExra(allWeapon[tmpWarrior.weapon]);
        }
        else if(warriorName == "lion"){
            lion tmpWarrior(sequence[actualIndex],totLife);
            teamLion.push_back(tmpWarrior);
            warriorIndex = teamLion.size();
            tmpWarrior.printBasic(selfIndex, name, warriorName, sequence[actualIndex].life, warriorIndex);
            tmpWarrior.printExra();
        }
        else if(warriorName == "wolf"){
            wolf tmpWarrior(sequence[actualIndex]);
            teamWolf.push_back(tmpWarrior);
            warriorIndex = teamWolf.size();
            tmpWarrior.printBasic(selfIndex, name, warriorName, sequence[actualIndex].life, warriorIndex);
        }

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
        w1.name="iceman"; w1.life=l3[i];
        w2.name="lion"; w2.life=l4[i];
        w3.name="wolf"; w3.life=l5[i];
        w4.name="ninja"; w4.life=l2[i];
        w5.name="dragon"; w5.life=l1[i];

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

    delete [] TotalLife;
    delete [] l1;
    delete [] l2;
    delete [] l3;
    delete [] l4;
    delete [] l5;
    return 0;
}
