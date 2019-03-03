#include "Player.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include <string>
using namespace std;

Player::Player(uint id, int x, int y):id(id),coordinate(Coordinate(x,y))
{
  isdead=0;
}

Player::~Player()
{}

uint Player::getID() const
{
  return this->id;
}

const Coordinate& Player::getCoord() const
{
  return this->coordinate;
}

int Player::getHP() const
{
  return HP;
}

string Player::getBoardID() const
{
  string BoardID;
  BoardID.push_back((this->id/10)+'0');
  BoardID.push_back((this->id%10) + '0');
  return BoardID;
}

Armor Player::getArmor() const
{}

Weapon Player::getWeapon() const
{}

vector<Move> Player::getPriorityList() const
{}

const string Player::getFullName() const
{}

bool Player::isDead() const
{
  if(this->HP<=0)
    return true;
  else
    return false;
}

void Player::executeMove(Move move)
{
  this->coordinate=coordinate+(move);//?
  switch(move)
  {
      case NOOP:
      case ATTACK:
          break;
      case UP:
          cout<<this->getFullName()<<"("<<this->getHP()<<") moved UP.\n";
          break;
      case DOWN:
          cout<<this->getFullName()<<"("<<this->getHP()<<") moved DOWN.\n";
          break;
      case LEFT:
          cout<<this->getFullName()<<"("<<this->getHP()<<") moved LEFT.\n";
          break;
      case RIGHT:
          cout<<this->getFullName()<<"("<<this->getHP()<<") moved RIGHT.\n";
          break;
  }
}

bool Player::attackTo(Player *player)
{
  if(this==player)
    return false;
  int damage=max(Entity::damageForWeapon(this->getWeapon())-Entity::damageReductionForArmor(player->getArmor()),0);
  cout<<this->getFullName() << "(" << this->getHP() << ") ATTACKED "<<player->getFullName()<< "(" << player->getHP() << ")! (-"<<damage<<")\n";
  player->setPlayerHP(player->getHP()-damage);
  return player->isDead();
}

int max(int a,int b)
{
  if(a>b) return a;
  else  return b;
}
void Player::setPlayerHP(int newHP)
{
  this->HP=newHP;
}
