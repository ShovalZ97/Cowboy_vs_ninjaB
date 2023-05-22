#include <iostream>
#include "SmartTeam.hpp"
#include <cmath>

using namespace std;
using namespace ariel;

SmartTeam::SmartTeam(Character *leader) : Team(leader) {}
// copy constructor
SmartTeam::SmartTeam(SmartTeam *team) : Team(team->leader)
{
    if (team == nullptr)
    {
        throw("given null pointer");
    }

    this->leader = team->leader;
    for (Character *warrior : this->warriors)
    {
        delete warrior;
    }
    for (Character *warrior : team->warriors)
    {
        this->warriors.push_back(warrior);
    }
}

void SmartTeam::attack(Team *enemies)
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
    if (this->leader->isAlive() == false)
    {
        Character *leadNew = nullptr;
        double minDis = INFINITY;
        // Check the most close character to the dead leader
        for (Character *warrior : warriors)
        {
            if (warrior->isAlive() && warrior->distance(leader) < minDis)
            {
                minDis = warrior->distance(leader);
                leadNew = warrior;
            }
        }
        // cout << "The team leader died and the team have new leader" << endl;
        this->leader = leadNew;
    }
    // When the leader is alive
    // cout << "The team leader is attack the team " << endl;
    // Check the close victim from the enemies to the the attacking team
    Character *victim = findVictim(enemies);
    for (Character *warrior : warriors)
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
    for (Character *warrior : warriors)
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
            if (ninja->getLocation().distance(victim->getLocation()) < 1)
                ninja->slash(victim);
            // When the ninja approaching the victim
            else
                ninja->move(victim);
        }
    }
}
void SmartTeam::print() const
{
      cout << "The name of team leader: " << leader->getName() << endl;
        for (Character *warrior : warriors)
        {
            if (dynamic_cast<Cowboy *>(warrior) != nullptr)
                cout << warrior->print() << endl;
        }
        for (Character *warrior : warriors)
        {
            if (dynamic_cast<Ninja *>(warrior) != nullptr)
                cout << warrior->print() << endl;
        }
}