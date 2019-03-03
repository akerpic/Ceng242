#include "GameEngine.h"
#include <cmath>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
GameEngine::GameEngine(uint boardSize, std::vector<Player *> *players):board(boardSize,players)
{
  currentRound=1;
  //this->board = Board(boardSize,players);

}
GameEngine::~GameEngine()
{
  int size=board.getVecSize();
  for(int i=0;i<size;i++)
  {
      board.rmindex(i);
      i--;
      size=board.getVecSize();
  }
  delete board.getVec();
}

const Board& GameEngine::getBoard() const
{
  return board;
}

Player* GameEngine::operator[](uint id) const
{
  int size= board.getVecSize();
  for(int i=0;i< size ;i++)
  {
    if( (*((*board.getVec())[i])).getID()==id )
      return (*board.getVec())[i];
  }
  return nullptr;
}

bool GameEngine::isFinished() const
{
  //std::cout<<"vector size="<<board.getVecSize()<<"\n";
  //std::cout<<"nerde x="<<(*(*(board.getVec()))[0]).getCoord().x<<" y="<<(*(*(board.getVec()))[0]).getCoord().y<<"adı"<<(*(*(board.getVec()))[0]).getFullName()<<"\n";
  if(board.getVecSize()==0)
    return true;
  if(board.getVecSize()==1 &&  board.isCoordHill( (*(*(board.getVec()))[0]).getCoord() ) )
    return true;

  return false;
}

void GameEngine::takeTurn()
{
  std::cout << "-- START ROUND " << currentRound << " --\n";
  board.updateStorm(currentRound);
  for(int i=0;i<100;i++)
  {
    if((*this)[i]!=nullptr && (*(*this)[i]).isDead()==false)
    {
      takeTurnForPlayer(i);
    }
  }
  int size=board.getVecSize();
  /*for(int i=0;i<size;i++)
  {
    if( (*(*(board.getVec()))[i]).isDead() )
    {
      board.rmindex(i);
      i--;
    }
    size=board.getVecSize();
  }*/
  std::cout << "-- END ROUND " << currentRound << " --\n";
  currentRound++;
}

