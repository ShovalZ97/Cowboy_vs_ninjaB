#pragma once
#include <vector>
#include "Point.hpp"
#include "Character.hpp"
#include "Ninja.hpp"
#include "Cowboy.hpp"
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"

namespace ariel
{
    class Team
    {
    private:
        Character *leader;
        std::vector<Character *> warriors;

    public:
        // Constructor
        Team(Character *character);
        // Copy constructor
        Team(const Team &other);
        // Move constructor
        Team(Team &&other) noexcept;
        // Copy assignment operator
        Team &operator=(const Team &other);
        // Move assignment operator
        Team &operator=(Team &&other) noexcept;
        // Destructor,frees the memory allocated to all characters in the group.
        virtual ~Team();
        // Receives a pointer for a morning or ninja, and adds it to the group.
        void add(Character *warrior);
        // Find the victim to the attack function
        Character *findVictim(Team *other) const;
        // Attacking the enemy group will be done in the following way:
        //- First check if the leader of the attacking group is alive.
        // Otherwise, a new leader must be chosen, who is the living character closest (in terms of location) to the dead leader.
        // Then the group will choose a victim from among the enemy group.
        // The victim is the member of the living enemy group who is closest to the leader of the attacking group.
        // All living members of the attacking group will attack the chosen victim.
        // Cowboys who have bullets in their guns will shoot the victim, and cowboys who don't have bullets will load their weapons.
        // Ninjas within 1 meter of the victim will kill the victim, and ninjas further away will advance towards the victim.
        // At each stage, if the victim If dead,
        // a new victim will be chosen (which will be, again, the living enemy character closest to the leader of the attacking group).
        // If there are no living members in the attacking group or the enemy group the attack will end. –
        virtual void attack(Team *enemies);
        // Returns an integer number of surviving group members
        int stillAlive();
        // Goes through all the characters in the group and prints their details
        virtual void print() const;
        // Return the leader of the team
        Character *getLeader() const;
        // Set the leader of the team
        void setLeader(Character *leader);
        // Return The size of the team
        int getSize() const;
        const vector<Character*>& getWarriors() const;
       
    };
}