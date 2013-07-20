/**********************************
* Jeopardy Game v. 3.0
* 
* Complete rewrite of version 2.0

<<<<<<< HEAD
  @author: 	Joel Cranmer <42.joel.cranmer@gmail.com>
=======
  @author:   Joel Cranmer <42.joel.cranmer@gmail.com>
>>>>>>> 89e39b31ecef3062167e915917601bc0e0e76053
  @created:	2013/06/23
  @modified:	
  @version:	3

*
**********************************/

#include "jgame.h"

int main()
{
	char again = "y"; 
	while ( again == "y" || again == "Y" )
	{
		// start game
		game * jeopardy = new game();

		cout << "Welcome to a new game of Jeopardy.\n\n";

		// while game not done continue playing
		while(jeopardy->playing == 1)
		{

		}
		// when game is finished display the score
		jeopardy->showScore();
		delete jeopardy;
		// Play another game?
		cout << "Do you want to play again? [y/N] \n";
		cin >> again;
	}
	return 0;
}

