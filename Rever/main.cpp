#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

enum { // enumerator, ma typ int, stale musza byc ustawione rosnaco
	 
	EMPTY =0,
	BLACK =1,
	WHITE =2,
	POSSIBLE =3
	};

class board {	// klasa planszy i zachowania kamieni
	
private: 
	int Grid[8][8]; // wielkosc planszy
public:
	//==============================================================================
             void initialState()
			 //przypisuje wartosci wszystkim polom na planszy
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
			 // drukuje plansze z kamieniami w konsoli
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
			 // sprawdza czy prawd¹ jest ze pole jest puste
             {
                  return (Grid[x][y]==EMPTY);
             }

//------------------------------------------------------------------------------			 
             bool inboard(int x, int y)
			 // warunek znajdowania sie w planszy
             {
                  return ( x<8 && x>=0 && y<8 && y>=0);
             }
//------------------------------------------------------------------------------             
             bool checkLoc(int x, int y, int dx, int dy)
			 // sprawdza czy podane wspolrzedne mieszcza sie w planszy
			 // i czy pola o wspolrzednych zmienionych o dany kierunek 
			 //tez mieszcza sie w planszy
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
			 // obracanie kamieni
             {
                  if( Grid[x+dx][y+dy]!=Grid[x][y] ) 
				  // warunek, jezeli "kamien oddalony" jest ró¿ny od wskazanego to odwracaj
                  {
                      Grid[x+dx][y+dy]=Grid[x][y];
                      revert(x+dx,y+dy,dx,dy);
                  }                  
             }
//------------------------------------------------------------------------------            
             bool checkDirection (int x, int y, int colour)
			 // kolejno sprawdza czy w danym kierunku napotyka 
			 //wiecej niz jeden kamien przeciwnego koloru
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
			 // sprawdza na tym miejscu mozna umiescic kamien
             {
                  if ( checkEmpty( x,y)  && checkDirection( x, y, colour) )
				  return true;
                  else 
                  return false;    
             }
//------------------------------------------------------------------------------			
             bool canPut(int x, int y, int colour)
             {
                  if( checkplace( colour, x, y) )
                  {
                         Grid[x][y]=colour;
                         if (3-colour==Grid[x+1][y] && checkLoc(x+1, y,1,0)) revert(x, y,1,0); // right
                             
                         if (3-colour==Grid[x+1][y+1] && checkLoc(x+1, y+1,1,1)) revert(x, y,1,1); // downright
                             
                         if (3-colour==Grid[x+1][y-1] && checkLoc(x+1, y-1,1,-1)) revert(x, y,1,-1); // upright
                             
                         if (3-colour==Grid[x][y+1] && checkLoc(x, y+1,0,1)) revert(x, y,0,1); //down
                             
                         if (3-colour==Grid[x][y-1] && checkLoc(x, y-1,0,-1)) revert(x, y,0,-1); //up
                             
                         if (3-colour==Grid[x-1][y+1] && checkLoc(x-1, y+1,-1,1)) revert(x, y,-1,1); //downleft
                             
                         if (3-colour==Grid[x-1][y-1] && checkLoc(x-1, y-1,-1,-1)) revert(x, y,-1,-1); // upleft
                             
                         if (3-colour==Grid[x-1][y] && checkLoc(x-1, y,-1,0)) revert(x, y,-1,0); //left

						 
                         return true;
                  }
                  else
                  cout<<"Zle pole\n";
                  return false;
			 }

};
//------------------------------------------------------------------------------			
             
int main()
{
	board play;			// wywolanie do klasy board
	bool won=false; 	// warunek dzialania programu
    string player;
    int row,column;
    int turn=BLACK;
    
	play.initialState(); // stan poczatkowy
	play.printBoard();	//wyrysowanie planszy
	
	cout<<endl;
    
    while (! won)
    {
			if (turn==BLACK) player="Czarny";
			else player="Bialy";

            cout<<"Gracz: "<< player <<"\n";
			cout<<"Wiersz: ";
            cin>>row;
            cout<<"Kolumna: ";
            cin>>column;
            cout<<endl;
            row--;
            column--;
            
			// uruchomienie cia³a programu
			//  sprawdzenie mozliwosci umieszczenia kamienia
			if( ! play.canPut(row,column,turn) ) turn=3-turn;
			
			system("cls"); // czyszczenie ekranu, odswierzanie planszy
			
            play.printBoard(); // wyrysowuje plansze
            cout<<endl;
            
            turn=3-turn; // zmiana gracza -- 3-BLACK=WHITE // 3-WHITE=BLACK
            
            
    }
	system("PAUSE");
    return 0;
}