#ifndef NINJA_HPP
#define NINJA_HPP
#pragma once
#include "Character.hpp"

#include <string>
using namespace std;

namespace ariel
{
    class Ninja : public Character
    {
    private:
        int speed;

    public:
        Ninja(string name, Point location, int hitPoints, int speed);
        // Receives a pointer to the enemy and advances towards the enemy. The ninja advances a distance equal to its speed.
        void move(Character *enemy);
        // Receives a pointer to the enemy. If the ninja is alive and the enemy is less than 1 meter away, the ninja will deal 40 damage to the enemy.
        // Otherwise, no damage will be done to the enemy.
        bool slash(Character *enemy) ;
        std::string print() const override;
    };
}
#endif