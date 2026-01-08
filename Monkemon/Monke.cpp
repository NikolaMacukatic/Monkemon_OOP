#include "Monke.h"
using namespace std;


Monke::Monke(const string& name, int hp, int atk, ElementType type)
    : name(name), hp(hp), maxHp(hp), attackPower(atk), type(type), normalAttackCounter(0) {
}

string Monke::GetName() const { return name; }
int Monke::GetHP() const { return hp; }
ElementType Monke::GetType() const { return type; }

bool Monke::IsFainted() const {
    return hp <= 0;
}

void Monke::TakeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

int Monke::NormalAttack() {
    normalAttackCounter++;
    return attackPower;
}

int Monke::ElementalAttack(Monke& target) {
    if (normalAttackCounter < 3) {
        return 0; 
    }

    normalAttackCounter = 0; 

    float multiplier = 1.5f;


    if (type == ElementType::FIRE && target.GetType() == ElementType::EARTH)
        multiplier *= 1.2f;
    else if (type == ElementType::WATER && target.GetType() == ElementType::FIRE)
        multiplier *= 1.2f;
    else if (type == ElementType::EARTH && target.GetType() == ElementType::WATER)
        multiplier *= 1.2f;

    int damage = (int)(attackPower * multiplier);
    target.TakeDamage(damage);
    return damage;
}



FireMonke::FireMonke(const string& name, int hp, int atk)
    : Monke(name, hp, atk, ElementType::FIRE) {
}

WaterMonke::WaterMonke(const string& name, int hp, int atk)
    : Monke(name, hp, atk, ElementType::WATER) {
}

EarthMonke::EarthMonke(const string& name, int hp, int atk)
    : Monke(name, hp, atk, ElementType::EARTH) {
}
