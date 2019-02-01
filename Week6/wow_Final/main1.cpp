#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
/*Things to be done. There is still some error in the sequence of weapon. Also, there is something wrong with the final result/
/*To store event so that we can print it in a certain sequence*/
struct event{
    int cityIndex;
    int eventIndex;
    int hour;
    int min;
    string thingsHappened;
    event& operator=(const event& e){
        cityIndex = e.cityIndex;
        eventIndex = e.eventIndex;
        hour = e.hour;
        min = e.min;
        thingsHappened = e.thingsHappened;
        return *this;
    }
};
vector<event> allEvents;
int Hour=0;
/*double and int to char*/
string to_str(int data){
    char numStr[20];
    sprintf(numStr,"%d",data);
    string tmpString(numStr);
    return tmpString;
}

string to_str(double data){
    char numStr[20];
    sprintf(numStr,"%.2lf",data);
    string tmpString(numStr);
    return tmpString;
}

/*Weapon part*/
class Weapon{
protected:
    int attack=0;
    int endurance=3;
public:
    int index = 0;//0 means null weapon, 1 sword, 2 Bomb, 3 Arrow
    string name = "Null weapon";
    Weapon(){}
    Weapon(int _attack):attack(_attack){}
    Weapon(const Weapon& w){attack = w.attack;index = w.index;name = w.name;}
    Weapon& operator=(Weapon& w){attack = w.attack; index = w.index;name = w.name;return *this;}
    void setAttack(int _attack){attack = _attack;}
    void setEndurance(int _endurance){endurance = _endurance;}
    int getAttack(){return attack;}
    int getEndurance(){return endurance;}
    virtual void damage(){};
};
class Sword:public Weapon{
public:
    Sword(){index = 1;name = "sword";}
    Sword(int _attack):Weapon(_attack){index = 1;name = "sword";}
    Sword(const Sword& s):Weapon(s){index = 1;}
    Sword& operator=(Sword& s){Weapon::operator=(s); return *this;}
    virtual void damage(){
        int prevAtt = getAttack();
        int nowAtt = floor(prevAtt*0.8);
        if(nowAtt == 0){
            setEndurance(0);
            setAttack(0);
        }
        else{
            setAttack(nowAtt);
        }
    }
};
class Bomb:public Weapon{
public:
    Bomb(){index = 2;name = "bomb";}
    Bomb(int _attack):Weapon(0){index = 2;name = "bomb";}
    Bomb(const Bomb& a):Weapon(a){index = 2;}
    Bomb& operator=(Bomb& a){Weapon::operator=(a); index=2;return *this;}
    virtual void damage(){
        setEndurance(0);
    }
};
class Arrow:public Weapon{
public:
    Arrow(){index = 3;name = "arrow";}
    Arrow(int _attack):Weapon(_attack){index = 3;name = "arrow";}
    Arrow(const Arrow& a):Weapon(a){index = 3;}
    Arrow& operator=(Arrow& a){Weapon::operator=(a);index=3;return *this;}
    virtual void damage(){
        endurance -= 1;
    }
};

/*End of Weapon part*/

/*Warrior Part*/
class Warrior{
protected:
    int life;
    int preLife=0;
    int attack;
    int city=0;//every warrior should know the current city they are in. Index from 0 to numCity+1.
    int loyalty;
    double morale;
    int increment;
    int status=0;//0 means dead while 1 means alive, -1 means died by shot, -2 means killed by boom
    int stepsWalked=0;//Store how many steps have this poor guy walked by
    int index;//Store the index it belongs to the headquarter
    Weapon nullWeapon;
public:
    vector<Weapon*> weapon;/*Weapon are stored as: 0.No weapon 1.Sword 2.Bomb 3.Arrow*/
    string name = "Null Warrior";
    string belong;
    Warrior(){weapon.clear();}
    Warrior(int _life, int _attack, int _city, string _belong):life(_life),attack(_attack),city(_city),belong(_belong){weapon.clear();}
    Warrior(int _life, int _attack, int _city, string _belong, Weapon _weapon1, Weapon _weapon2):life(_life),attack(_attack),city(_city),belong(_belong){
        weapon.clear();
        weapon.push_back(&_weapon1);
        weapon.push_back(&_weapon2);
    }
    Warrior(int _life, int _attack, int _city, string _belong, double _morale, Weapon _weapon):life(_life),attack(_attack),city(_city),belong(_belong),morale(_morale){
        weapon.clear();
        weapon.push_back(&_weapon);
    }
    Warrior(int _life, int _attack, int _city,string _belong,int _loyalty, int _increment):
    life(_life),attack(_attack),city(_city),belong(_belong),loyalty(_loyalty),increment(_increment){weapon.clear();}
    Warrior(int _life, int _attack, int _city, string _belong, Weapon _weapon):life(_life),attack(_attack),city(_city),belong(_belong){
        weapon.clear();
        weapon.push_back(&_weapon);
    }

    Warrior(const Warrior& w){
        life = w.life; attack=w.attack;
        loyalty = w.loyalty;
        morale = w.morale;
        increment = w.increment;
        weapon.clear();
        name = w.name;
        status = w.status;
        for(int i=0; i<w.weapon.size(); i++){
            weapon.push_back(w.weapon[i]);
        }

        city = w.city;
        belong = w.belong;
    }
    Warrior& operator=(const Warrior& w){
        life = w.life; attack=w.attack;
        loyalty = w.loyalty;
        morale = w.morale;
        increment = w.increment;
        name = w.name;
        status = w.status;
        weapon.clear();
        for(int i=0; i<w.weapon.size(); i++){
            weapon.push_back(w.weapon[i]);
        }

        city = w.city;
        belong = w.belong;
        return *this;
    }
    ~Warrior(){
        weapon.clear();
    }

    void setLife(int _life){life = _life;}
    void setAttack(int _attack){attack = _attack;}
    void setLoyalty(int _loyalty){loyalty = _loyalty;}
    void setCity(int _city){city = _city;}
    void setMorale(double _morale){morale = _morale;}
    void setIndex(int _index){index = _index;}
    void setStatus(int _status){status = _status;}

    void assignWeapon(Weapon* _weapon){
        weapon.push_back(_weapon);
    }
    void assignWeapon(Weapon* _weapon1, Weapon* _weapon2){
        weapon.push_back(_weapon1);
        weapon.push_back(_weapon2);
    }
    void destroyWeapon(int index){
        weapon[index]->setEndurance(0);
    }
    bool releaseArrow(Warrior* w){
        int count = 0;
        for(int i=0; i<weapon.size(); i++){
            if(weapon[i]->index == 3 && weapon[i]->getEndurance() != 0){
                w->setLife(w->getLife() - weapon[i]->getAttack());
                count += 1;
                weapon[i]->damage();
                break;
            }
        }
        if(count == 0){
            return false;
        }
        else{
            return true;
        }
    }

    virtual void moraleUp(){}
    virtual void moraleDown(){}
    virtual string yell(){return "";}

    int getLife(){return life;}
    int getAttack(){return attack;}
    int getCity(){return city;}
    int getLoyalty(){return loyalty;}
    int getStatus(){return status;}
    double getMorale(){return morale;}
    int getIndex(){return index;}

    virtual void hurt(int lostLife){
        life -= lostLife;
        if(life <= 0) beingKilled();
    }
    void beingKilled(){
        //Killed by attack
        status = 0;
        attack = 0;
        weapon.clear();

    }
    virtual void walk(int step){
        if(status > 0) city += step;//can either be 1 or -1
    }
    virtual void lowerLoy(){}
    virtual void lifeTransfer(Warrior* w){}

