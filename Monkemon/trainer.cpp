#include "trainer.h"


Trainer::Trainer() : activeIndex(0), healingItems(1) {}

Trainer::~Trainer() {
    for (Monke* m : party) {
        delete m;
    }
}

void Trainer::AddMonke(Monke* monke) {
    if (party.size() < 3) {
        party.push_back(monke);
    }
}

Monke* Trainer::GetActiveMonke() {
    if (activeIndex < party.size()) {
        return party[activeIndex];
    }
    return nullptr;
}

bool Trainer::HasRemainingMonkes() {
    for (Monke* m : party) {
        if (!m->IsFainted()) return true;
    }
    return false;
}

void Trainer::SwitchToNextMonke() {
    for (int i = 0; i < party.size(); i++) {
        if (!party[i]->IsFainted()) {
            activeIndex = i;
            return;
        }
    }
}

int Trainer::GetHealingItems() const
{
    return healingItems;
}

bool Trainer::UseHealingItem(Monke* target)
{
    if (healingItems <= 0 || target == nullptr)
        return false;

    target->Heal(50);
    healingItems--;
    return true;
}



Player::Player() : Trainer() {}

CPUTrainer::CPUTrainer() : Trainer() {}
