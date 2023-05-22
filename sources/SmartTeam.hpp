#pragma once

#include "Team.hpp"

namespace ariel
{
    class SmartTeam : public Team
    {
    private:
        vector<Character *> warriors;
        Character *leader;

    public:
        SmartTeam(Character *leader);
        SmartTeam(SmartTeam *team);
        void attack(Team *enemyTeam) override;
        void print() const override;
    };
}
