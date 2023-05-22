#ifndef COWBOY_HPP
#define COWBOY_HPP
#pragma once
#include "Character.hpp"

namespace ariel
{
    //Same characteristics like Character
    class Cowboy : public Character
    {
    private:
        int amountBalls;
    public:
        Cowboy(string name,Point location);

        //If the cowboy is not dead and has bullets left, the cowboy shoots the enemy, 
        //Subtracting 10 hit points from the enemy - and losing 1 bullet. Otherwise, no damage will be done to the enemy.
        void shoot(Character *enemy);
        //Indicates whether there are any bullets left in the cowboy's gun
        bool hasboolets() const;
        //Loads the gun with six new bullets
        void reload();
        std::string print() const override;
    };
}
#endif 