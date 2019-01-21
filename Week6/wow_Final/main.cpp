#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <stdio.h>
using namespace std;

/*Weapon part*/
class Weapon{
protected:
    int attack=0;
    int endurance=3;
public:
    int index = 0;//0 means null weapon, 1 sword, 2 Arrow, 3 Bomb
    Weapon(){}
    Weapon(int _attack):attack(_attack){}
    Weapon(const Weapon& w){attack = w.attack;index = w.index;}
    Weapon& operator=(Weapon& w){attack = w.attack; index = w.index;return *this;}
    void setAttack(int _attack){attack = _attack;}
    int getAttack(){return attack;}
    int getEndurance(){return endurance;}
    virtual void damage(){};
};
class Sword:public Weapon{
public:
    Sword(int _attack):Weapon(_attack){index = 1;}
    Sword(const Sword& s){attack = s.attack; index = 1;}
    Sword& operator=(const Sword& s){attack = s.attack; index = 1; return *this;}
    virtual void damage(){
        int prevAtt = getAttack();
        int nowAtt = floor(prevAtt*0.8);
        setAttack(nowAtt);
    }
};
class Arrow:public Weapon{

public:
    Arrow(int _attack):Weapon(_attack){index = 2;}
    Arrow(const Arrow& a){attack = a.attack;endurance=a.endurance;index = 2;}
    Arrow& operator=(Arrow& a){attack = a.attack; endurance=a.endurance;index=2;return *this;}
    virtual void damage(){
        endurance -= 1;
        if (endurance == 0){
            setAttack(0);
        }
    }
};
class Bomb:public Weapon{
public:
    Bomb(int _attack):Weapon(_attack){index = 3;}
    Bomb(const Bomb& a){attack = a.attack; index = 3;}
    Bomb& operator=(Bomb& a){attack = a.attack; index=3;return *this;}
    virtual void damage(){
        setAttack(0);
    }
};
/*End of Weapon part*/

/*Warrior Part*/
class Warrior{
protected:
    int life;
    int preLife=0;
    int attack;
    int city;//every warrior should know the current city they are in. Index from 0 to numCity+1.
    int loyalty;
    int morale;
    int increment;
    int status=0;//0 means dead while 1 means alive
    int stepsWalked=0;//Store how many steps have this poor guy walked by
public:
    Weapon* weapon[2];/*Weapon are stored as: 0.No weapon 1.Sword 2.Bomb 3.Arrow*/
    string name = "Null Warrior";
    string belong;
    Warrior(){}
    Warrior(int _life, int _attack, int _city, string _belong):life(_life),attack(_attack),city(_city),belong(_belong){}
    Warrior(int _life, int _attack, int _city, string _belong, Weapon _weapon1, Weapon _weapon2):life(_life),attack(_attack),city(_city),belong(_belong){
        weapon[0] = &_weapon1;
        weapon[1] = &_weapon2;
    }
    Warrior(int _life, int _attack, int _city, string _belong, int _morale, Weapon _weapon):life(_life),attack(_attack),city(_city),belong(_belong),morale(_morale){
        weapon[0] = &_weapon;
    }
    Warrior(int _life, int _attack, int _city,string _belong,int _loyalty, int _increment):
    life(_life),attack(_attack),city(_city),belong(_belong),loyalty(_loyalty),increment(_increment){}
    Warrior(int _life, int _attack, int _city, string _belong, Weapon _weapon):life(_life),attack(_attack),city(_city),belong(_belong){
        weapon[0] = &_weapon;
    }

    Warrior(const Warrior& w){
        life = w.life; attack=w.attack;
        loyalty = w.loyalty;
        morale = w.morale;
        increment = w.increment;
        weapon[0] = w.weapon[0];weapon[1] = w.weapon[1];
        city = w.city;
        belong = w.belong;
    }
    Warrior& operator=(const Warrior& w){
        life = w.life; attack=w.attack;
        loyalty = w.loyalty;
        morale = w.morale;
        increment = w.increment;
        weapon[0] = w.weapon[0];weapon[1] = w.weapon[1];
        city = w.city;
        belong = w.belong;
        return *this;
    }

