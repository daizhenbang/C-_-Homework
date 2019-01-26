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
    Bomb& operator=(Bomb& a){Weapon::operator=(a); index=3;return *this;}
    virtual void damage(){
        setEndurance(0);
    }
};
class Arrow:public Weapon{
public:
    Arrow(){index = 3;name = "arrow";}
    Arrow(int _attack):Weapon(_attack){index = 3;name = "arrow";}
    Arrow(const Arrow& a):Weapon(a){index = 3;}
    Arrow& operator=(Arrow& a){Weapon::operator=(a);index=2;return *this;}
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
    int morale;
    int increment;
    int status=0;//0 means dead while 1 means alive
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
    Warrior(int _life, int _attack, int _city, string _belong, int _morale, Weapon _weapon):life(_life),attack(_attack),city(_city),belong(_belong),morale(_morale){
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
        for(vector<Weapon*>::iterator it = weapon.begin(); it != weapon.end(); it++){
            delete (*it);
        }
        weapon.clear();
    }

    void setLife(int _life){life = _life;}
    void setAttack(int _attack){attack = _attack;}
    void setLoyalty(int _loyalty){loyalty = _loyalty;}
    void setCity(int _city){city = _city;}
    void setMorale(int _morale){morale = _morale;}
    void setIndex(int _index){index = _index;}

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
    void releaseArrow(Warrior* w){
        for(int i=0; i<weapon.size(); i++){
            if(weapon[i]->index == 2 && weapon[i]->getEndurance() != 0){
                w->setLife(w->getLife() - weapon[i]->getAttack());
                break;
            }
        }
    }

    virtual void moraleUp(){}
    virtual void moraleDown(){}
    virtual void yell(){
        if(morale > 0.8){
            cout<<"This little dragon yelled"<<endl;
        }
    }

    int getLife(){return life;}
    int getAttack(){return attack;}
    int getCity(){return city;}
    int getLoyalty(){return loyalty;}
    int getStatus(){return status;}
    int getMorale(){return morale;}
    int getIndex(){return index;}

    virtual void hurt(int lostLife){
        life -= lostLife;
        if(life <= 0) beingKilled();
    }
    void ifKilled(){
        if(life <= 0) beingKilled();
    }
    void beingKilled(){
        status = 0;
        attack = 0;
        weapon[0] = &nullWeapon;
        weapon[1] = &nullWeapon;
    }
    virtual void walk(int step){
        if(status != 0) city += step;//can either be 1 or -1
    }
    virtual void lowerLoy(){}
    virtual void lifeTransfer(Warrior* w){}

