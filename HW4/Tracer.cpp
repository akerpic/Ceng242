#include "Tracer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
using namespace std;
Tracer::Tracer(uint id, int x, int y):Player(id , x, y)
{
  HP=100;
}
const string Tracer::getFullName() const
{
  string name("Tracer"+getBoardID());
  return name;
}
Armor Tracer::getArmor() const
{
  return BRICK;
}
Weapon Tracer::getWeapon() const
{
  return SHOVEL;
}

vector<Move> Tracer::getPriorityList() const
{
  vector<Move> plist;
  plist.push_back(UP);
  plist.push_back(LEFT);
  plist.push_back(DOWN);
  plist.push_back(RIGHT);
  plist.push_back(ATTACK);
  return plist;
}
