#include "GameParser.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
#include <fstream>
#include <string>
#include <iostream>
#include "Ambusher.h"
#include "Berserk.h"
#include "Dummy.h"
#include "Pacifist.h"
#include "Tracer.h"
#include "Player.h"




//using namespace std;
std::pair<int, std::vector<Player *> *> GameParser::parseFileWithName(const std::string& filename)
{
  std::pair<int, std::vector<Player *> *> mypair;
  std::vector<Player *>  *players=new std::vector<Player *>;
  //mypair.second=players;
  int count=0;
  int boardsize,pcount;
  std::string line;

  std::ifstream myfile (filename);

    while (getline (myfile,line))
    {
        std::string bline;
        std::string cline;
        std::string sid;
        std::string sname,sx,sy;
        int id,coord_x,coord_y;
        Player * newplayer;



	    if(count==0)
	    {
	    	for(int i=12;i<line.size();i++)
	    	{
	    		bline.push_back(line[i]);
	    	}
	    	boardsize = std::stoi(bline);
        mypair.first=boardsize;
	    }
	    else if(count==1)
	    {
	    	for(int i=14;i<line.size();i++)
	    	{
	    		cline.push_back(line[i]);
	    	}
	    	pcount = std::stoi(cline);
	    }
      else
      {
        int index,i;

        for(i=0;line[i]!=':';i++)
        sid.push_back(line[i]);
        index=i+2;
        for(i=index;line[i]!=':';i++)
          sname.push_back(line[i]);
        index=i+2;
        for(i=index;line[i]!=':';i++)
          sx.push_back(line[i]);
        index=i+2;
        for(i=index;i<line.size();i++)
          sy.push_back(line[i]);

        id=std::stoi(sid);
        coord_x=std::stoi(sx);
        coord_y=std::stoi(sy);

        if(sname=="Ambusher")
        {
          newplayer = new Ambusher(id,coord_x,coord_y);
          players->push_back(newplayer);
        }
        else if(sname=="Berserk")
        {
          newplayer = new Berserk(id,coord_x,coord_y);
          players->push_back(newplayer);
        }
        else if(sname=="Dummy")
        {
          newplayer = new Dummy(id,coord_x,coord_y);
          players->push_back(newplayer);
        }
        else if(sname=="Pacifist")
        {
          newplayer = new Pacifist(id,coord_x,coord_y);
          players->push_back(newplayer);
        }
        else if(sname=="Tracer")
        {
          newplayer = new Tracer(id,coord_x,coord_y);
          players->push_back(newplayer);
        }
      }
      count++;

    }

    mypair.second=players;

  return mypair;

}
