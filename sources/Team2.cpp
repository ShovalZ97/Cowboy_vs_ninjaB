#include "Team2.hpp"
#include <iostream>
#include <cmath>

using namespace ariel;
using namespace std;

Team2::Team2(Character *leader) : Team(leader) {}
void Team2::attack(Team *enemies) 
{
    if (enemies == nullptr)
        throw invalid_argument("The enemies team is null");
    else if (enemies == this)
        throw runtime_error("Cant attack team self");
    else if (enemies->stillAlive() == 0)
        throw runtime_error("The other team is dead");
    else if (this->stillAlive() == 0)
        throw runtime_error("The team is dead");
    // When the leader is not alive
    if (this->getLeader()->isAlive() == false)
    {
        Character *leadNew = nullptr;
        double minDis = INFINITY;
        // Check the most close character to the dead leader
        for (Character *warrior : getWarriors())
        {
            if (warrior->isAlive() && warrior->distance(getLeader()) < minDis)
            {
                minDis = warrior->distance(getLeader());
                leadNew = warrior;
            }
        }
        cout << "The team leader died and the team have new leader" << endl;
        setLeader(leadNew);
    }
    // When the leader is alive
    cout << "The team leader is attack the team " << endl;
    // Check the close victim from the enemies to the the attacking team
    Character *victim = findVictim(enemies);
    for (Character *warrior : getWarriors())
    {
        if (victim->isAlive() == false)
        {
            if (enemies->stillAlive() == 0)
                return;
            victim = findVictim(enemies);
        }
        Cowboy *cowboy = dynamic_cast<Cowboy *>(warrior);
        if (cowboy != nullptr && cowboy->isAlive())
        {
            if (cowboy->hasboolets())
                cowboy->shoot(victim);
            // No balls to cowboy
            else
                cowboy->reload();
        }
    }
    for (Character *warrior : getWarriors())
    {
        if (victim->isAlive() == false)
        {
            if (enemies->stillAlive() == 0)
                return;
            victim = findVictim(enemies);
        }
        Ninja *ninja = dynamic_cast<Ninja *>(warrior);
        if (ninja != nullptr && ninja->isAlive())
        {
            if (ninja->getLocation().distance(victim->getLocation()) <= 1)
                ninja->slash(victim);
            // When the ninja approaching the victim
            else
                ninja->move(victim);
        }
    }
}

void Team2::print() const
{
    cout << "Team Leader: " << getLeader()->getName() << endl;

    for (Character *warrior : getWarriors())
        cout << warrior->print() << endl;
}