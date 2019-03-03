#include "Berserk.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
using namespace std;
Berserk::Berserk(uint id, int x, int y):Player(id , x, y)
{
  HP=100;
}
const string Berserk::getFullName() const
{
  string name("Berserk"+getBoardID());
  return name;
}
Armor Berserk::getArmor() const
{
  return WOODEN;
}
Weapon Berserk::getWeapon() const
{
  return PISTOL;
}

vector<Move> Berserk::getPriorityList() const
{
  vector<Move> plist;
  plist.push_back(ATTACK);
  plist.push_back(UP);
  plist.push_back(LEFT);
  plist.push_back(DOWN);
  plist.push_back(RIGHT);
  return plist;
}
