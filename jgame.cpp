/**********************************
* Jeopardy Game v. 3.0
* 
* Complete rewrite of version 2.0

  @author:      Joel Cranmer <42.joel.cranmer@gmail.com>
  @created:     2013/06/23
  @modified:    
  @version:     3

* Contains the entry point for the program to execute.
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include "jgameClass.h"
#include <string>

using namespace std;

int main()
{
	bool lAgain = true;
	string lInput;
	while ( lAgain )
	{
		// start game
		Game * lJeopardy = new Game(1);

		cout << "Welcome to a new game of Jeopardy.\n\n";

		// while game not done continue playing
		while(lJeopardy->playing())
		{
			//Start by showing the board
			lJeopardy->showBoard();
			// updates the status (checks if the game is done)
			lJeopardy->updateStatus();
		}
		// when game is finished display the score
		lJeopardy->showScore();
		delete lJeopardy;
		// Play another game?
		cout << "Do you want to play again? [y/N] \n";
		cin >> lInput;
		if(lInput != "")
			lAgain = toupper(lInput[0]) == 'Y';
		else
			lAgain = false;
	}
	return 0;
}

