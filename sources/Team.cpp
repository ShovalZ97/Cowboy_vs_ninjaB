#include "Character.hpp"
#include "Team.hpp"
#include <iostream>
#include <cmath>

namespace ariel
{
    Team::Team(Character *leader) : leader(leader)
    {
        add(leader);
    }
    Team::Team(const Team &other)
    {
        this->leader = other.leader;
        for (Character *warrior : other.warriors)
        {
            Cowboy *cowboy = dynamic_cast<Cowboy *>(warrior);
            Ninja *ninja = dynamic_cast<Ninja *>(warrior);
            if (cowboy != nullptr)
                warriors.push_back(new Cowboy(*cowboy));
            else if (ninja != nullptr)
                warriors.push_back(new Ninja(*ninja));
        }
    }
    Team::Team(Team &&other) noexcept : leader(other.leader), warriors(move(other.warriors))
    {
        other.leader = nullptr;
    }
    Team &Team::operator=(const Team &other)
    {
        if (this != &other)
        {
            for (Character *warrior : warriors)
                delete warrior;
            warriors.clear();
            this->leader = other.leader;
            for (Character *warrior : other.warriors)
            {
                Cowboy *cowboy = dynamic_cast<Cowboy *>(warrior);
                Ninja *ninja = dynamic_cast<Ninja *>(warrior);
                if (cowboy != nullptr)
                    warriors.push_back(new Cowboy(*cowboy));
                else if (ninja != nullptr)
                    warriors.push_back(new Ninja(*ninja));
            }
        }
        return *this;
    }
    Team &Team::operator=(Team &&other) noexcept
    {
        if (this != &other)
        {
            for (Character *warrior : warriors)
                delete warrior;
            warriors.clear();
            leader = other.leader;
            warriors = move(other.warriors);
            other.leader = nullptr;
        }
        return *this;
    }
    Team::~Team()
    {
        for (Character *warrior : warriors)
            delete warrior;
        warriors.clear();
    }
    void Team::add(Character *warrior1)
    {
        if (warrior1 == nullptr)
            throw invalid_argument("The warrior is null");
        else if (warrior1->ifIsInTeam())
            throw runtime_error("The warrior is already in team");
        else if (this->warriors.size() == 10)
            throw runtime_error("The team is full");

        warriors.push_back(warrior1);
        warrior1->setInTeam(true);
    }
    Character *Team::findVictim(Team *other) const
    {
        Character *victim = nullptr;
        double minDis = INFINITY;
        for (Character *warrior : other->warriors)
        {
            if (warrior->isAlive() && leader->distance(warrior) < minDis)
            {
                minDis = leader->distance(warrior);
                victim = warrior;
            }
        }
        return victim;
    }
    void Team::attack(Team *enemies)
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
            //cout << "The team leader died and the team have new leader" << endl;
            this->leader = leadNew;
        }
        // When the leader is alive
        //cout << "The team leader is attack the team " << endl;
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
    int Team::stillAlive()
    {
        int isAlive1 = 0;
        for (Character *warrior : warriors)
        {
            if (warrior->isAlive())
            {
                isAlive1++;
            }
        }
        return isAlive1;
    }
    void Team::print() const
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
    Character *Team::getLeader() const
    {
        return leader;
    }
    void Team::setLeader(Character *leader)
    {
        this->leader = leader;
    }
    const vector<Character *> &Team::getWarriors() const
    {
        return warriors;
    }

}