
#include "team.hpp"


Team::~Team() {
    for (Animal* animal : animals)
        delete animal;
}

void Team::begin_turn() {
    for (Animal* animal : animals) {
        animal->reset_stats();
        animal->on_start_turn();
    }
}

void Team::order(int order[5]) {

}

void Team::add(Animal* animal) {
    animals.push_back(animal);
}

void Team::upgrade(int index, Animal* other_animal) {

}

int Team::sell(int index) {
    int xp = animals[index]->get_xp();
    delete animals[index];
    animals.erase(animals.begin()+index);
    if (xp == 6)
        return 3;
    else if (xp > 1)
        return 2;
    else
        return 1;
}

void Team::draw() const {
    for (Animal* animal : animals)
        animal->draw();
}