    int getTotalAttack(){
        int tmpAttack = 0;
        for(int i=0; i<weapon.size(); i++){
            tmpAttack += weapon[i]->getAttack();
        }
        return getAttack() + tmpAttack;
    }
    int getTotalFightBack(){
        int tmpAttack = 0;
        for(int i=0; i<weapon.size(); i++){
            tmpAttack += weapon[i]->getAttack();
        }
        return (floor(getAttack()/2) + tmpAttack);
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
    virtual void reportWeapon(){
        if(weapon.size() > 0 || weapon[0]->getEndurance() > 0){
            if(weapon[0]->getEndurance() != 0){
                switch(weapon[0]->index){
                    case 1:cout<<belong<<" "<<name<<" "<<index<<" has "<<weapon[0]->name<<"("<<weapon[0]->getAttack()<<")"<<endl;
                    case 2:cout<<belong<<" "<<name<<" "<<index<<" has "<<weapon[0]->name<<endl;
                    case 3:cout<<belong<<" "<<name<<" "<<index<<" has "<<weapon[0]->name<<"("<<weapon[0]->getEndurance()<<")"<<endl;
                }
            }
        }
        else{
            cout<<belong<<" "<<name<<" "<<index<<" has no weapon";
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
    virtual void moraleUp(){morale += 0.2;}
    virtual void moraleDown(){morale -= 0.2;}
    virtual void yell(){
        if(morale > 0.8){
            cout<<"dragon "<<getIndex()<<" yelled in city "<<getCity()<<endl;
        }
    }


};
class Ninjia:public Warrior{
public:
    Ninjia(){name = "ninjia";}
    Ninjia(int _life, int _attack, int _city, string _belong, Weapon _weapon1, Weapon _weapon2):Warrior(_life, _attack, _city,_belong,_weapon1, _weapon2){
        name = "ninjia";
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
    virtual void reportWeapon(){
        if(weapon.size() > 0){
            int numWeapon = weapon.size();
            cout<<belong<<" "<<name<<" "<<index<<" has ";
            for(int i=0;i<numWeapon;i++){
                if (weapon[i]->index == 1){
                    cout<<weapon[i]->name<<"("<<weapon[i]->getAttack()<<")";
                    break;
                }
            }
            for(int i=0;i<numWeapon;i++){
                if (weapon[i]->index == 2){
                    cout<<", "<<weapon[i]->name;
                    break;
                }
            }
            for(int i=0;i<numWeapon;i++){
                if (weapon[i]->index == 3){
                    cout<<","<<weapon[i]->name<<"("<<weapon[i]->getEndurance()<<")"<<endl;
                    break;
                }
            }
        }
        else{
            cout<<belong<<" "<<name<<" "<<index<<" has no weapon";
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
        if(status != 0){
            city += step;//Similarly, can either be 1 or -1
            if(city%2 == 0 && city != 0){
                if(life > 9){
                    life -= 9;
                    setAttack(getAttack() + 20);
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
    Lion(){name = "lion";}
    Lion(int _life, int _attack, int _city, string _belong, int _loyalty, int _increment):Warrior(_life, _attack, _city,_belong,_loyalty,_increment){
        name = "lion";
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
            beingKilled();
            preLife = life + lostLife;
        }

    }
    virtual void reportWeapon(){
        cout<<belong<<" "<<name<<" "<<index<<" has no weapon"<<endl;
    }
    void lowerLoy(){
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
    virtual void pickUpWeapon(Weapon w){
        int count=0;
        for(int i=0; i<weapon.size();i++){
            if(w.index == weapon[i]->index){
                count += 1;
            }
        }
        if(count == 0){
            weapon.push_back(&w);
        }
    }
    virtual void reportWeapon(){
        if(weapon.size() > 0){
            cout<<belong<<" "<<name<<" "<<index<<" has ";
            for(int i=0;i<weapon.size();i++){
                if (weapon[i]->index == 1){
                    cout<<weapon[i]->name<<"("<<weapon[i]->getAttack()<<")";
                    break;
                }
            }
            for(int i=0;i<weapon.size();i++){
                if (weapon[i]->index == 2){
                    cout<<", "<<weapon[i]->name;
                    break;
                }
            }
            for(int i=0;i<weapon.size();i++){
                if (weapon[i]->index == 3){
                    cout<<","<<weapon[i]->name<<"("<<weapon[i]->getEndurance()<<")"<<endl;
                    break;
                }
            }
        }
        else{
            cout<<belong<<" "<<name<<" "<<index<<" has no weapon";
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
    Warrior* RedWarrior = new Warrior();
    Warrior* BlueWarrior = new Warrior();
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
    int getOccupied(){return occupied;}
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
        if(headquarter == "red"){
            RedWarrior = new Warrior();
        }
        else if(headquarter == "blue"){
            BlueWarrior = new Warrior();
        }
    }
    void newWarriorCome(Warrior* w){
        if(w->belong == "red"){
            RedWarrior = NULL;
            RedWarrior = w;
        }
        else if(w->belong == "blue"){
            BlueWarrior = NULL;
            BlueWarrior = w;
        }
    }
};

class Headquarter{
private:
    Warrior* sequence[5];//Store the sequence according to which the headquarter generates new warrior
    Headquarter* otherHead;
    std::string name; //red or blue
    int totLife;
    int selfIndex; //The index of all warriors in each headquarter
    int MinLife;
    int numCity;
    vector<Warrior*> warriors;
    City** allCities = new City*[numCity];
    Sword nullSword; Bomb nullBomb; Arrow nullArrow;
public:
    int numEnemy=0; //How many enemies have already exisited in this city
    Headquarter(std::string _name, int _totLife, int _numCity, Warrior** _sequence,City** _allCities, int attackArrow):
    name(_name),totLife(_totLife),numCity(_numCity){
        for(size_t i=0; i<numCity; i++){
            allCities[i] = _allCities[i];
        }
        for (size_t i=0; i<5; i++){
            sequence[i] = _sequence[i];
        }

        selfIndex = -1;
        nullArrow.setAttack(attackArrow);
    }
    ~Headquarter(){
        delete [] allCities;
        delete [] sequence;
        for(vector<Warrior*>::iterator it = warriors.begin(); it != warriors.end(); it++){
            delete (*it);
        }
        warriors.clear();
    }

    void knowOtherQuater(Headquarter* head){
        otherHead = head;
    }

    bool generate();
    void lionRunAway();
    void warriorMove();

    void pickUpLife();
    void useArrow();
    void killedByArrow();
    void useBoom();
    void battle();
    void reportLife();
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
            tmpWarrior->setMorale(totLife/tmpWarrior->getLife());

            switch(selfIndex%3){
                case 0:tmpWeapon1 = new Sword();
                case 1:tmpWeapon1 = new Bomb();
                case 2:tmpWeapon1 = new Arrow();
            }
            tmpWarrior->weapon.clear();
            tmpWarrior->assignWeapon(tmpWeapon1);

            warriors.push_back(tmpWarrior);
            cout<<name<<" dragon "<<selfIndex+1<<" born"<<endl;
            cout<<"Its morale is "<<tmpWarrior->getMorale()<<endl;
        }
        else if(warriorName == "ninjia"){
            tmpWarrior = new Ninjia(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();

            switch(selfIndex%3){
                case 0:tmpWeapon1 = new Sword(); tmpWeapon2 = new Bomb();
                case 1:tmpWeapon1 = new Bomb(); tmpWeapon2 = new Arrow();
                case 2:tmpWeapon1 = new Arrow(); tmpWeapon2 = new Sword();
            }
            tmpWarrior->weapon.clear();
            tmpWarrior->assignWeapon(tmpWeapon1,tmpWeapon2);

            warriors.push_back(tmpWarrior);
            cout<<name<<" ninjia "<<selfIndex+1<<" born"<<endl;
        }
        else if(warriorName == "iceman"){
            tmpWarrior = new Iceman(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();

            switch(selfIndex%3){
                case 0:tmpWeapon1 = new Sword();
                case 1:tmpWeapon1 = new Bomb();
                case 2:tmpWeapon1 = new Arrow();
            }
            tmpWarrior->weapon.clear();

            tmpWarrior->assignWeapon(tmpWeapon1);
            warriors.push_back(tmpWarrior);
            cout<<name<<" iceman "<<selfIndex+1<<" born"<<endl;
        }
        else if(warriorName == "lion"){
            tmpWarrior = new Lion(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            tmpWarrior->setLoyalty(totLife);
            warriors.push_back(tmpWarrior);
            cout<<name<<" lion "<<selfIndex+1<<" born"<<endl;
            cout<<"Its loyalty is "<<tmpWarrior->getLoyalty()<<endl;
        }
        else if(warriorName == "wolf"){
            tmpWarrior = new Wolf(*sequence[seqIndex]);
            totLife -= tmpWarrior->getLife();
            warriors.push_back(tmpWarrior);
            cout<<name<<" wolf "<<selfIndex+1<<" born"<<endl;
        }
        if(name == "blue") warriors[warriors.size()-1]->setCity(numCity+1);
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
        if((*it)->name == "Lion" && (*it)->getLoyalty() <= 0){
            if(name == "red"){
                if((*it)->getCity() != numCity+1){
                    (*it)->beingKilled();
                    cout<<name<<" lion "<<(*it)->getIndex()<<" ran away"<<endl;
                }
            }
            else{
                if((*it)->getCity() != 0){
                    (*it)->beingKilled();
                }
                cout<<name<<" lion "<<(*it)->getIndex()<<" ran away"<<endl;
            }
        }
    }
}
void Headquarter::warriorMove(){
    if(name == "red"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->getCity() != numCity+1 && (*it)->getStatus() != 0){
                int CurrentCity = (*it)->getCity();
                (*it)->walk(1);
                if (CurrentCity !=0){
                    allCities[CurrentCity-1]->warriorLeave("red");//allCities are indexed starting from 0 rather than 1
                }
                if(CurrentCity != numCity){
                    allCities[CurrentCity]->newWarriorCome(*it);
                    cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" marched to city "<<CurrentCity-1<<" with "\
                    <<(*it)->getLife()<<" elements and force "<<(*it)->getTotalAttack()<<endl;
                }
                else if(CurrentCity == numCity){
                    cout<<"red "<<(*it)->name<<" "<<(*it)->getIndex()<<" reached blue headquarter with "\
                    <<(*it)->getLife()<<" elements and force "<<(*it)->getTotalAttack()<<endl;
                    otherHead->numEnemy += 1;
                }
            }
        }
    }
    else if(name == "blue"){

        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){

            if((*it)->getCity() != 0 && (*it)->getStatus() != 0){
                int CurrentCity = (*it)->getCity();

                (*it)->walk(-1);


                if (CurrentCity != numCity+1){
                    allCities[CurrentCity-1]->warriorLeave("blue");
                }


                if(CurrentCity != 1){
                    allCities[CurrentCity-2]->newWarriorCome(*it);
                    cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" marched to city "<<CurrentCity-1<<" with "\
                    <<(*it)->getLife()<<" elements and force "<<(*it)->getTotalAttack()<<endl;
                }
                if(CurrentCity == 1){
                    cout<<"blue "<<(*it)->name<<" "<<(*it)->getIndex()<<" reached red headquarter with "\
                    <<(*it)->getLife()<<" elements and force "<<(*it)->getTotalAttack()<<endl;
                    otherHead->numEnemy += 1;
                }
            }
        }
    }
}
void Headquarter::pickUpLife(){
    if(name == "red"){
        for(size_t i=0; i<numCity; i++){
            if (allCities[i]->RedWarrior->getStatus() == 1 && allCities[i]->BlueWarrior->getStatus() == 0){
                int lifeHere = allCities[i]->lifePickedUp();
                totLife += lifeHere;
                cout<<"red "<<allCities[i]->RedWarrior->name<<" "<<allCities[i]->RedWarrior->getIndex()<<\
                " earned "<<lifeHere<<" elements for his headquarter"<<endl;
            }
        }
    }
    else if(name == "blue"){
        for(size_t i=0; i<numCity; i++){
            if (allCities[i]->BlueWarrior->getStatus() == 1 && allCities[i]->RedWarrior->getStatus() == 0){
                int lifeHere = allCities[i]->lifePickedUp();
                totLife += lifeHere;
                cout<<"blue "<<allCities[i]->BlueWarrior->name<<" "<<allCities[i]->BlueWarrior->getIndex()<<\
                " earned "<<lifeHere<<" elements for his headquarter"<<endl;
            }
        }
    }
}
void Headquarter::useArrow(){
    if(name == "red"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->getCity() <= numCity-2)
            if(allCities[(*it)->getCity()]->BlueWarrior->getStatus() != 0){
                (*it)->releaseArrow(allCities[(*it)->getCity() -1]->BlueWarrior);

                if(allCities[(*it)->getCity()]->BlueWarrior->getLife() <= 0){
                    cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" shot and killed"<<\
                    allCities[(*it)->getCity()]->BlueWarrior->belong<<allCities[(*it)->getCity()]->BlueWarrior->name<<\
                    allCities[(*it)->getCity()]->BlueWarrior->getIndex()<<endl;
                }
                else{
                    cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" shot"<<endl;
                }
            }
        }
    }
    else if(name == "blue"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            if((*it)->getCity() >= 2){
                if(allCities[(*it)->getCity()-2]->RedWarrior->getStatus() != 0){
                    (*it)->releaseArrow(allCities[(*it)->getCity()-2]->RedWarrior);

                    if(allCities[(*it)->getCity()]->RedWarrior->getLife() <= 0){
                        cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" shot and killed"<<\
                        allCities[(*it)->getCity()]->RedWarrior->belong<<allCities[(*it)->getCity()]->RedWarrior->name<<\
                        allCities[(*it)->getCity()]->RedWarrior->getIndex()<<endl;
                    }
                    else{
                        cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" shot"<<endl;
                    }
                }
            }
        }
    }
}
void Headquarter::killedByArrow(){
    for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
        (*it)->ifKilled();
    }
}
void Headquarter::useBoom(){
    if(name == "red"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            for(vector<Weapon*>::iterator wp=(*it)->weapon.begin(); wp != (*it)->weapon.end();wp++){
                if((*wp)->index == 3 && (*wp)->getEndurance() != 0 && (*it)->getStatus() != 0){
                    if(allCities[(*it)->getCity()-1]->getPrivilege() == 1 &&\
                    allCities[(*it)->getCity()-1]->BlueWarrior->getTotalAttack() >= (*it)->getLife()){
                        (*it)->weapon[0]->damage();
                        (*it)->beingKilled();
                        allCities[(*it)->getCity()-1]->BlueWarrior->beingKilled();
                        cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" used a bomb and killed "<<\
                        allCities[(*it)->getCity()]->BlueWarrior->belong<<" "<<allCities[(*it)->getCity()]->BlueWarrior->name<<\
                        allCities[(*it)->getCity()]->BlueWarrior->getIndex()<<endl;
                    }
                    else if(allCities[(*it)->getCity()-1]->getPrivilege() == 0 &&\
                    allCities[(*it)->getCity()-1]->BlueWarrior->getTotalFightBack() >= (*it)->getLife() &&\
                    (*it)->getTotalAttack() < allCities[(*it)->getCity()-1]->BlueWarrior->getLife()){
                        (*wp)->damage();
                        (*it)->beingKilled();
                        allCities[(*it)->getCity()-1]->BlueWarrior->beingKilled();
                        cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" used a bomb and killed "<<\
                        allCities[(*it)->getCity()]->BlueWarrior->belong<<" "<<allCities[(*it)->getCity()]->BlueWarrior->name<<\
                        allCities[(*it)->getCity()]->BlueWarrior->getIndex()<<endl;
                    }
                }
            }
        }
    }
    else if(name == "blue"){
        for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
            for(vector<Weapon*>::iterator wp=(*it)->weapon.begin(); wp != (*it)->weapon.end();wp++){
                if((*wp)->index == 3 && (*wp)->getEndurance() > 0 && (*it)->getStatus() != 0){
                    if(allCities[(*it)->getCity()-1]->getPrivilege() == 0 &&\
                    allCities[(*it)->getCity()-1]->RedWarrior->getTotalAttack() >= (*it)->getLife()){
                        (*wp)->damage();
                        (*it)->beingKilled();
                        allCities[(*it)->getCity()-1]->RedWarrior->beingKilled();
                        cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" used a bomb and killed "<<\
                        allCities[(*it)->getCity()]->RedWarrior->belong<<" "<<allCities[(*it)->getCity()]->RedWarrior->name<<\
                        allCities[(*it)->getCity()]->RedWarrior->getIndex()<<endl;
                    }
                    else if(allCities[(*it)->getCity()-1]->getPrivilege() == 1 &&\
                    allCities[(*it)->getCity()-1]->RedWarrior->getTotalFightBack() >= (*it)->getLife() &&\
                    (*it)->getTotalAttack() < allCities[(*it)->getCity()-1]->RedWarrior->getLife()){
                        (*wp)->damage();
                        (*it)->beingKilled();
                        allCities[(*it)->getCity()-1]->BlueWarrior->beingKilled();
                        cout<<name<<" "<<(*it)->name<<" "<<(*it)->getIndex()<<" used a bomb and killed "<<\
                        allCities[(*it)->getCity()]->RedWarrior->belong<<" "<<allCities[(*it)->getCity()]->RedWarrior->name<<\
                        allCities[(*it)->getCity()]->RedWarrior->getIndex()<<endl;
                    }
                    break;
                }
            }
        }
    }


}
void Headquarter::battle(){
    if (name == "red"){
        for(size_t i=0; i<numCity; i++){
            if(allCities[i]->getPrivilege() == 0){ //Red has the privilege
                if(allCities[i]->RedWarrior->getStatus() == 1 && allCities[i]->BlueWarrior->getStatus() != 0){
                    allCities[i]->RedWarrior->fight(allCities[i]->BlueWarrior);
                    //Print info
                    cout<<"red "<<allCities[i]->RedWarrior->name<<" "<<allCities[i]->RedWarrior->getIndex()<<\
                    " attacked blue "<<allCities[i]->BlueWarrior->name<<" in city "<<i<<"with "<<\
                    allCities[i]->RedWarrior->getLife()<<" elements and "<<allCities[i]->RedWarrior->getTotalAttack()<<" force"<<endl;

                    //didn't kill the enemy. Enemy fightback
                    if(allCities[i]->BlueWarrior->getStatus() != 0 && allCities[i]->BlueWarrior->name != "Ninjia"){
                        allCities[i]->BlueWarrior->fightBack(allCities[i]->RedWarrior);
                        //Print info
                        cout<<"blue "<<allCities[i]->BlueWarrior->name<<" "<<allCities[i]->BlueWarrior->getIndex()<<\
                        " fought back against red "<<allCities[i]->RedWarrior->name<<" "<<\
                        allCities[i]->RedWarrior->getIndex()<<" in city "<<i<<endl;

                        //Killed by fight back
                        if(allCities[i]->RedWarrior->getStatus() == 0){
                            allCities[i]->BcontinuousWinning += 1;
                            allCities[i]->RedWarrior->lifeTransfer(allCities[i]->BlueWarrior);
                            allCities[i]->BlueWarrior->pickUpWeapon();
                            allCities[i]->BlueWarrior->moraleUp();
                            /*Blue not yell since it's not an active battle*/
                            if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                                allCities[i]->setOccupied(1);
                                cout<<"blue flag raised in city "<<i+1<<endl;
                            }
                        }
                        //Starting to yell and change morale

                        else{//No one dies. It's a tie.
                            allCities[i]->BcontinuousWinning = 0;
                            allCities[i]->RedWarrior->moraleDown();
                            allCities[i]->RcontinuousWinning = 0;
                        }
                    }

                    //Killed the enemy
                    else if(allCities[i]->BlueWarrior->getStatus() == 0){
                        allCities[i]->RedWarrior->moraleUp();
                        allCities[i]->RedWarrior->yell();
                        allCities[i]->RcontinuousWinning += 1;
                        allCities[i]->RedWarrior->pickUpWeapon();
                        allCities[i]->BlueWarrior->lifeTransfer(allCities[i]->RedWarrior);
                        if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                            allCities[i]->setOccupied(0);
                            cout<<"red flag raised in city "<<i+1<<endl;
                        }
                    }
                    else{//No one dies. It's tie.
                        allCities[i]->BcontinuousWinning = 0;
                        allCities[i]->RedWarrior->moraleDown();
                        allCities[i]->BcontinuousWinning = 0;
                    }
                }

                else if(allCities[i]->RedWarrior->getStatus() == 1 && allCities[i]->BlueWarrior->getStatus() == 0 && allCities[i]->BlueWarrior->getLoyalty() > 0){
                    allCities[i]->RcontinuousWinning += 1;
                    allCities[i]->RedWarrior->moraleUp();
                    allCities[i]->RedWarrior->yell();
                    allCities[i]->BlueWarrior->lifeTransfer(allCities[i]->RedWarrior);
                    allCities[i]->RedWarrior->pickUpWeapon();
                    if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                        allCities[i]->setOccupied(0);
                        cout<<"red flag raised in city "<<i+1<<endl;
                    }
                }
            }
        }
    }
    else if(name == "blue"){
        for(size_t i=0; i<numCity; i++){
            if(allCities[i]->getPrivilege() == 1){ //Blue has the privilege
                if(allCities[i]->BlueWarrior->getStatus() == 1 && allCities[i]->RedWarrior->getStatus() != 0){
                    allCities[i]->BlueWarrior->fight(allCities[i]->RedWarrior);
                    //Print info
                    cout<<"blue "<<allCities[i]->BlueWarrior->name<<" "<<allCities[i]->BlueWarrior->getIndex()<<\
                    " attacked red "<<allCities[i]->RedWarrior->name<<" in city "<<i<<"with "<<\
                    allCities[i]->BlueWarrior->getLife()<<" elements and "<<allCities[i]->BlueWarrior->getTotalAttack()<<" force"<<endl;

                    if(allCities[i]->RedWarrior->getStatus() != 0 && allCities[i]->RedWarrior->name != "Ninjia"){
                        allCities[i]->RedWarrior->fightBack(allCities[i]->BlueWarrior);

                        //Print info
                        cout<<"red "<<allCities[i]->RedWarrior->name<<" "<<allCities[i]->RedWarrior->getIndex()<<\
                        " fought back against red "<<allCities[i]->BlueWarrior->name<<" "<<\
                        allCities[i]->BlueWarrior->getIndex()<<" in city "<<i<<endl;

                        //Killed by fightBack
                        if(allCities[i]->BlueWarrior->getStatus() == 0){
                            allCities[i]->RcontinuousWinning += 1;
                            allCities[i]->BlueWarrior->lifeTransfer(allCities[i]->RedWarrior);
                            allCities[i]->RedWarrior->pickUpWeapon();
                            allCities[i]->RedWarrior->moraleUp();
                            if (allCities[i]->RcontinuousWinning%2 == 0 && allCities[i]->RcontinuousWinning !=0){
                                allCities[i]->setOccupied(0);
                                cout<<"red flag raised in city "<<i+1<<endl;
                            }
                        }
                        else{//No one dies. It's a tie.
                            allCities[i]->BcontinuousWinning = 0;
                            allCities[i]->BlueWarrior->moraleDown();
                            allCities[i]->RcontinuousWinning = 0;
                        }
                    }
                    else if(allCities[i]->RedWarrior->getStatus() == 0){
                        allCities[i]->BcontinuousWinning += 1;
                        allCities[i]->BlueWarrior->moraleUp();
                        allCities[i]->BlueWarrior->yell();
                        allCities[i]->RedWarrior->lifeTransfer(allCities[i]->BlueWarrior);
                        allCities[i]->BlueWarrior->pickUpWeapon();
                        if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                            allCities[i]->setOccupied(1);
                            cout<<"blue flag raised in city "<<i+1<<endl;
                        }
                    }
                    else{//No one dies. It's tie.
                        allCities[i]->BcontinuousWinning = 0;
                        allCities[i]->BlueWarrior->moraleDown();
                        allCities[i]->RcontinuousWinning = 0;
                    }
                }
                else if(allCities[i]->BlueWarrior->getStatus() == 1 && allCities[i]->RedWarrior->getStatus() == 0 && allCities[i]->RedWarrior->getLoyalty() > 0){
                    allCities[i]->BcontinuousWinning += 1;
                    allCities[i]->BlueWarrior->moraleUp();
                    allCities[i]->BlueWarrior->yell();
                    allCities[i]->RedWarrior->lifeTransfer(allCities[i]->BlueWarrior);
                    allCities[i]->BlueWarrior->pickUpWeapon();
                    if (allCities[i]->BcontinuousWinning%2 == 0 && allCities[i]->BcontinuousWinning !=0){
                        allCities[i]->setOccupied(1);
                        cout<<"blue flag raised in city "<<i+1<<endl;
                    }
                }
            }
        }
    }
}
void Headquarter::reportLife(){
    cout<<totLife<<" elements in "<<name<<" headquarter"<<endl;
}
void Headquarter::reportWeapon(){
    for(vector<Warrior*>::iterator it=warriors.begin(); it != warriors.end(); it++){
        (*it)->reportWeapon();
    }
}
bool Headquarter::beingOccupied(){
    if(numEnemy == 2){
        cout<<name<<" headquarter was taken"<<endl;
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

    int* l1 = new int[caseNum]; int* at1 = new int[caseNum];//dragon
    int* l2 = new int[caseNum]; int* at2 = new int[caseNum];//Ninjia
    int* l3 = new int[caseNum]; int* at3 = new int[caseNum];//iceman
    int* l4 = new int[caseNum]; int* at4 = new int[caseNum];//lion
    int* l5 = new int[caseNum]; int* at5 = new int[caseNum];//wolf
    for (size_t i=0;i<caseNum;i++){
        cin>>inM[i]>>inN[i]>>inR[i]>>inK[i]>>inT[i];
        cin>>l1[i]>>l2[i]>>l3[i]>>l4[i]>>l5[i];
        cin>>at1[i]>>at2[i]>>at3[i]>>at4[i]>>at5[i];
    }

    double timerMins[10] = {0};
    timerMins[0] = 0; timerMins[1] = 5; timerMins[2] = 10; timerMins[3] = 20;
    timerMins[4] = 30; timerMins[5] = 35; timerMins[6] = 38; timerMins[7] = 40;
    timerMins[8] = 50; timerMins[9] = 55;

    Warrior* seqRed[5];
    Warrior* seqBlue[5];
    City** allCities;

    for (size_t i=0;i<caseNum; i++){

        Warrior* Redw1;Warrior* Bluew1;
        Warrior* Redw2;Warrior* Bluew2;
        Warrior* Redw3;Warrior* Bluew3;
        Warrior* Redw4;Warrior* Bluew4;
        Warrior* Redw5;Warrior* Bluew5;


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

        allCities = new City*[inN[i]];
        for(int j=0; j<inN[i]; j++){
            allCities[j] = new City(0,-1,0);
        }

        cout<<inM[i]<<endl;

        Headquarter red("red",inM[i],inN[i],seqRed, allCities,inK[i]);
        Headquarter blue("blue",inM[i],inN[i],seqBlue, allCities,inK[i]);

        red.knowOtherQuater(&blue);
        blue.knowOtherQuater(&red);

        cout<<"Case:"<<i+1<<endl;

        bool redOccupied = false;
        bool blueOccupied = false;
        while(redOccupied == false && blueOccupied == false){
            red.generate();
            blue.generate();
            red.lionRunAway();
            blue.lionRunAway();

            red.warriorMove();
            blue.warriorMove();

            for(size_t j=0; j<inN[i]; j++){
                allCities[j]->generateLife();
            }

            redOccupied = red.beingOccupied();
            blueOccupied = blue.beingOccupied();
            if(redOccupied == true || blueOccupied == true){
                break;
            }


            red.useArrow();
            blue.useArrow();
            red.killedByArrow();
            blue.killedByArrow();

            red.useBoom();
            blue.useBoom();

            red.battle();
            blue.battle();

            red.pickUpLife();
            blue.pickUpLife();

            red.reportLife();
            blue.reportLife();

            red.reportWeapon();
            blue.reportWeapon();

        }




    }


    delete [] inM, inN, inR, inK, inT;
    delete [] l1, at1;
    delete [] l2, at2;
    delete [] l3, at3;
    delete [] l4, at4;
    delete [] l5, at5;

    delete [] seqRed;
    delete [] seqBlue;
    delete [] allCities;

    return 0;
}