    void setLife(int _life){life = _life;}
    void setAttack(int _attack){attack = _attack;}
    void setLoyalty(int _loyalty){loyalty = _loyalty;}
    void setCity(int _city){city = _city;}
    void assignWeapon(Weapon _weapon){
        weapon[0] = &_weapon;
    }
    void assignWeapon(Weapon _weapon1, Weapon _weapon2){
        weapon[0] = &_weapon1;
        weapon[1] = &_weapon2;
    }
    void destroyWeapon(int index){
        weapon[0]->index = 0;

    }
    int getLife(){return life;}
    int getAttack(){return attack;}
    int getCity(){return city;}
    int getLoyalty(){return loyalty;}
    int getStatus(){return status;}
    virtual void hurt(int lostLife){
        life -= lostLife;
    }
    void beingKilled(){
        status = 0;
    }
    virtual void walk(int step){
        if(status != 0) city += step;//can either be 1 or -1
    }
    virtual void lowerLoy(){}
    virtual void lifeTransfer(Warrior* w){}

    int getTotalAttack(){
        return getAttack() + weapon[0]->getAttack() + weapon[1]->getAttack();
    }
    int getTotalFightBack(){
        return (floor(getAttack()/2) + weapon[0]->getAttack() + weapon[1]->getAttack());
    }
    virtual void fight(Warrior* w){
        w->hurt(getTotalAttack());
        weapon[0]->damage();
        weapon[1]->damage();
        if (w->getLife() <= 0){
            w->beingKilled();
        }
    }
    virtual void fightBack(Warrior* w){
        w->hurt(getTotalFightBack());
        weapon[0]->damage();
        weapon[1]->damage();
        if (w->getLife() <= 0){
            w->beingKilled();
        }
    }
    virtual void pickUpWeapon(){}
};
/*Weapon are stored as: 1.Sword 2.Bomb 3.Arrow*/
class Dragon:public Warrior{
public:
    Dragon(){}
    Dragon(int _life, int _attack, int _city, string _belong,Weapon _weapon, double _morale):Warrior(_life, _attack,city,_belong,_weapon,_morale){
            name = "Dragon";
            status = 1;
    }
    Dragon(const Dragon& d):Warrior(d){}
    Dragon(const Warrior& w):Warrior(w){};
    Dragon& operator=(Dragon& d){
        Warrior::operator=(d);
        return *this;
    }
    virtual void fight(Warrior* w){
        w->hurt(getTotalAttack());
        weapon[0]->damage();
        if (w->getLife() <= 0){
            w->beingKilled();
            morale += 0.2;
            yell();
        }
        else{
            morale -= 0.2;
        }
    }
    virtual void fightBack(Warrior& w){
        w.hurt(getTotalFightBack());
    }
    void moraleUp(){
        morale += 0.2;
    }
    void moraleDown(){
        morale -= 0.2;
    }
    void yell(){
        if(morale > 0.8){
            cout<<"This little dragon yelled"<<endl;
        }
    }
};
class Ninjia:public Warrior{
public:
    Ninjia(){}
    Ninjia(int _life, int _attack, int _city, string _belong, Weapon _weapon1, Weapon _weapon2):Warrior(_life, _attack, _city,_belong,_weapon1, _weapon2){
        name = "Ninjia";
        status = 1;
    }
    Ninjia(const Ninjia& n):Warrior(n){}
    Ninjia(const Warrior& w):Warrior(w){};
    Ninjia& operator=(const Ninjia& n){
        Warrior::operator=(n);
        return *this;
    }
    virtual void fightBack(Warrior& w){
        w.hurt(getTotalFightBack());
    }

};
class Iceman:public Warrior{
public:
    Iceman(){}
    Iceman(int _life, int _attack, int _city, string _belong, Weapon _weapon):Warrior(_life, _attack, _city, _belong, _weapon){
        name = "Iceman";
        status = 1;
    }
    Iceman(const Iceman& i):Warrior(i){}
    Iceman(const Warrior& w):Warrior(w){};
    Iceman& operator=(const Iceman& i){
        Warrior::operator=(i);
        return *this;
    }
    virtual void walk(int step){
        if(status != 0){
            city += step;//Similarly, can either be 1 or -1
            if(city%2 == 0 && city != 0){
                hurt(9);
                setAttack(getAttack() + 20);
                if (getLife() <= 0){
                    setLife(1);
                    setAttack(getAttack()-20);
                }
            }
        }
    }
    virtual void fightBack(Warrior& w){
        w.hurt(getTotalFightBack());
    }
};
class Lion:public Warrior{
public:
    Lion(){}
    Lion(int _life, int _attack, int _city, string _belong, int _loyalty, int _increment):Warrior(_life, _attack, _city,_belong,_loyalty,_increment){
        name = "Lion";
        status = 1;
    }
    Lion(const Lion& l):Warrior(l){}
    Lion(const Warrior& w):Warrior(w){};
    Lion& operator=(const Lion& l){
        Warrior::operator=(l);
        return *this;
    }
    virtual void lifeTransfer(Warrior* w){
        w->setLife(w->getLife() + preLife);
    }
    virtual void hurt(int lostLife){
        life -= lostLife;
        if(life <= 0){
            preLife = life + lostLife;
        }

    }

