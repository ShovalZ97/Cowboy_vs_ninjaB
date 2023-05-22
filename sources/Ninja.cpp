#include "Ninja.hpp"
#include <iostream>

#include <string>
using namespace std;
using namespace ariel;

// Constructor
Ninja::Ninja(string name1, Point location1, int hitPoints1, int speed1)
    : Character(name1, location1, hitPoints1), speed(speed1)
{
    // Rest of the constructor code
}

void Ninja::move(Character* enemy)
{
    if (this->isAlive() == false)
        throw runtime_error("Can't move the character is dead");
    else if (enemy == nullptr)
        throw invalid_argument("The other is null");
    else if (enemy == this)
        throw invalid_argument("Can't move to himself!");

    Point locationNew = Point::moveTowards(this->getLocation(), enemy->getLocation(), this->speed);
    setLocation(locationNew);
}
bool Ninja::slash(Character* enemy)
{
    if (enemy == nullptr)
        throw invalid_argument("The enemy is null");
    else if (enemy == this)
        throw runtime_error("Can't slash himself");
    else if (this->isAlive() == false)
        throw runtime_error("Can't slash, the character is dead");
    else if (enemy->isAlive() == false)
        throw runtime_error("Can't slash, the enemy is dead");

    double distance = this->getLocation().distance(enemy->getLocation());

    if (distance < 1.0)
    {
        enemy->hit(40);
        return true;
    }
    else
    {
        cout << "The distance is too far, can't slash" << endl;
        return false;
    }
}

std::string Ninja::print() const
{
    string st = "";
    st += "Name: N (" + getName() + ")";
    if (this->isAlive() == true)
        st += " ,Hit Points : " + to_string(getHitPoints());
    st += " ,Location : (" + to_string(this->getLocation().getX()) + "," + to_string(this->getLocation().getY()) + ")";
    return st;
}