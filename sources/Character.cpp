#include "Character.hpp"
#include <iostream>

using namespace std;

using namespace ariel;

Character::Character(string name1, Point location1)
{
    this->name = name1;
    this->location = location1;
}
Character::Character(string name1, Point location1, int hitPoints1)
{
    this->name = name1;
    this->location = location1;
    this->hitPoints = hitPoints1;
}
Character::Character(const Character &other)
{
    this->name = other.name;
    this->location = other.location;
}
// Inside the member initialization list, _name is initialized using move(other._name).
// This line invokes the move constructor of the _name member, allowing it to efficiently "steal" the resources (e.g., dynamically allocated memory) from other._name.
// This move operation is typically more efficient than making a copy.
Character::Character(Character &&other) noexcept : name(move(other.name)), location(other.location), hitPoints(other.hitPoints)
{
    other.hitPoints = 0;
}
Character::~Character()
{
}
bool Character::isAlive() const
{
    return (this->hitPoints > 0);
}
double Character::distance(Character *other) const
{
    if (other == nullptr)
        throw invalid_argument("Other is null");
    return location.distance(other->getLocation());
}
void Character::hit(int hittPoints)
{
    if (hittPoints < 0)
        throw invalid_argument("The hit points cant be negative");
    this->hitPoints = this->hitPoints - hittPoints;
}
const Point &Character::getLocation() const
{
    return location;
}
std::string Character::getName() const
{
    return name;
}
int Character::getHitPoints() const
{
    return hitPoints;
}
void Character::setLocation(Point location1) 
{
    this->location = location1;
}
Character &Character::operator=(const Character &other)
{
    if (this != &other)
    {
        hitPoints = other.hitPoints;
        name = other.name;
    }
    return *this;
}
Character &Character::operator=(Character &&other) noexcept
{
    if (this != &other)
    {
        hitPoints = other.hitPoints;
        name = move(other.name);
        other.hitPoints = 0;
    }
    return *this;
}