    void lowerLoy(){
        loyalty -= increment;
    }
};
class Wolf:public Warrior{
public:
    Wolf(){}
    Wolf(int _life, int _attack, int _city, string _belong):Warrior(_life, _attack, _city,_belong){
        name = "Wolf";
        status = 1;
    }
    Wolf(const Wolf& w):Warrior(w){}
    Wolf(const Warrior& w):Warrior(w){};
    Wolf& operator=(const Wolf& w){
        Warrior::operator=(w);
        return *this;
    }
    virtual void pickUpWeapon(Weapon w){
        if(weapon[0]->index == 0){
            weapon[0] = &w;
        }
    }
};
/*End of Warrior Part*/

class City{
private:
    int numWarrior=0;
    int occupied=-1;//0 means occupied by Red and 1 means occupied by Blue
    int privilege = -1;//0 means Red has privilege and 1 means blue has privilege
    int numLife=0;//How many life elements remained in this City

public:
    Warrior* RedWarrior;
    Warrior* BlueWarrior;
    int RcontinuousWinning = 0;
    int BcontinuousWinning = 0;
    City(){}
    City(int _numWarrior, int _occupied, int _numLife):
    numWarrior(_numWarrior),occupied(_occupied),numLife(_numLife){
        RedWarrior = new Warrior();
        BlueWarrior = new Warrior();
    }
    City(const City& c){
        numWarrior = c.numWarrior;
        occupied = c.occupied;
        numLife = c.numLife;
        RedWarrior = c.RedWarrior; BlueWarrior = c.BlueWarrior;
    }
    City& operator=(const City& c){
        numWarrior = c.numWarrior;
        occupied = c.occupied;
        numLife = c.numLife;
        RedWarrior = c.RedWarrior; BlueWarrior = c.BlueWarrior;
        return *this;
    }
    ~City(){
        delete RedWarrior;
        delete BlueWarrior;
    }
    void generateLife(){
        numLife += 10;
    }

    int lifePickedUp(){
        int tmp = numLife;
        numLife = 0;
        return tmp;
    }
    int getPrivilege(){return privilege;}
    void decidePrivilege(int index){
        if(index%2 == 1 || occupied != 1){
            privilege = 0;
        }
        else if(index%2 == 0 || occupied != 0){
            privilege = 1;
        }
    }
    void setOccupied(int headquarter){
        occupied = headquarter;
    }

    void warriorLeave(string headquarter){
        if(headquarter == "Red"){
            // Warrior* tmpWarrior = new Warrior();
            RedWarrior = NULL;
        }
        else if(headquarter == "Blue"){
            // Warrior* tmpWarrior = new Warrior();
            BlueWarrior = NULL;
        }
    }
    void newWarriorCome(Warrior* w){
        if(w->belong == "Red"){
            delete RedWarrior;
            RedWarrior = w;
        }
        else if(w->belong == "Blue"){
            delete RedWarrior;
            BlueWarrior = w;
        }
    }
};

class Headquarter{
private:
    vector<Warrior*> sequence;//Store the sequence according to which the headquarter generates new warrior
    std::string name; //red or blue
    int totLife;
    int selfIndex; //The index of all warriors in each headquarter
    int controlIndex;
    int MinLife;
    int vigor;//It's unable to generate more warriors if the vigor is zero.
    int numCity;
    int numEnemy=0;
    vector<Warrior*> warriors;
    vector<std::string> allWeapon;
    City** allCities = new City*[numCity];
public:
    Headquarter(std::string _name, int _totLife, int _numCity, vector<Warrior*> _sequence,City** _allCities):
    name(_name),totLife(_totLife),numCity(_numCity),sequence(_sequence){
        for(size_t i=0; i<numCity; i++){
            allCities[i] = _allCities[i];
        }
        controlIndex = -1;
        selfIndex = -1;
        vigor = 1;
        allWeapon.push_back("Sword");
        allWeapon.push_back("Bomb");
        allWeapon.push_back("Arrow");
    }
    ~Headquarter(){delete [] allCities;}

