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
#include <stdlib.h>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <string>		// std::string
#include <vector>		// std::vector
#include "jgameClass.h"
#include "jQuestion.h"
#include "RapidXml/rapidxml_utils.hpp"
#include "tinydir/tinydir.h"

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

	for(i = 0; i < mSize; i++)	// different rows (prices)
	{
		for(j=0; j < mSize; j++) // go through each category
		{
			// display empty slot if the question has already been played
			if(mQuestionSet[j][i]->hasBeenPlayed())
			{
				cout << "----\t";
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
	cin >> lPrompt; // get user's question selection
	showQuestion(lPrompt);
	return 0;
}

int Game::showScore(void)
{
	clearScreen();
	// display final score;
	return 0;
}

bool Game::showQuestion(int aPrompt)
{	
	if( aPrompt == 9000 )
	{
		cout << "I'm sorry, Dave. I'm afraid I can't do that.\n";
		return false;
	}
	int lCatagory, lPrice;
	int lPrompt;
	bool lCorrect;
	// split 2 digit prompt into category and price (and zero base)
	lCatagory = (aPrompt / 10 % 10) - 1;	// tens digit
	lPrice = (aPrompt % 10) - 1;			// ones digit
	
	// make sure they are a valid choice
	if( lCatagory >= 0 && lCatagory < this->mSize && lPrice >= 0 && lPrice < this->mSize)
	{
		// make sure it hasn't been played before
		if(!mQuestionSet[lCatagory][lPrice]->hasBeenPlayed())
		{
			// display the question from the questionSet
			mQuestionSet[lCatagory][lPrice]->askQuestion();
			cout << "\n\n";
			mQuestionSet[lCatagory][lPrice]->showAnswers();
		}
		else // has been played
		{
			cout << "This question has already been played.\n";
			return false;
		}
	}
	else // not a valid choice
	{
		cout << "Invalid input: out of bounds.\n";
		return false;
	}
	
	cout << "What is your answer: \n";
	// get user's answer
	cin >> lPrompt;
	// Play the user's answer
	lCorrect = mQuestionSet[lCatagory][lPrice]->play(lPrompt);
	
	if(lCorrect)
	{
		cout << "That is correct!\n";
		// add to the score
		mScore += (lPrice * 100);
	}
	else
	{
		cout << "That is incorrect.\n";
	}
	
	return true;
}

bool Game::playing(void)
{
	return mPlaying;
}

int Game::updateStatus(void)
{
	bool lDone = true; // assume done
	// loop through the questionSet and see if they have all been played
	// for efficency, start with the high dollar/harder questions
	
	// loop through rows (bottom to top)
	for(int i = mSize-1; i >= 0; i--)
	{
		// loop through columns
		for(int j=0; j < mSize; j++)
		{
			// sets done to false if a question hasn't been played
			if( lDone && !mQuestionSet[j][i]->hasBeenPlayed() )
			{
				lDone = false;
			}
		}
	}
	mPlaying = !(lDone);
	return 0;
}

int Game::loadQuestions(void)
{
	/*
	// this will dynamically load the questions from ./Data
	// XML files (using RapidXML) but for testing
	// purposes the questions will be hardcoded.
	mQuestionSet[0][0] = new Question("Cat1",100,"This program is not done yet.");
	mQuestionSet[0][0]->addAnswer(0, "Answer a");
	mQuestionSet[0][0]->addAnswer(1, "Answer b");
	mQuestionSet[0][0]->addAnswer(2, "Answer c");
	mQuestionSet[0][0]->addAnswer(3, "Answer d");
	mQuestionSet[0][0]->setCorrectAns(2);
	*/
	
	/* initialize random seed: */
	srand (time(NULL));
	
	std::vector <std::string> files;
	// get list of xml files
	files = findXML(".");
	
	if( files.size() < mSize)
	{
		cout << "Unable load game: inadequate categories. ("<< files.size() <<")\n";
		return -1;
	}
	
	// shuffle up the list
	std::random_shuffle ( files.begin(), files.end() );
	
	// look in data folder for at least 5 catagory xml documents
		// does the ./Data folder exist?
		// Are there at least 5 *.xml files?
	// load 5 at random
		// - parse each catagory file
			// + is the data tree formatted correctly
			// + are there 5 levels
			// + Is there at least one item per level
		// - load each level
			// + if multiple items in a level, randomly choose one
	for( int f=0; f<mSize; f++ )
	{
		// string lFileLocation = files.at(f);
		// rapidxml::file<> lXmlFile(lFileLocation.data());
		rapidxml::file<> lXmlFile(files.at(f).data());
		rapidxml::xml_document<> lDoc;
		
		int lFileCounter = 1;		// start at 1
		int lLevelCounter = 1;	// start at $100
		int lItemCounter;
		int lChosenItem;
		int lAns[4] = {0, 1, 2, 3};
		rapidxml::xml_node<> * lItem;
		rapidxml::xml_node<> * lAnswerNode;
		
		// Parse the buffer using the xml file parsing library into lDoc
		lDoc.parse<0>(lXmlFile.data());
		//set the root node
		rapidxml::xml_node<> * lRoot_node = lDoc.first_node("items");
		// make sure there are the right number of levels
		if( rapidxml::count_children(lRoot_node) < mSize )
		{
			// bad things are happening
			cout << "Unable load game: inadequate questions in Data/" << files.at(f) << ".\n";
			return -1;
		}
		// go through each Level of question (100,200,300,...)
		for( rapidxml::xml_node<> * lLevel = lRoot_node->first_node("levels"); lLevel; lLevel = lLevel->next_sibling() )
		{
			// make sure that the level id matches
			if( * lLevel->first_attribute("id")->value() != (lLevelCounter * 100) )
			{
				// level doesn't match
				// complain with error/exception
			}
			
			// count the # or items in the level
			//set default to 1
			lChosenItem = 1;
			
			if( rapidxml::count_children(lLevel) > 1 ) // if more than one item in the level
			{
				// pick one at random
				lChosenItem = rand() % rapidxml::count_children(lLevel) + 1;
			}
			
			lItemCounter = 1;
			lItem = lLevel->first_node("item");
			
			// now open the chosen item
			while(lChosenItem > lItemCounter)
			{
				lItem = lItem->next_sibling();
				lItemCounter ++;
			}
			
			//Have the right item, now extract the question and answers.
			mQuestionSet[lFileCounter - 1][lLevelCounter - 1] = new Question("FileName",(lLevelCounter * 100), lItem->first_node("question")->value());
			
			// mix up the answers
			random_shuffle(&lAns[0],&lAns[4]);
			lAnswerNode = lItem->first_node("answers")->first_node("ans");
			// loop through the answers
			for(int i = 0; i < 4; i++)
			{
				//Check if this is the correct answer
				if( lAnswerNode->first_attribute("correct") != 0 && lAnswerNode->first_attribute("correct")->value() == "TRUE" )
				{
					// set the correct answer
					mQuestionSet[lFileCounter - 1][lLevelCounter - 1]->setCorrectAns(lAns[i]);
				}
				// add the answer to the stack
				mQuestionSet[lFileCounter - 1][lLevelCounter - 1]->addAnswer(lAns[i], lAnswerNode->value());
				// go to the next answer exept the last loop
				if( i < 3 ) lAnswerNode = lAnswerNode->next_sibling();
			}
		}
	}
	return 0;
}

std::vector <std::string> Game::findXML ( const char *path)
{
	tinydir_dir dir;
	std::string s;
	std::vector <std::string> output;
	
	// open the current directory
	if (tinydir_open(&dir, path) == -1)
	{
		std::cout << "Error opening directory";
	}
	
	while (dir.has_next)
	{
		tinydir_file file;
		// get the file
		if (tinydir_readfile(&dir, &file) == -1)
		{
			std::cout << "Error getting file";
		}
		
		if (file.is_dir)
		{
			// prevent bad things from happening
			if ( strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0 )
			{
				// look one directory deeper and append the directory to the filename
				std::vector <std::string> returnedVector = findXML(file.name);
				for( unsigned j = 0; j<returnedVector.size();j++)
				{
					//output.push_back( file.name  + "/" + returnedVector.at(j) );
					output.push_back( file.name + std::string("/") + returnedVector.at(j) );
				}
			}
		}
		else
		{
			// print the file's name
			s = file.name;
			// don't include the format file
			if ( (s.find(".xml",0) != -1 || s.find(".XML",0) != -1) && (s.find("format") == -1) )
			{
				output.push_back( file.name );
			}
		}
		// next one
		tinydir_next(&dir);
	}
	return output;
}