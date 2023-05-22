#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#pragma once
#include "Point.hpp"
#include <string>
using namespace std;

namespace ariel
{

    class Character
    {
    private:
        Point location;
        int hitPoints;
        string name;
        bool inTeam=false;

    public:
        Character(string name, Point location);
        Character(string name, Point location, int hitPoints);
        // Copy constructor
        Character(const Character &other);
        // Move constructor
        Character(Character &&other) noexcept;
        // Copy assignment operator
        Character &operator=(const Character &other);
        // Move assignment operator
        Character &operator=(Character &&other) noexcept;
        // The base class destructor virtual to ensure proper cleanup and avoid potential memory leaks.
        virtual ~Character();
        // Returns a Boolean value whether the character is alive (meaning it has more than zero hit points).
        bool isAlive() const;
        // Gets a pointer to another character and returns the distance between the characters
        double distance(Character *other) const;
        // Subtracts the appropriate amount of hit points from the character.
        void hit(int SubHitPoints);
        std::string getName() const;
        const Point &getLocation() const;
        int getHitPoints() const;
        void setLocation(Point location);
        // Return true if the character is in a team
        bool ifIsInTeam() const
        {
            return inTeam;
        }
        // Set in team true if the character is in a team
        void setInTeam(bool inTeam)
        {
            this->inTeam = inTeam;
        }
        // Prints the name of the character, the number of its hit points, and the point where the character is.
        // Virtual function because the class is abstract.
        virtual std::string print() const = 0;
    };

}

#endif