    int getTotalAttack(){
        int tmpAttack = 0;
        for(int i=0; i<weapon.size(); i++){
            if(weapon[i]->index == 1){
                //Only sword can contribute to the total attack
                tmpAttack += weapon[i]->getAttack();
            }
        }
        return getAttack() + tmpAttack;
    }
    virtual int getTotalFightBack(){
        int tmpAttack = 0;
        for(int i=0; i<weapon.size(); i++){
            if(weapon[i]->index == 1){
                //Only sword can contribute to the total attack
                tmpAttack += weapon[i]->getAttack();
            }
        }
        return (floor(getAttack()/2) + tmpAttack);
    }
    virtual void fight(Warrior* w){
        if(w->getStatus() == 1){
            w->hurt(getTotalAttack());
            for(vector<Weapon*>::iterator it=weapon.begin(); it != weapon.end(); it++){
                if((*it)->index == 1){
                    //Only Sword will be damaged by normal attack
                    (*it)->damage();
                }
            }
            if (w->getLife() <= 0){
                w->beingKilled();
            }
        }
    }
    virtual void fightBack(Warrior* w){
        if(w->getStatus() == 1){
            w->hurt(getTotalFightBack());
            for(vector<Weapon*>::iterator it=weapon.begin(); it != weapon.end(); it++){
                if((*it)->index == 1){
                    //Only Sword will be damaged by normal attack
                    (*it)->damage();
                }
            }
            if (w->getLife() <= 0){
                w->beingKilled();
            }
        }
    }
    virtual void pickUpWeapon(Warrior* w){}
    void checkWeapon(){
        //Check whether the weapon has been damgaed. If it is, remove it from the weapon;
        bool allChecked = false;
        while(allChecked == false){
            int count = 0;
            for(int i=0; i<weapon.size(); i++){
                if (weapon[i]->getEndurance() <= 0){
                    delete weapon[i];
                    weapon.erase(weapon.begin()+i);
                    count += 1;
                    break;
                }
            }
            if(count != 0){
                allChecked = false;
            }
            else{
                allChecked = true;
            }
        }
    }

    virtual void reportWeapon(){
        if(status > 0){
            if(weapon.size() > 0 && weapon[0]->getEndurance() > 0){
                int weaponIndex = 0;
                if(weapon[0]->getEndurance() != 0){
                    weaponIndex = weapon[0]->index;

                    string tmpString = "";

                    switch(weaponIndex){
                        case 1:tmpString = tmpString+belong+" "+name+" "+to_str(index)+" has "+weapon[0]->name+"("+to_str(weapon[0]->getAttack())+")"+"\n";
                        break;
                        case 2:tmpString = tmpString+belong+" "+name+" "+to_str(index)+" has "+weapon[0]->name+"\n";
                        break;
                        case 3:tmpString = tmpString+belong+" "+name+" "+to_str(index)+" has "+weapon[0]->name+"("+to_str(weapon[0]->getEndurance())+")"+"\n";
                        break;
                    }

                    event tmpEvent = {city,15,Hour,55,tmpString};
                    if(belong == "blue"){
                        tmpEvent.cityIndex = city +100000000;
                    }
                    allEvents.push_back(tmpEvent);

                }
            }
            else{
                string tmpString = "";
                tmpString = tmpString+belong+" "+name+" "+to_str(index)+" has no weapon"+"\n";
                event tmpEvent = {city,15,Hour,55,tmpString};
                if(belong == "blue"){
                    tmpEvent.cityIndex = city +100000000;
                }
                allEvents.push_back(tmpEvent);
            }
        }
    }
};
/*Weapon are stored as: 1.Sword 2.Bomb 3.Arrow*/
class Dragon:public Warrior{
public:
    Dragon(){name = "dragon";}
    Dragon(int _life, int _attack, int _city, string _belong,Weapon _weapon, double _morale):Warrior(_life, _attack,city,_belong,_weapon,_morale){
            name = "dragon";
            status = 1;
    }
    Dragon(const Dragon& d):Warrior(d){}
    Dragon(const Warrior& w):Warrior(w){};
    Dragon& operator=(Dragon& d){
        Warrior::operator=(d);
        return *this;
    }
    virtual void fight(Warrior* w){
        if(w->getStatus() == 1){
            w->hurt(getTotalAttack());
            for(vector<Weapon*>::iterator it=weapon.begin(); it != weapon.end(); it++){
                if((*it)->index == 1){
                    //Only Sword will be damaged by normal attack
                    (*it)->damage();
                }
            }
            if (w->getLife() == 0){
                w->beingKilled();
                morale += 0.2;
                yell();
            }
            else{
                morale -= 0.2;
            }
        }
    }
    virtual void fightBack(Warrior& w){
        w.hurt(getTotalFightBack());
    }
    virtual void moraleUp(){morale += 0.2;}
    virtual void moraleDown(){morale -= 0.2;}
    virtual string yell(){
        if(morale > 0.8){
            return belong+" dragon "+to_str(getIndex())+" yelled in city "+to_str(getCity())+"\n";
        }
        else{
            return "";
        }
    }

};
class Ninjia:public Warrior{
public:
    Ninjia(){name = "ninja";}
    Ninjia(int _life, int _attack, int _city, string _belong, Weapon _weapon1, Weapon _weapon2):Warrior(_life, _attack, _city,_belong,_weapon1, _weapon2){
        name = "ninja";
        status = 1;
    }
    Ninjia(const Ninjia& n):Warrior(n){}
    Ninjia(const Warrior& w):Warrior(w){};
    Ninjia& operator=(const Ninjia& n){
        Warrior::operator=(n);
        return *this;
    }
    virtual int getTotalFightBack(){
        return 0;
    }
    virtual void fightBack(Warrior& w){}
    virtual void reportWeapon(){
        if(status > 0){
            string tmpString = "";
            if(weapon.size() > 0){
                int numWeapon = weapon.size();
                int count = 0;
                int weaponIndex;
                int findWeapon = 0;
                int numWeaponFound = 0;
                tmpString = tmpString+belong+" "+name+" "+to_str(index)+" has ";

                while(count < 3){
                    findWeapon = 0;
                    for(int i=0; i<numWeapon; i++){
                        weaponIndex = weapon[i]->index;
                        if (weaponIndex == 3-count){
                            if((count == 1 || count == 2) && (numWeaponFound != 0)){
                                tmpString = tmpString + ",";
                            }
                            switch(weaponIndex){
                                case 1:tmpString = tmpString+weapon[i]->name+"("+to_str(weapon[i]->getAttack())+")";
                                break;
                                case 2:tmpString = tmpString+weapon[i]->name;
                                break;
                                case 3:tmpString = tmpString+weapon[i]->name+"("+to_str(weapon[i]->getEndurance())+")";
                                break;
                            }
                            findWeapon = 1;
                            numWeaponFound += 1;
                            count += findWeapon;
                            break;
                        }
                        else{
                            continue;
                        }
                    }

                    if(findWeapon == 0){
                        count += 1;
                    }
                }

                tmpString = tmpString +"\n";
                event tmpEvent = {city,15,Hour,55,tmpString};
                if(belong == "blue"){
                    tmpEvent.cityIndex = city +100000000;
                }
                allEvents.push_back(tmpEvent);
            }
            else{
                tmpString = tmpString+belong+" "+name+" "+to_str(index)+" has no weapon"+"\n";
                event tmpEvent = {city,15,Hour,55,tmpString};
                if(belong == "blue"){
                    tmpEvent.cityIndex = city +100000000;
                }
                allEvents.push_back(tmpEvent);
            }
        }
    }
};
class Iceman:public Warrior{
public:
    Iceman(){name = "iceman";}
    Iceman(int _life, int _attack, int _city, string _belong, Weapon _weapon):Warrior(_life, _attack, _city, _belong, _weapon){
        name = "iceman";
        status = 1;
    }
    Iceman(const Iceman& i):Warrior(i){}
    Iceman(const Warrior& w):Warrior(w){};
    Iceman& operator=(const Iceman& i){
        Warrior::operator=(i);
        return *this;
    }

