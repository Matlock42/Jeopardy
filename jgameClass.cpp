/**********************************
* Jeopardy Game v. 3.0
* 
* Complete rewrite of version 2.0

  @author:      Joel Cranmer <42.joel.cranmer@gmail.com>
  @created:     2013/06/23
  @modified:    
  @version:     3

*
**********************************/
game::game()
{
<<<<<<< HEAD
	score = 0;
=======
  score = 0;
>>>>>>> 89e39b31ecef3062167e915917601bc0e0e76053
	playing = 1;

	loadQuestions();
}

game::~game(){ }

int game::clearScreen(void)
{
	// 25 new lines
	int i;
	for(i = 0; i < 25; i++) cout << "\n";
	return 0;
}

int game::showBoard(void)
{
	clearScreen();
	int i,j;
	int prompt;
	for(j=0; j<gameSize; j++)	// print category names
	{
		cout << questionSet[j][1].category << "\t";
	}
	cout << "\n";

	for(i=0; i<gameSize; i++)	// different rows
	{
		for(j=0; j<gameSize; j++)
		{
			if(questionSet[j][i].played == 1)
			{
				cout << "---\t";
			}
			else
			{
				cout << "$" << (i+1) << "00\t";	 // disp: $200
			}
		}
		cout << "\n\n";
	}
	cout << "\t\t Score: " << score << "\n";
	cout << "Next question: \n";
	cin >> prompt;
	showQuestion(prompt);
}

int game::showScore(void)
{
	// display final score;
}

int game::showQuestin(int prompt)
{
	// split 2 digit prompt into category and price
	// display the question from the questionSet
}

int game::loadQuestions(void)
{
	// this will dynamically load the questions but for testing
	// purposes the questions will be hardcoded.

	questionSet[0][0].category = "Cat1";
	questionSet[0][0].price = 100;
	questionSet[0][0].question = "What...?";
	questionSet[0][0].a = "Answer a";
	questionSet[0][0].b = "Answer b";	// correct answer
	questionSet[0][0].c = "Answer c";
	questionSet[0][0].d = "Answer d";
	questionSet[0][0].correct = 2;	// points to answer B
	questionSet[0][0].played = 0;	// this question has not been played when initalized
}
