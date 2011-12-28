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


};
            
int main()
{
    cout<<"MAIN OTHELLO";
    return 0;
}