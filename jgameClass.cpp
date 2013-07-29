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
#include <iostream>
#include "jgameClass.h"
#include "jQuestion.h"

using namespace std;

Game::Game(int aSize)
{
	this->mScore = 0;
	this->mPlaying = true;
	this->mSize = aSize;
	this->mQuestionSet = new Question**[mSize];
	for(int lRow = 0; lRow < aSize; lRow++)
	{
		this->mQuestionSet[lRow] = new Question*[mSize];
	}
	// Need to find a good place to check if all the questions have been played
	// and then set playing to 0.
	loadQuestions();
}

Game::~Game(){ }

int Game::clearScreen(void)
{
	// 25 new lines
	int i;
	for(i = 0; i < 25; i++) cout << "\n";
	return 0;
}

int Game::showBoard(void)
{
	clearScreen();
	int i,j;
	int lPrompt;
	for(j = 0; j < mSize; j++)	// print category names
	{
		cout << mQuestionSet[j][0]->category() << "\t";
	}
	cout << "\n";

	for(i = 0; i < mSize; i++)	// different rows
	{
		for(j=0; j < mSize; j++) // go through each category
		{
			// display empty slot if the question has already been played
			if(mQuestionSet[j][i]->hasBeenPlayed())
			{
				cout << "---\t";
			}
			else	// display the amount the question is worth
			{
				cout << "$" << mQuestionSet[j][i]->price();
			}
		}
		cout << "\n\n";
	}
	// Display the current score and prompt for the next question
	cout << "\t\t Score: " << mScore << "\n";
	cout << "Next question: \n";
	cin >> lPrompt;
	showQuestion(lPrompt);
}

int Game::showScore(void)
{
	// display final score;
}

int Game::showQuestion(int prompt)
{
	// split 2 digit prompt into category and price
	// display the question from the questionSet
}

bool Game::playing()
{
	return mPlaying;
}

int Game::loadQuestions(void)
{
	// this will dynamically load the questions from ./Data
	// XML files (using RapidXML) but for testing
	// purposes the questions will be hardcoded.
	mQuestionSet[0][0] = new Question("Cat1",100,"What...?", 2);
	mQuestionSet[0][0]->addAnswer(0, "Answer a");
	mQuestionSet[0][0]->addAnswer(1, "Answer b");
	mQuestionSet[0][0]->addAnswer(2, "Answer c");
	mQuestionSet[0][0]->addAnswer(3, "Answer d");
}
