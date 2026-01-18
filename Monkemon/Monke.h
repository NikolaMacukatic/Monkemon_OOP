
#ifndef MONKE_H
#define MONKE_H

#include <string>
using namespace std;


enum class ElementType {
    FIRE,
    WATER,
    EARTH
};

class Monke {
protected:
    string name;
    int hp;
    int maxHp;
    int attackPower;
    ElementType type;

    int normalAttackCounter; 

public:
    Monke(const string& name, int hp, int atk, ElementType type);
    virtual ~Monke() {}

    
    string GetName() const;
    int GetHP() const;
    ElementType GetType() const;
    bool IsFainted() const;

    
    int NormalAttack();
    int ElementalAttack(Monke& target); 

    void TakeDamage(int dmg);

    void Heal(int amount);
    int GetMaxHP() const;

};



class FireMonke : public Monke {
public:
    FireMonke(const string& name, int hp, int atk);
};

class WaterMonke : public Monke {
public:
    WaterMonke(const string& name, int hp, int atk);
};

class EarthMonke : public Monke {
public:
    EarthMonke(const string& name, int hp, int atk);
};

#endif
