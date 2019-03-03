#include "Pacifist.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
using namespace std;
Pacifist::Pacifist(uint id, int x, int y):Player(id , x, y)
{
  HP=100;
}
const string Pacifist::getFullName() const
{
  string name("Pacifist"+getBoardID());
  return name;
}
Armor Pacifist::getArmor() const
{
  return METAL;
}
Weapon Pacifist::getWeapon() const
{
  return NOWEAPON;
}

vector<Move> Pacifist::getPriorityList() const
{
  vector<Move> plist;
  plist.push_back(UP);
  plist.push_back(LEFT);
  plist.push_back(DOWN);
  plist.push_back(RIGHT);
  return plist;
}
