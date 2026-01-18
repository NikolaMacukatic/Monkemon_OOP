#ifndef TRAINER_H
#define TRAINER_H

#include <vector>
#include "Monke.h"
using namespace std;

class Trainer {
protected:
    vector<Monke*> party;
    int activeIndex;
    int healingItems;

public:
    Trainer();
    virtual ~Trainer();

    void AddMonke(Monke* monke);
    Monke* GetActiveMonke();
    bool HasRemainingMonkes();
    void SwitchToNextMonke();
    int GetHealingItems() const;
    bool UseHealingItem(Monke* target);
};



class Player : public Trainer {
public:
    Player();
};

class CPUTrainer : public Trainer {
public:
    CPUTrainer();
};

#endif
