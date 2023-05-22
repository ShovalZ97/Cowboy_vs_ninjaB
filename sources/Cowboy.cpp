#include "Cowboy.hpp"
#include <iostream>

using namespace ariel;

// Constructor
Cowboy::Cowboy(string name, Point location) : Character(name, location, 110), amountBalls(6)
{
}
void Cowboy::shoot(Character *enemy)
{
    if (enemy == nullptr)
        throw invalid_argument("The enemy is null");
    else if (enemy == this)
        throw runtime_error("Cant shoot himself!");
    else if (this->isAlive() == false || enemy->isAlive() == false)
        throw runtime_error("Cant shoot the character is dead!");
    else if (amountBalls > 0)
    {
        enemy->hit(10);
        amountBalls = amountBalls - 1;
        cout << this->getName() << " shoots on " << enemy->getName() << " 10 balls" << endl;
    }
}
void Cowboy::reload()
{
    if (this->isAlive() == false)
        throw runtime_error("Cant reload the gun because the cowboy is dead");
    amountBalls = 6;
    cout << getName() << "Make relad and add 6 balls" << endl;
}
bool Cowboy::hasboolets() const
{
    return (amountBalls>0);
}
string Cowboy::print() const
{
    string st="";
    st+= "Name: C (" + getName() +")";
	if (this->isAlive()==true)
		st+= " ,Hit Points : " + to_string(getHitPoints());
    st+=" ,Location : (" + to_string(this->getLocation().getX()) + "," + to_string(this->getLocation().getY())+")" ;
    return st;
}

