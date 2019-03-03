#include "Board.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Board::Board(uint boardSize, std::vector<Player *> *players):boardSize(boardSize)
{
  this->stormwidth=0;
  this->players=players;
}
Board::~Board()
{}
uint Board::getSize() const
{
  return boardSize;
}

bool Board::isCoordInBoard(const Coordinate& coord) const
{
  int x=coord.x;
  int y=coord.y;
  if(x<0 || y<0 || x>=boardSize || y>=boardSize)
    return false;
  else
    return true;
}

bool Board::isStormInCoord(const Coordinate &coord) const
{
  int upleft=stormwidth,downright=boardSize-stormwidth-1;
  if(!isCoordInBoard(coord))
    return false;
  if(isCoordHill(coord))
    return false;
  if(coord.x>=upleft && coord.y>=upleft && coord.x<=downright && coord.y<=downright)
    return false;
  return true;
}
bool Board::isCoordHill(const Coordinate& coord) const
{
  if(coord.x==(boardSize-1)/2 && coord.y ==(boardSize-1)/2)
    return true;
  return false;
}

Player* Board::operator[](const Coordinate& coord) const
{
  for(int i=0;i<players->size();i++)
  {
    if((*players)[i]->getCoord()==coord)
      return (*players)[i];
  }
  return  nullptr;
}

Coordinate Board::calculateCoordWithMove(Move move, const Coordinate &coord) const
{
  int x=coord.x;
  int y=coord.y;
  if(!isCoordInBoard(coord+move))
  {
    //std::cout<<"asdadhere  x=\n"<<(coord+move).x<<(coord+move).y;
    return coord;
  }
  if(this->operator[](coord+(move))!=nullptr)
  {
    //std::cout<<"asdadhere  x=\n"<<(coord+move).x<<(coord+move).y;
    return coord;
  }

  return coord+(move);

}

std::vector<Coordinate> Board::visibleCoordsFromCoord(const Coordinate &coord) const
{
    std::vector<Coordinate> visibles;
    if(!isCoordInBoard(coord))
      return visibles;
    if(coord.y-1>=0)
      visibles.push_back(Coordinate(coord.x, coord.y-1));
    if(coord.y+1<boardSize)
      visibles.push_back(Coordinate(coord.x, coord.y+1));
    if(coord.x-1>=0)
      visibles.push_back(Coordinate(coord.x-1,coord.y));
    if(coord.x+1<boardSize)
      visibles.push_back(Coordinate(coord.x+1,coord.y));
    return visibles;
}

void Board::updateStorm(uint currentRound)
{
  stormwidth=Entity::stormWidthForRound(currentRound);
}

int Board::getVecSize() const
{
  return (*players).size();
}
std::vector<Player *> * Board::getVec() const
{
  return players;
}

void Board::rmindex(int i)
{
  Player * temp=(*players)[i];
  (*players).erase((*players).begin()+i);
  delete temp;
}
/*
void Board::setplayers(std::vector<Player *>  *players)
{
  for(int i=0;i<(*(this->players)).size();i++)
  {
    rmindex(i);
  }
  vector<Player *>  *players=new vector<Player *>;

}*/