    virtual void walk(int step){
        if(status == 1){
            city += step;//Similarly, can either be 1 or -1
            stepsWalked += 1;
            if(stepsWalked%2 == 0 && stepsWalked != 0){
                if(life > 0 && life != 1){
                    life -= 9;
                    if(life <= 0){
                        life = 1;
                    }
                    setAttack(getAttack() + 20);
                }
            }
        }
    }

};
class Lion:public Warrior{
public:
    Lion(){name = "lion";}
    Lion(int _life, int _attack, int _city, string _belong, int _loyalty, int _increment):Warrior(_life, _attack, _city,_belong,_loyalty,_increment){
        name = "lion";
        status = 1;
    }
    Lion(const Lion& l):Warrior(l){weapon.clear();}
    Lion(const Warrior& w):Warrior(w){weapon.clear();};
    Lion& operator=(const Lion& l){
        Warrior::operator=(l);
        weapon.clear();
        return *this;
    }
    virtual void lifeTransfer(Warrior* w){
        w->setLife(w->getLife() + preLife);
    }
    virtual void hurt(int lostLife){
        life -= lostLife;
        if(life <= 0){
            beingKilled();
            preLife = life + lostLife;
        }

    }
    virtual void lowerLoy(){
        loyalty -= increment;
    }
};
class Wolf:public Warrior{
public:
    Wolf(){name = "wolf";}
    Wolf(int _life, int _attack, int _city, string _belong):Warrior(_life, _attack, _city,_belong){
        name = "wolf";
        status = 1;
    }
    Wolf(const Wolf& w):Warrior(w){}
    Wolf(const Warrior& w):Warrior(w){};
    Wolf& operator=(const Wolf& w){
        Warrior::operator=(w);
        return *this;
    }
    virtual void pickUpWeapon(Warrior* w){
        for(int i=0; i<w->weapon.size(); i++){
            int count = 0;
            for(int j=0; j<weapon.size();j++){
                if(w->weapon[i]->index == weapon[j]->index){
                    count += 1;
                }
            }
            if(count == 0){
                weapon.push_back(w->weapon[i]);
            }
        }
    }
    virtual void reportWeapon(){
        if(status > 0){
            string tmpString = "";
            if(weapon.size() > 0){
                // int count = 0;
                string tmpString = "";
                int numWeapon = weapon.size();
                int weaponIndex;
                int count = 0;
                int findWeapon = 0;
                int numWeaponFound = 0;
                tmpString = tmpString+belong+" "+name+" "+to_str(index)+" has ";

                while(count < 3){
                    findWeapon = 0;
                    for(int i=0; i<numWeapon; i++){
                        weaponIndex = weapon[i]->index;
                        if (weaponIndex == 3-count){
                            if((count == 1 || count == 2) && (numWeaponFound != 0)){
                                tmpString = tmpString + ",";
                            }
                            switch(weaponIndex){
                                case 1:tmpString = tmpString+weapon[i]->name+"("+to_str(weapon[i]->getAttack())+")";
                                break;
                                case 2:tmpString = tmpString+weapon[i]->name;
                                break;
                                case 3:tmpString = tmpString+weapon[i]->name+"("+to_str(weapon[i]->getEndurance())+")";
                                break;
                            }
                            findWeapon = 1;
                            numWeaponFound += 1;
                            count += findWeapon;
                            break;
                        }
                        else{
                            continue;
                        }
                    }
                    if(findWeapon == 0){
                        count += 1;
                    }
                }

                tmpString =tmpString+"\n";
                event tmpEvent = {city,15,Hour,55,tmpString};
                if(belong == "blue"){
                    tmpEvent.cityIndex = city +100000000;
                }
                allEvents.push_back(tmpEvent);
            }
            else{
                tmpString = tmpString+belong+" "+name+" "+to_str(index)+" has no weapon"+"\n";
                event tmpEvent = {city,15,Hour,55,tmpString};
                if(belong == "blue"){
                    tmpEvent.cityIndex = city +100000000;
                }
                allEvents.push_back(tmpEvent);
            }
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

    //The buffer is to store the warrios that have left
    Warrior* RedBuffer;
    Warrior* BlueBuffer;

    Warrior tmpW;

    int RcontinuousWinning = 0;
    int BcontinuousWinning = 0;
    City(){}
    City(int _numWarrior, int _occupied, int _numLife):
    numWarrior(_numWarrior),occupied(_occupied),numLife(_numLife){
        RedWarrior = &tmpW;
        BlueWarrior = &tmpW;
        RedBuffer = &tmpW;
        BlueBuffer = &tmpW;

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
    ~City(){}
    void generateLife(){
        numLife += 10;
    }

    int lifePickedUp(){
        int tmp = numLife;
        numLife = 0;
        return tmp;
    }
    int getPrivilege(){return privilege;}
    int getOccupied(){return occupied;}
    void decidePrivilege(int index){
        if(occupied == -1){
            if( index%2 == 1 ){
                privilege = 0;
            }
            else if( index%2 == 0 ){
                privilege = 1;
            }
        }
        else{
            if(occupied == 1){
                privilege = 0;
            }
            else if(occupied == 0){
                privilege = 1;
            }
        }
    }

    void setOccupied(int headquarter){
        occupied = headquarter;
    }

    void warriorLeave(string headquarter){
        if(headquarter == "red"){
            RedBuffer = RedWarrior;
            RedWarrior = &tmpW;
        }
        else if(headquarter == "blue"){
            BlueBuffer = BlueWarrior;
            BlueWarrior = &tmpW;
        }
    }
    void newWarriorCome(Warrior* w){
        if(w->belong == "red"){
            RedWarrior = w;
        }
        else if(w->belong == "blue"){
            BlueWarrior = w;
        }
    }
};

class Headquarter{
private:
    Warrior* sequence[5];//Store the sequence according to which the headquarter generates new warrior
    Headquarter* otherHead;
    string name; //red or blue
    int selfIndex=-1; //The index of all warriors in each headquarter
    int MinLife;
    int numCity;
    int attackArrow;
    int loyaltyDownIncre;
    int timerMins[10];
    vector<Warrior*> warriors;
    vector<City*> allCities;

    // City** allCities = new City*[numCity];
public:
    int numEnemy=0; //How many enemies have already exisited in this city
    // int hour = 0;
    int totLife;
    int lifeAcc = 0;
    Headquarter(std::string _name, int _totLife, int _numCity, Warrior** _sequence,City** _allCities, int _attackArrow, int _loyaltyDownIncre):
    name(_name),totLife(_totLife),numCity(_numCity),attackArrow(_attackArrow),loyaltyDownIncre(_loyaltyDownIncre){
        for(int i=0; i<numCity; i++){
            allCities.push_back(_allCities[i]);
            // allCities[i] = _allCities[i];
        }
        for (int i=0; i<5; i++){
            sequence[i] = _sequence[i];
        }
        timerMins[0] = 0; timerMins[1] = 5; timerMins[2] = 10; timerMins[3] = 20;
        timerMins[4] = 30; timerMins[5] = 35; timerMins[6] = 38; timerMins[7] = 40;
        timerMins[8] = 50; timerMins[9] = 55;
        selfIndex = -1;
    }
    ~Headquarter(){
        for(vector<Warrior*>::iterator it = warriors.begin(); it != warriors.end(); it++){
            delete (*it);
        }
        warriors.clear();
    }

    void knowOtherQuater(Headquarter* head){
        otherHead = head;
    }
    void rewardLife(Warrior* w);

    bool generate();
    void lionRunAway();
    void warriorMove();

    void addUpLife(){
        totLife += lifeAcc;
        lifeAcc = 0;
    }
    void pickUpLife();
    void useArrow();
    void useBoom();
    void battle();
    void reportLife();
    void checkWeapon();
    void reportWeapon();
    bool beingOccupied();
};

bool Headquarter::generate(){
    selfIndex += 1;
    int seqIndex = selfIndex%5;
    string warriorName = sequence[seqIndex]->name;
    if (sequence[seqIndex]->getLife() <= totLife){
        Warrior* tmpWarrior;
        Weapon* tmpWeapon1;
        Weapon* tmpWeapon2;
        if(warriorName == "dragon"){
            tmpWarrior = new Dragon(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            double tmpMorale = (double)totLife;
            tmpMorale = tmpMorale/tmpWarrior->getLife();

            tmpWarrior->setMorale(tmpMorale);

            int weaponIndex = (selfIndex+1)%3;
            switch(weaponIndex){
                case 0:tmpWeapon1 = new Sword();
                tmpWeapon1->setAttack(floor(0.2*(tmpWarrior->getAttack())));
                break;
                case 1:tmpWeapon1 = new Bomb();
                break;
                case 2:tmpWeapon1 = new Arrow();
                tmpWeapon1->setAttack(attackArrow);
                break;
            }
            tmpWarrior->weapon.clear();
            tmpWarrior->assignWeapon(tmpWeapon1);

            warriors.push_back(tmpWarrior);

            string tmpString = "";
            tmpString = tmpString +name+ " dragon " + to_str(selfIndex+1) +" born" + "\n" + "Its morale is " +\
            to_str(tmpWarrior->getMorale()) +'\n';
            event tmpEvent = {0,1,Hour,0,tmpString};
            if(name == "blue"){
                tmpEvent.cityIndex = numCity + 1;
            }
            allEvents.push_back(tmpEvent);
        }
        else if(warriorName == "ninja"){
            tmpWarrior = new Ninjia(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();

            int weaponIndex = (selfIndex+1)%3;
            switch(weaponIndex){
                case 0:tmpWeapon1 = new Sword(); tmpWeapon2 = new Bomb();
                tmpWeapon1->setAttack(floor(0.2*(tmpWarrior->getAttack())));
                break;
                case 1:tmpWeapon1 = new Bomb(); tmpWeapon2 = new Arrow();
                tmpWeapon2->setAttack(attackArrow);
                break;
                case 2:tmpWeapon1 = new Arrow(); tmpWeapon2 = new Sword();
                tmpWeapon1->setAttack(attackArrow);
                tmpWeapon2->setAttack(floor(0.2*(tmpWarrior->getAttack())));
                break;
            }
            tmpWarrior->weapon.clear();
            tmpWarrior->assignWeapon(tmpWeapon1,tmpWeapon2);

            warriors.push_back(tmpWarrior);

            string tmpString = "";
            tmpString = tmpString + name + " ninja " + to_str(selfIndex+1) + " born" + "\n";
            event tmpEvent = {0,1,Hour,0,tmpString};
            if(name == "blue"){
                tmpEvent.cityIndex = numCity + 1;
            }
            allEvents.push_back(tmpEvent);
        }
        else if(warriorName == "iceman"){
            tmpWarrior = new Iceman(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();

            int weaponIndex = (selfIndex+1)%3;
            switch(weaponIndex){
                case 0:tmpWeapon1 = new Sword();
                tmpWeapon1->setAttack(floor(0.2*(tmpWarrior->getAttack())));
                break;
                case 1:tmpWeapon1 = new Bomb();
                break;
                case 2:tmpWeapon1 = new Arrow();
                tmpWeapon1->setAttack(attackArrow);
                break;
            }
            tmpWarrior->weapon.clear();
            tmpWarrior->assignWeapon(tmpWeapon1);
            warriors.push_back(tmpWarrior);
            string tmpString = "";
            tmpString = tmpString+name+" iceman "+to_str(selfIndex+1)+" born"+"\n";
            event tmpEvent = {0,1,Hour,0,tmpString};
            if(name == "blue"){
                tmpEvent.cityIndex = numCity + 1;
            }
            allEvents.push_back(tmpEvent);
        }
        else if(warriorName == "lion"){
            tmpWarrior = new Lion(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            tmpWarrior->setLoyalty(totLife);
            warriors.push_back(tmpWarrior);

            string tmpString = "";
            tmpString = tmpString+name+" lion "+to_str(selfIndex+1)+" born"+"\n";
            tmpString = tmpString+"Its loyalty is "+to_str(tmpWarrior->getLoyalty())+"\n";
            event tmpEvent = {0,1,Hour,0,tmpString};
            if(name == "blue"){
                tmpEvent.cityIndex = numCity + 1;
            }
            allEvents.push_back(tmpEvent);
        }
        else if(warriorName == "wolf"){
            tmpWarrior = new Wolf(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            warriors.push_back(tmpWarrior);

            string tmpString = "";
            tmpString = tmpString+name+" wolf "+to_str(selfIndex+1)+" born"+"\n";
            event tmpEvent = {0,1,Hour,0,tmpString};
            if(name == "blue"){
                tmpEvent.cityIndex = numCity + 1;
            }
            allEvents.push_back(tmpEvent);
        }


        if(name == "blue"){
            warriors[warriors.size()-1]->setCity(numCity+1);
        }
        else{
            warriors[warriors.size()-1]->setCity(0);
        }
        warriors[warriors.size()-1]->setIndex(selfIndex+1);
        return true;
    }
    else{
        selfIndex -= 1;
        return false;
    }
}
void Headquarter::lionRunAway(){
    for(vector<Warrior*>::iterator it = warriors.begin(); it != warriors.end(); it++){
        if((*it)->name == "lion" && (*it)->getLoyalty() <= 0 && (*it)->getStatus() > 0){
            if(name == "red"){
                if((*it)->getCity() != numCity+1){
                    (*it)->setStatus(-2);

                    string tmpString = "";
                    tmpString = tmpString+name+" lion "+to_str((*it)->getIndex())+" ran away"+"\n";
                    event tmpEvent = {(*it)->getCity(),2,Hour,5,tmpString};
                    allEvents.push_back(tmpEvent);
                }
            }
            else{
                if((*it)->getCity() != 0){
                    (*it)->setStatus(-2);

                    string tmpString = "";
                    tmpString = tmpString+name+" lion "+to_str((*it)->getIndex())+" ran away"+"\n";
                    event tmpEvent = {(*it)->getCity(),2,Hour,5,tmpString};
                    allEvents.push_back(tmpEvent);
                }
            }
        }
    }
}
void Headquarter::warriorMove(){
    if(name == "red"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->getCity() != numCity+1 && (*it)->getStatus() > 0){
                int CurrentCity = (*it)->getCity();
                (*it)->walk(1);
                if (CurrentCity !=0 && CurrentCity != numCity){
                    allCities[CurrentCity-1]->warriorLeave("red");//allCities are indexed starting from 0 rather than 1
                    allCities[CurrentCity]->newWarriorCome(*it);

                    string tmpString = "";
                    tmpString = tmpString+name+" "+(*it)->name+" "+to_str((*it)->getIndex())+" marched to city "+to_str(CurrentCity+1)+" with "\
                    +to_str((*it)->getLife())+" elements and force "+to_str((*it)->getAttack())+"\n";

                    event tmpEvent = {CurrentCity+1,3,Hour,10,tmpString};
                    allEvents.push_back(tmpEvent);

                }
                else if(CurrentCity == numCity){
                    allCities[CurrentCity-1]->warriorLeave("red");//allCities are indexed starting from 0 rather than 1

                    string tmpString = "";
                    tmpString = tmpString+name+" "+(*it)->name+" "+to_str((*it)->getIndex())+" reached blue headquarter with "\
                    +to_str((*it)->getLife())+" elements and force "+to_str((*it)->getAttack())+"\n";

                    event tmpEvent = {CurrentCity+1,3,Hour,10,tmpString};
                    allEvents.push_back(tmpEvent);

                    (*it)->setCity(numCity+1);
                    otherHead->numEnemy += 1;

                }
                else if(CurrentCity == 0){
                    allCities[CurrentCity]->newWarriorCome(*it);

                    string tmpString = "";
                    tmpString = tmpString+name+" "+(*it)->name+" "+to_str((*it)->getIndex())+" marched to city "+to_str(CurrentCity+1)+" with "\
                    +to_str((*it)->getLife())+" elements and force "+to_str((*it)->getAttack())+"\n";

                    event tmpEvent = {CurrentCity+1,3,Hour,10,tmpString};
                    allEvents.push_back(tmpEvent);
                }
            }
            else if((*it)->getCity() != numCity+1 && (*it)->getCity() != 0 && (*it)->getStatus() <= 0){
                allCities[(*it)->getCity()-1]->warriorLeave("red");
            }
        }
    }
    else if(name == "blue"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->getCity() != 0 && (*it)->getStatus() > 0){
                int CurrentCity = (*it)->getCity();
                (*it)->walk(-1);
                if (CurrentCity != numCity+1 && CurrentCity != 1){
                    allCities[CurrentCity-1]->warriorLeave("blue");
                    allCities[CurrentCity-2]->newWarriorCome(*it);

                    string tmpString = "";
                    tmpString = tmpString+name+" "+(*it)->name+" "+to_str((*it)->getIndex())+" marched to city "+to_str(CurrentCity-1)+" with "\
                    +to_str((*it)->getLife())+" elements and force "+to_str((*it)->getAttack())+"\n";

                    event tmpEvent = {CurrentCity-1,3,Hour,10,tmpString};
                    allEvents.push_back(tmpEvent);
                }
                else if(CurrentCity == 1){
                    allCities[CurrentCity-1]->warriorLeave("blue");

                    string tmpString = "";
                    tmpString = tmpString+name+" "+(*it)->name+" "+to_str((*it)->getIndex())+" reached red headquarter with "\
                    +to_str((*it)->getLife())+" elements and force "+to_str((*it)->getAttack())+"\n";

                    event tmpEvent = {0,2,Hour,10,tmpString};
                    allEvents.push_back(tmpEvent);

                    (*it)->setCity(0);
                    otherHead->numEnemy += 1;
                }
                else if(CurrentCity == numCity+1){
                    allCities[CurrentCity-2]->newWarriorCome(*it);

                    string tmpString = "";
                    tmpString = tmpString+name+" "+(*it)->name+" "+to_str((*it)->getIndex())+" marched to city "+to_str(CurrentCity-1)+" with "\
                    +to_str((*it)->getLife())+" elements and force "+to_str((*it)->getAttack())+"\n";

                    event tmpEvent = {CurrentCity-1,3,Hour,10,tmpString};
                    allEvents.push_back(tmpEvent);
                }
            }
            else if((*it)->getCity() != numCity+1 && (*it)->getCity() != 0 && (*it)->getStatus() <= 0){
                allCities[(*it)->getCity()-1]->warriorLeave("blue");
            }
        }
    }
}
void Headquarter::pickUpLife(){
    if(name == "red"){
        for(int i=0; i<numCity; i++){
            if (allCities[i]->RedWarrior->getStatus() == 1 && allCities[i]->BlueWarrior->getStatus() <= 0){
                int lifeHere = allCities[i]->lifePickedUp();
                totLife += lifeHere;

                string tmpString = "";
                tmpString = tmpString+"red "+allCities[i]->RedWarrior->name+" "+to_str(allCities[i]->RedWarrior->getIndex())+\
                " earned "+to_str(lifeHere)+" elements for his headquarter"+"\n";

                event tmpEvent = {i+1,10,Hour,30,tmpString};
                allEvents.push_back(tmpEvent);
            }
        }
    }
    else if(name == "blue"){
        for(int i=0; i<numCity; i++){
            if (allCities[i]->BlueWarrior->getStatus() == 1 && allCities[i]->RedWarrior->getStatus() <= 0){
                int lifeHere = allCities[i]->lifePickedUp();
                totLife += lifeHere;

                string tmpString = "";
                tmpString = tmpString+"blue "+allCities[i]->BlueWarrior->name+" "+to_str(allCities[i]->BlueWarrior->getIndex())+\
                " earned "+to_str(lifeHere)+" elements for his headquarter"+"\n";

                event tmpEvent = {i+1,10,Hour,30,tmpString};
                allEvents.push_back(tmpEvent);
            }
        }
    }
}
void Headquarter::useArrow(){
    for(int i=0; i<numCity;i++){
        Warrior* active;
        Warrior* negative;
        if(name == "red" && i != numCity-1){
            active = allCities[i]->RedWarrior;
            negative = allCities[i+1]->BlueWarrior;
        }
        else if(name == "blue" && i != 0){
            active = allCities[i]->BlueWarrior;
            negative = allCities[i-1]->RedWarrior;
        }
        else{
            continue;
        }

        if( ((name == "red" && (active->getStatus() == 1 ) && negative->getStatus() == 1)) || \
        ((name == "blue" && (active->getStatus() == 1 ||  active->getStatus() == -1) && negative->getStatus() == 1)) ){
            bool whetherShot = active->releaseArrow(negative);
            if (whetherShot == true){
                if(negative->getLife() <= 0){
                    negative->setStatus(-1);

                    string tmpString = "";
                    tmpString = tmpString+name+" "+active->name+" "+to_str(active->getIndex())+" shot and killed "+\
                    negative->belong+" "+negative->name+" "+to_str(negative->getIndex())+"\n";

                    event tmpEvent = {i+1,4,Hour,35,tmpString};
                    allEvents.push_back(tmpEvent);
                }
                else{
                    string tmpString = "";
                    tmpString = tmpString+name+" "+active->name+" "+to_str(active->getIndex())+" shot"+"\n";

                    event tmpEvent = {i+1,4,Hour,35,tmpString};
                    allEvents.push_back(tmpEvent);
                }
            }
        }
    }
}
void Headquarter::useBoom(){
    Warrior* active;
    Warrior* negative;
    if(name == "red"){
        for(int i=0; i<numCity; i++){
            active = allCities[i]->RedWarrior;
            negative = allCities[i]->BlueWarrior;
            if(active->getStatus() <= 0){
                break;
            }
            for(int j=0; j<active->weapon.size();j++){
                if(active->weapon[j]->index != 2){
                    continue;
                }
            // for(vector<Weapon*>::iterator wp=active->weapon.begin(); wp != active->weapon.end();wp++){
                if( (allCities[i]->getPrivilege() == 1 && negative->getTotalAttack() >= active->getLife()) ||\
                (allCities[i]->getPrivilege() == 0 && active->getTotalAttack() < negative->getLife()\
                && negative->getTotalFightBack() >= active->getLife()) ){
                    active->weapon[j]->damage();
                    active->setStatus(-2); negative->setStatus(-2);

                    string tmpString = "";
                    tmpString = tmpString+name+" "+active->name+" "+to_str(active->getIndex())+" used a bomb and killed "+\
                    negative->belong+" "+negative->name+" "+to_str(negative->getIndex())+"\n";

                    event tmpEvent = {i+1,5,Hour,38,tmpString};
                    allEvents.push_back(tmpEvent);
                }
            }
        }
    }
    else if(name == "blue"){
        for(int i=0; i<numCity; i++){
            active = allCities[i]->BlueWarrior;
            negative = allCities[i]->RedWarrior;
            if(active->getStatus() <= 0){
                break;
            }
            for(int j=0; j<active->weapon.size();j++){
                if(active->weapon[j]->index != 2){
                    continue;
                }
            // for(vector<Weapon*>::iterator wp=active->weapon.begin(); wp != active->weapon.end();wp++){
                if( (allCities[i]->getPrivilege() == 0 && negative->getTotalAttack() >= active->getLife()) ||\
                (allCities[i]->getPrivilege() == 1 && active->getTotalAttack() < negative->getLife()\
                && negative->getTotalFightBack() >= active->getLife()) ){
                    active->weapon[j]->damage();
                    active->setStatus(-2); negative->setStatus(-2);

                    string tmpString = "";
                    tmpString = tmpString+name+" "+active->name+" "+to_str(active->getIndex())+" used a bomb and killed "+\
                    negative->belong+" "+negative->name+" "+to_str(negative->getIndex())+"\n";

                    event tmpEvent = {i+1,5,Hour,38,tmpString};
                    allEvents.push_back(tmpEvent);
                }
            }
        }
    }
}
void Headquarter::rewardLife(Warrior* w){
    if(totLife >= 8){
        totLife -= 8;
        w->setLife(w->getLife()+8);
    }
}
void Headquarter::battle(){
    Warrior* active;
    Warrior* negative;
    if (name == "red"){
        for(int i=0; i<numCity; i++){
            active = allCities[i]->RedWarrior;
            negative = allCities[i]->BlueWarrior;
            if(allCities[i]->getPrivilege() == 0){
                //Red has the privilege
                if(active->getStatus() == 1 && negative->getStatus() == 1){

                    active->fight(negative);
                    //Print info
                    string tmpString = "";
                    tmpString = tmpString+"red "+active->name+" "+to_str(active->getIndex())+" attacked blue "+negative->name+\
                    " "+to_str(negative->getIndex())+" in city "+to_str(i+1)+" with "+to_str(active->getLife())+\
                    " elements and force "+to_str(active->getAttack())+"\n";

                    event tmpEvent = {i+1,6,Hour,40,tmpString};
                    allEvents.push_back(tmpEvent);

                    //didn't kill the enemy. Enemy fightback
                    if(negative->getStatus() == 1 && negative->name != "ninja"){
                        negative->fightBack(active);
                        //Print info
                        string tmpString = "";
                        tmpString = tmpString+"blue "+negative->name+" "+to_str(negative->getIndex())+" fought back against red "+\
                        active->name+" "+to_str(active->getIndex())+" in city "+to_str(i+1)+"\n";

                        event tmpEvent = {i+1,7,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);

                        //Negative win! Killed by fight back
                        if(active->getStatus() == 0){
                            string tmpString = "";
                            tmpString = tmpString+"red "+active->name+" "+to_str(negative->getIndex())+" was killed in city "+to_str(i+1)+"\n";
                            event tmpEvent = {i+1,8,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);

                            /*Reward 8 life elements*/
                            otherHead->rewardLife(negative);

                            /*Immediately get the life in this city*/
                            int lifeHere = allCities[i]->lifePickedUp();
                            otherHead->lifeAcc += lifeHere;

                            if(lifeHere > 0){
                                string tmpString = "";
                                tmpString = tmpString+"blue "+negative->name+" "+to_str(negative->getIndex())+" earned "+\
                                to_str(lifeHere)+" elements for his headquarter"+"\n";
                                event tmpEvent = {i+1,10,Hour,40,tmpString};
                                allEvents.push_back(tmpEvent);
                            }

                            allCities[i]->BcontinuousWinning += 1;
                            active->lifeTransfer(negative);
                            negative->pickUpWeapon(active);
                            negative->moraleUp();
                            /*Blue not yell since it's not an active battle*/
                            if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                                allCities[i]->setOccupied(1);

                                string tmpString = "";
                                tmpString = tmpString+"blue flag raised in city "+to_str(i+1)+"\n";
                                event tmpEvent = {i+1,11,Hour,40,tmpString};
                                allEvents.push_back(tmpEvent);
                            }
                        }
                        //Starting to yell and change morale

                        else{
                            //No one dies. It's a tie.
                            allCities[i]->BcontinuousWinning = 0;
                            active->moraleDown();

                            if(active->name == "dragon"){
                                string tmpString = active->yell();
                                if(tmpString != ""){
                                    event tmpEvent = {i+1,9,Hour,40,tmpString};
                                    allEvents.push_back(tmpEvent);
                                }
                            }
                            active->lowerLoy();
                            negative->lowerLoy();
                            allCities[i]->RcontinuousWinning = 0;
                        }
                    }

                    //Active wins! Killed the enemy
                    else if(negative->getStatus() == 0){

                        string tmpString = "";
                        tmpString = tmpString+"blue "+negative->name+" "+to_str(negative->getIndex())+" was killed in city "+to_str(i+1)+"\n";
                        event tmpEvent = {i+1,8,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);

                        active->moraleUp();
                        /*Reward life*/
                        rewardLife(active);

                        /*Immediately get the life in this city*/
                        int lifeHere = allCities[i]->lifePickedUp();
                        lifeAcc += lifeHere;

                        if(lifeHere > 0){
                            string tmpString = "";
                            tmpString = tmpString+"red "+active->name+" "+to_str(active->getIndex())+" earned "+\
                            to_str(lifeHere)+" elements for his headquarter"+"\n";
                            event tmpEvent = {i+1,10,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);
                        }

                        if(active->name == "dragon"){
                            string tmpString = active->yell();
                            if(tmpString != ""){
                                event tmpEvent = {i+1,9,Hour,40,tmpString};
                                allEvents.push_back(tmpEvent);
                            }
                        }
                        allCities[i]->RcontinuousWinning += 1;
                        negative->lifeTransfer(active);
                        active->pickUpWeapon(negative);
                        if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                            allCities[i]->setOccupied(0);

                            string tmpString = "";
                            tmpString = tmpString+"red flag raised in city "+to_str(i+1)+"\n";
                            event tmpEvent = {i+1,11,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);
                        }
                    }
                    else{//No one dies. It's tie.
                        allCities[i]->BcontinuousWinning = 0;
                        active->moraleDown();
                        if(active->name == "dragon"){
                            string tmpString = active->yell();
                            if(tmpString != ""){
                                event tmpEvent = {i+1,9,Hour,40,tmpString};
                                allEvents.push_back(tmpEvent);
                            }
                        }
                        active->lowerLoy();
                        negative->lowerLoy();
                        allCities[i]->BcontinuousWinning = 0;
                    }
                }
                //Active wins! It was shot by the arrow
                else if(active->getStatus() == 1 && negative->getStatus() == -1){
                    /*No life reward since it's already died before min 40*/
                    /*Immediately get the life in this city*/
                    rewardLife(active);
                    int lifeHere = allCities[i]->lifePickedUp();
                    lifeAcc += lifeHere;

                    if(lifeHere > 0){
                        string tmpString = "";
                        tmpString = tmpString+"red "+active->name+" "+to_str(active->getIndex())+" earned "+\
                        to_str(lifeHere)+" elements for his headquarter"+"\n";
                        event tmpEvent = {i+1,10,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);
                    }

                    allCities[i]->RcontinuousWinning += 1;
                    active->moraleUp();

                    if(active->name == "dragon"){
                        string tmpString = active->yell();
                        if(tmpString != ""){
                            event tmpEvent = {i+1,9,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);
                        }
                    }
                    negative->lifeTransfer(active);
                    active->pickUpWeapon(negative);
                    if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                        allCities[i]->setOccupied(0);

                        string tmpString = "";
                        tmpString = tmpString+"red flag raised in city "+to_str(i+1)+"\n";
                        event tmpEvent = {i+1,11,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);
                    }
                }
            }
            else if(allCities[i]->getPrivilege() == 1){
                //Still possible to win since the other warrior may be shot do deatth
                if(active->getStatus() == 1 && negative->getStatus() == -1){
                    /*No life reward since it's already died before min 40*/
                    /*Immediately get the life in this city*/
                    rewardLife(active);
                    int lifeHere = allCities[i]->lifePickedUp();
                    lifeAcc += lifeHere;

                    if(lifeHere > 0){
                        string tmpString = "";
                        tmpString = tmpString+"red "+active->name+" "+to_str(active->getIndex())+" earned "+\
                        to_str(lifeHere)+" elements for his headquarter"+"\n";
                        event tmpEvent = {i+1,10,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);
                    }

                    allCities[i]->RcontinuousWinning += 1;
                    active->moraleUp();

                    if(active->name == "dragon"){
                        string tmpString = active->yell();
                        if(tmpString != ""){
                            event tmpEvent = {i+1,9,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);
                        }
                    }
                    negative->lifeTransfer(active);
                    active->pickUpWeapon(negative);
                    if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                        allCities[i]->setOccupied(0);

                        string tmpString = "";
                        tmpString = tmpString+"red flag raised in city "+to_str(i+1)+"\n";
                        event tmpEvent = {i+1,11,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);
                    }
                }
            }
        }
    }
    else if(name == "blue"){
        for(int i=numCity-1; i>=0; i--){
            active = allCities[i]->BlueWarrior;
            negative = allCities[i]->RedWarrior;
            if(allCities[i]->getPrivilege() == 1){
                //Blue has the privilege
                if(active->getStatus() == 1 && negative->getStatus() == 1){
                    active->fight(negative);
                    //Print info
                    string tmpString = "";
                    tmpString = tmpString+"blue "+active->name+" "+to_str(active->getIndex())+" attacked red "+negative->name+\
                    " "+to_str(negative->getIndex())+" in city "+to_str(i+1)+" with "+to_str(active->getLife())+\
                    " elements and force "+to_str(active->getAttack())+"\n";

                    event tmpEvent = {i+1,6,Hour,40,tmpString};
                    allEvents.push_back(tmpEvent);

                    //Enemy fought back
                    if(negative->getStatus() == 1 && negative->name != "ninja"){
                        negative->fightBack(active);

                        //Print info
                        string tmpString = "";
                        tmpString = tmpString+"red "+negative->name+" "+to_str(negative->getIndex())+" fought back against blue "+\
                        active->name+" "+to_str(active->getIndex())+" in city "+to_str(i+1)+"\n";

                        event tmpEvent = {i+1,7,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);

                        //Negative wins! Killed by fightBack
                        if(active->getStatus() == 0){
                            string tmpString = "";
                            tmpString = tmpString+"blue "+active->name+" "+to_str(active->getIndex())+" was killed in city "+to_str(i+1)+"\n";
                            event tmpEvent = {i+1,8,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);

                            /*Reward life*/
                            otherHead->rewardLife(negative);
                            /*Immediately get the life in this city*/
                            int lifeHere = allCities[i]->lifePickedUp();
                            otherHead->lifeAcc += lifeHere;

                            if(lifeHere > 0){
                                string tmpString = "";
                                tmpString = tmpString+"red "+negative->name+" "+to_str(negative->getIndex())+" earned "+\
                                to_str(lifeHere)+" elements for his headquarter"+"\n";
                                event tmpEvent = {i+1,10,Hour,40,tmpString};
                                allEvents.push_back(tmpEvent);
                            }

                            allCities[i]->RcontinuousWinning += 1;
                            active->lifeTransfer(negative);
                            negative->pickUpWeapon(active);
                            negative->moraleUp();
                            if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                                allCities[i]->setOccupied(0);

                                string tmpString = "";
                                tmpString = tmpString+"red flag raised in city "+to_str(i+1)+"\n";
                                event tmpEvent = {i+1,11,Hour,40,tmpString};
                                allEvents.push_back(tmpEvent);
                            }
                        }
                        else{
                            //No one dies. It's a tie.
                            allCities[i]->BcontinuousWinning = 0;
                            active->moraleDown();

                            if(active->name == "dragon"){
                                string tmpString = active->yell();
                                if(tmpString != ""){
                                    event tmpEvent = {i+1,9,Hour,40,tmpString};
                                    allEvents.push_back(tmpEvent);
                                }
                            }
                            negative->lowerLoy();
                            active->lowerLoy();
                            allCities[i]->RcontinuousWinning = 0;
                        }
                    }

                    /*Active wins!*/
                    else if(negative->getStatus() == 0){

                        string tmpString = "";
                        tmpString = tmpString+"red "+negative->name +" "+to_str(negative->getIndex())+" was killed in city "+to_str(i+1)+"\n";
                        event tmpEvent = {i+1,8,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);

                        /*Reward life*/
                        rewardLife(active);

                        /*Immediately get the life in this city*/
                        int lifeHere = allCities[i]->lifePickedUp();
                        lifeAcc += lifeHere;

                        if(lifeHere > 0){
                            string tmpString = "";
                            tmpString = tmpString+"blue "+active->name+" "+to_str(active->getIndex())+" earned "+\
                            to_str(lifeHere)+" elements for his headquarter"+"\n";
                            event tmpEvent = {i+1,10,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);
                        }

                        allCities[i]->BcontinuousWinning += 1;
                        active->moraleUp();

                        if(active->name == "dragon"){
                            string tmpString = active->yell();
                            if(tmpString != ""){
                                event tmpEvent = {i+1,9,Hour,40,tmpString};
                                allEvents.push_back(tmpEvent);
                            }
                        }
                        negative->lifeTransfer(active);
                        active->pickUpWeapon(negative);
                        if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                            allCities[i]->setOccupied(1);

                            string tmpString = "";
                            tmpString = tmpString+"blue flag raised in city "+to_str(i+1)+"\n";
                            event tmpEvent = {i+1,11,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);
                        }
                    }
                    else{
                        //No one dies. It's tie.
                        allCities[i]->BcontinuousWinning = 0;
                        active->moraleDown();
                        if(active->name == "dragon"){
                            string tmpString = active->yell();
                            if(tmpString != ""){
                                event tmpEvent = {i+1,9,Hour,40,tmpString};
                                allEvents.push_back(tmpEvent);
                            }
                        }
                        negative->lowerLoy();
                        active->lowerLoy();
                        allCities[i]->RcontinuousWinning = 0;
                    }
                }
                /*Active wins! Shot by arrow*/
                else if(active->getStatus() == 1 && negative->getStatus() == -1){
                    /*No life reward since it's already dide before min40*/
                    /*Immediately get the life in this city*/
                    rewardLife(active);
                    int lifeHere = allCities[i]->lifePickedUp();
                    lifeAcc += lifeHere;

                    if(lifeHere > 0){
                        string tmpString = "";
                        tmpString = tmpString+"blue "+active->name+" "+to_str(active->getIndex())+" earned "+\
                        to_str(lifeHere)+" elements for his headquarter"+"\n";
                        event tmpEvent = {i+1,10,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);
                    }


                    allCities[i]->BcontinuousWinning += 1;
                    active->moraleUp();

                    if(active->name == "dragon"){
                        string tmpString = active->yell();
                        if(tmpString != ""){
                            event tmpEvent = {i+1,9,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);
                        }
                    }
                    negative->lifeTransfer(active);
                    active->pickUpWeapon(negative);
                    if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                        allCities[i]->setOccupied(1);
                        string tmpString = "";
                        tmpString = tmpString+"blue flag raised in city "+to_str(i+1)+"\n";
                        event tmpEvent = {i+1,11,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);
                    }
                }
            }
            else if(allCities[i]->getPrivilege() == 0){
                //Still possible to win since the other warrior may be shot do deatth
                if(active->getStatus() == 1 && negative->getStatus() == -1){
                    /*No life reward since it's already died before min 40*/
                    /*Immediately get the life in this city*/
                    rewardLife(active);
                    int lifeHere = allCities[i]->lifePickedUp();
                    lifeAcc += lifeHere;

                    if(lifeHere > 0){
                        string tmpString = "";
                        tmpString = tmpString+"blue "+active->name+" "+to_str(active->getIndex())+" earned "+\
                        to_str(lifeHere)+" elements for his headquarter"+"\n";
                        event tmpEvent = {i+1,10,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);
                    }

                    allCities[i]->RcontinuousWinning += 1;
                    active->moraleUp();

                    if(active->name == "dragon"){
                        string tmpString = active->yell();
                        if(tmpString != ""){
                            event tmpEvent = {i+1,9,Hour,40,tmpString};
                            allEvents.push_back(tmpEvent);
                        }
                    }
                    negative->lifeTransfer(active);
                    active->pickUpWeapon(negative);
                    if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                        allCities[i]->setOccupied(0);

                        string tmpString = "";
                        tmpString = tmpString+"blue flag raised in city "+to_str(i+1)+"\n";
                        event tmpEvent = {i+1,11,Hour,40,tmpString};
                        allEvents.push_back(tmpEvent);
                    }
                }
            }
        }
    }
}
void Headquarter::reportLife(){
    string tmpString = "";
    tmpString = tmpString + to_str(totLife)+" elements in "+name+" headquarter"+"\n";
    if(name == "red"){
        event tmpEvent = {0,14,Hour,50,tmpString};
        allEvents.push_back(tmpEvent);
    }
    else if(name == "blue"){
        event tmpEvent = {numCity+1,14,Hour,50,tmpString};
        allEvents.push_back(tmpEvent);
    }
}
void Headquarter::checkWeapon(){
    for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
        (*it)->checkWeapon();
    }
}
void Headquarter::reportWeapon(){
    for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
        if((*it)->getStatus()>0){
            (*it)->reportWeapon();
        }
    }
}
bool Headquarter::beingOccupied(){
    if(numEnemy == 2){
        return true;
    }
    else{
        return false;
    }
}

