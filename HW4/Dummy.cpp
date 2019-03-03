#include "Dummy.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
using namespace std;
Dummy::Dummy(uint id, int x, int y):Player(id , x, y)
{
  HP=1000;
}
const string Dummy::getFullName() const
{
  string name("Dummy"+getBoardID());
  return name;
}
Armor Dummy::getArmor() const
{
  return NOARMOR;
}
Weapon Dummy::getWeapon() const
{
  return NOWEAPON;
}

vector<Move> Dummy::getPriorityList() const
{
  vector<Move> plist;
  plist.push_back(NOOP);
  return plist;
}