    void minLife();
    bool generate();
    void lionRunAway();
    void warriorMove();

    void pickUpLife();
    void useArrow();
    void useBoom();
    void battle();
    void reportLife();
    void reportWeapon();
    bool beingOccupied();
};

void Headquarter::minLife(){
    MinLife = 100000000;
    for(size_t i=0; i<sequence.size();i++){
        if(MinLife > sequence[i]->getLife()){
            MinLife = sequence[i]->getLife();
        }
    }
}
bool Headquarter::generate(){
    if(vigor == 0){
        return false;
    }
    selfIndex += 1;
    controlIndex += 1;
    int seqIndex = controlIndex%5;
    int actualIndex = -1;
    std::string warriorName;
    if (sequence[seqIndex]->getLife() <= totLife){
        warriorName = sequence[seqIndex]->name;
        actualIndex = seqIndex;
        controlIndex = seqIndex;
        Warrior* tmpWarrior;
        if(warriorName == "Dragon"){
            tmpWarrior = new Dragon(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            warriors.push_back(tmpWarrior);
        }
        else if(warriorName == "Ninjia"){
            tmpWarrior = new Ninjia(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            warriors.push_back(tmpWarrior);
        }
        else if(warriorName == "Iceman"){
            tmpWarrior = new Iceman(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            warriors.push_back(tmpWarrior);
        }
        else if(warriorName == "Lion"){
            tmpWarrior = new Lion(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            tmpWarrior->setLoyalty(totLife);
            warriors.push_back(tmpWarrior);
        }
        else if(warriorName == "Wolf"){
            tmpWarrior = new Wolf(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            warriors.push_back(tmpWarrior);
        }
        cout<<"Some baby is born"<<endl;
        return true;
    }
    else{
        selfIndex -= 1;
        cout<<"We don't have enough life to generate new Warrior"<<endl;
        return false;
    }
}
void Headquarter::lionRunAway(){
    for(vector<Warrior*>::iterator it = warriors.begin(); it != warriors.end(); it++){
        if((*it)->name == "Lion" && (*it)->getLoyalty() <= 0){
            if(name == "Red"){
                if((*it)->getCity() != numCity+1){
                    (*it)->beingKilled();
                }
            }
            else{
                if((*it)->getCity() != 0){
                    (*it)->beingKilled();
                }
            }
        }
    }
}
void Headquarter::warriorMove(){
    if(name == "Red"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->getCity() != numCity+1 && (*it)->getStatus() != 0){
                int CurrentCity = (*it)->getCity();
                (*it)->walk(1);
                if (CurrentCity !=0){
                    allCities[CurrentCity-1]->warriorLeave("Red");//allCities are indexed starting from 0 rather than 1
                }
                if(CurrentCity != numCity){
                    allCities[CurrentCity]->newWarriorCome(*it);
                }
                else if(CurrentCity == numCity){
                    numEnemy += 1;
                }
            }
        }
    }
    else if(name == "Blue"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->getCity() != 0 && (*it)->getStatus() != 0){
                int CurrentCity = (*it)->getCity();
                (*it)->walk(-1);
                if (CurrentCity !=numCity){
                    allCities[CurrentCity-1]->warriorLeave("Blue");
                }
                if(CurrentCity != 1){
                    allCities[CurrentCity-2]->newWarriorCome(*it);
                }
                if(CurrentCity == 1){
                    numEnemy += 1;
                }
            }
        }
    }
}
void Headquarter::pickUpLife(){
    if(name == "Red"){
        for(size_t i=0; i<numCity; i++){
            if (allCities[i]->RedWarrior->getStatus() == 1 && allCities[i]->BlueWarrior->getStatus() == 0){
                totLife += allCities[i]->lifePickedUp();
            }
        }
    }
    else if(name == "Blue"){
        for(size_t i=0; i<numCity; i++){
            if (allCities[i]->BlueWarrior->getStatus() == 1 && allCities[i]->RedWarrior->getStatus() == 0){
                totLife += allCities[i]->lifePickedUp();
            }
        }
    }
}
void Headquarter::useArrow(){
    if(name == "Red"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->weapon[0]->index == 2 || (*it)->weapon[0]->getEndurance() != 0){
                if(allCities[(*it)->getCity()]->BlueWarrior->getStatus() != 0){
                    (*it)->fight(allCities[(*it)->getCity()]->BlueWarrior);
                    (*it)->weapon[0]->damage();
                }
            }
        }
    }
    else if(name == "Blue"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->weapon[0]->index == 2 || (*it)->weapon[0]->getEndurance() != 0){
                if(allCities[(*it)->getCity()-2]->RedWarrior->getStatus() != 0){
                    (*it)->fight(allCities[(*it)->getCity()-2]->RedWarrior);
                    (*it)->weapon[0]->damage();
                }
            }
        }
    }
}
void Headquarter::useBoom(){
    if(name == "Red"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->weapon[0]->index == 3 || (*it)->weapon[0]->getEndurance() != 0){
                if(allCities[(*it)->getCity()-1]->BlueWarrior->getStatus() != 0 ||\
                 allCities[(*it)->getCity()-1]->BlueWarrior->getLife() <= (*it)->weapon[0]->getAttack()){
                    (*it)->fight(allCities[(*it)->getCity()]->BlueWarrior);
                    (*it)->weapon[0]->damage();
                    (*it)->beingKilled();
                }
            }
        }
    }
    if(name == "Blue"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->weapon[0]->index == 3 || (*it)->weapon[0]->getEndurance() != 0){
                if(allCities[(*it)->getCity()-1]->RedWarrior->getStatus() != 0 ||\
                 allCities[(*it)->getCity()-1]->RedWarrior->getLife() <= (*it)->weapon[0]->getAttack()){
                    (*it)->fight(allCities[(*it)->getCity()]->RedWarrior);
                    (*it)->weapon[0]->damage();
                    (*it)->beingKilled();
                }
            }
        }
    }
}
void Headquarter::battle(){
    if (name == "Red"){
        for(size_t i=0; i<numCity; i++){
            if(allCities[i]->getPrivilege() == 0){ //Red has the privilege
                if(allCities[i]->RedWarrior->getStatus() == 1 && allCities[i]->BlueWarrior->getStatus() != 0){
                    allCities[i]->RedWarrior->fight(allCities[i]->BlueWarrior);
                    if(allCities[i]->BlueWarrior->getStatus() != 0 && allCities[i]->BlueWarrior->name != "Ninjia"){
                        allCities[i]->BlueWarrior->fightBack(allCities[i]->RedWarrior);
                        if(allCities[i]->RedWarrior->getStatus() == 0){
                            allCities[i]->BcontinuousWinning += 1;
                            allCities[i]->RedWarrior->lifeTransfer(allCities[i]->BlueWarrior);
                            allCities[i]->BlueWarrior->pickUpWeapon();

                            if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                                allCities[i]->setOccupied(1);
                            }
                        }
                        else{//No one dies. It's a tie.
                            allCities[i]->BcontinuousWinning = 0;
                            allCities[i]->RcontinuousWinning = 0;
                        }
                    }
                    else if(allCities[i]->BlueWarrior->getStatus() == 0){
                        allCities[i]->RcontinuousWinning += 1;
                        allCities[i]->RedWarrior->pickUpWeapon();
                        allCities[i]->BlueWarrior->lifeTransfer(allCities[i]->RedWarrior);
                        if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                            allCities[i]->setOccupied(0);
                        }
                    }
                    else{//No one dies. It's tie.
                        allCities[i]->BcontinuousWinning = 0;
                        allCities[i]->BcontinuousWinning = 0;
                    }
                }
            }
            else if(allCities[i]->RedWarrior->getStatus() == 1 && allCities[i]->BlueWarrior->getStatus() == 0){
                allCities[i]->RcontinuousWinning += 1;
                allCities[i]->BlueWarrior->lifeTransfer(allCities[i]->RedWarrior);
                allCities[i]->RedWarrior->pickUpWeapon();
                if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                    allCities[i]->setOccupied(0);
                }
            }
        }
    }
    else if(name == "Blue"){
        for(size_t i=0; i<numCity; i++){
            if(allCities[i]->getPrivilege() == 1){ //Blue has the privilege
                if(allCities[i]->BlueWarrior->getStatus() == 1 && allCities[i]->RedWarrior->getStatus() != 0){
                    allCities[i]->BlueWarrior->fight(allCities[i]->RedWarrior);
                    if(allCities[i]->RedWarrior->getStatus() != 0 && allCities[i]->RedWarrior->name != "Ninjia"){
                        allCities[i]->RedWarrior->fightBack(allCities[i]->BlueWarrior);
                        if(allCities[i]->BlueWarrior->getStatus() == 0){
                            allCities[i]->RcontinuousWinning += 1;
                            allCities[i]->BlueWarrior->lifeTransfer(allCities[i]->RedWarrior);
                            allCities[i]->RedWarrior->pickUpWeapon();
                            if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                                allCities[i]->setOccupied(0);
                            }
                        }
                        else{//No one dies. It's a tie.
                            allCities[i]->BcontinuousWinning = 0;
                            allCities[i]->RcontinuousWinning = 0;
                        }
                    }
                    else if(allCities[i]->RedWarrior->getStatus() == 0){
                        allCities[i]->BcontinuousWinning += 1;
                        allCities[i]->RedWarrior->lifeTransfer(allCities[i]->BlueWarrior);
                        allCities[i]->BlueWarrior->pickUpWeapon();
                        if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                            allCities[i]->setOccupied(1);
                        }
                    }
                    else{//No one dies. It's tie.
                        allCities[i]->BcontinuousWinning = 0;
                        allCities[i]->RcontinuousWinning = 0;
                    }
                }
            }
            else if(allCities[i]->BlueWarrior->getStatus() == 1 && allCities[i]->RedWarrior->getStatus() == 0){
                allCities[i]->BcontinuousWinning += 1;
                allCities[i]->RedWarrior->lifeTransfer(allCities[i]->BlueWarrior);
                allCities[i]->BlueWarrior->pickUpWeapon();
                if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                    allCities[i]->setOccupied(1);
                }
            }
        }
    }
}
void Headquarter::reportLife(){
    cout<<name<<" headquarter has "<<totLife<<" element"<<endl;
}
void Headquarter::reportWeapon(){
    for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
        cout<<"I have this weapon: "<<(*it)->weapon[0]->index<<endl;
    }
}
bool Headquarter::beingOccupied(){
    if(numEnemy == 2){
        cout<<"This headquarter has been occupied"<<endl;
        return true;
    }
    else{
        return false;
    }
}