bool eventCompare(const event i, const event j){
    if(i.hour < j.hour){
        return true;
    }
    else if(i.hour > j.hour){
        return false;
    }
    else{
        if(i.min < j.min){
            return true;
        }
        else if(i.min > j.min){
            return false;
        }
        else{
            if(i.cityIndex < j.cityIndex){
                return true;
            }
            else if(i.cityIndex > j.cityIndex){
                return false;
            }
            else{
                if(i.eventIndex < j.eventIndex){
                    return true;
                }
                else if(i.eventIndex > j.eventIndex){
                    return false;
                }
                else{
                    if(i.thingsHappened.find("red") != string::npos && j.thingsHappened.find("blue") != string::npos){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
        }
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

    int* l1 = new int[caseNum]; int* at1 = new int[caseNum];//dragon
    int* l2 = new int[caseNum]; int* at2 = new int[caseNum];//Ninjia
    int* l3 = new int[caseNum]; int* at3 = new int[caseNum];//iceman
    int* l4 = new int[caseNum]; int* at4 = new int[caseNum];//lion
    int* l5 = new int[caseNum]; int* at5 = new int[caseNum];//wolf
    for (int i=0;i<caseNum;i++){
        cin>>inM[i]>>inN[i]>>inR[i]>>inK[i]>>inT[i];
        cin>>l1[i]>>l2[i]>>l3[i]>>l4[i]>>l5[i];
        cin>>at1[i]>>at2[i]>>at3[i]>>at4[i]>>at5[i];
    }

    for (int i=0;i<caseNum; i++){
        Warrior* seqRed[5];
        Warrior* seqBlue[5];
        City** allCities = new City*[inN[i]];


        Weapon nullWeapon;
        seqRed[0] = new Iceman(l3[i],at3[i],0,"red",nullWeapon);
        seqRed[1] = new Lion(l4[i],at4[i],0,"red",inM[i],inK[i]);
        seqRed[2] = new Wolf(l5[i],at5[i],0,"red");
        seqRed[3] = new Ninjia(l2[i],at2[i],0,"red",nullWeapon,nullWeapon);
        seqRed[4] = new Dragon(l1[i],at1[i],0,"red",nullWeapon,inM[i]);

        seqBlue[3] = new Iceman(l3[i],at3[i],inN[i],"blue",nullWeapon);
        seqBlue[0] = new Lion(l4[i],at4[i],inN[i],"blue",inM[i],inK[i]);
        seqBlue[4] = new Wolf(l5[i],at5[i],inN[i],"blue");
        seqBlue[2] = new Ninjia(l2[i],at2[i],inN[i],"blue",nullWeapon,nullWeapon);
        seqBlue[1] = new Dragon(l1[i],at1[i],inN[i],"blue",nullWeapon,inM[i]);

        for(int j=0; j<inN[i]; j++){
            allCities[j] = new City(0,-1,0);
            allCities[j]->decidePrivilege(j+1);
        }

        Headquarter red("red",inM[i],inN[i],seqRed, allCities,inR[i],inK[i]);
        Headquarter blue("blue",inM[i],inN[i],seqBlue, allCities,inR[i],inK[i]);

        red.knowOtherQuater(&blue);
        blue.knowOtherQuater(&red);

        cout<<"Case:"<<i+1<<"\n";

        bool redOccupied = false;
        bool blueOccupied = false;

        while(redOccupied == false && blueOccupied == false){
            red.generate();
            blue.generate();

            red.lionRunAway();
            blue.lionRunAway();

            red.warriorMove();
            blueOccupied = blue.beingOccupied();
            if(blueOccupied == true){
                string tmpString = "blue headquarter was taken\n";
                event tmpEvent = {inN[i]+1,13,Hour,10,tmpString};
                allEvents.push_back(tmpEvent);
            }
            blue.warriorMove();
            redOccupied = red.beingOccupied();
            if(redOccupied == true){
                string tmpString = "red headquarter was taken\n";
                event tmpEvent = {0,13,Hour,10,tmpString};
                allEvents.push_back(tmpEvent);
            }

            if(redOccupied == true || blueOccupied == true || Hour >= inT[i]/60+1){
                sort(allEvents.begin(),allEvents.end(),eventCompare);
                for(vector<event>::iterator it = allEvents.begin(); it != allEvents.end(); it++){
                    if( ((*it).hour)*60+(*it).min <= inT[i] ){
                        cout<<setfill('0')<<setw(3)<<(*it).hour<<":"<<setfill('0')<<setw(2)<<(*it).min<<" "<<(*it).thingsHappened;
                    }
                }
                allEvents.clear();
                break;
            }

            for(int j=0; j<inN[i]; j++){
                allCities[j]->generateLife();
            }

            red.pickUpLife();
            blue.pickUpLife();

            red.checkWeapon();
            red.useArrow();
            blue.checkWeapon();
            blue.useArrow();

            red.checkWeapon();
            red.useBoom();
            blue.checkWeapon();
            blue.useBoom();

            red.checkWeapon();
            blue.checkWeapon();

            for(int j=0; j<inN[i]; j++){
                allCities[j]->decidePrivilege(j+1);
            }
            red.battle();
            blue.battle();
            red.addUpLife();
            blue.addUpLife();

            red.reportLife();
            blue.reportLife();

            red.checkWeapon();
            blue.checkWeapon();
            red.reportWeapon();
            blue.reportWeapon();
            Hour += 1;
        }

        Hour = 0;

        for(int j=0; j<5; j++){
            delete seqRed[j];
            delete seqBlue[j];
        }


        for(int j=0; j<inN[i]; j++){
            delete allCities[j];
        }
    }


    delete [] inM, inN, inR, inK, inT;
    delete [] l1, at1;
    delete [] l2, at2;
    delete [] l3, at3;
    delete [] l4, at4;
    delete [] l5, at5;



    return 0;
}