Move GameEngine::takeTurnForPlayer(uint playerID)
{
  int k=0,j=0;
  if((*this)[playerID]==nullptr)
    return NOOP;
  Player * curr_player=(*this)[playerID];
  std::vector<Move> priorities=(*curr_player).getPriorityList();
  std::vector<Coordinate> visibles=board.visibleCoordsFromCoord((*curr_player).getCoord());
  if(board.isStormInCoord((*curr_player).getCoord()))//stormdaysa
  {
    std::cout<<(*curr_player).getFullName()<<"("<<(*curr_player).getHP()<<") is STORMED! (-"<<Entity::stormDamageForRound(this->currentRound)<<")\n";
    (*curr_player).setPlayerHP((*curr_player).getHP()-Entity::stormDamageForRound(this->currentRound));
    if((*curr_player).isDead())
    {
      int del_index=-1;
      for(int k=0;k<board.getVecSize();k++)//silinecek indexi bul
      {
        if( (*(*(board.getVec()))[k]).getID()==playerID )
        {
          del_index=k;
          //std::cout<<"del_index="<<del_index<<"\n";
          break;
        }
      }
      std::cout<<(*curr_player).getFullName()<<"("<<(*curr_player).getHP()<<") DIED.\n";
      board.rmindex(del_index);
      //std::cout<<"storm_mid\n";
      return NOOP;
    }
    //std::cout<<"storm_end\n";
  }
  for(int k=0;k<priorities.size();k++)
  {
    if(priorities[k]==NOOP)
      return NOOP;
    else if(priorities[k]==ATTACK)
    {
      //std::cout<<"attacked\n";
      Player* attacked;
      if(visibles.size()==0)
        continue;
      //this->operator[](coord+(move))
      int min=100;

      for(int i=0;i<visibles.size();i++)
      {
        if(board.operator[](visibles[i])!=nullptr)
        {
          if( (*(board.operator[](visibles[i]))).getID() < min && (*(board.operator[](visibles[i]))).isDead()==false )
            {
              min=(*(board.operator[](visibles[i]))).getID();
              attacked=board.operator[](visibles[i]);
              //std::cout<<"id="<<(*attacked).getID()<<"\n";
            }
        }
      }
      if(min!=100)//is there anyone attacked ?
      {
        (*curr_player).attackTo(attacked);
        int del_index=-1;
        if((*attacked).isDead())//attacked is dead or not?
        {
          for(int j=0;j<board.getVecSize();j++)//silinecek indexi bul
          {
            if( (*(*(board.getVec()))[j]).getID()==(*attacked).getID() )
              {
                del_index=j;
                break;
              }
          }
          std::cout<<(*attacked).getFullName()<<"("<<(*attacked).getHP()<<") DIED.\n";
          board.rmindex(del_index);
        }
        return ATTACK;
      }
      else//if there is no attacked
        continue;
    }

    else if(priorities[k]==UP)
    {
      int man1=manhattan((*curr_player).getCoord().x,(*curr_player).getCoord().y,(board.getSize()-1)/2,(board.getSize()-1)/2);
      int man2=manhattan((*curr_player).getCoord().x,(*curr_player).getCoord().y-1,(board.getSize()-1)/2,(board.getSize()-1)/2);
      //std::cout<<"uman1 "<<man1 <<"man2" << man2;
      if(man2<man1 && board[Coordinate((*curr_player).getCoord().x , (*curr_player).getCoord().y-1)]==nullptr)
      {
        //std::cout<<"up yaptı\n";
        (*curr_player).executeMove(UP);
        return UP;
      }
      else
        continue;
    }
    else if(priorities[k]==DOWN)
    {
      int man1=manhattan((*curr_player).getCoord().x,(*curr_player).getCoord().y,(board.getSize()-1)/2,(board.getSize()-1)/2);
      int man2=manhattan((*curr_player).getCoord().x,(*curr_player).getCoord().y+1,(board.getSize()-1)/2,(board.getSize()-1)/2);
      //std::cout<<"dman1 "<<man1 <<"man2" << man2;

      if(man2<man1 && board[Coordinate((*curr_player).getCoord().x , (*curr_player).getCoord().y+1)]==nullptr )
      {
      //  std::cout<<"down yaptı\n";

        (*curr_player).executeMove(DOWN);
        return DOWN;
      }
      else
        continue;
    }
    else if(priorities[k]==RIGHT)
    {
      int man1=manhattan((*curr_player).getCoord().x,(*curr_player).getCoord().y,(board.getSize()-1)/2,(board.getSize()-1)/2);
      int man2=manhattan((*curr_player).getCoord().x+1,(*curr_player).getCoord().y,(board.getSize()-1)/2,(board.getSize()-1)/2);
      //std::cout<<"rman1 "<<man1 <<"man2" << man2;
      if(man2<man1 && board[Coordinate((*curr_player).getCoord().x+1 , (*curr_player).getCoord().y)]==nullptr)
      {
        //std::cout<<"right yaptı\n";

        (*curr_player).executeMove(RIGHT);
        return RIGHT;
      }
      else
        continue;
    }
    else if(priorities[k]==LEFT)
    {

      int man1=manhattan((*curr_player).getCoord().x,(*curr_player).getCoord().y,(board.getSize()-1)/2,(board.getSize()-1)/2);
      int man2=manhattan((*curr_player).getCoord().x-1,(*curr_player).getCoord().y,(board.getSize()-1)/2,(board.getSize()-1)/2);
      //std::cout<<"man1 "<<man1 <<"man2" << man2;
      if(man2<man1 && board[Coordinate((*curr_player).getCoord().x-1 , (*curr_player).getCoord().y)]==nullptr)
      {
        //std::cout<<"left yaptı\n";
        (*curr_player).executeMove(LEFT);
        return LEFT;
      }
      else
        continue;
    }
  }


  return NOOP;
}

Player* GameEngine::getWinnerPlayer() const
{
  if(!isFinished())
    return nullptr;
  if(board.getVecSize()==0)
    return nullptr;
  if(board.getVecSize()==1)
    return (*(board.getVec()))[0];
  return nullptr;
}
int GameEngine::manhattan(int x1,int y1,int x2,int y2)
{
  return abs(x1-x2)+abs(y1-y2);
}