int main(){
    int caseNum;
    cin>>caseNum;
    int* inM = new int[caseNum];
    int* inN = new int[caseNum];
    int* inR = new int[caseNum];
    int* inK = new int[caseNum];
    int* inT = new int[caseNum];

    int* l1 = new int[caseNum]; int* at1 = new int[caseNum];
    int* l2 = new int[caseNum]; int* at2 = new int[caseNum];
    int* l3 = new int[caseNum]; int* at3 = new int[caseNum];
    int* l4 = new int[caseNum]; int* at4 = new int[caseNum];
    int* l5 = new int[caseNum]; int* at5 = new int[caseNum];
    for (size_t i=0;i<caseNum;i++){
        cin>>inM[i]>>inN[i]>>inR[i]>>inK[i]>>inT[i];
        cin>>l1[i]>>l2[i]>>l3[i]>>l4[i]>>l5[i];
        cin>>at1[i]>>at2[i]>>at3[i]>>at4[i]>>at5[i];
    }

    for (size_t i=0;i<caseNum; i++){
        std::vector<Warrior*> seqRed,seqBlue;
        Warrior* w1;
        Warrior* w2;
        Warrior* w3;
        Warrior* w4;
        Warrior* w5;

        w1 = new Iceman();
        w2 = new Iceman();
        w3 = new Wolf();
        w4 = new Ninjia();
        w5 = new Dragon();

        w1->setLife(l3[i]);
        w2->setLife(l4[i]);
        w3->setLife(l5[i]);
        w4->setLife(l2[i]);
        w5->setLife(l1[i]);

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

        City** allCities = new City*[inN[i]];
        for(int i=0; i<inN[i]; i++){
            allCities[i] = new City();
        }

        Headquarter red("Red",inM[i],inN[i],seqRed, allCities);
        Headquarter blue("Blue",inM[i],inN[i],seqBlue, allCities);
        red.minLife(); blue.minLife();

        cout<<"Case:"<<i+1<<endl;


        // bool indi1, indi2;
        // indi1 = red.generate();
        // indi2 = blue.generate();
        // while(indi1 || indi2){
        //     indi1 = red.generate();
        //     indi2 = blue.generate();
        // }
        //
        // delete w1, w2, w3, w4, w5;
    }


    delete [] inM, inN, inR, inK, inT;
    delete [] l1, at1;
    delete [] l2, at2;
    delete [] l3, at3;
    delete [] l4, at4;
    delete [] l5, at5;
    return 0;
}
