#include "Ambusher.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
using namespace std;
Ambusher::Ambusher(uint id, int x, int y):Player(id , x, y)
{
  HP=100;
}
const string Ambusher::getFullName() const
{
  string name("Ambusher"+getBoardID());
  return name;
}
Armor Ambusher::getArmor() const
{
  return NOARMOR;
}
Weapon Ambusher::getWeapon() const
{
  return SEMIAUTO;
}

vector<Move> Ambusher::getPriorityList() const
{
  vector<Move> plist;
  plist.push_back(ATTACK);
  return plist;
}
