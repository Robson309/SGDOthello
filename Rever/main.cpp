#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

enum {
	 
	EMPTY =0,
	BLACK =1,
	WHITE =2,
	POSSIBLE =3
	};

class board {
	
private: 
	int Grid[8][8];
public:
	//==============================================================================
             void initialState()
             {
                  for (int i=0; i<8; i++)
                  {
                      for (int j=0; j<8; j++)
                      {
                          Grid[i][j]=EMPTY;
                      }
                  }
             
                  Grid[3][3]=BLACK;
                  Grid[3][4]=WHITE;
                  Grid[4][3]=WHITE;
                  Grid[4][4]=BLACK;
             }
//------------------------------------------------------------------------------             
             void printBoard()
             {		 
                  cout<<" |12345678\n----------\n";
                  for (int i=0; i<8; i++)
                  {
                      cout<<i+1<<"|";
                      for (int j=0; j<8; j++)
                      {
						  if (Grid[i][j]==EMPTY) cout << ".";
							else if (Grid[i][j]==BLACK) cout << "x";
								else if (Grid[i][j]==WHITE) cout << "o";
									else cout << "*";
                      }
                      cout<<endl;
                  }
             }
			 
			//------------------------------------------------------------------------------
             bool checkEmpty(int x, int y)
             {
                  return (Grid[x][y]==EMPTY);
             }

//------------------------------------------------------------------------------			 
             bool inboard(int x, int y)
             {
                  return ( x<8 && x>=0 && y<8 && y>=0);
             }
//------------------------------------------------------------------------------             
             bool checkLoc(int x, int y, int dx, int dy)
             {
                  if(!inboard(x,y)) return false;
                  if ( inboard(x+dx, y+dy) )
                  {
                       if ( Grid[x+dx][y+dy]==Grid[x][y] ) return checkLoc(x+dx, y+dy, dx, dy);
                       
                       else
                       {
                           if( Grid[x+dx][y+dy]==EMPTY ) return false;
								else return true;
                       }
                  }
                  else return false;
             }

//------------------------------------------------------------------------------
             void revert(int x, int y, int dx, int dy)
             {
                  if( Grid[x+dx][y+dy]!=Grid[x][y] )
                  {
                      Grid[x+dx][y+dy]=Grid[x][y];
                      revert(x+dx,y+dy,dx,dy);
                  }                  
             }
//------------------------------------------------------------------------------            
             bool checkDirection (int x, int y, int colour)
             {
                  
                         if (3-colour==Grid[x+1][y] && checkLoc(x+1, y,1,0)) return true;  //right
                              
                         if (3-colour==Grid[x+1][y+1] && checkLoc(x+1, y+1,1,1)) return true; //downright
                         
                         if (3-colour==Grid[x+1][y-1] && checkLoc(x+1, y-1,1,-1)) return true; // upright
                             
                         if (3-colour==Grid[x][y+1] && checkLoc(x, y+1,0,1)) return true; //down
                             
                         if (3-colour==Grid[x][y-1] && checkLoc(x, y-1,0,-1)) return true;
                             
                         if (3-colour==Grid[x-1][y+1] && checkLoc(x-1, y+1,-1,1)) return true;
                             
                         if (3-colour==Grid[x-1][y-1] && checkLoc(x-1, y-1,-1,-1)) return true;
                             
                         if (3-colour==Grid[x-1][y] && checkLoc(x-1, y,-1,0)) return true;

				return false;
             }

//------------------------------------------------------------------------------            
             bool checkplace(int colour, int x, int y)
             {
                  if ( checkEmpty( x,y)  && checkDirection( x, y, colour) )
				  return true;
                  else 
                  return false;    
             }

};
            
int main()
{
	board play;
	bool won=false;
    string player;
    int row,column;
    int turn=BLACK;
    cout<<"MAIN OTHELLO";
	play.initialState();
	play.printBoard();
	system("PAUSE");
    return 0;
}